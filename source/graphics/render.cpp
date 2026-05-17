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
int circle_r = 12;
int start_size = 5;
int space_size = 5;
int font_size = 20;
int rect_width = 4 * circle_r * 2 + 2 * start_size + 4 * space_size;
int rect_height = int (rect_width * 1.2);


void render_turn(Player player)
{
	std::string text = player.name + "'s Turn";
	DrawText( (text).c_str() , 600, 10, 30, RED);
}

void render_tokens(int tokens[6])
{
	int x = 20;
	int y = 3 * (rect_height + int(0.4 * rect_width)) + 80;
	int temp_y = y;
	for (int i = 0;i < 6; i++) {
		if (tokens[i] > 0) {
			for (int tok_num = 0; tok_num < tokens[i]; tok_num++) {
				Rectangle token_rect = { x, temp_y, 4 * circle_r,  circle_r };
				DrawRectangleRounded(token_rect, 0.5, 10, get_color_from_jem(i));
				temp_y +=  circle_r + space_size;
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

int return_hovered_card_index(Rectangle card_boxes[12])
{
	for (int i = 0; i < 12; i++) {
		if (CheckCollisionPointRec(GetMousePosition(), card_boxes[i])) {
			return i;
		}
	}
	return -1;
}
void return_clicked_card_index(Rectangle card_boxes[12], int &is_clicked)
{
	for (int i = 0; i < 12; i++) {
		if (CheckCollisionPointRec(GetMousePosition(), card_boxes[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			is_clicked = i;
		}
	}
}

void render_buy_or_reserve_card(int index, std::vector<std::vector<Card>> visible_cards)
{
	int row = index / 4;
	int col = index % 4;
	std::string text = "Do you want to buy or reserve this card? (Y/N)";
	DrawText((text).c_str(), 600, 50, 20, RED);
}

Rectangle render_card_at_coordinate(Card card, int coord[2], bool selected) {
	int coord_x = coord[0];
	int coord_y = coord[1];
	Color color = get_color_from_jem(card.type);

	int y = (coord_y + rect_height + 0.2 * rect_width);
	int x = coord_x + start_size + circle_r;
	int text_width = 0;
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

void render_all_visible_cards(std::vector<std::vector<Card>> visible_cards, Rectangle card_boxes[12], int hovered_index, int selected_index)
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
			if (is_hovered) {
				x -= 5;
				y -= 5;
			}
			card_boxes[index] = render_card_at_coordinate(visible_cards[row][col], new int[2] { x,y }, is_selected);
		} 
	}
}
;

