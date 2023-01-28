#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <SDL.h>
#include <vector>
#include <iostream>
#include "math/vector2d.h"

class InputHandler {
   public:
    static InputHandler* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }

    void update();
    void clean();

    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

    void initialiseJoysticks();
    bool joysticksInitialised() {
        return m_bJoysticksInitialised;
    }

    ~InputHandler() = default;

   private:
    InputHandler() = default;

    static InputHandler* s_pInstance;

    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoysticksInitialised;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
};

typedef InputHandler TheInputHandler;

const int m_joystickDeadZone = 10000;

#endif /* _INPUT_HANDLER_H_ */
