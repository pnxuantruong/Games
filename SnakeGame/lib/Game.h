#pragma once
#ifndef GAME_H
#define GAME_H


#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <list>
#include "Map.h"
#include "SmartMap.h"
#include <filesystem>
#include "SearchMap.h"

class Game
{
public:

	// if "./assets/font/ThaleahFat_TTF.ttf" don't work
	// try to use "../assets/font/ThaleahFat_TTF.ttf"
	// or "../../assets/font/ThaleahFat_TTF.ttf"
	Game(int width, int height, int cellSize = 30, float fps = 60, const char* fontPath = "./assets/font/ThaleahFat_TTF.ttf");

	~Game() {
		Clean();
	}

	void Initialize();

	void Start();

	void Clean();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width, height;
	std::list<GameObject*> gameObjects;

	// game properties
	bool endGame;
	float fps;
	int cellSize;

	// font Path
	const char* fontPath;

	void SetUp(int width, int height, int cellSize = 30, bool endGame = false, float fps = 60);
};

#endif // !GAME_H

