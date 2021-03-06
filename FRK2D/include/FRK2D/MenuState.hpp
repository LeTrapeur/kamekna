#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Graphics/Sprite.hpp>
#include <TGUI/TGUI.hpp>

#include <FRK2D/State.hpp>
#include <FRK2D/SoundPlayer.hpp>

class MenuState : public State
{
    public:
       MenuState(StateStack& stack, Context context);

        virtual void                        draw();
        virtual bool                        update(sf::Time dt);
        virtual bool                        handleEvent(const sf::Event& event);

        void                                updateOptionText();

    private:
            sf::Sprite                      m_backgroundSprite;
            tgui::Gui                       m_gui;

            SoundPlayer&                    m_sounds;
};

#endif // MENUSTATE_H
