#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include"Background.h"

class MainMenu
{
private:
	bool isClicked;
	bool isPressed;
	Background menuBackground;
	Background start;

public:
	MainMenu();
	~MainMenu();
	SDL_Rect destButton;
	void init(SDL_Renderer* ren);
	int handleEvents(SDL_Event& e);
	void Render(SDL_Renderer* ren, SDL_Event& e);
	bool getClicked();
	bool checkPressed(int x, int y);
};

