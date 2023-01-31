#pragma comment(lib, "SDL2main.lib")

class Game {

private:
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;
  SDL_Event m_SDLEvent;
  bool m_BGameRunning; // deltatime
  float m_DeltaTime;
  Uint64 m_StartTime;
  Uint64 m_PreFrameTime;
  void InitWindow() {
    m_Window =
        SDL_CreateWindow("HelloSDL", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    m_Renderer = SDL_CreateRenderer(
        m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  }

public:
  Game() : m_BGameRunning(true), m_DeltaTime(0) {
    InitWindow();
    // // deltaTime
    m_StartTime = SDL_GetTicks64();
    //
    m_PreFrameTime = m_StartTime;
  }

  ~Game() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
  }
  void Run() {
    while (m_BGameRunning) {
      UpdateDeltaTime();
      //
      Update();
      Render();
    }
  }
  void Update() {
    //
    UpdateSDLEvent();
  }
  void Render() {
    //
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    //
    SDL_RenderClear(m_Renderer); // Draw items
    //
    SDL_RenderPresent(m_Renderer);
  }

  void UpdateDeltaTime() {
    /* Updates the deltaTime with the
    time it takes to update and render one frame. */
    Uint64 currTime = SDL_GetTicks64();
    m_DeltaTime = (currTime - m_PreFrameTime) / 1000.0f;
    m_PreFrameTime = currTime;
    float totalTime = (currTime - m_StartTime) / 1000.0f;
    float FPS = 1.0f / m_DeltaTime;
    SDL_LogInfo(0, "totalTime: %f\tdt: %f\tFPS: %f\n", totalTime, m_DeltaTime,
                FPS);
    // 限制帧率
    int MaxFPS = 60;
    if (m_DeltaTime) {
      switch (m_SDLEvent.type) {
      case SDL_QUIT:
        m_BGameRunning = false;
        break;
      }
    }
  }
};

int main(int argc, char *argv[]) {
  Game game;
  game.Run();
  return 0;
}
