#ifndef _MENU_BUTTON_H_
#define _MENU_BUTTON_H_

#include "sdl_game_object.h"

enum button_state {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
};

class MenuButton : public SDLGameObject {
public:
    MenuButton(const LoaderParams *pParams, void (*callback)());

    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    void (*m_callback)();
    bool m_bReleased;
};

#endif /* _MENU_BUTTON_H_ */
