#include "Entities.hpp"
#include "GameFunctions.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include "MusicFunctions.hpp"
#include "GameMenu.hpp"
#include "Items.hpp"
#include "StoryLine.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>

sEntity dungeon_gate, plainLands_gate, basementStairs, ladderToIsland, seaExtensionEntrance, lostTempleEntrance, 
          lostTempleStairsToLevel1, lostTempleStairsToLevel2;
sEntity oldHermit, woundedKnight, villager1, villager2, basementLockedDoor, weirdMan, islander;
sEntity randomTrinket;
sEntity boat;
int levelCap = 100;
bool playerLeveledUp = false;
bool chestIsPresent = false;


//Init enemies
Enemy orc(
    Enemy::ORC, "Orc", // id, name
    TILE_WIDTH * 5, TILE_HEIGHT * 5, //spawn pos
    200, ZONE_WORLD_PLAIN_LANDS, 40, 60, 20, //maxhp, zone, dmgMin, dmgMax, def
    180, 3, "Intelligence", false, 200, 700 // exp, level, weakness, special Status, moneyMin, moneyMax
);

Enemy wanderingEye(
    Enemy::WANDERING_EYE, "Wandering Eye",
    TILE_WIDTH * 10, TILE_HEIGHT * 20,
    240, ZONE_WORLD_PLAIN_LANDS, 50, 70, 12,
    215, 3, "Strenght", false , 300, 850
);

Enemy treant(
    Enemy::TREANT, "Treant",
    TILE_WIDTH * 5, TILE_HEIGHT * 8,
    190, ZONE_WORLD, 10, 80, 11,
    180, 3, "Dexterity", false, 150, 300
);

Enemy vengefulSpirit(
    Enemy::VENGEFUL_SPIRIT, "Vengeful Spirit",
    TILE_WIDTH * 1, TILE_HEIGHT * 1,
    100, ZONE_DUNGEON, 45, 50, 8,
    160, 2, "Intelligence", false, 450, 550
);

Enemy golem(
    Enemy::GOLEM, "Golem",
    TILE_WIDTH * 2, TILE_HEIGHT * 2,
    250, ZONE_DUNGEON, 18, 28, 25,
    200, 4, "Strenght", false, 350, 600
);

Enemy snake(
    Enemy::SNAKE, "Snake",
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    100, ZONE_WORLD, 25, 45, 10,
    125, 1, "Strenght", false, 200, 400
);

Enemy dog(
    Enemy::DOG, "Dog",
    TILE_WIDTH * 3, TILE_HEIGHT * 4,
    190, ZONE_BASEMENT_DUNGEON, 70, 90, 19,
    260, 5, "Dexterity", false, 500, 1000
);

Enemy rat(
    Enemy::RAT, "Rat",
    TILE_WIDTH * 3, TILE_HEIGHT * 5,
    80, ZONE_DUNGEON, 25, 45, 8,
    120, 2, "Intelligence", false, 280, 670
);

Enemy slime(
    Enemy::SLIME, "Slime",
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    240, ZONE_BASEMENT_DUNGEON, 54, 83, 20,
    230, 4, "Intelligence", false, 700, 1200
);

Enemy floatingCrab(
    Enemy::FLOATING_CRAB, "Floating Crab",
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    300, ZONE_ISLAND, 68, 101, 25,
    300, 5, "Dexterity", false, 800, 1400
);

Enemy waterSlime(
    Enemy::WATER_SLIME, "Water Slime",
    TILE_WIDTH * 3, TILE_HEIGHT * 3,
    450, ZONE_SEA, 48, 90, 30,
    400, 6, "Intelligence", false, 1000, 2000
);

//bosses | special
Enemy crabThing(
    Enemy::CRAB_THING, "The Crab Thing",
    TILE_WIDTH * 1, TILE_HEIGHT * 5,
    150, ZONE_WORLD, 30, 50, 15,
    240, 6, "NULL", true, 1800, 2000
);

Enemy monsterSquid(
    Enemy::MONSTER_SQUID, "The Great Monster Squid",
    TILE_WIDTH * 2, TILE_HEIGHT * 5,
    550, ZONE_SEA, 78, 100, 35,
    550, 7, "NULL", true, 4500, 5000
);

Enemy mutatedFrog(
    Enemy::MUTATED_FROG, "The Mutant Frog | 0-02",
    TILE_WIDTH * 2, TILE_HEIGHT * 5,
    300, ZONE_WORLD_PLAIN_LANDS, 50, 90, 30,
    510, 8, "NULL", true, 3500, 4000
);

Enemy guardian(
    Enemy::GAURDIAN, "The Guardian",
    TILE_WIDTH * 2, TILE_HEIGHT * 5,
    1000, ZONE_WORLD_PLAIN_LANDS, 10, 400, 45,
    999, 100, "NULL", true, 9000, 10000
);

