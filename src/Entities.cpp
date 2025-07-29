#include "Entities.hpp"
#include "GameFunctions.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include "MusicFunctions.hpp"
#include "GameMenu.hpp"
#include "Items.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>

sEntity dungeon_gate, plainLands_gate, basementStairs, ladderToIsland;
sEntity oldHermit, woundedKnight, villager1, villager2, basementLockedDoor;
sEntity boat;
int levelCap = 100;
bool playerLeveledUp = false;
bool chestIsPresent = false;


//Init enemies
Enemy orc(
    Enemy::ORC, "Orc", // id, name
    TILE_WIDTH * 5, TILE_HEIGHT * 5, //spawn pos
    200, ZONE_WORLD_PLAIN_LANDS, 40, 60, 20, //maxhp, zone, dmgMin, dmgMax, def
    180, 3, "Intelligence", false // exp, level, weakness, special Status
);

Enemy wanderingEye(
    Enemy::WANDERING_EYE, "Wandering Eye",
    TILE_WIDTH * 10, TILE_HEIGHT * 20,
    240, ZONE_WORLD_PLAIN_LANDS, 50, 70, 12,
    215, 3, "Strenght", false
);

Enemy treant(
    Enemy::TREANT, "Treant",
    TILE_WIDTH * 5, TILE_HEIGHT * 8,
    190, ZONE_WORLD, 10, 80, 11,
    180, 3, "Dexterity", false
);

Enemy vengefulSpirit(
    Enemy::VENGEFUL_SPIRIT, "Vengeful Spirit",
    TILE_WIDTH * 1, TILE_HEIGHT * 1,
    100, ZONE_DUNGEON, 45, 50, 8,
    160, 2, "Intelligence", false
);

Enemy golem(
    Enemy::GOLEM, "Golem",
    TILE_WIDTH * 2, TILE_HEIGHT * 2,
    250, ZONE_DUNGEON, 18, 28, 25,
    200, 4, "Strenght", false
);

Enemy snake(
    Enemy::SNAKE, "Snake",
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    100, ZONE_WORLD, 25, 45, 10,
    125, 1, "Strenght", false
);

Enemy dog(
    Enemy::DOG, "Dog",
    TILE_WIDTH * 3, TILE_HEIGHT * 4,
    190, ZONE_BASEMENT_DUNGEON, 70, 90, 19,
    260, 5, "Dexterity", false
);

Enemy rat(
    Enemy::RAT, "Rat",
    TILE_WIDTH * 3, TILE_HEIGHT * 5,
    80, ZONE_DUNGEON, 25, 45, 8,
    120, 2, "Intelligence", false
);

Enemy slime(
    Enemy::SLIME, "Slime",
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    240, ZONE_BASEMENT_DUNGEON, 54, 83, 20,
    230, 4, "Intelligence", false
);

Enemy floatingCrab(
    Enemy::FLOATING_CRAB, "Floating Crab",
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    300, ZONE_ISLAND, 68, 101, 25,
    300, 5, "Dexterity", false
);

//bosses | special
Enemy crabThing(
    Enemy::CRAB_THING, "The Crab Thing",
    TILE_WIDTH * 1, TILE_HEIGHT * 5,
    150, ZONE_WORLD, 30, 50, 15,
    200, 6, "NULL", true
);

Enemy monsterSquid(
    Enemy::MONSTER_SQUID, "The Great Monster Squid",
    TILE_WIDTH * 2, TILE_HEIGHT * 5,
    200, ZONE_WORLD_PLAIN_LANDS, 50, 60, 20,
    340, 7, "NULL", true
);

Enemy mutatedFrog(
    Enemy::MUTATED_FROG, "The Mutant Frog | 0-02",
    TILE_WIDTH * 2, TILE_HEIGHT * 5,
    300, ZONE_WORLD_PLAIN_LANDS, 50, 90, 30,
    510, 8, "NULL", true
);

Enemy guardian(
    Enemy::GAURDIAN, "The Guardian",
    TILE_WIDTH * 2, TILE_HEIGHT * 5,
    500, ZONE_WORLD_PLAIN_LANDS, 1, 150, 30,
    999, 15, "NULL", true
);


//Init Heroes
Hero Knight (
    "Knight", "Strength", //Name, type
    TILE_WIDTH * 3, TILE_HEIGHT * 3, // pos X, pos Y
    200, 200, 100, 100, 200, 300 /*to be fixed*/, 24, 0, 1, 1000, ZONE_WORLD, true, true // hp, maxhp, energy, maxenergy, damagemin,damagemax,defense, experience, level, money, zone, is alive, is passable
);

Hero Wizard (
    "Wizard", "Intelligence", 
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    100, 100, 200, 200, 45, 55, 12, 0, 1, 1000, ZONE_WORLD, true, true
);

Hero Rogue (
    "Rogue", "Dexterity", 
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    140, 140, 130, 130, 35, 44, 17, 0, 1, 1300, ZONE_WORLD, true, true
);



Hero Player = Knight;
//enemy pointers
Enemy* orc1 = nullptr;
Enemy* orc2 = nullptr;
Enemy* orc3 = nullptr;
Enemy* orc4 = nullptr;

Enemy* wanderingEye1 = nullptr;
Enemy* wanderingEye2 = nullptr;
Enemy* wanderingEye3 = nullptr;
Enemy* wanderingEye4 = nullptr;


