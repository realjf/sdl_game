#include "game.h"
#include "input_handler.h"
#include "game_timing.h"
#include "game_object_factory.h"
#include "menu_button.h"
#include "player.h"
#include "enemy.h"
#include "animated_graphic.h"
#include "between_level_state.h"
#include "sound_manager.h"
#include "scrolling_background.h"
#include "shot_glider.h"
#include "turret.h"
#include "eskeletor.h"
#include "roof_turret.h"
#include "level1_boss.h"

Game *Game::s_pInstance = 0;

bool Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    m_gameWidth = width;
    m_gameHeight = height;

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL init success\n";

        if (TTF_Init() < 0) {
            std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
            return false;
        }

        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != 0) {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
            } else {
                std::cout << "renderer init fail\n";
                return false;
            }
        } else {
            std::cout << "window init fail\n";
            return false;
        }
    } else {
        std::cout << "SDL init fail\n";
        return false;
    }

    m_font = TTF_OpenFont("assets/fonts/04B_08.ttf", FONT_SIZE);
    if (m_font == 0) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
        return false;
    }

    std::cout << "init success\n";

    if (TheTextureManager::Instance() == 0) {
        std::cout << "instance texture manager failed\n";
        return false;
    }

    // add some sound effects - TODO move to better place
    TheSoundManager::Instance()->load("assets/audio/DST_ElectroRock.ogg", "music1", SOUND_MUSIC);
    TheSoundManager::Instance()->load("assets/audio/boom.wav", "explode", SOUND_SFX);
    TheSoundManager::Instance()->load("assets/audio/phaser.wav", "shoot", SOUND_SFX);

    TheSoundManager::Instance()->playMusic("music1", -1);

    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    // TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
    TheGameObjectFactory::Instance()->registerType("Turret", new TurretCreator());
    TheGameObjectFactory::Instance()->registerType("Glider", new GliderCreator());
    TheGameObjectFactory::Instance()->registerType("ShotGlider", new ShotGliderCreator());
    TheGameObjectFactory::Instance()->registerType("RoofTurret", new RoofTurretCreator());
    TheGameObjectFactory::Instance()->registerType("Eskeletor", new EskeletorCreator());
    TheGameObjectFactory::Instance()->registerType("Level1Boss", new Level1BossCreator());

    m_pGameStateMachine = new GameStateMachine();
    if (m_pGameStateMachine == NULL) {
        std::cout << "create game state machine failed\n";
        return false;
    }
    m_pGameStateMachine->enEventQueue(new GameStateEvent(CHANGE, new MainMenuState()));

    m_bRunning = true;

    return true;
}

void Game::render() {
    m_pGameStateMachine->render();
}

void Game::update() {
    // loop through and update our objects

    m_pGameStateMachine->deEventQueue();
    m_pGameStateMachine->update();
}

void Game::handleEvents() {
    TheInputHandler::Instance()->update();
}

void Game::clean() {
    std::cout << "cleaning game\n";
    TheInputHandler::Instance()->clean();

    m_pGameStateMachine->clean();

    // m_pGameStateMachine = 0;
    delete m_pGameStateMachine;

    TTF_CloseFont(m_font);

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::draw() {
    for (std::vector<GameObject *>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}

void Game::quit() {
    // m_pGameStateMachine->popAllState();
    m_pGameStateMachine->enEventQueue(new GameStateEvent(POP_ALL));
    m_bRunning = false;
}

void Game::setCurrentLevel(int currentLevel) {
    m_currentLevel = currentLevel;
    m_pGameStateMachine->enEventQueue(new GameStateEvent(CHANGE, new BetweenLevelState()));
    m_bLevelComplete = false;
}

Game::~Game() {
    m_pRenderer = 0;
    m_pWindow = 0;
}

Game::Game() : m_pWindow(0),
               m_pRenderer(0),
               m_bRunning(false),
               m_pGameStateMachine(0),
               m_playerLives(3),
               m_scrollSpeed(0.8),
               m_bLevelComplete(false),
               m_bChangingState(false) {
    // add some level files to an array
    m_levelFiles.push_back("assets/levels/maps/map1.tmx");
    m_levelFiles.push_back("assets/levels/maps/map2.tmx");

    // start at this level
    m_currentLevel = 1;
}
