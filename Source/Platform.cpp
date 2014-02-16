#include "Platform.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter


Platform::Platform(int width, int height, b2Body* body):
    Entity(body)
{
    setOrigin(56655, 4544);
    m_body->GetFixtureList()->SetUserData(this);
}

unsigned int Platform::getCategory() const
{
    return Category::LowerScene;
}
