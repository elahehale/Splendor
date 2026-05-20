// Splendor.cpp : Defines the entry point for the application.
//
#include "utils.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Game.h"
#include "Splendor.h"
#include "raylib.h"
#include "Card.h"
#include "render.h"
#include "Message.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // initialization of the game
    const int screenWidth = 1700;
    const int screenHeight = 1000;
    int turn = 0;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    //SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_UNDECORATED);
    //InitWindow(GetScreenWidth(), GetScreenHeight(), "Borderless fullscreen");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	Game game = Game(2);
    shuffle_list(game.cards[0]);
    shuffle_list(game.cards[1]);
    shuffle_list(game.cards[2]);
    std::cout << game.cards[0].size() << std::endl;

    game.initialize_visible_cards();
	std::cout << game.cards[0].size() << std::endl;
	std::cout << game.visible_cards[0].size() << std::endl;
    
	game.initialize_players({ "Alice", "Bob" });
	//std::cout << game.players[0].name << std::endl;
	//Player& player = game.players[0];
 //   std::string text = player; // OK	
 //   std::cout << text << std::endl;

	//bool buy_result = game.buy_card(game.players[0], game.visible_cards[0][0], 0);
	//std::cout << "buy result: " << buy_result << std::endl;
	//text = player; // OK	
 //   std::cout << text << std::endl;
	Rectangle card_boxes[12];
    Rectangle token_selector_boxes[6];
    TokenBoxState token_boxes[25] = {};

    //std::vector<std::vector<Rectangle>> token_boxes;
    //token_boxes.push_back(std::vector<Rectangle>());
    //token_boxes.push_back(std::vector<Rectangle>());
    //token_boxes.push_back(std::vector<Rectangle>());
    //token_boxes.push_back(std::vector<Rectangle>());
    //token_boxes.push_back(std::vector<Rectangle>());
    //token_boxes.push_back(std::vector<Rectangle>());
    //s = game.cards[0][15];
    //std::cout << s << std::endl;
    //--------------------------------------------------------------------------------------

    // Main game loop
    int hover_card_index = -1;
	int clicked_card_index = -1;
	int clicked_token_index = -1;
	int prev_hover_card_index = -1;
	int token_clicked = 0;
	int tokens_to_gather[5] = { 0,0,0,0,0 };   
	Renderer renderer = Renderer();
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        renderer.render_all_visible_cards(game.visible_cards, card_boxes, hover_card_index, clicked_card_index);
        renderer.render_turn(game.players[turn]);
        renderer.message_handler.update();
        hover_card_index = renderer.return_hovered_card_index(card_boxes);
        if (hover_card_index != -1) {
            game.visible_cards[hover_card_index / 4][hover_card_index % 4].is_hover_animating = true;
        }
        if (prev_hover_card_index != -1 && prev_hover_card_index != hover_card_index) {
            game.visible_cards[prev_hover_card_index / 4][prev_hover_card_index % 4].is_hover_animating = false;
		}
        renderer.return_clicked_card_index(card_boxes, clicked_card_index);
        renderer.render_token_selector_btns(token_selector_boxes);
        renderer.return_clicked_token_index( token_boxes,  token_clicked);
        renderer.render_tokens(game.tokens, token_boxes);
        renderer.render_players_state(game.players);
        if (token_clicked > 0) {
            renderer.render_gather_tokens();
		}
        if (clicked_card_index!= -1) {
            renderer.render_buy_or_reserve_card(clicked_card_index, game.visible_cards);
        }
        if (IsKeyPressed(KEY_G)) {
            std::cout << "G is pressed!" << std::endl;
            for (int i = 0; i < 25; i++) {
                if (token_boxes[i].is_clicked) {
					int token_type = i / 4;
					tokens_to_gather[token_type] = tokens_to_gather[token_type] + 1;
                    token_boxes[i].is_clicked = false;
                }
			}
			std::cout << "tokens to gather: " << tokens_to_gather[0] << " " << tokens_to_gather[1] << " " << tokens_to_gather[2] << " " << tokens_to_gather[3] << " " << tokens_to_gather[4] << std::endl;
			bool gather_result = game.give_tokens(game.players[turn], tokens_to_gather);
			std::cout << "gather result: " << gather_result << std::endl;
            if (gather_result)
            {
				std::cout << "Tokens gathered successfully!" << std::endl;
                Player& player = game.players[turn];
                std::string text = player; // OK	
                std::cout << text << std::endl;
                turn = (turn + 1) % game.players_num;
                clicked_card_index = -1;
               
            }
            for (int j = 0; j < 5; j++) {
                tokens_to_gather[j] = 0;
            }
            std::cout << "tokens to gather: " << tokens_to_gather[0] << " " << tokens_to_gather[1] << " " << tokens_to_gather[2] << " " << tokens_to_gather[3] << " " << tokens_to_gather[4] << std::endl;

            for (int k = 0; k < 25; k++) {
                token_boxes[k].is_clicked = false;

            }

        }
        if (IsKeyPressed(KEY_Y)) {
            std::cout << "Y is pressed!" << std::endl;
            int row = clicked_card_index / 4;
            int col = clicked_card_index % 4;
			bool buy_result = game.buy_card(game.players[turn], game.visible_cards[row][col], col);
			std::cout << "buy result: " << buy_result << std::endl;
            if  (buy_result)
            {
                turn = (turn + 1) % game.players_num;
                clicked_card_index = -1;
            }
        }
		prev_hover_card_index = hover_card_index;
        renderer.message_handler.show();
        //std::cout << "hover card index: " << hover_card_index << std::endl;
        //std::cout << "clicked card index: " << clicked_card_index << std::endl;
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}