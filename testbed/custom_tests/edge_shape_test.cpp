#include "test.h"

class EdgeShapeTest : public Test
{
public:
    EdgeShapeTest()
    {
        // Edge Shape 생성
        b2Vec2 v1(0.0f, 0.0f);
        b2Vec2 v2(1.0f, 0.0f);

        b2EdgeShape edge;
        edge.SetTwoSided(v1, v2);

        // 강체 정의
        b2BodyDef bodyDef;
        bodyDef.position.Set(0.0f, 0.0f);

        // Testbed의 세계에 강체 추가
        b2Body* body = m_world->CreateBody(&bodyDef);

        // 강체에 에지 형태의 픽스처 추가
        body->CreateFixture(&edge, 0.0f);
    }

    // 필요한 경우에 추가적인 시뮬레이션 코드 작성
    void Step(Settings& settings) override
    {
        Test::Step(settings);
        // 시뮬레이션 관련 추가적인 코드는 여기에 작성
    }

    static Test* Create()
    {
        return new EdgeShapeTest;
    }
};

// 테스트 등록
static int testIndex = RegisterTest("Custom", "Edge Shape Test", EdgeShapeTest::Create);
