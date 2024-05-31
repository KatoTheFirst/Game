#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include"Background.h"

class MainMenu
{
private:
	bool isClicked;
	Background menuBackground;
public:
	MainMenu();
	~MainMenu();
	void init(SDL_Renderer* ren);
	int handleEvents(SDL_Event& e);
	void Render(SDL_Renderer* ren);
	bool getClicked();
};

