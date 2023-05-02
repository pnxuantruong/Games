#include "SearchMap.h"
#ifndef PDD
#define PDD std::pair<Direction, float>

#endif // !PDD
#ifndef CFM
#define CFM std::tuple<SDL_Point, float, std::list<Direction>>

#endif // !CFM



SearchMap::SearchMap(SDL_Point position, int width, int height, int cellSize, const char* fontPath, float snakeSpeed, Color::Enum gridColor)
	:SmartMap(position, width, height, cellSize, fontPath, snakeSpeed, gridColor)
{
	this->maxLeaf = 16384;
}

Direction SearchMap::ChooseDirection()
{
	if (movementPath.empty()) {

		snakeList = snake->ToList();

		explored.clear();
		explored.push_back(snakeList.front());

		//DFS
		
		int leaf = 0;
		if (_DFS(snakeList.size(), &leaf) == false) {
			std::cout << "HAI!! QUAY XE\n";
			movementPath.clear();
			return _TurnBack(snakeList.size());
		}

		////AStar
		//// if found path to food
		//if (AStar(food, snakeList.size())) {
		//}
		//// if not reach food find path to head
		//else {
		//	movementPath.clear();
		//	explored.clear();
		//	if (AStar(snakeList.back(), snakeList.size())) {
		//		std::cout << "Chase the tail " << snakeList.back().x << " " << snakeList.back().y << std::endl;
		//	}
		//	// if not, let the dices decide
		//	else {
		//		return _TurnBack(snakeList.size());
		//	}
		//}
		//
	}

	Direction direction = movementPath.front();

	movementPath.pop_front();

	return direction;
}

void SearchMap::Reload()
{
	SmartMap::Reload();

	explored.clear();
	movementPath.clear();
}


/* Idea: AStar
* 
* AStar():
*	if snakeList->front() == food: return true;
*	
*	f(x) = g(x) + h(x)
*	h(x): distance between cell's position and food's positon
*	g(x): how many step from head position to cell ( movepath.size() )
*	movepath: how the snake can go from head to cell (list of directions)
* 
*	states = priority_queue of (cell position, f(x), movepath)
* 
* // add to queue, smallest f(x) will on top
* 
*	while(states not empty){
*		state = actions.top()
*		if(state.cell == food) {
*			movementPath = movepath
*			return true;
*		}
* 
*		for neighbor of state.cell: (get neighbor by direction)
*			f(neighbor) = calculate f(x) of neighbor
*			movepath(neighbor) = copy state.movepath and add new direction
*			states.push_back(neighbor, f(neighbor), movepath(neighbor))
*			
*	}
*	return false;
*/

bool SearchMap::AStar(SDL_Point des, int length)
{
	// check if reach head

	if (_IsPointEqual(snakeList.front(), des)) {
		return true;
	}

	auto FxFunction = [&](SDL_Point cellPos, int movePathSizeAfterUpdate) {
		int g = movePathSizeAfterUpdate;
		float h = Distance(cellPos, des);
		return (float)g + h;
	};

	// create queue
	auto CustomCompare = [](CFM a, CFM b) {
		// need to sort ascending, smallest f(x) will on top
		return std::get<1>(a) > std::get<1>(b);
	};

	std::priority_queue<CFM, std::vector<CFM>, std::function<bool(CFM, CFM)>> states(CustomCompare);

	states.push(std::make_tuple(snakeList.front(), Distance(snakeList.front(), des), movementPath));


	// list of directions
	Direction directions[4] = { Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT };
	while (!states.empty()) {
		CFM state = states.top();
		states.pop();

		// check if state reach food
		if (_IsPointEqual(des, std::get<0>(state))) {

			movementPath.assign( std::get<2>(state).begin(), std::get<2>(state).end() );
			return true;
		}

		for (auto d : directions) {
			SDL_Point cellPos = _TakeNextPosition(std::get<0>(state), d);

			// check if cell is valid
			if (_IsInSnake(cellPos, length-1)) continue;
			if (_WasExplored(cellPos)) continue;

			// update explored
			explored.push_back(cellPos);

			std::list<Direction> movePath(std::get<2>(state)); // copy linked-list
			movePath.push_back(d); // update movepath
			float f = FxFunction(cellPos, movePath.size()) ; // calculate f(x)

			// add to queue
			states.push(std::make_tuple(cellPos, f, movePath));
		}


	}

	return false;
}

