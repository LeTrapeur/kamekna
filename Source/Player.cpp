#include "Player.h"

#include "Astronaut.h"

Player::Player()
{
        // Set initial key bindings
        m_keyBinding[sf::Keyboard::Q] = MoveLeft;
        m_keyBinding[sf::Keyboard::D] = MoveRight;
        m_keyBinding[sf::Keyboard::Space] = Jump;
        m_keyBinding[sf::Keyboard::Key::F] = Fire;
        m_keyBinding[sf::Keyboard::Left] = ThursterLeft;
        m_keyBinding[sf::Keyboard::Right] = ThursterRight;
        m_keyBinding[sf::Keyboard::Up] = ThursterUp;
        m_keyBinding[sf::Keyboard::Down] = ThursterDown;

        // Set initial action bindings
        initializeActions();

        for (auto it = m_actionBinding.begin(); it!= m_actionBinding.end(); ++it)
            (*it).second.category = Category::PlayerActor;

}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
         auto found = m_keyBinding.find(event.key.code);
            if (found != m_keyBinding.end() && !isRealtimeAction(found->second))
                commands.push(m_actionBinding[found->second]);
    }
}

void Player::handleRealTimeInput(CommandQueue& commands)
{
    // Traverse all assigned keys and check if they are pressed
    for (auto it = m_keyBinding.begin(); it!= m_keyBinding.end(); ++it)
    {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed((*it).first) && isRealtimeAction((*it).second))
            commands.push(m_actionBinding[(*it).second]);
    }
}

void Player::updateMouseWorldPosition(const sf::Vector2f& pos)
{
    m_mouseWorldPos = pos;
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
    // Remove all keys that already map to action
    for (auto it = m_keyBinding.begin(); it != m_keyBinding.end(); )
    {
        if (it->second == action)
            m_keyBinding.erase(it++);
        else
            ++it;
    }
    // Insert new binding
    m_keyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
    for (auto it = m_keyBinding.begin(); it != m_keyBinding.end(); ++it )
    {
        if ((*it).second == action)
            return (*it).first;
    }
    return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
        m_actionBinding[MoveLeft].action  = derivedAction<Astronaut>([] (Astronaut& astronaut, sf::Time){astronaut.walkLeft();});
        m_actionBinding[MoveRight].action = derivedAction<Astronaut>([] (Astronaut& astronaut, sf::Time){astronaut.walkRight();});
        m_actionBinding[Jump].action = derivedAction<Astronaut>([] (Astronaut& astronaut, sf::Time){astronaut.jump();});
        m_actionBinding[ThursterLeft].action = derivedAction<Astronaut>([] (Astronaut& astronaut, sf::Time){astronaut.thrusterLeft();});
        m_actionBinding[ThursterRight].action = derivedAction<Astronaut>([] (Astronaut& astronaut, sf::Time){astronaut.thrusterRight();});
        m_actionBinding[ThursterUp].action = derivedAction<Astronaut>([] (Astronaut& astronaut, sf::Time){astronaut.thrusterUp();});
        m_actionBinding[ThursterDown].action = derivedAction<Astronaut>([] (Astronaut& astronaut, sf::Time){astronaut.thrusterDown();});

        m_actionBinding[Fire].action = derivedAction<Astronaut>([this] (Astronaut& astronaut, sf::Time){astronaut.fire(m_mouseWorldPos);});
}

bool Player::isRealtimeAction(Action action)
{
    switch (action)
    {
            case MoveLeft:
            case MoveRight:
            case ThursterLeft:
            case ThursterRight:
            case ThursterUp:
            case ThursterDown:
            case Fire:
                    return true;

            default:
                    return false;
    }
}
