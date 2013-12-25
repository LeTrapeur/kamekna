#include "Actor.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "TextNode.h"

#include <string>

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Textures::ID toTextureID(Actor::Type type)
{
    switch (type)
    {
        case Actor::Hero:
            return Textures::Hero;
        case Actor::Enemy:
            return Textures::Enemy;
    }
    return Textures::Hero;
}

Actor::Actor(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world):
    Entity(),
    m_sprite(textures.get(toTextureID(type))),
    m_type(type),
    m_numFootContacts(0),
    m_life(100),
    m_lookingOrientation(LookingOrientation::Right)
{
    // Player
    sf::Rect<float> spriteBounds = m_sprite.getGlobalBounds();
    setOrigin(sf::Vector2f(spriteBounds.width/2,spriteBounds.height/2));

    b2BodyDef ActorBodyDef;
    ActorBodyDef.type = b2_dynamicBody;
    ActorBodyDef.fixedRotation = true;
    ActorBodyDef.linearDamping = 0.2f;
    m_body = world.CreateBody(&ActorBodyDef);

    b2FixtureDef ActorFixtureDef;
    b2PolygonShape ActorShape;
    ActorShape.SetAsBox((spriteBounds.width/2.0f)/SCALE, (spriteBounds.height/2.0f)/SCALE);
    ActorFixtureDef.shape = &ActorShape;
    ActorFixtureDef.density = 1.0f;
    ActorFixtureDef.friction = 0.3f;
    ActorFixtureDef.userData = this;
    m_body->CreateFixture(&ActorFixtureDef);

    //add foot sensor fixture
    b2PolygonShape FootShape;
    FootShape.SetAsBox(((spriteBounds.width-10)/2.0f)/SCALE, 5/SCALE, b2Vec2(0,(spriteBounds.height/2.0f)/SCALE), 0);
    b2FixtureDef footSensorFixture;
    footSensorFixture.shape = &FootShape;
    footSensorFixture.isSensor = true;
    footSensorFixture.userData = this;
    m_body->CreateFixture(&footSensorFixture);

    if(type != Actor::Hero)
    {
        std::string textActor(std::to_string(m_life) + " HP");
        std::unique_ptr<TextNode> nameDisplay(new TextNode(fonts, textActor));
        nameDisplay->setPosition(0.f, -25.f);
        m_infoDisplay = nameDisplay.get();
        attachChild(std::move(nameDisplay));
    }
}

void Actor::jump()
{
    if (m_numFootContacts >= 1)
        m_body->ApplyLinearImpulse(b2Vec2(0,-m_body->GetMass()*8), m_body->GetWorldCenter());
}

void Actor::walkLeft()
{
    if (m_numFootContacts >= 1 && m_body->GetLinearVelocity().x * SCALE > -150)
        m_body->ApplyForce(b2Vec2(-m_body->GetMass()*8,0), m_body->GetWorldCenter());

    m_lookingOrientation = LookingOrientation::Left;
}

void Actor::walkRight()
{
    if (m_numFootContacts >= 1 && m_body->GetLinearVelocity().x * SCALE < 150)
        m_body->ApplyForce(b2Vec2(m_body->GetMass()*8,0), m_body->GetWorldCenter());

    m_lookingOrientation = LookingOrientation::Right;
}

void Actor::addFootContact()
{
    m_numFootContacts++;
}

void Actor::removeFootContact()
{
    m_numFootContacts--;
}

void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

float Actor::getLife() const
{
    return m_life;
}

void Actor::takeDamage(unsigned int damage)
{
    m_life -= damage;
    if(m_life < 0)
        m_life = 0;
}

void Actor::updateText()
{
    if(m_infoDisplay)
        m_infoDisplay->setString(std::to_string(m_life) + " HP");
}

void Actor::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    updateText();
    Entity::updateCurrent(dt, commands);
}

unsigned int Actor::getCategory() const
{
    switch(m_type)
    {
        case Hero:
            return Category::PlayerActor;
        case Enemy:
            return Category::EnemyActor;
    }
}
