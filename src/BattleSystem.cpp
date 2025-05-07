#include "BattleSystem.hpp"
#include "GameFunctions.hpp"
#include "GameMenu.hpp"
#include "Entities.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include "raylib.h"
#include <iostream>

Vector2 playerOriginalPos = {160, 192}; //Original pos of player 
Vector2 enemyOriginalPos = {576, 192};  //Original pos of enemy 
Vector2 playerCurrentPos = playerOriginalPos;
Vector2 enemyCurrentPos = enemyOriginalPos;

//animation states
bool playerAnimating = false;
bool enemyAnimating = false;
bool showDamage = false;
bool showText = false;
int damageToShow = 0;
int textToShow = 0;
Vector2 damagePosition = {0, 0};
Vector2 textPosition = {0,0};
float animationTimer = 0;
float damageDisplayTime = 0;
float textDisplayTime = 0;
const float ANIMATION_SPEED = 5.0f;
const float ANIMATION_DURATION = 0.5f;
const float DAMAGE_DISPLAY_DURATION = 1.0f;

//bools
bool battleMode = false;
bool playerTurn = true;
bool playerDefending = false;
bool actionButtonIsPressed = false;
bool itemButtonIsPressed = false;
bool skillButtonIsPressed = false;
bool attackButtonIsPressed = false;
bool aTabIsOpen = false;

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
Rectangle playerHealthBox = { playerOriginalPos.x - 100, playerOriginalPos.y + 100, 250, 40};
Rectangle enemyHealthBox = { enemyOriginalPos.x - 90, enemyOriginalPos.y + 100, 250, 40};

//Action Button Rects
Rectangle actionBackButton = {actionButtonMore.x + 216, actionButtonMore.y + 120, 120, 36};
Rectangle actionAttackButton = {actionButtonMore.x +24, actionButtonMore.y + 72, 160, 64};
Rectangle actionDefendButton = {actionButtonMore.x +24, actionButtonMore.y + 152, 160, 56};

//Skills Button Rects
Rectangle skillsBackButton = {skillOrItemsButtonMore.x + 10, skillOrItemsButtonMore.y + 5, 120, 40};
Rectangle skills1 = {skillOrItemsButtonMore.x + 10, skillOrItemsButtonMore.y + 65, 160, 60};
Rectangle skills2 = {skillOrItemsButtonMore.x + 190, skillOrItemsButtonMore.y + 65, 160, 60};
Rectangle skills3 = {skillOrItemsButtonMore.x + 380, skillOrItemsButtonMore.y + 65, 160, 60};

//colors
Color buttonColor = {36, 38, 36, 255};


