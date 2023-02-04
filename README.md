# sdl_game

sdl game demo

### Dependencies

- [SDL2 SDL2/release-2.26.2](https://github.com/libsdl-org/SDL/tree/SDL2)
- [logc](https://github.com/realjf/logc.git)
- [SDL_image SDL2/release-2.6.2](https://github.com/libsdl-org/SDL_image.git)
- [SDL_ttf SDL2/release-2.20.1](https://github.com/libsdl-org/SDL_ttf.git)
- [spdlog v1.x/v1.11.0](https://github.com/gabime/spdlog.git)
- [base64](https://github.com/ReneNyffenegger/cpp-base64.git)
- [zlib v1.2.13](https://github.com/madler/zlib.git)
- [tinyxml](https://github.com/realjf/tinyxml.git)

### Build

**`Linux`**

```sh
git clone --recursive https://github.com/realjf/sdl_game.git
cd sdl_game
make deps
make build
make run
```

**`Windows`**

```sh
git clone --recursive https://github.com/realjf/sdl_game.git
cd sdl_game
make deps
make build PLAT=WINDOWS
make run PLAT=WINDOWS

```
