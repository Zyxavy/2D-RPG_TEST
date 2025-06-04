#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include "raylib.h"
#include "GameFunctions.hpp"
#include <string>

class Enemy;

//definitions
#define MAX_ORCS_INSTANCES 2
#define MAX_WANDERING_EYE_INSTANCES 2

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
    int healthPotions;
    int energyFoods;
    std::string name;
    std::string type;

} sEntity;


//externs
extern sEntity dungeon_gate;
extern sEntity chest;
extern int levelCap;
extern bool playerLeveledUp;

extern Enemy* orcArr[MAX_ORCS_INSTANCES];
extern Enemy* eyeArr[MAX_WANDERING_EYE_INSTANCES];

//functions
void EntitiesInit();
void PlayerRender();
void EnemyRender();
void PlayerLevelUp();




#endif // ENTITIES_HPP

