#include"Game.h"

Game::Game()
{
	window = NULL;
	renderer = NULL;
	isRunning = false;
	restart = false;

	b.setSrc(0, 0, 24, 32);
	b.setDest(25, HEIGHT / 2, 28, 38);

	bg.setSrc(0, 0, 512, 288);
	bg.setDest(0, 0, HEIGHT, WIDTH);
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

	ScoreTbl.setSrc(0, 0, 282, 444);
	ScoreTbl.setDest(175, 250, 320, 473);
}

bool Game::running()
{
	return isRunning;
}

void Game::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//sound
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

	//window
	window = SDL_CreateWindow("Flapping Birb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (window)
	{
		std::cout << "Window created" << std::endl;
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			std::cout << "Render created" << std::endl;
			isRunning = true;

			b.CreateTexture("Image/yellowbird1.png", renderer);
			b.CreateTexture1("Image/yellowbird2.png", renderer);
			b.CreateTexture2("Image/yellowbird3.png", renderer);

			bg.CreateTexture("Image/background-day.png", renderer);
			ScoreTbl.CreateTexture("Image/Score.png", renderer);

			ground1.CreateTexture("Image/ground.png", renderer);
			ground2.CreateTexture("Image/ground.png", renderer);

			Pipe_Above1.CreateTexture("Image/topPipe.png", renderer);
			Pipe_Below1.CreateTexture("Image/botPipe.png", renderer);
			Pipe_Above2.CreateTexture("Image/topPipe.png", renderer);
			Pipe_Below2.CreateTexture("Image/botPipe.png", renderer);
			Pipe_Above3.CreateTexture("Image/topPipe.png", renderer);
			Pipe_Below3.CreateTexture("Image/botPipe.png", renderer);


			score.CreateFont("Fonts/04B_19__.TTF", 38);
			RestartMenu.CreateTexture("Image/gameover.png", renderer);
			buttonReplay.CreateFont("Fonts/04B_19__.TTF", 40);
			buttonExit.CreateFont("Fonts/04B_19__.TTF", 40);
			highScore.CreateFont("Fonts/04B_19__.TTF", 70);
			currentScore.CreateFont("Fonts/04B_19__.TTF", 80);
			buttonReplay.Text("REPLAY", 255, 255, 255, renderer);
			buttonExit.Text("EXIT", 255, 255, 255, renderer);
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
		SDL_RenderClear(renderer);
		menu.Render(renderer, event1);
	}
	SDL_Delay(100);
}

void Game::handleEvents()
{
	b.GetJumpTime();
	SDL_PollEvent(&event1);

	if (event1.type == SDL_QUIT) {
		isRunning = false;
	}

	if (birdDie) {
		if (event1.type == SDL_MOUSEBUTTONDOWN && event1.motion.x > 490 && event1.motion.x < 620 && event1.motion.y > 485 && event1.motion.y < 525)
		{
			Mix_PlayChannel(-1, replaySound, 0);
			SDL_Delay(100);
			Reset();
		}
		else if (event1.type == SDL_MOUSEBUTTONDOWN && event1.motion.x > 490 && event1.motion.x < 560 && event1.motion.y > 535 && event1.motion.y < 575)
		{
			Mix_PlayChannel(-1, exitSound, 0);
			SDL_Delay(100);
			isRunning = false;
			Clear();
		}
	}
	else {
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
}

void Game::Update()
{

	if (birdDie) {
		Restart();
	}

	// Scoring
	std::string s;
	s = "Score: " + std::to_string(points);
	score.Text(s, 255, 255, 255, renderer);

	if (!birdDie) {
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
			if (!birdDie) {
				Mix_PlayChannel(-1, pointSFX, 0);
			}
		}
		flag1 = Pipe_Above2.Pipe_Above2Update(variance2, points);
		flag2 = Pipe_Below2.Pipe_Below2Update(variance2);
		if (flag1 && flag2)
		{
			srand(SDL_GetTicks());
			variance2 = rand() % 201 - 100;
			Pipe_Above2.Pipe_Above2Update(variance2, points);
			Pipe_Below2.Pipe_Below2Update(variance2);
			if (!birdDie) {
				Mix_PlayChannel(-1, pointSFX, 0);
			}
		}
		flag1 = Pipe_Above3.Pipe_Above3Update(variance3, points);
		flag1 = Pipe_Below3.Pipe_Below3Update(variance3);
		if (flag1 && flag2)
		{
			srand(SDL_GetTicks());
			variance3 = rand() % 201 - 100;
			Pipe_Above3.Pipe_Above3Update(variance3, points);
			Pipe_Below3.Pipe_Below3Update(variance3);
			if (!birdDie) {
				Mix_PlayChannel(-1, pointSFX, 0);
			}
		}
		CollisionDetection();
	}
}

