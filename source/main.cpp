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
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // initialization of the game
    const int screenWidth = 1500;
    const int screenHeight = 800;
    int turn = 0;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

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
	std::cout << game.players[0].name << std::endl;
	Player& player = game.players[0];
    std::string text = player; // OK	
    std::cout << text << std::endl;

	bool buy_result = game.buy_card(game.players[0], game.visible_cards[0][0], 0);
	std::cout << "buy result: " << buy_result << std::endl;
	text = player; // OK	
    std::cout << text << std::endl;
	Rectangle card_boxes[12];
    //s = game.cards[0][15];
    //std::cout << s << std::endl;
    //--------------------------------------------------------------------------------------

    // Main game loop
    int hover_card_index = -1;
	int clicked_card_index = -1;
    bool card_clicked = false;
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
        render_all_visible_cards(game.visible_cards, card_boxes, hover_card_index, clicked_card_index);
        render_turn(game.players[turn]);
        hover_card_index = return_hovered_card_index(card_boxes);
        return_clicked_card_index(card_boxes, clicked_card_index);

        if (clicked_card_index!= -1) {
            render_buy_or_reserve_card(clicked_card_index, game.visible_cards);

        }
        if (IsKeyPressed(KEY_Y)) {
            std::cout << "Y is pressed!" << std::endl;
            int row = clicked_card_index / 4;
            int col = clicked_card_index % 4;
            game.buy_card(game.players[turn], game.visible_cards[row][col], col);
			turn = (turn + 1) % game.players_num;
			clicked_card_index = -1;
        }

        //std::cout << "hover card index: " << hover_card_index << std::endl;
        std::cout << "clicked card index: " << clicked_card_index << std::endl;
        render_tokens(game.tokens);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}