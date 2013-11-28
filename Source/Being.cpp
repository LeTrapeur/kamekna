#include "Being.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "TextNode.h"

#include <string>

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

Being::Being(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world):
    Entity(),
    m_sprite(textures.get(toTextureID(type))),
    m_type(type),
    m_numFootContacts(0),
    m_life(100)
{
    // Player
    sf::Rect<float> spriteBounds = m_sprite.getGlobalBounds();

    setOrigin(sf::Vector2f(spriteBounds.width/2,spriteBounds.height/2));

    b2BodyDef BeingBodyDef;
    BeingBodyDef.type = b2_dynamicBody;
    BeingBodyDef.fixedRotation = true;
    m_body = world.CreateBody(&BeingBodyDef);

    b2FixtureDef BeingBFixtureDef;
    b2PolygonShape BeingShape;
    BeingShape.SetAsBox((spriteBounds.width/2.0f)/SCALE, (spriteBounds.height/2.0f)/SCALE);
    BeingBFixtureDef.shape = &BeingShape;
    BeingBFixtureDef.density = 1.0f;
    BeingBFixtureDef.friction = 0.3f;
    m_body->CreateFixture(&BeingBFixtureDef);

    //add foot sensor fixture
    b2PolygonShape FootShape;
    FootShape.SetAsBox(((spriteBounds.width-10)/2.0f)/SCALE, 5/SCALE, b2Vec2(0,(spriteBounds.height/2.0f)/SCALE), 0);
    b2FixtureDef footSensorFixture;
    footSensorFixture.shape = &FootShape;
    footSensorFixture.isSensor = true;
    footSensorFixture.userData = this;
    m_body->CreateFixture(&footSensorFixture);


    std::string textBeing(std::to_string(m_life) + " HP");

    std::unique_ptr<TextNode> nameDisplay(new TextNode(fonts, textBeing));
    nameDisplay->setPosition(0.f, -25.f);
    attachChild(std::move(nameDisplay));
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
