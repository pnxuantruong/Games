#include <SDL.h>
#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {

	srand(time(NULL));
	Game game(700, 500, 25, 60);

	game.Start();

	return 0;
}