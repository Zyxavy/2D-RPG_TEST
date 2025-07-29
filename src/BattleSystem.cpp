#include "BattleSystem.hpp"
#include "GameFunctions.hpp"
#include "GameMenu.hpp"
#include "Entities.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include "raylib.h"
#include "StoryLine.hpp"
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
bool showEnemyStatus =false;
bool showPlayerStatus = false;
int damageToShow = 0;
int textToShow = 0;
int enemyStatusToShow = 0;
int playerStatusToShow = 0;
Vector2 damagePosition = {0, 0};
Vector2 textPosition = {0,0};
Vector2 enemyStatusTextPosition = {0,0};
Vector2 playerStatusTextPosition = {0,0};
float animationTimer = 0;
float damageDisplayTime = 0;
float textDisplayTime = 0;
float enemyStatusDisplayTime = 0;
float playerStatusDisplayTime = 0;
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

//skills
int damageBuff = 0;
int defenseBuff = 0;
int damageBuffCounter = 0;
int defenseBuffCounter = 0;
int enemyOnFire = 0;
int enemyIsShocked = 0;
int enemyIsFrozen = 0;
int enemyIsPoisoned = 0;
bool skill1WasUsed = false;
bool skill2WasUsed = false;
bool skill3WasUsed = false;

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
        resetAllStates();

        //spawn chest
        spawnChest(enemy);

        GetRewardFromBosses();
        return;
    } 
    else if(Player.GetHealth() <= 0) // player dies
    {
        Player.SetAlive(false);
        Player.SetZone(enemy->GetZone());

        resetAllStates();

        PlaySound(sounds[SOUND_DEATH]);
        isDead = true;
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
                else if(CheckCollisionPointRec(mousePos, actionDefendButton) ) //defend
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
                else if(CheckCollisionPointRec(mousePos, skills1) && Player.GetEnergy() >= 15)
                {
                    skill1WasUsed = true;
                    playerAnimating = true;
                    animationTimer = 0;
                    skillButtonIsPressed = false;  
                    aTabIsOpen = false;
                    PlaySound(sounds[SOUND_HOVER_ITEMS]);
                }
                else if(CheckCollisionPointRec(mousePos, skills2) && Player.GetEnergy() >= 20)
                {
                    skill2WasUsed = true;
                    playerAnimating = true;
                    animationTimer = 0;
                    skillButtonIsPressed = false;  
                    aTabIsOpen = false;
                    PlaySound(sounds[SOUND_HOVER_ITEMS]);
                }
                else if(CheckCollisionPointRec(mousePos, skills3) && Player.GetEnergy() >= 50)
                {
                    skill3WasUsed = true;
                    playerAnimating = true;
                    animationTimer = 0;
                    skillButtonIsPressed = false;  
                    aTabIsOpen = false;
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

        if (!playerTurn)
        {
            CheckEnemyStatus(enemy);
            if (enemyIsPoisoned > 0) enemyIsPoisoned--;
            if (enemyOnFire > 0) enemyOnFire--;
            if (enemyIsFrozen > 0) enemyIsFrozen--;
            if (enemyIsShocked > 0) enemyIsShocked--;
            if(enemyIsPoisoned <= 0 && enemyOnFire <= 0 && enemyIsFrozen <= 0 && enemyIsShocked <= 0) showEnemyStatus = false;

            CheckPlayerStatus();
            if(defenseBuffCounter > 0) defenseBuffCounter--;
            if(damageBuffCounter > 0) damageBuffCounter--;
            if(damageBuffCounter <= 0 && defenseBuffCounter <= 0) showPlayerStatus = false;
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
    else if(Player.GetName() == Rogue.GetName())  DrawTile(playerCurrentPos.x, playerCurrentPos.y, 8, 0, 10.0f); 

    //enemy Tile
    switch(enemy->GetID())
    {
        case Enemy::ORC: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 11, 0, 10.0f); break; 
        case Enemy::WANDERING_EYE: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 13, 0, 10.0f); break; 
        case Enemy::TREANT: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 12, 1, 10.0f); break; 
        case Enemy::VENGEFUL_SPIRIT: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 9, 1, 10.0f); break; 
        case Enemy::GOLEM: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 10, 0, 10.0f); break; 
        case Enemy::SNAKE: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 4, 1, 10.0f); break; 
        case Enemy::RAT: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 6, 1, 10.0f); break; 
        case Enemy::SLIME: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 8, 1, 10.0f); break; 
        case Enemy::DOG: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 5, 1, 10.0f); break; 
        case Enemy::FLOATING_CRAB: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 7, 1, 10.0f); break;
        
        case Enemy::CRAB_THING: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 12, 0, 10.0f); break; 
        case Enemy::MUTATED_FROG: DrawTile(enemyCurrentPos.x, enemyCurrentPos.y, 10, 1, 10.0f); break; 
        
    }



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

        DrawText("Back", skillsBackButton.x + 5, skillsBackButton.y + 5, 25, WHITE);
        DrawText(TextFormat("Energy: %d / %d", Player.GetEnergy(), Player.GetMaxEnergy()), skillsBackButton.x + 160, skillsBackButton.y + 5, 25, WHITE);

        if(Player.GetName() == Knight.GetName())  ShowKnightSkill();
        else if(Player.GetName() == Wizard.GetName())  ShowWizardSkill(); 
        else if(Player.GetName() == Rogue.GetName())  ShowRogueSkill(); 
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
    
    if(showEnemyStatus)
    {
        float yOffset = -10.0f * (enemyStatusDisplayTime / DAMAGE_DISPLAY_DURATION);
        
        Color textColor = WHITE;
        switch (enemyStatusToShow)
        {
        case 1:
        {
            textColor = PURPLE;
            DrawText("Poisoned" , enemyStatusTextPosition.x, enemyStatusTextPosition.y + yOffset, 24, textColor);
            break;
        }
        case 2:
        {
            textColor = RED;
            DrawText("Burned", enemyStatusTextPosition.x, enemyStatusTextPosition.y + yOffset, 24, textColor);
            break;
        }
        case 3:
        {
            textColor = BLUE;
            DrawText("Frozen", enemyStatusTextPosition.x, (enemyStatusTextPosition.y - 20) + yOffset, 24, textColor);
            break;
        }
        case 4:
        {
            textColor = YELLOW;
            DrawText("Shocked", enemyStatusTextPosition.x, (enemyStatusTextPosition.y - 20) + yOffset, 24, textColor);
            break;  
        }
        }
    }

    if(showPlayerStatus)
    {
        float yOffset = -10.0f * (playerStatusDisplayTime / DAMAGE_DISPLAY_DURATION);
        
        Color textColor = WHITE;
        switch (playerStatusToShow)
        {
        case 1:
        {
            textColor = GREEN;
            DrawText("Damaged Buff!", playerStatusTextPosition.x, playerStatusTextPosition.y + yOffset, 24, textColor);
            break; 
        }
        case 2:
        {
            textColor = DARKBLUE;
            DrawText("Defense Buff!", playerStatusTextPosition.x, playerStatusTextPosition.y + yOffset, 24, textColor);
            break; 
        }
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

            if(!skill2WasUsed) playerCurrentPos.x = playerOriginalPos.x + (enemyOriginalPos.x - playerOriginalPos.x - 112) * progress;
            else if (skill2WasUsed)   playerCurrentPos.y = playerOriginalPos.y - 30 * sinf(progress * 3.14f);
        }
        else if (skill2WasUsed)
        {
            int skillNum = 2;
               
            Player.UseSkill(skillNum, enemy);
            skill2WasUsed = false;
            playerTurn = false;
        } 
        else if (animationTimer < ANIMATION_DURATION * 2 && playerTurn) 
        {
            //play attack sound and show damage
            if(skill1WasUsed || skill3WasUsed)
            {
                int skillNum = skill1WasUsed ? 1 : 3;
               
                Player.UseSkill(skillNum, enemy);
                skill1WasUsed = skill3WasUsed = false;
            }
            else if (!showDamage) 
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
        
        if (animationTimer < ANIMATION_DURATION ) 
        {
            //move to player
            float progress = animationTimer / ANIMATION_DURATION;
            enemyCurrentPos.x = enemyOriginalPos.x - (enemyOriginalPos.x - playerOriginalPos.x - 96) * progress;
        } 
        else if (animationTimer < ANIMATION_DURATION * 2 ) 
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
    
    //update damage and timer
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

    if(showEnemyStatus)
    {
        enemyStatusDisplayTime += frameTime;
        if(enemyStatusDisplayTime >= DAMAGE_DISPLAY_DURATION)
        {
            showEnemyStatus = false;
        }
    }

    if(showPlayerStatus)
    {
        playerStatusDisplayTime += frameTime;
        if(playerStatusDisplayTime >= DAMAGE_DISPLAY_DURATION)
        {
            showPlayerStatus = false;
        }
    }
}

void PlayerAttacks(Enemy *enemy)
{
    showDamage = true;
    damageToShow = GetRandomValue(Player.GetDamageMin(), Player.GetDamageMax()) - enemy->GetDefense();
    if(damageBuffCounter > 0) damageToShow += damageBuff;
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
    if(defenseBuffCounter > 0) enemyDamage = GetRandomValue(enemy->GetDamageMin(), enemy->GetDamageMax()) - (Player.GetDefense() + defenseBuff);

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
                damagePosition = (Vector2){playerCurrentPos.x + 50, playerCurrentPos.y};
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

void resetAllStates()
{
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
    damageBuff = 0;
    defenseBuff = 0;
    damageBuffCounter = 0;
    defenseBuffCounter = 0;
    enemyOnFire = 0;
    enemyIsShocked = 0;
    enemyIsFrozen = 0;
    enemyIsPoisoned = 0;
    playerCurrentPos = playerOriginalPos;
    enemyCurrentPos = enemyOriginalPos;
}

void ShowKnightSkill()
{
    //draw
    DrawText("Crushing Blow", skills1.x + 5, skills1.y + 5, 23, WHITE);
    DrawText("15 Energy", skills1.x + 10, skills1.y + 35, 20, WHITE);

    DrawText("Iron Wall", skills2.x + 5, skills2.y + 5, 26, WHITE);
    DrawText("20 Energy", skills2.x + 10, skills2.y + 35, 20, WHITE);

    DrawText("Valor's Edge", skills3.x + 5, skills3.y + 5, 17, WHITE);
    DrawText("50 Energy", skills3.x + 10, skills3.y + 35, 20, WHITE);
}

void ShowWizardSkill()
{
   
    //draw
    DrawText("Ignis Fulgur", skills1.x + 5, skills1.y + 5, 25, WHITE);
    DrawText("15 Energy", skills1.x + 10, skills1.y + 35, 20, WHITE);

    DrawText("Aegis Arcanum", skills2.x + 5, skills2.y + 5, 20, WHITE);
    DrawText("20 Energy", skills2.x + 10, skills2.y + 35, 20, WHITE);

    DrawText("Rite of Cataclysm", skills3.x + 5, skills3.y + 5, 17, WHITE);
    DrawText("50 Energy", skills3.x + 10, skills3.y + 35, 20, WHITE);

}

void ShowRogueSkill()
{

    //draw
    DrawText("Daggerfang", skills1.x + 5, skills1.y + 5, 25, WHITE);
    DrawText("15 Energy", skills1.x + 10, skills1.y + 35, 20, WHITE);

    DrawText("Smoke Viel", skills2.x + 5, skills2.y + 5, 26, WHITE);
    DrawText("20 Energy", skills2.x + 10, skills2.y + 35, 20, WHITE);

    DrawText("Final Requiem", skills3.x + 5, skills3.y + 5, 17, WHITE);
    DrawText("70 Energy", skills3.x + 10, skills3.y + 35, 20, WHITE);
}

void CheckEnemyStatus(Enemy *enemy)
{
    showEnemyStatus = true;

    if(enemyIsPoisoned > 0)
    {
        damageToShow = 10;
        enemy->TakeDamage(damageToShow);
        damagePosition = (Vector2){enemyCurrentPos.x + 50, enemyCurrentPos.y - 30};
        damageDisplayTime = 0;

        std::cout << "Enemy is poisoned for " << enemyIsPoisoned << " turns, took " << damageToShow << std::endl; 
        enemyStatusToShow = 1;
        if(enemyIsPoisoned < 0) enemyIsPoisoned = 0;

    }
    if(enemyOnFire > 0)
    {
        damageToShow = 15;
        enemy->TakeDamage(damageToShow);
        damagePosition = (Vector2){enemyCurrentPos.x + 50, enemyCurrentPos.y - 30};
        damageDisplayTime = 0;

        std::cout << "Enemy is on fire for " << enemyOnFire << " turns, took " << damageToShow << std::endl; 
        enemyStatusToShow = 2;
        if(enemyOnFire < 0) enemyOnFire = 0;

    }
    if(enemyIsFrozen > 0)
    {
        
        damageToShow = (enemy->GetHealth() / 100) + 2;
        enemy->TakeDamage(damageToShow);
        damagePosition = (Vector2){enemyCurrentPos.x + 50, enemyCurrentPos.y - 30};
        damageDisplayTime = 0;

        std::cout << "Enemy is frozen for " << enemyIsFrozen << " turns, took " << damageToShow << std::endl; 
        enemyStatusToShow = 3;
        if(enemyIsFrozen < 0) enemyIsFrozen = 0;

    }
    if(enemyIsShocked > 0)
    {
        std::cout << "Enemy is shocked for " << enemyIsShocked << " turns" << std::endl; 
        if(enemyIsShocked < 0) enemyIsShocked = 0;
        enemyStatusToShow = 4;

    }

    if(enemyAnimating && (enemyIsShocked > 0 || enemyIsFrozen > 0))
    {
        enemyAnimating = false;
        playerTurn = true;
        playerDefending = false;
        
        std::cout << "Enemy attack skipped due to status effect" << std::endl;
        
    }
     
    if(enemyIsFrozen || enemyIsShocked) {enemyStatusTextPosition = (Vector2) {enemyCurrentPos.x + 30, enemyCurrentPos.y - 50};}
    if(enemyIsPoisoned || enemyOnFire) {enemyStatusTextPosition = (Vector2) {enemyCurrentPos.x + 30, enemyCurrentPos.y - 70};}

    enemyStatusDisplayTime = 0;

}

void CheckPlayerStatus()
{
    showPlayerStatus = true;

    if(damageBuffCounter > 0)
    {
        std::cout << "Damaged buffed for " << damageBuffCounter << " turns" << std::endl; 
        if(damageBuffCounter < 0) damageBuffCounter = 0;

        playerStatusToShow = 1;
    }

    if(defenseBuffCounter > 0 )
    {
        std::cout << "Defense buffed for " << defenseBuffCounter << " turns" << std::endl; 
        if(defenseBuffCounter < 0) defenseBuffCounter = 0;

        playerStatusToShow = 2;
    }

    playerStatusTextPosition = (Vector2) {playerCurrentPos.x + 30, playerCurrentPos.y - 70};
    playerStatusDisplayTime = 0;
}

void GetRewardFromBosses()
{
    switch (enemy->GetID())
    {
    case Enemy::CRAB_THING:
    {
        dungeonKey = true;
        StartDialogue({"[You obtained Dungeon Key]"});
        break;
    }
    case Enemy::MUTATED_FROG:
    {
        mutantFrogKilled = true;
        break;
    }    
    default:
        break;
    }
}


