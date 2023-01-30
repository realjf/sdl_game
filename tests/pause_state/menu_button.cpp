#include "menu_button.h"
#include "input_handler.h"

MenuButton::MenuButton(const LoaderParams *pParams, void (*callback)()) : SDLGameObject(pParams), m_callback(callback) {
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw() {
    // use the base class drawing
    SDLGameObject::draw();
}

void MenuButton::update() {
    Vector2D *pMousePos = TheInputHandler::Instance()->getMousePosition();
    std::cout.setf(std::ios::fixed);
    std::cout.setf(std::ios::showpoint);
    // std::cout << "mouse pos: x=" << pMousePos->getX() << ",y=" << pMousePos->getY() << "\n";
    // std::cout << "menu pos: x=" << m_position.getX() << ",y=" << m_position.getY() << "\n";
    if (pMousePos->getX() < (m_position.getX() + m_width) && pMousePos->getX() > m_position.getX() && pMousePos->getY() < (m_position.getY() + m_height) && pMousePos->getY() > m_position.getY()) {
        m_currentFrame = MOUSE_OVER;
        if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
            m_currentFrame = CLICKED;
            // call callback function
            m_callback();

            m_bReleased = false;
            std::cout << "mouse clicked\n";
        } else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
            std::cout << "mouse over\n";
        } else {
            std::cout << "mouse over\n";
        }
    } else {
        m_currentFrame = MOUSE_OUT;
        // std::cout << "mouse out\n";
    }
}

void MenuButton::clean() {
    SDLGameObject::clean();
}
