#pragma once 
#include "Card.h"
#include <vector>
#include  "raylib.h"
#include "Player.h"

void render_turn(Player player);
void render_tokens(int tokens[6]);
int return_hovered_card_index(Rectangle card_boxes[12]);
void return_clicked_card_index(Rectangle card_boxes[12], int &is_clicked);
void render_buy_or_reserve_card(int index, std::vector<std::vector<Card>> visible_cards);
Rectangle render_card_at_coordinate(Card card, int coord[2], bool selected);
void render_all_visible_cards(std::vector<std::vector<Card>> visible_cards, Rectangle card_boxes[12], int hovered_index, int selected_index);