#pragma once
#include <stdexcept>

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
	int cost[4];
	Jem type;
	Level level;
	Card(int score, int cost[4], Jem type, Level level) {
		this->score = score;
		for (int i = 0; i < 4; i++) {
			this->cost[i] = cost[i];
		}
		if (type==Yellow) {
			throw std::invalid_argument("recieved yellow for the card type");
		}
		this->type = type;
		this->level = level;
	}
};