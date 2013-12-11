#ifndef CATEGORY_H_INCLUDED
#define CATEGORY_H_INCLUDED

namespace Category
{
    enum Type
    {
        None = 0,
        Scene = 1 << 0,
        PlayerActor = 1 << 1,
        EnemyActor = 1 << 2,
    };
}

#endif // CATEGORY_H_INCLUDED
