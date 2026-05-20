#pragma once

#include "Player.h"
#include "Message.h"
class Game {
public:	

	Game(int num, std::vector<std::string> names);
	void initialize_cards();
	void initialize_visible_cards();
	void initialize_players(std::vector<std::string> names);
	void initialize_tokens();
	bool buy_card(Player& player, Card card, int card_index);
	bool give_tokens(Player& player, int tokens_to_give[5]);
	int players_num;
	std::vector<Player> players;
	std::vector<std::vector<Card>> cards;
	std::vector<std::vector<Card>> visible_cards;
	int tokens[6];
	int initial_token_number;
	MessageHandler message_handler;



};

