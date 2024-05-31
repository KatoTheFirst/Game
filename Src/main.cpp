#include"Game.h"

Game* game = new Game();

int main(int argc, char** argv)
{
	double first;
	double last = 0;

	game->init();
	game->MainMenu();
	while (game->getGameState())
	{
		game->handleEvents();
		game->Update();
		game->Render();
		
		first = SDL_GetTicks();
		if (first - last < 16.7)
		{
			SDL_Delay(16.7 - (first - last));
		}
		last = first;
	}
	game->Clear();
	return 0;
}
