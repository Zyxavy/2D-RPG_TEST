#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include "raylib.h"
#include "GameFunctions.hpp"
#include <string>

class Enemy;

//definitions
#define MAX_ORCS_INSTANCES 4
#define MAX_WANDERING_EYE_INSTANCES 4
#define MAX_TREANT_INSTANCES 2
#define MAX_VENGEFUL_SPIRIT_INSTANCES 4
#define MAX_GOLEM_INSTANCES 8
#define MAX_SNAKE_INSTANCES 4
#define MAX_DOG_INSTANCES 3
#define MAX_RAT_INSTANCES 5
#define MAX_SLIME_INSTANCES 7
#define MAX_FLOATING_CRAB_INSTANCES 9
#define MAX_WATER_SLIME_INSTANCES 6

#define MAX_CRAB_THING_INSTANCES 3
#define MAX_MONSTER_SQUID_INSTANCES 3
#define MAX_MUTATED_FROG_INSTANCES 3
#define MAX_GUARDIAN_INSTANCES 1
#define MAX_SPECIAL_GOLEM_INSTANCES 3

#define MAX_CHEST_INSTANCES 4


//structs for player and enemy (OLD)
typedef struct 
{
    int x;
    int y;
    int x2;
    int y2;
    int textureX;
    int textureY;
    eZones zone1;
    eZones zone2;
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
extern sEntity dungeon_gate, plainLands_gate, basementStairs, ladderToIsland, seaExtensionEntrance, lostTempleEntrance, 
                lostTempleStairsToLevel1, lostTempleStairsToLevel2;
extern sEntity oldHermit, woundedKnight, villager1, villager2, villager3, basementLockedDoor, weirdMan, islander;
extern sEntity randomTrinket;
extern sEntity boat;
extern sEntity* chest1; 
extern sEntity* chest2; 
extern sEntity* chest3;
extern sEntity* chest4;
extern sEntity chest;

extern int levelCap;
extern bool playerLeveledUp;
extern bool chestIsPresent;

extern Enemy* orcArr[MAX_ORCS_INSTANCES];
extern Enemy* eyeArr[MAX_WANDERING_EYE_INSTANCES];
extern Enemy* treantArr[MAX_TREANT_INSTANCES];
extern Enemy* vengefulSpiritArr[MAX_VENGEFUL_SPIRIT_INSTANCES];
extern Enemy* golemArr[MAX_GOLEM_INSTANCES];
extern Enemy* snakeArr[MAX_SNAKE_INSTANCES];
extern Enemy* dogArr[MAX_DOG_INSTANCES];
extern Enemy* ratArr[MAX_RAT_INSTANCES];
extern Enemy* slimeArr[MAX_SLIME_INSTANCES];
extern Enemy* floatingCrabArr[MAX_FLOATING_CRAB_INSTANCES];
extern Enemy* waterSlimeArr[MAX_WATER_SLIME_INSTANCES];

extern Enemy* crabArr[MAX_CRAB_THING_INSTANCES];
extern Enemy* squidArr[MAX_MONSTER_SQUID_INSTANCES];
extern Enemy* mutantFrogArr[MAX_MUTATED_FROG_INSTANCES];
extern Enemy* guardianArr[MAX_GUARDIAN_INSTANCES];
extern Enemy* specialGolemArr[MAX_SPECIAL_GOLEM_INSTANCES];

extern sEntity* chestArr[MAX_CHEST_INSTANCES];

//functions
void EntitiesInit();
void PlayerRender();
void EnemyRender();
void PlayerLevelUp();
void HostileEntitiesLevelUp();
void ResetAllEnemies();
void spawnChest(Enemy *enemy);
void CheckContactWithEnemies();
void ExecuteEnemyBehaviors();

void EnterGates();
void RenderGates();

void InteractWithNPCs();
void RenderNPCs();
void RenderBoat();





#endif // ENTITIES_HPP

