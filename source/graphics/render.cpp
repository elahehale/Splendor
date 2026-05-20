#include "render.h"
#include "Card.h"
#include  "raylib.h"
#include <vector>
#include <iostream>
#include <Game.h>
#include <string>
Color get_color_from_jem(auto type) {
	switch (type) {
	case Jem::White:
		return WHITE;
	case Jem::Red:
		return RED;
	case Jem::Green:
		return DARKGREEN;
	case Jem::Blue:
		return BLUE;
	case Jem::Black:
		return DARKBROWN;
	case Jem::Yellow:	
		return GOLD;
	default:
	    return GRAY;
	}
};



//int circle_r = 12;
//int start_size = 5;
//int space_size = 5;
//int font_size = 20;
//int rect_width = 4 * circle_r * 2 + 2 * start_size + 4 * space_size;
//int rect_height = int (rect_width * 1.2);


void Renderer::render_players_state(std::vector<Player> players)
{
	int x = 600;
	int y = 150;
	for (const auto& player : players) {
		std::string text = static_cast<std::string>(player);
		DrawText((text).c_str(), x, y, font_size, BLACK);
		y += font_size * 6;
	}
}

void Renderer::render_turn(Player player)
{
	std::string text = player.name + "'s Turn";
	DrawText( (text).c_str() , 600, 10, 30, RED);
}

