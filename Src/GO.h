#pragma once

#include "Object.h"
#include "Background.h"

class GO : public Object
{
private:
public:
    void Render(SDL_Renderer* ren);
};
