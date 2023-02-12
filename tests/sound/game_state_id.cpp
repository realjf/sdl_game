#include "game_state_id.h"

const char *StateIDToString(StateID id) {
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
        return "";
    }
}