Enemy* treant1 = nullptr;
Enemy* treant2 = nullptr;

Enemy* vengefulSpirit1 = nullptr;
Enemy* vengefulSpirit2 = nullptr;

Enemy* golem1 = nullptr;
Enemy* golem2 = nullptr;

Enemy* snake1 = nullptr;
Enemy* snake2 = nullptr;
Enemy* snake3 = nullptr;
Enemy* snake4 = nullptr;

Enemy* dog1 = nullptr;
Enemy* dog2 = nullptr;
Enemy* dog3 = nullptr;

Enemy* rat1 = nullptr;
Enemy* rat2 = nullptr;

Enemy* slime1 = nullptr;
Enemy* slime2 = nullptr;
Enemy* slime3 = nullptr;
Enemy* slime4 = nullptr;

Enemy* floatingCrab1 = nullptr;
Enemy* floatingCrab2 = nullptr; 
Enemy* floatingCrab3 = nullptr;
Enemy* floatingCrab4 = nullptr;

Enemy* crabThing1 = nullptr;
Enemy* monsterSquid1 = nullptr;
Enemy* mutatedFrog1 = nullptr;
Enemy* guardian1 = nullptr;

Enemy* enemy = nullptr;

//enemy arrays
Enemy* orcArr[MAX_ORCS_INSTANCES];
Enemy* eyeArr[MAX_WANDERING_EYE_INSTANCES];
Enemy* treantArr[MAX_TREANT_INSTANCES];
Enemy* vengefulSpiritArr[MAX_VENGEFUL_SPIRIT_INSTANCES];
Enemy* golemArr[MAX_GOLEM_INSTANCES];
Enemy* snakeArr[MAX_SNAKE_INSTANCES];
Enemy* dogArr[MAX_DOG_INSTANCES];
Enemy* ratArr[MAX_RAT_INSTANCES];
Enemy* slimeArr[MAX_SLIME_INSTANCES];
Enemy* floatingCrabArr[MAX_FLOATING_CRAB_INSTANCES];

Enemy* crabArr[MAX_CRAB_THING_INSTANCES];
Enemy* squidArr[MAX_MONSTER_SQUID_INSTANCES];
Enemy* mutantFrogArr[MAX_MUTATED_FROG_INSTANCES];
Enemy* guardianArr[MAX_GUARDIAN_INSTNACES];

sEntity chest = (sEntity)
{
    .x = 0, .y = 0, .zone1 = ZONE_ALL, .zone2 = ZONE_ALL,
    .isAlive = false, .isPassable = true, .health = 1, .maxHealth = 1,
    .damageMin = 1, .damageMax = 1, .defense = 1, .money = 1, .experience = 1, .level = 1,
    .healthPotions = 1,  .energyFoods = 1, .name = "Chest", .type = "Entity"
};


sEntity* chest1 = nullptr; 
sEntity* chest2 = nullptr; 
sEntity* chest3 = nullptr;
sEntity* chest4 = nullptr;
sEntity* chestArr[MAX_CHEST_INSTANCES] = {chest1, chest2, chest3, chest4};