void BattleUpdate(Enemy *enemy)
{
    Vector2 mousePos = GetMousePosition();
    Player.SetZone(ZONE_BATTLE);

    //Update animations
    UpdateBattleAnimations(GetFrameTime(), enemy);

    if (enemy->GetHealth() <= 0)  
    {
        enemy->SetAlive(false); 
        PlaySound(sounds[SOUND_DEATH]);

        Player.GiveExperience(Player.GetExperience() + GetRandomValue(5, enemy->GetExperience()));
        Player.SetZone(enemy->GetZone());
        Player.SetX(enemy->GetX() + TILE_WIDTH);
        
        PlayerLevelUp();
        battleMode = false;
        playerTurn = true;
        playerDefending = false;
        actionButtonIsPressed = false;
        itemButtonIsPressed = false;
        skillButtonIsPressed = false;
        attackButtonIsPressed = false;
        playerAnimating = false;
        enemyAnimating = false;
        showDamage = false;
        showText = false;
        playerCurrentPos = playerOriginalPos;
        enemyCurrentPos = enemyOriginalPos;

        //spawn chest
        chest.x = enemy->GetX();
        chest.y = enemy->GetY();
        chest.isAlive = true;
        chest.money = GetRandomValue(23, 205);
        chest.healthPotions = GetRandomValue(1,4);

        return;
    } 
    else if(Player.GetHealth() <= 0) // player dies
    {
        Player.SetAlive(false);
        battleMode = false;
        playerTurn = true;
        playerDefending = false;
        actionButtonIsPressed = false;
        itemButtonIsPressed = false;
        skillButtonIsPressed = false;
        attackButtonIsPressed = false;
        playerAnimating = false;
        enemyAnimating = false;
        showDamage = false;
        showText = false;
        playerCurrentPos = playerOriginalPos;
        enemyCurrentPos = enemyOriginalPos;

        PlaySound(sounds[SOUND_DEATH]);
        isDead = true;
        Player.SetZone(enemy->GetZone());
    }

    if (!playerAnimating && !enemyAnimating) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            //Action 
            if (CheckCollisionPointRec(mousePos, actionButton) && playerTurn && !aTabIsOpen) 
            {
                actionButtonIsPressed = true;
                aTabIsOpen = true;
                PlaySound(sounds[SOUND_HOVER_ITEMS]);
            }
            //skill
            else if(CheckCollisionPointRec(mousePos, skillButton) && playerTurn && !aTabIsOpen)
            {
                skillButtonIsPressed = true;
                aTabIsOpen = true;
                PlaySound(sounds[SOUND_HOVER_ITEMS]);
            }
            //Items
            else if(CheckCollisionPointRec(mousePos, itemsButton) && playerTurn && !aTabIsOpen)
            {
                itemButtonIsPressed = true;
                //aTabIsOpen = true;
                PlaySound(sounds[SOUND_HOVER_ITEMS]);
                playerTurn = false;
            }
            //Run
            else if (CheckCollisionPointRec(mousePos, runButton) && playerTurn && !aTabIsOpen) 
            {
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
    
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(actionButtonIsPressed)
            {
                if(CheckCollisionPointRec(mousePos, actionAttackButton)) // attack
                {
                    attackButtonIsPressed = true;
                    playerAnimating = true;
                    animationTimer = 0;
                    showDamage = false;
                    actionButtonIsPressed = false;  
                    aTabIsOpen = false;
                    PlaySound(sounds[SOUND_HOVER_ITEMS]);

                }
                else if(CheckCollisionPointRec(mousePos, actionDefendButton)) //defend
                {
                    playerDefending = true;
                    showText = false;
                    playerTurn = false; 
                    actionButtonIsPressed = false; 
                    aTabIsOpen = false; 
                    PlaySound(sounds[SOUND_HOVER_ITEMS]);
                }
                else if(CheckCollisionPointRec(mousePos, actionBackButton)) // back
                {
                    actionButtonIsPressed = false;
                    aTabIsOpen = false;
                    PlaySound(sounds[SOUND_HOVER_ITEMS]);
                }
            }

            if(skillButtonIsPressed)
            {
                if(CheckCollisionPointRec(mousePos, skillsBackButton))
                {
                    skillButtonIsPressed = false;
                    aTabIsOpen = false;
                    PlaySound(sounds[SOUND_HOVER_ITEMS]);
                }
                else if(CheckCollisionPointRec(mousePos, skills1))
                {
                    PlaySound(sounds[SOUND_HOVER_ITEMS]);
                }
                else if(CheckCollisionPointRec(mousePos, skills2))
                {
                    PlaySound(sounds[SOUND_HOVER_ITEMS]);
                }
                else if(CheckCollisionPointRec(mousePos, skills3))
                {
                    PlaySound(sounds[SOUND_HOVER_ITEMS]);
                }
            }
        }
    

        if (!playerTurn && enemy->GetHealth() > 0 && !enemyAnimating) 
        {
            //enemy attacks
            enemyAnimating = true;
            animationTimer = 0;
            showDamage = false;
            showText = false;
        }
    }
}

