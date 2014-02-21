#ifndef SENSOR_H
#define SENSOR_H

#include "Entity.h"

class Sensor : public Entity
{
    public:
                        Sensor();


    private:
        b2Body*         createBody();
};

#endif // SENSOR_H