/* Idea: DFS
*
* DFS():
*	if snakeList->front() == food: return true;
*
*	actions = priority_queue of (direction, distance)
*
* // add to queue, smallest distance will on top
*	for d in directions:
*		point = take_position(d)
*		if (point in snakeList[:length]) continue
*		if (point in exploredCell) continue
*
*		actions.push({direcition, Distance(point, food)})
*
*	for action in actions:
*		update_state(action)
		if(DFS()) return true;
*		redo_state()
*	return false;
*/


bool SearchMap::_DFS(int length, int *leaf)
{
	 
	if (*leaf >= maxLeaf) {

		return false;
	}
	
	// check if reach head
	
	if (_IsPointEqual(snakeList.front(), food)) {
		return true;
	}

	// create queue
	auto CustomCompare = [](PDD a, PDD b) {
		// need to sort ascending
		return a.second > b.second;
	};

	std::priority_queue<PDD, std::vector<PDD>, std::function<bool(PDD, PDD)>> actions(CustomCompare);
	
	// add valid direction to queue
	Direction directions[4] = { Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT };

	auto Shuffle = [&]() {
		int stNum = std::rand() % 4;
		int ndNum = std::rand() % 4;

		if (std::rand() % 2 == 0) std::swap(directions[stNum], directions[3 - stNum]);
		if (std::rand() % 2 == 0) std::swap(directions[ndNum], directions[3 - ndNum]);
	};

	for (auto d : directions) {
		SDL_Point point = _TakeNextPosition(snakeList.front(), d);
		if (_IsInSnake(point, length)) continue;
		if (_WasExplored(point)) continue;
		actions.push(std::make_pair(d, Distance(point, food)));
	}

	while (!actions.empty()) {

		Direction d = actions.top().first;
		actions.pop();

		_UpdateState(d);
		if (_DFS(length, leaf)) return true;
		*leaf += 1;
		_RedoState();
	}

	return false;
}

void SearchMap::_UpdateState(Direction d)
{

	SDL_Point newHead = _TakeNextPosition(snakeList.front(), d);
	snakeList.push_front(newHead);

	// update explored
	explored.push_back(newHead);

	//update movementPath
	movementPath.push_back(d);
}

void SearchMap::_RedoState()
{
	snakeList.pop_front();

	explored.pop_back();

	movementPath.pop_back();
}

SDL_Point SearchMap::_TakeNextPosition(SDL_Point point, Direction d)
{
	SDL_Point vector({ 0, -1 });
	switch (d)
	{
	case Direction::UP:
		vector = { 0, -1 };
		break;
	case Direction::DOWN:
		vector = { 0, 1 };
		break;
	case Direction::LEFT:
		vector = { -1, 0 };
		break;
	case Direction::RIGHT:
		vector = { 1, 0 };
		break;
	default:
		break;
	}
	SDL_Point newPoint = { (columns + point.x + vector.x) % columns, (rows + point.y + vector.y) % rows };

	return newPoint;
}

bool SearchMap::_IsInSnake(SDL_Point point, int length)
{
	int i = 0;
	for (auto &p : snakeList) {
		if (i >= length) break;
		if (_IsPointEqual(p, point)) return true;
		i++;
	}
	return false;
}

bool SearchMap::_WasExplored(SDL_Point point)
{
	for (auto& p : explored) {
		if (_IsPointEqual(p, point)) return true;
	}
	return false;
}

bool SearchMap::_IsPointEqual(SDL_Point p1, SDL_Point p2)
{
	return (p1.x == p2.x) && (p1.y == p2.y);
}

Direction SearchMap::_TurnBack(int length)
{
	Direction directions[4] = { Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT };
	std::vector<Direction> chooseDirection;

	int maxNum = -1;

	for (auto dir : directions) {
		SDL_Point point = _TakeNextPosition(snakeList.front(), dir);
		if (_IsInSnake(point, length)) continue;

		// count neightbors of this neighbor
		int num = 0;
		for (auto dir2 : directions) {
			SDL_Point neightbor = _TakeNextPosition(point, dir2);
			if (_IsInSnake(neightbor, length)) continue;
			num++;
		}

		if (maxNum < num) {
			maxNum = num;
			chooseDirection.clear();
			chooseDirection.push_back(dir);
		}
		else if (maxNum == num) {
			chooseDirection.push_back(dir);
		}

	}

	std::cout << maxNum << " " << chooseDirection.size() << std::endl;
	Direction direction = Direction::UNKNOWN;
	if (chooseDirection.size() > 0) direction = chooseDirection[std::rand() % chooseDirection.size()];

	return direction;

}

