#ifndef IA_H
#define IA_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Astronaut.h"

class IA
{
    public:
        IA();
        void addPlayer(Astronaut* player);
        void addEnemy(Astronaut* enemy);
        void updateIA(sf::Time dt, CommandQueue& commands);

    private:
        Astronaut*      m_player;
        Astronaut*      m_enemy;
};

#endif // IA_H
