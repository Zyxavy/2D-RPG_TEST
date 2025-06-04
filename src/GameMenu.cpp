#include "GameMenu.hpp"
#include "GameFunctions.hpp"
#include "Entities.hpp"
#include "MusicFunctions.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include <string>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

//for SoundFx
static bool hoveringOverItems = false;
static double lastHoverSoundTime = 0.0;

static bool showItemInfo = false;
static bool healthPotionsWasClicked = false;
static bool energyFoodWasClicked = false;

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
          //enemies
           Player.SetAlive(true);
           Player.SetZone(ZONE_WORLD);
           Player.SetHealth(Player.GetMaxHealth());

        }
        //Options
        else if (CheckCollisionPointRec(mousePos, optionsButton)) {
           inOptions = true;
           isDead = false;
           //eniemies
           Player.SetAlive(true);
           Player.SetZone(ZONE_WORLD);
           Player.SetHealth(Player.GetMaxHealth());
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
         Player = Knight;     
         inCharacterSelect = false;                
        }
        //Wizard
        else if (CheckCollisionPointRec(mousePos, wizardButton)) {
         Player = Wizard;
         inCharacterSelect = false;
         
        }
        //Rogue
        else if (CheckCollisionPointRec(mousePos, rougeButton) ) {
         Player = Rogue;
         inCharacterSelect = false;
        }
    } else
    {
        //Knight
        if (CheckCollisionPointRec(mousePos, knightButton)) {
            DrawRectangle(knightButton_x, button_y, buttonWidth , buttonHeight, WHITE);
            DrawRectangle(knightButton_x - 40, button_y + 130 , buttonWidth + 200, buttonHeight + 150, GRAY);

            DrawText(TextFormat("Health: %d", Knight.GetMaxHealth()), knightButton_x - 30, button_y + 140, 25, WHITE);
            DrawText(TextFormat("Damage: %d - %d", Knight.GetDamageMin(), Knight.GetDamageMax()), knightButton_x - 30, button_y + 180, 25, WHITE);
            DrawText(TextFormat("Defense: %d", Knight.GetDefense()), knightButton_x - 30, button_y + 220, 25, WHITE);
            DrawText(TextFormat("Type: %s ", Knight.GetType().c_str()), knightButton_x - 30, button_y + 260, 25, WHITE);
            
         }
         //Wizard
         else if (CheckCollisionPointRec(mousePos, wizardButton)) {
            DrawRectangle(wizardButton_x, button_y, buttonWidth , buttonHeight, WHITE);
            DrawRectangle(wizardButton_x - 100, button_y + 130 , buttonWidth + 200, buttonHeight + 150, GRAY);

            DrawText(TextFormat("Health: %d", Wizard.GetMaxHealth()), wizardButton_x - 80, button_y + 140, 25, WHITE);
            DrawText(TextFormat("Damage: %d - %d", Wizard.GetDamageMin(), Wizard.GetDamageMax()), wizardButton_x - 80, button_y + 180, 25, WHITE);
            DrawText(TextFormat("Defense: %d", Wizard.GetDefense()), wizardButton_x - 80, button_y + 220, 25, WHITE);
            DrawText(TextFormat("Type: %s ", Wizard.GetType().c_str()), wizardButton_x - 80, button_y + 260, 25, WHITE);
         }
         //Rogue
         else if (CheckCollisionPointRec(mousePos, rougeButton) ) {
            DrawRectangle(rougeButton_x, button_y, buttonWidth , buttonHeight, WHITE);
            DrawRectangle(rougeButton_x - 140, button_y + 130 , buttonWidth + 200, buttonHeight + 150, GRAY);

            DrawText(TextFormat("Health: %d", Rogue.GetMaxHealth()), rougeButton_x - 120, button_y + 140, 25, WHITE);
            DrawText(TextFormat("Damage: %d - %d", Rogue.GetDamageMin(), Rogue.GetDamageMax()), rougeButton_x - 120, button_y + 180, 25, WHITE);
            DrawText(TextFormat("Defense: %d", Rogue.GetDefense()), rougeButton_x - 120, button_y + 220, 25, WHITE);
            DrawText(TextFormat("Type: %s ", Rogue.GetType().c_str()), rougeButton_x - 120, button_y + 260, 25, WHITE);

            

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
	DrawText("Rogue",  rougeButton_x- 7, button_y - 30, 25, BLACK);

   DrawTile(knightButton_x - 15, button_y + 30, 6, 0, 10); // knight
   DrawTile(wizardButton_x - 15, button_y + 30, 9, 0, 10); // wizard
   DrawTile(rougeButton_x - 15, button_y + 30, 8, 0, 10); // Rogue
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

void Inventory()
{
   //for sound FX
   const double cooldownDuration = 100.0;
   bool isCurrentlyHovering = false;
   double currentTime = GetTime();

   Vector2 mousePos = GetMousePosition();

   Rectangle outer {20, 20, 760, 560};
   Rectangle inner {40, 40, 720, 520};
   Rectangle header {270, 20, 250, 50};
   Rectangle exitButton {20, 20, 50, 50};
   Rectangle charBorder {530, 60, 220, 500};
   Rectangle health{ 535, 275, 30, 30};
   Rectangle defense{ 650, 280, 30, 30};
   Rectangle damage{ 535, 340, 30, 30};
   Rectangle level {535, 390, 30, 30};
   Rectangle energy {535, 460, 30, 30};

   //items-blahblah
   Rectangle healthPotion{41, 71, 45, 45};
   Rectangle energyFood{91, 71, 45, 45};
   

   DrawRectangleRounded(outer, 0.2, 2, GRAY);
   DrawRectangleRounded(inner, 0.2, 2, LIGHTGRAY);
   DrawRectangleRounded(header, 0.1, 1, BLACK);
   DrawRectangleRounded(exitButton, 0.2, 4, WHITE);

   //Grids - Horizontal
   int distance = 50;
   DrawLine(40, 70, 530, 70, BLACK);
   for(int i = 0; i < 9; i++)
   {
      DrawLine(40, 70 + distance, 530, 70 + distance, BLACK);
      distance += 50;
   }

   //Grids - Vertical
   distance = 50;
   DrawLine(40, 70, 40, 520, BLACK);
   for (int i = 0; i < 9; i++)
   {
      DrawLine(40 + distance, 70, 40 + distance, 520, BLACK);
      distance += 50;
   }

   //Items / Consumable
   DrawTile(41, 71, 7, 8, 5.8f);
   DrawTile(energyFood.x, energyFood.y,10, 8, 5.8f);
   
   //Player Status
   DrawRectangleLinesEx(charBorder, 4, BLACK);

   DrawText("INVENTORY", 300, 25, 30, WHITE); // header
   DrawText("X", 28, 22, 46, BLACK); // exit Buttoon
   
   if(Player.GetName() == Knight.GetName())  DrawTile(560, 80, 6, 0, 20.0f);
   else if(Player.GetName() == Wizard.GetName())  DrawTile(560, 80, 9, 0, 20.0f); 
   else if(Player.GetName() == Rogue.GetName())  DrawTile(560, 80, 8, 0, 20.0f);

   DrawText(TextFormat("Type: %s ", Player.GetType().c_str()), 535, 240, 20, BLACK);

   DrawText(TextFormat("%d", Player.GetHealth()), 580, 290, 25, BLACK );
   DrawTile(535, 280, 6, 6, 5.0f);

   DrawText(TextFormat("%d", Player.GetDefense()), 700, 290, 25, BLACK );
   DrawTile(650, 280, 9, 6, 5.0f);

   DrawText(TextFormat("Avg: %d", (Player.GetDamageMin() + Player.GetDamageMax()) / 2), 580, 340, 25, BLACK );
   DrawTile(535, 330, 6, 4, 5.0f);

   DrawText(TextFormat("Level: %d", Player.GetLevel() ), 580, 390, 25, BLACK );
   DrawTile(535, 390, 8, 5, 5.0f);

   DrawText(TextFormat("Energy: %d", Player.GetEnergy()), 580, 470, 25, BLACK);
   DrawTile(535, 460, 5, 8, 5.0f);
   

   if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& !showItemInfo)
   {
      // X button
      if(CheckCollisionPointRec(mousePos, exitButton))
      {
         isInventory = false;
         if(battleMode) itemButtonIsPressed = false;
      }

      //Items/Consumables
      if(CheckCollisionPointRec(mousePos, healthPotion))
      {
         showItemInfo = true;  
         healthPotionsWasClicked = true;       
      }

      if(CheckCollisionPointRec(mousePos, energyFood))
      {
         showItemInfo = true;  
         energyFoodWasClicked = true;       
      }

   }

   if(CheckCollisionPointRec(mousePos, health) && !showItemInfo)
   {

      DrawRectangle(500, 290, 200, 200, BLACK);
      DrawText(TextFormat("Current health: %d", Player.GetHealth()), 510, 300, 18, WHITE );
      DrawText(TextFormat("Max health: %d", Player.GetMaxHealth()), 510, 320, 18, WHITE );
      DrawText(TextFormat("The amount of hits a \nHero can recieve"), 510, 345, 18, WHITE );
      
      isCurrentlyHovering = true;
      PlaySoundWhenHoveringItem(hoveringOverItems, currentTime, lastHoverSoundTime, cooldownDuration);

   } 
   

   if (CheckCollisionPointRec(mousePos, defense)&& !showItemInfo)
   {
      DrawRectangle(550, 290, 200, 200, BLACK);
      DrawText(TextFormat("%d damage is reduced \nfrom enemy attacks", Player.GetDefense()), 555, 300, 18, WHITE );
      
      isCurrentlyHovering = true;
      PlaySoundWhenHoveringItem(hoveringOverItems, currentTime, lastHoverSoundTime, cooldownDuration);
   }
   else if (CheckCollisionPointRec(mousePos, damage)&& !showItemInfo)
   {
      DrawRectangle(500, 300, 220, 200, BLACK);
      DrawText(TextFormat("Minimun Attack damage: %d", Player.GetDamageMin() ), 510, 310, 15, WHITE );
      DrawText(TextFormat("Maximum Attack damage: %d", Player.GetDamageMax() ), 510, 330, 15, WHITE );
      DrawText(TextFormat("The hero deals %d - %d \namount of damage \ndepending on RNG", Player.GetDamageMin(), Player.GetDamageMax()), 510, 370, 18, WHITE );
      
      isCurrentlyHovering = true;
      PlaySoundWhenHoveringItem(hoveringOverItems, currentTime, lastHoverSoundTime, cooldownDuration);
   }
   else if (CheckCollisionPointRec(mousePos, level)&& !showItemInfo)
   {
      DrawRectangle(500, 360, 220, 200, BLACK);
      DrawText(TextFormat("Experience Points: %d", Player.GetExperience()),  510, 370, 15, WHITE);
      DrawText(TextFormat("Experience Till Level Up:\n   %d / %d ", Player.GetExperience(), levelCap),  510, 390, 15, WHITE);
      
      isCurrentlyHovering = true;
      PlaySoundWhenHoveringItem(hoveringOverItems, currentTime, lastHoverSoundTime, cooldownDuration);
   }
   else if (CheckCollisionPointRec(mousePos, energy)&& !showItemInfo)
   {
      DrawRectangle(500, 360, 220, 200, BLACK);
      DrawText(TextFormat("Energy Points: %d / %d", Player.GetEnergy(), Player.GetMaxEnergy()),  510, 370, 15, WHITE);
      
      isCurrentlyHovering = true;
      PlaySoundWhenHoveringItem(hoveringOverItems, currentTime, lastHoverSoundTime, cooldownDuration);
   }

   //Items Consumables
   else if (CheckCollisionPointRec(mousePos, healthPotion)&& !showItemInfo)
   {
      DrawRectangle(40, 70, 50, 50, {255, 255, 255, 150});
      
      isCurrentlyHovering = true;
      PlaySoundWhenHoveringItem(hoveringOverItems, currentTime, lastHoverSoundTime, cooldownDuration);
      
   }
   else if (CheckCollisionPointRec(mousePos, energyFood)&& !showItemInfo)
   {
      DrawRectangle(energyFood.x-1, energyFood.y-1, 50, 50, {255, 255, 255, 150});
      
      isCurrentlyHovering = true;
      PlaySoundWhenHoveringItem(hoveringOverItems, currentTime, lastHoverSoundTime, cooldownDuration);
      
   }

   if(showItemInfo)
   {
      ShowItemInfos();
   }


   //plays sound fx only once when hovering over an item
   if (!isCurrentlyHovering) 
   {
      hoveringOverItems = false;
   }

            
}

void ShowItemInfos()
{
   Vector2 mousePos = GetMousePosition();

   Rectangle shadowBackground{0,0,screenWidth,screenHeight};
   Rectangle interactItem{250, 300, 300, 50};
   Rectangle itemRectBox {150, 170, 500, 200};
   Rectangle exitItemRectBox{150, 170, 25,25};

   DrawRectangleRec(shadowBackground, {0, 0, 0, 100});
   DrawRectangleRounded(itemRectBox, 0.1, 1, BLACK);
   DrawRectangleRounded(exitItemRectBox, 0.1, 1, WHITE);
   DrawText(" X", exitItemRectBox.x, exitItemRectBox.y, 25, BLACK);

   //identify what item
   if(healthPotionsWasClicked)
   {
      DrawText("Health Potions provides 25-75 points of \nhealth when consumed.",  itemRectBox.x + 30, itemRectBox.y + 30, 17, WHITE);
      DrawText(TextFormat(" X %d", Player.GetRemainingHealthPotions()), itemRectBox.x + 430, itemRectBox.y + 30, 30, WHITE);
      DrawTile(itemRectBox.x + 395, itemRectBox.y + 20, 7, 8, 5.8f);

      DrawRectangleRec(interactItem, DARKGRAY);
      DrawText("Drink Potion", interactItem.x + 40, interactItem.y + 10, 25, WHITE);
   }

   if(energyFoodWasClicked)
   {
      DrawText("Food provides 15-40 points of energy \nwhen consumed.",  itemRectBox.x + 30, itemRectBox.y + 30, 17, WHITE);
      DrawText(TextFormat(" X %d", Player.GetRemainingEnergyFoods()), itemRectBox.x + 430, itemRectBox.y + 30, 30, WHITE);
      DrawTile(itemRectBox.x + 395, itemRectBox.y + 20, 10, 8, 5.8f);

      DrawRectangleRec(interactItem, DARKGRAY);
      DrawText("Consume Meat", interactItem.x + 45, interactItem.y + 10, 25, WHITE);
   }



   if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
   {
      if(CheckCollisionPointRec(mousePos, exitItemRectBox))
      {
         showItemInfo = false;
         healthPotionsWasClicked = false;
         energyFoodWasClicked = false;
      }

      //items or consumables
      if(CheckCollisionPointRec(mousePos, interactItem) && healthPotionsWasClicked) // Health Potion
      {
         if(Player.GetRemainingHealthPotions() <= 0 || Player.GetHealth() == Player.GetMaxHealth()) return;

         int hpAmount = GetRandomValue(25, 75);
         Player.SetHealth(Player.GetHealth() + hpAmount);
         Player.SetHealthPotions(Player.GetRemainingHealthPotions() - 1);
         
         if(Player.GetHealth() > Player.GetMaxHealth())
         {
            Player.SetHealth(Player.GetMaxHealth());
         }
      }

      if(CheckCollisionPointRec(mousePos, interactItem) && energyFoodWasClicked) // energy Food
      {
         if(Player.GetRemainingEnergyFoods() <= 0 || Player.GetEnergy() == Player.GetMaxEnergy()) return;

         int energyAmount = GetRandomValue(15, 45);
         Player.SetEnergy(Player.GetEnergy() + energyAmount);
         Player.SetEnergyFoods(Player.GetRemainingEnergyFoods() - 1);

         if(Player.GetEnergy() > Player.GetMaxEnergy())
         {
            Player.SetEnergy(Player.GetMaxEnergy());
         }
      }

      
   }
}

void LevelUpScreen()
{  
   //Image Positions
   Vector2 StarPos1 = {330, 5};
   Vector2 StarPos2 = {210, 45};
   Vector2 StarPos3 = {490, 45};

   Rectangle LayoutBox {50, 50, 700, 500};
   Rectangle LayoutBoxInner {70, 70, 660, 460};
   Rectangle ExitBox { 300, 480, 200, 50};

   //Colors
   Color layoutColorInner = {97, 62, 25, 255};
   Color layoutColorOuter = {189, 104, 34, 255};
   Color ExitBoxColor = {61, 168, 75, 255};
   Color LevelUpColor = {227, 220, 32, 255};

   Vector2 mousePos = GetMousePosition();

   //Shapes
   ClearBackground({237, 225, 211, 255});
   DrawRectangleRounded(LayoutBox, 0.1, 1, layoutColorOuter);
   DrawRectangleRounded(LayoutBoxInner,0.2, 1, layoutColorInner);
   DrawRectangleRounded(ExitBox, 0.2, 2, ExitBoxColor);


   //Text
   DrawText("Continue", ExitBox.x + 50, ExitBox.y + 15, 25, WHITE);
   DrawText("LEVELED UP!", 290, 190, 40, LevelUpColor );
   DrawText(TextFormat("LEVEL: %d -> %d", Player.GetLevel(), Player.GetLevel() + 1), 100, 250, 35, WHITE);
   DrawText(TextFormat("MINIMUM DAMAGE: %d -> %d", Player.GetDamageMin(), Player.GetDamageMin() + 10), 115, 300, 30, BLACK);
   DrawText(TextFormat("MAXIMUM DAMAGE: %d -> %d", Player.GetDamageMax(), Player.GetDamageMax() + 10), 115, 340, 30, BLACK);
   DrawText(TextFormat("DEFENSE: %d -> %d", Player.GetDefense(), Player.GetDefense() + 1), 115, 380, 30, BLACK);
   DrawText(TextFormat("MAX HEALTH: %d -> %d", Player.GetMaxHealth(), Player.GetMaxHealth() + 50), 115, 420, 30, BLACK);

   //Texture or Image
   DrawTextureEx(textures[TEXTURE_STAR], StarPos1, 0.0f, 0.4f, WHITE);
   DrawTextureEx(textures[TEXTURE_STAR], StarPos2, 0.0f, 0.3f, WHITE);
   DrawTextureEx(textures[TEXTURE_STAR], StarPos3, 0.0f, 0.3f, WHITE);


   //Collisions
   if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
   {
      if(CheckCollisionPointRec(mousePos, ExitBox))
      {
         playerLeveledUp = false;

         for(int i = 0; i < MAX_LIGHT_MUSIC; i++)
        {
            SetMusicVolume(musicLight[i], musicVolume );
            SetMusicVolume(musicDark[i], musicVolume);
            SetMusicVolume(musicAction[i], musicVolume);
        }

         //Upgrade Stats
         if(Player.GetExperience() >= levelCap)
         {
            Player.SetLevel(Player.GetLevel() + 1);
            Player.SetDamageMin(Player.GetDamageMin() + 10);
            Player.SetDamageMax(Player.GetDamageMax() + 10);
            Player.SetDefense(Player.GetDefense() + 1);
            Player.SetMaxHealth(Player.GetMaxHealth() + 50);
            Player.GiveExperience(0);
            levelCap += 100;
         }
         
      }
   }


}


