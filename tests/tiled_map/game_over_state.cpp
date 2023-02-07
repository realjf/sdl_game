#include "game_over_state.h"
#include "game.h"
#include "texture_manager.h"
#include "animated_graphic.h"
#include "menu_button.h"
#include "state_parser.h"
#include "game_object_factory.h"

const std::string GameOverState::s_gameOverID = StateIDToString(StateID::GAMEOVER);

void GameOverState::update() {
    if (!m_isExit) {
        if (!over_mutex.try_lock()) {
            return;
        }
        // std::shared_lock<std::recursive_mutex> rl(pause_mutex, std::try_to_lock);
        // if (rl.owns_lock() == false) {
        //     return;
        // }
        for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->update();
        }
        over_mutex.unlock();
    }
}

void GameOverState::render() {
    if (!m_isExit) {
        if (!over_mutex.try_lock()) {
            return;
        }
        // std::shared_lock<std::recursive_mutex> rl(pause_mutex, std::try_to_lock);
        // if (rl.owns_lock() == false) {
        //     return;
        // }
        for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
        over_mutex.unlock();
    }
}

bool GameOverState::onEnter() {
    if (!over_mutex.try_lock()) {
        return false;
    }

    // parse the state
    StateParser stateParser;
    stateParser.parseState("assets/xml/test_data.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    // set the callbacks for menu items
    setCallbacks(m_callbacks);

    over_mutex.unlock();

    std::cout << "entering GameOverState\n";
    return true;
}

bool GameOverState::onExit() {
    if (!over_mutex.try_lock()) {
        return false;
    }

    // clear the texture manager
    for (unsigned int i = 0; i < m_textureIDList.size(); i++) {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    over_mutex.unlock();
    std::cout << "exiting GameOverState\n";
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback> &callbacks) {
    if (!m_isExit) {
        if (!over_mutex.try_lock()) {
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

        over_mutex.unlock();
    }
}

void GameOverState::s_gameOverToMain() {
    TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(CHANGE, new MainMenuState()));
}

void GameOverState::s_restartPlay() {
    TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(CHANGE, new PlayState()));
}
