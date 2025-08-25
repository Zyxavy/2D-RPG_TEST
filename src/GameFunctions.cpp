#include "GameFunctions.hpp"
#include "BattleSystem.hpp"
#include "GameMenu.hpp"
#include "Entities.hpp"
#include "MusicFunctions.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include "StoryLine.hpp"
#include "ZoneMaps.hpp"
#include "Items.hpp"
#include <iostream>


Camera2D camera { 0 };

Texture2D textures[MAX_TEXTURES];
Texture2D pagePictures[MAX_PAGE_PICTURES];
Sound sounds[MAX_SOUNDS];
sTile world[WORLD_WIDTH][WORLD_HEIGHT];
sTile dungeon[WORLD_WIDTH][WORLD_HEIGHT];
sTile plainLands[WORLD_WIDTH][WORLD_HEIGHT];
sTile basementDungeon[WORLD_WIDTH][WORLD_HEIGHT];
sTile island[WORLD_WIDTH][WORLD_HEIGHT];
sTile sea[WORLD_WIDTH][WORLD_HEIGHT];
sTile lostTemple[WORLD_WIDTH][WORLD_HEIGHT];
sTile lostTempleLevel1[WORLD_WIDTH][WORLD_HEIGHT];
sTile lostTempleLevel2[WORLD_WIDTH][WORLD_HEIGHT];
sTile lostTempleBadEnding[WORLD_WIDTH][WORLD_HEIGHT];
sTile lostTempleGoodEnding[WORLD_WIDTH][WORLD_HEIGHT];
eZones lastZone = ZONE_WORLD;
bool isInventory = false;
int count;
int lastKeyPressed;

