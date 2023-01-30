#include "play_state.h"
#include "texture_manager.h"
#include "game.h"
#include "input_handler.h"
#include "pause_state.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
    if (!m_isExit) {
        std::lock_guard<std::mutex> lk(play_mutex);
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->update();
        }
    }
}

void PlayState::render() {
    if (!m_isExit) {
        std::lock_guard<std::mutex> lk(play_mutex);
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
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
    {
        std::lock_guard<std::mutex> lk(play_mutex);
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->clean();
        }
        m_gameObjects.clear();
    }
    TheTextureManager::Instance()->clearFromTextureMap("helicopter");
    std::cout << "exiting PlayState\n";
    return true;
}
