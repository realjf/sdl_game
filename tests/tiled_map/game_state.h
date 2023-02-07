#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <string>
#include <iostream>
#include <vector>

enum class StateID { PAUSE,
                     PLAY,
                     GAMEOVER,
                     MAINMENU };

constexpr const char *StateIDToString(StateID id) throw() {
    switch (id) {
    case StateID::PAUSE:
        return "PAUSE";
    case StateID::PLAY:
        return "PLAY";
    case StateID::GAMEOVER:
        return "GAMEOVER";
    case StateID::MAINMENU:
        return "MAINMENU";
    default:
        break;
    }
}

class GameState {
public:
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;

protected:
    std::vector<std::string> m_textureIDList;
};

#endif /* _GAME_STATE_H_ */
