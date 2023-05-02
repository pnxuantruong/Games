#pragma once
#ifndef INPUT_H
#define INPUT_H


#include "SDL.h"
#include <iostream>
#include <list>

class Input {
public:
	static Input* Instance();

	void HandleEvents(bool *quitFlag = nullptr);

	const bool GetInput(SDL_Keycode code);

protected:
	Input();
	~Input();
private:
	static Input* pInstance;

	std::list<SDL_Keycode> keyCodes;
	size_t queueLimit;

	void HandleKeyDown(SDL_Event);
	void HandleKeyUp(SDL_Event);
};


#endif // !INPUT_H