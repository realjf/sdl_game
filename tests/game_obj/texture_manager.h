#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_


#include <SDL.h>
#include <iostream>
#include <map>
#include <SDL_image.h>

class TextureManager {
   private:
    TextureManager() = default;

   public:
    static TextureManager* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new TextureManager();
            return s_pInstance;
        }
        return s_pInstance;
    }

    ~TextureManager() = default;

    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

   private:
    std::map<std::string, SDL_Texture*> m_textureMap;
    static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;



#endif /* _TEXTURE_MANAGER_H_ */