GameState currentGameState;
GameState prevGameState;
bool isRidingBoat = false; 
bool isBoatFacingRight = true; 
void GameStartup() {

    dungeonKey = true;
    plainsKey = true;
    mutantFrogKilled = true;
    cursedGoldenKey.SetPickedUpState(true); 

    InitAudioDevice();

    //Load Textures
    LoadAllTextures();

    //Tutorial pages
    LoadAllPages();

    //generate World/Zones
    for(int y = 0; y < WORLD_HEIGHT; y++){
        for(int x = 0; x < WORLD_WIDTH; x++){
            world[x][y] = (sTile)
            {
                .x = x,
                .y = y,
                .type = zone1Map[y][x]
            };

            dungeon[x][y] = (sTile)
            {
                .x = x,
                .y = y,
                .type = zoneDungeon1Map[y][x]
            };

            plainLands[x][y] = (sTile) 
            {
                .x = x,
                .y = y,
                .type = zoneWorldPlainsMap[y][x]
            };

            basementDungeon[x][y] = (sTile) 
            {
                .x = x,
                .y = y,
                .type = zoneBasementDungeon[y][x]
            };

            island[x][y] = (sTile) 
            {
                .x = x,
                .y = y,
                .type = zoneIsland[y][x]
            };

            sea[x][y] = (sTile) 
            {
                .x = x,
                .y = y,
                .type = zoneSea[y][x]
            };

            lostTemple[x][y] = (sTile) 
            {
                .x = x,
                .y = y,
                .type = zoneLostTempleEntrance[y][x]
            };

            lostTempleLevel1[x][y] = (sTile) 
            {
                .x = x,
                .y = y,
                .type = zoneLostTempleLevel1[y][x]
            };

            lostTempleLevel2[x][y] = (sTile) 
            {
                .x = x,
                .y = y,
                .type = zoneLostTempleLevel2[y][x]
            };

            lostTempleBadEnding[x][y] = (sTile) 
            {
                .x = x,
                .y = y,
                .type = zoneLostTempleBadEnding[y][x]
            };

            lostTempleGoodEnding[x][y] = (sTile) 
            {
                .x = x,
                .y = y,
                .type = zoneLostTempleGoodEnding[y][x]
            };

        }
    }

    //initialize entities
    EntitiesInit();
    ItemsInit();

    while(IsBarrierCollision(dungeon_gate.x, dungeon_gate.y))
    {
        int count = 1;
        dungeon_gate.x += TILE_WIDTH * count;
        dungeon_gate.y += TILE_HEIGHT * count;
        count++;
        
    }

    //cameras
    camera.target = (Vector2) { (float)Player.GetX(), (float)Player.GetY()};
    camera.offset = (Vector2) { (float)screenWidth / 2, (float)screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 4.0f;

    //Sounds/Music
    sounds[SOUND_FOOT_GRASS]  = LoadSound("assets/GrassWalk.mp3");
    sounds[SOUND_FOOT_STONE]  = LoadSound("assets/Stonewalk.wav");
    sounds[SOUNDS_ATTACK]  = LoadSound("assets/hitHurt.wav");
    sounds[SOUND_DEATH]  = LoadSound("assets/death.wav");
    sounds[SOUND_COINS]  = LoadSound("assets/pickupCoin.wav");
    sounds[SOUND_HOVER_ITEMS] = LoadSound("assets/HoverItems.wav");
    sounds[SOUNDS_LEVEL_UP] = LoadSound("assets/LevelUp FX.wav");
    sounds[SOUNDS_TREE_CUTTING] = LoadSound("assets/TreeCutting.wav");
    sounds[SOUNDS_ERROR_SOUND] = LoadSound("assets/ErrorSound.wav");
    //skils sounds
    sounds[SOUNDS_KNIGHT_SKILL1] = LoadSound("assets/KnightSkill1.wav");
    sounds[SOUNDS_KNIGHT_SKILL2] = LoadSound("assets/KnightSkill2.wav");
    sounds[SOUNDS_KNIGHT_SKILL3] = LoadSound("assets/KnightSkill3.wav");
    sounds[SOUNDS_WIZARD_SKILL1] = LoadSound("assets/WizardSkill1.wav");
    sounds[SOUNDS_WIZARD_SKILL2] = LoadSound("assets/WizardSkill2.wav");
    sounds[SOUNDS_WIZARD_SKILL3] = LoadSound("assets/WizardSkill3.wav");
    sounds[SOUNDS_ROGUE_SKILL1] = LoadSound("assets/RogueSkill1.wav");
    sounds[SOUNDS_ROGUE_SKILL2] = LoadSound("assets/RogueSkill2.wav");
    sounds[SOUNDS_ROGUE_SKILL3] = LoadSound("assets/RogueSkill3.wav");
    sounds[SOUNDS_BUY_SOUND] = LoadSound("assets/BuySound.wav");
    
    LoadMusic();
}

void GameUpdate() 
{

    //Music
    UpdateMusic();
    if((Player.GetZone() == ZONE_WORLD || Player.GetZone() == ZONE_WORLD_PLAIN_LANDS
    || Player.GetZone() == ZONE_ISLAND || Player.GetZone() == ZONE_SEA || Player.GetZone() == ZONE_LOST_TEMPLE_ENTRANCE) && currentMusicZone != LIGHT) {PlayRandomMusic(LIGHT);}
    else if((Player.GetZone() == ZONE_DUNGEON || Player.GetZone() == ZONE_BASEMENT_DUNGEON ||
             Player.GetZone() == ZONE_LOST_TEMPLE_LEVEL1 || Player.GetZone() == ZONE_LOST_TEMPLE_LEVEL2 ) && currentMusicZone != DARK) {PlayRandomMusic(DARK);}
    else if (Player.GetZone() == ZONE_BATTLE && currentMusicZone != ACTION){ PlayRandomMusic(ACTION);}

    if(battleMode)
    {
        BattleUpdate(enemy);
    }
    else if (inDialogue || inDialogueWithOptions)
    {
        UpdateDialogue();
        UpdateDialogueWithOptions();
    }
    else if(isInventory)
    {
        if(IsKeyPressed(KEY_Q)) {isInventory = false;}
    }
    else
    {
        //Movement
        float x = Player.GetX();
        float y = Player.GetY();
        bool hasKeyPressed = false;

        if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) 
        {
            lastKeyPressed = KEY_A;
            if (isRidingBoat) isBoatFacingRight = false; 
            if (!IsBarrierCollision(Player.GetX() - TILE_WIDTH, Player.GetY())) 
            { 
                x -= TILE_WIDTH;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) 
        {
            lastKeyPressed = KEY_D;
            if (isRidingBoat) isBoatFacingRight = true; 
            if (!IsBarrierCollision(Player.GetX() + TILE_WIDTH, Player.GetY()))
            {  
                x += TILE_WIDTH;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_UP)|| IsKeyPressed(KEY_W)) 
        {
            lastKeyPressed = KEY_W;
            if (!IsBarrierCollision(Player.GetX(), Player.GetY() - TILE_HEIGHT))
            {  
                y -= TILE_HEIGHT;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) 
        { 
            lastKeyPressed = KEY_S;
            if (!IsBarrierCollision(Player.GetX(), Player.GetY() + TILE_HEIGHT))
            {  
                y += TILE_HEIGHT;
                hasKeyPressed = true;

            }
        }

        if(IsKeyPressed(KEY_R))
        {
            CutDownTree();
        }

        if(chestIsPresent)
        {
            int j = 0;
            for(int i = 0; i < MAX_CHEST_INSTANCES; i++)
            {
                if(chestArr[i] != nullptr && Player.GetX() == chestArr[i]->x && Player.GetY() == chestArr[i]->y && chestArr[i]->isAlive && chestArr[i]->zone1 == Player.GetZone()) //interact with chestArr[i]
                {
                    Player.SetMoney(Player.GetMoney() + chestArr[i]->money);
                    Player.SetHealthPotions(Player.GetRemainingHealthPotions() + chestArr[i]->healthPotions);
                    Player.SetEnergyFoods(Player.GetRemainingEnergyFoods() + chestArr[i]->energyFoods );
                    chestArr[i]->isAlive = false;
                    PlaySound(sounds[SOUND_COINS]);
                }

                if(chestArr[i] != nullptr && !chestArr[i]->isAlive)
                {
                    if(++j >= 4) chestIsPresent = false;
                }
            }
        }

        //Enemy moves or Player Escapes and stuns enemy
        if (hasKeyPressed) 
        {
            ExecuteEnemyBehaviors();

            if(Act4_WeirdManSecondMeetingInteracted)
            {
                if(Act4_BadEndingAchieved)
                {
                    Act4_BadEnding();
                }
                else if(Act4_GoodEndingAchieved)
                {
                    Act4_GoodEnding();
                }
            }
        }
        
        //mouse wheel zoom
        float wheel = GetMouseWheelMove();
        if(wheel != 0) 
        { 
            const float zoomIncrement = 0.125f;
            camera.zoom += (wheel * zoomIncrement);
            if(camera.zoom < 3.0f) camera.zoom = 3.0f;
            if(camera.zoom > 9.0f) camera.zoom = 9.0f;
        }

        //CHECK Contact with enemies
        CheckContactWithEnemies();
        
        if(hasKeyPressed && !isRidingBoat) //Play FootSteps when on foot
        {
            if(Player.GetZone() == ZONE_WORLD || Player.GetZone() == ZONE_WORLD_PLAIN_LANDS) PlaySound(sounds[SOUND_FOOT_GRASS]);
            else if (Player.GetZone() == ZONE_DUNGEON) PlaySound(sounds[SOUND_FOOT_STONE]);

        }

        //confirm and set the X&Y coords
        Player.SetX(x);
        Player.SetY(y);

        //Camera Follows Player
        camera.target = (Vector2) {(float)Player.GetX(), (float)Player.GetY()};
    
        InteractWithItems();

        if(IsKeyPressed(KEY_E))
        {
            bool boatInteraction = false;
    
            if (!isRidingBoat && Player.GetZone() >= ZONE_ISLAND && Player.GetZone() <= ZONE_LOST_TEMPLE_ENTRANCE  && 
            abs(Player.GetX() - boat.x) <= TILE_WIDTH && 
            abs(Player.GetY() - boat.y) <= TILE_HEIGHT)
            {
                isRidingBoat = true;
                Player.SetX(boat.x); 
                Player.SetY(boat.y);
                boat.x = -100; 
                boat.y = -100;
                boatInteraction = true;
            }
            else if (isRidingBoat)
            {
                int playerTileX = Player.GetX() / TILE_WIDTH;
                int playerTileY = Player.GetY() / TILE_HEIGHT;
                int landTileX = -1, landTileY = -1; 

                //Check all 4 adjacent tiles for a landing spot 
                int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
                for (int i = 0; i < 4; ++i) 
                {
                    int targetX = playerTileX + directions[i][0];
                    int targetY = playerTileY + directions[i][1];

                    if (targetX >= WORLD_LEFT && targetX <= WORLD_RIGHT && targetY >= WORLD_TOP && targetY <= WORLD_BOTTOM) 
                    {
                        sTile adjacentTile = island[targetX][targetY];
                        
                        if (adjacentTile.type == TILE_TYPE_SAND || adjacentTile.type == TILE_TYPE_GRASS || adjacentTile.type == TILE_TYPE_DIRT) 
                        {
                            landTileX = targetX;
                            landTileY = targetY;
                            break; 
                        }
                    }
                }

                if (landTileX != -1)
                {
                    isRidingBoat = false;
                    boat.x = Player.GetX(); 
                    boat.y = Player.GetY();
                    Player.SetX(landTileX * TILE_WIDTH); 
                    Player.SetY(landTileY * TILE_HEIGHT);
                }
                boatInteraction = true; 
            }
            if (!boatInteraction)
            {
                EnterGates();
                InteractWithNPCs();
            }
        }
        else if(IsKeyPressed(KEY_Q))
        {
            if(isInventory == false) {isInventory = true;}
        }

        //gates with no interaction
        //islands
        if(Player.GetX() == seaExtensionEntrance.x && Player.GetY() == seaExtensionEntrance.y && Player.GetZone() == ZONE_ISLAND)
        {
            Player.SetZone(ZONE_SEA);
            currentGameState = IN_SEA;
            Player.SetX(seaExtensionEntrance.x2 - TILE_WIDTH);
            Player.SetY(seaExtensionEntrance.y2);
        }
        else if(Player.GetX() == lostTempleEntrance.x && Player.GetY() == lostTempleEntrance.y && Player.GetZone() == ZONE_ISLAND)
        {
            Player.SetZone(ZONE_LOST_TEMPLE_ENTRANCE);
            currentGameState = IN_LOST_TEMPLE_ENTRANCE;
            Player.SetX(lostTempleEntrance.x2 + TILE_WIDTH);
            Player.SetY(lostTempleEntrance.y2);
            Act4_LostTempleIntroduction();

        }

        //sea
        if(Player.GetX() == seaExtensionEntrance.x2 && Player.GetY() == seaExtensionEntrance.y2 && Player.GetZone() == ZONE_SEA)
        {
            Player.SetZone(ZONE_ISLAND);
            currentGameState = IN_ISLAND;
            Player.SetX(seaExtensionEntrance.x + TILE_WIDTH);
            Player.SetY(seaExtensionEntrance.y);
        }

        //temple
        if(Player.GetX() == lostTempleEntrance.x2 && Player.GetY() == lostTempleEntrance.y2 && Player.GetZone() == ZONE_LOST_TEMPLE_ENTRANCE)
        {
            Player.SetZone(ZONE_ISLAND);
            currentGameState = IN_ISLAND;
            Player.SetX(lostTempleEntrance.x - TILE_WIDTH);
            Player.SetY(lostTempleEntrance.y);
        }
    
    }
    

}

void GameRender() 
{
    
    if(battleMode)
    {
        BattleRender(enemy);
    }
    else if(isInventory)
    {
        Inventory();
    }
    else if (inShop)
    {
        islanderShop();
    }
    else if (playerLeveledUp)
    {
        LevelUpScreen();
    }
    else{

        BeginMode2D(camera);
        
        //renders Zones
        sTile tile;
        int texture_index_x = 0;
        int texture_index_y = 0;

        for(int i = 0; i < WORLD_WIDTH; i++){
            for (int j = 0; j < WORLD_HEIGHT; j++){
                if(Player.GetZone() == ZONE_WORLD)
                {
                    tile = world[i][j];
                }
                else if (Player.GetZone() == ZONE_DUNGEON)
                {
                    tile = dungeon[i][j];
                }
                else if (Player.GetZone() == ZONE_WORLD_PLAIN_LANDS) 
                {
                    tile = plainLands[i][j];
                }
                else if (Player.GetZone() == ZONE_BASEMENT_DUNGEON) 
                {
                    tile = basementDungeon[i][j];
                }
                else if (Player.GetZone() == ZONE_ISLAND) 
                {
                    tile = island[i][j];
                }
                else if (Player.GetZone() == ZONE_SEA) 
                {
                    tile = sea[i][j];
                }
                else if (Player.GetZone() == ZONE_LOST_TEMPLE_ENTRANCE) 
                {
                    tile = lostTemple[i][j];
                }
                else if (Player.GetZone() == ZONE_LOST_TEMPLE_LEVEL1) 
                {
                    tile = lostTempleLevel1[i][j];
                }
                else if (Player.GetZone() == ZONE_LOST_TEMPLE_LEVEL2) 
                {
                    tile = lostTempleLevel2[i][j];
                }
                else if (Player.GetZone() == ZONE_LOST_TEMPLE_BAD_ENDING) 
                {
                    tile = lostTempleBadEnding[i][j];
                }
                else if (Player.GetZone() == ZONE_LOST_TEMPLE_GOOD_ENDING) 
                {
                    tile = lostTempleGoodEnding[i][j];
                }

                RenderTile(tile, texture_index_x, texture_index_y);

                if (tile.type == TILE_TYPE_SAND)
                {
                    DrawTexture(textures[TEXTURE_SAND], tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, WHITE);
                }
                else if (tile.type == TILE_TYPE_STONE_WALL)
                {
                    DrawTexture(textures[TEXTURE_STONE_WALL], tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, WHITE);
                }
                else
                {
                    DrawTile(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, texture_index_x, texture_index_y);
                }
            }
            
        }
 

        //Gate
        RenderGates();
        RenderBoat(); 
        // enemies | Npcs
        EnemyRender();
        RenderNPCs();
        RenderItems();
        // player
        PlayerRender();

        EndMode2D();

        // Top-left thingy
        DrawHotBar();

        if(inDialogue) RenderDialogue();
        else RenderDialogueWithOptions();
    }
}

void RenderTile(const sTile &tile,int &texture_index_x, int &texture_index_y )
{
    switch (tile.type) 
    {
        case TILE_TYPE_DIRT: // 0
            texture_index_x = 4; texture_index_y = 4; break;
        case TILE_TYPE_GRASS: // 1
            texture_index_x = 5; texture_index_y = 4; break;
        case TILE_TYPE_TREE:  //2
            texture_index_x = 4; texture_index_y = 5; break;
        case TILE_TYPE_STONE: // 3
            texture_index_x = 1; texture_index_y = 6; break;
        case TILE_TYPE_STUMP: // 4
            texture_index_x = 8; texture_index_y = 3; break;
            //water
        case TILE_TYPE_WATER_TOP_LEFT: // 5
            texture_index_x = 11; texture_index_y = 7; break;
        case TILE_TYPE_WATER_TOP_MID: // 6
            texture_index_x = 12; texture_index_y = 7; break;
        case TILE_TYPE_WATER_TOP_RIGHT: 
            texture_index_x = 13; texture_index_y = 7; break;
        case TILE_TYPE_WATER_MID_LEFT: // 8
            texture_index_x = 11; texture_index_y = 8; break;
        case TILE_TYPE_WATER_MID_MID: //9
            texture_index_x = 12; texture_index_y = 8; break;
        case TILE_TYPE_WATER_MID_RIGHT: 
            texture_index_x = 13; texture_index_y = 8; break;
        case TILE_TYPE_WATER_BOT_LEFT: // 11
            texture_index_x = 11; texture_index_y = 9; break;
        case TILE_TYPE_WATER_BOT_MID: //12
            texture_index_x = 12; texture_index_y = 9; break;
        case TILE_TYPE_WATER_BOT_RIGHT: 
            texture_index_x = 13; texture_index_y = 9; break;
        case TILE_TYPE_WATER_HORIZONTAL: //14
            texture_index_x = 12; texture_index_y = 6; break;
        case TILE_TYPE_WATER_VERTICAL: //15
            texture_index_x = 13; texture_index_y = 6; break;
        case TILE_TYPE_WATER_WELL: //16
            texture_index_x = 11; texture_index_y = 6; break;
            //dungeon misc
        case TILE_TYPE_RAIL_STRAIGHT: // 17
            texture_index_x = 12; texture_index_y = 2; break;
        case TILE_TYPE_RAIL_CURVE://18
            texture_index_x = 11; texture_index_y = 2; break;
        case TILE_TYPE_RAIL_BROKEN://19
            texture_index_x = 13; texture_index_y = 2; break;
        case TILE_TYPE_PILLAR://20
            texture_index_x = 13; texture_index_y = 1; break;
        case TILE_TYPE_BROKEN_PILLAR://21
            texture_index_x = 14; texture_index_y = 1; break;
        case TILE_TYPE_GRAVE://22
            texture_index_x = 9; texture_index_y = 7; break;
        case TILE_TYPE_CROSS: //23
            texture_index_x = 8; texture_index_y = 7; break;
        case TILE_TYPE_TOP_LEFT_WALL_CORNER: //24 
            texture_index_x = 0; texture_index_y = 0; break;
        case  TILE_TYPE_TOP1_WALL: //25
            texture_index_x = 1; texture_index_y = 0; break; 
        case TILE_TYPE_TOP2_WALL: //26
            texture_index_x = 2; texture_index_y = 0; break;
        case TILE_TYPE_TOP_RIGHT_WALL_CORNER: //27 
            texture_index_x = 3; texture_index_y = 0; break;
        case TILE_TYPE_MID_LEFT_WALL_CORNER: //28
            texture_index_x = 0; texture_index_y = 1; break;
        case TILE_TYPE_MID_WALL1: //29
            texture_index_x = 1; texture_index_y = 1; break;
        case TILE_TYPE_MID_WALL2:// 30
            texture_index_x = 2; texture_index_y = 1; break;
        case TILE_TYPE_MID_RIGHT_WALL_CORNER: //31 
            texture_index_x = 3; texture_index_y = 1; break;
        case TILE_TYPE_BOT_LEFT_OUTER_WALL_CORNER: //32 
            texture_index_x = 0; texture_index_y = 2; break;
        case  TILE_TYPE_BOT_OUTER_WALL1: //33
            texture_index_x = 1; texture_index_y = 2; break;
        case TILE_TYPE_BOT_OUTER_WALL2: // 34
            texture_index_x = 2; texture_index_y = 2; break;
        case TILE_TYPE_BOT_RIGHT_OUTER_WALL_CORNER: //35 
            texture_index_x = 3; texture_index_y = 2; break;
        case TILE_TYPE_HOUSE: //36
            texture_index_x = 5; texture_index_y = 7; break;
        case TILE_TYPE_STAIRS_DOWN: //37
            texture_index_x = 4; texture_index_y = 3; break;
            //basement  dungeon
        case TILE_TYPE_CAULDRON: //38
            texture_index_x = 8; texture_index_y = 2; break;
        case TILE_TYPE_BED: //39
            texture_index_x = 14; texture_index_y = 3; break;
        case TILE_TYPE_DOOR_LOCKED: //40
            texture_index_x = 7; texture_index_y = 2; break;
        case TILE_TYPE_DOOR_UNLOCEKD: //41
            texture_index_x = 5; texture_index_y = 2; break;
        case TILE_TYPE_SQUARE_RAIL: //42
            texture_index_x = 14; texture_index_y = 2; break;
        case TILE_TYPE_SAND:
            texture_index_x = -1; texture_index_y = -1; break;
        case TILE_TYPE_STONE_WALL:
             texture_index_x = -2; texture_index_y = -2; break;
        default:
            break;
    }
}

void LoadAllTextures()
{
    //init tiles/graphics
    Image image = LoadImage("assets/colored_tilemap_packed.png");
    textures[TEXTURE_TILEMAP] = LoadTextureFromImage(image);
    UnloadImage(image);

    Image StarImage = LoadImage("assets/Star.png");
    textures[TEXTURE_STAR]= LoadTextureFromImage(StarImage);
    UnloadImage(StarImage);

    Image BookImage = LoadImage("assets/Book.png");
    textures[TEXTURE_BOOK]= LoadTextureFromImage(BookImage);
    UnloadImage(BookImage);

    Image SandTile = LoadImage("assets/sand.png");
    textures[TEXTURE_SAND] = LoadTextureFromImage(SandTile);
    UnloadImage(SandTile);

    Image palmTreeTile = LoadImage("assets/palmTree.png");
    textures[TEXTURE_PALM_TREE] = LoadTextureFromImage(palmTreeTile);
    UnloadImage(palmTreeTile);

    Image randomTrinketPNG = LoadImage("assets/randomTrinket.png");
    textures[TEXTURE_RANDOM_TRINKET] = LoadTextureFromImage(randomTrinketPNG);
    UnloadImage(randomTrinketPNG);

    Image stoneWallPNG = LoadImage("assets/StoneWall.png");
    textures[TEXTURE_STONE_WALL] = LoadTextureFromImage(stoneWallPNG);
    UnloadImage(stoneWallPNG);

    //Load boat textures
    Image boatFacingLeft = LoadImage("assets/Boat/boatFacingLeft.png");
    textures[TEXTURE_BOAT_LEFT] = LoadTextureFromImage(boatFacingLeft);
    UnloadImage(boatFacingLeft);

    Image boatFacingRight = LoadImage("assets/Boat/boatFacingRight.png");
    textures[TEXTURE_BOAT_RIGHT] = LoadTextureFromImage(boatFacingRight);
    UnloadImage(boatFacingRight);

    //heroes textures

    Image knightPNG = LoadImage("assets/Heroes/knight.png");
    textures[TEXTURE_KNIGHT] = LoadTextureFromImage(knightPNG);
    UnloadImage(knightPNG);

    Image wizardPNG = LoadImage("assets/Heroes/wizard.png");
    textures[TEXTURE_WIZARD] = LoadTextureFromImage(wizardPNG);
    UnloadImage(wizardPNG);

    Image roguePNG = LoadImage("assets/Heroes/rogue.png");
    textures[TEXTURE_ROGUE] = LoadTextureFromImage(roguePNG);
    UnloadImage(roguePNG);

    //enemies
    Image floatingCrabPNG = LoadImage("assets/Enemies/floatingCrab.png");
    textures[TEXTURE_FLOATING_CRAB] = LoadTextureFromImage(floatingCrabPNG);
    UnloadImage(floatingCrabPNG);

    Image monsterSquidPNG = LoadImage("assets/Enemies/monsterSquid.png");
    textures[TEXTURE_MONSTER_SQUID] = LoadTextureFromImage(monsterSquidPNG);
    UnloadImage(monsterSquidPNG);

    Image waterSlimePNG = LoadImage("assets/Enemies/waterSlime.png");
    textures[TEXTURE_WATER_SLIME] = LoadTextureFromImage(waterSlimePNG);
    UnloadImage(waterSlimePNG);

    Image specialGolemPNG = LoadImage("assets/Enemies/SpecialGolem.png");
    textures[TEXTURE_SPECIAL_GOLEM] = LoadTextureFromImage(specialGolemPNG);
    UnloadImage(specialGolemPNG);

    Image islanderPNG = LoadImage("assets/islander.png");
    textures[TEXTURE_ISLANDER] = LoadTextureFromImage(islanderPNG);
    UnloadImage(islanderPNG);

    //potions
    Image healthPotionPNG = LoadImage("assets/Potions/healthPotion.png");
    textures[TEXTURE_HEALTH_POTION] = LoadTextureFromImage(healthPotionPNG);
    UnloadImage(healthPotionPNG);

    Image defensePotionPNG = LoadImage("assets/Potions/defensePotion.png");
    textures[TEXTURE_DEFENSE_POTION] = LoadTextureFromImage(defensePotionPNG);
    UnloadImage(defensePotionPNG);

    Image strengthPotionPNG = LoadImage("assets/Potions/strengthPotion.png");
    textures[TEXTURE_STRENGTH_POTION] = LoadTextureFromImage(strengthPotionPNG);
    UnloadImage(strengthPotionPNG);

    Image experiencePotionPNG = LoadImage("assets/Potions/experiencePotion.png");
    textures[TEXTURE_EXPERIENCE_POTION] = LoadTextureFromImage(experiencePotionPNG);
    UnloadImage(experiencePotionPNG);

    Image energyFoodPNG = LoadImage("assets/Potions/energyFood.png");
    textures[TEXTURE_ENERGY_FOOD] = LoadTextureFromImage(energyFoodPNG);
    UnloadImage(energyFoodPNG);

}

void GameShutdown() 
{

    for(int i = 0; i < MAX_TEXTURES; i++)
    {
        UnloadTexture(textures[i]);
    }

    for(int i = 0; i < MAX_PAGE_PICTURES; i++)
    {
        UnloadTexture(pagePictures[i]);
    }

    for(int i = 0; i < MAX_SOUNDS; i++)
    {
        UnloadSound(sounds[i]);
    }


   
    DeleteEnemies();
    StopCurrentMusic();
    UnloadMusic();
    CloseAudioDevice();
    
}

void LoadAllPages()
{
    Image pg1 = LoadImage("assets/TutorialAssets/Pg1.png");
    pagePictures[PAGE1]= LoadTextureFromImage(pg1);
    UnloadImage(pg1);

    Image pg2 = LoadImage("assets/TutorialAssets/Pg2.png");
    pagePictures[PAGE2]= LoadTextureFromImage(pg2);
    UnloadImage(pg2);

    Image pg3 = LoadImage("assets/TutorialAssets/Pg3.png");
    pagePictures[PAGE3]= LoadTextureFromImage(pg3);
    UnloadImage(pg3);

    Image pg4 = LoadImage("assets/TutorialAssets/Pg4.png");
    pagePictures[PAGE4]= LoadTextureFromImage(pg4);
    UnloadImage(pg4);

    Image pg5 = LoadImage("assets/TutorialAssets/Pg5.png");
    pagePictures[PAGE5]= LoadTextureFromImage(pg5);
    UnloadImage(pg5);

    Image pg6 = LoadImage("assets/TutorialAssets/Pg6.png");
    pagePictures[PAGE6]= LoadTextureFromImage(pg6);
    UnloadImage(pg6);

    Image pg7 = LoadImage("assets/TutorialAssets/Pg7.png");
    pagePictures[PAGE7]= LoadTextureFromImage(pg7);
    UnloadImage(pg7);

    Image pg8 = LoadImage("assets/TutorialAssets/Pg8.png");
    pagePictures[PAGE8]= LoadTextureFromImage(pg8);
    UnloadImage(pg8);

    Image pg9 = LoadImage("assets/TutorialAssets/Pg9.png");
    pagePictures[PAGE9]= LoadTextureFromImage(pg9);
    UnloadImage(pg9);

    Image pg10 = LoadImage("assets/TutorialAssets/Pg10.png");
    pagePictures[PAGE10]= LoadTextureFromImage(pg10);
    UnloadImage(pg10);

    Image pg11 = LoadImage("assets/TutorialAssets/Pg11.png");
    pagePictures[PAGE11]= LoadTextureFromImage(pg11);
    UnloadImage(pg11);
}

void DeleteEnemies()
{
    for(int i = 0; i < MAX_ORCS_INSTANCES; i++)
    {
        delete orcArr[i];
    }
    
    for(int i = 0; i < MAX_WANDERING_EYE_INSTANCES; i++)
    {
        delete eyeArr[i];
    }

    for(int i = 0; i < MAX_TREANT_INSTANCES; i++)
    {
        delete treantArr[i];
    }

    for(int i = 0; i < MAX_VENGEFUL_SPIRIT_INSTANCES; i++)
    {
        delete vengefulSpiritArr[i];
    }

    for(int i = 0; i < MAX_GOLEM_INSTANCES; i++)
    {
        delete golemArr[i];
    }

    for(int i = 0; i < MAX_SNAKE_INSTANCES; i++)
    {
        delete snakeArr[i];
    }

    for(int i = 0; i < MAX_RAT_INSTANCES; i++)
    {
        delete ratArr[i];
    }

    for(int i = 0; i < MAX_DOG_INSTANCES; i++)
    {
        delete dogArr[i];
    }

    for(int i = 0; i < MAX_SLIME_INSTANCES; i++)
    {
        delete slimeArr[i];
    }

    for(int i = 0; i < MAX_FLOATING_CRAB_INSTANCES; i++)
    {
        delete floatingCrabArr[i];
    }


    for(int i = 0; i < MAX_WATER_SLIME_INSTANCES; i++)
    {
        delete waterSlimeArr[i];
    }

    
    //special or bosses
    for(int i = 0; i < MAX_CRAB_THING_INSTANCES; i++)
    {
        delete crabArr[i];
    }

    for(int i = 0; i < MAX_MONSTER_SQUID_INSTANCES; i++)
    {
        delete squidArr[i];
    }

    for(int i = 0; i < MAX_MUTATED_FROG_INSTANCES; i++)
    {
        delete mutantFrogArr[i];
    }

    for(int i = 0; i < MAX_SPECIAL_GOLEM_INSTANCES; i++)
    {
        delete specialGolemArr[i];
    }

    //chest
    for(int i = 0; i < MAX_CHEST_INSTANCES; i++)
    {
        delete chestArr[i];
    }
}

void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y)
{

    Rectangle source = { (float)texture_index_x * TILE_WIDTH, (float)texture_index_y * TILE_HEIGHT, (float)TILE_WIDTH, (float)TILE_HEIGHT};
    Rectangle dest = { (float)(pos_x), (float)(pos_y), (float)TILE_WIDTH, (float)TILE_HEIGHT};
    Vector2 origin { 0, 0};
    DrawTexturePro(textures[TEXTURE_TILEMAP], source, dest, origin, 0.0f, WHITE );
}

void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y, float scale) 
{

    Rectangle source = {
        (float)texture_index_x * TILE_WIDTH,
        (float)texture_index_y * TILE_HEIGHT,
        (float)TILE_WIDTH,
        (float)TILE_HEIGHT
    };
    
    float scaledWidth = TILE_WIDTH * scale;
    float scaledHeight = TILE_HEIGHT * scale;
    
    Rectangle dest = { 
        (float)pos_x, 
        (float)pos_y, 
        scaledWidth, 
        scaledHeight 
    };
    
    Vector2 origin = { 0, 0 };
    DrawTexturePro(textures[TEXTURE_TILEMAP], source, dest, origin, 0.0f, WHITE);
}

