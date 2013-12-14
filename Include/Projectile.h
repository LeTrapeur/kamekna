#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
#include "ResourceHolder.h"

class Projectile : public Entity
{
    public:
        enum Type
        {
            AlliedBullet,
            EnemyBullet,
            TypeCount
        };

    public:
        Projectile(Type type, const TextureHolder& textures, b2World& world);

        virtual unsigned int getCategory() const;
        int getMaxSpeed() const;

    private:
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        Type m_type;
        sf::Sprite m_sprite;

};

#endif // PROJECTILE_H
