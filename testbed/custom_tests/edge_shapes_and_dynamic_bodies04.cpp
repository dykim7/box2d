#include <Box2D/Box2D.h>
#include <cstdlib>
#include <ctime>
#include "test.h"

// Box2D Testbed �ڵ带 �����Ͽ� �� ��ü�� ���θ� ���� �����̰� �ε������� �ϰڽ��ϴ�.
// �� ��ü�� �ʱ� ��ġ�� ������ ��, �߾� ���� �Ǵ� �ٸ� ��ü�� ���� �����̵��� ���� �ӵ��� �����մϴ�.
// �� ��ü�� ���� �ٸ� ��ġ�� �����Ƿ�, �� ��ü�� ���� �ݴ� ���⿡ ��ġ�� ��ü�� ���� ������ ���Դϴ�.

class EdgeShapesAndMovingBodiesTest : public Test
{
public:
    EdgeShapesAndMovingBodiesTest()
    {
        srand((unsigned)time(0)); // ���� �õ� �ʱ�ȭ

        // Edge Shape ����
        CreateEdgeShape(b2Vec2(-3.0f, -3.0f), b2Vec2(3.0f, -3.0f)); // �Ʒ���
        CreateEdgeShape(b2Vec2(3.0f, -3.0f), b2Vec2(3.0f, 3.0f));   // ������
        CreateEdgeShape(b2Vec2(3.0f, 3.0f), b2Vec2(-3.0f, 3.0f));   // ����
        CreateEdgeShape(b2Vec2(-3.0f, 3.0f), b2Vec2(-3.0f, -3.0f)); // ����

        // �� ���� ���� ��ü ���� �� �ʱ� ��ġ ����
        b2Body* bodyA = CreateDynamicBody();
        b2Body* bodyB = CreateDynamicBody();

        // ���θ� ���� �����̵��� ����
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
        // ��ü ��ġ ���� ����
        int gridX = rand() % 6;
        int gridY = rand() % 6;
        float x = -2.5f + gridX;
        float y = -2.5f + gridY;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);
        bodyDef.gravityScale = 0.0f; // �߷� ���� ����
        b2Body* body = m_world->CreateBody(&bodyDef);

        b2PolygonShape box;
        box.SetAsBox(0.5f, 0.5f); // 1x1 ũ��

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
