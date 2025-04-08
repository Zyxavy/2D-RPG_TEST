#include "GameFunctions.hpp"
#include "Heroes.hpp"
#include "Entities.hpp"
#include <string>
#include <cmath>

//constructor
Hero::Hero(std::string name, std::string type, int x, int y, int health, int maxHealth, int damageMin, int damageMax, int defense, int experience,
    int level, int money, eZones zone, bool isAlive, bool isPassable )
    :
    name(name), type(type), x(x), y(y), health(health), maxHealth(maxHealth), damageMin(damageMin), damageMax(damageMax), defense(defense),
    experience(0), level(1), money(1000), zone(ZONE_WORLD), isAlive(true), isPassable(true) {}


//getters
std::string Hero::GetName() const { return name; }

std::string Hero::GetType() const { return type; }
int Hero::GetX() const {return x;}
int Hero::GetY() const {return y;}
int Hero::GetHealth() const { return health; }
int Hero::GetMaxHealth() const { return maxHealth; }
int Hero::GetDamageMin() const { return damageMin; }
int Hero::GetDamageMax() const { return damageMax; }
int Hero::GetDefense() const { return defense; }
int Hero::GetExperience() const { return experience; }
int Hero::GetLevel() const { return level; }
int Hero::GetMoney() const { return money; }
eZones Hero::GetZone() const {return zone;}
bool Hero::IsAlive() const { return isAlive; }
bool Hero::IsPassable() const { return isPassable; }

//setters
void Hero::SetX(int newX) { x = newX;}

void Hero::SetY(int newY) { y = newY;}

void Hero::SetHealth(int amount)
{
    health = amount;

    if(health <= 0) SetAlive(false);
}

void Hero::SetMaxHealth(int amount) {maxHealth = amount;}

void Hero::SetDamageMin(int amount) {damageMin = amount;}

void Hero::SetDamageMax(int amount) {damageMax = amount;}

void Hero::SetDefense(int amount) {defense = amount;}

void Hero::GiveExperience(int amount) {experience = amount;}

void Hero::SetLevel(int amount) {level = amount;}

void Hero::SetMoney(int amount){ money = amount;}

void Hero::SetZone(eZones newZone) {zone = newZone;}

void Hero::SetAlive(bool state) {isAlive = state;}

void Hero::SetPermeation(bool state) {isPassable = state;}
