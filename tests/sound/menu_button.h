#ifndef _MENU_BUTTON_H_
#define _MENU_BUTTON_H_

#include "sdl_game_object.h"
#include <vector>
#include "game_object_factory.h"

enum button_state {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
};

class MenuButton : public SDLGameObject {
public:
    MenuButton();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);

    void setCallback(void (*callback)()) { m_callback = callback; }

private:
    void (*m_callback)();
    bool m_bReleased = false;
    bool m_bClickLock;
};

class MenuButtonCreator : public BaseCreator {
public:
    GameObject *createGameObject() const {
        return new MenuButton();
    }
};

#endif /* _MENU_BUTTON_H_ */
