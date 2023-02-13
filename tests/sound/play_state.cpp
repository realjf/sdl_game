#include "play_state.h"
#include "texture_manager.h"
#include "game.h"
#include "input_handler.h"
#include "pause_state.h"
#include "game_state_machine.h"
#include "game_over_state.h"
#include "state_parser.h"
#include "game_object_factory.h"
#include "bullet_handler.h"

const std::string PlayState::s_playID = StateIDToString(StateID::PLAY);

void PlayState::update() {
    if (m_loadingComplete && !m_exiting) {
        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
            TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(PUSH, new PauseState()));
        }
        if (!m_isExit) {
            if (!play_mutex.try_lock()) {
                return;
            }

            TheBulletHandler::Instance()->updateBullets();

            for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
                m_gameObjects[i]->update();
                if (i > 0 && checkCollision(dynamic_cast<ShooterObject *>(m_gameObjects[0]), dynamic_cast<ShooterObject *>(m_gameObjects[i]))) {
                    TheGame::Instance()->getStateMachine()->enEventQueue(new GameStateEvent(PUSH, new GameOverState()));
                }
            }

            if (pLevel != 0) {
                pLevel->update();
            }

            play_mutex.unlock();
        }
    }
}

void PlayState::render() {
    if (m_loadingComplete) {
        if (!m_isExit) {
            if (!play_mutex.try_lock()) {
                return;
            }

            if (pLevel != 0) {
                pLevel->render();
            }

            for (int i = 0; i < TheGame::Instance()->getPlayerLives(); i++) {
                TheTextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 1.0f, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
            }

            TheBulletHandler::Instance()->drawBullets();

            play_mutex.unlock();
        }
    }
}

bool PlayState::onEnter() {
    if (!play_mutex.try_unique_lock()) {
        return false;
    }
    TheGame::Instance()->setPlayerLives(3);

    LevelParser levelParser;
    // pLevel = levelParser.parseLevel("assets/levels/map2/map.tmx");

    pLevel = levelParser.parseLevel(TheGame::Instance()->getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1].c_str());

    TheTextureManager::Instance()->load("assets/images/bullet1.png", "bullet1", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("assets/images/bullet2.png", "bullet2", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("assets/images/bullet3.png", "bullet3", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("assets/images/lives.png", "lives", TheGame::Instance()->getRenderer());

    if (pLevel != 0) {
        m_loadingComplete = true;
    }

    // parse the state
    // StateParser stateParser;
    // stateParser.parseState("assets/xml/attack.xml", s_playID, &m_gameObjects, &m_textureIDList);

    play_mutex.unlock();

    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit() {
    m_exiting = true;
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

    TheBulletHandler::Instance()->clearBullets();

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
