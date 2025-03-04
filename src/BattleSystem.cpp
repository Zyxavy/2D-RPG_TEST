#include "BattleSystem.hpp"
#include "GameFunctions.hpp"
#include "GameMenu.hpp"
#include "Entities.hpp"
#include "raylib.h"
#include <iostream>

bool battleMode = false;
bool playerTurn = true;
bool playerDefending = false;

void BattleUpdate() {
    Vector2 mousePos = GetMousePosition();
    if(orc.health <= 0) 
    {   
        orc.isAlive = false;
        battleMode = false;
        player.experience += orc.experience;
        PlaySound(sounds[SOUND_DEATH]);

        chest.x = orc.x;
            chest.y = orc.y;
            chest.isAlive = true;
            chest.money = GetRandomValue(23, 205);
    } 
    else if(player.health <= 0)
    {
        player.isAlive = false;
        battleMode = false;
        PlaySound(sounds[SOUND_DEATH]);
        isDead = true;

    
        //Continue
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        //Attack 
        if (CheckCollisionPointRec(mousePos, (Rectangle){120, 500, 150, 40}) && playerTurn) {
            int damage = GetRandomValue(player.damageMin, player.damageMax) - orc.defense;
            if(orc.weakness == player.type) damage *= 2;
            if(damage <= 0) damage = 1;
            orc.health -= damage;
            playerTurn = false;
            playerDefending = false;
            PlaySound(sounds[SOUNDS_ATTACK]);
        }
        //Defend
        else if (CheckCollisionPointRec(mousePos, (Rectangle){320, 500, 150, 40}) && playerTurn) {
            playerDefending = true;
            playerTurn = false;
        }
        //Run
        else if (CheckCollisionPointRec(mousePos, (Rectangle){520, 500, 150, 40}) && playerTurn) {
            if (GetRandomValue(0, 1) == 1) {  
                battleMode = false;
            }
            playerTurn = false;
        }
    }
    if (!playerTurn && orc.health > 0) {
        int orcDamage = GetRandomValue(orc.damageMin, orc.damageMax) -  player.defense;
        if (playerDefending) orcDamage /= 2;
        if(orcDamage <= 0) orcDamage = 1;
        player.health -= orcDamage;
        playerTurn = true;
    } 
}

void BattleRender() {
    DrawRectangle(0, 0, screenWidth, screenHeight, DARKGRAY);
    DrawText("BATTLE!", 350, 30, 20, WHITE);

    Rectangle rec {40, 50, (screenWidth - 40) - 40, (screenHeight-50) - 150};
    DrawRectangleLinesEx(rec, 4.5, BLACK);


    if(player.name == Knight.name)  DrawTile(200, 350, 6, 0, 10.0f);
    else if(player.name == Wizard.name)  DrawTile(200, 350, 9, 0, 10.0f); 
    else if(player.name == Rouge.name)  DrawTile(200, 350, 8, 0, 10.0f); 
    
    DrawTile(500, 350, 11, 0, 10.0f);  //Orc

    DrawText(TextFormat("Orc HP: %d", orc.health), 480, 330, 20, RED);
    DrawText(TextFormat("%s HP: %d", player.name.c_str(), player.health), 180, 330, 20, GREEN);

    //Draw Buttons 
    DrawRectangle(20, 470, 760, 300, BLACK);
    DrawRectangle(120, 500, 150, 40, LIGHTGRAY);
    DrawRectangle(320, 500, 150, 40, LIGHTGRAY);
    DrawRectangle(520, 500, 150, 40, LIGHTGRAY);

    DrawText("ATTACK", 150, 510, 20, BLACK);
    DrawText("DEFEND", 350, 510, 20, BLACK);
    DrawText("RUN", 570, 510, 20, BLACK);
}