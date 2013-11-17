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
}
