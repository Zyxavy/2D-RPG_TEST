#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
#include "GameFunctions.hpp"

class Enemy {
private:
    int id;
    std::string name;
    int x, y;
    int health, maxHealth;  
    eZones zone;  
    int damageMin, damageMax;
    int defense;
    int experience;
    int level;
    bool isAlive;
    std::string weakness;
    bool isSpecial;
    int moneyMin, moneyMax;
    bool stunned;
    int stunCounter;
    
public:
    // Constructor
    Enemy(int id, std::string name, int x, int y, int health, eZones zone, int damageMin, int damageMax, int defense, 
        int experience, int level, std::string weakness, bool isSpecial, int moneyMin, int moneyMax);

    // Getters
    int GetID() const;
    std::string GetName() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetDamageMin() const;
    int GetDamageMax() const;
    int GetDefense() const;
    int GetExperience() const;
    int GetLevel() const;
    std::string GetWeakness() const;
    bool IsAlive() const;
    eZones GetZone() const;
    int GetX() const;
    int GetY() const;
    bool GetStunStatus() const;
    int GetStunCounter() const;
    bool GetSpecialStatus() const;
    int GetMoneyMin() const;
    int GetMoneyMax() const;

    // Setters
    void SetDamageMin(int amount);
    void SetDamageMax(int amount);
    void SetDefense(int amount);
    void SetLevel(int amount);
    void SetMaxHealth(int amount);
    void SetExperience(int amount);
    void TakeDamage(int amount);
    void Move(int newX, int newY);
    void Render(int tileX, int tileY) const;
    void SetAlive(bool state);
    void SetHealth(int amount);
    void SetStunStatus(int state);
    void SetStunCounter(int num);
    void SetSpecialStatus(bool status);
    void SetZone(eZones newZone);
    void SetMoneyMin(int amount);
    void SetMoneyMax(int amount);

    void MoveAI(int playerX, int playerY);  
    void Wander();

    enum EnemyID
    {
        ORC = 1,
        WANDERING_EYE = 2,
        TREANT = 3,
        VENGEFUL_SPIRIT = 4,
        GOLEM = 5,
        SNAKE = 6,
        DOG = 7,
        RAT = 8,
        SLIME = 9,
        CRAB_THING = 10,
        MONSTER_SQUID = 11,
        MUTATED_FROG = 12,
        GAURDIAN = 13,
        FLOATING_CRAB = 14,
        WATER_SLIME = 15,
        SPECIAL_GOLEM = 16
    };
};
//normal enemies
extern Enemy orc, wanderingEye, treant, vengefulSpirit, golem, snake, dog, rat, slime, floatingCrab, waterSlime;

//special / boss enemies
extern Enemy crabThing, monsterSquid, mutatedFrog, guardian, specialGolem;

//enemy pointers
extern Enemy* orc1;
extern Enemy* orc2;
extern Enemy* orc3;
extern Enemy* orc4;

extern Enemy* wanderingEye1;
extern Enemy* wanderingEye2;
extern Enemy* wanderingEye3;
extern Enemy* wanderingEye4;

extern Enemy* treant1;
extern Enemy* treant2;

extern Enemy* vengefulSpirit1;
extern Enemy* vengefulSpirit2;
extern Enemy* vengefulSpirit3;
extern Enemy* vengefulSpirit4;

extern Enemy* golem1;
extern Enemy* golem2;
extern Enemy* golem3;
extern Enemy* golem4;
extern Enemy* golem5;
extern Enemy* golem6;
extern Enemy* golem7;
extern Enemy* golem8;

extern Enemy* snake1;
extern Enemy* snake2;
extern Enemy* snake3;
extern Enemy* snake4;

extern Enemy* dog1;
extern Enemy* dog2;
extern Enemy* dog3;

extern Enemy* rat1;
extern Enemy* rat2;
extern Enemy* rat3;
extern Enemy* rat4;
extern Enemy* rat5;

extern Enemy* slime1;
extern Enemy* slime2;
extern Enemy* slime3;
extern Enemy* slime4;
extern Enemy* slime5;
extern Enemy* slime6;
extern Enemy* slime7;

extern Enemy* floatingCrab1;
extern Enemy* floatingCrab2;
extern Enemy* floatingCrab3;
extern Enemy* floatingCrab4;
extern Enemy* floatingCrab5;
extern Enemy* floatingCrab6;
extern Enemy* floatingCrab7;
extern Enemy* floatingCrab8;
extern Enemy* floatingCrab9;

extern Enemy* waterSlime1;
extern Enemy* waterSlime2;
extern Enemy* waterSlime3;
extern Enemy* waterSlime4;
extern Enemy* waterSlime5;
extern Enemy* waterSlime6;

extern Enemy* crabThing1;
extern Enemy* monsterSquid1;
extern Enemy* mutatedFrog1;
extern Enemy* guardian1;
extern Enemy* specialGolem1;

extern Enemy* enemy;

#endif // ENTITIES_HPP

