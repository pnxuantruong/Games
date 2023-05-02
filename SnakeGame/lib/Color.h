#pragma once
#ifndef COLOR_H
#define COLOR_H

#include "SDL.h"

class Color {
public:
	enum class Enum {
		RED,
		GREEN,
		BLUE,
		YELLOW,
		CYAN,
		WHITE,
		BLACK,
		TRANSPARENT,
		GRAY,
	};

	static SDL_Color ToSDLColor(const Color::Enum color) {
		SDL_Color sdlColor{};
		switch (color) {
		case Enum::RED:
			return sdlColor = { 255, 0, 0, 255 };

		case Enum::GREEN:
			return sdlColor = { 0, 200, 0, 255 };

		case Enum::BLUE:
			return sdlColor = { 0, 0, 255, 255 };

		case Enum::YELLOW:
			return sdlColor = { 255, 255, 0, 255 };

		case Enum::CYAN:
			return sdlColor = { 0, 255, 255, 255 };

		case Enum::WHITE:
			return sdlColor = { 255, 255, 255, 255 };

		case Enum::BLACK:
			return sdlColor = { 0, 0, 0, 255 };

		case Enum::TRANSPARENT:
			return sdlColor = { 0, 0, 0, 0 };

		case Enum::GRAY:
			return sdlColor = { 150, 150, 150, 255 };
			// Handle additional colors here
		}
		return sdlColor;
	};
};

#endif // !COLOR
