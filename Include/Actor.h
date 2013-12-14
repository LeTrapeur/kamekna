#ifndef ACTOR_H
#define ACTOR_H

#include "Entity.h"
#include "ResourceHolder.h"

class Actor : public Entity
{
    public:
        enum Type
        {
            Hero,
            Enemy,
        };

    public:
        explicit                Actor(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world);

        void                    jump();
        void                    walkLeft();
        void                    walkRight();

        void                    addFootContact();
        void                    removeFootContact();

        virtual unsigned int    getCategory() const;

        float                   getLife() const;

    private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        sf::Sprite              m_sprite;
        unsigned int            m_numFootContacts;

        Type                    m_type;

        unsigned int            m_life;
};

#endif // ACTOR_H
