#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "SoundPlayer.h"

class MenuState : public State
{
    public:
       MenuState(StateStack& stack, Context context);

        virtual void                        draw();
        virtual bool                        update(sf::Time dt);
        virtual bool                        handleEvent(const sf::Event& event);

        void                                updateOptionText();
    private:
        enum OptionNames
        {
            Play,
            Options,
            Exit,
        };

    private:
            sf::Sprite                      m_backgroundSprite;
            std::vector<sf::Text>           m_options;
            std::size_t                     m_optionIndex;

            SoundPlayer&                    m_sounds;
};

#endif // MENUSTATE_H
