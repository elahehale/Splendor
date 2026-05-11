#include "Player.h"

void Player::spend_to_buy(Card card)
{
	for (int i = 0; i < 5; i++) {
		tokens[i] += std::min(0, card_counts[i] - card.cost[i]);
	}
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

bool Player::buy_card(Card card)
{
	std::string text;
	if (card.cost[0] > tokens[0] + card_counts[0]) {
		text += "Not enough White!";
		return false;
	}
	if (card.cost[1] > tokens[1] + card_counts[1]) {
		text += "Not enough Red!";
		return false;
	}
	if (card.cost[2] > tokens[2] + card_counts[2]) {
		text += "Not enough Green!";
		return false;
	}
	if (card.cost[3] > tokens[3] + card_counts[3]) {
		text += "Not enough Blue!";
		return false;
	}
	if (card.cost[4] > tokens[4] + card_counts[4]) {
		text += "Not enough Black!";
		return false;
	}
	spend_to_buy(card);
	add_card(card);
	text += "Card bought successfully!";
	return true;
}
