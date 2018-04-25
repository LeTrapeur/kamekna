#include <FRK2D/State.hpp>
#include <FRK2D/StateStack.hpp>


State::Context::Context(sf::RenderWindow& window, SettingsHolder& settings, TextureHolder& textures, FontHolder& fonts, Player& player, MusicPlayer& music, SoundPlayer& sounds, TiledMapHolder& maps):
    window(&window),
    settings(&settings),
    textures(&textures),
    fonts(&fonts),
    player(&player),
    music(&music),
    sounds(&sounds),
    maps(&maps)
{}

State::State(StateStack& stack, Context context):
    m_stack(&stack),
    m_context(context)
{}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
    m_stack->pushState(stateID);
}

void State::requestStackPop()
{
    m_stack->popState();
}

void State::requestStateClear()
{
    m_stack->clearStates();
}

State::Context State::getContext() const
{
    return m_context;
}
