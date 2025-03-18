#include "GameMenu.hpp"
#include "GameFunctions.hpp"
#include "Entities.hpp"
#include "MusicFunctions.hpp"
#include <string>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

Rectangle
		startButton = { button_x, startButton_y, buttonWidth, buttonHeight },
		optionsButton = { button_x, optionsButton_y, buttonWidth, buttonHeight },
		exitButton = { button_x, exitButton_y, buttonWidth, buttonHeight },

		startButton_lines = { button_x - 5, startButton_y - 5, buttonWidth + 10, buttonHeight + 10 },
		optionsButton_lines = { button_x - 5, optionsButton_y - 5, buttonWidth + 10, buttonHeight + 10 },
		exitButton_lines = { button_x - 5, exitButton_y - 5, buttonWidth + 10, buttonHeight + 10 };


float buttonWidth = 50, buttonHeight = 25;
float button_x = 200;
float startButton_y = 250;
float optionsButton_y = 350;
float exitButton_y = 450;

bool inOptions = false;
bool inMenu = true;
bool isDead = false;
bool inCharacterSelect = false;

void GameMenu()
{
  //collisions
  Vector2 mousePos = GetMousePosition();

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      //Start 
      if (CheckCollisionPointRec(mousePos, startButton)) {
         inMenu = false;
         inCharacterSelect = true;
      }
      //Options
      else if (CheckCollisionPointRec(mousePos, optionsButton)) {
         inOptions = true;
         inMenu = false;
      }
      //Exit
      else if (CheckCollisionPointRec(mousePos, exitButton) ) {
          exit(0);
      }
  } else
  {
      //start
      if (CheckCollisionPointRec(mousePos, startButton)) {
          DrawRectangle(button_x, startButton_y, buttonWidth , buttonHeight, WHITE);
       }
       //Options
       else if (CheckCollisionPointRec(mousePos, optionsButton)) {
          DrawRectangle(button_x, optionsButton_y, buttonWidth , buttonHeight, WHITE);
       }
       //Exit
       else if (CheckCollisionPointRec(mousePos, exitButton) ) {
          DrawRectangle(button_x, exitButton_y, buttonWidth , buttonHeight, WHITE);
       }
  }

  //shapes
  ClearBackground(Color{ 50, 80, 110, 255 });
 DrawRectangleLinesEx(startButton_lines, 5, BLACK);
 DrawRectangleLinesEx(optionsButton_lines, 5, BLACK);
 DrawRectangleLinesEx(exitButton_lines, 5, BLACK);

 DrawText("2D RPG",  (screenWidth / 2) - 70, 100 , 50, BLACK);
 DrawText("Start game",button_x + 70, startButton_y + 7 , 25, BLACK);
 DrawText("Options", button_x + 70, optionsButton_y + 7 , 25, BLACK);
 DrawText("Exit game",  button_x + 70, exitButton_y + 7 , 25, BLACK);
 EndDrawing();
}

void DeathMenu(){

   Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        //Start 
        if (CheckCollisionPointRec(mousePos, startButton)) {
           isDead = false;
           orc.isAlive = true;
           orc.health = 100;
           player.isAlive = true;
           player.zone = ZONE_WORLD;
           player.health = 100;

        }
        //Options
        else if (CheckCollisionPointRec(mousePos, optionsButton)) {
           inOptions = true;
           isDead = false;
           orc.isAlive = true;
           orc.health = 100;
           player.isAlive = true;
           player.zone = ZONE_WORLD;
           player.health = 100;
        }
        //Exit
        else if (CheckCollisionPointRec(mousePos, exitButton) ) {
            exit(0);
        }
    } else
    {
        //start
        if (CheckCollisionPointRec(mousePos, startButton)) {
            DrawRectangle(button_x, startButton_y, buttonWidth , buttonHeight, WHITE);
         }
         //Options
         else if (CheckCollisionPointRec(mousePos, optionsButton)) {
            DrawRectangle(button_x, optionsButton_y, buttonWidth , buttonHeight, WHITE);
         }
         //Exit
         else if (CheckCollisionPointRec(mousePos, exitButton) ) {
            DrawRectangle(button_x, exitButton_y, buttonWidth , buttonHeight, WHITE);
         }
    }

    //shapes
    ClearBackground(Color{ 50, 80, 110, 255 });
	DrawRectangleLinesEx(startButton_lines, 5, BLACK);
	DrawRectangleLinesEx(optionsButton_lines, 5, BLACK);
	DrawRectangleLinesEx(exitButton_lines, 5, BLACK);

	DrawText("You Died :<",  (screenWidth / 2) - 250, 80 , 100, WHITE);
	DrawText("Retry",button_x + 70, startButton_y + 7 , 25, BLACK);
	DrawText("Options", button_x + 70, optionsButton_y + 7 , 25, BLACK);
	DrawText("Exit game",  button_x + 70, exitButton_y + 7 , 25, BLACK);
	EndDrawing();
}