void BattleRender(Enemy *enemy) 
{
    //layout
    ClearBackground(DARKGRAY);
    DrawRectangleRec(battleScreen, {34,35,35,255});
    RenderBackground(enemy);
    DrawRectangleRounded(actionButton, 0.2f, 1, buttonColor);
    DrawRectangleRounded(skillButton, 0.2f, 1, buttonColor);
    DrawRectangleRounded(itemsButton, 0.2f, 1, buttonColor);
    DrawRectangleRounded(runButton, 0.2f, 1, buttonColor);

    //tiles
    DrawTile(actionButton.x + 39, actionButton.y + 8, 6, 4, 7.0f);
    DrawTile(skillButton.x + 39, skillButton.y + 8, 8, 8, 7.0f);
    DrawTile(itemsButton.x + 39, itemsButton.y + 8, 7, 8, 7.0f);
    DrawTile(runButton.x + 39, runButton.y + 8, 3, 7, 7.0f);

    //Player tile
    if(Player.GetName() == Knight.GetName())  DrawTile(playerCurrentPos.x, playerCurrentPos.y, 6, 0, 10.0f);
    else if(Player.GetName() == Wizard.GetName())  DrawTile(playerCurrentPos.x, playerCurrentPos.y, 9, 0, 10.0f); 
    else if(Player.GetName() == Rouge.GetName())  DrawTile(playerCurrentPos.x, playerCurrentPos.y, 8, 0, 10.0f); 

    //enemy Tile
    if(enemy->GetName() == "Orc") DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 11, 0, 10.0f);
    else if(enemy->GetName() == "Wandering Eye") DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 13, 0, 10.0f);

    //health
    DrawRectangleRounded(playerHealthBox, 0.1, 1, BLACK);
    DrawRectangleRounded(enemyHealthBox, 0.1, 1, BLACK);
    //player HP
    DrawText(TextFormat("Health: %d", Player.GetHealth()), playerHealthBox.x + 5, playerHealthBox.y + 10, 25, WHITE);
    RenderPlayerHearts();
    //enemy HP
    DrawText(TextFormat("Health: %d", enemy->GetHealth()), enemyHealthBox.x +5, enemyHealthBox.y + 10, 25, WHITE);
    RenderEnemyHearts(enemy);

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

    if(skillButtonIsPressed)
    {

        DrawRectangleRec(skillOrItemsButtonMore, BLACK);
        DrawRectangleRounded(skillsBackButton, 0.1f, 1, buttonColor);
        DrawRectangleRounded(skills1, 0.1f, 3, buttonColor);
        DrawRectangleRounded(skills2, 0.1f, 3, buttonColor);
        DrawRectangleRounded(skills3, 0.1f, 3, buttonColor);



        if(Player.GetName() == Knight.GetName())  KnightSkill();
        else if(Player.GetName() == Wizard.GetName())  WizardSkill(); 
        else if(Player.GetName() == Rouge.GetName())  RougeSkill(); 
    }

    if(itemButtonIsPressed)
    {
        Inventory();
    }

    //Display damage numbers 
    if (showDamage) 
    {
        float yOffset = -10.0f * (damageDisplayTime / DAMAGE_DISPLAY_DURATION);
        char damageText[20];
        sprintf(damageText, "%d", damageToShow);
        
        Color textColor = damageToShow > 0 ? RED : GREEN;
        DrawText(damageText, damagePosition.x, damagePosition.y + yOffset, 24, textColor);
    }
    //display Text
    if (playerDefending)
    {
        DrawText("DEFENDING", playerCurrentPos.x - 20, playerCurrentPos.y - 50, 20, GRAY);
    }
    if (showText) 
    {
        float yOffset = -10.0f * (damageDisplayTime / DAMAGE_DISPLAY_DURATION);
        
        Color textColor = WHITE;
        switch (textToShow)
        {
        case 1:
            textColor = YELLOW;
            DrawText("Attack Blocked", textPosition.x, textPosition.y + yOffset, 24, textColor);
            break;
        
        case 2:
            DrawText("Attack Partially Blocked", textPosition.x, textPosition.y + yOffset, 24, textColor);
            break;
        case 3:
            textColor = YELLOW;
            DrawText("Countered!", textPosition.x, textPosition.y + yOffset, 24, textColor);
            break;
        case 4:
            textColor = RED;
            DrawText("Failed to Block", textPosition.x, textPosition.y + yOffset, 24, textColor);
            break;  
        }
    }
}

void RenderBackground(Enemy *enemy) 
{
  
}