bool IsBarrierCollision(int x, int y)
{
    int tileX = x / TILE_WIDTH;
    int tileY = y / TILE_HEIGHT;

    //boundary check for all entities
    if (tileX < WORLD_LEFT || tileX > WORLD_RIGHT || tileY < WORLD_TOP || tileY > WORLD_BOTTOM) 
    {
        std::cout << "Boundary Collision!\n";
        return true; 
    }
    
    sTile tile;
    eZones currentZone = Player.GetZone();

    // Get the tile from the zone map
    if (currentZone == ZONE_WORLD) { tile = world[tileX][tileY]; } 
    else if (currentZone == ZONE_DUNGEON) { tile = dungeon[tileX][tileY]; }
    else if (currentZone == ZONE_WORLD_PLAIN_LANDS) { tile = plainLands[tileX][tileY]; }
    else if (currentZone == ZONE_BASEMENT_DUNGEON) { tile = basementDungeon[tileX][tileY]; }
    else if (currentZone == ZONE_ISLAND) { tile = island[tileX][tileY]; }
    else if (currentZone == ZONE_SEA) { tile = sea[tileX][tileY]; }
    else if (currentZone == ZONE_LOST_TEMPLE_ENTRANCE) { tile = lostTemple[tileX][tileY]; }
    else if (currentZone == ZONE_LOST_TEMPLE_LEVEL1) { tile = lostTempleLevel1[tileX][tileY]; }
    else if (currentZone == ZONE_LOST_TEMPLE_LEVEL2) { tile = lostTempleLevel2[tileX][tileY]; }
    else if (currentZone == ZONE_LOST_TEMPLE_BAD_ENDING) { tile = lostTempleBadEnding[tileX][tileY]; }
    else if (currentZone == ZONE_LOST_TEMPLE_GOOD_ENDING) { tile = lostTempleGoodEnding[tileX][tileY]; }
    else { return false; }

    if (isRidingBoat)
    {
        bool isWaterTile = (tile.type >= TILE_TYPE_WATER_TOP_LEFT && tile.type <= TILE_TYPE_WATER_WELL);
        return !isWaterTile; 
    }
    
    else
    {
        if (tile.type == TILE_TYPE_TREE) 
        {
            std::cout << "Tree Collision at (" << tileX << ", " << tileY << ")\n";
            return true;
        }
        else if((tile.type >= TILE_TYPE_WATER_TOP_LEFT && tile.type <= TILE_TYPE_WATER_WELL) || 
                (tile.type == TILE_TYPE_PILLAR || tile.type == TILE_TYPE_BROKEN_PILLAR) ||
                (tile.type >= TILE_TYPE_TOP_LEFT_WALL_CORNER && tile.type <= TILE_TYPE_HOUSE) || 
                tile.type == TILE_TYPE_DOOR_LOCKED||
                tile.type == TILE_TYPE_STONE_WALL) 
        {
            return true;
        }

        //Check for collision with the boat when not riding it
        if (Player.GetZone() == boat.zone1 && x == boat.x && y == boat.y)
        {
            return true;
        }

        //Check for NPC collision
        if(Player.GetZone() == ZONE_WORLD)
        {
            if(x == oldHermit.x && y == oldHermit.y) return true;
            else if(x == woundedKnight.x && y == woundedKnight.y) return true;
        }
        else if(Player.GetZone() == ZONE_WORLD_PLAIN_LANDS)
        {
            if(x == villager1.x && y == villager1.y) return true;
            else if(x == villager2.x && y == villager2.y) return true;
        }
        else if(Player.GetZone() == ZONE_BASEMENT_DUNGEON)
        {
            if(x == basementLockedDoor.x && y == basementLockedDoor.y) return true;
            if(x == weirdMan.x && y == weirdMan.y) return true;
        }
        
        // Check for Item collision
        if(Player.GetZone() == ZONE_DUNGEON)
        {
            if(x == goldenRing.GetPosX() && y == goldenRing.GetPosY() && !goldenRing.IsPickedUp()) return true;
            else if(x == cursedGoldenKey.GetPosX() && y == cursedGoldenKey.GetPosY() && !cursedGoldenKey.IsPickedUp()) return true;
        }
    }

    return false;
}

