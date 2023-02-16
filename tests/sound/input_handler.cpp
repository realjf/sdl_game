#include "input_handler.h"
#include "game.h"
#include <stdlib.h>

InputHandler *InputHandler::s_pInstance = 0;

void InputHandler::reset() {
    setMouseButtonState(LEFT, false);
    setMouseButtonState(RIGHT, false);
    setMouseButtonState(MIDDLE, false);
}

void InputHandler::update() {
    std::thread m_thread(&InputHandler::eventLoop, this);
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void InputHandler::clean() {
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
    if (!mouse_mutex.try_lock()) {
        return false;
    }
    if (m_keystates != 0) {
        if (m_keystates[key] == 1) {
            mouse_mutex.unlock();
            return true;
        }
    }
    mouse_mutex.unlock();
    return false;
}

void InputHandler::onKeyDown() {
    if (!mouse_mutex.try_lock()) {
        return;
    }
    m_keystates = SDL_GetKeyboardState(0);
    mouse_mutex.unlock();
}

void InputHandler::onKeyUp() {
    if (!mouse_mutex.try_lock()) {
        return;
    }
    m_keystates = SDL_GetKeyboardState(0);
    mouse_mutex.unlock();
}

void InputHandler::onMouseMove(SDL_Event event) {
    setMousePosition(static_cast<float>(event.motion.x), static_cast<float>(event.motion.y));
}

void InputHandler::onMouseButtonDown(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        setMouseButtonState(LEFT, true);
        std::cout << "mouse left clicked\n";
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        setMouseButtonState(MIDDLE, true);
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
        setMouseButtonState(RIGHT, true);
        std::cout << "mouse right clicked\n";
    }
}

void InputHandler::onMouseButtonUp(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        setMouseButtonState(LEFT, false);
        std::cout << "mouse left released\n";
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        setMouseButtonState(MIDDLE, false);
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
        setMouseButtonState(RIGHT, false);
        std::cout << "mouse right released\n";
    }
}

void InputHandler::eventLoop() {
    while (true) {
        SDL_Event event;
        if (SDL_PollEvent(&event) == 0) {
            return;
        }
        switch (event.type) {
        case SDL_QUIT:
            TheGame::Instance()->quit();
            break;

        case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;

        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;

        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;

        case SDL_KEYDOWN:
            onKeyDown();
            break;

        case SDL_KEYUP:
            onKeyUp();
            break;

        default:
            break;
        }
    }
}
