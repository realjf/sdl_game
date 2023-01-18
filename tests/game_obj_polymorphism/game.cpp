#include "game.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL init success\n";
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

    std::cout << "init success\n";
    m_bRunning = true;

    if (TheTextureManager::Instance() == 0) {
        std::cout << "instance texture manager fail\n";
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/images/goku_148x117.png", "goku", m_pRenderer)) {
        std::cout << "load png fail\n";
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/images/piccolo_125x125.png", "piccolo", m_pRenderer)) {
        std::cout << "load png fail\n";
        return false;
    }

    // init game objects
    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 148, 117, "goku")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(100, 100, 125, 125, "piccolo")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(200, 100, 125, 125, "piccolo")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(300, 100, 125, 125, "piccolo")));

    return true;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);  // clear to the draw color

    // loop through our objects and draw them
    for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }

    SDL_RenderPresent(m_pRenderer);
}

void Game::update() {
    // loop through and update our objects
    for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
    }
}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    m_bRunning = false;
                    break;
                }
            case SDL_QUIT:
                m_bRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::clean() {
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::draw() {
    for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}
