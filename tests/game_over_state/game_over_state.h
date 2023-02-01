#ifndef _GAME_OVER_STATE_H_
#define _GAME_OVER_STATE_H_

#include "game_state.h"
#include <vector>
#include "game_object.h"
#include "lock/shared_recursive_mutex.h"

class GameOverState : public GameState {

public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {
        return s_gameOverID;
    }

private:
    static void s_gameOverToMain();
    static void s_restartPlay();

    static const std::string s_gameOverID;

    std::vector<GameObject *> m_gameObjects;
    bool m_isExit = false;
    SharedRecursiveMutex over_mutex;
};

#endif /* _GAME_OVER_STATE_H_ */
