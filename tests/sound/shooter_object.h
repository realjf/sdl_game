#ifndef _SHOOTER_OBJECT_H_
#define _SHOOTER_OBJECT_H_

#include "game_object.h"
#include <SDL.h>

class ShooterObject : public GameObject {
public:
    virtual ~ShooterObject() {}
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void draw();
    virtual void update();
    virtual void clean() {}     // not implemented in this class
    virtual void collision() {} // not implemented in this class
    virtual std::string type() { return "SDLGameObject"; }
    void drawCollisionRect();

protected:
    // we won't directly create ShooterObject's
    ShooterObject();
    // draw the animation for the object being destroyed
    void doDyingAnimation();
    // how fast will this object fire bullets? with a counter
    int m_bulletFiringSpeed;
    int m_bulletCounter;
    // how fast will this object move?
    int m_moveSpeed;
    // how long will the death animation takes? with a counter
    int m_dyingTime;
    int m_dyingCounter;
    // has the explosion sound played?
    bool m_bPlayedDeathSound;

    int m_drawCollision; // draw collision rect
};

#endif /* _SHOOTER_OBJECT_H_ */
