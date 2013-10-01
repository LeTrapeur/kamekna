#include "Game.h"

int numFootContacts = 0;
const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter


Game::Game():
    m_window(sf::VideoMode(1280, 720), "Prototype player"),
    m_world(b2Vec2(0, 15.0f)),
    m_gameView(m_window.getView()),
    m_miniMapView(m_window.getView())
{
    m_window.setView(m_gameView);
    m_window.setFramerateLimit(60);
    m_miniMapView.zoom(4.0f);
    m_miniMapView.setViewport(sf::FloatRect(0.85f, 0.f, 0.15f, 0.15f));

    numFootContacts = 0;
    m_world.SetContactListener(&m_contactListener);


        //Floor
    const int FLOOR_WIDTH = 1024;
    const int FLOOR_HEIGHT = 32;

    m_groundShape.setSize(sf::Vector2f(FLOOR_WIDTH,FLOOR_HEIGHT));
    m_groundShape.setOrigin(sf::Vector2f(FLOOR_WIDTH/2,FLOOR_HEIGHT/2));
    m_groundShape.setFillColor(sf::Color::Black);
    m_groundShape.setPosition(1280/2, 720-(FLOOR_HEIGHT/2));// Center

    b2BodyDef GroundBodyDef;
    GroundBodyDef.position = b2Vec2(m_groundShape.getPosition().x/SCALE, m_groundShape.getPosition().y/SCALE);
    GroundBodyDef.type = b2_staticBody;
    m_groundBody = m_world.CreateBody(&GroundBodyDef);

    b2FixtureDef GroundFixtureDef;
    b2PolygonShape GroundShape;
    GroundShape.SetAsBox((FLOOR_WIDTH/2.0f)/SCALE, (FLOOR_HEIGHT/2.0f)/SCALE);
    GroundFixtureDef.shape = &GroundShape;
    GroundFixtureDef.density = 1.0f;
    m_groundBody->CreateFixture(&GroundFixtureDef);

    // Player
    const int PLAYER_WIDTH = 32;
    const int PLAYER_HEIGHT = 64;

    m_playerShape.setSize(sf::Vector2f(PLAYER_WIDTH,PLAYER_HEIGHT));
    m_playerShape.setOrigin(sf::Vector2f(PLAYER_WIDTH/2,PLAYER_HEIGHT/2));
    m_playerShape.setFillColor(sf::Color::Red);
    m_playerShape.setPosition(1280/2, 720/2);// Center

    b2BodyDef PlayerBodyDef;
    PlayerBodyDef.type = b2_dynamicBody;
    PlayerBodyDef.position = b2Vec2(m_playerShape.getPosition().x/SCALE, m_playerShape.getPosition().y/SCALE);
    PlayerBodyDef.fixedRotation = true;
    m_playerBody = m_world.CreateBody(&PlayerBodyDef);

    b2FixtureDef PlayerFixtureDef;
    b2PolygonShape PlayerShape;
    PlayerShape.SetAsBox((PLAYER_WIDTH/2.0f)/SCALE, (PLAYER_HEIGHT/2.0f)/SCALE);
    PlayerFixtureDef.shape = &PlayerShape;
    PlayerFixtureDef.density = 1.0f;
    PlayerFixtureDef.friction = 0.3f;
    m_playerBody->CreateFixture(&PlayerFixtureDef);

    //add foot sensor fixture
    PlayerShape.SetAsBox(((PLAYER_WIDTH-10)/2.0f)/SCALE, 5/SCALE, b2Vec2(0,(PLAYER_HEIGHT/2.0f)/SCALE), 0);
    PlayerFixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = m_playerBody->CreateFixture(&PlayerFixtureDef);
    footSensorFixture->SetUserData( (void*)3 );

        // DEBUG Text
    if (!m_font.loadFromFile("arial.ttf"))
    {
        std::cout << "Unable to load font..." << std::endl;
    }
    m_debugText.setFont(m_font);
    m_debugText.setString("DEBUG");
    m_debugText.setCharacterSize(24);
    m_debugText.setColor(sf::Color::Blue);
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        if (event.type == sf::Event::Resized)
        {}
        if (event.type == sf::Event::KeyPressed)
        {
        // Jumping
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                if (numFootContacts >= 1)
                    m_playerBody->ApplyLinearImpulse(b2Vec2(0,-m_playerBody->GetMass()*8), m_playerBody->GetWorldCenter());
            }
        }
    }
}

void Game::update()
{
    // Moving left/right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    {
        if (numFootContacts >= 1 && m_playerBody->GetLinearVelocity().x * SCALE > -150)
            m_playerBody->ApplyForce(b2Vec2(-m_playerBody->GetMass()*8,0), m_playerBody->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (numFootContacts >= 1 && m_playerBody->GetLinearVelocity().x * SCALE < 150)
            m_playerBody->ApplyForce(b2Vec2(m_playerBody->GetMass()*8,0), m_playerBody->GetWorldCenter());
    }

    // Thrusters
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        m_playerBody->ApplyForce(b2Vec2(0, m_playerBody->GetMass()*25), m_playerBody->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        m_playerBody->ApplyForce(b2Vec2(0, -m_playerBody->GetMass()*25), m_playerBody->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        m_playerBody->ApplyForce(b2Vec2(m_playerBody->GetMass()*10, 0), m_playerBody->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        m_playerBody->ApplyForce(b2Vec2(-m_playerBody->GetMass()*10, 0), m_playerBody->GetWorldCenter());
    }
    // Update physic
    m_world.Step(1.0f/60.0f, 8, 4);

    // Aplly physic to objects
    m_groundShape.setPosition(m_groundBody->GetPosition().x * SCALE, m_groundBody->GetPosition().y * SCALE);
    m_playerShape.setPosition(m_playerBody->GetPosition().x * SCALE, m_playerBody->GetPosition().y * SCALE);

    // DEBUG
    std::string str = static_cast<std::ostringstream*>(&(std::ostringstream() << "X: " << static_cast<int>(m_playerBody->GetPosition().x * SCALE) << " Y: " << static_cast<int>(m_playerBody->GetPosition().y * SCALE)
                                                     << "\nvX: " << static_cast<int>(m_playerBody->GetLinearVelocity().x * SCALE) << " vY: " << static_cast<int>(m_playerBody->GetLinearVelocity().y * SCALE)))
                                                     ->str();
    m_debugText.setString(str);
}

void Game::render()
{
    m_window.clear(sf::Color::White);
    m_gameView.setCenter(m_playerShape.getPosition());
    m_window.setView(m_gameView);
    m_window.draw(m_groundShape);
    m_window.draw(m_playerShape);
    m_debugText.setPosition(sf::Vector2f(m_window.mapPixelToCoords(sf::Vector2i(0,0))));
    m_window.draw(m_debugText);

    m_window.setView(m_miniMapView);
    m_window.draw(m_groundShape);
    m_window.draw(m_playerShape);

    m_window.display();
}

void Game::run()
{
    while(m_window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

