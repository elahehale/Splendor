#pragma once

#include "Player.h"
class Game {
public:	

	Game(int num);
	auto initialize_cards();
	void initialize_visible_cards();
	void initialize_players(std::vector<std::string> names);
	void initialize_tokens();
	bool buy_card(Player& player, Card card, int card_index);
	int players_num;
	std::vector<Player> players;
	std::vector<std::vector<Card>> cards;
	std::vector<std::vector<Card>> visible_cards;
	int tokens[6];



};

