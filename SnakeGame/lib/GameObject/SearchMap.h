#include "SmartMap.h"
#include <queue>
#include <functional>

class SearchMap :
	public SmartMap 
{
public:
	SearchMap(SDL_Point position, int width, int height, int cellSize, const char* fontPath, float snakeSpeed = 0.1F, Color::Enum gridColor = Color::Enum::GRAY);
	~SearchMap() {};

	virtual Direction ChooseDirection();

	void Reload();

private:

	bool AStar(SDL_Point des, int length);

	bool _DFS(int length, int *leaf);

	void _UpdateState(Direction d);

	void _RedoState();

	SDL_Point _TakeNextPosition(SDL_Point point, Direction d);

	bool _IsInSnake(SDL_Point point, int length);

	bool _WasExplored(SDL_Point point);

	bool _IsPointEqual(SDL_Point p1, SDL_Point p2);

	// take the neighbor has most neighbors
	Direction _TurnBack(int length);


	std::list<SDL_Point> snakeList;

	std::vector<SDL_Point> explored;

	std::list<Direction> movementPath;

	int maxLeaf;
};