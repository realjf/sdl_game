#ifndef _GAME_STATE_MACHINE_H_
#define _GAME_STATE_MACHINE_H_

#include "game_state.h"
#include <vector>
#include <mutex>

class GameStateMachine {
public:
    bool pushState(GameState *pState);
    bool changeState(GameState *pState);
    bool popState();
    void popAllState();

    void update();
    void render();

private:
    std::vector<GameState *> m_gameStates;
    std::mutex game_mutex;
};

#endif /* _GAME_STATE_MACHINE_H_ */
