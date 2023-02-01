#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SDL.h>
#include "sdl_game_object.h"
#include <time.h>

class Enemy : public SDLGameObject {
public:
    Enemy(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    int m_numFrames = 5;
    int m_Axis = 0;
    bool m_bSameSpeed = false;
};

#endif /* _ENEMY_H_ */
