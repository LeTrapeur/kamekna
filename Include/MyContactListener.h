#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <Box2D/Box2D.h>

#include "Category.h"
#include "CommandQueue.h"

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
  };

#endif // MYCONTACTLISTENER_H
