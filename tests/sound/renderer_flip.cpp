#include "renderer_flip.h"

SDL_RendererFlip RendererFlipToSDLFlip(RendererFlip flip) {
    switch (flip) {
    case RendererFlip::FLIP_VERTICAL:
        return SDL_FLIP_VERTICAL;
    case RendererFlip::FLIP_HORIZONTAL:
        return SDL_FLIP_HORIZONTAL;
    default:
        return SDL_FLIP_NONE;
    }
}