void EntitiesInit() { 

    //gates
    dungeon_gate = (sEntity) 
    {
        .x = TILE_WIDTH * 3, // 15
        .y = TILE_HEIGHT * 3, // 17
        .zone1 = ZONE_WORLD,
        .zone2 = ZONE_DUNGEON
    };

    plainLands_gate = (sEntity) 
    {
        .x = TILE_WIDTH * 4,
        .y = TILE_HEIGHT * 6,
        .zone1 = ZONE_DUNGEON,
        .zone2 = ZONE_WORLD_PLAIN_LANDS
    };

    basementStairs = (sEntity) 
    {
        .x = TILE_WIDTH * 22,
        .y = TILE_HEIGHT * 18,
        .zone1 = ZONE_WORLD_PLAIN_LANDS,
        .zone2 = ZONE_BASEMENT_DUNGEON
    };

    ladderToIsland = (sEntity) 
    {
        .x = TILE_WIDTH * 11,
        .y = TILE_HEIGHT * 9,
        .zone1 = ZONE_BASEMENT_DUNGEON,
        .zone2 = ZONE_ISLAND
    };

    //NPCs - Zone1
    oldHermit = (sEntity)
    {
        .x = TILE_WIDTH * 11,
        .y = TILE_HEIGHT * 3,
        .zone1 = ZONE_WORLD,
        .zone2 = ZONE_WORLD_PLAIN_LANDS,
        .isPassable = false
    };

    woundedKnight = (sEntity)
    {
        .x = TILE_WIDTH * 13,
        .y = TILE_HEIGHT * 15,
        .zone1 = ZONE_WORLD,
        .zone2 = ZONE_BASEMENT_DUNGEON,
        .isPassable = false
    };

    //ZONE2
    villager1 = (sEntity)
    {
        .x = TILE_WIDTH * 23,
        .y = TILE_HEIGHT * 4,
        .zone1 = ZONE_WORLD_PLAIN_LANDS,
        .zone2 = ZONE_WORLD_PLAIN_LANDS,
        .isPassable = false
    };

    villager2 = (sEntity)
    {
        .x = TILE_WIDTH * 20,
        .y = TILE_HEIGHT * 3,
        .zone1 = ZONE_WORLD_PLAIN_LANDS,
        .zone2 = ZONE_WORLD_PLAIN_LANDS,
        .isPassable = false
    };

    //basement
    
    basementLockedDoor = (sEntity)
    {
        .x = TILE_WIDTH * 11,
        .y = TILE_HEIGHT * 12,
        .zone1 = ZONE_BASEMENT_DUNGEON,
        .zone2 = ZONE_BASEMENT_DUNGEON,
        .isPassable = false
    };

    boat = (sEntity)
    {
        .x = TILE_WIDTH * 14,
        .y = TILE_HEIGHT * 12,
        .zone1 = ZONE_ISLAND,
        .zone2 = ZONE_ISLAND, 
        .isPassable = false 
    };

    //Place enemy instances

    //zone1

    treant1 = new Enemy(treant);
    treant1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    treant2 = new Enemy(treant);
    treant2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));


    crabThing1 = new Enemy(crabThing);
    crabThing1->Move(dungeon_gate.x + TILE_WIDTH, dungeon_gate.y + TILE_HEIGHT);

    snake1 = new Enemy(snake);
    snake1->Move(TILE_WIDTH * GetRandomValue(1,15), TILE_HEIGHT * GetRandomValue(1,20));

    snake2 = new Enemy(snake);
    snake2->Move(TILE_WIDTH * GetRandomValue(1,15), TILE_HEIGHT * GetRandomValue(1,20));

    snake3 = new Enemy(snake);
    snake3->Move(TILE_WIDTH * GetRandomValue(1,15), TILE_HEIGHT * GetRandomValue(1,20));

    snake4 = new Enemy(snake);
    snake4->Move(TILE_WIDTH * GetRandomValue(1,15), TILE_HEIGHT * GetRandomValue(1,20));

    //dungeon1

    rat1 = new Enemy(rat);
    rat1->Move(TILE_WIDTH * GetRandomValue(1,15), TILE_HEIGHT * GetRandomValue(1,20));

    rat2 = new Enemy(rat);
    rat2->Move(TILE_WIDTH * GetRandomValue(1,15), TILE_HEIGHT * GetRandomValue(1,20));

    vengefulSpirit1 = new Enemy(vengefulSpirit);
    vengefulSpirit1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    vengefulSpirit2 = new Enemy(vengefulSpirit);
    vengefulSpirit2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    golem1 = new Enemy(golem);
    golem1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    golem2 = new Enemy(golem);
    golem2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    //plains
    orc1 = new Enemy(orc);
    orc1->Move( TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    orc2 = new Enemy(orc);
    orc2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    orc3 = new Enemy(orc);
    orc3->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    orc4 = new Enemy(orc);
    orc4->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    wanderingEye1 = new Enemy(wanderingEye);
    wanderingEye1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    wanderingEye2 = new Enemy(wanderingEye);
    wanderingEye2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    wanderingEye3 = new Enemy(wanderingEye);
    wanderingEye3->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    wanderingEye4 = new Enemy(wanderingEye);
    wanderingEye4->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    mutatedFrog1 = new Enemy(mutatedFrog);
    mutatedFrog1->Move(TILE_WIDTH * 2, TILE_HEIGHT * 21);

    //dungeon Basement
    slime1 = new Enemy(slime);
    slime1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    slime2 = new Enemy(slime);
    slime2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    slime3 = new Enemy(slime);
    slime3->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    slime4 = new Enemy(slime);
    slime4->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    dog1 = new Enemy(dog);
    dog1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    dog2 = new Enemy(dog);
    dog2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    dog3 = new Enemy(dog);
    dog3->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    //Island
    floatingCrab1 = new Enemy(floatingCrab);
    floatingCrab1->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    floatingCrab2 = new Enemy(floatingCrab);
    floatingCrab2->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    floatingCrab3 = new Enemy(floatingCrab);
    floatingCrab3->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    floatingCrab4 = new Enemy(floatingCrab);
    floatingCrab4->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    //array of enemies
    orcArr[0] = orc1;
    orcArr[1] = orc2;
    orcArr[2] = orc3;
    orcArr[3] = orc4;

    eyeArr[0] = wanderingEye1;
    eyeArr[1] = wanderingEye2;
    eyeArr[2] = wanderingEye3;
    eyeArr[3] = wanderingEye4;

    treantArr[0] = treant1;
    treantArr[1] = treant2;

    vengefulSpiritArr[0] = vengefulSpirit1;
    vengefulSpiritArr[1] = vengefulSpirit2;

    golemArr[0] = golem1;
    golemArr[1] = golem2;

    snakeArr[0] = snake1;
    snakeArr[1] = snake2;
    snakeArr[2] = snake3;
    snakeArr[3] = snake4;

    ratArr[0] = rat1;
    ratArr[1] = rat2;

    slimeArr[0] = slime1;
    slimeArr[1] = slime2;
    slimeArr[2] = slime3;
    slimeArr[3] = slime4;

    dogArr[0] = dog1;
    dogArr[1] = dog2;
    dogArr[2] = dog3;

    floatingCrabArr[0] = floatingCrab1;
    floatingCrabArr[1] = floatingCrab2;
    floatingCrabArr[2] = floatingCrab3;
    floatingCrabArr[3] = floatingCrab4;

    crabArr[0] = crabThing1;
    mutantFrogArr[0] = mutatedFrog1;

    Player.SetZone(ZONE_WORLD);

}

