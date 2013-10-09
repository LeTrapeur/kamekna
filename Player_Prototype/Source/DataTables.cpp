#include "DataTables.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

std::vector<EntityData> initializeEntityData()
{
    std::vector<EntityData> data(Entity::TypeCount);

    data[Entity::Hero].width = 32;
    data[Entity::Hero].height = 64;

    b2BodyDef PlayerBodyDef;
    PlayerBodyDef.type = b2_dynamicBody;
    PlayerBodyDef.position = b2Vec2(1280/2/SCALE, 720/2/SCALE);
    PlayerBodyDef.fixedRotation = true;
    data[Entity::Hero].bodyDef = PlayerBodyDef;

    b2FixtureDef PlayerFixtureDef;
    b2PolygonShape PlayerShape;
    PlayerShape.SetAsBox((32/2.0f)/SCALE, (64/2.0f)/SCALE);
    PlayerFixtureDef.shape = &PlayerShape;
    PlayerFixtureDef.density = 1.0f;
    PlayerFixtureDef.friction = 0.3f;
    data[Entity::Hero].fixturesDef.push_back(PlayerFixtureDef);

    b2PolygonShape FootShape;
    FootShape.SetAsBox(((32-10)/2.0f)/SCALE, 5/SCALE, b2Vec2(0,(64/2.0f)/SCALE), 0);
    b2FixtureDef footSensorFixture;
    footSensorFixture.shape = &FootShape;
    footSensorFixture.isSensor = true;
    footSensorFixture.userData = ((void*)3);
    data[Entity::Hero].fixturesDef.push_back(footSensorFixture);

    return data;
}
