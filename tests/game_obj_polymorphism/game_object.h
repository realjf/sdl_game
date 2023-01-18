#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "loader_params.h"

class GameObject {
   public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

   protected:
    GameObject(const LoaderParams* pParams) {}
    virtual ~GameObject() {}
};

#endif /* _GAME_OBJECT_H_ */
