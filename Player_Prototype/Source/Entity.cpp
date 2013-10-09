#include "Entity.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

namespace
{
    const std::vector<EntityData> dataTable = initializeEntityData();
}

Entity::Entity(b2World& world, Entity::Type type):
    m_body(nullptr)
{
    if(type == Entity::Hero)
    {
        const int PLAYER_WIDTH = 32;
        const int PLAYER_HEIGHT = 64;
//        b2BodyDef PlayerBodyDef;
//        PlayerBodyDef.type = b2_dynamicBody;
//        PlayerBodyDef.position = b2Vec2(1280/2/SCALE, 720/2/SCALE);
//        PlayerBodyDef.fixedRotation = true;
        m_body = world.CreateBody(&dataTable[Entity::Hero].bodyDef);
//
//        for(auto it = dataTable[Entity::Hero].fixturesDef.begin(); it != dataTable[Entity::Hero].fixturesDef.end(); it++)
//        {
//            b2FixtureDef tempFixtureDef;
//            tempFixtureDef = (*it);
//            m_body->CreateFixture(&tempFixtureDef);
//        }

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
        footSensorFixture.userData = ((void*)3);
        m_body->CreateFixture(&footSensorFixture);
    }
    else if (type == Entity::Platform)
    {
        const int FLOOR_WIDTH = 1024;
        const int FLOOR_HEIGHT = 32;
        b2BodyDef GroundBodyDef;
        GroundBodyDef.position = b2Vec2((1280/2)/SCALE, (720-(FLOOR_HEIGHT/2))/SCALE);
        GroundBodyDef.type = b2_staticBody;
        m_body = world.CreateBody(&GroundBodyDef);

        b2FixtureDef GroundFixtureDef;
        b2PolygonShape GroundShape;
        GroundShape.SetAsBox((FLOOR_WIDTH/2.0f)/SCALE, (FLOOR_HEIGHT/2.0f)/SCALE);
        GroundFixtureDef.shape = &GroundShape;
        GroundFixtureDef.density = 1.0f;
        m_body->CreateFixture(&GroundFixtureDef);
    }
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

void Entity::update()
{
    setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
    setRotation(m_body->GetAngle());
}

void Entity::setPosition(float x, float y)
{
    sf::Transformable::setPosition(x,y);
    m_body->SetTransform(b2Vec2(x/SCALE, y/SCALE), m_body->GetAngle());
}

void Entity::setRotation(float angle)
{
    sf::Transformable::setRotation(angle);
    m_body->SetTransform(b2Vec2(sf::Transformable::getPosition().x/SCALE, sf::Transformable::getPosition().y/SCALE), (angle*pi())/180);
}
