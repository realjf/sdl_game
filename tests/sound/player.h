#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "shooter_object.h"
#include <SDL.h>
#include "game_object_factory.h"

class Player : public ShooterObject {
public:
    virtual ~Player() {}
    Player();
    virtual void draw(RendererFlip flip = RendererFlip::FLIP_NONE);
    virtual void update();
    virtual void clean();
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void collision();
    virtual std::string type() { return "Player"; }

private:
    // bring the player back if there are lives left
    void ressurect();
    // handle any input from the keyboard, mouse, or joystick
    void handleInput();

    // handle any animation for the player
    void handleAnimation();

    // player can be invulnerable for a time
    int m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;
};

class PlayerCreator : public BaseCreator {
public:
    GameObject *createGameObject() const {
        return new Player();
    }
};

#endif /* _PLAYER_H_ */
