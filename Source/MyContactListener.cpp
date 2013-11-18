#include "MyContactListener.h"

#include "Entity.h"
#include "Being.h"


MyContactListener::MyContactListener()
{
    //ctor
}

void MyContactListener::BeginContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    Being* hero = dynamic_cast<Being*>(A);
    if (hero)
    {
        hero->addFootContact();
    }
    hero = dynamic_cast<Being*>(B);
    if (hero)
    {
        hero->addFootContact();
    }
}

void MyContactListener::EndContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    Being* hero = dynamic_cast<Being*>(A);
    if (hero)
    {
        hero->removeFootContact();
    }
    hero = dynamic_cast<Being*>(B);
    if (hero)
    {
        hero->removeFootContact();
    }
}
