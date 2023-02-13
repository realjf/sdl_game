#include "pause_state.h"
#include "game.h"
#include "texture_manager.h"
#include "input_handler.h"
#include "menu_button.h"
#include "state_parser.h"
#include "game_object_factory.h"

const std::string PauseState::s_pauseID = StateIDToString(StateID::PAUSE);

void PauseState::update() {
    if (!m_isExit) {
        if (!pause_mutex.try_lock()) {
            return;
        }
        // std::shared_lock<std::recursive_mutex> rl(pause_mutex, std::try_to_lock);
        // if (rl.owns_lock() == false) {
        //     return;
        // }
        for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->update();
        }
        pause_mutex.unlock();
    }
}

void PauseState::render() {
    if (!m_isExit) {
        if (!pause_mutex.try_lock()) {
            return;
        }
        // std::shared_lock<std::recursive_mutex> rl(pause_mutex, std::try_to_lock);
        // if (rl.owns_lock() == false) {
        //     return;
        // }
        for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
        pause_mutex.unlock();
    }
}

bool PauseState::onEnter() {
    if (pause_mutex.try_lock() == false) {
        return false;
    }
    // std::unique_lock<std::recursive_mutex> wl(pause_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return false;
    // }

    // parse the state
    StateParser stateParser;
    stateParser.parseState("assets/xml/attack.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    setCallbacks(m_callbacks);

    pause_mutex.unlock();

    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::onExit() {

    if (pause_mutex.try_lock() == false) {
        return false;
    }

    // std::unique_lock<std::recursive_mutex> wl(pause_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return false;
    // }
    m_isExit = true;
    for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    // clear the texture manager
    for (unsigned int i = 0; i < m_textureIDList.size(); i++) {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    pause_mutex.unlock();

    std::cout << "exiting PauseState\n";
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback> &callbacks) {
    if (!m_isExit) {
        if (!pause_mutex.try_lock()) {
            return;
        }
        // go through the game objects
        for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
            // if they are of type MenuButton then assign a callback based on the id passed in from the file
            if (dynamic_cast<MenuButton *>(m_gameObjects[i])) {
                MenuButton *pButton = dynamic_cast<MenuButton *>(m_gameObjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
            }
        }

        pause_mutex.unlock();
    }
}

void PauseState::s_pauseToMain() {
    TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(CHANGE, new MainMenuState()));
    std::cout << "pause to main\n";
}

void PauseState::s_resumePlay() {
    TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(POP));
    std::cout << "resume play\n";
}
