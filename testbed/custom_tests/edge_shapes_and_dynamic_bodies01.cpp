#include <cstdlib>
#include <ctime>
#include "test.h"

class EdgeShapesAndDynamicBodiesTest : public Test
{
public:
    EdgeShapesAndDynamicBodiesTest()
    {
        // 랜덤 시드 초기화
        srand((unsigned)time(0));

        // Edge Shapes 생성
        CreateEdgeShape(b2Vec2(-3.0f, -3.0f), b2Vec2(3.0f, -3.0f)); // 아래쪽
        CreateEdgeShape(b2Vec2(3.0f, -3.0f), b2Vec2(3.0f, 3.0f));   // 오른쪽
        CreateEdgeShape(b2Vec2(3.0f, 3.0f), b2Vec2(-3.0f, 3.0f));   // 위쪽
        CreateEdgeShape(b2Vec2(-3.0f, 3.0f), b2Vec2(-3.0f, -3.0f)); // 왼쪽

        // 두 개의 동적 물체 생성
        CreateDynamicBody();
        CreateDynamicBody();
    }

    void CreateEdgeShape(const b2Vec2& start, const b2Vec2& end)
    {
        b2BodyDef bodyDef;
        b2Body* body = m_world->CreateBody(&bodyDef);

        b2EdgeShape edgeShape;
        edgeShape.SetTwoSided(start, end);

        body->CreateFixture(&edgeShape, 0.0f);
    }

    void CreateDynamicBody()
    {
        // 물체 위치 랜덤 설정
        float x = ((float)rand() / RAND_MAX) * 4 - 2; // -2 ~ 2 범위
        float y = ((float)rand() / RAND_MAX) * 4 - 2; // -2 ~ 2 범위

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);

        b2Body* body = m_world->CreateBody(&bodyDef);

        b2PolygonShape box;
        box.SetAsBox(0.5f, 0.5f); // 1x1 크기

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);
    }

    static Test* Create()
    {
        return new EdgeShapesAndDynamicBodiesTest;
    }
};

static int testIndex = RegisterTest("Custom", "Edge Shapes01", EdgeShapesAndDynamicBodiesTest::Create);
