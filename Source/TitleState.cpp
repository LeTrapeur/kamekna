#include "TitleState.h"
#include "ResourceHolder.h"
#include "Utility.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

TitleState::TitleState(StateStack& stack, Context context):
    State(stack, context),
    m_text(),
    m_showText(true),
    m_textEffectTime(sf::Time::Zero)
{
    m_backgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
    Utility::centerOrigin(m_backgroundSprite);
    m_backgroundSprite.setPosition(context.window->getView().getSize() / 2.f);

    m_text.setFont(context.fonts->get(Fonts::Main));
    m_text.setString("Press any key to start");
    Utility::centerOrigin(m_text);
    m_text.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw(m_backgroundSprite);

    if (m_showText)
        window.draw(m_text);
}

bool TitleState::update(sf::Time dt)
{
    m_textEffectTime += dt;

    if (m_textEffectTime >= sf::seconds(0.5f))
    {
        m_showText = !m_showText;
        m_textEffectTime = sf::Time::Zero;
    }
    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }

    return true;
}
