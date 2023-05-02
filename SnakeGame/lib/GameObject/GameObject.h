#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "SDL.h"
#include "Color.h"
#include <iostream>

class GameObject
{
public:
	GameObject() {};
	~GameObject() {};
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer*) = 0;
};

#endif // !GAMEOBJECT_H
