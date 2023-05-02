#include "Game.h"

Game::Game(int width, int height, int cellSize, float fps, const char* fontPath)
{
	window = nullptr;
	renderer = nullptr;
	this->fontPath = fontPath;
	SetUp(width, height, cellSize, false, fps);
	Initialize();
}

void Game::SetUp(int width, int height, int cellSize, bool endGame, float fps)
{
	this->width = width;
	this->height = height;
	this->endGame = endGame;
	this->fps = fps;
	this->cellSize = cellSize;
}

void Game::Initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
		return;
	}

	if (TTF_Init() < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize TTF: %s", TTF_GetError());
		return;
	}

	// Create a window
	window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
		SDL_Quit();
		return;
	}

	// Create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}

	
}

void Game::Start()
{
	// distance between 2 map
	int gap = width * 2 / 100;

	//// create human map only
	//Map* map = new Map({ 0, 0 }, width, height, cellSize, fontPath);
	//gameObjects.push_back(map);


	//// create auto map and human map
	//Map* map = new Map({ 0, 0 }, (width - gap) / 2, height, cellSize, fontPath);
	//gameObjects.push_back(map);

	//SearchMap* searchMap = new SearchMap({ (width + gap)/ 2, 0 }, (width - gap) / 2, height, cellSize, fontPath);
	//gameObjects.push_back(searchMap);

	//// create Smart map only
	//SmartMap* smartMap = new SmartMap({ 0, 0 }, width, height, cellSize, fontPath, 0.6F);
	//gameObjects.push_back(smartMap);

	// create Search map only
	SearchMap* searchMap = new SearchMap({ 0, 0 }, width, height, cellSize, fontPath, 0.6F);
	gameObjects.push_back(searchMap);


	while (!endGame) {

		//handle input
		Input::Instance()->HandleEvents(&endGame);
		if (endGame) Clean();


		// update
		for (auto& object : gameObjects) {
			object->Update();
		}

		//Render
		// Clear the window
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
		SDL_RenderClear(renderer);

		for (auto object : gameObjects) {
			object->Render(renderer);
		}

		// Update the screen
		SDL_RenderPresent(renderer);
		SDL_Delay(1000 / fps);

	}


}

void Game::Clean()
{
	endGame = true;

	if (window) SDL_DestroyWindow(window);
	if (renderer) SDL_DestroyRenderer(renderer);
	gameObjects.clear();
	TTF_Quit();
	SDL_Quit();
}
