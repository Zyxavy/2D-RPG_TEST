#ifndef BATTLE_SYSTEM_HPP
#define BATTLE_SYSTEM_HPP

#include "Entities.hpp"
#include "GameFunctions.hpp"
#include "Enemy.hpp"
#include "Entities.hpp"


//externs
extern bool battleMode;
extern bool playerTurn;
extern bool playerDefending;
extern bool actionButtonIsPressed;
extern bool itemButtonIsPressed;
extern bool skillButtonIsPressed;
extern bool attackButtonIsPressed;
extern bool defendButtonIsPressed;
extern bool aTabIsOpen;

// Animation related variables
extern Vector2 playerOriginalPos;
extern Vector2 enemyOriginalPos;
extern Vector2 playerCurrentPos;
extern Vector2 enemyCurrentPos;
extern bool playerAnimating;
extern bool enemyAnimating;
extern bool showDamage;
extern int damageToShow;
extern Vector2 damagePosition;
extern Vector2 textPosition;
extern float animationTimer;
extern float damageDisplayTime;
extern const float ANIMATION_SPEED;
extern const float ANIMATION_DURATION;
extern const float DAMAGE_DISPLAY_DURATION;

//functions
void BattleUpdate(Enemy *enemy);
void BattleRender(Enemy *enemy);
void PlayerAttacks(Enemy *enemy);
void EnemyAttacks(Enemy *enemy);
void RenderBackground(Enemy *enemy);
void UpdateBattleAnimations(float frameTime, Enemy *enemy);
void RenderPlayerHearts();
void RenderEnemyHearts(Enemy *enemy);
void KnightSkill();
void WizardSkill();
void RougeSkill();


#endif // BATTLE_SYSTEM_HPP