#ifndef _ENEMY_BULLET_H_
#define _ENEMY_BULLET_H_

#include "player_bullet.h"

class EnemyBullet : public PlayerBullet {

public:
    EnemyBullet() : PlayerBullet() {}

    virtual ~EnemyBullet() {}

    virtual std::string type() { return "EnemyBullet"; }
};

#endif /* _ENEMY_BULLET_H_ */
