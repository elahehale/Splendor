#pragma once

#include "Card.h"
#include <vector>
#include <string>

class Player {
private:
	void spend_to_buy(Card card, int payment[6]);
	void add_card(Card card);
	std::string get_player_state_text() const;

public:
	int score;
	int tokens[6];
	int card_counts[5];
	std::vector<Card> cards;
	std::vector<Card> reserved_cards;
	std::string name;
	void buy_card(Card card, int payment[6]);
	bool take_tokens(int tokens_to_take[5]);
	operator std::string() const {
		std::string text = get_player_state_text();
		return text;
	}
	Player(std::string name) {
		this->name = name;
		this->score = 0;
		for (int i = 0; i < 5; i++) {
			this->tokens[i] = 0;
			this->card_counts[i] = 0;
		}
		this->tokens[6] = 0;

	}
};