#include "GameFunctions.hpp"
#include "BattleSystem.hpp"
#include "Heroes.hpp"
#include "Entities.hpp"
#include <string>
#include <cmath>

//constructor
Hero::Hero(std::string name, std::string type, int x, int y, int health, int maxHealth, int energy, int maxEnergy, int damageMin, int damageMax, int defense, int experience,
    int level, int money, eZones zone, bool isAlive, bool isPassable )
    :
    name(name), type(type), x(x), y(y), health(health), maxHealth(maxHealth), energy(energy), maxEnergy(maxEnergy), healthPotions(3), energyFoods(2), damageMin(damageMin), damageMax(damageMax), defense(defense),
    experience(0), level(1), money(1000), zone(ZONE_WORLD), isAlive(true), isPassable(true) {}


//getters
std::string Hero::GetName() const { return name; }
std::string Hero::GetType() const { return type; }
int Hero::GetX() const {return x;}
int Hero::GetY() const {return y;}
int Hero::GetHealth() const { return health; }
int Hero::GetMaxHealth() const { return maxHealth; }
int Hero::GetEnergy() const {return energy;}
int Hero::GetMaxEnergy() const {return maxEnergy;}
int Hero::GetRemainingHealthPotions() const {return healthPotions;}
int Hero::GetRemainingEnergyFoods() const {return energyFoods;}
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

void Hero::SetEnergy(int amount) {energy = amount;}

void Hero::SetMaxEnergy(int amount) {maxEnergy = amount;}

void Hero::SetDamageMin(int amount) {damageMin = amount;}

void Hero::SetDamageMax(int amount) {damageMax = amount;}

void Hero::SetHealthPotions(int amount) {healthPotions = amount;}

void Hero::SetEnergyFoods(int amount) {energyFoods = amount;}

void Hero::SetDefense(int amount) {defense = amount;}

void Hero::GiveExperience(int amount) {experience = amount;}

void Hero::SetLevel(int amount) {level = amount;}

void Hero::SetMoney(int amount){ money = amount;}

void Hero::SetZone(eZones newZone) {zone = newZone;}

void Hero::SetAlive(bool state) {isAlive = state;}

void Hero::SetPermeation(bool state) {isPassable = state;}

