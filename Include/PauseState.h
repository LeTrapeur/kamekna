#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State
{
        public:
                                        PauseState(StateStack& stack, Context context);
            virtual void                draw();
            virtual bool                update(sf::Time dt);
            virtual bool                handleEvent(const sf::Event& event);

        private:
            sf::Sprite                  m_backgroundSprite;
            sf::Text                    m_pausedText;
            sf::Text                    m_instructionText;
};

#endif // PAUSESTATE_H
