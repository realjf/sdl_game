#ifndef _TURRET_H_
#define _TURRET_H_

#include <iostream>
#include "game_object_factory.h"
#include "bullet_handler.h"
#include "sound_manager.h"
#include <math.h>
#include "enemy.h"

class Turret : public Enemy {
public:
    Turret() {
        m_dyingTime = 1000;
        m_health = 15;
        m_bulletFiringSpeed = 50;
    }

    virtual ~Turret() {}

    virtual void collision() {
        m_health -= 1;

        if (m_health == 0) {
            if (!m_bPlayedDeathSound) {
                TheSoundManager::Instance()->playSound("explode", 0);

                m_textureID = "largeexplosion";
                m_currentFrame = 0;
                m_numFrames = 9;
                m_width = 60;
                m_height = 60;
                m_bDying = true;
            }
        }
    }

    virtual void update() {
        if (!m_bDying) {
            // we want to scroll this object with the rest
            scroll(TheGame::Instance()->getScrollSpeed());

            if (m_bulletCounter == m_bulletFiringSpeed) {
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet2", 1, Vector2D(-3, -3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(0, -3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(3, -3));
                m_bulletCounter = 0;
            }

            m_bulletCounter++;
        } else {
            scroll(TheGame::Instance()->getScrollSpeed());
            doDyingAnimation();
        }
    }
};

class TurretCreator : public BaseCreator {
    GameObject *createGameObject() const {
        return new Turret();
    }
};

#endif /* _TURRET_H_ */
