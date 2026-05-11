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
    const int screenWidth = 800;
    const int screenHeight = 450;

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
    //s = game.cards[0][15];
    //std::cout << s << std::endl;
    //--------------------------------------------------------------------------------------

    // Main game loop
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

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		int coord[2] = {60, 80};
        render_card_at_coordinate(game.cards[0][15], coord);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}