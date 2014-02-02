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
    Entity(createBody(world)),
    m_type(type),
    m_shape(sf::Vector2f(width, height))
{
    setOrigin(sf::Vector2f(width/2,height/2));

    b2FixtureDef GroundFixtureDef;
    b2PolygonShape GroundShape;
    GroundShape.SetAsBox((width/2.0f)/SCALE, (height/2.0f)/SCALE);
    GroundFixtureDef.shape = &GroundShape;
    GroundFixtureDef.density = 1.0f;
    GroundFixtureDef.userData = this;
    m_body->CreateFixture(&GroundFixtureDef);

    // TODO Voir la destruction du pointeur
    sf::Texture* texture = new sf::Texture(textures.get(Textures::Metal));
    texture->setRepeated(true);
    m_shape.setTexture(texture);
    m_shape.setTextureRect(sf::IntRect(0, 0, m_shape.getSize().x, m_shape.getSize().y)); // Proportionel
}

void Platform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

b2Body* Platform::createBody(b2World& world)
{
    b2BodyDef GroundBodyDef;
    GroundBodyDef.type = b2_staticBody;
    b2Body* body = world.CreateBody(&GroundBodyDef);

    return body;
}
