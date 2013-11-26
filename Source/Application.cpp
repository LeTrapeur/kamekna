#include "Application.h"
#include "TitleState.h"
#include "GameState.h"
#include "MenuState.h"
#include "PauseState.h"


const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

Application::Application():
    m_window(sf::VideoMode(1280, 720), "Prototype player"),
    m_textures(),
    m_fonts(),
    m_player(),
    m_stateStack(State::Context(m_window, m_textures, m_fonts, m_player))
{
    m_fonts.load(Fonts::Main, "airstrip.ttf");
    m_fonts.load(Fonts::Debug, "arial.ttf");
    m_textures.load(Textures::TitleScreen, "titlescreen.png");

    m_statisticsText.setFont(m_fonts.get(Fonts::Debug));
    m_statisticsText.setString("DEBUG");
    m_statisticsText.setCharacterSize(10);
    m_statisticsText.setColor(sf::Color::Blue);

    registerStates();
    m_stateStack.pushState(States::Title);
}

void Application::processInputs()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        m_stateStack.handleEvent(event);

        if(event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Application::update(sf::Time elapsedTime)
{
    m_stateStack.update(elapsedTime);
}

void Application::render()
{
    m_window.clear(sf::Color::Yellow);
    m_stateStack.draw();

    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_statisticsText);

    m_window.display();
}


void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(m_window.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            processInputs();
            update(TIME_PER_FRAME);

            if (m_stateStack.isEmpty())
                m_window.close();
        }
        updateStatistics(TIME_PER_FRAME);
        render();
    }
}

void Application::updateStatistics(sf::Time elapsedTime)
{
    m_statisticsUpdateTime += elapsedTime;
    m_statisticsNumFrames += 1;

    if(m_statisticsUpdateTime >= sf::seconds(1.0f))
    {
        std::string str = static_cast<std::ostringstream*>(&(std::ostringstream()
        << "Fps: " << m_statisticsNumFrames << "\nTime/update: " << m_statisticsUpdateTime.asMicroseconds()/m_statisticsNumFrames << "us"))
        ->str();
        m_statisticsText.setString(str);

        m_statisticsUpdateTime -= sf::seconds(1.0f);
        m_statisticsNumFrames = 0;
    }
}

void Application::registerStates()
{
        m_stateStack.registerState<TitleState>(States::Title);
        m_stateStack.registerState<MenuState>(States::Menu);
        m_stateStack.registerState<GameState>(States::Game);
        m_stateStack.registerState<PauseState>(States::Pause);
}
