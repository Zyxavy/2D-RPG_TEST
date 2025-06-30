#include "Entities.hpp"
#include "GameFunctions.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include "MusicFunctions.hpp"
#include "GameMenu.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>

sEntity dungeon_gate;
sEntity plainLands_gate;
int levelCap = 100;
bool playerLeveledUp = false;

//Init enemies
Enemy orc(
    "Orc", // name
    TILE_WIDTH * 5, TILE_HEIGHT * 5, //spawn pos
    120, ZONE_DUNGEON, 20, 40, 10, //maxhp, zone, dmgMin, dmgMax, def
    100, 1, "Intelligence" // exp, level, weakness
);

Enemy wanderingEye(
    "Wandering Eye",
    TILE_WIDTH * 10, TILE_HEIGHT * 20,
    100, ZONE_WORLD, 20, 48, 8,
    120, 1, "Strenght"
);

Enemy treant(
    "Treant",
    TILE_WIDTH * 5, TILE_HEIGHT * 8,
    190, ZONE_WORLD, 10, 80, 11,
    180, 3, "Dexterity"
);

Enemy vengefulSpirit(
    "Vengeful Spirit",
    TILE_WIDTH * GetRandomValue(1,6), TILE_HEIGHT * GetRandomValue(2,8),
    100, ZONE_DUNGEON, 45, 50, 8,
    160, 2, "Intelligence"
);

Enemy golem(
    "Golem",
    TILE_WIDTH * GetRandomValue(2,9), TILE_HEIGHT * GetRandomValue(2,8),
    250, ZONE_DUNGEON, 18, 28, 25,
    200, 3, "Strenght"
);

Enemy crabThing(
    "The Crab Thing",
    TILE_WIDTH * GetRandomValue(2,9), TILE_HEIGHT * GetRandomValue(2,8),
    120, ZONE_WORLD_PLAIN_LANDS, 30, 50, 15,
    170, 2, "NULL"
);

