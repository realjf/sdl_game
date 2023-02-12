#ifndef _BETWEEN_LEVEL_STATE_H_
#define _BETWEEN_LEVEL_STATE_H_

#include "game_state.h"
#include "game_object.h"
#include <iostream>
#include <vector>
#include "lock/shared_recursive_mutex.h"

class BetweenLevelState : public GameState {
public:
    virtual ~BetweenLevelState() {}
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {
        return s_betweenLevelID;
    }

private:
    static const std::string s_betweenLevelID;

    std::vector<GameObject *> m_gameObjects;
    bool m_isExit = false;
    SharedRecursiveMutex play_mutex;
};

#endif /* _BETWEEN_LEVEL_STATE_H_ */
