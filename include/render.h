#pragma once 
#include "Card.h"
#include <vector>
#include  "raylib.h"
#include "Player.h"
#include "Message.h"
class Renderer {
public:
	MessageHandler message_handler;
	int circle_r = 12;
	int start_size = 5;
	int space_size = 5;
	int font_size = 20;
	int rect_width = 4 * circle_r * 2 + 2 * start_size + 4 * space_size;
	int rect_height = int(rect_width * 1.2);

	Renderer() {
		message_handler = MessageHandler();
	}

	void render_players_state(std::vector<Player> players);
	void render_turn(Player player);
	void render_tokens(int tokens[6], TokenBoxState token_boxes[25]);
	void render_token_selector_btns(Rectangle seletors[6]);
	int return_hovered_card_index(Rectangle card_boxes[12]);
	void return_clicked_card_index(Rectangle card_boxes[12], int& is_clicked);
	void return_clicked_token_index(TokenBoxState token_boxes[25], int& clicked);
	void render_gather_tokens();
	void render_buy_or_reserve_card(int index, std::vector<std::vector<Card>> visible_cards);
	Rectangle render_card_at_coordinate(Card& card, int coord[2], bool selected);
	void render_all_visible_cards(std::vector<std::vector<Card>>& visible_cards, Rectangle card_boxes[12], int hovered_index, int selected_index);
};