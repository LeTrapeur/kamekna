#include <FRK2D/PauseState.hpp>
#include <FRK2D/ResourceHolder.hpp>
#include <FRK2D/MusicPlayer.hpp>
#include <FRK2D/Utility.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, Context context):
    State(stack, context),
    m_backgroundSprite(),
    m_pausedText(),
    m_instructionText()
{
    sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Vector2f viewSize = context.window->getView().getSize();

    m_pausedText.setFont(font);
    m_pausedText.setString("Game Paused");
    m_pausedText.setCharacterSize(70);
    Utility::centerOrigin(m_pausedText);
    m_pausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

    m_instructionText.setFont(font);
    m_instructionText.setString("(Press Backspace to return to the main menu)");
    Utility::centerOrigin(m_instructionText);
    m_instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);

    getContext().music->setPaused(true);
}

PauseState::~PauseState()
{
    getContext().music->setPaused(false);
}

void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(m_pausedText);
    window.draw(m_instructionText);
}

bool PauseState::update(sf::Time)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Escape)
    {
        // Escape pressed, remove itself to return to the game
        requestStackPop();
    }

    if (event.key.code == sf::Keyboard::BackSpace)
    {
        // Escape pressed, remove itself to return to the game
        requestStateClear();
        requestStackPush(States::Menu);
    }

    return false;
}
