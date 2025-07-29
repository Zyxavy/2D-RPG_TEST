#include "Items.hpp"
#include "Heroes.hpp"
#include "GameFunctions.hpp"
#include "StoryLine.hpp"
#include <string>
#include <iostream>


Items::Items(int itemID, std::string name, eZones zone, int x, int y, bool pickedUp, int tileTextureX, int tileTextureY)
    : itemID(itemID), name(name), zone(zone), x(x), y(y), pickedUp(pickedUp), 
      tileTextureX(tileTextureX), tileTextureY(tileTextureY),
      damageBoostMin(0), damageBoostMax(0), defenseBoost(0), 
      healthBoost(0), energyBoost(0), experienceBoost(0),
      enemyDamageBoostMin(0), enemyDamageBoostMax(0), enemyHealthBoost(0), enemyDefenseBoost(0) {}

//getters
    int Items::GetID() const {return itemID;}
    std::string Items::GetName() const{return name;}
    eZones Items::GetZone() const {return zone;}
    int Items::GetPosX() const {return x;}
    int Items::GetPosY() const {return y;}
    bool Items::IsPickedUp() const {return pickedUp;}
    int Items::GetTextureX() const {return tileTextureX;}
    int Items::GetTextureY() const {return tileTextureY;}

    int Items::GetDamageBoostMin() const {return damageBoostMin;}
    int Items::GetDamageBoostMax() const {return damageBoostMax;}
    int Items::GetDefenseBoost() const {return defenseBoost;}
    int Items::GetHealthBoost() const {return healthBoost;}
    int Items::GetEnergyBoost() const {return energyBoost;}
    int Items::GetExperienceBoost() const {return experienceBoost;}

    int Items::GetEnemyDamageBoostMin() const {return enemyDamageBoostMin;}
    int Items::GetEnemyDamageBoostMax() const {return enemyDamageBoostMax;}
    int Items::GetEnemyHealthBoost() const {return enemyHealthBoost;}
    int Items::GetEnemyDefenseBoost() const {return enemyDefenseBoost;}

    //setters
    void Items::SetPosX(int newX){x = newX;}
    void Items::SetPosY(int newY){y = newY;}
    void Items::SetZone(eZones newZone){zone = newZone;}
    void Items::SetPickedUpState(bool state){pickedUp = state;}
    void Items::SetDamageBoostMin(int amount){damageBoostMin = amount;}
    void Items::SetDamageBoostMax(int amount){damageBoostMax = amount;}
    void Items::SetDefenseBoost(int amount){defenseBoost = amount;}
    void Items::SetHealthBoost(int amount){healthBoost = amount;}
    void Items::SetEnergyBoost(int amount){energyBoost = amount;}
    void Items::SetExperienceBoost(int amount){experienceBoost = amount;}

    void Items::SetEnemyDamageBoostMin(int amount){enemyDamageBoostMin = amount;}
    void Items::SetEnemyDamageBoostMax(int amount){damageBoostMax = amount;}
    void Items::SetEnemyHealthBooost(int amount){enemyHealthBoost = amount;}
    void Items::SetEnemyDefenseBoost(int amount){enemyDefenseBoost = amount;}
 
//

Items goldenRing(
    Items::GOLDEN_RING, "Golden Ring of Fá!_a@#i", ZONE_DUNGEON, TILE_WIDTH * 13, TILE_HEIGHT * 5,
    false, 9, 5   
);

Items cursedGoldenKey(
    Items::CURSED_GOLDEN_KEY, "({})Cursed Golden Key({})", ZONE_WORLD_PLAIN_LANDS, TILE_WIDTH * 1, TILE_HEIGHT * 22,
    false, 10,5
); 


Items* itemArr[MAX_ITEMS] = {nullptr};

//funct
void ItemsInit()
{

    goldenRing.SetHealthBoost(100);
    goldenRing.SetEnemyDefenseBoost(3);
    itemArr[0] = &goldenRing;

    cursedGoldenKey.SetDamageBoostMin(20);
    cursedGoldenKey.SetDamageBoostMax(30);
    cursedGoldenKey.SetEnemyHealthBooost(150);
    itemArr[1] = &cursedGoldenKey;

}

void RenderItems()
{
    for(int i = 0; i < MAX_ITEMS; i++)
    {
        if(itemArr[i] != nullptr && itemArr[i]->GetZone() == Player.GetZone() && !itemArr[i]->IsPickedUp()) 
        {
           
            DrawTile(itemArr[i]->GetPosX(), itemArr[i]->GetPosY(), itemArr[i]->GetTextureX(), itemArr[i]->GetTextureY());
            
        }

    }
}

void InteractWithItems()
{
    static int currentItemIndex = -1;
    if (inDialogueWithOptions) return;

    if (currentItemIndex != -1)
    {
        if (YesorNo == true)
        {
            std::cout << "Yes selected\n";
            Player.SetMaxHealth(Player.GetMaxHealth() + itemArr[currentItemIndex]->GetHealthBoost());
            Player.SetDamageMin(Player.GetDamageMin() + itemArr[currentItemIndex]->GetDamageBoostMin());
            Player.SetDamageMax(Player.GetDamageMax() + itemArr[currentItemIndex]->GetDamageBoostMax());
            Player.SetDefense(Player.GetDefense() + itemArr[currentItemIndex]->GetDefenseBoost());
            itemArr[currentItemIndex]->SetPickedUpState(true);
        }
        else
        {
            std::cout << "No selected\n";
        }

        // Reset state
        currentItemIndex = -1;
        YesorNo = 0;
        return;
    }

    if (IsKeyPressed(KEY_E))
    {
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            if (itemArr[i] != nullptr &&
                abs(Player.GetX() - itemArr[i]->GetPosX()) <= TILE_WIDTH &&
                abs(Player.GetY() - itemArr[i]->GetPosY()) <= TILE_HEIGHT &&
                Player.GetZone() == itemArr[i]->GetZone() &&
                !itemArr[i]->IsPickedUp())
            {
                StartDialogueWithOptions({"Do you wish to pick up " + itemArr[i]->GetName() + "?"});
                currentItemIndex = i;
                break;
            }
        }
    }

}

 