void CharacterSelect()
{

   float knightButton_x = 130;
   float wizardButton_x = 380;
   float rougeButton_x = 640;
   float button_y = 220;

   Rectangle
		knightButton = { knightButton_x, button_y, buttonWidth, buttonHeight },
		wizardButton = { wizardButton_x, button_y, buttonWidth, buttonHeight },
		rougeButton = { rougeButton_x, button_y, buttonWidth, buttonHeight },

		knightButton_lines = { knightButton_x - 5, button_y - 5, buttonWidth + 10, buttonHeight + 10 },
		wizardButton_lines = { wizardButton_x - 5, button_y - 5, buttonWidth + 10, buttonHeight + 10 },
		rougeButton_lines = { rougeButton_x - 5, button_y - 5, buttonWidth + 10, buttonHeight + 10 };



    //collisions
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        //Knight
        if (CheckCollisionPointRec(mousePos, knightButton)) {
         player = Knight;     
         inCharacterSelect = false;                
        }
        //Wizard
        else if (CheckCollisionPointRec(mousePos, wizardButton)) {
         player = Wizard;
         inCharacterSelect = false;
         
        }
        //Rouge
        else if (CheckCollisionPointRec(mousePos, rougeButton) ) {
         player = Rouge;
         inCharacterSelect = false;
        }
    } else
    {
        //Knight
        if (CheckCollisionPointRec(mousePos, knightButton)) {
            DrawRectangle(knightButton_x, button_y, buttonWidth , buttonHeight, WHITE);
            DrawRectangle(knightButton_x - 40, button_y + 130 , buttonWidth + 200, buttonHeight + 150, GRAY);

            DrawText(TextFormat("Health: %d", Knight.health), knightButton_x - 30, button_y + 140, 25, WHITE);
            DrawText(TextFormat("Damage: %d - %d", Knight.damageMin, Knight.damageMax), knightButton_x - 30, button_y + 180, 25, WHITE);
            DrawText(TextFormat("Defense: %d", Knight.defense), knightButton_x - 30, button_y + 220, 25, WHITE);
            DrawText(TextFormat("Type: %s ", Knight.type.c_str()), knightButton_x - 30, button_y + 260, 25, WHITE);
            
         }
         //Wizard
         else if (CheckCollisionPointRec(mousePos, wizardButton)) {
            DrawRectangle(wizardButton_x, button_y, buttonWidth , buttonHeight, WHITE);
            DrawRectangle(wizardButton_x - 100, button_y + 130 , buttonWidth + 200, buttonHeight + 150, GRAY);

            DrawText(TextFormat("Health: %d", Wizard.health), wizardButton_x - 80, button_y + 140, 25, WHITE);
            DrawText(TextFormat("Damage: %d - %d", Wizard.damageMin, Wizard.damageMax), wizardButton_x - 80, button_y + 180, 25, WHITE);
            DrawText(TextFormat("Defense: %d", Wizard.defense), wizardButton_x - 80, button_y + 220, 25, WHITE);
            DrawText(TextFormat("Type: %s ", Wizard.type.c_str()), wizardButton_x - 80, button_y + 260, 25, WHITE);
         }
         //Rouge
         else if (CheckCollisionPointRec(mousePos, rougeButton) ) {
            DrawRectangle(rougeButton_x, button_y, buttonWidth , buttonHeight, WHITE);
            DrawRectangle(rougeButton_x - 140, button_y + 130 , buttonWidth + 200, buttonHeight + 150, GRAY);

            DrawText(TextFormat("Health: %d", Rouge.health), rougeButton_x - 120, button_y + 140, 25, WHITE);
            DrawText(TextFormat("Damage: %d - %d", Rouge.damageMin, Rouge.damageMax), rougeButton_x - 120, button_y + 180, 25, WHITE);
            DrawText(TextFormat("Defense: %d", Rouge.defense), rougeButton_x - 120, button_y + 220, 25, WHITE);
            DrawText(TextFormat("Type: %s ", Rouge.type.c_str()), rougeButton_x - 120, button_y + 260, 25, WHITE);

            

         }
    }

    //shapes
   ClearBackground(Color{ 50, 80, 110, 255 });
	DrawRectangleLinesEx(knightButton_lines, 5, BLACK);
	DrawRectangleLinesEx(wizardButton_lines, 5, BLACK);
	DrawRectangleLinesEx(rougeButton_lines, 5, BLACK);

	DrawText("Select Your Character",  (screenWidth / 2) - 300, 100 , 50, BLACK);
	DrawText("Knight",knightButton_x - 7, button_y - 30 , 25, BLACK);
	DrawText("Wizard", wizardButton_x- 7, button_y - 30 , 25, BLACK);
	DrawText("Rouge",  rougeButton_x- 7, button_y - 30, 25, BLACK);

   DrawTile(knightButton_x - 15, button_y + 30, 6, 0, 10); // knight
   DrawTile(wizardButton_x - 15, button_y + 30, 9, 0, 10); // wizard
   DrawTile(rougeButton_x - 15, button_y + 30, 8, 0, 10); // rouge
	EndDrawing();
}

