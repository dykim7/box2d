#include <Box2D/Box2D.h>
#include <cstdlib>
#include <ctime>
#include "test.h"

class GroundAndMovingObjectsTest : public Test
{
public:
    GroundAndMovingObjectsTest()
    {
        // 랜덤 시드 초기화
        srand((unsigned)time(0));

        // Ground 생성
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, 0.0f);
        b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
        b2PolygonShape groundBox;
        groundBox.SetAsBox(3.0f, 3.0f); // 6x6 제곱미터
        groundBody->CreateFixture(&groundBox, 0.0f);

        // 첫 번째 물체 생성
        CreateMovingObject();

        // 두 번째 물체 생성
        CreateMovingObject();
    }

    void CreateMovingObject()
    {
        // 물체 위치 랜덤 설정
        float x = ((float)rand() / RAND_MAX) * 5 - 2.5f;
        float y = ((float)rand() / RAND_MAX) * 5 - 2.5f;

        // 동적 강체 정의
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);
        b2Body* body = m_world->CreateBody(&bodyDef);

        // 물체 모양 정의
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(0.5f, 0.5f); // 1x1 크기

        // 픽스처 정의
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);

        // 중앙으로 향하는 속도 설정
        b2Vec2 center(0.0f, 0.0f);
        b2Vec2 direction = center - body->GetPosition();
        direction.Normalize();
        body->SetLinearVelocity(direction); // 중앙으로 이동
    }

    static Test* Create()
    {
        return new GroundAndMovingObjectsTest;
    }
};

static int testIndex = RegisterTest("Custom", "Ground and Moving Objects", GroundAndMovingObjectsTest::Create);
