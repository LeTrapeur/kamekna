#include <FRK2D/Application.hpp>
#include <FRK2D/TitleState.hpp>
#include <FRK2D/GameState.hpp>
#include <FRK2D/MenuState.hpp>
#include <FRK2D/PauseState.hpp>
#include <FRK2D/GameoverState.hpp>


const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

Application::Application():
    m_window(sf::VideoMode(1280, 720), "Framework 2D"),
    m_settings(),
    m_textures(),
    m_fonts(),
    m_player(),
    m_music(),
    m_sounds(),
    m_stateStack(State::Context(m_window, m_settings, m_textures, m_fonts, m_player, m_music, m_sounds))
{
    // settings loading
    m_settings.load(Settings::Default, "resources/settings.txt");
    SettingsParser settings = m_settings.get(Settings::Default);
    std::string window_title;
    settings.get("window_title", window_title);
    m_window.setTitle(window_title);

    // load basic resources
    m_fonts.load(Fonts::Main, "resources/fonts/arial.ttf");
    m_fonts.load(Fonts::Debug, "resources/fonts/arial.ttf");
    m_textures.load(Textures::TitleScreen, "resources/titlescreen.png");

    // stats text 
    m_statisticsText.setFont(m_fonts.get(Fonts::Debug));
    m_statisticsText.setString("DEBUG");
    m_statisticsText.setCharacterSize(10);
    m_statisticsText.setColor(sf::Color::Blue);

    registerStates();

    // start title screen
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
    // TODO décalage de quelques pixels entre la fenêtre et le sprite background
    m_window.clear(sf::Color::Black);
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
        std::string str("Fps: " + std::to_string(m_statisticsNumFrames) + "\nTime/update: " + std::to_string(m_statisticsUpdateTime.asMicroseconds()/m_statisticsNumFrames) + "us");
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
    m_stateStack.registerState<GameoverState>(States::Gameover);
}
