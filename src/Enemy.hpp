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

    // Setters
    void TakeDamage(int amount);
    void Move(int newX, int newY);
    void Render(int tileX, int tileY) const;
    void SetAlive(bool state);
    void SetHealth(int hp);

    void MoveAI(int playerX, int playerY);  
    void Wander();
};

extern Enemy orc, enemy;

#endif // ENTITIES_HPP

