#include "Platform.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Platform::Platform(b2World& world)
{
    const int FLOOR_WIDTH = 1024;
    const int FLOOR_HEIGHT = 32;

    m_shape.setSize(sf::Vector2f(FLOOR_WIDTH,FLOOR_HEIGHT));
    setOrigin(sf::Vector2f(FLOOR_WIDTH/2,FLOOR_HEIGHT/2));
    m_shape.setFillColor(sf::Color::Black);
//    setPosition(1280/2, 720-(FLOOR_HEIGHT/2));// Center

    b2BodyDef GroundBodyDef;
    GroundBodyDef.position = b2Vec2((1280/2)/SCALE, (720-(FLOOR_HEIGHT/2))/SCALE);
    GroundBodyDef.type = b2_staticBody;
    m_body = world.CreateBody(&GroundBodyDef);

    b2FixtureDef GroundFixtureDef;
    b2PolygonShape GroundShape;
    GroundShape.SetAsBox((FLOOR_WIDTH/2.0f)/SCALE, (FLOOR_HEIGHT/2.0f)/SCALE);
    GroundFixtureDef.shape = &GroundShape;
    GroundFixtureDef.density = 1.0f;
    m_body->CreateFixture(&GroundFixtureDef);
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_shape, states);
}

void Platform::update()
{
    setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
    //setRotation(m_body->GetAngle());
}
