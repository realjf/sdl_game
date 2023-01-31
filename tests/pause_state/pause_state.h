#ifndef _PAUSE_STATE_H_
#define _PAUSE_STATE_H_

#include "game_state.h"
#include <vector>
#include <mutex>
#include "game_object.h"
#include <shared_mutex>
#include "lock/shared_recursive_mutex.h"

class PauseState : public GameState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {
        return s_pauseID;
    }

private:
    static void s_pauseToMain();
    static void s_resumePlay();

    static const std::string s_pauseID;

    std::vector<GameObject *> m_gameObjects;
    SharedRecursiveMutex pause_mutex;
    bool m_isExit = false;
};

#endif /* _PAUSE_STATE_H_ */
