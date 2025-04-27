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
bool actionButtonIsPressed = false;
bool itemButtonIsPressed = false;
bool skillButtonIsPressed = false;
bool attackButtonIsPressed = false;


//main rects
Rectangle battleScreen = {48, 56, 712, 288};
Rectangle actionButton = {48, 360, 136, 64};
Rectangle skillButton = {232, 360, 136, 64};
Rectangle itemsButton = {424, 360, 136, 64};
Rectangle runButton = {616, 360, 136, 64};
Rectangle actionButtonMore = {24, 352, 360, 224};
Rectangle skillOrItemsButtonMore = {112, 360, 592, 216};
Rectangle textBoxPlayer = {104, 64, 200, 72};
Rectangle textBoxEnemy = {520, 64, 200, 72};

//Action Button Rects
Rectangle actionBackButton = {actionButtonMore.x + 216, actionButtonMore.y + 120, 120, 36};
Rectangle actionAttackButton = {actionButtonMore.x +24, actionButtonMore.y + 72, 160, 64};
Rectangle actionDefendButton = {actionButtonMore.x +24, actionButtonMore.y + 152, 160, 56};

//colors
Color buttonColor = {36, 38, 36, 255};


void BattleUpdate(Enemy *enemy) {

    playerTurn = true;
    Vector2 mousePos = GetMousePosition();
    Player.SetZone(ZONE_BATTLE);

    if (enemy->GetHealth() <= 0)  
    {
        enemy->SetAlive(false); 
        PlaySound(sounds[SOUND_DEATH]);

        Player.GiveExperience(Player.GetExperience() + GetRandomValue(5, enemy->GetExperience()));
        Player.SetZone(enemy->GetZone());
        Player.SetX(enemy->GetX() + TILE_WIDTH);
        
        PlayerLevelUp();
        //spawn chest
        chest.x = enemy->GetX();
        chest.y = enemy->GetY();
        chest.isAlive = true;
        chest.money = GetRandomValue(23, 205);
        chest.healthPotions = GetRandomValue(1,4);

        battleMode = false;
        return;

    } 
    else if(Player.GetHealth() <= 0) // player dies
    {
        Player.SetAlive(false);
        battleMode = false;
        PlaySound(sounds[SOUND_DEATH]);
        isDead = true;
        Player.SetZone(enemy->GetZone());

    
        //Continue
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        //Action 
        if (CheckCollisionPointRec(mousePos, actionButton) && playerTurn) {
            actionButtonIsPressed = true;
            PlaySound(sounds[SOUND_HOVER_ITEMS]);
        
        }

        //Run
        else if (CheckCollisionPointRec(mousePos, runButton) && playerTurn) {
            if (GetRandomValue(0, 1) == 1) {  
                PlaySound(sounds[SOUND_HOVER_ITEMS]);
                battleMode = false;
                
                //stun enemies
                enemy->SetStunStatus(true);

                Player.SetX(enemy->GetX() + (TILE_WIDTH * 2));
                Player.SetZone(enemy->GetZone());
                return;
                
                
            }
            playerTurn = false;
        }
    }
    
    if(actionButtonIsPressed)
    {
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(CheckCollisionPointRec(mousePos, actionAttackButton)) // attack
            {
                attackButtonIsPressed = true;
                PlayerAttacks(enemy);
            }
            else if(CheckCollisionPointRec(mousePos, actionDefendButton)) //defend
            {
                PlaySound(sounds[SOUND_HOVER_ITEMS]);
                playerDefending = true;
                playerTurn = false;
            }
            else if(CheckCollisionPointRec(mousePos, actionBackButton)) // back
            {
                actionButtonIsPressed = false;
                PlaySound(sounds[SOUND_HOVER_ITEMS]);
            }
        }
    }

    if (!playerTurn && enemy->GetHealth() > 0 ) 
    {
        //enemy attacks
        EnemyAttacks(enemy);
    } 
}

