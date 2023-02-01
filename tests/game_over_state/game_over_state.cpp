#include "game_over_state.h"
#include "game.h"
#include "texture_manager.h"
#include "animated_graphic.h"
#include "menu_button.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update() {
    if (!m_isExit) {
        if (!over_mutex.try_lock()) {
            return;
        }
        // std::shared_lock<std::recursive_mutex> rl(pause_mutex, std::try_to_lock);
        // if (rl.owns_lock() == false) {
        //     return;
        // }
        for (int i = 0; i < m_gameObjects.size(); i++) {
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
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
        over_mutex.unlock();
    }
}

bool GameOverState::onEnter() {
    if (!TheTextureManager::Instance()->load("assets/images/gameover405x65.png", "gameovertext", TheGame::Instance()->getRenderer())) {
        return false;
    }
    if (!TheTextureManager::Instance()->load("assets/gui/mainmenu284x116.png", "mainmenubutton", TheGame::Instance()->getRenderer())) {
        return false;
    }
    if (!TheTextureManager::Instance()->load("assets/gui/restartbutton284x113.png", "restartbutton", TheGame::Instance()->getRenderer())) {
        return false;
    }

    GameObject *gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 405, 65, "gameovertext", 2), 2);
    GameObject *btn1 = new MenuButton(new LoaderParams(200, 200, 284, 116, "mainmenubutton"), s_gameOverToMain);
    GameObject *btn2 = new MenuButton(new LoaderParams(200, 300, 284, 113, "restartbutton"), s_restartPlay);

    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(btn1);
    m_gameObjects.push_back(btn2);

    std::cout << "entering GameOverState\n";
    return true;
}

bool GameOverState::onExit() {
    std::cout << "exiting GameOverState\n";
    return true;
}

void GameOverState::s_gameOverToMain() {
    TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(CHANGE, new MenuState()));
}

void GameOverState::s_restartPlay() {
    TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(CHANGE, new PlayState()));
}
