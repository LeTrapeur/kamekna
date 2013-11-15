#ifndef BEING_H
#define BEING_H

#include "Entity.h"

class Being : public Entity
{
    public:
        enum Type
        {
            Hero,
        };
    public:
        Being(b2World& world);

        void handleEvent(const sf::Event& event);
        void handleRealTimeInput();

        void addFootContact();
        void removeFootContact();

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::RectangleShape m_shape;
        unsigned int m_numFootContacts;
};

#endif // HERO_H
