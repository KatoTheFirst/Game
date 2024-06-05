#include "MainMenu.h"

MainMenu::MainMenu()
{
	isClicked = false;
	isPressed = false;
	destButton.x = 285;
	destButton.y = 470;
	destButton.w = 225;
	destButton.h = 65;
}

void MainMenu::init(SDL_Renderer* ren)
{
	menuBackground.CreateTexture("Image/MainMenu.png", ren);
	start.CreateTexture("Image/PressStart.PNG", ren);
}

bool MainMenu::checkPressed(int x, int y)
{
	if (x >= destButton.x
		&& x <= destButton.x + destButton.w
		&& y >= destButton.y
		&& y <= destButton.y + destButton.h)
	{
		return true;
	}
	return false;
}

int MainMenu::handleEvents(SDL_Event& e)
{
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
	{
		return -1;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN && e.motion.x > 285 && e.motion.x < 510 && e.motion.y > 470 && e.motion.y < 535)
	{
		isClicked = true;
	}
	return 0;
}

void MainMenu::Render(SDL_Renderer* ren, SDL_Event& e)
{
	menuBackground.setSrc(0, 0, 640, 800);
	menuBackground.setDest(0, 0, 600, 800);
	while (true)
	{
		menuBackground.Render(ren);
		start.Render(ren);
		SDL_RenderPresent(ren);
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				exit(0);
			}
			if (e.type == SDL_MOUSEMOTION)
			{
				if (checkPressed(e.motion.x, e.motion.y))
				{
					if (!isPressed)
					{
						isPressed = true;
						start.setSrc(0, 0, 66, 225);
						start.setDest(285, 470, 64, 225);
					}
				}
				else
				{
					if (isPressed)
					{
						isPressed = false;
						start.setSrc(0, 0, 66, 225);
						start.setDest(285, 472, 65, 225);
					}
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN
				&& e.motion.x > 285
				&& e.motion.x < 510
				&& e.motion.y > 470
				&& e.motion.y < 535)
			{
				isClicked = true;
			}
		}
		if (isClicked == true)
		{
			break;
		}
	}
}

bool MainMenu::getClicked()
{
	return isClicked;
}

MainMenu::~MainMenu()
{
	isClicked = false;
}