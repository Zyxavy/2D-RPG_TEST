#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <string>
#include "GameFunctions.hpp"

#define MAX_ITEMS 5

class Items 
{
    private:
        int itemID;
        std::string name;
        eZones zone;
        int x;
        int y;
        bool pickedUp;
        int tileTextureX;
        int tileTextureY;
        //buff
        int damageBoostMin;
        int damageBoostMax;
        int defenseBoost;
        int healthBoost;
        int energyBoost;
        int experienceBoost;
        //debuffs
        int enemyDamageBoostMin;
        int enemyDamageBoostMax;
        int enemyHealthBoost;
        int enemyDefenseBoost;
    
    public:
    //constructor
        Items(int ItemID, std::string name, eZones zone, int x, int y, bool pickedUp, int tileTextureX, int tileTextureY);

    //getters
        int GetID() const;
        std::string GetName() const;
        eZones GetZone() const;
        int GetPosX() const;
        int GetPosY() const;
        bool IsPickedUp() const;
        int GetTextureX() const;
        int GetTextureY() const;

        int GetDamageBoostMin() const;
        int GetDamageBoostMax() const;
        int GetDefenseBoost() const;
        int GetHealthBoost() const;
        int GetEnergyBoost() const;
        int GetExperienceBoost() const;

        int GetEnemyDamageBoostMin() const;
        int GetEnemyDamageBoostMax() const;
        int GetEnemyHealthBoost() const;
        int GetEnemyDefenseBoost() const;
    
    //setters
        void SetPosX(int newX);
        void SetPosY(int newY);
        void SetZone(eZones newZone);
        void SetPickedUpState(bool state);

        void SetDamageBoostMin(int amount);
        void SetDamageBoostMax(int amount);
        void SetDefenseBoost(int amount);
        void SetHealthBoost(int amount);
        void SetEnergyBoost(int amount);
        void SetExperienceBoost(int amount);

        void SetEnemyDamageBoostMin(int amount);
        void SetEnemyDamageBoostMax(int amount);
        void SetEnemyHealthBooost(int amount);
        void SetEnemyDefenseBoost(int amount);


    enum ItemID
    {
        GOLDEN_RING = 0,
        CURSED_GOLDEN_KEY = 1,
        GREEN_HEART = 2,
        EYE_CORE = 3,
        PITCH_FORK = 4,
    };
};

//functions
void ItemsInit();
void RenderItems();
void InteractWithItems();

//items
extern Items goldenRing;
extern Items cursedGoldenKey;
extern Items greenHeart;
extern Items eyeCore;
extern Items pitchFork;

extern Items* itemArr[MAX_ITEMS];

#endif // ITEMS_HPP