#include "Entities.hpp"
#include "GameFunctions.hpp"
#include <raylib.h>
#include <iostream>


sEntity player, dungeon_gate;
sEnemy orc;
sEntity Knight, Wizard, Rouge;

void EntitiesInit() { 

    player = (sEntity) {
        .x = TILE_WIDTH * 3,
        .y = TILE_HEIGHT * 3,
        .zone = ZONE_WORLD,
        .isAlive = true,
        .isPassable = false,
        .health = 100,
        .damageMin = 30,
        .damageMax = 40,
        .defense = 4, 
        .money = 1000,
        .experience = 0,
        .name = "Player",
        .type = " ",
    };

    Knight = (sEntity) {
        .x = TILE_WIDTH * 3,
        .y = TILE_HEIGHT * 3,
        .zone = ZONE_WORLD,
        .isAlive = true,
        .isPassable = false,
        .health = 200,
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
        .damageMin = 35,
        .damageMax = 44,
        .defense = 14,
        .money = 1200,
        .experience = 0, 
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
        .damageMin = 25,
        .damageMax = 30,
        .defense = 13, 
        .experience = GetRandomValue(10,100),
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