void DrawHotBar()
{
    Rectangle hotBarRect{5,5, 330, 120};

    DrawRectangleRec(hotBarRect, {36, 38, 36, 255});
    DrawRectangleLinesEx(hotBarRect, 2.0, {178, 204, 214, 255});


    DrawText(TextFormat("Coordinates: (X: %06.2f, Y: %06.2f)", camera.target.x, camera.target.y), 15, 10, 15, WHITE);
    DrawText(TextFormat("Health: %d", Player.GetHealth()), 15, 40, 15, WHITE);

    if(Player.GetHealth() <= 20)
    {
        DrawTile(100, 40, 5, 6, 2.5f );
        DrawTile(125, 40, 4, 6, 2.5f );
        DrawTile(150, 40, 4, 6, 2.5f );
    }
    else if(Player.GetHealth() <= Player.GetMaxHealth() / 2)
    {
        DrawTile(100, 40, 6, 6, 2.5f );
        DrawTile(125, 40, 5, 6, 2.5f );
        DrawTile(150, 40, 4, 6, 2.5f );
    }
    else if(Player.GetHealth() < Player.GetMaxHealth())
    {
        
        DrawTile(100, 40, 6, 6, 2.5f );
        DrawTile(125, 40, 6, 6, 2.5f );
        DrawTile(150, 40, 5, 6, 2.5f );
    }
    else if(Player.GetHealth() == Player.GetMaxHealth()) 
    {
        DrawTile(100, 40, 6, 6, 2.5f );
        DrawTile(125, 40, 6, 6, 2.5f );
        DrawTile(150, 40, 6, 6, 2.5f );
    }

    DrawText(TextFormat("Money: %d", Player.GetMoney()), 15, 70, 15, WHITE);
    DrawText("Press R to cut down tree", 15, 85, 15, WHITE);
}

