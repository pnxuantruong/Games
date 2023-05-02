#pragma once
#ifndef GRID_H
#define GRID_H


#include "GameObject.h"
#include <vector>
#include "Cell.h"

class Grid :
	public GameObject
{
public:
	Grid(SDL_Point position, int columns, int rows, int cellSize, Color::Enum backgroundColor = Color::Enum::GRAY);
	~Grid();

	void Update();
	
	void Render(SDL_Renderer*);

	void ChangeCell(SDL_Point cellPosition, Cell* cell);
	Cell* GetCell(SDL_Point position);

	SDL_Point GetSize();

	void SwapCell(SDL_Point cellPos1, SDL_Point cellPos2);
	const SDL_Point GetPostiton();

	void Reload();


private:
	// top left position
	SDL_Point position;
	// number of cells
	int columns, rows;
	Color::Enum backgroundColor; 

	// Cell container
	std::vector<std::vector<Cell*>> grid;

};


#endif // !GRID_H
