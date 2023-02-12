#include "texture_manager.h"

TextureManager *TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer *pRenderer) {
    SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

    if (pTempSurface == 0) {
        return false;
    }

    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture != 0) {
        m_textureMap[id] = pTexture;
        return true;
    }

    // reaching here means something went wrong
    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, float scale, SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = width;
    srcRect.h = height;

    dstRect.w = width * scale;
    dstRect.h = height * scale;
    dstRect.x = x;
    dstRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, float scale, int currentRow, int currentFrame, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = width;
    srcRect.h = height;

    dstRect.w = width * scale;
    dstRect.h = height * scale;
    dstRect.x = x;
    dstRect.y = y;

    // SDL_SetTextureBlendMode(m_textureMap[id], SDL_BLENDMODE_BLEND);
    // set the alpha of the texture and pass in the angle
    SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, angle, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, float scale, int currentRow, int currentFrame, SDL_Renderer *pRenderer) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = width;
    srcRect.h = height;
    destRect.w = width / scale;
    destRect.h = height / scale;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
