#include "Input.h"

Input* Input::pInstance = 0;

Input* Input::Instance()
{
	if (pInstance == 0) {
		pInstance = new Input();
	}
	return pInstance;
}

void Input::HandleEvents(bool *quitFlag)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		switch (event.type)
		{
		case SDL_QUIT:
			// Handle quit event, such as setting a flag to exit the application
			*quitFlag = true;
			break;

		case SDL_KEYDOWN:
			// Handle key down event
			HandleKeyDown(event);
			break;

		case SDL_KEYUP:
			// Handle key up event
			HandleKeyUp(event);
			
			break;

		default:
			// don't do anything
			break;
		}
	}
}

const bool Input::GetInput(SDL_Keycode code)
{
	if (keyCodes.empty()) return false;

	for (auto& keycode : keyCodes) {
		if (keycode == code) {
			keyCodes.remove(keycode);
			return true;
		}
	}
	return false;
}

Input::Input()
{
	queueLimit = 20;
}

Input::~Input()
{
	keyCodes.clear();
}

void Input::HandleKeyDown(SDL_Event event)
{
	if (keyCodes.size() == queueLimit) {
		std::cout << "Full\n";
		keyCodes.pop_front();
	}
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		keyCodes.push_back(SDLK_w);
		break;

	case SDLK_s:
		keyCodes.push_back(SDLK_s);
		break;

	case SDLK_a:
		keyCodes.push_back(SDLK_a);
		break;

	case SDLK_d:
		keyCodes.push_back(SDLK_d);
		break;

	case SDLK_r:
		keyCodes.push_back(SDLK_r);
		break;

	default:
		break;
	}
}

void Input::HandleKeyUp(SDL_Event event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		for (auto& keycode : keyCodes) {
			if (keycode == SDLK_w) {
				keyCodes.remove(keycode);
				break;
			}
		}
		break;

	case SDLK_s:
		for (auto& keycode : keyCodes) {
			if (keycode == SDLK_s) {
				keyCodes.remove(keycode);
				break;
			}
		}
		break;

	case SDLK_a:
		for (auto& keycode : keyCodes) {
			if (keycode == SDLK_a) {
				keyCodes.remove(keycode);
				break;
			}
		}
		break;

	case SDLK_d:
		for (auto& keycode : keyCodes) {
			if (keycode == SDLK_d) {
				keyCodes.remove(keycode);
				break;
			}
		}
		break;

	case SDLK_r:
		for (auto& keycode : keyCodes) {
			if (keycode == SDLK_r) {
				keyCodes.remove(keycode);
				break;
			}
		}
		break;

	default:
		break;
	}
}
