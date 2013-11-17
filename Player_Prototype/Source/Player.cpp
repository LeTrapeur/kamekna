#include "Player.h"

#include "Being.h"

struct BeingJumper
{
    BeingJumper(){}
    void operator()(Being& being, sf::Time) const {being.jump();}
};

struct BeingLeftWalker
{
    BeingLeftWalker(){}
    void operator()(Being& being, sf::Time) const {being.walkLeft();}
};

struct BeingRightWalker
{
    BeingRightWalker(){}
    void operator()(Being& being, sf::Time) const {being.walkRight();}
};



Player::Player()
{}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Jumping
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            Command jump;
            jump.category = Category::PlayerBeing;
            jump.action = derivedAction<Being>(BeingJumper());
            commands.push(jump);
        }
    }

}

void Player::handleRealTimeInput(CommandQueue& commands)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    {
        Command walkLeft;
        walkLeft.category = Category::PlayerBeing;
        walkLeft.action = derivedAction<Being>(BeingLeftWalker());
        commands.push(walkLeft);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        Command walkRight;
        walkRight.category = Category::PlayerBeing;
        walkRight.action = derivedAction<Being>(BeingRightWalker());
        commands.push(walkRight);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        Command thrustUp;
        thrustUp.category = Category::PlayerBeing;
        thrustUp.action = derivedAction<Being>([] (Being& being, sf::Time){being.thrusterUp();});
        commands.push(thrustUp);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        Command thrustDown;
        thrustDown.category = Category::PlayerBeing;
        thrustDown.action = derivedAction<Being>([] (Being& being, sf::Time){being.thrusterDown();});
        commands.push(thrustDown);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        Command thrustLeft;
        thrustLeft.category = Category::PlayerBeing;
        thrustLeft.action = derivedAction<Being>([] (Being& being, sf::Time){being.thrusterLeft();});
        commands.push(thrustLeft);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        Command thrustRight;
        thrustRight.category = Category::PlayerBeing;
        thrustRight.action = derivedAction<Being>([] (Being& being, sf::Time){being.thrusterRight();});
        commands.push(thrustRight);
    }
}