void Game::CollisionDetection()
{
	if (CollisionManager::CheckCollision(&b.getDest(), &Pipe_Above1.getDest()) || CollisionManager::CheckCollision(&b.getDest(), &Pipe_Below1.getDest()) ||
		CollisionManager::CheckCollision(&b.getDest(), &Pipe_Above2.getDest()) || CollisionManager::CheckCollision(&b.getDest(), &Pipe_Below2.getDest()) ||
		CollisionManager::CheckCollision(&b.getDest(), &Pipe_Above3.getDest()) || CollisionManager::CheckCollision(&b.getDest(), &Pipe_Below3.getDest()))
	{
		birdDie = true;
		Mix_VolumeChunk(hitSFX, 50);
		Mix_PlayChannel(-1, hitSFX, 0);
		SDL_Delay(500);
		Mix_VolumeChunk(dieSFX, 50);
		Mix_PlayChannel(-1, dieSFX, 0);
	}
	else if (CollisionManager::CheckCollision(&b.getDest(), &ground1.getDest()) || CollisionManager::CheckCollision(&b.getDest(), &ground2.getDest()) || b.getYpos() < 0)
	{
		birdDie = true;
		Mix_VolumeChunk(hitSFX, 50);
		Mix_PlayChannel(-1, hitSFX, 0);
		Mix_VolumeChunk(dieSFX, 50);
		Mix_PlayChannel(-1, dieSFX, 0);
		SDL_Delay(500);
	}
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
	if (birdDie)
	{
		RestartMenu.Render(renderer);
		ScoreTbl.Render(renderer);
		buttonReplay.Render(renderer, 490, 485);
		buttonExit.Render(renderer, 490, 535);
		currentScore.Render(renderer, 305, 380);
		highScore.Render(renderer, 490, 345);
	}
	else
	{
		b.Render(renderer);
		score.Render(renderer, 0, 0);
	}
	SDL_RenderPresent(renderer);
}

void Game::Restart()
{
	currentScore.Text(std::to_string(points), 0, 0, 0, renderer);
	std::ifstream inputFile("HighScore.txt");
	if (inputFile)
	{
		while (!inputFile.eof())
		{
			inputFile >> _highScore;
		}
	}
	inputFile.close();
	std::ofstream writeFile("HighScore.txt");
	if (writeFile)
	{
		if (points > _highScore)
		{
			_highScore = points;
		}
		writeFile << _highScore;
	}
	writeFile.close();
	highScore.Text(std::to_string(_highScore), 0, 0, 0, renderer);
}

void Game::Reset()
{
	points = 0;
	variance1 = rand() % 201 - 100;
	variance2 = rand() % 201 - 100;
	variance3 = rand() % 201 - 100;
	b.Restart();
	Pipe_Above1.Reset();
	Pipe_Above2.Reset();
	Pipe_Above3.Reset();
	Pipe_Below1.Reset();
	Pipe_Below2.Reset();
	Pipe_Below3.Reset();
	birdDie = false;
}

void Game::Clear()
{
	currentScore.CloseFont();
	buttonExit.CloseFont();
	buttonReplay.CloseFont();
	score.CloseFont();
	highScore.CloseFont();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_FreeChunk(flapSFX);
	Mix_FreeChunk(hitSFX);
	Mix_FreeChunk(pointSFX);
	Mix_FreeChunk(dieSFX);
	Mix_FreeChunk(replaySound);
	Mix_FreeChunk(exitSound);
	Mix_FreeMusic(bgm);
}
