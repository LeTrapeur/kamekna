#include "Actor.hpp"

#include <FRK2D/ResourceHolder.hpp>
#include <FRK2D/Utility.hpp>
#include <FRK2D/TextNode.hpp>

#include <string>
#include <FRK2D/AnimatedSprite.hpp>

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

//Textures::ID toTextureID(Actor::Type type)
//{
//  switch (type)
//    {
//        case Actor::Hero:
//            return Textures::Hero;
//        case Actor::Enemy:
//            return Textures::Enemy;
//    }
//    return Textures::Hero;
//}

Actor::Actor(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world):
    Entity(createBody(world)),
    m_type(type),
    m_animatedSprite(sf::seconds(0.2), true, false),
    m_walkLeft(),
    m_walkRight(),
    m_walkUp(),
    m_walkDown(),
    m_numFootContacts(1), // TODO remove old contact code
    m_life(100),
    m_lookingOrientation(LookingOrientation::Right),
    m_infoDisplay()
{
    // set up the animations for all four directions (set spritesheet and push frames)
    m_walkDown.setSpriteSheet(textures.get(Textures::Hero));
    m_walkDown.addFrame(sf::IntRect(32, 0, 32, 32));
    m_walkDown.addFrame(sf::IntRect(64, 0, 32, 32));
    m_walkDown.addFrame(sf::IntRect(32, 0, 32, 32));
    m_walkDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    m_walkLeft.setSpriteSheet(textures.get(Textures::Hero));
    m_walkLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    m_walkLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    m_walkLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    m_walkLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    m_walkRight.setSpriteSheet(textures.get(Textures::Hero));
    m_walkRight.addFrame(sf::IntRect(32, 64, 32, 32));
    m_walkRight.addFrame(sf::IntRect(64, 64, 32, 32));
    m_walkRight.addFrame(sf::IntRect(32, 64, 32, 32));
    m_walkRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    m_walkUp.setSpriteSheet(textures.get(Textures::Hero));
    m_walkUp.addFrame(sf::IntRect(32, 96, 32, 32));
    m_walkUp.addFrame(sf::IntRect(64, 96, 32, 32));
    m_walkUp.addFrame(sf::IntRect(32, 96, 32, 32));
    m_walkUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    m_currentAnim = m_walkDown;

    // Player
    // TODO rendre adaptable taille anim (frame)
    sf::Rect<float> spriteBounds(0,0,32,32);// = m_sprite.getGlobalBounds();
    Transformable::setOrigin(sf::Vector2f(spriteBounds.width/2,spriteBounds.height/2));

    b2FixtureDef ActorFixtureDef;
    b2PolygonShape ActorShape;
    ActorShape.SetAsBox((spriteBounds.width/2.0f)/SCALE, (spriteBounds.height/2.0f)/SCALE);
    ActorFixtureDef.shape = &ActorShape;
    ActorFixtureDef.density = 1.0f;
    ActorFixtureDef.friction = 0.4f;

    ActorFixtureDef.userData = this;
    m_body->CreateFixture(&ActorFixtureDef);

//    if(type != Actor::Hero)
//    {
//        std::string textActor(std::to_string(m_life) + " HP");
//        std::unique_ptr<TextNode> nameDisplay(new TextNode(fonts, textActor));
//        nameDisplay->setPosition(0.f, -25.f);
//        m_infoDisplay = nameDisplay.get();
//        attachChild(std::move(nameDisplay));
//	}

}

void Actor::goLeft()
{
    m_isGoingLeft = true;
}

void Actor::walkLeft()
{

    lookLeft();
    m_body->ApplyForce(b2Vec2(m_body->GetMass()*-10,0), m_body->GetWorldCenter(), true);
    m_isGoingLeft = false;
}

void Actor::goRight()
{
    m_isGoingRight = true;
}

void Actor::walkRight()
{
    lookRight();
    m_body->ApplyForce(b2Vec2(m_body->GetMass()*10,0), m_body->GetWorldCenter(), true);
    m_isGoingRight = false;
}

void Actor::goUp()
{
    m_isGoingUp = true;
}

void Actor::walkUp()
{
    lookUp();
    m_body->ApplyForce(b2Vec2(m_body->GetMass()*0,-10), m_body->GetWorldCenter(), true);
    m_isGoingUp = false;
}

void Actor::goDown()
{
    m_isGoingDown = true;
}

void Actor::walkDown()
{
    lookDown();
    m_body->ApplyForce(b2Vec2(-m_body->GetMass()*0,10), m_body->GetWorldCenter(), true);
    m_isGoingDown = false;
}

void Actor::lookLeft()
{
    m_lookingOrientation = LookingOrientation::Left;
}

void Actor::lookRight()
{
    m_lookingOrientation = LookingOrientation::Right;
}

void Actor::lookUp()
{
    m_lookingOrientation = LookingOrientation::Up;
}

void Actor::lookDown()
{
    m_lookingOrientation = LookingOrientation::Down;
}

void Actor::updateLookingDirection()
{
    if(m_lookingOrientation == LookingOrientation::Right)
        this->setScale(1.f, 1.f);
    else if(m_lookingOrientation == LookingOrientation::Left)
        this->setScale(-1.f, 1.f);
}

const int THRESHOLD_VELOCITY = 200;
void Actor::checkMove(sf::Time dt, CommandQueue& commands)
{
    if(m_isGoingLeft && m_body->GetLinearVelocity().x * SCALE > -THRESHOLD_VELOCITY)
    {
        m_currentAnim = m_walkLeft;
        walkLeft();
    }
    else if(m_isGoingRight && m_body->GetLinearVelocity().x * SCALE < THRESHOLD_VELOCITY)
    {
        m_currentAnim = m_walkRight;
        walkRight();
    }
    else if(m_isGoingUp && m_body->GetLinearVelocity().y * SCALE > -THRESHOLD_VELOCITY)
    {
        m_currentAnim = m_walkUp;
        walkUp();
    }
    else if(m_isGoingDown && m_body->GetLinearVelocity().y * SCALE < THRESHOLD_VELOCITY)
    {
        m_currentAnim = m_walkDown;
        walkDown();
    }
    else
        m_animatedSprite.stop();

    m_animatedSprite.play(m_currentAnim);
}

void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_animatedSprite, states);
}

float Actor::getLife() const
{
    return m_life;
}

void Actor::takeDamage(unsigned int damage)
{
    m_life -= damage;
    if(m_life <= 0)
        m_life = 0;
}

void Actor::updateText()
{
    if(m_infoDisplay != nullptr)
        m_infoDisplay->setString(std::to_string(m_life) + " HP");
}

void Actor::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    updateText();
    checkMove(dt, commands);
    //updateLookingDirection();
    m_animatedSprite.update(dt);

    Entity::updateCurrent(dt, commands);

}

bool Actor::isDestroyed() const
{
    return m_life <= 0;
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
b2Body* Actor::createBody(b2World& world)
{
    b2BodyDef ActorBodyDef;
    ActorBodyDef.type = b2_dynamicBody;
    ActorBodyDef.fixedRotation = true;
    ActorBodyDef.linearDamping = 3.5f;
    b2Body* body = world.CreateBody(&ActorBodyDef);

    return body;
}

