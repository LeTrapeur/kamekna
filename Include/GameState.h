#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "StateStack.h"
#include "World.h"
#include "Player.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class GameState : public State
{
    public:
                            GameState(StateStack& stack, Context context);
        virtual void        draw();
        virtual bool        update(sf::Time dt);
        virtual bool        handleEvent(const sf::Event& event);

    private:
        void                drawHud();

    private:
        World               m_world;
        Player&             m_player;

        sf::RectangleShape  m_lifeBar;
        sf::RectangleShape  m_powerBar;

};

#endif // GAMESTATE_H
