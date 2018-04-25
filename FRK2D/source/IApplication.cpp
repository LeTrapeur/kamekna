#include <FRK2D/IApplication.hpp>

const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

IApplication::IApplication():
    m_window(sf::VideoMode(800, 600), "window"),
    m_settings(),
    m_textures(),
    m_fonts(),
    m_player(),
    m_music(),
    m_sounds(),
    m_maps(),
    m_stateStack(State::Context(m_window, m_settings, m_textures, m_fonts, m_player, m_music, m_sounds, m_maps))
{}

void IApplication::processInputs()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        m_stateStack.handleEvent(event);

        if(event.type == sf::Event::Closed)
            m_window.close();
    }
}

void IApplication::update(sf::Time elapsedTime)
{
    m_stateStack.update(elapsedTime);
}

void IApplication::render()
{
    m_window.clear(sf::Color::Black);
    m_stateStack.draw();

    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_statisticsText);

    m_window.display();
}


void IApplication::run()
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

void IApplication::updateStatistics(sf::Time elapsedTime)
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

