#include "Player.h"
#include <iostream>
void Player::spend_to_buy(Card card, int payment[6])
{
	for (int i = 0; i < 5; i++) {
		payment[i] = std::max(0, card.cost[i] - card_counts[i]);
		if (tokens[i] < payment[i]) {
			payment[5] += payment[i] - tokens[i];
			payment[i] = tokens[i];
		}
		tokens[i] -= payment[i];
	}
	tokens[5] -= payment[5];
}

void Player::add_card(Card card)
{
	cards.push_back(card);
	score += card.score;
	card_counts[card.type]++;
}



std::string Player::get_player_state_text() const
{
	std::string text = "=================State of Player=================\n";
	text += "Player: " + name + "\n";
	text += "Score: " + std::to_string(score) + "\n";
	text += "Tokens: White(" + std::to_string(tokens[0]) + "), Red(" + std::to_string(tokens[1]) + "), Green(" + std::to_string(tokens[2]) + "), Blue(" + std::to_string(tokens[3]) + "), Black(" + std::to_string(tokens[4]) + ")\n";
	text += "Cards: White(" + std::to_string(card_counts[0]) + "), Red(" + std::to_string(card_counts[1]) + "), Green(" + std::to_string(card_counts[2]) + "), Blue(" + std::to_string(card_counts[3]) + "), Black(" + std::to_string(card_counts[4]) + ")\n";
	return text;
	
}

void Player::buy_card(Card card, int payment[6])
{
	spend_to_buy(card, payment);
	add_card(card);
}

bool Player::take_tokens(int tokens_to_take[5])
{
	for (int i = 0; i < 5; i++) {
		if (tokens_to_take[i] > 0) {
			tokens[i] += tokens_to_take[i];
		}
	}
	return true;
}