Enemy specialGolem(
    Enemy::SPECIAL_GOLEM, "Golem Knight",
    TILE_WIDTH * 2, TILE_HEIGHT * 5,
    300, ZONE_LOST_TEMPLE_LEVEL1, 100, 150, 55,
    790, 14, "NULL", true, 4000, 5000
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
Enemy* vengefulSpirit3 = nullptr;
Enemy* vengefulSpirit4 = nullptr;

Enemy* golem1 = nullptr;
Enemy* golem2 = nullptr;
Enemy* golem3 = nullptr;
Enemy* golem4 = nullptr;
Enemy* golem5 = nullptr;
Enemy* golem6 = nullptr;
Enemy* golem7 = nullptr;
Enemy* golem8 = nullptr;

Enemy* snake1 = nullptr;
Enemy* snake2 = nullptr;
Enemy* snake3 = nullptr;
Enemy* snake4 = nullptr;

Enemy* dog1 = nullptr;
Enemy* dog2 = nullptr;
Enemy* dog3 = nullptr;

Enemy* rat1 = nullptr;
Enemy* rat2 = nullptr;
Enemy* rat3 = nullptr;
Enemy* rat4 = nullptr;
Enemy* rat5 = nullptr;

Enemy* slime1 = nullptr;
Enemy* slime2 = nullptr;
Enemy* slime3 = nullptr;
Enemy* slime4 = nullptr;
Enemy* slime5 = nullptr;
Enemy* slime6 = nullptr;
Enemy* slime7 = nullptr;

Enemy* floatingCrab1 = nullptr;
Enemy* floatingCrab2 = nullptr; 
Enemy* floatingCrab3 = nullptr;
Enemy* floatingCrab4 = nullptr;
Enemy* floatingCrab5 = nullptr;
Enemy* floatingCrab6 = nullptr;
Enemy* floatingCrab7 = nullptr;
Enemy* floatingCrab8 = nullptr;
Enemy* floatingCrab9 = nullptr;

Enemy* waterSlime1 = nullptr;
Enemy* waterSlime2 = nullptr;
Enemy* waterSlime3 = nullptr;
Enemy* waterSlime4 = nullptr;
Enemy* waterSlime5 = nullptr;
Enemy* waterSlime6 = nullptr;

Enemy* crabThing1 = nullptr;
Enemy* crabThing2 = nullptr;
Enemy* crabThing3 = nullptr;

Enemy* monsterSquid1 = nullptr;
Enemy* monsterSquid2 = nullptr;
Enemy* monsterSquid3 = nullptr;

Enemy* mutatedFrog1 = nullptr;
Enemy* mutatedFrog2 = nullptr;
Enemy* mutatedFrog3 = nullptr;

Enemy* specialGolem1 = nullptr;
Enemy* specialGolem2 = nullptr;
Enemy* specialGolem3 = nullptr;

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
Enemy* waterSlimeArr[MAX_WATER_SLIME_INSTANCES];

Enemy* crabArr[MAX_CRAB_THING_INSTANCES];
Enemy* squidArr[MAX_MONSTER_SQUID_INSTANCES];
Enemy* mutantFrogArr[MAX_MUTATED_FROG_INSTANCES];
Enemy* guardianArr[MAX_GUARDIAN_INSTANCES];
Enemy* specialGolemArr[MAX_SPECIAL_GOLEM_INSTANCES];

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
        .x = TILE_WIDTH * 15, // 15
        .y = TILE_HEIGHT * 17, // 17
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

    seaExtensionEntrance = (sEntity) 
    {
        .x = TILE_WIDTH * 0,
        .y = TILE_HEIGHT * 11,

        .x2 = TILE_WIDTH * 24,
        .y2 = TILE_HEIGHT * 11,
        .zone1 = ZONE_ISLAND,
        .zone2 = ZONE_SEA
    };

    lostTempleEntrance = (sEntity) 
    {
        .x = TILE_WIDTH * 24,
        .y = TILE_HEIGHT * 11,

        .x2 = TILE_WIDTH * 0,
        .y2 = TILE_HEIGHT * 11,
        .zone1 = ZONE_ISLAND,
        .zone2 = ZONE_LOST_TEMPLE_ENTRANCE
    };

    lostTempleStairsToLevel1 = (sEntity) 
    {
        .x = TILE_WIDTH * 18,
        .y = TILE_HEIGHT * 10,

        .x2 = TILE_WIDTH * 1,
        .y2 = TILE_HEIGHT * 4,
        .zone1 = ZONE_LOST_TEMPLE_ENTRANCE,
        .zone2 = ZONE_LOST_TEMPLE_LEVEL1
    };

    lostTempleStairsToLevel2 = (sEntity) 
    {
        .x = TILE_WIDTH * 12,
        .y = TILE_HEIGHT * 13,

        .x2 = TILE_WIDTH * 23,
        .y2 = TILE_HEIGHT * 1,
        .zone1 = ZONE_LOST_TEMPLE_LEVEL1,
        .zone2 = ZONE_LOST_TEMPLE_LEVEL2
    };


    //NPCs - Zone1
    oldHermit = (sEntity)
    {
        .x = TILE_WIDTH * 11,
        .y = TILE_HEIGHT * 3,
        .x2 = TILE_WIDTH * 8,
        .y2 = TILE_HEIGHT * 8,

        .zone1 = ZONE_WORLD,
        .zone2 = ZONE_LOST_TEMPLE_ENTRANCE,
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

    //ZONE2 Plains
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

    weirdMan = (sEntity)
    {
        .x = TILE_WIDTH * 20,
        .y = TILE_HEIGHT * 4,
        .x2 = TILE_WIDTH * 5,
        .y2 = TILE_HEIGHT * 6,

        .zone1 = ZONE_BASEMENT_DUNGEON,
        .zone2 = ZONE_LOST_TEMPLE_LEVEL2,
        .isPassable = false
    };

    //Island
    islander = (sEntity)
    {
        .x = TILE_WIDTH * 3,
        .y = TILE_HEIGHT * 21,
        .zone1 = ZONE_ISLAND,
        .zone2 = ZONE_ISLAND,
        .isPassable = false
    };

    randomTrinket = (sEntity)
    {
        .x = TILE_WIDTH * 22,
        .y = TILE_HEIGHT * 2,
        .zone1 = ZONE_ISLAND,
        .zone2 = ZONE_ISLAND,
        .isPassable = false
    };

    // BUG FIX: Initialize the boat only once to prevent its position from resetting.
    static bool boatIsInitialized = false;
    if (!boatIsInitialized)
    {
        boat = (sEntity)
        {
            .x = TILE_WIDTH * 14,
            .y = TILE_HEIGHT * 12,
            .zone1 = ZONE_ISLAND,
            .zone2 = ZONE_ISLAND, 
            .isPassable = false 
        };
        boatIsInitialized = true;
    }


    //Place enemy instances (TO BE OPTIMIZED)

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

    floatingCrab8 = new Enemy(floatingCrab);
    floatingCrab8->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    //sea
    monsterSquid1 = new Enemy(monsterSquid);
    monsterSquid1->Move(TILE_WIDTH * 7, TILE_HEIGHT * 9);

    floatingCrab5 = new Enemy(floatingCrab);
    floatingCrab5->SetZone(ZONE_SEA);
    floatingCrab5->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    floatingCrab6 = new Enemy(floatingCrab);
    floatingCrab6->SetZone(ZONE_SEA);
    floatingCrab6->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    floatingCrab7 = new Enemy(floatingCrab);
    floatingCrab7->SetZone(ZONE_SEA);
    floatingCrab7->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    floatingCrab9 = new Enemy(floatingCrab);
    floatingCrab9->SetZone(ZONE_SEA);
    floatingCrab9->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));


    waterSlime1 = new Enemy(waterSlime);
    waterSlime1->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    waterSlime2 = new Enemy(waterSlime);
    waterSlime2->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    waterSlime3 = new Enemy(waterSlime);
    waterSlime3->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    waterSlime4 = new Enemy(waterSlime);
    waterSlime4->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    waterSlime5 = new Enemy(waterSlime);
    waterSlime5->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    waterSlime6 = new Enemy(waterSlime);
    waterSlime6->Move(TILE_WIDTH * GetRandomValue(1,23), TILE_HEIGHT * GetRandomValue(1,23));

    //lost Temple
    golem3 = new Enemy(golem);
    golem3->SetZone(ZONE_LOST_TEMPLE_ENTRANCE);
    golem3->Move(TILE_WIDTH * 15, TILE_HEIGHT * 10);
    golem3->SetHealth(500); 
    golem3->SetMaxHealth(500);
    golem3->SetDamageMin(100);
    golem3->SetDamageMax(150);
    golem3->SetDefense(40);

    golem4 = new Enemy(golem);
    golem4->SetZone(ZONE_LOST_TEMPLE_ENTRANCE);
    golem4->Move(TILE_WIDTH * 16, TILE_HEIGHT * 10);
    golem4->SetHealth(500);
    golem4->SetMaxHealth(500);
    golem4->SetDamageMin(100);
    golem4->SetDamageMax(150);
    golem4->SetDefense(40);

    golem5 = new Enemy(golem);
    golem5->SetZone(ZONE_LOST_TEMPLE_ENTRANCE);
    golem5->Move(TILE_WIDTH * 17, TILE_HEIGHT * 10);
    golem5->SetHealth(500);
    golem5->SetMaxHealth(500);
    golem5->SetDamageMin(100);
    golem5->SetDamageMax(150);
    golem5->SetDefense(40);

    vengefulSpirit3 = new Enemy(vengefulSpirit);
    vengefulSpirit3->SetZone(ZONE_LOST_TEMPLE_ENTRANCE);
    vengefulSpirit3->Move(TILE_WIDTH * 18, TILE_HEIGHT * 8);
    vengefulSpirit3->SetHealth(200);
    vengefulSpirit3->SetMaxHealth(200);
    vengefulSpirit3->SetDamageMin(160);
    vengefulSpirit3->SetDamageMax(200);
    vengefulSpirit3->SetDefense(25);

    vengefulSpirit4 = new Enemy(vengefulSpirit);
    vengefulSpirit4->SetZone(ZONE_LOST_TEMPLE_ENTRANCE);
    vengefulSpirit4->Move(TILE_WIDTH * 18, TILE_HEIGHT * 12);
    vengefulSpirit4->SetHealth(200);
    vengefulSpirit4->SetMaxHealth(200);
    vengefulSpirit4->SetDamageMin(160);
    vengefulSpirit4->SetDamageMax(200);
    vengefulSpirit4->SetDefense(25);

    //templeLevel1
    specialGolem1 = new Enemy(specialGolem);
    specialGolem1->Move(TILE_WIDTH * 11, TILE_HEIGHT * 12);

    golem6 = new Enemy(golem);
    golem6->SetZone(ZONE_LOST_TEMPLE_LEVEL1);
    golem6->Move(TILE_WIDTH * GetRandomValue(1,24), TILE_HEIGHT * GetRandomValue(1,24));
    golem6->SetHealth(500);
    golem6->SetMaxHealth(500);
    golem6->SetDamageMin(170);
    golem6->SetDamageMax(230);
    golem6->SetDefense(60);
    golem6->SetExperience(800);

    golem7 = new Enemy(golem);
    golem7->SetZone(ZONE_LOST_TEMPLE_LEVEL1);
    golem7->Move(TILE_WIDTH * GetRandomValue(1,24), TILE_HEIGHT * GetRandomValue(1,24));
    golem7->SetHealth(500);
    golem7->SetMaxHealth(500);
    golem7->SetDamageMin(170);
    golem7->SetDamageMax(230);
    golem7->SetDefense(60);
    golem7->SetExperience(800);

    golem8 = new Enemy(golem);
    golem8->SetZone(ZONE_LOST_TEMPLE_LEVEL1);
    golem8->Move(TILE_WIDTH * GetRandomValue(1,24), TILE_HEIGHT * GetRandomValue(1,24));
    golem8->SetHealth(500);
    golem8->SetMaxHealth(500);
    golem8->SetDamageMin(170);
    golem8->SetDamageMax(230);
    golem8->SetDefense(60);
    golem8->SetExperience(800);


    rat3 = new Enemy(rat);
    rat3->SetZone(ZONE_LOST_TEMPLE_LEVEL1);
    rat3->Move(TILE_WIDTH * GetRandomValue(1,24), TILE_HEIGHT * GetRandomValue(1,24));
    rat3->SetHealth(200);
    rat3->SetMaxHealth(200);
    rat3->SetDamageMin(100);
    rat3->SetDamageMax(180);
    rat3->SetDefense(40);
    rat3->SetExperience(500);

    rat4 = new Enemy(rat);
    rat4->SetZone(ZONE_LOST_TEMPLE_LEVEL1);
    rat4->Move(TILE_WIDTH * GetRandomValue(1,24), TILE_HEIGHT * GetRandomValue(1,24));
    rat4->SetHealth(200);
    rat4->SetMaxHealth(200);
    rat4->SetDamageMin(100);
    rat4->SetDamageMax(180);
    rat4->SetDefense(40);
    rat4->SetExperience(500);

    rat5 = new Enemy(rat);
    rat5->SetZone(ZONE_LOST_TEMPLE_LEVEL1);
    rat5->Move(TILE_WIDTH * GetRandomValue(1,24), TILE_HEIGHT * GetRandomValue(1,24));
    rat5->SetHealth(200);
    rat5->SetMaxHealth(200);
    rat5->SetDamageMin(100);
    rat5->SetDamageMax(180);
    rat5->SetDefense(40);
    rat5->SetExperience(500);

    slime5 = new Enemy(slime);
    slime5->SetZone(ZONE_LOST_TEMPLE_LEVEL1);
    slime5->Move(TILE_WIDTH * GetRandomValue(1,24), TILE_HEIGHT * GetRandomValue(1,24));
    slime5->SetHealth(350);
    slime5->SetMaxHealth(350);
    slime5->SetDamageMin(240);
    slime5->SetDamageMax(300);
    slime5->SetDefense(50);
    slime5->SetExperience(700);

    slime6 = new Enemy(slime);
    slime6->SetZone(ZONE_LOST_TEMPLE_LEVEL1);
    slime6->Move(TILE_WIDTH * GetRandomValue(1,24), TILE_HEIGHT * GetRandomValue(1,24));
    slime6->SetHealth(350);
    slime6->SetMaxHealth(350);
    slime6->SetDamageMin(240);
    slime6->SetDamageMax(300);
    slime6->SetDefense(50);
    slime6->SetExperience(700);

    slime7 = new Enemy(slime);
    slime7->SetZone(ZONE_LOST_TEMPLE_LEVEL1);
    slime7->Move(TILE_WIDTH * GetRandomValue(1,24), TILE_HEIGHT * GetRandomValue(1,24));
    slime7->SetHealth(350);
    slime7->SetMaxHealth(350);
    slime7->SetDamageMin(240);
    slime7->SetDamageMax(300);
    slime7->SetDefense(50);
    slime7->SetExperience(700);

    //Bad Ending
    guardian1 = new Enemy(guardian);
    guardian1->SetZone(ZONE_LOST_TEMPLE_BAD_ENDING);
    guardian1->Move(TILE_WIDTH * 19, TILE_HEIGHT * 7);

    crabThing2 = new Enemy(crabThing);
    crabThing2->Move(TILE_WIDTH * 18, TILE_HEIGHT * 6);
    crabThing2->SetZone(ZONE_LOST_TEMPLE_BAD_ENDING);
    crabThing2->SetHealth(400);
    crabThing2->SetMaxHealth(400);
    crabThing2->SetDamageMin(170);
    crabThing2->SetDamageMax(220);
    crabThing2->SetDefense(50);

    crabThing3 = new Enemy(crabThing);
    crabThing3->Move(TILE_WIDTH * 18, TILE_HEIGHT * 5);
    crabThing3->SetZone(ZONE_LOST_TEMPLE_BAD_ENDING);
    crabThing3->SetHealth(400);
    crabThing3->SetMaxHealth(400);
    crabThing3->SetDamageMin(170);
    crabThing3->SetDamageMax(220);
    crabThing3->SetDefense(50);

    monsterSquid2 = new Enemy(monsterSquid);
    monsterSquid2->Move(TILE_WIDTH * 16, TILE_HEIGHT * 6);
    monsterSquid2->SetZone(ZONE_LOST_TEMPLE_BAD_ENDING);
    monsterSquid2->SetHealth(800);
    monsterSquid2->SetMaxHealth(800);
    monsterSquid2->SetDamageMin(300);
    monsterSquid2->SetDamageMax(400);
    monsterSquid2->SetDefense(70);

    monsterSquid3 = new Enemy(monsterSquid);
    monsterSquid3->Move(TILE_WIDTH * 16, TILE_HEIGHT * 5);
    monsterSquid3->SetZone(ZONE_LOST_TEMPLE_BAD_ENDING);
    monsterSquid3->SetHealth(800);
    monsterSquid3->SetMaxHealth(800);
    monsterSquid3->SetDamageMin(300);
    monsterSquid3->SetDamageMax(400);
    monsterSquid3->SetDefense(70);

    specialGolem2 = new Enemy(specialGolem);
    specialGolem2->Move(TILE_WIDTH * 14, TILE_HEIGHT * 6);
    specialGolem2->SetZone(ZONE_LOST_TEMPLE_BAD_ENDING);
    specialGolem2->SetHealth(1500);
    specialGolem2->SetMaxHealth(1500);
    specialGolem2->SetDamageMin(400);
    specialGolem2->SetDamageMax(600);
    specialGolem2->SetDefense(100);
    specialGolem2->SetExperience(2000);

    specialGolem3 = new Enemy(specialGolem);
    specialGolem3->Move(TILE_WIDTH * 14, TILE_HEIGHT * 5  );
    specialGolem3->SetZone(ZONE_LOST_TEMPLE_BAD_ENDING);
    specialGolem3->SetHealth(1500);
    specialGolem3->SetMaxHealth(1500);
    specialGolem3->SetDamageMin(400);
    specialGolem3->SetDamageMax(600);
    specialGolem3->SetDefense(100);
    specialGolem3->SetExperience(2000);

    mutatedFrog2 = new Enemy(mutatedFrog);
    mutatedFrog2->Move(TILE_WIDTH * 12, TILE_HEIGHT * 6);
    mutatedFrog2->SetZone(ZONE_LOST_TEMPLE_BAD_ENDING);
    mutatedFrog2->SetHealth(600);
    mutatedFrog2->SetMaxHealth(600);
    mutatedFrog2->SetDamageMin(250);
    mutatedFrog2->SetDamageMax(350);
    mutatedFrog2->SetDefense(80);
    mutatedFrog2->SetExperience(1500);

    mutatedFrog3 = new Enemy(mutatedFrog);
    mutatedFrog3->Move(TILE_WIDTH * 12, TILE_HEIGHT * 5);
    mutatedFrog3->SetZone(ZONE_LOST_TEMPLE_BAD_ENDING);
    mutatedFrog3->SetHealth(600);
    mutatedFrog3->SetMaxHealth(600);
    mutatedFrog3->SetDamageMin(250);
    mutatedFrog3->SetDamageMax(350);
    mutatedFrog3->SetDefense(80);
    mutatedFrog3->SetExperience(1500);

    //Good Ending


    //array of enemies (TO BE OPTIMIZED)
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
    vengefulSpiritArr[2] = vengefulSpirit3;
    vengefulSpiritArr[3] = vengefulSpirit4;

    golemArr[0] = golem1;
    golemArr[1] = golem2;
    golemArr[2] = golem3;
    golemArr[3] = golem4;
    golemArr[4] = golem5;
    golemArr[5] = golem6;
    golemArr[6] = golem7;
    golemArr[7] = golem8;

    snakeArr[0] = snake1;
    snakeArr[1] = snake2;
    snakeArr[2] = snake3;
    snakeArr[3] = snake4;

    ratArr[0] = rat1;
    ratArr[1] = rat2;
    ratArr[2] = rat3;
    ratArr[3] = rat4;
    ratArr[4] = rat5;

    slimeArr[0] = slime1;
    slimeArr[1] = slime2;
    slimeArr[2] = slime3;
    slimeArr[3] = slime4;
    slimeArr[4] = slime5;
    slimeArr[5] = slime6;
    slimeArr[6] = slime7;

    dogArr[0] = dog1;
    dogArr[1] = dog2;
    dogArr[2] = dog3;

    floatingCrabArr[0] = floatingCrab1;
    floatingCrabArr[1] = floatingCrab2;
    floatingCrabArr[2] = floatingCrab3;
    floatingCrabArr[3] = floatingCrab4;
    floatingCrabArr[4] = floatingCrab5;
    floatingCrabArr[5] = floatingCrab6;
    floatingCrabArr[6] = floatingCrab7;
    floatingCrabArr[7] = floatingCrab8;
    floatingCrabArr[8] = floatingCrab9;

    waterSlimeArr[0] = waterSlime1;
    waterSlimeArr[1] = waterSlime2;
    waterSlimeArr[2] = waterSlime3;
    waterSlimeArr[3] = waterSlime4;
    waterSlimeArr[4] = waterSlime5;
    waterSlimeArr[5] = waterSlime6;

    crabArr[0] = crabThing1;
    crabArr[1] = crabThing2;
    crabArr[2] = crabThing3;

    mutantFrogArr[0] = mutatedFrog1;
    mutantFrogArr[1] = mutatedFrog2;
    mutantFrogArr[2] = mutatedFrog3;

    squidArr[0] = monsterSquid1;
    squidArr[1] = monsterSquid2;
    squidArr[2] = monsterSquid3;

    specialGolemArr[0] = specialGolem1;
    specialGolemArr[1] = specialGolem2;
    specialGolemArr[2] = specialGolem3;

    guardianArr[0] = guardian1;

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

    for(int i = 0; i < MAX_MONSTER_SQUID_INSTANCES; i++)
    {
        if(squidArr[i]->GetZone() == Player.GetZone())
        {
            if(squidArr[i]->IsAlive() == true) 
            {
                DrawTexture(textures[TEXTURE_MONSTER_SQUID], squidArr[i]->GetX(), squidArr[i]->GetY(), WHITE);
            }
        }   
    }

    for(int i = 0; i < MAX_WATER_SLIME_INSTANCES; i++)
    {
        if(waterSlimeArr[i]->GetZone() == Player.GetZone())
        {
            if(waterSlimeArr[i]->IsAlive() == true) 
            {
                DrawTexture(textures[TEXTURE_WATER_SLIME], waterSlimeArr[i]->GetX(), waterSlimeArr[i]->GetY(), WHITE);
            }
        }   
    }

    for(int i = 0; i < MAX_SPECIAL_GOLEM_INSTANCES; i++)
    {
        if(specialGolemArr[i]->GetZone() == Player.GetZone())
        {
            if(specialGolemArr[i]->IsAlive() == true) 
            {
                DrawTexture(textures[TEXTURE_SPECIAL_GOLEM], specialGolemArr[i]->GetX(), specialGolemArr[i]->GetY(), WHITE);
            }
        }   
    }

    for(int i = 0; i < MAX_GUARDIAN_INSTANCES; i++)
    {
        if(guardianArr[i]->GetZone() == Player.GetZone())
        {
            if(guardianArr[i]->IsAlive() == true) 
            {
                DrawTile(guardianArr[i]->GetX(), guardianArr[i]->GetY(), 10, 2); 
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

    //level1
    if(Player.GetZone() == ZONE_LOST_TEMPLE_ENTRANCE) DrawTile(lostTempleStairsToLevel1.x, lostTempleStairsToLevel1.y, 4, 3);  //templeStairs
    else if(Player.GetZone() == ZONE_LOST_TEMPLE_LEVEL1) DrawTile(lostTempleStairsToLevel1.x2, lostTempleStairsToLevel1.y2, 4, 3); //templeStairs

    //level2
    if(Player.GetZone() == ZONE_LOST_TEMPLE_LEVEL1) DrawTile(lostTempleStairsToLevel2.x, lostTempleStairsToLevel2.y, 4, 3);  //templeStairs
    else if(Player.GetZone() == ZONE_LOST_TEMPLE_LEVEL2) DrawTile(lostTempleStairsToLevel2.x2, lostTempleStairsToLevel2.y2, 4, 3); //templeStairs

}

void RenderNPCs()
{
    if(Player.GetZone() == ZONE_WORLD ) DrawTile(oldHermit.x, oldHermit.y, 14, 0); //Old Hermit
    
    if(Player.GetZone() == ZONE_WORLD ) DrawTile(woundedKnight.x, woundedKnight.y, 5, 0); //Wounded Knight

    if(Player.GetZone() == ZONE_WORLD_PLAIN_LANDS ) DrawTile(villager1.x, villager1.y, 4, 0); //villager1

    if(Player.GetZone() == ZONE_WORLD_PLAIN_LANDS ) DrawTile(villager2.x, villager2.y, 7, 0); //Wounded Knight

    if(Player.GetZone() == ZONE_BASEMENT_DUNGEON) DrawTile(basementLockedDoor.x, basementLockedDoor.y, 7, 2); //Basement Locked Door

    if(Player.GetZone() == ZONE_BASEMENT_DUNGEON) DrawTile(weirdMan.x, weirdMan.y, 15, 0); //Weird Man

    if(Player.GetZone() == ZONE_ISLAND)  DrawTexture(textures[TEXTURE_ISLANDER], islander.x, islander.y, WHITE); //Islander Man

    if(Player.GetZone() == ZONE_ISLAND)  DrawTexture(textures[TEXTURE_RANDOM_TRINKET], randomTrinket.x, randomTrinket.y, WHITE); // Trinket

    if(Player.GetZone() == ZONE_LOST_TEMPLE_ENTRANCE ) DrawTile(oldHermit.x2, oldHermit.y2, 14, 0); //Old Hermit

    if(Player.GetZone() == ZONE_LOST_TEMPLE_LEVEL2) DrawTile(weirdMan.x2, weirdMan.y2, 15, 0); //Weird Man
}

void RenderBoat()
{
    if(Player.GetZone() >= ZONE_ISLAND &&  Player.GetZone() <= ZONE_SEA && !isRidingBoat)
    {
        DrawTexture(textures[TEXTURE_BOAT_RIGHT], boat.x, boat.y, WHITE);
    }

    if(Player.GetZone() == ZONE_ISLAND)
    {
        DrawTexture(textures[TEXTURE_PALM_TREE], TILE_WIDTH * 3, TILE_HEIGHT * 2, WHITE);
        DrawTexture(textures[TEXTURE_PALM_TREE], TILE_WIDTH * 23, TILE_HEIGHT * 2, WHITE);
        DrawTexture(textures[TEXTURE_PALM_TREE], TILE_WIDTH * 3, TILE_HEIGHT * 23, WHITE);
        DrawTexture(textures[TEXTURE_PALM_TREE], TILE_WIDTH * 4, TILE_HEIGHT * 19, WHITE);
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
            chestArr[i]->money = GetRandomValue(enemy->GetMoneyMin(), enemy->GetMoneyMax());
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

    
    for(int i = 0; i < MAX_MONSTER_SQUID_INSTANCES; i++) //check contact with Monster Squid
    {
        if (squidArr[i] != nullptr && Player.GetZone() == squidArr[i]->GetZone() && Player.GetX() == squidArr[i]->GetX() && Player.GetY() == squidArr[i]->GetY() && squidArr[i]->IsAlive() == true) 
        {
            enemy = squidArr[i];
            battleMode = true;
        }
    }

    for(int i = 0; i < MAX_WATER_SLIME_INSTANCES; i++) //check contact with Water Slime
    {
        if (waterSlimeArr[i] != nullptr && Player.GetZone() == waterSlimeArr[i]->GetZone() && Player.GetX() == waterSlimeArr[i]->GetX() && Player.GetY() == waterSlimeArr[i]->GetY() && waterSlimeArr[i]->IsAlive() == true) 
        {
            enemy = waterSlimeArr[i];
            battleMode = true;
        }
    }

    for(int i = 0; i < MAX_SPECIAL_GOLEM_INSTANCES; i++) //check contact with Special Golem
    {
        if (specialGolemArr[i] != nullptr && Player.GetZone() == specialGolemArr[i]->GetZone() && Player.GetX() == specialGolemArr[i]->GetX() && Player.GetY() == specialGolemArr[i]->GetY() && specialGolemArr[i]->IsAlive() == true) 
        {
            enemy = specialGolemArr[i];
            battleMode = true;
        }
    }

    for(int i = 0; i < MAX_GUARDIAN_INSTANCES; i++) //check contact with Guardian
    {
        if (guardianArr[i] != nullptr && Player.GetZone() == guardianArr[i]->GetZone() && Player.GetX() == guardianArr[i]->GetX() && Player.GetY() == guardianArr[i]->GetY() && guardianArr[i]->IsAlive() == true) 
        {
            enemy = guardianArr[i];
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
            if(count > 4) 
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

    for(int i = 0; i < MAX_WATER_SLIME_INSTANCES; i++) 
    {
        if(!waterSlimeArr[i]->GetStunStatus()) 
        {
            waterSlimeArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            waterSlimeArr[i]->SetStunCounter(count);
            if(count > 4) 
            {
                waterSlimeArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(waterSlimeArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    for(int i = 0; i < MAX_SPECIAL_GOLEM_INSTANCES; i++) 
    {
        if(!specialGolemArr[i]->GetStunStatus()) 
        {
            specialGolemArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            specialGolemArr[i]->SetStunCounter(count);
            if(count > 2) 
            {
                specialGolemArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(specialGolemArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    for(int i = 1; i < MAX_MUTATED_FROG_INSTANCES; i++) 
    {
        if(!mutantFrogArr[i]->GetStunStatus()) 
        {
            mutantFrogArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            mutantFrogArr[i]->SetStunCounter(count);
            if(count > 3) 
            {
                mutantFrogArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(mutantFrogArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }

    for(int i = 1; i < MAX_MONSTER_SQUID_INSTANCES; i++) 
    {
        if(!squidArr[i]->GetStunStatus()) 
        {
            squidArr[i]->MoveAI(Player.GetX(), Player.GetY());
        }
        else
        {
            
            squidArr[i]->SetStunCounter(count);
            if(count > 4) 
            {
                squidArr[i]->SetStunStatus(false);
                count = 0;
                
            }
        }

        if(squidArr[i]->GetStunStatus())
        {
            count++;
            std::cout << count;
        }
    }


    
}

void EnterGates()
{
    if(Player.GetX() == dungeon_gate.x && Player.GetY() == dungeon_gate.y)
    {
        if(dungeonKey)
        {
            if(Player.GetZone() == ZONE_WORLD)
            {
                Player.SetZone(dungeon_gate.zone2); // this aswell to dungeon_gate.zone2
                currentGameState = IN_DUNGEON; // CHANGE THIS TO IN_DUNGEON
                Act1_Dungeon1();
            }
            else if(Player.GetZone() == ZONE_DUNGEON)
            {
                Player.SetZone(dungeon_gate.zone1);
                currentGameState = IN_ZONE_1;
            }  
        }
        else
        {
            StartDialogue({"You need Dungeon Key to enter."});
            return;
        }
    }

   
    if(Player.GetX() == plainLands_gate.x && Player.GetY() == plainLands_gate.y)
    {   
        if (plainsKey && currentGameState == IN_PLAINS)
        {
            StartDialogue({"The Dungeon collapsed..."});
        }
        else if(plainsKey)
        {
            if(Player.GetZone() == ZONE_DUNGEON)
            {
                Player.SetZone(plainLands_gate.zone2);
                currentGameState = IN_PLAINS;
                Act2_Introduction();
            }
        }
        else
        {
            StartDialogue({"Defeat all enemies first to Enter."});
        }
        return;
    }

    if(Player.GetX() == basementStairs.x && Player.GetY() == basementStairs.y)
    {   
        if (mutantFrogKilled && currentGameState == IN_PLAINS)
        {
            Player.SetZone(basementStairs.zone2);
            currentGameState = IN_DUNGEON_BASEMENT;
        }
        else if (currentGameState == IN_DUNGEON_BASEMENT)
        {
            
            Player.SetZone(basementStairs.zone1);
            currentGameState = IN_PLAINS;
        }
        else
        {
            StartDialogue({"Defeat the mutant frog first to enter."});
        }
        return;
    }

    if(Player.GetX() == ladderToIsland.x && Player.GetY() == ladderToIsland.y)
    {   
        if (currentGameState == IN_DUNGEON_BASEMENT)
        {
            Player.SetZone(ladderToIsland.zone2);
            currentGameState = IN_ISLAND;
        }
        else if (currentGameState == IN_ISLAND)
        {
            
            Player.SetZone(ladderToIsland.zone1);
            currentGameState = IN_DUNGEON_BASEMENT;
        }
        return;
    }

    if(Player.GetX() == lostTempleStairsToLevel1.x && Player.GetY() == lostTempleStairsToLevel1.y)
    {   
        if (currentGameState == IN_LOST_TEMPLE_ENTRANCE)
        {
            Player.SetZone(lostTempleStairsToLevel1.zone2);
            Player.SetX(lostTempleStairsToLevel1.x2);
            Player.SetY(lostTempleStairsToLevel1.y2);
            currentGameState = IN_LOST_TEMPLE_LEVEL1;
        }
        else if (currentGameState == IN_LOST_TEMPLE_LEVEL1)
        {
            
            Player.SetZone(lostTempleStairsToLevel1.zone1);
            Player.SetX(lostTempleStairsToLevel1.x);
            Player.SetY(lostTempleStairsToLevel1.y);
            currentGameState = IN_LOST_TEMPLE_ENTRANCE;
        }
        return;
    }

    if(Player.GetX() == lostTempleStairsToLevel2.x && Player.GetY() == lostTempleStairsToLevel2.y)
    {   
        if (currentGameState == IN_LOST_TEMPLE_LEVEL1)
        {
            Player.SetZone(lostTempleStairsToLevel2.zone2);
            Player.SetX(lostTempleStairsToLevel2.x2);
            Player.SetY(lostTempleStairsToLevel2.y2);
            currentGameState = IN_LOST_TEMPLE_LEVEL2;
        }
        else if (currentGameState == IN_LOST_TEMPLE_LEVEL2)
        {
            
            Player.SetZone(lostTempleStairsToLevel2.zone1);
            Player.SetX(lostTempleStairsToLevel2.x);
            Player.SetY(lostTempleStairsToLevel2.y);
            currentGameState = IN_LOST_TEMPLE_LEVEL1;
        }
        return;
    }

}

void InteractWithNPCs()
{
    //Zone1
    if(abs(Player.GetX() - oldHermit.x) <= TILE_WIDTH && 
       abs(Player.GetY() - oldHermit.y) <= TILE_HEIGHT &&
        Player.GetZone() == oldHermit.zone1)
    {
        Act1_HermitLine();
        Player.SetHealthPotions(Player.GetRemainingHealthPotions() + 4);
    }
    else if(abs(Player.GetX() - woundedKnight.x) <= TILE_WIDTH && 
            abs(Player.GetY() - woundedKnight.y) <= TILE_HEIGHT &&
        Player.GetZone() == woundedKnight.zone1)
    {
        Act1_WoundedKnight();
        Player.SetEnergyFoods(Player.GetRemainingEnergyFoods() + 2);
    }
    
    //villagers in plains
    if(abs(Player.GetX() - villager1.x) <= TILE_WIDTH && 
       abs(Player.GetY() - villager1.y) <= TILE_HEIGHT &&
        Player.GetZone() == villager1.zone1)
    {
       Act2_VillageCheif1();
       if(mutantFrogKilled  && !Act2_VillageChiefRewardClaimed)
       {
        Player.SetMoney(Player.GetMoney() + 2300);
        Player.SetHealthPotions(Player.GetRemainingHealthPotions() + 7);
        Player.SetEnergyFoods(Player.GetRemainingEnergyFoods() + 5);
        Act2_VillageChiefRewardClaimed = true;
       }
    }

    if(abs(Player.GetX() - villager2.x) <= TILE_WIDTH && 
       abs(Player.GetY() - villager2.y) <= TILE_HEIGHT &&
        Player.GetZone() == villager2.zone1)
    {
        Act2_RandomVillager1();
    }

    //basement dungeon 
    if(abs(Player.GetX() - basementLockedDoor.x) <= TILE_WIDTH && 
       abs(Player.GetY() - basementLockedDoor.y) <= TILE_HEIGHT &&
        Player.GetZone() == basementLockedDoor.zone1)
    {
        if(cursedGoldenKey.IsPickedUp())
        {
            StartDialogue({
                "[You unlocked the door.]"
            });
            basementLockedDoor.x = TILE_WIDTH * 99;
            basementLockedDoor.y = TILE_HEIGHT * 99;
        }
        else
        {
            StartDialogue({
                "[You need a key to unlock this door.]"
            });
        }
    }

    if(abs(Player.GetX() - weirdMan.x) <= TILE_WIDTH && 
       abs(Player.GetY() - weirdMan.y) <= TILE_HEIGHT &&
        Player.GetZone() == weirdMan.zone1)
    {
        Act2_WeirdMan();
    }

    //island
    if(abs(Player.GetX() - islander.x) <= TILE_WIDTH && 
       abs(Player.GetY() - islander.y) <= TILE_HEIGHT &&
        Player.GetZone() == islander.zone1)
    {
        Act3_Islander();
    }

    if(abs(Player.GetX() - randomTrinket.x) <= TILE_WIDTH && 
       abs(Player.GetY() - randomTrinket.y) <= TILE_HEIGHT &&
        Player.GetZone() == randomTrinket.zone1)
    {
        if(cursedGoldenKey.IsPickedUp())
        {
            StartDialogue({
                "[You picked up an item.]"
            });
            randomTrinket.x = TILE_WIDTH * 99;
            randomTrinket.y = TILE_HEIGHT * 99;
            Act3_LostTrinketFound = true;
        }
    }

    //lost temple entrance
    if(abs(Player.GetX() - oldHermit.x2) <= TILE_WIDTH && 
       abs(Player.GetY() - oldHermit.y2) <= TILE_HEIGHT &&
        Player.GetZone() == oldHermit.zone2)
    {
        Act4_oldHermit();
    }

    //lost temple level2
     if(abs(Player.GetX() - weirdMan.x2) <= TILE_WIDTH && 
       abs(Player.GetY() - weirdMan.y2) <= TILE_HEIGHT &&
        Player.GetZone() == weirdMan.zone2)
    {
        Act4_WeirdManSecondMeeting();

    }


}
