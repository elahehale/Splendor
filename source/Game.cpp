#include "Game.h"
#include <utils.h>
#include <fstream>
#include <string>
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
void Game::initialize_visible_cards()
{
	visible_cards.push_back(std::vector<Card>()); // level 0
	visible_cards.push_back(std::vector<Card>()); // level 1
	visible_cards.push_back(std::vector<Card>()); // level 2
	visible_cards[0].push_back(cards[0][0]);
	visible_cards[0].push_back(cards[0][1]);
	visible_cards[0].push_back(cards[0][2]);
	visible_cards[1].push_back(cards[1][0]);
	visible_cards[1].push_back(cards[1][1]);
	visible_cards[1].push_back(cards[1][2]);
	visible_cards[2].push_back(cards[2][0]);
	visible_cards[2].push_back(cards[2][1]);
	visible_cards[2].push_back(cards[2][2]);

	cards[0].erase(cards[0].begin(), cards[0].begin() + 3);
	cards[1].erase(cards[1].begin(), cards[1].begin() + 3);
	cards[2].erase(cards[2].begin(), cards[2].begin() + 3);

}
void Game::initialize_players(std::vector<std::string> names)
{
	for (int i = 0; i < players_num; i++) {
		players.push_back(Player(names[i]));
	}

}
Game::Game(int num)
{
	players_num = num;
	cards = initialize_cards();
}