void Renderer::render_tokens(int tokens[6], TokenBoxState token_boxes[25])
{
	int x = 20;
	int y = 3 * (rect_height + int(0.4 * rect_width)) + 120;
	int temp_y = y;
	for (int i = 0;i < 6; i++) {
		if (tokens[i] > 0) {
			for (int tok_num = 0; tok_num < tokens[i]; tok_num++) {
				if (token_boxes[i*4 + tok_num].is_clicked){
					Rectangle shadow_token_rect = { x -2 , temp_y - 2, 4 * circle_r + 4,  circle_r + 4 };
					DrawRectangleRounded(shadow_token_rect, 0.5, 10, GRAY);
				}
				Rectangle token_rect = { x, temp_y, 4 * circle_r,  circle_r };
				DrawRectangleRounded(token_rect, 0.5, 10, get_color_from_jem(i));
				temp_y +=  circle_r + space_size;
				token_boxes[i * 4 + tok_num].box = token_rect;
				token_boxes[i * 4 + tok_num].enabled = true;
			}
			for (int tok_num = tokens[i]; tok_num < 4; tok_num++) {
				Rectangle token_rect = { 0,0,0,0 };
				token_boxes[i * 4 + tok_num].box = token_rect;
				token_boxes[i * 4 + tok_num].enabled = false;
			}
		}
		else {
			Rectangle token_rect = { x, y, 2 * circle_r,  circle_r };
			DrawRectangleRounded(token_rect, 0.5, 10, GRAY);
		}
		x += 4 * circle_r + space_size;
		temp_y = y;
	}
}
void Renderer::render_token_selector_btns(Rectangle seletors[6]) {

	int x = 20;
	int y = 3 * (rect_height + int(0.4 * rect_width)) + 60;
	int temp_y = y;
	for (int i = 0;i < 6; i++) {
		Rectangle token_rect = { x, y, 4 * circle_r,  4*circle_r };
		DrawRectangle(x,y, 4*circle_r, 4*circle_r, get_color_from_jem(i));
		x += 4 * circle_r + space_size;
		seletors[i] = token_rect;
	}
}
int Renderer::return_hovered_card_index(Rectangle card_boxes[12])
{
	for (int i = 0; i < 12; i++) {
		if (CheckCollisionPointRec(GetMousePosition(), card_boxes[i])) {

			return i;
		}
	}
	return -1;
}
void Renderer::return_clicked_card_index(Rectangle card_boxes[12], int &is_clicked)
{
	for (int i = 0; i < 12; i++) {
		if (CheckCollisionPointRec(GetMousePosition(), card_boxes[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			is_clicked = i;
		}
	}
}
void Renderer::return_clicked_token_index(TokenBoxState token_boxes[25], int &clicked)
{
	for (int i = 0; i < 25; i++) {
		if (CheckCollisionPointRec(GetMousePosition(), token_boxes[i].box) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			if (!token_boxes[i].enabled) {
				return;
			}
			token_boxes[i].is_clicked = !token_boxes[i].is_clicked;
			if (token_boxes[i].is_clicked) {
				clicked++;
			}
			else {
				clicked = clicked - 1;
			}
		}
	}
}

void Renderer::render_buy_or_reserve_card(int index, std::vector<std::vector<Card>> visible_cards)
{
	int row = index / 4;
	int col = index % 4;
	std::string text = "Do you want to buy or reserve this card? (Y/N)";
    message_handler.set_message(TextType::Question, text);
	//DrawText((text).c_str(), 600, 50, 20, RED);
}
void Renderer::render_gather_tokens()
{
	std::string text = "Do you want to gather selected tokens? (G/N)";
	message_handler.set_message(TextType::Question, text);
	//DrawText((text).c_str(), 600, 100, 20, BLUE);
}
Rectangle Renderer::render_card_at_coordinate(Card &card, int coord[2], bool selected) {
	int coord_x = coord[0];
	int coord_y = coord[1];
	Color color = get_color_from_jem(card.type);


	int text_width = 0;
	//std::cout << "animating" << card.current_step << std::endl;

	if(card.is_hover_animating){

			//std::cout << "animating step" << card.current_step << std::endl;
			coord_y -= int(card.current_step * 10 / card.steps);
			if (card.current_step < card.steps) {

				card.current_step = card.current_step + 1;
			}
			//std::cout << "animating step next" << card.current_step << std::endl;

	}
	else {
		card.is_hover_animating = false;
		if (card.current_step != 0) {
			coord_y -= int(card.current_step * 10 / card.steps);
			card.current_step -= 1;
		}
	}
	int y = (coord_y + rect_height + 0.2 * rect_width);
	int x = coord_x + start_size + circle_r;
	Rectangle card_rect = { coord_x, coord_y, rect_width, rect_height + int(0.4 * rect_width) };
	if (selected) {
		DrawRectangle(coord_x - 5, coord_y - 5, rect_width + 10, rect_height + int(0.4 * rect_width) + 10, BLACK);
	}
	DrawRectangle(coord_x, coord_y, rect_width, rect_height, color);
	DrawRectangle(coord_x, coord_y + rect_height, rect_width, 0.4 * rect_width, GRAY);
	std::string const score_text = std::to_string(card.score);
	const char* score_data = score_text.data();
	int score_width = MeasureText(score_data, 2 * font_size);
	DrawRectangle(coord_x + 10, coord_y + 10, score_width * 2, 2 * font_size + score_width, WHITE);
	DrawText(TextFormat("%i", card.score), coord_x + 10 + score_width / 2, coord_y + 10 + score_width / 2, 2 * font_size, BLACK);

	for (int i = 0; i < 5; i++) {
		if (card.cost[i] > 0) {

			DrawCircle(x, y, circle_r, get_color_from_jem(i));
			std::string const text = std::to_string(card.cost[0]);
			const char* data = text.data();
			text_width = MeasureText(data, font_size);
			DrawText(TextFormat("%i", card.cost[i]), x - circle_r + (2 * circle_r - text_width) / 2, y - circle_r + (2 * circle_r - font_size) / 2 + 1, font_size, BLACK);
			x += circle_r * 2 + space_size;
		}
	}
	return card_rect;
}

void Renderer::render_all_visible_cards(std::vector<std::vector<Card>> &visible_cards, Rectangle card_boxes[12], int hovered_index, int selected_index)
{
	int x = 0;
	int y = 0;
	int index = 0;
	bool is_hovered = false;
	bool is_selected = false;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 4; col++)
		{
			index = 4 * row + col;
			is_hovered = (index == hovered_index);
			is_selected = (index == selected_index);
			x = rect_width * col + 20 * col + 10;
			y = (int(0.4 * rect_width) + rect_height) * row + 20 * row + 10;
			//if (is_hovered) {
			//	x -= 5;
			//	y -= 5;
			//}
			card_boxes[index] = render_card_at_coordinate(visible_cards[row][col], new int[2] { x,y }, is_selected);
		} 
	}
}
;

