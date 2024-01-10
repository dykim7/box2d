#include <Box2D/Box2D.h>
#include <cstdlib>
#include <ctime>
#include <set>
#include "test.h"

class EdgeShapesAndRandomBodiesTest : public Test
{
public:
    EdgeShapesAndRandomBodiesTest()
    {
        // ���� �õ� �ʱ�ȭ
        srand((unsigned)time(0));

        // Edge Shapes ����
        CreateEdgeShape(b2Vec2(-3.0f, -3.0f), b2Vec2(3.0f, -3.0f)); // �Ʒ���
        CreateEdgeShape(b2Vec2(3.0f, -3.0f), b2Vec2(3.0f, 3.0f));   // ������
        CreateEdgeShape(b2Vec2(3.0f, 3.0f), b2Vec2(-3.0f, 3.0f));   // ����
        CreateEdgeShape(b2Vec2(-3.0f, 3.0f), b2Vec2(-3.0f, -3.0f)); // ����

        // �� ���� ������Ʈ�� ���� ��ġ�� ����
        std::set<int> occupiedPositions;
        CreateRandomBody(occupiedPositions);
        CreateRandomBody(occupiedPositions);
    }

    void CreateEdgeShape(const b2Vec2& start, const b2Vec2& end)
    {
        b2BodyDef bodyDef;
        b2Body* body = m_world->CreateBody(&bodyDef);

        b2EdgeShape edgeShape;
        edgeShape.SetTwoSided(start, end);

        body->CreateFixture(&edgeShape, 0.0f);
    }

    void CreateRandomBody(std::set<int>& occupiedPositions)
    {
        int positionIndex;
        do {
            positionIndex = rand() % 36; // 0 ~ 35 ����
        } while (occupiedPositions.find(positionIndex) != occupiedPositions.end());

        occupiedPositions.insert(positionIndex);

        // ��ġ ���
        float x = -2.5f + (positionIndex % 6);
        float y = -2.5f + (positionIndex / 6);

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
    }

    static Test* Create()
    {
        return new EdgeShapesAndRandomBodiesTest;
    }
};

static int testIndex = RegisterTest("Custom", "Edge Shapes03", EdgeShapesAndRandomBodiesTest::Create);
