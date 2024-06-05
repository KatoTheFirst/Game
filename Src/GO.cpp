#include "GO.h"

void GO::Render(SDL_Renderer* ren)
{
    setSrc(0, 0, 42, 192);
    setDest(200, 50, 88, 400);
    SDL_RenderCopy(ren, getTexture(), &src, &dest);
}

