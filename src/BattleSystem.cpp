#include "BattleSystem.hpp"
#include "GameFunctions.hpp"
#include "GameMenu.hpp"
#include "Entities.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include "raylib.h"
#include <iostream>

bool battleMode = false;
bool playerTurn = true;
bool playerDefending = false;

void BattleUpdate(Enemy &enemy) {

    Vector2 mousePos = GetMousePosition();
    Player.SetZone(ZONE_BATTLE);

    if (enemy.GetHealth() <= 0)  
    {
        enemy.SetAlive(false); 
        battleMode = false;
        Player.GiveExperience(enemy.GetExperience());
        PlaySound(sounds[SOUND_DEATH]);

        Player.SetZone(enemy.GetZone());

        Player.SetX(enemy.GetX() + TILE_WIDTH);
        
        if (enemy.GetName() == "Orc") {
            orc.SetAlive(false);
        } else if (enemy.GetName() == "Wandering Eye") {
            wanderingEye.SetAlive(false);
        }

        
        PlayerLevelUp();
        //spawn chest
        chest.x = enemy.GetX();
        chest.y = enemy.GetY();
        chest.isAlive = true;
        chest.money = GetRandomValue(23, 205);
        return;

    } 
    else if(Player.GetHealth() <= 0) // player dies
    {
        Player.SetAlive(false);
        battleMode = false;
        PlaySound(sounds[SOUND_DEATH]);
        isDead = true;
        Player.SetZone(enemy.GetZone());

    
        //Continue
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        //Attack 
        if (CheckCollisionPointRec(mousePos, (Rectangle){120, 500, 150, 40}) && playerTurn) {
        
            int damage = GetRandomValue(Player.GetDamageMin(), Player.GetDamageMax()) - enemy.GetDefense();  
            if (enemy.GetWeakness() == Player.GetType()) damage *= 2;  
            if(damage <= 0) damage = 1;
            enemy.TakeDamage(damage); 
            std::cout << "Player attacked! Damage dealt: " << damage << std::endl;
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
                
                //stun enemies
                if(enemy.GetName() == wanderingEye.GetName()) wanderingEye.SetStunStatus(true);
                else if(enemy.GetName() == orc.GetName())  orc.SetStunStatus(true);

                Player.SetX(enemy.GetX() + (TILE_WIDTH * 2));
                Player.SetZone(enemy.GetZone());
                return;
                
                
            }
            playerTurn = false;
        }
    }
    if (!playerTurn && enemy.GetHealth() > 0 ) {
        //enemy attacks
        int enemyDamage = GetRandomValue(enemy.GetDamageMin(), enemy.GetDamageMax()) -  Player.GetDefense();
        if (playerDefending) enemyDamage /= 2;
        if(enemyDamage <= 0) enemyDamage = 1;
        Player.SetHealth( Player.GetHealth() - enemyDamage);
        playerTurn = true;
    } 
}

void BattleRender(Enemy &enemy) {

    DrawRectangle(0, 0, screenWidth, screenHeight, DARKGRAY);
    DrawText("BATTLE!", 350, 30, 20, WHITE);

    Rectangle rec {40, 50, (screenWidth - 40) - 40, (screenHeight-50) - 150};
    DrawRectangleLinesEx(rec, 4.5, BLACK);

    //Player
    if(Player.GetName() == Knight.GetName())  DrawTile(200, 350, 6, 0, 10.0f);
    else if(Player.GetName() == Wizard.GetName())  DrawTile(200, 350, 9, 0, 10.0f); 
    else if(Player.GetName() == Rouge.GetName())  DrawTile(200, 350, 8, 0, 10.0f); 
    
    //Enemy
    
    if(enemy.GetName() == "Orc") DrawTile(500, 350, 11, 0, 10.0f);
    else if(enemy.GetName() == "Wandering Eye") DrawTile(500, 350, 13, 0, 10.0f);

    DrawText(TextFormat("%s HP: %d", enemy.GetName().c_str(), enemy.GetHealth()), 480, 330, 20, RED);
    DrawText(TextFormat("%s HP: %d", Player.GetName().c_str(), Player.GetHealth()), 180, 330, 20, GREEN);

    //Draw Buttons 
    DrawRectangle(20, 470, 760, 300, BLACK);
    DrawRectangle(120, 500, 150, 40, LIGHTGRAY);
    DrawRectangle(320, 500, 150, 40, LIGHTGRAY);
    DrawRectangle(520, 500, 150, 40, LIGHTGRAY);

    //draw Text
    DrawText("ATTACK", 150, 510, 20, BLACK);
    DrawText("DEFEND", 350, 510, 20, BLACK);
    DrawText("RUN", 570, 510, 20, BLACK);
}