void OptionsMenu()
{
   Vector2 mousePos = GetMousePosition();
   Rectangle backButton = { 50, 50, 180, 50 };
   ClearBackground(Color{ 50, 80, 110, 255 });

   DrawRectangle(backButton.x, backButton.y, backButton.width, backButton.height, GRAY);


    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        //Start 
        if (CheckCollisionPointRec(mousePos, backButton)) {
            inOptions = false;
            inMenu = true;   
        }
    } else
    {
        //start
        if (CheckCollisionPointRec(mousePos, backButton)) {
            DrawRectangle(backButton.x, backButton.y, backButton.width , backButton.height, WHITE);
         }
    }
	
   //sliders for volume
   if(GuiSliderBar((Rectangle){ 600, 40, 150, 40}, "Master Volume", TextFormat("%.2f", masterVolume), &masterVolume, 0.0f, 1.0f))
   {
      UpdateAudioVolumes();
   }

   if(GuiSliderBar((Rectangle){ 600, 100, 150, 40}, "Music Volume", TextFormat("%.2f", musicVolume), &musicVolume, 0.0f, 1.0f))
   {
      for(int i = 0; i < MAX_LIGHT_MUSIC; i++)
      {
         SetMusicVolume(musicLight[i], musicVolume);
         SetMusicVolume(musicDark[i], musicVolume);
         SetMusicVolume(musicAction[i], musicVolume);
      }
   }

   if(GuiSliderBar((Rectangle){ 600, 160, 160, 40}, "SoundFX Volume", TextFormat("%.2f", soundFXVolume), &soundFXVolume, 0.0f, 1.0f))
   {
      for(int i = 0; i < MAX_SOUNDS; i++)
      {
        SetSoundVolume(sounds[i], soundFXVolume);
      }
   }

   DrawText("Back to Menu", backButton.x, backButton.y, 25, BLACK);

	EndDrawing();
}
