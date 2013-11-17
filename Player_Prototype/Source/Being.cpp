#include "Being.h"
#include "ResourceHolder.h"
// Being => walk left.. etc jump
// Astronaut => thrusters

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Textures::ID toTextureID(Being::Type type)
{
    switch (type)
    {
        case Being::Hero:
            return Textures::Hero;
    }
    return Textures::Hero;
}

Being::Being(Type type, const TextureHolder& textures, b2World& world):
    Entity(),
    m_sprite(textures.get(toTextureID(type))),
    m_type(type),
    m_numFootContacts(0)
{
    // Player
    sf::Rect<float> spriteBounds = m_sprite.getGlobalBounds();

    setOrigin(sf::Vector2f(spriteBounds.width/2,spriteBounds.height/2));

    b2BodyDef PlayerBodyDef;
    PlayerBodyDef.type = b2_dynamicBody;
    PlayerBodyDef.fixedRotation = true;
    m_body = world.CreateBody(&PlayerBodyDef);

    b2FixtureDef PlayerFixtureDef;
    b2PolygonShape PlayerShape;
    PlayerShape.SetAsBox((spriteBounds.width/2.0f)/SCALE, (spriteBounds.height/2.0f)/SCALE);
    PlayerFixtureDef.shape = &PlayerShape;
    PlayerFixtureDef.density = 1.0f;
    PlayerFixtureDef.friction = 0.3f;
    m_body->CreateFixture(&PlayerFixtureDef);

    //add foot sensor fixture
    b2PolygonShape FootShape;
    FootShape.SetAsBox(((spriteBounds.width-10)/2.0f)/SCALE, 5/SCALE, b2Vec2(0,(spriteBounds.height/2.0f)/SCALE), 0);
    b2FixtureDef footSensorFixture;
    footSensorFixture.shape = &FootShape;
    footSensorFixture.isSensor = true;
    footSensorFixture.userData = this;
    m_body->CreateFixture(&footSensorFixture);
}

void Being::jump()
{
    if (m_numFootContacts >= 1)
        m_body->ApplyLinearImpulse(b2Vec2(0,-m_body->GetMass()*8), m_body->GetWorldCenter());
}

void Being::walkLeft()
{
    if (m_numFootContacts >= 1 && m_body->GetLinearVelocity().x * SCALE > -150)
        m_body->ApplyForce(b2Vec2(-m_body->GetMass()*8,0), m_body->GetWorldCenter());
}

void Being::walkRight()
{
    if (m_numFootContacts >= 1 && m_body->GetLinearVelocity().x * SCALE < 150)
        m_body->ApplyForce(b2Vec2(m_body->GetMass()*8,0), m_body->GetWorldCenter());
}

void Being::handleRealTimeInput()
{

    // Thrusters
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_body->GetLinearVelocity().y * SCALE < -300)
    {
        m_body->ApplyForce(b2Vec2(0, m_body->GetMass()*25), m_body->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_body->GetLinearVelocity().y * SCALE > -300)
    {
        m_body->ApplyForce(b2Vec2(0, -m_body->GetMass()*25), m_body->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && m_body->GetLinearVelocity().x * SCALE < 300)
    {
        m_body->ApplyForce(b2Vec2(m_body->GetMass()*10, 0), m_body->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && m_body->GetLinearVelocity().x * SCALE > -300)
    {
        m_body->ApplyForce(b2Vec2(-m_body->GetMass()*10, 0), m_body->GetWorldCenter());
    }
}

void Being::addFootContact()
{
    m_numFootContacts++;
}

void Being::removeFootContact()
{
    m_numFootContacts--;
}

void Being::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

unsigned int Being::getCategory() const
{
    switch(m_type)
    {
        case Hero:
        return Category::PlayerBeing;
    }
}

