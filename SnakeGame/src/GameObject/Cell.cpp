#include "Cell.h"

Cell::Cell(Color::Enum color, CellType type)
{
	position.x = 0;
	position.y = 0;
	this->size = 1;
	this->color = Color::ToSDLColor(color);
	this->type = type;
}

Cell::Cell(int x, int y, int size, Color::Enum color, CellType type)
{
	position.x = x;
	position.y = y;
	this->size = size;
	this->color = Color::ToSDLColor(color);
	this->type = type;
}

Cell::Cell(SDL_Point position, int size, Color::Enum color, CellType type)
{
	this->position = position;
	this->size = size;
	this->color = Color::ToSDLColor(color);
	this->type = type;
}

Cell::~Cell()
{
}

void Cell::Update()
{

}

void Cell::Render(SDL_Renderer* renderer)
{
	SDL_Rect squareRect = { position.x, position.y, size, size }; // x, y, width, height
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); // Set color
	SDL_RenderFillRect(renderer, &squareRect);
}

CellType Cell::GetType()
{
	return type;
}

void Cell::SetType(const CellType type)
{
	this->type = type;
}

int Cell::GetSize()
{
	return size;
}

void Cell::SetSize(int size)
{
	this->size = size;
}


void Cell::SetColor(Color::Enum color)
{
	this->color = Color::ToSDLColor(color);
}

void Cell::SetColor(int r, int g, int b, int a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}


void Cell::SetPosition(const SDL_Point position)
{
	this->position = position;
}

SDL_Point Cell::GetPosition() const
{
	return position;
}

