#include "play_state.h"
#include "texture_manager.h"
#include "game.h"
#include "input_handler.h"
#include "pause_state.h"
#include "game_state_machine.h"
#include "game_over_state.h"
#include "state_parser.h"
#include "game_object_factory.h"

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

        if (checkCollision(dynamic_cast<SDLGameObject *>(m_gameObjects[0]), dynamic_cast<SDLGameObject *>(m_gameObjects[1]))) {
            TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(PUSH, new GameOverState()));
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

    // parse the state
    StateParser stateParser;
    stateParser.parseState("assets/xml/test_data.xml", s_playID, &m_gameObjects, &m_textureIDList);

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

    // clear the texture manager
    for (int i = 0; i < m_textureIDList.size(); i++) {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();

    play_mutex.unlock();
    std::cout << "exiting PlayState\n";
    return true;
}

bool PlayState::checkCollision(SDLGameObject *p1, SDLGameObject *p2) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();

    // calculate the sides of rect B
    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();

    // if any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }
    if (topA >= bottomB) {
        return false;
    }
    if (rightA <= leftB) {
        return false;
    }
    if (leftA >= rightB) {
        return false;
    }

    return true;
}
