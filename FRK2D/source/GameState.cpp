#include <FRK2D/GameState.hpp>
#include <FRK2D/MusicPlayer.hpp>

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, m_world(*context.window, *context.fonts, *context.sounds)
, m_player(*context.player)
{

    // TODO set default music theme
    //context.music->setVolume(5.f);
    //context.music->play(Music::GameTheme);
}

void GameState::draw()
{
    m_world.draw();
}

bool GameState::update(sf::Time dt)
{
    m_world.update(dt);

    if(false) // TODO condition de fin 
        requestStackPush(States::Gameover);

    CommandQueue& commands = m_world.getCommandQueue();

    m_player.handleRealTimeInput(commands);
    m_player.updateMouseWorldPosition(m_world.getMouseWorldPosition());

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
}
