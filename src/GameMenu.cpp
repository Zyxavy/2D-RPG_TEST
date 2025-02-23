#include "GameMenu.hpp"
#include "GameFunctions.hpp"

Rectangle
		start_button = { button_x, start_button_y, button_width, button_height },
		options_button = { button_x, options_button_y, button_width, button_height },
		exit_button = { button_x, exit_button_y, button_width, button_height },

		start_button_lines = { button_x - 5, start_button_y - 5, button_width + 10, button_height + 10 },
		options_button_lines = { button_x - 5, options_button_y - 5, button_width + 10, button_height + 10 },
		exit_button_lines = { button_x - 5, exit_button_y - 5, button_width + 10, button_height + 10 };



float button_width = 50, button_height = 25;
float button_x = 200;
float start_button_y = 250;
float options_button_y = 350;
float exit_button_y = 450;


bool inMenu = true;

void GameMenu()
{
    //collisions
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        //Start 
        if (CheckCollisionPointRec(mousePos, start_button)) {
           inMenu = false;
        }
        //Options
        else if (CheckCollisionPointRec(mousePos, options_button)) {
           //WIP
        }
        //Exit
        else if (CheckCollisionPointRec(mousePos, exit_button) ) {
            exit(0);
        }
    } else
    {
        //start
        if (CheckCollisionPointRec(mousePos, start_button)) {
            DrawRectangle(button_x, start_button_y, button_width , button_height, WHITE);
         }
         //Options
         else if (CheckCollisionPointRec(mousePos, options_button)) {
            DrawRectangle(button_x, options_button_y, button_width , button_height, WHITE);
         }
         //Exit
         else if (CheckCollisionPointRec(mousePos, exit_button) ) {
            DrawRectangle(button_x, exit_button_y, button_width , button_height, WHITE);
         }
    }

    //shapes
    ClearBackground(Color{ 50, 80, 110, 255 });
	DrawRectangleLinesEx(start_button_lines, 5, BLACK);
	DrawRectangleLinesEx(options_button_lines, 5, BLACK);
	DrawRectangleLinesEx(exit_button_lines, 5, BLACK);

	DrawText("2D RPG",  (screenWidth / 2) - 70, 100 , 40, BLACK);
	DrawText("Start game",button_x + 70, start_button_y + 7 , 25, BLACK);
	DrawText("Options", button_x + 70, options_button_y + 7 , 25, BLACK);
	DrawText("Exit game",  button_x + 70, exit_button_y + 7 , 25, BLACK);
	EndDrawing();
}
