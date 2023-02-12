#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SDL.h>
#include "sdl_game_object.h"
#include <time.h>
#include "game_object_factory.h"
#include "shooter_object.h"

class Enemy : public ShooterObject {
public:
    Enemy();
    virtual std::string type() const { return "Enemy"; }
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);

protected:
    int m_health;
    virtual ~Enemy() {}

private:
    int m_Axis = 0;
    bool m_bSameSpeed = false;
};

class EnemyCreator : public BaseCreator {
public:
    GameObject *createGameObject() const {
        return new Enemy();
    }
};

#endif /* _ENEMY_H_ */
