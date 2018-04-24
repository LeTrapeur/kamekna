#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <queue>

#include <FRK2D/Command.hpp>

class CommandQueue
{
    public:
        explicit CommandQueue();
        void push(const Command& command);
        Command pop();
        bool isEmpty() const;

    private:
        std::queue<Command> m_queue;
};

#endif // COMMANDQUEUE_H
