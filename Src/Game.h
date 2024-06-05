#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Birb.h"
#include "Background.h"
#include "CollisionManager.h"
#include "TextManager.h"
#include "MainMenu.h"
#include "Background.h"
#include "GO.h"

class Game
{
private:
	Birb b;
	Background bg;
	Background ground1, ground2;
	Background Pipe_Above1;
	Background Pipe_Below1;
	Background Pipe_Above2;
	Background Pipe_Below2;
	Background Pipe_Above3;
	Background Pipe_Below3;
	Background ScoreTbl;
	GO RestartMenu;
	Mix_Chunk* flapSFX;
	Mix_Chunk* dieSFX;
	Mix_Chunk* hitSFX;
	Mix_Chunk* pointSFX;
	Mix_Chunk* replaySound;
	Mix_Chunk* exitSound;
	Mix_Music* bgm;

	TextManager score;
	TextManager buttonReplay;
	TextManager buttonExit;
	TextManager highScore;
	TextManager currentScore;

	MainMenu menu;

	const SDL_Color WHITECOLOR = { 255, 255, 255, 255 };
	const int HEIGHT = 600;
	const int WIDTH = 800;
	int _highScore;
	int points = 0;
	int variance1 = rand() % 201 - 100;
	int variance2 = rand() % 201 - 100;
	int variance3 = rand() % 201 - 100;
	bool isRunning;
	bool restart = false;
	bool birdDie = false;
	SDL_Window* window;
	SDL_Event event1;
	SDL_Renderer* renderer;

	const std::string REPLAY = "REPLAY";
	const std::string EXIT = "EXIT";

public:
	Game();
	void MainMenu();
	bool running();
	void Update();
	void Reset();
	void CollisionDetection();
	void init();
	void handleEvents();
	void Restart();
	void Render();
	void Clear();
};