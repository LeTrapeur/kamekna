#include "MyContactListener.h"

#include "Entity.h"
#include "Actor.h"
#include "Projectile.h"
#include "GravityZone.h"


MyContactListener::MyContactListener(CommandQueue& commandQueue):
    m_commandQueue(commandQueue),
    SENSOR_FLAG(false)
{}

void MyContactListener::BeginContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    SENSOR_FLAG = false;
    if(contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
        SENSOR_FLAG = true;

    std::pair<Entity*, Entity*> entities = std::make_pair(A,B);

    if(matchesCategory(entities, Category::EnemyActor, Category::AlliedProjectile))
    {
        auto& enemy = static_cast<Actor&>(*entities.first);
        auto& projectile = static_cast<Projectile&>(*entities.second);
        if(projectile.getTotalVelocity() > projectile.getMinVelocityDamage())
        {
            enemy.takeDamage(projectile.getDamage());
            enemy.playLocalSound(m_commandQueue, SoundEffect::Impact);
            projectile.destroy();
        }
    }

    if(matchesCategory(entities, Category::PlayerActor, Category::EnemyProjectile))
    {
        auto& player = static_cast<Actor&>(*entities.first);
        auto& projectile = static_cast<Projectile&>(*entities.second);
        if(projectile.getTotalVelocity() > projectile.getMinVelocityDamage())
        {
            player.takeDamage(projectile.getDamage());
            player.playLocalSound(m_commandQueue, SoundEffect::Impact);
            projectile.destroy();
        }
    }

    if(matchesCategory(entities, Category::Actor, Category::PhysicalObject))
    {
        auto& actor = static_cast<Actor&>(*entities.first);
        if(SENSOR_FLAG)
            actor.addFootContact();
    }

    if(matchesCategory(entities, Category::Projectile, Category::PhysicalObject))
    {
        auto& projectile = static_cast<Projectile&>(*entities.first);
        projectile.destroy();
    }

    if(matchesCategory(entities, Category::Actor, Category::GravityZone))
    {
        std::cout << "Entering zone !" << std::endl;
        auto& actor = static_cast<Actor&>(*entities.first);
        auto& zone = static_cast<GravityZone&>(*entities.second);

        actor.setGravityActivated(false);
        zone.addActorInside();
    }
}

void MyContactListener::EndContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());

    SENSOR_FLAG = false;
    if(contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
        SENSOR_FLAG = true;

    std::pair<Entity*, Entity*> entities = std::make_pair(A,B);

    if(matchesCategory(entities, Category::Actor, Category::PhysicalObject))
    {
        auto& actor = static_cast<Actor&>(*entities.first);
        if(SENSOR_FLAG)
            actor.removeFootContact();
    }

    if(matchesCategory(entities, Category::Actor, Category::GravityZone))
    {
        std::cout << "Leaving zone !" << std::endl;
        auto& actor = static_cast<Actor&>(*entities.first);
        auto& zone = static_cast<GravityZone&>(*entities.second);

        actor.setGravityActivated(true);
        zone.removeActorInside();
    }
}

bool MyContactListener::matchesCategory(std::pair<Entity*,Entity*>& entities, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = entities.first->getCategory();
    unsigned int category2 = entities.second->getCategory();

    if(type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if(type1 & category2 && type2 & category1)
    {
        std::swap(entities.first, entities.second);
        return true;
    }
    else
    {
        return false;
    }
}
