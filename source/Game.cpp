#include "Game.h"
#include <utils.h>
#include <fstream>
#include <string>
#include "Message.h"
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
	visible_cards[0].push_back(cards[0][3]);
	visible_cards[1].push_back(cards[1][0]);
	visible_cards[1].push_back(cards[1][1]);
	visible_cards[1].push_back(cards[1][2]);
	visible_cards[1].push_back(cards[1][3]);
	visible_cards[2].push_back(cards[2][0]);
	visible_cards[2].push_back(cards[2][1]);
	visible_cards[2].push_back(cards[2][2]);
	visible_cards[2].push_back(cards[2][4]);

	cards[0].erase(cards[0].begin(), cards[0].begin() + 4);
	cards[1].erase(cards[1].begin(), cards[1].begin() + 4);
	cards[2].erase(cards[2].begin(), cards[2].begin() + 4);

}
void Game::initialize_players(std::vector<std::string> names)
{
	for (int i = 0; i < players_num; i++) {
		players.push_back(Player(names[i]));
	}

}
bool Game::buy_card(Player& player, Card card, int card_index)
{
	int payment[6] = { 0, 0, 0, 0, 0, 0 };
	if (player.buy_card(card, payment)) {
		int level = card.level;
		visible_cards[level].erase(visible_cards[level].begin() + card_index);
		if (cards[level].size() > 0) {
			visible_cards[level].push_back(cards[level][0]);
			cards[level].erase(cards[level].begin());
		}
		for (int i = 0; i < 5; i++) {
			tokens[i] += payment[i];
		}
		return true;
	}
	return false;
}
bool Game::give_tokens(Player& player, int tokens_to_give[5])
{
	for (int i = 0; i < 5; i++) {
		if (tokens_to_give[i] > tokens[i]) {
			message_handler.set_message(TextType::Warning, "Not enough tokens of type " + std::to_string(i) + " in the game.");
			std::cout << "Not enough tokens of type " << i << " in the game." << std::endl;
			return false;
		}
		if (tokens_to_give[i] == 2 && tokens[i] < 4) {
			message_handler.set_message(TextType::Warning, "Cannot take 2 tokens of type " + std::to_string(i) + " because there are less than 4 tokens of that type in the game.");
			std::cout << "Cannot take 2 tokens of type " << i << " because there are less than 4 tokens of that type in the game." << std::endl;
			return false;
		}
	}
	if (player.take_tokens(tokens_to_give)) {
		for (int i = 0; i < 5; i++) {
			tokens[i] -= tokens_to_give[i];
		}
		return true;
	}
	return false;
}
void Game::initialize_tokens() {
    tokens[0] = 4;
    tokens[1] = 4;
    tokens[2] = 4;
    tokens[3] = 4;
    tokens[4] = 4;
	tokens[5] = 5; // yellow token
}
Game::Game(int num)
{
	players_num = num;
	cards = initialize_cards();
	initialize_tokens();
	message_handler = MessageHandler();
}


