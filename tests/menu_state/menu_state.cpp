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
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
        menu_mutex.unlock();
    }
}

bool MenuState::onEnter() {

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

    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit() {
    m_isExit = true;
    if (!menu_mutex.try_lock()) {
        return false;
    }
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    menu_mutex.unlock();
    TheTextureManager::Instance()->clearFromTextureMap("playbutton");
    TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

    std::cout << "exiting MenuState\n";
    return true;
}

void MenuState::s_menuToPlay() {
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
    std::cout << "Play button clicked\n";
}

void MenuState::s_exitFromMenu() {
    TheGame::Instance()->quit();
    std::cout << "Exit button clicked\n";
}
