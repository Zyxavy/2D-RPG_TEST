#ifndef GAME_MENU_HPP
#define GAME_MENU_HPP

#include <raylib.h>
#include <raymath.h>

//bools
extern bool options;
extern bool start_game;

extern bool inMenu;

//buttons
extern float button_width, button_height;
extern float button_x;
extern float start_button_y;
extern float options_button_y;
extern float exit_button_y;

void GameMenu();

#endif