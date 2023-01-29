#ifndef _GAME_STATE_MACHINE_H_
#define _GAME_STATE_MACHINE_H_

#include "game_state.h"
#include <vector>

class GameStateMachine {
public:
    void pushState(GameState *pState);
    void changeState(GameState *pState);
    void popState();
    void popAllState();

    void update();
    void render();

private:
    std::vector<GameState *> m_gameStates;
};

#endif /* _GAME_STATE_MACHINE_H_ */
