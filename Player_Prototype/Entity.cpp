#include "Entity.h"

Entity::Entity()
{

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

void Entity::update()
{

}
