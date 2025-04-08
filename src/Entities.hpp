#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include "raylib.h"
#include "GameFunctions.hpp"
#include <string>

//structs for player and enemy (OLD)
typedef struct 
{
    int x;
    int y;
    eZones zone;
    bool isAlive;
    bool isPassable;
    int health;
    int maxHealth;
    int damageMin;
    int damageMax;
    int defense;
    int money;
    int experience;
    int level;
    std::string name;
    std::string type;

} sEntity;


//externs
extern sEntity dungeon_gate;
extern sEntity chest;
extern int levelCap;
extern bool playerLeveledUp;

//functions
void EntitiesInit();
void PlayerRender();
void EnemyRender();
void PlayerLevelUp();




#endif // ENTITIES_HPP

