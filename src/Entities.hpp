#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include "raylib.h"
#include "GameFunctions.hpp"
#include <string>

typedef struct 
{
    int x;
    int y;
    eZones zone;
    bool isAlive;
    bool isPassable;
    int health;
    int damageMin;
    int damageMax;
    int defense;
    int money;
    int experience;
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
    int damageMin;
    int damageMax;
    int defense;
    int money;
    int experience;
    std::string name;
    std::string weakness;

} sEnemy;

extern sEntity player;
extern sEntity dungeon_gate;
extern sEnemy orc;
extern sEntity chest;
extern sEntity Knight, Wizard, Rouge;


void EntitiesInit();
void PlayerRender();

#endif // ENTITIES_HPP

