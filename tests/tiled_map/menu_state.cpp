#include "menu_state.h"
#include "texture_manager.h"
#include "game.h"
#include "menu_button.h"
#include "input_handler.h"
#include "state_parser.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update() {
    if (!m_isExit) {
        if (!menu_mutex.try_lock()) {
            return;
        }
        // std::shared_lock<std::recursive_mutex> rl(menu_mutex, std::try_to_lock);
        // if (rl.owns_lock() == false) {
        //     return;
        // }
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->update();
        }
        menu_mutex.unlock();
    }
}

void MainMenuState::render() {
    if (!m_isExit) {
        if (!menu_mutex.try_lock()) {
            return;
        }
        // std::shared_lock<std::recursive_mutex> rl(menu_mutex, std::try_to_lock);
        // if (rl.owns_lock() == false) {
        //     return;
        // }
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
        menu_mutex.unlock();
    }
}

bool MainMenuState::onEnter() {
    if (!menu_mutex.try_lock()) {
        return false;
    }
    // std::unique_lock<std::recursive_mutex> wl(menu_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return false;
    // }

    // parse the state
    StateParser stateParser;
    stateParser.parseState("assets/xml/test_data.xml", s_menuID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0); // pushback 0 callbackID start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    // set the callbacks for menu items
    setCallbacks(m_callbacks);

    menu_mutex.unlock();
    std::cout << "entering MainMenuState\n";
    return true;
}

bool MainMenuState::onExit() {
    if (!menu_mutex.try_lock()) {
        return false;
    }
    // std::unique_lock<std::recursive_mutex> wl(menu_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return false;
    // }
    m_isExit = true;
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();

    // clear the texture manager
    for (int i = 0; i < m_textureIDList.size(); i++) {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();

    menu_mutex.unlock();
    std::cout << "exiting MainMenuState\n";
    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks) {
    if (!m_isExit) {
        if (!menu_mutex.try_lock()) {
            return;
        }
        // go through the game objects
        for (int i = 0; i < m_gameObjects.size(); i++) {
            // if they are of type MenuButton then assign a callback based on the id passed in from the file
            if (dynamic_cast<MenuButton *>(m_gameObjects[i])) {
                MenuButton *pButton = dynamic_cast<MenuButton *>(m_gameObjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
            }
        }

        menu_mutex.unlock();
    }
}

void MainMenuState::s_menuToPlay() {
    TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(CHANGE, new PlayState()));
    std::cout << "Play button clicked\n";
}

void MainMenuState::s_exitFromMenu() {
    TheGame::Instance()->quit();
    std::cout << "Exit button clicked\n";
}