void PlayerRender()
{
    if (isRidingBoat)
    {
        if (isBoatFacingRight)
        {
            DrawTexture(textures[TEXTURE_BOAT_RIGHT], camera.target.x, camera.target.y, WHITE);
        }
        else
        {
            DrawTexture(textures[TEXTURE_BOAT_LEFT], camera.target.x, camera.target.y, WHITE);
        }
    }
    else
    {
        if(Player.GetName() == Knight.GetName())  DrawTexture(textures[TEXTURE_KNIGHT], camera.target.x, camera.target.y, WHITE);
        else if(Player.GetName() == Wizard.GetName()) DrawTexture(textures[TEXTURE_WIZARD], camera.target.x, camera.target.y, WHITE); 
        else if(Player.GetName() == Rogue.GetName())  DrawTexture(textures[TEXTURE_ROGUE], camera.target.x, camera.target.y, WHITE);  
    }
}

void EnemyRender()
{

    for(int i = 0; i < MAX_ORCS_INSTANCES; i++) 
    {
        if(orcArr[i]->GetZone() == Player.GetZone()) 
        {
            if(orcArr[i]->IsAlive() == true) 
            {
                DrawTile(orcArr[i]->GetX(), orcArr[i]->GetY(), 11, 0);
            }
        }
    }
    
    for(int i = 0; i < MAX_WANDERING_EYE_INSTANCES; i++)
    {
        if(eyeArr[i]->GetZone() == Player.GetZone())
        {
            if(eyeArr[i]->IsAlive() == true) 
            {
                DrawTile(eyeArr[i]->GetX(), eyeArr[i]->GetY(), 13, 0); 
            }
        }   
    }

    for(int i = 0; i < MAX_TREANT_INSTANCES; i++)
    {
        if(treantArr[i]->GetZone() == Player.GetZone())
        {
            if(treantArr[i]->IsAlive() == true) 
            {
                DrawTile(treantArr[i]->GetX(), treantArr[i]->GetY(), 12, 1); 
            }
        }   
    }

    for(int i = 0; i < MAX_VENGEFUL_SPIRIT_INSTANCES; i++)
    {
        if(vengefulSpiritArr[i]->GetZone() == Player.GetZone())
        {
            if(vengefulSpiritArr[i]->IsAlive() == true) 
            {
                DrawTile(vengefulSpiritArr[i]->GetX(), vengefulSpiritArr[i]->GetY(), 9, 1); 
            }
        }   
    }

    for(int i = 0; i < MAX_GOLEM_INSTANCES; i++)
    {
        if(golemArr[i]->GetZone() == Player.GetZone())
        {
            if(golemArr[i]->IsAlive() == true) 
            {
                DrawTile(golemArr[i]->GetX(), golemArr[i]->GetY(), 10, 0); 
            }
        }   
    }

    for(int i = 0; i < MAX_SNAKE_INSTANCES; i++)
    {
        if(snakeArr[i]->GetZone() == Player.GetZone())
        {
            if(snakeArr[i]->IsAlive() == true) 
            {
                DrawTile(snakeArr[i]->GetX(), snakeArr[i]->GetY(), 4, 1); 
            }
        }   
    }

    for(int i = 0; i < MAX_CRAB_THING_INSTANCES; i++)
    {
        if(crabArr[i]->GetZone() == Player.GetZone())
        {
            if(crabArr[i]->IsAlive() == true) 
            {
                DrawTile(crabArr[i]->GetX(), crabArr[i]->GetY(), 12, 0); 
            }
        }   
    }

    for(int i = 0; i < MAX_RAT_INSTANCES; i++)
    {
        if(ratArr[i]->GetZone() == Player.GetZone())
        {
            if(ratArr[i]->IsAlive() == true) 
            {
                DrawTile(ratArr[i]->GetX(), ratArr[i]->GetY(), 6, 1); 
            }
        }   
    }

    for(int i = 0; i < MAX_MUTATED_FROG_INSTANCES; i++)
    {
        if(mutantFrogArr[i]->GetZone() == Player.GetZone())
        {
            if(mutantFrogArr[i]->IsAlive() == true) 
            {
                DrawTile(mutantFrogArr[i]->GetX(), mutantFrogArr[i]->GetY(), 10, 1); 
            }
        }   
    }

    for(int i = 0; i < MAX_SLIME_INSTANCES; i++)
    {
        if(slimeArr[i]->GetZone() == Player.GetZone())
        {
            if(slimeArr[i]->IsAlive() == true) 
            {
                DrawTile(slimeArr[i]->GetX(), slimeArr[i]->GetY(), 8, 1); 
            }
        }   
    }

    for(int i = 0; i < MAX_DOG_INSTANCES; i++)
    {
        if(dogArr[i]->GetZone() == Player.GetZone())
        {
            if(dogArr[i]->IsAlive() == true) 
            {
                DrawTile(dogArr[i]->GetX(), dogArr[i]->GetY(), 5, 1); 
            }
        }   
    }

    for(int i = 0; i < MAX_FLOATING_CRAB_INSTANCES; i++)
    {
        if(floatingCrabArr[i]->GetZone() == Player.GetZone())
        {
            if(floatingCrabArr[i]->IsAlive() == true) 
            {
                DrawTexture(textures[TEXTURE_FLOATING_CRAB], floatingCrabArr[i]->GetX(), floatingCrabArr[i]->GetY(), WHITE);
            }
        }   
    }

    //Render chest
    for(int i = 0; i < MAX_CHEST_INSTANCES; i++)
    {
        if(chestArr[i] != nullptr && chestArr[i]->zone1 == Player.GetZone())
        {
            if(chestArr[i]->isAlive) 
            {
                DrawTile(chestArr[i]->x, chestArr[i]->y, 9, 3); 
            }
        }   
    }
    
}

