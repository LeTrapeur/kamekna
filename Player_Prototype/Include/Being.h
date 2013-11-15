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
        };
    public:
        Being(Type type, const TextureHolder& textures, b2World& world);

        void handleEvent(const sf::Event& event);
        void handleRealTimeInput();

        void addFootContact();
        void removeFootContact();

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::Sprite m_sprite;
        unsigned int m_numFootContacts;
};

#endif // HERO_H
