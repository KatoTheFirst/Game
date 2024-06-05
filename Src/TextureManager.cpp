#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filepath, SDL_Renderer* ren)
{
	SDL_Surface* tempSurface;
	tempSurface = IMG_Load(filepath);
	SDL_Texture* tex;
	tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}
