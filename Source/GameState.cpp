#include "GameState.h"
#include "MusicPlayer.h"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, m_world(*context.window, *context.fonts, *context.sounds)
, m_player(*context.player)
{
    m_lifeBar.setSize(sf::Vector2f(m_world.getPlayerLife() * 3, 25));
    m_lifeBar.setPosition(10, 10);
    m_lifeBar.setFillColor(sf::Color(55, 190, 255, 200));
    m_powerBar.setSize(sf::Vector2f(m_world.getPlayerPower() * 3, 25));
    m_powerBar.setPosition(10, 45);
    m_powerBar.setFillColor(sf::Color(255, 128, 0, 200));

    context.music->setVolume(5.f);
    context.music->play(Music::GameTheme);
}

void GameState::draw()
{
    m_world.draw();
    drawHud();
}

bool GameState::update(sf::Time dt)
{
    m_world.update(dt);

    if(m_world.getPlayerLife() <= 0.0f)
        requestStackPush(States::Gameover);

    CommandQueue& commands = m_world.getCommandQueue();

    m_player.handleRealTimeInput(commands);
    m_player.updateMouseWorldPosition(m_world.getMouseWorldPosition());

    m_lifeBar.setSize(sf::Vector2f(m_world.getPlayerLife() * 3, 25));
    m_powerBar.setSize(sf::Vector2f(m_world.getPlayerPower() * 3, 25));

    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    // Game input handling
    CommandQueue& commands = m_world.getCommandQueue();
    m_player.handleEvent(event, commands);

     //Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPush(States::Pause);
    }
    return true;
}

void GameState::drawHud()
{

    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(m_lifeBar);
    window.draw(m_powerBar);
}
