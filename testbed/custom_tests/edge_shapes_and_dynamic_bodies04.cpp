#include <Box2D/Box2D.h>
#include <cstdlib>
#include <ctime>
#include "test.h"

// Box2D Testbed 코드를 수정하여 두 객체가 서로를 향해 움직이고 부딪히도록 하겠습니다.
// 각 객체의 초기 위치를 설정한 후, 중앙 지점 또는 다른 객체를 향해 움직이도록 선형 속도를 설정합니다.
// 두 객체가 서로 다른 위치에 있으므로, 각 객체는 서로 반대 방향에 위치한 객체를 향해 움직일 것입니다.

class EdgeShapesAndMovingBodiesTest : public Test
{
public:
    EdgeShapesAndMovingBodiesTest()
    {
        srand((unsigned)time(0)); // 랜덤 시드 초기화

        // Edge Shape 생성
        CreateEdgeShape(b2Vec2(-3.0f, -3.0f), b2Vec2(3.0f, -3.0f)); // 아래쪽
        CreateEdgeShape(b2Vec2(3.0f, -3.0f), b2Vec2(3.0f, 3.0f));   // 오른쪽
        CreateEdgeShape(b2Vec2(3.0f, 3.0f), b2Vec2(-3.0f, 3.0f));   // 위쪽
        CreateEdgeShape(b2Vec2(-3.0f, 3.0f), b2Vec2(-3.0f, -3.0f)); // 왼쪽

        // 두 개의 동적 물체 생성 및 초기 위치 설정
        b2Body* bodyA = CreateDynamicBody();
        b2Body* bodyB = CreateDynamicBody();

        // 서로를 향해 움직이도록 설정
        b2Vec2 directionToB = bodyB->GetPosition() - bodyA->GetPosition();
        b2Vec2 directionToA = bodyA->GetPosition() - bodyB->GetPosition();
        directionToB.Normalize();
        directionToA.Normalize();

        bodyA->SetLinearVelocity(directionToB);
        bodyB->SetLinearVelocity(directionToA);
    }

    void CreateEdgeShape(const b2Vec2& start, const b2Vec2& end)
    {
        b2BodyDef bodyDef;
        b2Body* body = m_world->CreateBody(&bodyDef);

        b2EdgeShape edgeShape;
        edgeShape.SetTwoSided(start, end);

        body->CreateFixture(&edgeShape, 0.0f);
    }

    b2Body* CreateDynamicBody()
    {
        // 물체 위치 랜덤 설정
        int gridX = rand() % 6;
        int gridY = rand() % 6;
        float x = -2.5f + gridX;
        float y = -2.5f + gridY;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);
        bodyDef.gravityScale = 0.0f; // 중력 영향 제거
        b2Body* body = m_world->CreateBody(&bodyDef);

        b2PolygonShape box;
        box.SetAsBox(0.5f, 0.5f); // 1x1 크기

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);
        return body;
    }

    static Test* Create()
    {
        return new EdgeShapesAndMovingBodiesTest;
    }
};

static int testIndex = RegisterTest("Custom", "Edge Shapes04", EdgeShapesAndMovingBodiesTest::Create);
