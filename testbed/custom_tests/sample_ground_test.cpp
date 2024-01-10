#include <Box2D/Box2D.h>
#include "test.h"

class GroundTest : public Test
{
public:
    GroundTest()
    {
        // 강체 정의
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, 0.0f); // 원점에 위치

        // Testbed의 세계에 강체 추가
        b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

        // 바닥 모양 정의
        b2PolygonShape groundBox;
        groundBox.SetAsBox(3.0f, 3.0f); // 6x6 제곱미터 크기의 정사각형

        // 강체에 픽스처 추가
        groundBody->CreateFixture(&groundBox, 0.0f);
    }

    // 필요한 경우에 추가적인 시뮬레이션 코드 작성
    void Step(Settings& settings) override
    {
        Test::Step(settings);
        // 시뮬레이션 관련 추가적인 코드는 여기에 작성
    }

    static Test* Create()
    {
        return new GroundTest;
    }
};

// 테스트 등록
static int testIndex = RegisterTest("Custom", "Ground Test", GroundTest::Create);
