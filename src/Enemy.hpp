#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
#include "GameFunctions.hpp"

class Enemy {
private:
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
    bool stunned;
    int stunCounter;

public:
    // Constructor
    Enemy(std::string name, int x, int y, int health, eZones zone, int damageMin, int damageMax, int defense, int experience, int level, std::string weakness);

    // Getters
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
    void SetHealth(int hp);
    void SetStunStatus(int state);
    void SetStunCounter(int num);

    void MoveAI(int playerX, int playerY);  
    void Wander();
};

extern Enemy orc, wanderingEye, treant, vengefulSpirit, golem, crabThing;

extern Enemy* orc1;
extern Enemy* orc2;

extern Enemy* wanderingEye1;

extern Enemy* enemy;

#endif // ENTITIES_HPP

