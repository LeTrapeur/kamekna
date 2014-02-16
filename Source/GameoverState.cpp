#include "GameoverState.h"
#include "ResourceHolder.h"
#include "MusicPlayer.h"
#include "Utility.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameoverState::GameoverState(StateStack& stack, Context context):
    State(stack, context),
    m_backgroundSprite(),
    m_gameoverText(),
    m_instructionText()
{
    sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Vector2f viewSize = context.window->getView().getSize();

    m_gameoverText.setFont(font);
    m_gameoverText.setString("Game Over ...");
    m_gameoverText.setCharacterSize(70);
    Utility::centerOrigin(m_gameoverText);
    m_gameoverText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

    m_instructionText.setFont(font);
    m_instructionText.setString("(Press Backspace to return to the main menu)");
    Utility::centerOrigin(m_instructionText);
    m_instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);

    getContext().music->setPaused(true);
}

GameoverState::~GameoverState()
{
    getContext().music->setPaused(false);
}

void GameoverState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(m_gameoverText);
    window.draw(m_instructionText);
}

bool GameoverState::update(sf::Time)
{
    return false;
}

bool GameoverState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::BackSpace)
    {
        requestStateClear();
        requestStackPush(States::Menu);
    }

    return false;
}
