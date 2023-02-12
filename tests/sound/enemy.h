#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SDL.h>
#include "shooter_object.h"
#include <time.h>
#include "game_object_factory.h"
#include "shooter_object.h"

class Enemy : public ShooterObject {
public:
    virtual std::string type() const { return "Enemy"; }

protected:
    int m_health;
    Enemy() : ShooterObject() {}
    virtual ~Enemy() {}

private:
    int m_Axis = 0;
    bool m_bSameSpeed = false;
};

#endif /* _ENEMY_H_ */