void PlayerLevelUp()
{
    if(Player.GetExperience() >= levelCap)
    {
        playerLeveledUp = true;
        
        for(int i = 0; i < MAX_LIGHT_MUSIC; i++)
        {
            SetMusicVolume(musicLight[i], 0.2f );
            SetMusicVolume(musicDark[i], 0.2f);
            SetMusicVolume(musicAction[i], 0.2f);
        }

        HostileEntitiesLevelUp();
        PlaySound(sounds[SOUNDS_LEVEL_UP]);
    
    }
}

void HostileEntitiesLevelUp()
{
    //orcs
    for(int i = 0; i < MAX_ORCS_INSTANCES;i++)
    {
        orcArr[i]->SetMaxHealth(orc.GetMaxHealth() + 60);
        orcArr[i]->SetDamageMin(orc.GetDamageMin() + 8);
        orcArr[i]->SetDamageMax(orc.GetDamageMax() + 10);
        orcArr[i]->SetDefense(orc.GetDefense() + 2);
        orcArr[i]->SetLevel(orc.GetLevel() + 1);
        orcArr[i]->SetExperience(orc.GetExperience() + 35);
        orcArr[i]->SetHealth(orc.GetMaxHealth());
    }

    //wandering Eyes
    for(int i = 0; i < MAX_WANDERING_EYE_INSTANCES;i++)
    {
        eyeArr[i]->SetMaxHealth(wanderingEye.GetMaxHealth() + 50);
        eyeArr[i]->SetDamageMin(wanderingEye.GetDamageMin() + 10);
        eyeArr[i]->SetDamageMax(wanderingEye.GetDamageMax() + 15);
        eyeArr[i]->SetDefense(wanderingEye.GetDefense() + 1);
        eyeArr[i]->SetLevel(wanderingEye.GetLevel() + 1);
        eyeArr[i]->SetExperience(wanderingEye.GetExperience() + 40);
        eyeArr[i]->SetHealth(wanderingEye.GetMaxHealth());
    }

    //Treants
    for(int i = 0; i < MAX_TREANT_INSTANCES;i++)
    {
        treantArr[i]->SetMaxHealth(treant.GetMaxHealth() + 80);
        treantArr[i]->SetDamageMin(treant.GetDamageMin() + 5);
        treantArr[i]->SetDamageMax(treant.GetDamageMax() + 5);
        treantArr[i]->SetDefense(treant.GetDefense() + 3);
        treantArr[i]->SetLevel(treant.GetLevel() + 1);
        treantArr[i]->SetExperience(treant.GetExperience() + 35);
        treantArr[i]->SetHealth(treant.GetMaxHealth());
    }

    //Vengeful Spirits
    for(int i = 0; i < MAX_VENGEFUL_SPIRIT_INSTANCES;i++)
    {
        vengefulSpiritArr[i]->SetMaxHealth(vengefulSpirit.GetMaxHealth() + 50);
        vengefulSpiritArr[i]->SetDamageMin(vengefulSpirit.GetDamageMin() + 10);
        vengefulSpiritArr[i]->SetDamageMax(vengefulSpirit.GetDamageMax() + 15);
        vengefulSpiritArr[i]->SetDefense(vengefulSpirit.GetDefense() + 1);
        vengefulSpiritArr[i]->SetLevel(vengefulSpirit.GetLevel() + 1);
        vengefulSpiritArr[i]->SetExperience(vengefulSpirit.GetExperience() + 40);
        vengefulSpiritArr[i]->SetHealth(vengefulSpirit.GetMaxHealth());
    }

    //Golems
    for(int i = 0; i < MAX_GOLEM_INSTANCES;i++)
    {
        golemArr[i]->SetMaxHealth(golem.GetMaxHealth() + 100);
        golemArr[i]->SetDamageMin(golem.GetDamageMin() + 3);
        golemArr[i]->SetDamageMax(golem.GetDamageMax() + 3);
        golemArr[i]->SetDefense(golem.GetDefense() + 5);
        golemArr[i]->SetLevel(golem.GetLevel() + 1);
        golemArr[i]->SetExperience(golem.GetExperience() + 35);
        golemArr[i]->SetHealth(golem.GetMaxHealth());
    }

    //snakes
    for(int i = 0; i < MAX_SNAKE_INSTANCES;i++)
    {
        snakeArr[i]->SetMaxHealth(orc.GetMaxHealth() + 60);
        snakeArr[i]->SetDamageMin(orc.GetDamageMin() + 8);
        snakeArr[i]->SetDamageMax(orc.GetDamageMax() + 10);
        snakeArr[i]->SetDefense(orc.GetDefense() + 2);
        snakeArr[i]->SetLevel(orc.GetLevel() + 1);
        snakeArr[i]->SetExperience(orc.GetExperience() + 35);
        snakeArr[i]->SetHealth(orc.GetMaxHealth());
    }

    //rats
    for(int i = 0; i < MAX_RAT_INSTANCES;i++)
    {
        ratArr[i]->SetMaxHealth(orc.GetMaxHealth() + 60);
        ratArr[i]->SetDamageMin(orc.GetDamageMin() + 8);
        ratArr[i]->SetDamageMax(orc.GetDamageMax() + 10);
        ratArr[i]->SetDefense(orc.GetDefense() + 2);
        ratArr[i]->SetLevel(orc.GetLevel() + 1);
        ratArr[i]->SetExperience(orc.GetExperience() + 35);
        ratArr[i]->SetHealth(orc.GetMaxHealth());
    }

    //The Crab
    for(int i = 0; i < MAX_CRAB_THING_INSTANCES;i++)
    {
        crabArr[i]->SetMaxHealth(crabThing.GetMaxHealth() + 70);
        crabArr[i]->SetDamageMin(crabThing.GetDamageMin() + 25);
        crabArr[i]->SetDamageMax(crabThing.GetDamageMax() + 30);
        crabArr[i]->SetDefense(crabThing.GetDefense() + 3);
        crabArr[i]->SetLevel(crabThing.GetLevel() + 2);
        crabArr[i]->SetExperience(crabThing.GetExperience() + 85);
        crabArr[i]->SetHealth(crabThing.GetMaxHealth());
    }
}

