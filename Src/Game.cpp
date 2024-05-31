#include"Game.h"

Game::Game()
{
	window = NULL;
	renderer = NULL;
	GameState = false;
	b.setSrc(0, 0, 24, 32);
	b.setDest(25, HEIGHT / 2, 28, 38);
	ground1.setSrc(0, 0, 112, 336);
	ground1.setDest(0, 520, 112, 805);
	ground2.setSrc(0, 0, 112, 336);
	ground2.setDest(805, 520, 112, 805);
	Pipe_Above1.setSrc(0, 0, 320, 52);
	Pipe_Above1.setDest(400, -200, 400, 52);
	Pipe_Below1.setSrc(0, 0, 320, 52);
	Pipe_Below1.setDest(400, 350, 400, 52);
	Pipe_Above2.setSrc(0, 0, 320, 52);
	Pipe_Above2.setDest(700, -200, 400, 52);
	Pipe_Below2.setSrc(0, 0, 320, 52);
	Pipe_Below2.setDest(700, 350, 400, 52);
	Pipe_Above3.setSrc(0, 0, 320, 52);
	Pipe_Above3.setDest(1000, -200, 400, 52);
	Pipe_Below3.setSrc(0, 0, 320, 52);
	Pipe_Below3.setDest(1000, 350, 400, 52);
}

bool Game::getGameState()
{
	return GameState;
}

void Game::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! Error : " << Mix_GetError();
	}
	else {
		flapSFX = Mix_LoadWAV("flap.wav");
		dieSFX = Mix_LoadWAV("die.wav");
		hitSFX = Mix_LoadWAV("hit.wav");
		pointSFX = Mix_LoadWAV("point.wav");
		bgm = Mix_LoadMUS("bgm.mp3");
		Mix_VolumeMusic(40);
		Mix_PlayMusic(bgm, -1);
	}
	window = SDL_CreateWindow("Flapping Birb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (window)
	{
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			GameState = true;
			b.CreateTexture("Image/yellowbird1.png", renderer);
			b.CreateTexture1("Image/yellowbird2.png", renderer);
			b.CreateTexture2("Image/yellowbird3.png", renderer);
			bg.CreateTexture("Image/background-day.png", renderer);
			ground1.CreateTexture("Image/base.png", renderer);
			ground2.CreateTexture("Image/base.png", renderer);
			leaderboard.CreateTexture("Image/Leaderboard.png", renderer);
			Pipe_Above1.CreateTexture("Image/Pipe_Above.png", renderer);
			Pipe_Below1.CreateTexture("Image/Pipe_Below.png", renderer);
			Pipe_Above2.CreateTexture("Image/Pipe_Above.png", renderer);
			Pipe_Below2.CreateTexture("Image/Pipe_Below.png", renderer);
			Pipe_Above3.CreateTexture("Image/Pipe_Above.png", renderer);
			Pipe_Below3.CreateTexture("Image/Pipe_Below.png", renderer);
			score.CreateFont("Fonts/calibrib.ttf", 38);
		}
		else
		{
			std::cout << "Not created!" << std::endl;
		}
	}
	else
	{
		std::cout << "window not created!" << std::endl;
	}
}

void Game::MainMenu()
{
	menu.init(renderer);
	while (!menu.getClicked())
	{
		if (menu.handleEvents(event1) == -1)
		{
			GameState = false;
			break;
		}
		SDL_RenderClear(renderer);
		menu.Render(renderer);
		SDL_RenderPresent(renderer);
	}
}

void Game::handleEvents()
{
	b.GetJumpTime();
	SDL_PollEvent(&event1);
	if (event1.type == SDL_QUIT) {
		GameState = false;
	}

	if (event1.type == SDL_KEYDOWN) {
		if (event1.key.keysym.sym == SDLK_SPACE) {
			if (!b.JumpState()) {
				b.Jump();
				Mix_VolumeChunk(flapSFX, 50);
				Mix_PlayChannel(-1, flapSFX, 0);
			}
			else {
				b.Gravity();
			}
		}
	}
	else {
		b.Gravity();
	}
}

