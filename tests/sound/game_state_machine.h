#ifndef _GAME_STATE_MACHINE_H_
#define _GAME_STATE_MACHINE_H_

#include "game_state.h"
#include <vector>
#include <mutex>
#include <shared_mutex>
#include "lock/shared_recursive_mutex.h"
#include "game_state_event.h"
#include <queue>

class GameStateMachine {
public:
    GameStateMachine() {}
    ~GameStateMachine() {}
    bool pushState(GameState *pState);
    bool changeState(GameState *pState);
    bool popState();
    void popAllState();

    void enEventQueue(GameStateEvent *event);
    void deEventQueue();

    void update();
    void render();
    void clean();

    void clearGameState(GameState *gameState);

private:
    std::vector<GameState *> m_gameStates;
    SharedRecursiveMutex game_mutex;
    std::queue<GameStateEvent *> m_eventQueue;
    bool m_bInterrupted = false;
};

#endif /* _GAME_STATE_MACHINE_H_ */
