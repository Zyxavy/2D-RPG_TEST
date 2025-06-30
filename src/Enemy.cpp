#include "GameFunctions.hpp"
#include "Enemy.hpp"
#include "Entities.hpp"
#include "Heroes.hpp"
#include <string>
#include <cmath>

Enemy::Enemy(std::string name, int x, int y, int health, eZones zone, int damageMin, int damageMax, int defense, int experience, int level, std::string weakness)
    : name(name), x(x), y(y), health(health), maxHealth(health), zone(zone),
      damageMin(damageMin), damageMax(damageMax), defense(defense), experience(experience), 
      level(level), isAlive(true), weakness(weakness), stunned(false), stunCounter(0) {}


//getters
std::string Enemy::GetName() const { return name; }
int Enemy::GetHealth() const { return health; }
int Enemy::GetMaxHealth() const { return maxHealth; }
int Enemy::GetDamageMin() const { return damageMin; }
int Enemy::GetDamageMax() const { return damageMax; }
int Enemy::GetDefense() const { return defense; }
int Enemy::GetExperience() const { return experience; }
int Enemy::GetLevel() const { return level; }
std::string Enemy::GetWeakness() const { return weakness; }
bool Enemy::IsAlive() const { return isAlive; }
eZones Enemy::GetZone() const {return zone;}
int Enemy::GetX() const {return x;}
int Enemy::GetY() const {return y;}
bool Enemy::GetStunStatus() const {return stunned;}
int Enemy::GetStunCounter() const{return stunCounter;}

//setters
void Enemy::SetDamageMin(int amount) {damageMin = amount;}
void Enemy::SetDamageMax(int amount) {damageMax = amount;}
void Enemy::SetDefense(int amount){defense = amount;}
void Enemy::SetLevel(int amount){level = amount;}
void Enemy::SetMaxHealth(int amount){maxHealth = amount;}
void Enemy::SetExperience(int amount){experience = amount;}
void Enemy::Enemy::TakeDamage(int amount)
{
    health -= amount;
    if (health <= 0) {
        health = 0;
        SetAlive(false);
    }
}

void Enemy::Move(int newX, int newY) 
{
    x = newX;
    y = newY;
}

void Enemy::Render(int tileX, int tileY) const 
{
    if (isAlive) {
        DrawTile(x, y, tileX, tileY); 
    }
}
void Enemy::SetAlive(bool state) 
{
    isAlive = state;
}
void Enemy::SetHealth(int hp)
{
    health = hp;
}

void Enemy::SetStunStatus(int state)
{
    stunned = state;
}

void Enemy::SetStunCounter(int num)
{
    stunCounter = num;
}

//movement
void Enemy::MoveAI(int playerX, int playerY) 
{
    if (!isAlive) return;  
    if(stunned) return;

    int distanceX = std::abs(playerX - x) / TILE_WIDTH;
    int distanceY = std::abs(playerY - y) / TILE_HEIGHT;

    int newX = x;
    int newY = y;

    if(Player.GetZone() == zone){

        if (distanceX + distanceY > 5) 
        {
            Wander();
            return;
        }  
        //x-axis
        if (playerX > x) newX += TILE_WIDTH;  
        else if (playerX < x) newX -= TILE_WIDTH;

        //x-axis
        if (playerY > y) newY += TILE_HEIGHT;
        else if (playerY < y) newY -= TILE_HEIGHT;

        
        if (!IsBarrierCollision(newX, newY)) {
            x = newX;
            y = newY;
        }
    }
}

void Enemy::Wander()
{
    int direction = GetRandomValue(1,4);

    int newX = x;
    int newY = y;

    switch (direction)
    {
        case 1: newX += TILE_WIDTH; break;  
        case 2: newX -= TILE_WIDTH; break;  
        case 3: newY += TILE_HEIGHT; break;
        case 4: newY -= TILE_HEIGHT; break; 
    }

    if (!IsBarrierCollision(newX, newY)) {
        x = newX;
        y = newY;
    }
}