#include "game.h"

int main(int argc, char** argv) {
    if (!TheGame::Instance()->init("animate", 100, 100, 640, 480, false)) {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }
    std::cout << "game init success!\n";
    while (TheGame::Instance()->running()) {
        TheGame::Instance()->handleEvents();
        TheGame::Instance()->update();
        TheGame::Instance()->render();

        SDL_Delay(10);  // add the delay
    }

    std::cout << "game closing...\n";
    TheGame::Instance()->clean();

    return 0;
}
