#ifndef GAME_MENU_HPP
#define GAME_MENU_HPP

#include <raylib.h>
#include <raymath.h>

//bools
extern bool options;

extern bool inMenu;
extern bool isDead;
extern bool inCharacterSelect;

//buttons
extern float buttonWidth, buttonHeight;
extern float button_x;
extern float startButton_y;
extern float optionsButton_y;
extern float exitButton_y;

void GameMenu();
void DeathMenu();
void CharacterSelect();

#endif