void UpdateBattleAnimations(float frameTime, Enemy *enemy) 
{
    //Player attack animation
    if (playerAnimating) 
    {
        animationTimer += frameTime;
        
        if (animationTimer < ANIMATION_DURATION)
        {
            //move toward enemy
            float progress = animationTimer / ANIMATION_DURATION;
            playerCurrentPos.x = playerOriginalPos.x + (enemyOriginalPos.x - playerOriginalPos.x - 112) * progress;
        } 
        else if (animationTimer < ANIMATION_DURATION * 2) 
        {
            //play attack sound and show damage
            if (!showDamage) 
            { 
                PlaySound(sounds[SOUNDS_ATTACK]);
                PlayerAttacks(enemy);
            }
            
            //back to original pos
            float progress = (animationTimer - ANIMATION_DURATION) / ANIMATION_DURATION;
            playerCurrentPos.x = enemyOriginalPos.x - 112 + (playerOriginalPos.x - (enemyOriginalPos.x - 112)) * progress;
        } 
        else 
        {
            //complete
            playerCurrentPos = playerOriginalPos;
            playerAnimating = false;
            playerTurn = false;
            attackButtonIsPressed = false;
            actionButtonIsPressed = false;
        }
    }
    
    //enemy attack animation
    if (enemyAnimating) 
    {
        animationTimer += frameTime;
        
        if (animationTimer < ANIMATION_DURATION) 
        {
            //move to player
            float progress = animationTimer / ANIMATION_DURATION;
            enemyCurrentPos.x = enemyOriginalPos.x - (enemyOriginalPos.x - playerOriginalPos.x - 96) * progress;
        } 
        else if (animationTimer < ANIMATION_DURATION * 2) 
        {
            if (!showDamage) 
            {
                PlaySound(sounds[SOUNDS_ATTACK]);
                bool wasDefending = playerDefending;
                EnemyAttacks(enemy);
                playerDefending = wasDefending;
            }
            
            //back to original pos
            float progress = (animationTimer - ANIMATION_DURATION) / ANIMATION_DURATION;
            enemyCurrentPos.x = playerOriginalPos.x + 96 + (enemyOriginalPos.x - (playerOriginalPos.x + 96)) * progress;
        } 
        else 
        {
            enemyCurrentPos = enemyOriginalPos;
            enemyAnimating = false;
            playerTurn = true;
            playerDefending = false;
        }
    }
    
    //update damage display timer
    if (showDamage) 
    {
        damageDisplayTime += frameTime;
        if (damageDisplayTime >= DAMAGE_DISPLAY_DURATION) 
        {
            showDamage = false;
        }
    }

    if (showText) 
    {
        textDisplayTime += frameTime;
        if (textDisplayTime >= DAMAGE_DISPLAY_DURATION) 
        {
            showText = false;
        }
    }
}

void PlayerAttacks(Enemy *enemy)
{
    showDamage = true;
    damageToShow = GetRandomValue(Player.GetDamageMin(), Player.GetDamageMax()) - enemy->GetDefense();
    if (enemy->GetWeakness() == Player.GetType()) damageToShow *= 2;
    if (damageToShow <= 0) damageToShow = 1;
    enemy->TakeDamage(damageToShow);
    damagePosition = (Vector2){enemyCurrentPos.x + 50, enemyCurrentPos.y - 30};
    damageDisplayTime = 0;
}

void EnemyAttacks(Enemy *enemy)
{
    showDamage = true;
    
    int enemyDamage = GetRandomValue(enemy->GetDamageMin(), enemy->GetDamageMax()) - Player.GetDefense();
    
    if (playerDefending) 
    {
        showText = true;
        int act = GetRandomValue(0, 3);
        switch (act) 
        {
            case 0:
                enemyDamage = 0; // Completely blocked
                textToShow = 1;
                break;
            case 1:
                enemyDamage /= 2; // Partial block
                if (enemyDamage <= 0) enemyDamage = 3;
                textToShow = 2;
                break;
            case 2:
                // Parry 
                damageToShow = Player.GetDamageMin() / 2;
                if (damageToShow <= 0) damageToShow = 1;
                enemy->TakeDamage(damageToShow);
                damagePosition = (Vector2){playerCurrentPos.x + 50, playerCurrentPos.y - 70};
                enemyDamage = damageToShow;
                textToShow = 3;
                break;

            case 3:
                // Block failed 
                textToShow = 4;
                break;
        }
    }
    else
    {
        textToShow = 0;
        showText = false;
    }
    
    if (enemyDamage <= 0) enemyDamage = 0;
    else Player.SetHealth(Player.GetHealth() - enemyDamage);
    
    damageToShow = enemyDamage;
    damagePosition = (Vector2){playerCurrentPos.x + 50, playerCurrentPos.y - 30};
    damageDisplayTime = 0;

    textPosition = (Vector2) {playerCurrentPos.x + 30, playerCurrentPos.y - 70};
    textDisplayTime = 0;
}

