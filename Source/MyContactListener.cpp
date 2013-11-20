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
    Being* being = dynamic_cast<Being*>(A);
    if (being)
    {
        being->addFootContact();
    }
    being = dynamic_cast<Being*>(B);
    if (being)
    {
        being->addFootContact();
    }
}

void MyContactListener::EndContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    Being* being = dynamic_cast<Being*>(A);
    if (being)
    {
        being->removeFootContact();
    }
    being = dynamic_cast<Being*>(B);
    if (being)
    {
        being->removeFootContact();
    }
}
