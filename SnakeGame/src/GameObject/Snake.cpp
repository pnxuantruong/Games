#include "Snake.h"

Snake::Snake(Grid* grid, float snakeSpeed, SDL_Point position, Color::Enum headColor, Color::Enum bodyColor)
{
	this->grid = grid;
	this->constraint = grid->GetSize();

	this->speed = snakeSpeed;
	this->headColor = headColor;
	this->bodyColor = bodyColor;

	head = position;
	Cell* headCell = new Cell(headColor, CellType::SnakePart);
	this->grid->ChangeCell(head, headCell);

	length = 0;
	currentDirection = Direction::RIGHT;

	canMove = true;
	percent = 0;
}

void Snake::Update()
{
	
	if (percent > 1.0F) {
		percent = 0;
		canMove = true;
	}
	else {
		canMove = false;
		percent += speed;
	}
}

void Snake::Render(SDL_Renderer* renderer)
{
}

bool Snake::IsOpposite(Direction d1, Direction d2)
{
	switch (d1)
	{
	case Direction::UP:
		return d2 == Direction::DOWN;

	case Direction::DOWN:
		return d2 == Direction::UP;

	case Direction::LEFT:
		return d2 == Direction::RIGHT;

	case Direction::RIGHT:
		return d2 == Direction::LEFT;

	case Direction::UNKNOWN:
		return false;
	default:
		return false;
	}
}


void Snake::ChangeDirection(Direction direction)
{
	if (direction == Direction::UNKNOWN) return;


	if (direction == currentDirection) return;

	if (IsOpposite(direction, currentDirection)) {
		if (length != 0) return;
	}

	currentDirection = direction;
}

void Snake::Move()
{

	std::pair<int, int> vector2(0, -1);

	switch (currentDirection)
	{
	case Direction::UP:
		vector2.first = 0;
		vector2.second = -1;
		break;

	case Direction::DOWN:
		vector2.first = 0;
		vector2.second = 1;
		break;

	case Direction::LEFT:
		vector2.first = -1;
		vector2.second = 0;
		break;

	case Direction::RIGHT:
		vector2.first = 1;
		vector2.second = 0;
		break;

	case Direction::UNKNOWN:
		break;
	}

	// store in front of cell's position to set it to next cell position 
	SDL_Point prevCellPosition = head;

	// update head position
	head.x = (constraint.x + head.x + vector2.first) % constraint.x;
	head.y = (constraint.y + head.y + vector2.second) % constraint.y;

	CellType type = grid->GetCell(head)->GetType();
	// check if next cell is food
	if (type == CellType::Food) {

		// create new part
		Cell* cell = new Cell(bodyColor, CellType::SnakePart);
		grid->ChangeCell(head, cell);
		body.push_front(prevCellPosition);
		grid->SwapCell(head, prevCellPosition);

		length++;

		// notify to map when snake grew
		Notify(EventFlag::Food);
		return;
	}
	// check if next cell is snake
	else if (type == CellType::SnakePart) {
		std::cout << "Death\n";
		Notify(EventFlag::Death);
		return;
	}

	grid->SwapCell(head, prevCellPosition);

	//update body
	for (auto& part : body) {
		this->grid->SwapCell(part, prevCellPosition);

		SDL_Point temp = part;
		part = prevCellPosition;
		prevCellPosition = temp;
	}

	canMove = true;
}

bool Snake::CanMove()
{
	return canMove;
}

SDL_Point Snake::GetHeadPosition()
{
	return head;
}

void Snake::Reload()
{
	body.clear();

	Cell* cell = new Cell(headColor, CellType::SnakePart);
	head = { std::rand() % grid->GetSize().x, std::rand() % grid->GetSize().y };
	grid->ChangeCell(head, cell);
}

std::list<SDL_Point> Snake::ToList()
{
	std::list<SDL_Point> l;
	l.push_back({ head.x, head.y });
	
	for (auto& part : body) l.push_back({ part.x, part.y });

	return l;
}