void ResetAllEnemies()
{
    for(int i = 0; i < MAX_ORCS_INSTANCES;i++)
    {
        orcArr[i]->SetAlive(true);
        orcArr[i]->SetHealth(orc.GetMaxHealth());
        orcArr[i]->Move(TILE_WIDTH * GetRandomValue(1,10), TILE_HEIGHT * GetRandomValue(1,14));
    }

    for(int i = 0; i < MAX_WANDERING_EYE_INSTANCES;i++)
    {
        eyeArr[i]->SetAlive(true);
        eyeArr[i]->SetHealth(wanderingEye.GetMaxHealth());
        eyeArr[i]->Move(TILE_WIDTH * GetRandomValue(1,10), TILE_HEIGHT * GetRandomValue(1,14));
    }

    for(int i = 0; i < MAX_TREANT_INSTANCES;i++)
    {
        treantArr[i]->SetAlive(true);
        treantArr[i]->SetHealth(treant.GetMaxHealth());
        treantArr[i]->Move(TILE_WIDTH * GetRandomValue(1,10), TILE_HEIGHT * GetRandomValue(1,14));
    }

    for(int i = 0; i < MAX_VENGEFUL_SPIRIT_INSTANCES;i++)
    {
        vengefulSpiritArr[i]->SetAlive(true);
        vengefulSpiritArr[i]->SetHealth(vengefulSpirit.GetMaxHealth());
        vengefulSpiritArr[i]->Move(TILE_WIDTH * GetRandomValue(1,10), TILE_HEIGHT * GetRandomValue(1,14));
    }

    for(int i = 0; i < MAX_GOLEM_INSTANCES;i++)
    {
        golemArr[i]->SetAlive(true);
        golemArr[i]->SetHealth(golem.GetMaxHealth());
        golemArr[i]->Move(TILE_WIDTH * GetRandomValue(1,10), TILE_HEIGHT * GetRandomValue(1,14));
    }

    for(int i = 0; i < MAX_SNAKE_INSTANCES;i++)
    {
        snakeArr[i]->SetAlive(true);
        snakeArr[i]->SetHealth(golem.GetMaxHealth());
        snakeArr[i]->Move(TILE_WIDTH * GetRandomValue(1,10), TILE_HEIGHT * GetRandomValue(1,14));
    }

    for(int i = 0; i < MAX_RAT_INSTANCES;i++)
    {
        ratArr[i]->SetAlive(true);
        ratArr[i]->SetHealth(golem.GetMaxHealth());
        ratArr[i]->Move(TILE_WIDTH * GetRandomValue(1,10), TILE_HEIGHT * GetRandomValue(1,14));
    }

    for(int i = 0; i < MAX_CRAB_THING_INSTANCES;i++)
    {
        crabArr[i]->SetAlive(true);
        crabArr[i]->SetHealth(crabThing.GetMaxHealth());
        crabArr[i]->Move(TILE_WIDTH * GetRandomValue(1,10), TILE_HEIGHT * GetRandomValue(1,14));
    }
}

void RenderGates()
{
    if(Player.GetZone() == ZONE_WORLD || Player.GetZone() == ZONE_DUNGEON) DrawTile(dungeon_gate.x, dungeon_gate.y, 8, 9); //dungeon gate
    if(Player.GetZone() == ZONE_DUNGEON || Player.GetZone() == ZONE_WORLD_PLAIN_LANDS) DrawTile(plainLands_gate.x, plainLands_gate.y, 7, 7); //plainsGate
    if(Player.GetZone() == ZONE_WORLD_PLAIN_LANDS || Player.GetZone() == ZONE_BASEMENT_DUNGEON) DrawTile(basementStairs.x, basementStairs.y, 4, 3); //BasementStairs
    if(Player.GetZone() == ZONE_BASEMENT_DUNGEON || Player.GetZone() == ZONE_ISLAND) DrawTile(ladderToIsland.x, ladderToIsland.y, 11, 5);  //LaddertoIsland

}

