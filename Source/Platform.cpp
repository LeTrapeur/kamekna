#include "Platform.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter


Textures::ID toTextureID(Platform::Type type)
{
    switch (type)
    {
        case Platform::Metal:
            return Textures::Metal;
    }
    return Textures::Metal;
}

// TODO on doit enlever le const car on récupère un pointuer sur la ressource
Platform::Platform(Type type, int width, int height, TextureHolder& textures, b2World& world):
    Entity(),
    m_type(type),
    m_shape(sf::Vector2f(width, height))
{
    setOrigin(sf::Vector2f(width/2,height/2));

    b2BodyDef GroundBodyDef;
    GroundBodyDef.position = b2Vec2((1280/2)/SCALE, (720-(height/2))/SCALE);
    GroundBodyDef.type = b2_staticBody;
    m_body = world.CreateBody(&GroundBodyDef);

    b2FixtureDef GroundFixtureDef;
    b2PolygonShape GroundShape;
    GroundShape.SetAsBox((width/2.0f)/SCALE, (height/2.0f)/SCALE);
    GroundFixtureDef.shape = &GroundShape;
    GroundFixtureDef.density = 1.0f;
    GroundFixtureDef.userData = this;
    m_body->CreateFixture(&GroundFixtureDef);

    sf::Texture& texture = textures.get(Textures::Metal);
    texture.setRepeated(true);
    m_shape.setTexture(texture);
}

void Platform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}
