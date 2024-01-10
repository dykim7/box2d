#include <Box2D/Box2D.h>
#include <cstdlib>
#include <ctime>
#include "test.h"

class GroundAndStaticObjectsTest : public Test
{
public:
    GroundAndStaticObjectsTest()
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
        CreateStaticObject(2.0f); // 그라운드 위의 높이 설정

        // 두 번째 물체 생성
        CreateStaticObject(4.0f); // 그라운드 위의 높이 설정
    }

    void CreateStaticObject(float height)
    {
        // 물체 위치 랜덤 설정
        float x = ((float)rand() / RAND_MAX) * 5 - 2.5f;
        float y = height; // 높이 설정

        // 동적 강체 정의
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);
        bodyDef.gravityScale = 0; // 중력 영향 없음
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
    }

    static Test* Create()
    {
        return new GroundAndStaticObjectsTest;
    }
};

static int testIndex = RegisterTest("Custom", "Ground and Static Objects", GroundAndStaticObjectsTest::Create);
