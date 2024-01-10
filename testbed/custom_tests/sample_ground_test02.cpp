#include <Box2D/Box2D.h>
#include <cstdlib>
#include <ctime>
#include "test.h"

class GroundAndStaticObjectsTest : public Test
{
public:
    GroundAndStaticObjectsTest()
    {
        // ���� �õ� �ʱ�ȭ
        srand((unsigned)time(0));

        // Ground ����
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, 0.0f);
        b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
        b2PolygonShape groundBox;
        groundBox.SetAsBox(3.0f, 3.0f); // 6x6 ��������
        groundBody->CreateFixture(&groundBox, 0.0f);

        // ù ��° ��ü ����
        CreateStaticObject(2.0f); // �׶��� ���� ���� ����

        // �� ��° ��ü ����
        CreateStaticObject(4.0f); // �׶��� ���� ���� ����
    }

    void CreateStaticObject(float height)
    {
        // ��ü ��ġ ���� ����
        float x = ((float)rand() / RAND_MAX) * 5 - 2.5f;
        float y = height; // ���� ����

        // ���� ��ü ����
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);
        bodyDef.gravityScale = 0; // �߷� ���� ����
        b2Body* body = m_world->CreateBody(&bodyDef);

        // ��ü ��� ����
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(0.5f, 0.5f); // 1x1 ũ��

        // �Ƚ�ó ����
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);
    }

    static Test* Create()
    {
        return new GroundAndStaticObjectsTest;
    }
};

static int testIndex = RegisterTest("Custom", "Ground and Static Objects", GroundAndStaticObjectsTest::Create);
