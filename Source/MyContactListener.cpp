#include "MyContactListener.h"

#include "Entity.h"
#include "Actor.h"
#include "Projectile.h"


MyContactListener::MyContactListener()
{
    //ctor
}

void MyContactListener::BeginContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());

    Actor* actor = dynamic_cast<Actor*>(A);
    Projectile* projectile = dynamic_cast<Projectile*>(B);
    if(actor && projectile)
    {
        if(actor->getCategory() == Category::EnemyActor && projectile->getCategory() == Category::AlliedProjectile)
        {
            actor->takeDamage(5);
        }
    }
//    Actor* actor = dynamic_cast<Actor*>(A);
//    if (actor)
//    {
//        actor->addFootContact();
//        return;
//    }
//    actor = dynamic_cast<Actor*>(B);
//    if (actor)
//    {
//        actor->addFootContact();
//        return
//    }

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