//Init Heroes
Hero Knight (
    "Knight", "Strength", //Name, type
    TILE_WIDTH * 3, TILE_HEIGHT * 3, // pos X, pos Y
    200, 200, 100, 100, 18, 37, 24, 0, 1, 1000, ZONE_WORLD, true, true // hp, maxhp, energy, maxenergy, damagemin,damagemax,defense, experience, level, money, zone, is alive, is passable
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

Enemy* crabThing1 = nullptr;

Enemy* enemy = nullptr;

//enemy arrays
Enemy* orcArr[MAX_ORCS_INSTANCES];
Enemy* eyeArr[MAX_WANDERING_EYE_INSTANCES];
Enemy* treantArr[MAX_TREANT_INSTANCES];
Enemy* vengefulSpiritArr[MAX_VENGEFUL_SPIRIT_INSTANCES];
Enemy* golemArr[MAX_GOLEM_INSTANCES];
Enemy* crabArr[MAX_CRAB_THING_INSTANCES];


void EntitiesInit() { 

    dungeon_gate = (sEntity) 
    {
        .x = TILE_WIDTH * 10,
        .y = TILE_HEIGHT * 10,
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



    //Place enemy instances
    orc1 = new Enemy(orc);
    orc1->Move( TILE_WIDTH * 5, TILE_HEIGHT * 5);

    orc2 = new Enemy(orc);
    orc2->Move(TILE_WIDTH * 6, TILE_HEIGHT * 5);

    orc3 = new Enemy(orc);
    orc3->Move(TILE_WIDTH * 15, TILE_HEIGHT * 16);


    wanderingEye1 = new Enemy(wanderingEye);
    wanderingEye1->Move(TILE_WIDTH * 10, TILE_HEIGHT * 20);

    wanderingEye2 = new Enemy(wanderingEye);
    wanderingEye2->Move(TILE_WIDTH * 14, TILE_HEIGHT * 20);

    treant1 = new Enemy(treant);
    treant1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    treant2 = new Enemy(treant);
    treant2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    vengefulSpirit1 = new Enemy(vengefulSpirit);
    vengefulSpirit1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    vengefulSpirit2 = new Enemy(vengefulSpirit);
    vengefulSpirit2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    golem1 = new Enemy(golem);
    golem1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    golem2 = new Enemy(golem);
    golem2->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));

    crabThing1 = new Enemy(crabThing);
    crabThing1->Move(TILE_WIDTH * GetRandomValue(1,14), TILE_HEIGHT * GetRandomValue(1,20));


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

    //spawn chest
    if(chest.isAlive) { DrawTile(chest.x, chest.y, 9 ,3);}
    
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
        orcArr[i]->SetHealth(orc.GetMaxHealth());
        orcArr[i]->SetDamageMin(orc.GetDamageMin() + 8);
        orcArr[i]->SetDamageMax(orc.GetDamageMax() + 10);
        orcArr[i]->SetDefense(orc.GetDefense() + 2);
        orcArr[i]->SetLevel(orc.GetLevel() + 1);
        orcArr[i]->SetExperience(orc.GetExperience() + 35);
    }

    //wandering Eyes
    for(int i = 0; i < MAX_WANDERING_EYE_INSTANCES;i++)
    {
        eyeArr[i]->SetMaxHealth(wanderingEye.GetMaxHealth() + 50);
        eyeArr[i]->SetHealth(wanderingEye.GetMaxHealth());
        eyeArr[i]->SetDamageMin(wanderingEye.GetDamageMin() + 10);
        eyeArr[i]->SetDamageMax(wanderingEye.GetDamageMax() + 15);
        eyeArr[i]->SetDefense(wanderingEye.GetDefense() + 1);
        eyeArr[i]->SetLevel(wanderingEye.GetLevel() + 1);
        eyeArr[i]->SetExperience(wanderingEye.GetExperience() + 40);
    }

    //Treants
    for(int i = 0; i < MAX_TREANT_INSTANCES;i++)
    {
        treantArr[i]->SetMaxHealth(treant.GetMaxHealth() + 80);
        treantArr[i]->SetHealth(treant.GetMaxHealth());
        treantArr[i]->SetDamageMin(treant.GetDamageMin() + 5);
        treantArr[i]->SetDamageMax(treant.GetDamageMax() + 5);
        treantArr[i]->SetDefense(treant.GetDefense() + 3);
        treantArr[i]->SetLevel(treant.GetLevel() + 1);
        treantArr[i]->SetExperience(treant.GetExperience() + 35);
    }

    //Vengeful Spirits
    for(int i = 0; i < MAX_VENGEFUL_SPIRIT_INSTANCES;i++)
    {
        vengefulSpiritArr[i]->SetMaxHealth(vengefulSpirit.GetMaxHealth() + 50);
        vengefulSpiritArr[i]->SetHealth(vengefulSpirit.GetMaxHealth());
        vengefulSpiritArr[i]->SetDamageMin(vengefulSpirit.GetDamageMin() + 10);
        vengefulSpiritArr[i]->SetDamageMax(vengefulSpirit.GetDamageMax() + 15);
        vengefulSpiritArr[i]->SetDefense(vengefulSpirit.GetDefense() + 1);
        vengefulSpiritArr[i]->SetLevel(vengefulSpirit.GetLevel() + 1);
        vengefulSpiritArr[i]->SetExperience(vengefulSpirit.GetExperience() + 40);
    }

    //Golems
    for(int i = 0; i < MAX_GOLEM_INSTANCES;i++)
    {
        golemArr[i]->SetMaxHealth(golem.GetMaxHealth() + 100);
        golemArr[i]->SetHealth(golem.GetMaxHealth());
        golemArr[i]->SetDamageMin(golem.GetDamageMin() + 3);
        golemArr[i]->SetDamageMax(golem.GetDamageMax() + 3);
        golemArr[i]->SetDefense(golem.GetDefense() + 5);
        golemArr[i]->SetLevel(golem.GetLevel() + 1);
        golemArr[i]->SetExperience(golem.GetExperience() + 35);
    }

    //The Crab
    for(int i = 0; i < MAX_CRAB_THING_INSTANCES;i++)
    {
        crabArr[i]->SetMaxHealth(crabThing.GetMaxHealth() + 70);
        crabArr[i]->SetHealth(crabThing.GetMaxHealth());
        crabArr[i]->SetDamageMin(crabThing.GetDamageMin() + 25);
        crabArr[i]->SetDamageMax(crabThing.GetDamageMax() + 30);
        crabArr[i]->SetDefense(crabThing.GetDefense() + 3);
        crabArr[i]->SetLevel(crabThing.GetLevel() + 2);
        crabArr[i]->SetExperience(crabThing.GetExperience() + 85);
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

