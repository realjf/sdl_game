#include "menu_state.h"
#include "texture_manager.h"
#include "game.h"
#include "menu_button.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
    }
}

void MenuState::render() {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter() {

    if (!TheTextureManager::Instance()->load("assets/gui/playbutton258x72.png", "playbutton", TheGame::Instance()->getRenderer())) {
        return false;
    }
    if (!TheTextureManager::Instance()->load("assets/gui/exitbutton243x64.png", "exitbutton", TheGame::Instance()->getRenderer())) {
        return false;
    }
    GameObject *btn1 = new MenuButton(new LoaderParams(100, 100, 258, 72, "playbutton"));
    GameObject *btn2 = new MenuButton(new LoaderParams(100, 300, 243, 64, "exitbutton"));

    m_gameObjects.push_back(btn1);
    m_gameObjects.push_back(btn2);

    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit() {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("playbutton");
    TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

    std::cout << "exiting MenuState\n";
    return true;
}
