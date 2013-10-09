#ifndef DATATABLES_H
#define DATATABLES_H

#include <Box2D/Box2D.h>

#include "Entity.h"


struct EntityData
{
    int width;
    int height;
    b2BodyDef bodyDef;
    std::vector<b2FixtureDef> fixturesDef;
};

struct HeroData
{
    int maxSpeed;

};

struct PlatformData
{

};

std::vector<EntityData> initializeEntityData();

#endif // DATATABLES_H
