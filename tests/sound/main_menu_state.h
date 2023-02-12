#ifndef _MAIN_MENU_STATE_H_
#define _MAIN_MENU_STATE_H_

#include "game_state.h"
#include <vector>
#include "game_object.h"
#include <mutex>
#include <shared_mutex>
#include "lock/shared_recursive_mutex.h"
#include "menu_state.h"

class MainMenuState : public MenuState {
public:
    virtual ~MainMenuState() {}
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {
        return s_menuID;
    }

private:
    virtual void setCallbacks(const std::vector<Callback> &callbacks);

private:
    static const std::string s_menuID;

    // store menu items
    std::vector<GameObject *> m_gameObjects;

    // callback functions for menu items
    static void s_menuToPlay();
    static void s_exitFromMenu();
    bool m_isExit = false;
    SharedRecursiveMutex menu_mutex;
};

#endif /* _MAIN_MENU_STATE_H_ */
