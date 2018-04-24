#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <Box2D/Box2D.h>

#include <FRK2D/Category.hpp>
#include <FRK2D/CommandQueue.hpp>

class Entity;

class MyContactListener : public b2ContactListener
  {
    public:
          explicit  MyContactListener(CommandQueue& commandQueue);

          void      BeginContact(b2Contact* contact);
          void      EndContact(b2Contact* contact);

          bool      matchesCategory(std::pair<Entity*,Entity*>& entities, Category::Type type1, Category::Type type2);

    private:
        CommandQueue&    m_commandQueue;
        bool             SENSOR_FLAG;
  };

#endif // MYCONTACTLISTENER_H
