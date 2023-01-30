#include "pause_state.h"
#include "game.h"
#include "texture_manager.h"
#include "input_handler.h"
#include "menu_button.h"
#include "menu_state.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update() {
    if (!m_isExit) {
        std::lock_guard<std::mutex> lk(pause_mutex);
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->update();
        }
    }
}

void PauseState::render() {
    if (!m_isExit) {
        std::lock_guard<std::mutex> lk(pause_mutex);
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
    }
}

bool PauseState::onEnter() {
    if (!TheTextureManager::Instance()->load("assets/gui/resume284x116.png", "resumebutton", TheGame::Instance()->getRenderer())) {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/gui/mainmenu284x116.png", "mainmenubutton", TheGame::Instance()->getRenderer())) {
        return false;
    }

    GameObject *btn1 = new MenuButton(new LoaderParams(200, 100, 284, 116, "mainmenubutton"), s_pauseToMain);
    GameObject *btn2 = new MenuButton(new LoaderParams(200, 300, 284, 116, "resumebutton"), s_resumePlay);

    m_gameObjects.push_back(btn1);
    m_gameObjects.push_back(btn2);

    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::onExit() {
    m_isExit = true;
    {
        std::lock_guard<std::mutex> lk(pause_mutex);
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->clean();
        }
        m_gameObjects.clear();
    }

    TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
    TheTextureManager::Instance()->clearFromTextureMap("mainmenubutton");

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();

    std::cout << "exiting PauseState\n";
    return true;
}

void PauseState::s_pauseToMain() {
    TheGame::Instance()->getStateMachine()->changeState(new MenuState());
    std::cout << "pause to main\n";
}

void PauseState::s_resumePlay() {
    TheGame::Instance()->getStateMachine()->popState();
    std::cout << "resume play\n";
}
