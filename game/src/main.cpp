#include "core/game.hpp"

GameListener* setup();

Game* game = nullptr;

int main(){
	game = new Game();
	game->run(setup());

	delete game;

	return 0;
}