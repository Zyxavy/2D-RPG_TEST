#ifndef HEROES_HPP
#define HEROES_HPP

#include "raylib.h"
#include "Enemy.hpp"
#include "GameFunctions.hpp"
#include <string>

class Hero
{
    private:
    std::string name, type;
    int x, y;
    int health, maxHealth, energy, maxEnergy, healthPotions, energyFoods; 
    int damageMin, damageMax, defense, experience, level, money;
    eZones zone;  
    bool isAlive, isPassable;

    public:
    
    //Constructors
    Hero(std::string name, std::string type, int x, int y, int health, int maxHealth, int energy, int maxEnergy, int damageMin, int damageMax, int defense, int experience,
       int level, int money, eZones zone, bool isAlive, bool isPassable );

    //Getters
    std::string GetName() const;
    std::string GetType() const;
    int GetX() const;
    int GetY() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetEnergy() const;
    int GetMaxEnergy() const;
    int GetRemainingHealthPotions() const;
    int GetRemainingEnergyFoods() const;
    int GetDamageMin() const;
    int GetDamageMax() const;
    int GetDefense() const;
    int GetExperience() const;
    int GetLevel() const;
    int GetMoney() const;
    eZones GetZone() const;
    bool IsAlive() const;
    bool IsPassable() const;
    
    //setters
    void SetX(int x);
    void SetY(int y);
    void SetHealth(int amount);
    void SetMaxHealth(int amount);
    void SetEnergy(int amount);
    void SetMaxEnergy(int amount);
    void SetDamageMin(int amount);
    void SetDamageMax(int amount);
    void SetHealthPotions(int amount);
    void SetEnergyFoods(int amount);
    void SetDefense(int amount);
    void GiveExperience(int amount);
    void SetLevel(int amount);
    void SetMoney(int amount);
    void SetZone(eZones zone);
    void SetAlive(bool state);
    void SetPermeation(bool state);

    //skills
    void UseSkill(int skillNum, Enemy* target);

};

extern Hero Knight, Wizard, Rogue, Player;

#endif // HEROES_HPP