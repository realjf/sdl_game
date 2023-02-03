#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "sdl_game_object.h"
#include <SDL.h>
#include "game_object_factory.h"

class Player : public SDLGameObject {
public:
    Player();
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams *pParams);

    void handleInput();
};

class PlayerCreator : public BaseCreator {
public:
    GameObject *createGameObject() const override {
        return new Player();
    }
};

#endif /* _PLAYER_H_ */
