#include "Entities.hpp"
#include "GameFunctions.hpp"
#include <raylib.h>
#include <iostream>


sEntity player, dungeon_gate;
sEnemy enemy, orc;
sEntity Knight, Wizard, Rouge;
int levelCap = 100;
bool playerLeveledUp = false;

void EntitiesInit() { 

    //default states
    player = (sEntity) {
        .x = TILE_WIDTH * 3,
        .y = TILE_HEIGHT * 3,
        .zone = ZONE_WORLD,
        .isAlive = true,
        .isPassable = false,
        .health = 100,
        .maxHealth = 100,
        .damageMin = 30,
        .damageMax = 40,
        .defense = 4, 
        .money = 1000,
        .experience = 0,
        .name = "Player",
        .type = " ",
    };

    //default states
    enemy = (sEnemy) {
        .x = TILE_WIDTH * 5,
        .y = TILE_HEIGHT * 5,
        .zone = ZONE_DUNGEON,
        .isAlive = true,
        .isPassable = false,
        .health = 100,
        .maxHealth = 100,
        .damageMin = 25,
        .damageMax = 30,
        .defense = 13, 
        .experience = GetRandomValue(10,100),
        .level = 1,
        .name = "enemy",
        .weakness = "",
    };
////
    Knight = (sEntity) {
        .x = TILE_WIDTH * 3,
        .y = TILE_HEIGHT * 3,
        .zone = ZONE_WORLD,
        .isAlive = true,
        .isPassable = false,
        .health = 200,
        .maxHealth = 200,
        .damageMin = 18,
        .damageMax = 37,
        .defense = 17,
        .money = 1000,
        .experience = 0,
        .name = "Knight", 
        .type = "Strength",
    };

    Wizard = (sEntity) {
        .x = TILE_WIDTH * 3,
        .y = TILE_HEIGHT * 3,
        .zone = ZONE_WORLD,
        .isAlive = true,
        .isPassable = false,
        .health = 100,
        .maxHealth = 100,
        .damageMin = 45,
        .damageMax = 60,
        .defense = 13,
        .money = 1000,
        .experience = 0, 
        .name = "Wizard",
        .type = "Intelligence", 
    };

    Rouge = (sEntity) {
        .x = TILE_WIDTH * 3,
        .y = TILE_HEIGHT * 3,
        .zone = ZONE_WORLD,
        .isAlive = true,
        .isPassable = false,
        .health = 140,
        .maxHealth = 140,
        .damageMin = 35,
        .damageMax = 44,
        .defense = 14,
        .money = 1200,
        .experience = 0, 
        .level = 1,
        .name = "Rouge",
        .type = "Dexterity", 
    };

    dungeon_gate = (sEntity) {
        .x = TILE_WIDTH * 10,
        .y = TILE_HEIGHT * 10,
        .zone = ZONE_ALL,
    };

    orc = (sEnemy) {
        .x = TILE_WIDTH * 5,
        .y = TILE_HEIGHT * 5,
        .zone = ZONE_DUNGEON,
        .isAlive = true,
        .isPassable = false,
        .health = 100,
        .maxHealth = 100,
        .damageMin = 25,
        .damageMax = 30,
        .defense = 13, 
        .experience = GetRandomValue(10,100),
        .level = 1,
        .name = "Orc",
        .weakness = "Intelligence",
    };

}

void PlayerRender()
{
    if(player.name == Knight.name)  DrawTile(camera.target.x, camera.target.y, 6, 0);
    else if(player.name == Wizard.name)  DrawTile(camera.target.x, camera.target.y, 9, 0); 
    else if(player.name == Rouge.name)  DrawTile(camera.target.x, camera.target.y, 8, 0);  
}

void EnemyRender()
{
    if(orc.zone == player.zone)
        {
            if(orc.isAlive == true) DrawTile(orc.x, orc.y, 11, 0);

            //Draw chest
            if(chest.isAlive) { DrawTile(chest.x, chest.y, 9 ,3);}
        }
}

void PlayerLevelUp()
{
    if(player.experience == levelCap)
    {
        playerLeveledUp = true;
        player.level++;
        player.damageMin += 10;
        player.damageMax += 10;
        player.defense += 2;
        player.health += 50;
        player.experience = 0;
        levelCap += 100;
    }
}
