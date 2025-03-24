#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include "raylib.h"
#include "GameFunctions.hpp"
#include <string>

#define MAX_ENEMIES 5

//structs for player and enemy
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
    std::string weakness;

} sEnemy;

//externs
extern sEntity player;
extern sEnemy enemy;
extern sEntity dungeon_gate;
extern sEnemy orc;
extern sEntity chest;
extern sEntity Knight, Wizard, Rouge;
extern sEnemy enemies[MAX_ENEMIES];
extern sEnemy* encounteredEnemy;
extern int levelCap;
extern bool playerLeveledUp;



//functions
void EntitiesInit();
void PlayerRender();
void EnemyRender();
void PlayerLevelUp();

#endif // ENTITIES_HPP

