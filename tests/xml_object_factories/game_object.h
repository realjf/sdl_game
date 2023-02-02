#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "loader_params.h"

class GameObject {
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

    // load
    virtual void load(const LoaderParams *pParams) = 0;

protected:
    GameObject() {}
    virtual ~GameObject() {}
};

#endif /* _GAME_OBJECT_H_ */