void RenderNPCs()
{
    if(Player.GetZone() == ZONE_WORLD ) DrawTile(oldHermit.x, oldHermit.y, 14, 0); //Old Hermit
    
    if(Player.GetZone() == ZONE_WORLD ) DrawTile(woundedKnight.x, woundedKnight.y, 5, 0); //Wounded Knight

    if(Player.GetZone() == ZONE_WORLD_PLAIN_LANDS ) DrawTile(villager1.x, villager1.y, 4, 0); //villager1

    if(Player.GetZone() == ZONE_WORLD_PLAIN_LANDS ) DrawTile(villager2.x, villager2.y, 7, 0); //Wounded Knight

    if(Player.GetZone() == ZONE_BASEMENT_DUNGEON) DrawTile(basementLockedDoor.x, basementLockedDoor.y, 7, 2); //Wounded Knight


}

void RenderBoat()
{
    if(Player.GetZone() == boat.zone1 && !isRidingBoat)
    {
        DrawTexture(textures[TEXTURE_BOAT_RIGHT], boat.x, boat.y, WHITE);
    }
}

void spawnChest(Enemy *enemy)
{   
    for(int i = 0; i < MAX_CHEST_INSTANCES; i++)
    {
       if(chestArr[i] == nullptr) chestArr[i] = new sEntity(chest);

        if(!chestArr[i]->isAlive && chestArr[i] != nullptr)
        {
            chestArr[i]->x = enemy->GetX();
            chestArr[i]->y = enemy->GetY();
            chestArr[i]->isAlive = true;
            chestArr[i]->money = GetRandomValue(23, 205);
            chestArr[i]->healthPotions = GetRandomValue(1,4);
            chestArr[i]->energyFoods = GetRandomValue(0,3);
            chestArr[i]->zone1 = enemy->GetZone();
            chestIsPresent = true;
            return;
        }
    }

}

void CheckContactWithEnemies()
{

    //check contact with orc
    for(int i = 0; i < MAX_ORCS_INSTANCES; i++)
    {
        if (orcArr[i] != nullptr && Player.GetZone() == orcArr[i]->GetZone() && Player.GetX() == orcArr[i]->GetX() && Player.GetY() == orcArr[i]->GetY() && orcArr[i]->IsAlive() == true) 
        {
            enemy = orcArr[i];
            battleMode = true;
        }
    }

    //check contact with Eye
    for(int i = 0; i < MAX_WANDERING_EYE_INSTANCES; i++)
    {
        if (eyeArr[i] != nullptr && Player.GetZone() == eyeArr[i]->GetZone() && Player.GetX() == eyeArr[i]->GetX() && Player.GetY() == eyeArr[i]->GetY() && eyeArr[i]->IsAlive() == true) 
        {
            enemy = eyeArr[i];
            battleMode = true;
        }
    }

     //check contact with Treant
    for(int i = 0; i < MAX_TREANT_INSTANCES; i++)
    {
        if (treantArr[i] != nullptr && Player.GetZone() == treantArr[i]->GetZone() && Player.GetX() == treantArr[i]->GetX() && Player.GetY() == treantArr[i]->GetY() && treantArr[i]->IsAlive() == true) 
        {
            enemy = treantArr[i];
            battleMode = true;
        }
    }

      //check contact with Vengful Spirit
    for(int i = 0; i < MAX_VENGEFUL_SPIRIT_INSTANCES; i++)
    {
        if (vengefulSpiritArr[i] != nullptr && Player.GetZone() == vengefulSpiritArr[i]->GetZone() && Player.GetX() == vengefulSpiritArr[i]->GetX() && Player.GetY() == vengefulSpiritArr[i]->GetY() && vengefulSpiritArr[i]->IsAlive() == true) 
        {
            enemy = vengefulSpiritArr[i];
            battleMode = true;
        }
    }

      //check contact with Golem
    for(int i = 0; i < MAX_GOLEM_INSTANCES; i++)
    {
        if (golemArr[i] != nullptr && Player.GetZone() == golemArr[i]->GetZone() && Player.GetX() == golemArr[i]->GetX() && Player.GetY() == golemArr[i]->GetY() && golemArr[i]->IsAlive() == true) 
        {
            enemy = golemArr[i];
            battleMode = true;
        }
    }

    //check contact with Snakes
    for(int i = 0; i < MAX_SNAKE_INSTANCES; i++)
    {
        if (snakeArr[i] != nullptr && Player.GetZone() == snakeArr[i]->GetZone() && Player.GetX() == snakeArr[i]->GetX() && Player.GetY() == snakeArr[i]->GetY() && snakeArr[i]->IsAlive() == true) 
        {
            enemy = snakeArr[i];
            battleMode = true;
        }
    }

      //check contact with Crab
    for(int i = 0; i < MAX_CRAB_THING_INSTANCES; i++)
    {
        if (crabArr[i] != nullptr && Player.GetZone() == crabArr[i]->GetZone() && Player.GetX() == crabArr[i]->GetX() && Player.GetY() == crabArr[i]->GetY() && crabArr[i]->IsAlive() == true) 
        {
            enemy = crabArr[i];
            battleMode = true;
        }
    }

      //check contact with Rat
    for(int i = 0; i < MAX_RAT_INSTANCES; i++)
    {
        if (ratArr[i] != nullptr && Player.GetZone() == ratArr[i]->GetZone() && Player.GetX() == ratArr[i]->GetX() && Player.GetY() == ratArr[i]->GetY() && ratArr[i]->IsAlive() == true) 
        {
            enemy = ratArr[i];
            battleMode = true;
        }
    }

    for(int i = 0; i < MAX_MUTATED_FROG_INSTANCES; i++) //check contact with Frog
    {
        if (mutantFrogArr[i] != nullptr && Player.GetZone() == mutantFrogArr[i]->GetZone() && Player.GetX() == mutantFrogArr[i]->GetX() && Player.GetY() == mutantFrogArr[i]->GetY() && mutantFrogArr[i]->IsAlive() == true) 
        {
            enemy = mutantFrogArr[i];
            battleMode = true;
        }
    }

    for(int i = 0; i < MAX_SLIME_INSTANCES; i++)  //check contact with SLime
    {
        if (slimeArr[i] != nullptr && Player.GetZone() == slimeArr[i]->GetZone() && Player.GetX() == slimeArr[i]->GetX() && Player.GetY() == slimeArr[i]->GetY() && slimeArr[i]->IsAlive() == true) 
        {
            enemy = slimeArr[i];
            battleMode = true;
        }
    }

    for(int i = 0; i < MAX_DOG_INSTANCES; i++) //check contact with Dog
    {
        if (dogArr[i] != nullptr && Player.GetZone() == dogArr[i]->GetZone() && Player.GetX() == dogArr[i]->GetX() && Player.GetY() == dogArr[i]->GetY() && dogArr[i]->IsAlive() == true) 
        {
            enemy = dogArr[i];
            battleMode = true;
        }
    }

    for(int i = 0; i < MAX_FLOATING_CRAB_INSTANCES; i++) //check contact with Floating Crab
    {
        if (floatingCrabArr[i] != nullptr && Player.GetZone() == floatingCrabArr[i]->GetZone() && Player.GetX() == floatingCrabArr[i]->GetX() && Player.GetY() == floatingCrabArr[i]->GetY() && floatingCrabArr[i]->IsAlive() == true) 
        {
            enemy = floatingCrabArr[i];
            battleMode = true;
        }
    }

}

