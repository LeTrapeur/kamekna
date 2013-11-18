#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Command.h"
#include "CommandQueue.h"

class Player
{
    public:
        explicit Player();
        void handleEvent(const sf::Event& event, CommandQueue& commands);
        void handleRealTimeInput(CommandQueue& commands);
};

#endif // PLAYER_H
