#ifndef _GAME_STATE_ID_H_
#define _GAME_STATE_ID_H_

enum class StateID { PAUSE,
                     PLAY,
                     GAMEOVER,
                     MAINMENU };

const char *StateIDToString(StateID id);

#endif /* _GAME_STATE_ID_H_ */
