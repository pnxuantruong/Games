#pragma once
#include <SDL_ttf.h>
#include "Grid.h"
#include "Snake.h"
#include "Observer.h"

class Map :
    public GameObject, public Observer
{
public:
    Map() {};
    Map(SDL_Point position, int width, int height, int cellSize, const char* fontPath,  float snakeSpeed = 0.1F, Color::Enum gridColor = Color::Enum::CYAN);
    ~Map();

    virtual void Update();
    virtual void Render(SDL_Renderer*);

    virtual Direction ChooseDirection();

    void CreateFood();

    virtual void CreateMap(SDL_Point position, int width, int height, int cellSize, const char* fontPath, float snakeSpeed = 0.1F, Color::Enum gridColor = Color::Enum::CYAN);

    virtual Snake* CreateSnake(float snakeSpeed);

    void OnNotify(EventFlag flag);

    virtual void Reload();


protected:
    int columns, rows;

    Grid* grid;
    Color::Enum gridColor;

    Snake* snake;

    SDL_Point food;
    Color::Enum foodColor;

    bool stop;

private:

    SDL_Point position;

    // text
    TTF_Font* font;
    SDL_Color textColor;
    SDL_Point textPosition;

    int score;

    Direction humanInput;
};

