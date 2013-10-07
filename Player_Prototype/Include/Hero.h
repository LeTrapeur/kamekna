#ifndef HERO_H
#define HERO_H

#include "Entity.h"

class Hero : public Entity
{
    public:
        Hero(b2World& world);

        void handleEvent(const sf::Event& event);
        void handleRealTimeInput();

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::RectangleShape m_shape;
};

#endif // HERO_H
