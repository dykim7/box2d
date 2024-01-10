#include "test.h"

class EdgeShapeTest : public Test
{
public:
    EdgeShapeTest()
    {
        // Edge Shape ����
        b2Vec2 v1(0.0f, 0.0f);
        b2Vec2 v2(1.0f, 0.0f);

        b2EdgeShape edge;
        edge.SetTwoSided(v1, v2);

        // ��ü ����
        b2BodyDef bodyDef;
        bodyDef.position.Set(0.0f, 0.0f);

        // Testbed�� ���迡 ��ü �߰�
        b2Body* body = m_world->CreateBody(&bodyDef);

        // ��ü�� ���� ������ �Ƚ�ó �߰�
        body->CreateFixture(&edge, 0.0f);
    }

    // �ʿ��� ��쿡 �߰����� �ùķ��̼� �ڵ� �ۼ�
    void Step(Settings& settings) override
    {
        Test::Step(settings);
        // �ùķ��̼� ���� �߰����� �ڵ�� ���⿡ �ۼ�
    }

    static Test* Create()
    {
        return new EdgeShapeTest;
    }
};

// �׽�Ʈ ���
static int testIndex = RegisterTest("Custom", "Edge Shape Test", EdgeShapeTest::Create);
