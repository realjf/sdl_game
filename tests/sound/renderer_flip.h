#ifndef _RENDERER_FLIP_H_
#define _RENDERER_FLIP_H_

#include <SDL.h>

enum class RendererFlip { FLIP_NONE,
                          FLIP_HORIZONTAL,
                          FLIP_VERTICAL };

SDL_RendererFlip RendererFlipToSDLFlip(RendererFlip flip);

#endif /* _RENDER_FLIP_H_ */
