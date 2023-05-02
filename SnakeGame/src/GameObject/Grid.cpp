#include "Grid.h"

Grid::Grid(SDL_Point position, int columns, int rows, int cellSize, Color::Enum backgroundColor)
{
	this->position = position;
	this->backgroundColor = backgroundColor;
	this->columns = columns;
	this->rows = rows;


	// init grid
	grid.resize(this->rows);
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++)
		{
			Cell* cell = new Cell(j * cellSize + this->position.x, i * cellSize + this->position.y, cellSize, backgroundColor);
			grid[i].push_back(cell);
		}
	}
}

Grid::~Grid()
{
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++)
		{
			delete grid[i][j];
		}
	}
	grid.clear();
}

void Grid::Update()
{
	for (auto& line : grid) {
		for (auto& cell : line) {
			cell->Update();
		}
	}
}

void Grid::Render(SDL_Renderer* renderer)
{
	for (auto& line : grid) {
		for (auto& cell : line) {
			cell->Render(renderer);
		}
	}
}

void Grid::ChangeCell(SDL_Point cellPosition, Cell* cell)
{
	SDL_Point position = grid[cellPosition.y][cellPosition.x]->GetPosition();
	int size = grid[cellPosition.y][cellPosition.x]->GetSize();

	cell->SetPosition(position);
	cell->SetSize(size);

	delete grid[cellPosition.y][cellPosition.x];
	grid[cellPosition.y][cellPosition.x] = cell;
}

Cell* Grid::GetCell(SDL_Point position)
{
	return grid[position.y][position.x];
}

SDL_Point Grid::GetSize() {
	return { columns, rows };
}

void Grid::SwapCell(SDL_Point cellPos1, SDL_Point cellPos2)
{
	Cell* temp = grid[cellPos1.y][cellPos1.x];

	SDL_Point pos1 = temp->GetPosition();
	SDL_Point pos2 = grid[cellPos2.y][cellPos2.x]->GetPosition();

	grid[cellPos1.y][cellPos1.x] = grid[cellPos2.y][cellPos2.x];
	grid[cellPos1.y][cellPos1.x]->SetPosition(pos1);

	grid[cellPos2.y][cellPos2.x] = temp;
	grid[cellPos2.y][cellPos2.x]->SetPosition(pos2);
}

const SDL_Point Grid::GetPostiton()
{
	return position;
}
void Grid::Reload()
{
	for (auto& line : grid) {
		for (auto &cell : line) {
			cell->SetColor(backgroundColor);
			cell->SetType(CellType::Cell);
		}
	}
}
//
//void Grid::SetNewFood()
//{
//	int x = 0, y = 0;
//	do {
//		x = std::rand() % width;
//		y = std::rand() % height;
//	} while (map[y][x]->GetType() != CellType::SnakePart);
//
//	std::swap(map[foodPositon.y][foodPositon.x], map[y][x]);
//}
