#include "Game.h"

const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

Game::Game():
    m_window(sf::VideoMode(1280, 720), "Prototype player"),
    m_world(m_window),
    m_player()
{
        // DEBUG Text
    if (!m_font.loadFromFile("arial.ttf"))
    {
        std::cout << "Unable to load font..." << std::endl;
    }
    m_statisticsText.setFont(m_font);
    m_statisticsText.setString("DEBUG");
    m_statisticsText.setCharacterSize(20);
    m_statisticsText.setColor(sf::Color::Blue);
}

void Game::processInputs()
{
    CommandQueue& commands = m_world.getCommandQueue();

    sf::Event event;
    while(m_window.pollEvent(event))
    {
        m_player.handleEvent(event, commands);

        if(event.type == sf::Event::Closed)
            m_window.close();
    }

    m_player.handleRealTimeInput(commands);
}

void Game::update(sf::Time elapsedTime)
{
    m_world.update(elapsedTime);
}

void Game::render()
{
    m_window.clear(sf::Color::Yellow);

    m_world.draw();

    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_statisticsText);

    m_window.display();
}


void Game::run()
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
        }
        updateStatistics(TIME_PER_FRAME);
        render();
    }
}

void Game::updateStatistics(sf::Time elapsedTime)
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

