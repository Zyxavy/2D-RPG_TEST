#include "Entities.hpp"
#include "GameFunctions.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include <raylib.h>
#include <iostream>


sEntity dungeon_gate;
int levelCap = 100;
bool playerLeveledUp = false;


Enemy orc(
    "Orc",
    TILE_WIDTH * 5, TILE_HEIGHT * 5,
    130, ZONE_DUNGEON, 25, 30, 12,
    GetRandomValue(10, 100),
    1, "Intelligence"
);

Enemy wanderingEye(
    "Wandering Eye",
    TILE_WIDTH * 10, TILE_HEIGHT * 20,
    100, ZONE_WORLD, 20, 45, 8,
    GetRandomValue(30, 120),
    1, "Strenght"
);

Hero Knight (
    "Knight", "Strength", 
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    200, 200, 18, 37, 24, 0, 1, 1000, ZONE_WORLD, true, true
);

Hero Wizard (
    "Wizard", "Intelligence", 
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    100, 100, 45, 55, 12, 0, 1, 1000, ZONE_WORLD, true, true
);

Hero Rouge (
    "Rouge", "Dexterity", 
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    140, 140, 35, 44, 17, 0, 1, 1300, ZONE_WORLD, true, true
);


Enemy enemy = orc;
Hero Player = Knight;


void EntitiesInit() { 
    dungeon_gate = (sEntity) {
        .x = TILE_WIDTH * 10,
        .y = TILE_HEIGHT * 10,
        .zone = ZONE_ALL,
    };

    Player.SetZone(ZONE_WORLD);

}

void PlayerRender()
{
    if(Player.GetName() == Knight.GetName())  DrawTile(camera.target.x, camera.target.y, 6, 0);
    else if(Player.GetName() == Wizard.GetName())  DrawTile(camera.target.x, camera.target.y, 9, 0); 
    else if(Player.GetName() == Rouge.GetName())  DrawTile(camera.target.x, camera.target.y, 8, 0);  
}

void EnemyRender()
{
    if(orc.GetZone() == Player.GetZone())
    {
        if(orc.IsAlive() == true) DrawTile(orc.GetX(), orc.GetY(), 11, 0); 
        //Draw chest
        if(chest.isAlive) { DrawTile(chest.x, chest.y, 9 ,3);}
    }

    
    if(wanderingEye.GetZone() == Player.GetZone())
    {
        if(wanderingEye.IsAlive() == true) DrawTile(wanderingEye.GetX(), wanderingEye.GetY(), 13, 0); 
        //Draw chest
        if(chest.isAlive) { DrawTile(chest.x, chest.y, 9 ,3);}

    }
    
}

void PlayerLevelUp()
{
    if(Player.GetExperience() == levelCap)
    {
        playerLeveledUp = true;
        Player.SetLevel(Player.GetLevel() + 1);
        Player.SetDamageMin(Player.GetDamageMin() + 10);
        Player.SetDamageMax(Player.GetDamageMax() + 10);
        Player.SetDefense(Player.GetDefense() + 1);
        Player.SetMaxHealth(Player.GetMaxHealth() + 50);
        Player.GiveExperience(0);
        levelCap += 100;
    }
}

