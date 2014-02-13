#include "IA.h"

IA::IA():
    m_player(nullptr),
    m_enemy(nullptr)
{
    //ctor
}

void IA::addPlayer(Astronaut* player)
{
    m_player = player;
}

void IA::addEnemy(Astronaut* enemy)
{
    m_enemy = enemy;
}

void IA::updateIA(sf::Time dt, CommandQueue& commands)
{
    if(m_player->getPosition().x > m_enemy->getPosition().x && abs(m_player->getPosition().x - m_enemy->getPosition().x) > 100)
    {
        m_enemy->goRight();
        m_enemy->fire(m_player->getPosition());
    }
    else if(m_player->getPosition().x < m_enemy->getPosition().x && abs(m_player->getPosition().x - m_enemy->getPosition().x) > 100)
    {
        m_enemy->fire(m_player->getPosition());
        m_enemy->goLeft();

    }
}
