#include "MyContactListener.h"

#include "Entity.h"
#include "Actor.h"


MyContactListener::MyContactListener()
{
    //ctor
}

void MyContactListener::BeginContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    Actor* actor = dynamic_cast<Actor*>(A);
    if (actor)
    {
        actor->addFootContact();
    }
    actor = dynamic_cast<Actor*>(B);
    if (actor)
    {
        actor->addFootContact();
    }
}

void MyContactListener::EndContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    Actor* actor = dynamic_cast<Actor*>(A);
    if (actor)
    {
        actor->removeFootContact();
    }
    actor = dynamic_cast<Actor*>(B);
    if (actor)
    {
        actor->removeFootContact();
    }
}
