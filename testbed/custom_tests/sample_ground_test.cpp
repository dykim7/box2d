#include <Box2D/Box2D.h>
#include "test.h"

class GroundTest : public Test
{
public:
    GroundTest()
    {
        // ��ü ����
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, 0.0f); // ������ ��ġ

        // Testbed�� ���迡 ��ü �߰�
        b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

        // �ٴ� ��� ����
        b2PolygonShape groundBox;
        groundBox.SetAsBox(3.0f, 3.0f); // 6x6 �������� ũ���� ���簢��

        // ��ü�� �Ƚ�ó �߰�
        groundBody->CreateFixture(&groundBox, 0.0f);
    }

    // �ʿ��� ��쿡 �߰����� �ùķ��̼� �ڵ� �ۼ�
    void Step(Settings& settings) override
    {
        Test::Step(settings);
        // �ùķ��̼� ���� �߰����� �ڵ�� ���⿡ �ۼ�
    }

    static Test* Create()
    {
        return new GroundTest;
    }
};

// �׽�Ʈ ���
static int testIndex = RegisterTest("Custom", "Ground Test", GroundTest::Create);
