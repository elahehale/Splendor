#pragma once
#include <stdexcept>
#include <string>
#include "raylib.h"

enum Jem {
	White = 0,
	Red, 
	Green,
	Blue,
	Black,
	Yellow
};

inline Jem stringToJem(const std::string& str) {
	if (str == "White") return Jem::White;
	if (str == "Red") return Jem::Red;
	if (str == "Green") return Jem::Green;
	if (str == "Blue") return Jem::Blue;
	if (str == "Black") return Jem::Black;
	if (str == "Yellow") return Jem::Yellow;
	throw std::invalid_argument("Unknown Jem type: " + str);
}

enum Level {
	Easy = 0,
	Medium,
	Hard
};



class Card {
public:
	int score;
	int cost[5];
	Jem type;
	Level level;

	Card(int score, int cost[5], Jem type, Level level) {
		this->score = score;
		for (int i = 0; i < 5; i++) {
			this->cost[i] = cost[i];
		}
		if (type==Yellow) {
			throw std::invalid_argument("recieved yellow for the card type");
		}
		this->type = type;
		this->level = level;
		this->is_hover_animating = false;
		this->steps = 10;
		this->current_step = 0;
	}
	operator std::string() const {
		return std::to_string(score) + " " + std::to_string(type) + " " + std::to_string(level) + " " + std::to_string(cost[0]) + " " + std::to_string(cost[1]) + " " + std::to_string(cost[2]) + " " + std::to_string(cost[3]);
	};
	float duration;
	bool is_hover_animating;
	int steps;
	float step_size;
	int current_step;

};