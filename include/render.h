#pragma once 
#include "Card.h"
#include <vector>
#include  "raylib.h"

int return_hovered_card_index(Rectangle card_boxes[12]);
Rectangle render_card_at_coordinate(Card card, int coord[2]);
void render_all_visible_cards(std::vector<std::vector<Card>> visible_cards, Rectangle card_boxes[12], int hovered_index);