#ifndef _PLAY_STATE_H_
#define _PLAY_STATE_H_

#include "game_state.h"
#include <vector>
#include "game_object.h"
#include <mutex>
#include <shared_mutex>
#include "lock/shared_recursive_mutex.h"
#include "sdl_game_object.h"
#include "level_parser.h"
#include "level.h"
#include "tile_layer.h"

class PlayState : public GameState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    bool checkCollision(SDLGameObject *p1, SDLGameObject *p2);

    virtual std::string getStateID() const {
        return s_playID;
    }

private:
    static const std::string s_playID;

    std::vector<GameObject *> m_gameObjects;
    bool m_isExit = false;
    SharedRecursiveMutex play_mutex;

    Level *pLevel;
};

#endif /* _PLAY_STATE_H_ */