void RenderPlayerHearts()
{
    if(Player.GetHealth() <= 20)
    {
        DrawTile(playerHealthBox.x + 150, playerHealthBox.y +8, 5, 6, 3.5f );
        DrawTile(playerHealthBox.x + 180, playerHealthBox.y +8, 4, 6, 3.5f );
        DrawTile(playerHealthBox.x + 210, playerHealthBox.y +8, 4, 6, 3.5f );
    }
    else if(Player.GetHealth() <= Player.GetMaxHealth() / 2)
    {
        DrawTile(playerHealthBox.x + 150, playerHealthBox.y +8, 6, 6, 3.5f );
        DrawTile(playerHealthBox.x + 180, playerHealthBox.y +8, 5, 6, 3.5f );
        DrawTile(playerHealthBox.x + 210, playerHealthBox.y +8, 4, 6, 3.5f );
    }
    else if(Player.GetHealth() < Player.GetMaxHealth())
    {
        
        DrawTile(playerHealthBox.x + 150, playerHealthBox.y +8, 6, 6, 3.5f );
        DrawTile(playerHealthBox.x + 180, playerHealthBox.y +8, 6, 6, 3.5f );
        DrawTile(playerHealthBox.x + 210, playerHealthBox.y +8, 5, 6, 3.5f );
    }
    else if(Player.GetHealth() == Player.GetMaxHealth()) 
    {
        DrawTile(playerHealthBox.x + 150, playerHealthBox.y +8, 6, 6, 3.5f );
        DrawTile(playerHealthBox.x + 180, playerHealthBox.y +8, 6, 6, 3.5f );
        DrawTile(playerHealthBox.x + 210, playerHealthBox.y +8, 6, 6, 3.5f );
    }
}

void RenderEnemyHearts(Enemy *enemy)
{
    if(enemy->GetHealth() <= 20)
    {
        DrawTile(enemyHealthBox.x + 150, enemyHealthBox.y +8, 5, 6, 3.5f );
        DrawTile(enemyHealthBox.x + 180, enemyHealthBox.y +8, 4, 6, 3.5f );
        DrawTile(enemyHealthBox.x + 210, enemyHealthBox.y +8, 4, 6, 3.5f );
    }
    else if(enemy->GetHealth() <= enemy->GetMaxHealth() / 2)
    {
        DrawTile(enemyHealthBox.x + 150, enemyHealthBox.y +8, 6, 6, 3.5f );
        DrawTile(enemyHealthBox.x + 180, enemyHealthBox.y +8, 5, 6, 3.5f );
        DrawTile(enemyHealthBox.x + 210, enemyHealthBox.y +8, 4, 6, 3.5f );
    }
    else if(enemy->GetHealth() < enemy->GetMaxHealth())
    {
        
        DrawTile(enemyHealthBox.x + 150, enemyHealthBox.y +8, 6, 6, 3.5f );
        DrawTile(enemyHealthBox.x + 180, enemyHealthBox.y +8, 6, 6, 3.5f );
        DrawTile(enemyHealthBox.x + 210, enemyHealthBox.y +8, 5, 6, 3.5f );
    }
    else if(enemy->GetHealth() == enemy->GetMaxHealth()) 
    {
        DrawTile(enemyHealthBox.x + 150, enemyHealthBox.y +8, 6, 6, 3.5f );
        DrawTile(enemyHealthBox.x + 180, enemyHealthBox.y +8, 6, 6, 3.5f );
        DrawTile(enemyHealthBox.x + 210, enemyHealthBox.y +8, 6, 6, 3.5f );
    }
}

void KnightSkill()
{
    
}

void WizardSkill()
{

}

void RougeSkill()
{

}

