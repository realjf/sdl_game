#include "game.h"

bool Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
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

    // if (!TheTextureManager::Instance()->load("assets/gui/playbutton258x72.png", "playbutton", m_pRenderer)) {
    //     return false;
    // }
    // if (!TheTextureManager::Instance()->load("assets/gui/exitbutton243x64.png", "exitbutton", m_pRenderer)) {
    //     return false;
    // }
    // m_go.load(100, 100, 258, 72, "playbutton");
    // m_player.load(100, 300, 243, 64, "exitbutton");

    m_go.load(100, 100, 148, 117, "goku");
    m_player.load(300, 300, 125, 125, "piccolo");

    return true;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);

    m_go.draw(m_pRenderer);
    m_player.draw(m_pRenderer);

    SDL_RenderPresent(m_pRenderer);
}

void Game::update() {
    m_go.update();
    m_player.update();
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
