#pragma once

#include "Player.h"
class Game {
public:	
	Game(int num);
	auto initialize_cards();
	int players_num;
	std::vector<Player> players;
	std::vector<std::vector<Card>> cards;

};

