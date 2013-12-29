#include "Planet.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Planet::Planet(const TextureHolder& textures, b2World& world)
{
    const float radius = 300;
    setOrigin(radius, radius);
    m_shapePlanet.setRadius(radius);
    m_shapePlanet.setFillColor(sf::Color::White);

    b2BodyDef PlanetBodyDef;
    PlanetBodyDef.type = b2_staticBody;
    m_body = world.CreateBody(&PlanetBodyDef);

    b2FixtureDef PlanetFixtureDef;
    b2CircleShape PlanetShape;
    PlanetShape.m_radius = radius/SCALE;
    PlanetFixtureDef.shape = &PlanetShape;
    PlanetFixtureDef.density = 1.0f;
    PlanetFixtureDef.userData = this;
    m_body->CreateFixture(&PlanetFixtureDef);

    m_shapeInfluence.setRadius(radius*3);
    m_shapeInfluence.setOrigin(getOrigin().x*2.f, getOrigin().y*2.f);
    m_shapeInfluence.setFillColor(sf::Color(200,100,50,100));
}

void Planet::drawCurrent (sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shapePlanet, states);
    target.draw(m_shapeInfluence, states);
}