void Hero::UseSkill(int skillNum, Enemy* target)
{
    if(Player.GetName() == "Knight")
    {
        switch(skillNum)
        {
            case 1:
            { //Crushing blow
                showDamage = true;
                damageToShow = (Player.GetDamageMax()) - enemy->GetDefense();

                if (enemy->GetWeakness() == Player.GetType()) damageToShow *= 2;
                if (damageToShow <= 0) damageToShow = 1;
                enemy->TakeDamage(damageToShow);
                damagePosition = (Vector2){enemyCurrentPos.x + 50, enemyCurrentPos.y - 30};
                damageDisplayTime = 0;
                Player.SetEnergy(Player.GetEnergy() - 15);

                PlaySound(sounds[SOUNDS_KNIGHT_SKILL1]);
                break;
            }
            case 2:
            { //iron wall
                showDamage = false;
                defenseBuffCounter = GetRandomValue(2,4);
                defenseBuff = GetRandomValue(4, Player.GetDefense());
                Player.SetEnergy(Player.GetEnergy() - 20);

                PlaySound(sounds[SOUNDS_KNIGHT_SKILL2]);
                break;
            }
            case 3:
            { //Valor's Edge
                showDamage = true;
                damageToShow = GetRandomValue(Player.GetDamageMax(), Player.GetDamageMax() + 10); 

                if (enemy->GetWeakness() == Player.GetType()) damageToShow *= 2;
                if (damageToShow <= 0) damageToShow = 1;
                enemy->TakeDamage(damageToShow);
                damagePosition = (Vector2){enemyCurrentPos.x + 50, enemyCurrentPos.y - 30};
                damageDisplayTime = 0;
                Player.SetEnergy(Player.GetEnergy() - 50);

                int status = GetRandomValue(1,4);
                status == 1? defenseBuff = 100 : defenseBuff = Player.GetDefense() + 2;
                status == 1? defenseBuffCounter = 1 : defenseBuffCounter = 2;

                PlaySound(sounds[SOUNDS_KNIGHT_SKILL3]);
            }

        }
    }
    else if(Player.GetName() == "Wizard")
    {
        switch (skillNum)
        {
            case 1:
            { // Ignis Fulgur
                showDamage = true;
                damageToShow = (Player.GetDamageMin() - enemy->GetDefense());

                if (enemy->GetWeakness() == Player.GetType()) damageToShow *= 2;
                if (damageToShow <= 0) damageToShow = 1;
                
                int status = GetRandomValue(1,3);
                status == 1 ? enemyOnFire = 4 : status == 2 ? enemyIsShocked = 2 : damageToShow += 1; 

                enemy->TakeDamage(damageToShow);
                damagePosition = (Vector2){enemyCurrentPos.x + 50, enemyCurrentPos.y - 30};
                damageDisplayTime = 0;
                Player.SetEnergy(Player.GetEnergy() - 15);

                PlaySound(sounds[SOUNDS_WIZARD_SKILL1]);
                break;
            }
            case 2:
            { // Aegis Arcanum
                showDamage = false;
                defenseBuffCounter = 4;
                defenseBuff = GetRandomValue(Player.GetDefense(), Player.GetDefense() + 10);
                Player.SetEnergy(Player.GetEnergy() - 20);

                PlaySound(sounds[SOUNDS_WIZARD_SKILL2]);
                break;
            }
            case 3:
            { // Rite of Cataclysm
                showDamage = true;
                damageToShow = 10;

                if (enemy->GetWeakness() == Player.GetType()) damageToShow *= 2;
                if (damageToShow <= 0) damageToShow = 1;
                
                int status = GetRandomValue(1,4);
                status == 1 ? enemyOnFire = 4 : status == 2 ? enemyIsShocked = 2 : status == 3 ? enemyIsPoisoned = 4 : enemyIsFrozen = 3;

                enemy->TakeDamage(damageToShow);
                damagePosition = (Vector2){enemyCurrentPos.x + 50, enemyCurrentPos.y - 30};
                damageDisplayTime = 0;
                Player.SetEnergy(Player.GetEnergy() - 50);

                PlaySound(sounds[SOUNDS_WIZARD_SKILL3]);
                break;
            }
            
        }
    }
    else if (Player.GetName() == "Rogue")
    {
        switch (skillNum)
        {
            case 1:
            { // DaggerFang
                showDamage = true;
                damageToShow = ((Player.GetDamageMin() + 8) - enemy->GetDefense());

                if (enemy->GetWeakness() == Player.GetType()) damageToShow *= 2;
                if (damageToShow <= 0) damageToShow = 1;
                
                int status = GetRandomValue(1,2);
                status == 1 ? enemyIsPoisoned = 6 : damageToShow += 5;

                enemy->TakeDamage(damageToShow);
                damagePosition = (Vector2){enemyCurrentPos.x + 50, enemyCurrentPos.y - 30};
                damageDisplayTime = 0;
                Player.SetEnergy(Player.GetEnergy() - 15);

                PlaySound(sounds[SOUNDS_ROGUE_SKILL1]);
                break;
            }
            case 2:
            { // Smoke Viel
                showDamage = false;
                int random = GetRandomValue(1,3);
                random == 1 ? defenseBuffCounter = 3 : random == 2 ? defenseBuffCounter = 2 : defenseBuffCounter = 0;
                defenseBuff = random < 3 ? 200 : 0;

                Player.SetEnergy(Player.GetEnergy() - 20);

                PlaySound(sounds[SOUNDS_ROGUE_SKILL2]);
                break;
            }
            case 3:
            { // Final Requiem
                showDamage = true;
                damageToShow = ((Player.GetDamageMax() + 8) - enemy->GetDefense());

                if (enemy->GetWeakness() == Player.GetType()) damageToShow *= 2;
                if (damageToShow <= 0) damageToShow = 1;

                int random = GetRandomValue(1,3);
                random == 1 ? damageBuffCounter = 3 : random == 2 ? damageBuffCounter = 2 : damageBuffCounter = 0;
                random < 3 ? damageBuff = Player.GetDamageMax() + Player.GetDamageMin() : damageBuff = 0;

                Player.SetEnergy(Player.GetEnergy() - 70);

                PlaySound(sounds[SOUNDS_ROGUE_SKILL3]);
                break;
            }
        }
    }
}
