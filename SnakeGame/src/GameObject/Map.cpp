#include "Map.h"

Map::Map(SDL_Point position, int width, int height, int cellSize, const char* fontPath, float snakeSpeed, Color::Enum gridColor) :Observer()
{
	CreateMap(position, width, height, cellSize, fontPath, snakeSpeed, gridColor);
	humanInput = Direction::UNKNOWN;
}

Map::~Map()
{
	delete grid;
	delete snake;

	TTF_CloseFont(font);
}

void Map::Update()
{
	
	if (stop) {
		//reload
		if (Input::Instance()->GetInput(SDLK_r)) {
			Reload();
			return;
		}

		return;
	}
	
	humanInput = ChooseDirection();

	if (snake->CanMove()) {
		snake->ChangeDirection(humanInput);
		snake->Move();
	}

	snake->Update();

	grid->Update();
}

void Map::Render(SDL_Renderer* renderer)
{
	grid->Render(renderer);

	// draw score

	char scoreStr[20]; // Buffer to hold the formatted string
	snprintf(scoreStr, sizeof(scoreStr), "Score: %d", score);
	// Assign the formatted string to a const char* pointer
	const char* scoreText = scoreStr;

	// Create a texture from the surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText, textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); // Replace renderer with your SDL_Renderer

	SDL_Rect textRect = {textPosition.x , textPosition.y, textSurface->w, textSurface->h }; // Set desired position and size of the rendered text
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect); // Replace renderer with your SDL_Renderer

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);

}

Direction Map::ChooseDirection()
{
	//up
	if (Input::Instance()->GetInput(SDLK_w)) {
		std::cout << "Up\n";
		return Direction::UP;
	}

	//down
	if (Input::Instance()->GetInput(SDLK_s)) {
		std::cout << "Down\n";
		return Direction::DOWN;
	}

	//left
	if (Input::Instance()->GetInput(SDLK_a)) {
		std::cout << "Left\n";
		return Direction::LEFT;
	}

	//right
	if (Input::Instance()->GetInput(SDLK_d)) {
		std::cout << "Right\n";
		return Direction::RIGHT;
	}

	return humanInput;
}

void Map::CreateFood() {

	do {
		food.x = std::rand() % columns;
		food.y = std::rand() % rows;
	} while (grid->GetCell(food)->GetType() == CellType::SnakePart);

	Cell* foodCell = new Cell(Color::Enum::RED, CellType::Food);
	grid->ChangeCell(food, foodCell);
}

void Map::CreateMap(SDL_Point position, int width, int height, int cellSize, const char* fontPath, float snakeSpeed, Color::Enum gridColor)
{
	this->position = position;
	this->columns = width / cellSize;
	this->rows = (int) ((int) (height * 0.95) / cellSize);


	SDL_Point gridPosition = { position.x + (width % cellSize) / 2, position.y + ((int)(height * 0.95) % cellSize) / 2 };
	this->gridColor = gridColor;
	grid = new Grid(gridPosition, columns, rows, cellSize, this->gridColor);

	snake = CreateSnake(snakeSpeed);
	snake->Attach(this);

	food.x = std::rand() % columns;
	food.y = std::rand() % rows;
	foodColor = Color::Enum::RED;
	Cell* foodCell = new Cell(foodColor, CellType::Food);
	grid->ChangeCell(food, foodCell);

	stop = false;
	score = 0;

	//text positon
	textPosition.x = position.x + (int) (0.43 * width);
	textPosition.y = position.y + (int) (0.95 * height);
	int fontSize = std::min((int)(0.075 * height), (int)(0.05 * width));

	// font texture
	font = TTF_OpenFont(fontPath, fontSize); // Replace with the path to your font file, and desired font size
	if (font == nullptr) {
		printf("Failed to load font: %s\n", TTF_GetError());
	}

	// Create a surface from the font
	textColor = Color::ToSDLColor(Color::Enum::WHITE); // Replace with desired text color
}

Snake* Map::CreateSnake(float snakeSpeed)
{
	return new Snake(grid, snakeSpeed, { std::rand() % columns, std::rand() % rows });
}

void Map::OnNotify(EventFlag flag)
{
	switch (flag)
	{
	case EventFlag::Food:
		score++;
		CreateFood();
		break;
	case EventFlag::Death:
		stop = true;
		break;
	default:
		break;
	}

}

void Map::Reload()
{
	grid->Reload();
	snake->Reload();

	do {
		food = { std::rand() % columns, std::rand() % rows };
	} while (grid->GetCell(food)->GetType() == CellType::SnakePart);

	grid->GetCell(food)->SetColor(foodColor);
	grid->GetCell(food)->SetType(CellType::Food);

	stop = false;
	score = 0;
}

