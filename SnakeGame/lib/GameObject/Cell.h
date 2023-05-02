#pragma once
#ifndef CELL_H
#define CELL_H

#include "GameObject.h"

enum class CellType {
    Cell,
    SnakePart,
    Food
};

class Cell :
    public GameObject
{
public:
    Cell(Color::Enum color = Color::Enum::TRANSPARENT, CellType type = CellType::Cell);
    Cell(int x, int y, int size, Color::Enum color = Color::Enum::TRANSPARENT, CellType type = CellType::Cell);
    Cell(SDL_Point position, int size, Color::Enum color = Color::Enum::TRANSPARENT, CellType type = CellType::Cell);
    ~Cell();

    void Update();

    void Render(SDL_Renderer*);

    CellType GetType();
    void SetType(const CellType type);

    int GetSize();
    void SetSize(int size);

    void SetColor(Color::Enum);
    void SetColor(int r, int g, int b, int a);

    void SetPosition(const SDL_Point);
    SDL_Point GetPosition() const;

private:
    SDL_Point position;
    SDL_Color color;

    CellType type;
    // width and height in SDL
    int size;
};

#endif // !CELL_H
