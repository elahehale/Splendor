#pragma once 
#include "Card.h"
#include <vector>
#include  "raylib.h"
#include "Player.h"


struct CardHoverAnimation {
	float duration;
	bool is_animating;
	int steps;
	float step_size;
	int current_step;

	CardHoverAnimation() {
		duration = 0.2f; // Duration of the animation in seconds
		is_animating = false;
		steps = duration / GetFrameTime(); // Number of steps in the animation
		step_size = GetFrameTime(); // Size of each step in pixels
		current_step = 0;
	}

};

void render_turn(Player player);
void render_tokens(int tokens[6], TokenBoxState token_boxes[25]);
void render_token_selector_btns(Rectangle seletors[6]);
int return_hovered_card_index(Rectangle card_boxes[12]);
void return_clicked_card_index(Rectangle card_boxes[12], int &is_clicked);
void return_clicked_token_index(TokenBoxState token_boxes[25], int &clicked);
void render_gather_tokens();
void render_buy_or_reserve_card(int index, std::vector<std::vector<Card>> visible_cards);
Rectangle render_card_at_coordinate(Card &card, int coord[2], bool selected);
void render_all_visible_cards(std::vector<std::vector<Card>> &visible_cards, Rectangle card_boxes[12], int hovered_index, int selected_index);