#include "game_state_machine.h"

bool GameStateMachine::pushState(GameState *pState) {
    // if (!game_mutex.try_lock()) {
    //     return false;
    // }
    game_mutex.lock();
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
    game_mutex.unlock();
    return true;
}

bool GameStateMachine::changeState(GameState *pState) {

    if (!game_mutex.try_lock()) {
        return false;
    }

    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->getStateID() == pState->getStateID()) {
            return true;
        }
        if (m_gameStates.back()->onExit()) {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }

    // push back our new state
    m_gameStates.push_back(pState);

    // initialise it
    m_gameStates.back()->onEnter();
    game_mutex.unlock();
    return true;
}

bool GameStateMachine::popState() {
    if (!game_mutex.try_lock()) {
        return false;
    }
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->onExit()) {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
    if (!m_gameStates.empty()) {
        std::cout << "========= state: " << m_gameStates.back()->getStateID() << std::endl;
    }
    game_mutex.unlock();

    return true;
}

void GameStateMachine::popAllState() {
    if (!game_mutex.try_lock()) {
        return;
    }
    for (; !m_gameStates.empty();) {
        if (m_gameStates.back()->onExit()) {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
    game_mutex.unlock();
}

void GameStateMachine::update() {
    // if (!game_mutex.try_lock()) {
    //     return;
    // }
    if (!m_gameStates.empty()) {
        m_gameStates.back()->update();
    }
    // game_mutex.unlock();
}

void GameStateMachine::render() {
    // if (!game_mutex.try_lock()) {
    //     return;
    // }
    if (!m_gameStates.empty()) {
        m_gameStates.back()->render();
    }
    // game_mutex.unlock();
}
