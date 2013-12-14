#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include "Actor.h"
#include "Projectile.h"

class TextNode;

class Astronaut : public Actor
{
    public:
                                Astronaut(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world);

        void                    thrusterUp();
        void                    thrusterDown();
        void                    thrusterLeft();
        void                    thrusterRight();

        void                    fire(const sf::Vector2f& targetPos);

        float                   getPower() const;

    private:
        virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);
        void                    checkThrusters();
        void                    createBullets(SceneNode& node, const TextureHolder& textures, b2World& world) const;
        void                    createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures, b2World& world) const;
        void                    checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

    private:
        float                   m_power;
        bool                    m_isThrusting;
        sf::Clock               m_powerRecovery;
        sf::Time                m_powerRecoveryTime;
        TextNode*               m_powerDisplay;

        Command                 m_fireCommand;
        bool                    m_isFiring;
        sf::Time                m_fireCountdown;
        sf::Vector2f            m_targetPos;

};

#endif // ASTRONAUT_H
