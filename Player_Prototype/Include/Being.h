#ifndef BEING_H
#define BEING_H

#include "Entity.h"
#include "ResourceHolder.h"
#include "Category.h"

class Being : public Entity
{
    public:
        enum Type
        {
            Hero,
        };
    public:
        Being(Type type, const TextureHolder& textures, b2World& world);

        void jump();
        void walkLeft();
        void walkRight();
        //to be improved
        void thrusterUp();
        void thrusterDown();
        void thrusterLeft();
        void thrusterRight();

        void addFootContact();
        void removeFootContact();

        virtual unsigned int getCategory() const;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::Sprite m_sprite;
        unsigned int m_numFootContacts;

        Type m_type;
};

#endif // HERO_H
