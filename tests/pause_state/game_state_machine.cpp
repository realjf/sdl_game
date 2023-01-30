#include "game_state_machine.h"

bool GameStateMachine::pushState(GameState *pState) {

    {
        std::lock_guard<std::mutex> lk(game_mutex);
        m_gameStates.push_back(pState);
        m_gameStates.back()->onEnter();
    }
    return true;
}

bool GameStateMachine::changeState(GameState *pState) {
    {
        std::lock_guard<std::mutex> lk(game_mutex);

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
    }

    return true;
}

bool GameStateMachine::popState() {

    {
        std::lock_guard<std::mutex> lk(game_mutex);
        if (!m_gameStates.empty()) {
            if (m_gameStates.back()->onExit()) {
                delete m_gameStates.back();
                m_gameStates.pop_back();
            }
        }
        if (!m_gameStates.empty()) {
            std::cout << "========= state: " << m_gameStates.back()->getStateID() << std::endl;
        }
    }

    return true;
}

void GameStateMachine::popAllState() {
    std::lock_guard<std::mutex> lk(game_mutex);
    for (; !m_gameStates.empty();) {
        if (m_gameStates.back()->onExit()) {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::update() {
    std::lock_guard<std::mutex> lk(game_mutex);
    if (!m_gameStates.empty()) {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render() {
    std::lock_guard<std::mutex> lk(game_mutex);
    if (!m_gameStates.empty()) {
        m_gameStates.back()->render();
    }
}
