#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Command.h"
#include "CommandQueue.h"

class Player
{
    public:
        enum Action
        {
            MoveLeft,
            MoveRight,
            Jump,
            Fire,
            ThursterLeft,
            ThursterRight,
            ThursterUp,
            ThursterDown,
            ActionCount
        };

    public:
        explicit                                Player();
        void                                    handleEvent(const sf::Event& event, CommandQueue& commands);
        void                                    handleRealTimeInput(CommandQueue& commands);
        void                                    updateMouseWorldPosition(const sf::Vector2f& pos);

        void                                    assignKey(Action action, sf::Keyboard::Key key);
        sf::Keyboard::Key                       getAssignedKey(Action action) const;

    private:
        void                                    initializeActions();
        static bool                             isRealtimeAction(Action action);

    private:
        sf::Vector2f                            m_mouseWorldPos;
        std::map<sf::Keyboard::Key, Action>     m_keyBinding;
        std::map<Action, Command>               m_actionBinding;
};

#endif // PLAYER_H
