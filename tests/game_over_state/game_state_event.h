#ifndef _GAME_STATE_EVENT_H_
#define _GAME_STATE_EVENT_H_

#include "game_state.h"

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
    GameStateEvent(game_state_event_type eventType = UPDATE, GameState *pState = nullptr) : m_eventType(eventType), m_pState(pState) {
    }

    GameState *getState() {
        return m_pState;
    }

    game_state_event_type getEventType() {
        return m_eventType;
    }

private:
    game_state_event_type m_eventType;
    GameState *m_pState;
};

#endif /* _GAME_STATE_EVENT_H_ */
