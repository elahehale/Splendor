#include "render.h"
#include "Card.h"
#include  "raylib.h"


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
	default:
	    return GRAY;
	}
};
void render_card_at_coordinate(Card card, int coord[2]) {
	int coord_x = coord[0];
	int coord_y = coord[1];
	Color color = get_color_from_jem(card.type);
	int circle_r = 12;
	int start_size = 5;
	int space_size = 5;
	int font_size = 20;
	int rect_width = 4 * circle_r * 2 + 2 * start_size + 4 * space_size;
	int rect_height = rect_width * 1.2;
	int y = (coord_y + rect_height + 0.2 * rect_width);
	int x = coord_x + start_size + circle_r;
	int text_width = 0;

	DrawRectangle(coord_x, coord_y, rect_width, rect_height, color);
	DrawRectangle(coord_x, coord_y + rect_height, rect_width, 0.4 * rect_width, GRAY);
	std::string const score_text = std::to_string(card.score);
	const char* score_data = score_text.data();
	int score_width = MeasureText(score_data, 2*font_size);
	DrawRectangle(coord_x + 10, coord_y + 10, score_width * 2, 2*font_size + score_width , WHITE);
	DrawText(TextFormat("%i", card.score), coord_x + 10 + score_width/2, coord_y + 10 + score_width/2, 2 * font_size, BLACK);

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
};

