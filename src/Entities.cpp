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

sEntity dungeon_gate, plainLands_gate;
sEntity oldHermit, woundedKnight;
int levelCap = 100;
bool playerLeveledUp = false;
bool chestIsPresent = false;


//Init enemies
Enemy orc(
    Enemy::ORC, "Orc", // id, name
    TILE_WIDTH * 5, TILE_HEIGHT * 5, //spawn pos
    120, ZONE_WORLD_PLAIN_LANDS, 20, 40, 10, //maxhp, zone, dmgMin, dmgMax, def
    165, 2, "Intelligence", false // exp, level, weakness, special Status
);

Enemy wanderingEye(
    Enemy::WANDERING_EYE, "Wandering Eye",
    TILE_WIDTH * 10, TILE_HEIGHT * 20,
    200, ZONE_WORLD_PLAIN_LANDS, 40, 58, 20,
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
    100, ZONE_WORLD_PLAIN_LANDS, 35, 55, 15,
    200, 5, "Dexterity", false
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
    130, ZONE_DUNGEON, 32, 35, 14,
    190, 3, "Intelligence", false
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
    180, ZONE_WORLD_PLAIN_LANDS, 30, 90, 25,
    490, 8, "NULL", true
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

Enemy* wanderingEye1 = nullptr;
Enemy* wanderingEye2 = nullptr;

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

Enemy* rat1 = nullptr;
Enemy* rat2 = nullptr;

Enemy* slime1 = nullptr;
Enemy* slime2 = nullptr;

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
    //NPCs - Zone1
    oldHermit = (sEntity)
    {
        .x = TILE_WIDTH * 15,
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
        .zone2 = ZONE_DUNGEON,
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

    wanderingEye1 = new Enemy(wanderingEye);
    wanderingEye1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    wanderingEye2 = new Enemy(wanderingEye);
    wanderingEye2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));


    //array of enemies
    orcArr[0] = orc1;
    orcArr[1] = orc2;
    orcArr[2] = orc3;
    //3 more 

    eyeArr[0] = wanderingEye1;
    eyeArr[1] = wanderingEye2;

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

    crabArr[0] = crabThing1;

    Player.SetZone(ZONE_WORLD);

}

void PlayerRender()
{
    if(Player.GetName() == Knight.GetName())  DrawTile(camera.target.x, camera.target.y, 6, 0);
    else if(Player.GetName() == Wizard.GetName())  DrawTile(camera.target.x, camera.target.y, 9, 0); 
    else if(Player.GetName() == Rogue.GetName())  DrawTile(camera.target.x, camera.target.y, 8, 0);  
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
}

void RenderNPCs()
{
    if(Player.GetZone() == ZONE_WORLD ) DrawTile(oldHermit.x, oldHermit.y, 14, 0); //Old Hermit
    
    if(Player.GetZone() == ZONE_WORLD ) DrawTile(woundedKnight.x, woundedKnight.y, 5, 0); //Wounded Knight
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
