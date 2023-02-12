#include "play_state.h"
#include "texture_manager.h"
#include "game.h"
#include "input_handler.h"
#include "pause_state.h"
#include "game_state_machine.h"
#include "game_over_state.h"
#include "state_parser.h"
#include "game_object_factory.h"

const std::string PlayState::s_playID = StateIDToString(StateID::PLAY);

void PlayState::update() {
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
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
        pLevel->update();
        for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->update();
            if (i > 0 && checkCollision(dynamic_cast<ShooterObject *>(m_gameObjects[0]), dynamic_cast<ShooterObject *>(m_gameObjects[i]))) {
                TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(PUSH, new GameOverState()));
            }
        }

        play_mutex.unlock();
    }
}

void PlayState::render() {
    if (!m_isExit) {
        if (!play_mutex.try_lock()) {
            return;
        }
        pLevel->render();
        // std::shared_lock<std::recursive_mutex> rl(play_mutex, std::try_to_lock);
        // if (rl.owns_lock() == false) {
        //     return;
        // }
        for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }

        play_mutex.unlock();
    }
}

bool PlayState::onEnter() {
    if (!play_mutex.try_unique_lock()) {
        return false;
    }
    // std::unique_lock<std::recursive_mutex> wl(play_mutex, std::try_to_lock);
    // if (wl.owns_lock() == false) {
    //     return false;
    // }

    LevelParser levelParser;
    pLevel = levelParser.parseLevel("assets/levels/map2/map.tmx");

    // parse the state
    // StateParser stateParser;
    // stateParser.parseState("assets/xml/test_data.xml", s_playID, &m_gameObjects, &m_textureIDList);

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
    for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    // clear the texture manager
    for (unsigned int i = 0; i < m_textureIDList.size(); i++) {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();

    play_mutex.unlock();
    std::cout << "exiting PlayState\n";
    return true;
}

bool PlayState::checkCollision(ShooterObject *p1, ShooterObject *p2) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth() * p1->getScale();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight() * p1->getScale();

    // calculate the sides of rect B
    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth() * p2->getScale();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight() * p2->getScale();

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
