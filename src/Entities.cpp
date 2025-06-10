#include "Entities.hpp"
#include "GameFunctions.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include "MusicFunctions.hpp"
#include "GameMenu.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>

sEntity dungeon_gate;
int levelCap = 100;
bool playerLeveledUp = false;

//Init enemies
Enemy orc(
    "Orc",
    TILE_WIDTH * 5, TILE_HEIGHT * 5,
    130, ZONE_DUNGEON, 25, 50, 12,
    100, 1, "Intelligence"
);

Enemy wanderingEye(
    "Wandering Eye",
    TILE_WIDTH * 10, TILE_HEIGHT * 20,
    100, ZONE_WORLD, 20, 45, 8,
    120, 1, "Strenght"
);

//Init Heroes
Hero Knight (
    "Knight", "Strength", 
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    200, 200, 100, 100, 18, 37, 24, 0, 1, 1000, ZONE_WORLD, true, true
);


Hero Wizard (
    "Wizard", "Intelligence", 
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    100, 100, 200, 200, 45, 55, 12, 0, 1, 1000, ZONE_WORLD, true, true
);

Hero Rogue (
    "Rogue", "Dexterity", 
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    140, 140, 130, 130, 35, 44, 17, 0, 1, 1300, ZONE_WORLD, true, true
);

Hero Player = Knight;
//enemy pointers
Enemy* orc1 = nullptr;
Enemy* orc2 = nullptr;
Enemy* orc3 = nullptr;
Enemy* orc4 = nullptr;
Enemy* orc5 = nullptr;
Enemy* orc6 = nullptr;

Enemy* wanderingEye1 = nullptr;
Enemy* wanderingEye2 = nullptr;

Enemy* enemy = nullptr;

//enemy arrays
Enemy* orcArr[MAX_ORCS_INSTANCES];
Enemy* eyeArr[MAX_WANDERING_EYE_INSTANCES];


void EntitiesInit() { 

    dungeon_gate = (sEntity) 
    {
        .x = TILE_WIDTH * 10,
        .y = TILE_HEIGHT * 10,
        .zone = ZONE_ALL,
    };



    //Place enemy instances
    orc1 = new Enemy(orc);
    orc1->Move( TILE_WIDTH * 5, TILE_HEIGHT * 5);

    orc2 = new Enemy(orc);
    orc2->Move(TILE_WIDTH * 6, TILE_HEIGHT * 5);

    orc3 = new Enemy(orc);
    orc3->Move(TILE_WIDTH * 15, TILE_HEIGHT * 16);

    orc4 = new Enemy(orc);
    orc4->Move(TILE_WIDTH * 14, TILE_HEIGHT * 5);

    orc5 = new Enemy(orc);
    orc5->Move(TILE_WIDTH * 12, TILE_HEIGHT * 14);

    orc6 = new Enemy(orc);
    orc6->Move(TILE_WIDTH * 3, TILE_HEIGHT * 10);


    wanderingEye1 = new Enemy(wanderingEye);
    wanderingEye1->Move(TILE_WIDTH * 10, TILE_HEIGHT * 20);

    wanderingEye2 = new Enemy(wanderingEye);
    wanderingEye2->Move(TILE_WIDTH * 14, TILE_HEIGHT * 20);

    //array of enemies
    orcArr[0] = orc1;
    orcArr[1] = orc2;
    orcArr[2] = orc3;
    orcArr[3] = orc4;
    orcArr[4] = orc5;
    orcArr[5] = orc6;


    eyeArr[0] = wanderingEye1;
    eyeArr[1] = wanderingEye2;

    Player.SetZone(ZONE_WORLD);
    

}

void PlayerRender()
{
    if(Player.GetName() == Knight.GetName())  DrawTile(camera.target.x, camera.target.y, 6, 0);
    else if(Player.GetName() == Wizard.GetName())  DrawTile(camera.target.x, camera.target.y, 9, 0); 
    else if(Player.GetName() == Rogue.GetName())  DrawTile(camera.target.x, camera.target.y, 8, 0);  
}

void EnemyRender()
{

    for(int i = 0; i < MAX_ORCS_INSTANCES; i++) 
    {
        if(orcArr[i]->GetZone() == Player.GetZone()) 
        {
            if(orcArr[i]->IsAlive() == true) 
            {
                DrawTile(orcArr[i]->GetX(), orcArr[i]->GetY(), 11, 0);
            }
        }
    }
    
    for(int i = 0; i < MAX_WANDERING_EYE_INSTANCES; i++)
    {
        if(eyeArr[i]->GetZone() == Player.GetZone())
        {
            if(eyeArr[i]->IsAlive() == true) 
            {
                DrawTile(eyeArr[i]->GetX(), eyeArr[i]->GetY(), 13, 0); 
            }
        }   
    }

    //spawn chest
    if(chest.isAlive) { DrawTile(chest.x, chest.y, 9 ,3);}
    
}

void PlayerLevelUp()
{
    if(Player.GetExperience() >= levelCap)
    {
        playerLeveledUp = true;
        
        for(int i = 0; i < MAX_LIGHT_MUSIC; i++)
        {
            SetMusicVolume(musicLight[i], 0.2f );
            SetMusicVolume(musicDark[i], 0.2f);
            SetMusicVolume(musicAction[i], 0.2f);
        }

        PlaySound(sounds[SOUNDS_LEVEL_UP]);
    
    }
}
