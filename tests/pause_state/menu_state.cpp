#include "menu_state.h"
#include "texture_manager.h"
#include "game.h"
#include "menu_button.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
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

void MenuState::render() {
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

bool MenuState::onEnter() {
    if (!menu_mutex.try_lock()) {
        return false;
    }
    // std::unique_lock<std::recursive_mutex> wl(menu_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return false;
    // }

    if (!TheTextureManager::Instance()->load("assets/gui/playbutton258x72.png", "playbutton", TheGame::Instance()->getRenderer())) {
        return false;
    }
    if (!TheTextureManager::Instance()->load("assets/gui/exitbutton243x64.png", "exitbutton", TheGame::Instance()->getRenderer())) {
        return false;
    }
    GameObject *btn1 = new MenuButton(new LoaderParams(100, 100, 258, 72, "playbutton"), s_menuToPlay);
    GameObject *btn2 = new MenuButton(new LoaderParams(100, 300, 243, 64, "exitbutton"), s_exitFromMenu);

    m_gameObjects.push_back(btn1);
    m_gameObjects.push_back(btn2);

    menu_mutex.unlock();
    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit() {
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

    TheTextureManager::Instance()->clearFromTextureMap("playbutton");
    TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

    menu_mutex.unlock();
    std::cout << "exiting MenuState\n";
    return true;
}

void MenuState::s_menuToPlay() {
    // TheGame::Instance()->getStateMachine()->changeState(new PlayState());
    TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(CHANGE, new PlayState()));
    std::cout << "Play button clicked\n";
}

void MenuState::s_exitFromMenu() {
    TheGame::Instance()->quit();
    std::cout << "Exit button clicked\n";
}
