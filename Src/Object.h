#pragma once
#include"TextureManager.h"

class Object
{
private:
	SDL_Texture* Tex;
public:

	SDL_Texture* getTexture();
	SDL_Rect& getSrc();
	SDL_Rect& getDest();
	SDL_Rect src, dest;

	void setSrc(int x, int y, int h, int w);
	void setDest(int x, int y, int h, int w);

	void CreateTexture(const char* filepath, SDL_Renderer* ren);
	void virtual Render(SDL_Renderer* ren) = 0;
};