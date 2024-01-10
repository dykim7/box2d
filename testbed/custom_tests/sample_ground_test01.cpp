#include <Box2D/Box2D.h>
#include <cstdlib>
#include <ctime>
#include "test.h"

class GroundAndMovingObjectsTest : public Test
{
public:
    GroundAndMovingObjectsTest()
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
        CreateMovingObject();

        // �� ��° ��ü ����
        CreateMovingObject();
    }

    void CreateMovingObject()
    {
        // ��ü ��ġ ���� ����
        float x = ((float)rand() / RAND_MAX) * 5 - 2.5f;
        float y = ((float)rand() / RAND_MAX) * 5 - 2.5f;

        // ���� ��ü ����
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);
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

        // �߾����� ���ϴ� �ӵ� ����
        b2Vec2 center(0.0f, 0.0f);
        b2Vec2 direction = center - body->GetPosition();
        direction.Normalize();
        body->SetLinearVelocity(direction); // �߾����� �̵�
    }

    static Test* Create()
    {
        return new GroundAndMovingObjectsTest;
    }
};

static int testIndex = RegisterTest("Custom", "Ground and Moving Objects", GroundAndMovingObjectsTest::Create);
