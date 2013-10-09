#include "DataTables.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter


// todo enlever les static (vars globales)
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
    static b2PolygonShape PlayerShape;
    PlayerShape.SetAsBox((32/2.0f)/SCALE, (64/2.0f)/SCALE);
    PlayerFixtureDef.shape = &PlayerShape;
    PlayerFixtureDef.density = 1.0f;
    PlayerFixtureDef.friction = 0.3f;
    data[Entity::Hero].fixturesDef.push_back(PlayerFixtureDef);

    b2FixtureDef footSensorFixtureDef;
    static b2PolygonShape FootShape;
    FootShape.SetAsBox(((32-10)/2.0f)/SCALE, 5/SCALE, b2Vec2(0,(64/2.0f)/SCALE), 0);
    footSensorFixtureDef.shape = &FootShape;
    footSensorFixtureDef.isSensor = true;
    footSensorFixtureDef.userData = ((void*)3);
    data[Entity::Hero].fixturesDef.push_back(footSensorFixtureDef);

    data[Entity::Platform].width = 1024;
    data[Entity::Platform].height = 32;

    b2BodyDef GroundBodyDef;
    GroundBodyDef.position = b2Vec2((1280/2)/SCALE, (720-(32/2))/SCALE);
    GroundBodyDef.type = b2_staticBody;
    data[Entity::Platform].bodyDef = GroundBodyDef;

    b2FixtureDef GroundFixtureDef;
    static b2PolygonShape GroundShape;
    GroundShape.SetAsBox((1024/2.0f)/SCALE, (32/2.0f)/SCALE);
    GroundFixtureDef.shape = &GroundShape;
    GroundFixtureDef.density = 1.0f;
    data[Entity::Platform].fixturesDef.push_back(GroundFixtureDef);

    return data;
}
