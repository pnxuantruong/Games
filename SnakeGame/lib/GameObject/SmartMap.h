#pragma once
#include "Map.h"
class SmartMap :
    public Map
{
public:
    SmartMap(SDL_Point position, int width, int height, int cellSize, const char* fontPath, float snakeSpeed = 0.1F, Color::Enum gridColor = Color::Enum::GRAY);
    ~SmartMap();

    virtual void Update();

    virtual Direction ChooseDirection();
    
    virtual Snake* CreateSnake(float snakeSpeed);

    const float Distance(SDL_Point p1, SDL_Point p2);
};

