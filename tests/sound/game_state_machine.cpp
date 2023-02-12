#include "game_state_machine.h"
#include "pause_state.h"
#include "play_state.h"
#include "main_menu_state.h"
#include "game_over_state.h"

bool GameStateMachine::pushState(GameState *pState) {
    // if (!game_mutex.try_lock()) {
    //     return false;
    // }
    // game_mutex.lock();
    // std::unique_lock<std::recursive_mutex> wl(game_mutex, std::try_to_lock);
    //  if (wl.owns_lock() == false) {
    //     return false;
    // }
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
    // game_mutex.unlock();
    return true;
}

bool GameStateMachine::changeState(GameState *pState) {

    // if (!game_mutex.try_lock()) {
    //     return false;
    // }
    // std::unique_lock<std::recursive_mutex> wl(game_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return false;
    // }
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->getStateID() == pState->getStateID()) {
            std::cout << "========= change to state: " << m_gameStates.back()->getStateID() << std::endl;
            return true;
        }
        if (m_gameStates.back()->onExit()) {
            clearGameState(m_gameStates.back());
            m_gameStates.pop_back();
        }
    }

    // push back our new state
    m_gameStates.push_back(pState);

    if (!m_gameStates.empty()) {
        std::cout << "========= change to state: " << m_gameStates.back()->getStateID() << std::endl;
    }

    // initialise it
    m_gameStates.back()->onEnter();
    // game_mutex.unlock();
    return true;
}

bool GameStateMachine::popState() {
    // if (!game_mutex.try_lock()) {
    //     return false;
    // }
    // std::unique_lock<std::recursive_mutex> wl(game_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return false;
    // }
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->onExit()) {
            if (!m_gameStates.empty()) {
                std::cout << "========= pop state: " << m_gameStates.back()->getStateID() << std::endl;
            }
            clearGameState(m_gameStates.back());
            m_gameStates.pop_back();
        }
    }
    if (!m_gameStates.empty()) {
        std::cout << "========= state: " << m_gameStates.back()->getStateID() << std::endl;
    }
    // game_mutex.unlock();

    return true;
}

void GameStateMachine::popAllState() {
    // if (!game_mutex.try_lock()) {
    //     return;
    // }
    // std::unique_lock<std::recursive_mutex> wl(game_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return;
    // }
    for (; !m_gameStates.empty();) {
        if (m_gameStates.back()->onExit()) {
            clearGameState(m_gameStates.back());
            m_gameStates.pop_back();
        }
    }
    // game_mutex.unlock();
}

void GameStateMachine::enEventQueue(GameStateEvent *event) {
    if (m_bInterrupted) {
        return;
    }
    m_bInterrupted = true;
    if (!game_mutex.try_lock()) {
        return;
    }
    m_eventQueue.push(event);

    m_bInterrupted = false;
    game_mutex.unlock();
}

void GameStateMachine::deEventQueue() {
    if (m_bInterrupted || !game_mutex.try_lock()) {
        return;
    }
    if (!m_eventQueue.empty()) {
        GameStateEvent *event = m_eventQueue.front();

        if (event != NULL && event->getEventType() >= UPDATE) {
            switch (event->getEventType()) {
            case PUSH:
                pushState(std::move(event->getState()));
                break;
            case POP:
                popState();
                break;
            case POP_ALL:
                popAllState();
                break;
            case CHANGE:
                changeState(std::move(event->getState()));
                break;
            case UPDATE:
            case RENDER:
                break;
            default:
                break;
            }
        }
        m_eventQueue.pop();
    }

    game_mutex.unlock();

    return;
}

void GameStateMachine::update() {
    // std::cout << "++++++++++++++++" << m_bInterrupted << "++++++++++++++++" << std::endl;
    if (m_bInterrupted || !game_mutex.try_lock()) {
        return;
    }
    // std::shared_lock<std::recursive_mutex> rl(game_mutex, std::try_to_lock);
    // if (rl.owns_lock() == false) {
    //     return;
    // }

    if (!m_gameStates.empty()) {
        m_gameStates.back()->update();
        // std::cout << "========= state: " << m_gameStates.back()->getStateID() << std::endl;
    }
    game_mutex.unlock();
}

void GameStateMachine::render() {
    // std::cout << "-----------------" << m_bInterrupted << "-----------------" << std::endl;
    if (m_bInterrupted || !game_mutex.try_lock()) {
        return;
    }
    // std::shared_lock<std::recursive_mutex> rl(game_mutex, std::try_to_lock);
    // if (rl.owns_lock() == false) {
    //     return;
    // }
    if (!m_gameStates.empty()) {
        m_gameStates.back()->render();
        // std::cout << "========= state 1: " << m_gameStates.back()->getStateID() << std::endl;
    }
    game_mutex.unlock();
}

void GameStateMachine::clearGameState(GameState *gameState) {
    GameState *game_state = gameState;
    if (game_state->getStateID() == StateIDToString(StateID::PAUSE)) {
        PauseState *state = dynamic_cast<PauseState *>(game_state);
        delete state;
    } else if (game_state->getStateID() == StateIDToString(StateID::PAUSE)) {
        PlayState *state = dynamic_cast<PlayState *>(game_state);
        delete state;
    } else if (game_state->getStateID() == StateIDToString(StateID::PAUSE)) {
        MainMenuState *state = dynamic_cast<MainMenuState *>(game_state);
        delete state;
    } else if (game_state->getStateID() == StateIDToString(StateID::PAUSE)) {
        GameOverState *state = dynamic_cast<GameOverState *>(game_state);
        delete state;
    } else {
        delete game_state;
    }
}
