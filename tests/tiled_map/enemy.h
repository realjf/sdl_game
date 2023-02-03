#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SDL.h>
#include "sdl_game_object.h"
#include <time.h>
#include "game_object_factory.h"

class Enemy : public SDLGameObject {
public:
    Enemy();
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams *pParams);

private:
    int m_Axis = 0;
    bool m_bSameSpeed = false;
};

class EnemyCreator : public BaseCreator {
public:
    GameObject *createGameObject() const override {
        return new Enemy();
    }
};

#endif /* _ENEMY_H_ */
