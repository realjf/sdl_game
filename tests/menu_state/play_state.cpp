#include "play_state.h"
#include "texture_manager.h"
#include "game.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    if (!m_isExit) {
        if (!play_mutex.try_lock()) {
            return;
        }
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->update();
        }
        play_mutex.unlock();
    }
}

void PlayState::render() {
    if (!m_isExit) {
        if (!play_mutex.try_lock()) {
            return;
        }
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
        play_mutex.unlock();
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
    if (!play_mutex.try_lock()) {
        return false;
    }
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    play_mutex.unlock();
    TheTextureManager::Instance()->clearFromTextureMap("helicopter");
    std::cout << "exiting PlayState\n";
    return true;
}
