#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, m_world(*context.window, *context.fonts)
, m_player(*context.player)
{
}

void GameState::draw()
{
        m_world.draw();
}

bool GameState::update(sf::Time dt)
{
        m_world.update(dt);

        CommandQueue& commands = m_world.getCommandQueue();
        m_player.handleRealTimeInput(commands);

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
