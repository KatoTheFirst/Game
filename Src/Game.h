#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include "Birb.h"
#include "Background.h"
#include "CollisionManager.h"
#include "TextManager.h"
#include "MainMenu.h"
#include "Background.h"

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
	Background leaderboard;
	Mix_Chunk* flapSFX;
	Mix_Chunk* dieSFX;
	Mix_Chunk* hitSFX;
	Mix_Chunk* pointSFX;
	Mix_Music* bgm;
	TextManager score;
	MainMenu menu;
	const int HEIGHT = 600;
	const int WIDTH = 800;
	int points = 0;
	int nextCheckPoint = 0;
	int variance1 = rand() % 201 - 100;
	int variance2 = rand() % 201 - 100;
	int variance3 = rand() % 201 - 100;
	bool GameState;
	bool playing;
	bool restart_shown;
	SDL_Window* window;
	SDL_Event event1;
	SDL_Renderer* renderer;
public:
	Game();
	void MainMenu();
	bool getGameState();
	void Update();
	void Reset();
	void CollisionDetection();
	void init();
	void handleEvents();
	void Render();
	void Clear();
};