#include "SmartMap.h"

SmartMap::SmartMap(SDL_Point position, int width, int height, int cellSize, const char* fontPath, float snakeSpeed, Color::Enum gridColor)
{
	CreateMap(position, width, height, cellSize, fontPath, snakeSpeed, gridColor);
}

SmartMap::~SmartMap(){}

void SmartMap::Update()
{
	if (stop) {
		//reload
		if (Input::Instance()->GetInput(SDLK_r)) {
			Reload();
			return;
		}

		return;
	}

	if (snake->CanMove()) {
		Direction direction = ChooseDirection();
		
		snake->ChangeDirection(direction);
		snake->Move();
	}
	snake->Update();
}


Direction SmartMap::ChooseDirection()
{
	// 4 is number of directions
	SDL_Point neighbors[4];
	Direction directions[4];
	std::vector<Direction> chooseDirection;

	SDL_Point head = snake->GetHeadPosition();

	auto StandardPosition = [&](SDL_Point point) {
		point.x = (columns + point.x) % columns;
		point.y = (rows + point.y) % rows;
		return point;
	};

	neighbors[0] = StandardPosition({ head.x + 0, head.y - 1 }); // up
	directions[0] = Direction::UP;

	neighbors[1] = StandardPosition({ head.x + 0, head.y + 1 }); // down
	directions[1] = Direction::DOWN;

	neighbors[2] = StandardPosition({ head.x - 1, head.y + 0 }); // left
	directions[2] = Direction::LEFT;

	neighbors[3] = StandardPosition({ head.x + 1, head.y + 0 }); // right
	directions[3] = Direction::RIGHT;

	float distance = 99999;
	
	for (int i = 0; i < 4; i++)
	{
		if (grid->GetCell(neighbors[i])->GetType() == CellType::SnakePart) continue;

		float d = Distance(neighbors[i], food);
		if (distance > d) {
			distance = d;
			chooseDirection.clear();
			chooseDirection.push_back(directions[i]);
		}
		else if (distance == d) {
			chooseDirection.push_back(directions[i]);
		}
	}
	Direction direction = Direction::UNKNOWN;
	if(chooseDirection.size() > 0) direction = chooseDirection[std::rand() % chooseDirection.size()];

	return direction;
}

Snake* SmartMap::CreateSnake(float snakeSpeed)
{
	return new Snake(grid, snakeSpeed, { std::rand() % columns, std::rand() % rows }, Color::Enum::YELLOW, Color::Enum::WHITE);
}


const float SmartMap::Distance(SDL_Point p1, SDL_Point p2)
{
	// Mathatan distance
	int deltaX = std::min(std::abs(p1.x - p2.x), std::abs(p1.x - p2.x + columns) % columns);
	int deltaY = std::min(std::abs(p1.y - p2.y), std::abs(p1.y - p2.y + rows) % rows);
	
	return std::sqrt((float)(deltaX * deltaX) + (float)(deltaY * deltaY));
}