void Game::Update()
{

	if (Pipe_Below1.getPipe1X() < Pipe_Below2.getPipe2X() && Pipe_Below1.getPipe1X() < Pipe_Below3.getPipe3X()) {
		if (Pipe_Below1.getPipe1X() < -5) {
			nextCheckPoint = Pipe_Below2.getPipe2Y();
		}
		else {
			nextCheckPoint = Pipe_Below1.getPipe1Y();
		}
	}
	else if (Pipe_Below2.getPipe2X() < Pipe_Below1.getPipe1X() && Pipe_Below2.getPipe2X() < Pipe_Below3.getPipe3X()) {
		if (Pipe_Below2.getPipe2X() < -5) {
			nextCheckPoint = Pipe_Below3.getPipe3Y();
		}
		else {
			nextCheckPoint = Pipe_Below2.getPipe2Y();
		}
	}
	else if (Pipe_Below3.getPipe3X() < Pipe_Below1.getPipe1X() && Pipe_Below3.getPipe3X() < Pipe_Below2.getPipe2X()) {
		if (Pipe_Below3.getPipe3X() < -5) {
			nextCheckPoint = Pipe_Below1.getPipe1Y();
		}
		else {
			nextCheckPoint = Pipe_Below3.getPipe3Y();
		}
	}


	// Scoring
	std::string s;
	s = "Score: " + std::to_string(points);
	score.Text(s, 255, 255, 255, renderer);

	bool flag1 = false, flag2 = false;
	ground1.GroundUpdate1();
	ground2.GroundUpdate2();
	flag1 = Pipe_Above1.Pipe_Above1Update(variance1, points);
	flag2 = Pipe_Below1.Pipe_Below1Update(variance1);
	if (flag1 && flag2)
	{
		srand(SDL_GetTicks());
		variance1 = rand() % 201 - 100;
		Pipe_Above1.Pipe_Above1Update(variance1, points);
		Pipe_Below1.Pipe_Below1Update(variance1);
	}
	flag1 = Pipe_Above2.Pipe_Above2Update(variance2, points);
	flag2 = Pipe_Below2.Pipe_Below2Update(variance2);
	if (flag1 && flag2)
	{
		srand(SDL_GetTicks());
		variance2 = rand() % 201 - 100;
		Pipe_Above2.Pipe_Above2Update(variance2, points);
		Pipe_Below2.Pipe_Below2Update(variance2);
	}
	flag1 = Pipe_Above3.Pipe_Above3Update(variance3, points);
	flag1 = Pipe_Below3.Pipe_Below3Update(variance3);
	if (flag1 && flag2)
	{
		srand(SDL_GetTicks());
		variance3 = rand() % 201 - 100;
		Pipe_Above3.Pipe_Above3Update(variance3, points);
		Pipe_Below3.Pipe_Below3Update(variance3);
	}

	CollisionDetection();
}

void Game::CollisionDetection()
{
	if (CollisionManager::CheckCollision(&b.getDest(), &Pipe_Above1.getDest()) || CollisionManager::CheckCollision(&b.getDest(), &Pipe_Below1.getDest()) ||
		CollisionManager::CheckCollision(&b.getDest(), &Pipe_Above2.getDest()) || CollisionManager::CheckCollision(&b.getDest(), &Pipe_Below2.getDest()) ||
		CollisionManager::CheckCollision(&b.getDest(), &Pipe_Above3.getDest()) || CollisionManager::CheckCollision(&b.getDest(), &Pipe_Below3.getDest()))
	{
		Mix_VolumeChunk(hitSFX, 50);
		Mix_PlayChannel(-1, hitSFX, 0);
		SDL_Delay(500);
		Mix_VolumeChunk(dieSFX, 50);
		Mix_PlayChannel(-1, dieSFX, 0);
		Reset();
	}
	else if (CollisionManager::CheckCollision(&b.getDest(), &ground1.getDest()) || CollisionManager::CheckCollision(&b.getDest(), &ground2.getDest()) || b.getYpos() < 0)
	{
		Mix_VolumeChunk(hitSFX, 50);
		Mix_PlayChannel(-1, hitSFX, 0);
		SDL_Delay(500);
		Mix_VolumeChunk(dieSFX, 50);
		Mix_PlayChannel(-1, dieSFX, 0);
		Reset();
	}
}	

void Game::Reset()
{
	points = 0;
	variance1 = rand() % 201 - 100;
	variance2 = rand() % 201 - 100;
	variance3 = rand() % 201 - 100;
	b.Reset();
	Pipe_Above1.Reset();
	Pipe_Above2.Reset();
	Pipe_Above3.Reset();
	Pipe_Below1.Reset();
	Pipe_Below2.Reset();
	Pipe_Below3.Reset();
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	bg.Render(renderer);
	Pipe_Above1.PipeRender(renderer);
	Pipe_Below1.PipeRender(renderer);
	Pipe_Above2.PipeRender(renderer);
	Pipe_Below2.PipeRender(renderer);
	Pipe_Above3.PipeRender(renderer);
	Pipe_Below3.PipeRender(renderer);
	ground1.GroundRender(renderer);
	ground2.GroundRender(renderer);
	score.Render(renderer, 350, 10);
	b.Render(renderer);
	SDL_RenderPresent(renderer);
}

void Game::Clear()
{
	score.CloseFont();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_FreeChunk(flapSFX);
	Mix_FreeChunk(hitSFX);
	Mix_FreeChunk(pointSFX);
	Mix_FreeChunk(dieSFX);
	Mix_FreeMusic(bgm);
}
