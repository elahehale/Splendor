#include "Game.h"
#include <utils.h>

auto Game::initialize_cards() {
	auto data = readCSV(ASSETS_PATH"Splendor_Cards.csv");

	std::vector<std::vector<Card>> cards;
	cards.push_back(std::vector<Card>()); // level 0
	cards.push_back(std::vector<Card>()); // level 1
	cards.push_back(std::vector<Card>()); // level 2
	//Level, Color, PV, Black, Blue, Green, Red, White

	for (const auto row : data) {
		int score = std::stoi(row[2]);
		int cost[5] = { std::stoi(row[7]), std::stoi(row[6]), std::stoi(row[5]), std::stoi(row[4]), std::stoi(row[3])};
		Jem type = static_cast<Jem>(stringToJem(row[1]));
		Level level = static_cast<Level>(std::stoi(row[0]) - 1);
		Card card = Card(score, cost, type, level);
		cards[static_cast<int>(level)].push_back(card);
	}
	return cards;
}
Game::Game(int num)
{
	players_num = num;
	cards = initialize_cards();
}

