#include "Astronaut.h"
#include "Actor.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "TextNode.h"

#include <string>
#include <cmath>

// TODO Vitesse max

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Astronaut::Astronaut(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world):
    Actor(type, textures, fonts, world),
    m_power(100.f),
    m_powerRecoveryTime(sf::seconds(3.f)),
    m_isThrusting(false),
    m_powerDisplay(nullptr),
    m_fireCommand(),
    m_targetPos()
{
    if(type != Actor::Hero)
    {
        std::unique_ptr<TextNode> powerDisplay(new TextNode(fonts, (std::to_string(m_power) + " PW")));
        powerDisplay->setPosition(0.f, -50.f);
        m_powerDisplay = powerDisplay.get();
        attachChild(std::move(powerDisplay));
    }

    m_powerRecovery.restart();

    m_fireCommand.category = Category::UpperScene;
    m_fireCommand.action =
    [this, &textures, &world] (SceneNode& node, sf::Time)
    {
        createBullets(node, textures, world);
    };
}

void Astronaut::thrusterUp()
{
    if (m_body->GetLinearVelocity().y * SCALE < 300 && m_power)
        m_body->ApplyForce(b2Vec2(0, m_body->GetMass()*25), m_body->GetWorldCenter());

    m_isThrusting = true;
}

void Astronaut::thrusterDown()
{
    if (m_body->GetLinearVelocity().y * SCALE > -300 && m_power)
        m_body->ApplyForce(b2Vec2(0, -m_body->GetMass()*25), m_body->GetWorldCenter());

    m_isThrusting = true;
}

void Astronaut::thrusterLeft()
{
    if (m_body->GetLinearVelocity().x * SCALE < 300 && m_power)
        m_body->ApplyForce(b2Vec2(m_body->GetMass()*10, 0), m_body->GetWorldCenter());

    m_isThrusting = true;
}

void Astronaut::thrusterRight()
{
    if (m_body->GetLinearVelocity().x * SCALE > -300 && m_power)
        m_body->ApplyForce(b2Vec2(-m_body->GetMass()*10, 0), m_body->GetWorldCenter());

    m_isThrusting = true;
}

float Astronaut::getPower() const
{
    return m_power;
}
// TODO prendre en compte le dt pour enlever le clock
// TODO à nettoyer
void Astronaut::checkThrusters(sf::Time dt, CommandQueue& commands)
{
    static bool isPlayed = false;
    if(m_isThrusting)
    {
        m_powerRecovery.restart();
        m_power--;
        isPlayed = false;
    }
    else if(m_powerRecovery.getElapsedTime() > m_powerRecoveryTime)
    {
        if(!isPlayed)
        {
            playLocalSound(commands, SoundEffect::Regenerate);
            isPlayed = true;
        }
        m_power++;
    }

    if(m_power < 0)
        m_power = 0;
    if(m_power > 100)
        m_power = 100;

    m_isThrusting = false;

    // TODO update text
    if(m_powerDisplay)
        m_powerDisplay->setString(std::to_string(m_power) + " PW");
}

// 1 prendre dans player la position de la souris avec Event (voir si c'est relatif à la fenetre )ensuite l'envoyer à fire et mettre a jour une targetDirection et calsuler la direction de la bullet
// 2 passer window à player
// limiter le radius de tir
void Astronaut::fire(const sf::Vector2f& targetPos)
{
    m_isFiring = true;
    m_targetPos = targetPos;
}

void Astronaut::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)
{
    if(m_isFiring && m_fireCountdown <= sf::Time::Zero)
    {
        playLocalSound(commands, SoundEffect::AlliedGunfire);
        commands.push(m_fireCommand);
        m_fireCountdown += sf::seconds(1.f/(4.f));
        m_isFiring = false;
    }
    else if(m_fireCountdown > sf::Time::Zero)
    {
        m_fireCountdown -= dt;
        m_isFiring = false;
    }
}
// TODO const correctness problème
void Astronaut::createBullets(SceneNode& node, const TextureHolder& textures, b2World& world) const
{
    Projectile::Type type = Projectile::AlliedBullet;

    // Gun position
    if(m_lookingOrientation == LookingOrientation::Right)
        createProjectile(node, type, 0.30f, 0.0f, textures, world);
    else if(m_lookingOrientation == LookingOrientation::Left)
        createProjectile(node, type, -0.30f, 0.0f, textures, world);
}

// TODO à nettoyer
// TODO const correctness problème
void Astronaut::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures, b2World& world) const
{
    std::unique_ptr<Projectile> projectile(new Projectile(type, textures, world, 5));

    sf::Vector2f offset(xOffset * m_sprite.getGlobalBounds().width, yOffset * m_sprite.getGlobalBounds().height); // offset
    projectile->setPosition((this->m_body->GetWorldCenter().x * SCALE) + offset.x, (this->m_body->GetWorldCenter().y * SCALE) + offset.y);

    sf::Vector2f astronautPos(this->m_body->GetWorldCenter().x * SCALE, this->m_body->GetWorldCenter().y * SCALE); // position de lasronaut

    sf::Vector2f projectileDirection(m_targetPos - astronautPos);
    projectileDirection = Utility::unitVector(projectileDirection);

    // 75 deg cone to shoot
    if(projectileDirection.y > 0.75f)
        projectileDirection.y = 0.75f;
    if(projectileDirection.y < -0.75f)
        projectileDirection.y = -0.75f;

    projectileDirection *= 100.f; // Pour avoir un angle en deg

    float vx;
    if(m_lookingOrientation == LookingOrientation::Left)
        vx = -20.f;
    else
        vx = 20.f;

    float vy = 20.f * std::sin((projectileDirection.y*Utility::pi())/180.f); // sin(radians)

    projectile->m_body->SetLinearVelocity(b2Vec2(vx, vy));
    node.attachChild(std::move(projectile));
}

void Astronaut::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    checkThrusters(dt, commands);
    checkProjectileLaunch(dt, commands);
    Actor::updateCurrent(dt, commands);
}
