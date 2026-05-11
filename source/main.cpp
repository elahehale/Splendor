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
    const int screenWidth = 1000;
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
        render_all_visible_cards(game.visible_cards, card_boxes, hover_card_index);
        hover_card_index = return_hovered_card_index(card_boxes);
		std::cout << "hover card index: " << hover_card_index << std::endl;
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}