void ExecuteEnemyBehaviors()
{
    
    for(int i = 0; i < MAX_ORCS_INSTANCES; i++) 
    {
        if(!orcArr[i]->GetStunStatus()) 
        {
            orcArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            orcArr[i]->SetStunCounter(count);
            if(count > 3) 
            {
                orcArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(orcArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }
    
    for(int i = 0; i < MAX_WANDERING_EYE_INSTANCES; i++) 
    {
        if(!eyeArr[i]->GetStunStatus()) 
        {
            eyeArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            eyeArr[i]->SetStunCounter(count);
            if(count > 3) 
            {
                eyeArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(eyeArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    for(int i = 0; i < MAX_TREANT_INSTANCES; i++) 
    {
        if(!treantArr[i]->GetStunStatus()) 
        {
            treantArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            treantArr[i]->SetStunCounter(count);
            if(count > 3) 
            {
                treantArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(treantArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    for(int i = 0; i < MAX_VENGEFUL_SPIRIT_INSTANCES; i++) 
    {
        if(!vengefulSpiritArr[i]->GetStunStatus()) 
        {
            vengefulSpiritArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            vengefulSpiritArr[i]->SetStunCounter(count);
            if(count > 2) 
            {
                vengefulSpiritArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(vengefulSpiritArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    for(int i = 0; i < MAX_SNAKE_INSTANCES; i++) 
    {
        if(!snakeArr[i]->GetStunStatus()) 
        {
            snakeArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            snakeArr[i]->SetStunCounter(count);
            if(count > 5) 
            {
                snakeArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(snakeArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    for(int i = 0; i < MAX_RAT_INSTANCES; i++) 
    {
        if(!ratArr[i]->GetStunStatus()) 
        {
            ratArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            ratArr[i]->SetStunCounter(count);
            if(count > 3) 
            {
                ratArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(ratArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }
    
    //golem does not move or rarely moves (WIP)

    for(int i = 0; i < MAX_CRAB_THING_INSTANCES; i++) 
    {
        if(!crabArr[i]->GetStunStatus()) 
        {
            crabArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            crabArr[i]->SetStunCounter(count);
            if(count > 3) 
            {
                crabArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(crabArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    for(int i = 0; i < MAX_SLIME_INSTANCES; i++) 
    {
        if(!slimeArr[i]->GetStunStatus()) 
        {
            slimeArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            slimeArr[i]->SetStunCounter(count);
            if(count > 3) 
            {
                slimeArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(slimeArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    for(int i = 0; i < MAX_DOG_INSTANCES; i++) 
    {
        if(!dogArr[i]->GetStunStatus()) 
        {
            dogArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            dogArr[i]->SetStunCounter(count);
            if(count > 3) 
            {
                dogArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(dogArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    for(int i = 0; i < MAX_FLOATING_CRAB_INSTANCES; i++) 
    {
        if(!floatingCrabArr[i]->GetStunStatus()) 
        {
            floatingCrabArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            floatingCrabArr[i]->SetStunCounter(count);
            if(count > 3) 
            {
                floatingCrabArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(floatingCrabArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    
}



