#ifndef GAME_MENU_HPP
#define GAME_MENU_HPP

#include <raylib.h>
#include <raymath.h>

//bools
extern bool inOptions;
extern bool inMenu;
extern bool isDead;
extern bool inCharacterSelect;
extern bool inTutorial;
extern int itemID;
extern bool inShop;


//buttons
extern float buttonWidth, buttonHeight;
extern float button_x;
extern float startButton_y;
extern float optionsButton_y;
extern float exitButton_y;
extern float tutorialButton_y;

//functionjs
void GameMenu();
void DeathMenu();
void CharacterSelect();
void OptionsMenu();
void Inventory();
void ShowItemInfos();
void LevelUpScreen();
void Tutorial();
void islanderShop();


#endif