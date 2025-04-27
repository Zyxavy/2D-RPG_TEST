#ifndef BATTLE_SYSTEM_HPP
#define BATTLE_SYSTEM_HPP

#include "Entities.hpp"
#include "GameFunctions.hpp"
#include "Enemy.hpp"
#include "Entities.hpp"

//definitions

//extern
extern bool battleMode;
extern bool playerTurn;
extern bool playerDefending;
extern bool actionButtonIsPressed;
extern bool itemButtonIsPressed;
extern bool skillButtonIsPressed;
extern bool attackButtonIsPressed;

//functions
void BattleUpdate(Enemy *enemy);
void BattleRender(Enemy *enemy);
void PlayerAttacks(Enemy *enemy);
void EnemyAttacks(Enemy *enemy);
void RenderBackground();

#endif // BATTLE_SYSTEM_HPP