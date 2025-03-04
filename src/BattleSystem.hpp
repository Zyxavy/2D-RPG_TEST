// BattleSystem.hpp
#ifndef BATTLE_SYSTEM_HPP
#define BATTLE_SYSTEM_HPP

#include "Entities.hpp"
#include "GameFunctions.hpp"

extern bool battleMode;
extern bool playerTurn;
extern bool playerDefending;

void BattleUpdate();
void BattleRender();

#endif // BATTLE_SYSTEM_HPP