void CutDownTree()
{
    int TileX = Player.GetX() / TILE_WIDTH;
    int TileY = Player.GetY() / TILE_HEIGHT;
    sTile *tile = nullptr;

    switch (lastKeyPressed)
    {
    case KEY_A: TileX -= 1; break;
    case KEY_D: TileX += 1; break;
    case KEY_W: TileY -= 1; break;
    case KEY_S: TileY += 1; break;
    }

    if(Player.GetZone() == ZONE_WORLD)
    {
        tile = &world[TileX][TileY];
    }
    else if(Player.GetZone() == ZONE_WORLD_PLAIN_LANDS)
    {
        tile = &plainLands[TileX][TileY];
    }
    else if(Player.GetZone() == ZONE_DUNGEON || Player.GetZone() == ZONE_BASEMENT_DUNGEON ||
             Player.GetZone() == ZONE_ISLAND || Player.GetZone() == ZONE_SEA)
    {
        std::cout << "Invalid Zone!\n";
        return;
    }
    // add more zones if needed

    if(tile->type == TILE_TYPE_TREE)
    {
        tile->type = TILE_TYPE_STUMP;
        std::cout << "tree Cut down!\n"; 
        PlaySound(sounds[SOUNDS_TREE_CUTTING]);
    }

}

void CheckIfDungeonCompleted()
{
    //dungeon 1
    if(!plainsKey && currentGameState == IN_DUNGEON)
    {
        if((rat1->IsAlive() == false && rat2->IsAlive() == false) &&
            (vengefulSpirit1->IsAlive() == false && vengefulSpirit2->IsAlive() == false) &&
             (golem1->IsAlive() == false && golem2->IsAlive() == false))
        {   
            StartDialogue({"[You have cleared the dungeon.]"});
            plainsKey = true;
        }
    }

    //basement dungeon
    if(!Act2_BasementCleared && currentGameState == IN_DUNGEON_BASEMENT)
    {
        if((slime1->IsAlive() == false && slime2->IsAlive() == false) &&
            (slime3->IsAlive() == false && slime4->IsAlive() == false) &&
            (dog1->IsAlive() == false && dog2->IsAlive() == false) && dog3->IsAlive() == false)
        {
            Act2_BasementCleared = true;
            StartDialogue({"[You have cleared the basement dungeon.]"});
        }
    }

}