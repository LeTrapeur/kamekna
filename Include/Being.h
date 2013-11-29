#ifndef BEING_H
#define BEING_H

#include "Entity.h"
#include "ResourceHolder.h"

class Being : public Entity
{
    public:
        enum Type
        {
            Hero,
            Monster,
        };

    public:
        explicit                Being(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world);

        void                    jump();
        void                    walkLeft();
        void                    walkRight();

        void                    addFootContact();
        void                    removeFootContact();

        virtual unsigned int    getCategory() const;

        float                   getLife() const;

    private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite              m_sprite;
        unsigned int            m_numFootContacts;

        Type m_type;

        unsigned int            m_life;
};

#endif // HERO_H
