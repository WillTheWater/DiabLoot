#include "Game.h"

int main()
{
	auto game = std::make_unique<Game>();
	game->Run();
	return 0;   
}