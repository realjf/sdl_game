#include "play_state.h"
#include "texture_manager.h"
#include "game.h"
#include "input_handler.h"
#include "pause_state.h"
#include "game_state_machine.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        // TheGame::Instance()->getStateMachine()->pushState(new PauseState());
        TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(PUSH, new PauseState()));
    }
    if (!m_isExit) {
        if (!play_mutex.try_lock()) {
            return;
        }
        // std::shared_lock<std::recursive_mutex> rl(play_mutex, std::try_to_lock);
        // if (rl.owns_lock() == false) {
        //     return;
        // }
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
        // std::shared_lock<std::recursive_mutex> rl(play_mutex, std::try_to_lock);
        // if (rl.owns_lock() == false) {
        //     return;
        // }
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
        play_mutex.unlock();
    }
}

bool PlayState::onEnter() {
    if (!play_mutex.try_lock()) {
        return false;
    }
    // std::unique_lock<std::recursive_mutex> wl(play_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return false;
    // }
    if (!TheTextureManager::Instance()->load("assets/images/helicopter417x143.png", "helicopter", TheGame::Instance()->getRenderer())) {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/images/helicopter207x92.png", "helicopter1", TheGame::Instance()->getRenderer())) {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/images/helicopter207x92_2.png", "helicopter2", TheGame::Instance()->getRenderer())) {
        return false;
    }

    GameObject *player = new Player(new LoaderParams(500, 100, 417, 143, "helicopter", 0.2f));
    GameObject *enemy1 = new Enemy(new LoaderParams(100, 100, 207, 92, "helicopter1", 0.2f));
    GameObject *enemy2 = new Enemy(new LoaderParams(200, 100, 207, 92, "helicopter2", 0.2f));
    m_gameObjects.push_back(player);
    m_gameObjects.push_back(enemy1);
    m_gameObjects.push_back(enemy2);
    play_mutex.unlock();

    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit() {
    if (!play_mutex.try_lock()) {
        return false;
    }
    // std::unique_lock<std::recursive_mutex> wl(play_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return false;
    // }
    m_isExit = true;
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    TheTextureManager::Instance()->clearFromTextureMap("helicopter");

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();

    play_mutex.unlock();
    std::cout << "exiting PlayState\n";
    return true;
}
