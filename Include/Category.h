#ifndef CATEGORY_H_INCLUDED
#define CATEGORY_H_INCLUDED

namespace Category
{
    enum Type
    {
        None = 0,
        Scene = 1 << 0,
        PlayerBeing = 1 << 1,
    };
}


#endif // CATEGORY_H_INCLUDED
