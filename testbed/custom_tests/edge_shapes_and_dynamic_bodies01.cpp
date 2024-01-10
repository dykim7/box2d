#include <cstdlib>
#include <ctime>
#include "test.h"

class EdgeShapesAndDynamicBodiesTest : public Test
{
public:
    EdgeShapesAndDynamicBodiesTest()
    {
        // ���� �õ� �ʱ�ȭ
        srand((unsigned)time(0));

        // Edge Shapes ����
        CreateEdgeShape(b2Vec2(-3.0f, -3.0f), b2Vec2(3.0f, -3.0f)); // �Ʒ���
        CreateEdgeShape(b2Vec2(3.0f, -3.0f), b2Vec2(3.0f, 3.0f));   // ������
        CreateEdgeShape(b2Vec2(3.0f, 3.0f), b2Vec2(-3.0f, 3.0f));   // ����
        CreateEdgeShape(b2Vec2(-3.0f, 3.0f), b2Vec2(-3.0f, -3.0f)); // ����

        // �� ���� ���� ��ü ����
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
        // ��ü ��ġ ���� ����
        float x = ((float)rand() / RAND_MAX) * 4 - 2; // -2 ~ 2 ����
        float y = ((float)rand() / RAND_MAX) * 4 - 2; // -2 ~ 2 ����

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);

        b2Body* body = m_world->CreateBody(&bodyDef);

        b2PolygonShape box;
        box.SetAsBox(0.5f, 0.5f); // 1x1 ũ��

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
