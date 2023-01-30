#include "play_state.h"
#include "texture_manager.h"
#include "game.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    if (!m_isExit) {
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->update();
        }
        std::cout << "PlayState update\n";
    }
}

void PlayState::render() {
    if (!m_isExit) {
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
        std::cout << "PlayState render\n";
    }
}

bool PlayState::onEnter() {
    if (!TheTextureManager::Instance()->load("assets/images/helicopter417x143.png", "helicopter", TheGame::Instance()->getRenderer())) {
        return false;
    }

    GameObject *player = new Player(new LoaderParams(100, 100, 417, 143, "helicopter"));
    m_gameObjects.push_back(player);

    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit() {
    m_isExit = true;
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("helicopter");
    std::cout << "exiting PlayState\n";
    return true;
}
