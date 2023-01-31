#ifndef _GAME_STATE_MACHINE_H_
#define _GAME_STATE_MACHINE_H_

#include "game_state.h"
#include <vector>
#include <mutex>
#include <shared_mutex>
#include "lock/shared_recursive_mutex.h"
#include "data_structure/circular_queue.h"

enum game_state_event_type {
    UPDATE = 0,
    POP = 1,
    POP_ALL = 2,
    CHANGE = 3,
    RENDER = 4,
    PUSH = 5
};

class GameStateEvent {

public:
    GameStateEvent(game_state_event_type eventType, GameState *pState) : m_eventType(eventType), m_pState(pState) {
    }

    GameState *getState() {
        return m_pState;
    }

    game_state_event_type getEventType() {
        return m_eventType;
    }

private:
    game_state_event_type m_eventType = UPDATE;
    GameState *m_pState;
};

class GameStateMachine {
public:
    bool pushState(GameState *pState);
    bool changeState(GameState *pState);
    bool popState();
    void popAllState();

    void enEventQueue(GameStateEvent *event);
    GameStateEvent *deEventQueue();

    void update();
    void render();

private:
    std::vector<GameState *> m_gameStates;
    SharedRecursiveMutex game_mutex;
    CircularQueue<GameStateEvent *> m_eventQueue;
};

#endif /* _GAME_STATE_MACHINE_H_ */
