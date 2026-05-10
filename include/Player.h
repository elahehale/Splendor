#pragma once

#include "Card.h"
#include <vector>
#include <string>

class Player {
public:
	int score;
	int reserved_tokens;
	std::vector<Card> cards;
	std::vector<Card> reserved_cards;
	std::string name;
};