void BattleRender(Enemy *enemy) {

    //player tile placement = {160, 184, 96, 88}
    //enemy tile placement = {576, 192, 112, 80}


    //Draw
    ClearBackground(DARKGRAY);
    DrawRectangleRec(battleScreen, BLACK);
    DrawRectangleRounded(actionButton, 0.2f, 1, buttonColor);
    DrawRectangleRounded(skillButton, 0.2f, 1, buttonColor);
    DrawRectangleRounded(itemsButton, 0.2f, 1, buttonColor);
    DrawRectangleRounded(runButton, 0.2f, 1, buttonColor);

    //tiles
    DrawTile(actionButton.x + 39, actionButton.y + 8, 6, 4, 7.0f);
    DrawTile(skillButton.x + 39, skillButton.y + 8, 9, 8, 7.0f);
    DrawTile(itemsButton.x + 39, itemsButton.y + 8, 8, 8, 7.0f);
    DrawTile(runButton.x + 39, runButton.y + 8, 3, 7, 7.0f);

    //Player tile
    if(Player.GetName() == Knight.GetName())  DrawTile(160, 192, 6, 0, 10.0f);
    else if(Player.GetName() == Wizard.GetName())  DrawTile(160, 192, 9, 0, 10.0f); 
    else if(Player.GetName() == Rouge.GetName())  DrawTile(160, 192, 8, 0, 10.0f); 

    //enemy Tile
    if(enemy->GetName() == "Orc") DrawTile(576, 192, 11, 0, 10.0f);
    else if(enemy->GetName() == "Wandering Eye") DrawTile(576, 192, 13, 0, 10.0f);

    if(actionButtonIsPressed)
    {
        DrawRectangleRec(actionButtonMore, BLACK);
        DrawRectangleRounded(actionAttackButton, 0.2f, 1, buttonColor);
        DrawRectangleRounded(actionDefendButton, 0.2f, 1, buttonColor);
        DrawRectangleRounded(actionBackButton, 0.2f, 1, buttonColor);

        DrawText("BACK", actionBackButton.x + 10, actionBackButton.y + 10, 15 ,WHITE);
        DrawText("ATTACK", actionAttackButton.x + 50, actionAttackButton.y + 15, 15 ,WHITE);
        DrawText("DEFEND", actionDefendButton.x + 50, actionDefendButton.y + 15, 15 ,WHITE);
    }

}

void RenderBackground()
{

}

void PlayerAttacks(Enemy *enemy)
{
    int damage = GetRandomValue(Player.GetDamageMin(), Player.GetDamageMax()) - enemy->GetDefense();  
    if (enemy->GetWeakness() == Player.GetType()) damage *= 2;  
    if(damage <= 0) damage = 1;
    enemy->TakeDamage(damage); 
    std::cout << "Player attacked! Damage dealt: " << damage << std::endl;

    playerTurn = false;
    playerDefending = false;
    PlaySound(sounds[SOUNDS_ATTACK]);
}

void EnemyAttacks(Enemy *enemy)
{   
    int dmg;
    int enemyDamage = GetRandomValue(enemy->GetDamageMin(), enemy->GetDamageMax()) -  Player.GetDefense();

    if (playerDefending) 
    {
        int act = GetRandomValue(0,3);

        switch (act)
        {
        case 0:
            enemyDamage =  0;
            std::cout << "Completely Blocked off the attack\n"; 
            return;
        case 1:
            enemyDamage /= 2;
            std::cout << "Blocked off some damage!\n";
            break;
        case 2:
            dmg = Player.GetDamageMin() / 2;
            enemyDamage = 0;
            enemy->TakeDamage(dmg);
            std::cout << "Attack Parried!\n";
            std::cout << "Player Dealt " << dmg << " Damage!\n";
            return;
        case 3:
            std::cout << "Blocked Failed!\n";
            break;
        }
    }

    if(enemyDamage <= 0) enemyDamage = 1;
    Player.SetHealth( Player.GetHealth() - enemyDamage);
    playerTurn = true;
}


