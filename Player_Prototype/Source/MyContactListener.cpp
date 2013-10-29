#include "MyContactListener.h"

#include "Entity.h"
#include "Hero.h"


MyContactListener::MyContactListener()
{
    //ctor
}

void MyContactListener::BeginContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    Hero* hero = dynamic_cast<Hero*>(A);
    if (hero)
    {
        hero->addFootContact();
    }
    hero = dynamic_cast<Hero*>(B);
    if (hero)
    {
        hero->addFootContact();
    }
}

void MyContactListener::EndContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    Hero* hero = dynamic_cast<Hero*>(A);
    if (hero)
    {
        hero->removeFootContact();
    }
    hero = dynamic_cast<Hero*>(B);
    if (hero)
    {
        hero->removeFootContact();
    }
}
