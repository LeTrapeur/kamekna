#include "Being.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Being::Being(b2World& world):
    Entity(world),
    m_numFootContacts(0)
{
    // Player
    const int PLAYER_WIDTH = 32;
    const int PLAYER_HEIGHT = 64;

    setOrigin(sf::Vector2f(PLAYER_WIDTH/2,PLAYER_HEIGHT/2));
    m_shape.setSize(sf::Vector2f(PLAYER_WIDTH,PLAYER_HEIGHT));
    m_shape.setFillColor(sf::Color::Red);

    b2BodyDef PlayerBodyDef;
    PlayerBodyDef.type = b2_dynamicBody;
    PlayerBodyDef.position = b2Vec2(1280/2/SCALE, 720/2/SCALE);
    PlayerBodyDef.fixedRotation = true;
    m_body = world.CreateBody(&PlayerBodyDef);

    b2FixtureDef PlayerFixtureDef;
    b2PolygonShape PlayerShape;
    PlayerShape.SetAsBox((PLAYER_WIDTH/2.0f)/SCALE, (PLAYER_HEIGHT/2.0f)/SCALE);
    PlayerFixtureDef.shape = &PlayerShape;
    PlayerFixtureDef.density = 1.0f;
    PlayerFixtureDef.friction = 0.3f;
    m_body->CreateFixture(&PlayerFixtureDef);

    //add foot sensor fixture
    b2PolygonShape FootShape;
    FootShape.SetAsBox(((PLAYER_WIDTH-10)/2.0f)/SCALE, 5/SCALE, b2Vec2(0,(PLAYER_HEIGHT/2.0f)/SCALE), 0);
    b2FixtureDef footSensorFixture;
    footSensorFixture.shape = &FootShape;
    footSensorFixture.isSensor = true;
    footSensorFixture.userData = this;
    m_body->CreateFixture(&footSensorFixture);
}

void Being::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Jumping
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            if (m_numFootContacts >= 1)
                m_body->ApplyLinearImpulse(b2Vec2(0,-m_body->GetMass()*8), m_body->GetWorldCenter());
        }
    }
}

void Being::handleRealTimeInput()
{
    // Moving left/right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    {
        if (m_numFootContacts >= 1 && m_body->GetLinearVelocity().x * SCALE > -150)
            m_body->ApplyForce(b2Vec2(-m_body->GetMass()*8,0), m_body->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (m_numFootContacts >= 1 && m_body->GetLinearVelocity().x * SCALE < 150)
            m_body->ApplyForce(b2Vec2(m_body->GetMass()*8,0), m_body->GetWorldCenter());
    }

    // Thrusters
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_body->GetLinearVelocity().y * SCALE < -300)
    {
        m_body->ApplyForce(b2Vec2(0, m_body->GetMass()*25), m_body->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_body->GetLinearVelocity().y * SCALE > -300)
    {
        m_body->ApplyForce(b2Vec2(0, -m_body->GetMass()*25), m_body->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && m_body->GetLinearVelocity().x * SCALE < 300)
    {
        m_body->ApplyForce(b2Vec2(m_body->GetMass()*10, 0), m_body->GetWorldCenter());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && m_body->GetLinearVelocity().x * SCALE > -300)
    {
        m_body->ApplyForce(b2Vec2(-m_body->GetMass()*10, 0), m_body->GetWorldCenter());
    }
}

void Being::addFootContact()
{
    m_numFootContacts++;
}

void Being::removeFootContact()
{
    m_numFootContacts--;
}

void Being::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

