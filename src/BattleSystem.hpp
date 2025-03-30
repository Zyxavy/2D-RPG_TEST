#ifndef BATTLE_SYSTEM_HPP
#define BATTLE_SYSTEM_HPP

#include "Entities.hpp"
#include "GameFunctions.hpp"
#include "Enemy.hpp"
#include "Entities.hpp"

//extern
extern bool battleMode;
extern bool playerTurn;
extern bool playerDefending;

//functions
void BattleUpdate(Enemy &enemy);
void BattleRender(Enemy &enemy);

#endif // BATTLE_SYSTEM_HPP