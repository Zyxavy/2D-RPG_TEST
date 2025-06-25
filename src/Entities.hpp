#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include "raylib.h"
#include "GameFunctions.hpp"
#include <string>

class Enemy;

//definitions
#define MAX_ORCS_INSTANCES 3
#define MAX_WANDERING_EYE_INSTANCES 2
#define MAX_TREANT_INSTANCES 2
#define MAX_VENGEFUL_SPIRIT_INSTANCES 2
#define MAX_GOLEM_INSTANCES 2
#define MAX_CRAB_THING_INSTANCES 1

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
extern Enemy* treantArr[MAX_TREANT_INSTANCES];
extern Enemy* vengefulSpiritArr[MAX_VENGEFUL_SPIRIT_INSTANCES];
extern Enemy* golemArr[MAX_GOLEM_INSTANCES];
extern Enemy* crabArr[MAX_CRAB_THING_INSTANCES];

//functions
void EntitiesInit();
void PlayerRender();
void EnemyRender();
void PlayerLevelUp();




#endif // ENTITIES_HPP

