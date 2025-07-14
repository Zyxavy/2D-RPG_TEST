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
bool isInventory = false;
int count;
int lastKeyPressed;
GameState currentGameState;
GameState prevGameState;

void GameStartup() 
{

    InitAudioDevice();

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
                .type = GetRandomValue(TILE_TYPE_DIRT, TILE_TYPE_GRASS)
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
    
    LoadMusic();
}

void GameUpdate() 
{

    //Music
    UpdateMusic();
    if(Player.GetZone() == ZONE_WORLD && currentMusicZone != LIGHT) {PlayRandomMusic(LIGHT);}
    else if(Player.GetZone() == ZONE_DUNGEON && currentMusicZone != DARK) {PlayRandomMusic(DARK);}
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

        if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            lastKeyPressed = KEY_A;
            if (!IsBarrierCollision(Player.GetX() - TILE_WIDTH, Player.GetY())) 
            { 
                x -= TILE_WIDTH;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            lastKeyPressed = KEY_D;
            if (!IsBarrierCollision(Player.GetX() + TILE_WIDTH, Player.GetY()))
            {  
                x += TILE_WIDTH;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_UP)|| IsKeyPressed(KEY_W)) {
            lastKeyPressed = KEY_W;
            if (!IsBarrierCollision(Player.GetX(), Player.GetY() - TILE_HEIGHT))
            {  
                y -= TILE_HEIGHT;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) { 
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
        }
        
        //mouse wheel zoom
        float wheel = GetMouseWheelMove();
        if(wheel != 0) { 
            const float zoomIncrement = 0.125f;
            camera.zoom += (wheel * zoomIncrement);
            if(camera.zoom < 3.0f) camera.zoom = 3.0f;
            if(camera.zoom > 9.0f) camera.zoom = 9.0f;
        }

        //CHECK Contact with enemies
        CheckContactWithEnemies();
        
        if(hasKeyPressed) // Play FootSteps FX
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
            //Enter dungeon / gates
            EnterGates();
            //Interact with NPCs
            InteractWithNPCs();
        }
        else if(IsKeyPressed(KEY_Q))
        {
            if(isInventory == false) {isInventory = true;}
        }
    
    }

    //stories and etc
    
    


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

                RenderTile(tile, texture_index_x, texture_index_y);

                DrawTile(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, texture_index_x, texture_index_y);
            }
            
        }


        //Gate
        RenderGates();
        // enemies | Npcs
        EnemyRender();
        RenderNPCs();
        RenderItems();
        // player
        PlayerRender();

        EndMode2D();

        // Top-left thingy
        DrawHotBar();
        dungeonKey = true;

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
        default:
            break;
    }
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

    for(int i = 0; i < MAX_CRAB_THING_INSTANCES; i++)
    {
        delete crabArr[i];
    }


    //
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
    sTile tile;

    if (Player.GetZone() == ZONE_WORLD) 
    {
        tile = world[tileX][tileY];
    } else if (Player.GetZone() == ZONE_DUNGEON) 
    {
        tile = dungeon[tileX][tileY];
    }
    else if (Player.GetZone() == ZONE_WORLD_PLAIN_LANDS) 
    {
        tile = plainLands[tileX][tileY];
    } else
    {
        return false; 
    }

    //check if collides with barriers
    if (tileX < WORLD_LEFT + 1 || tileX > WORLD_RIGHT - 1 || tileY < WORLD_TOP + 1 || tileY > WORLD_BOTTOM - 1) 
    {
        std::cout << "Barrier Collision!\n";
        return true; 
    }

    // Check for tiles
    if (tile.type == TILE_TYPE_TREE) 
    {
        std::cout << "Tree Collision at (" << tileX << ", " << tileY << ")\n";
        return true;
    }
    else if((tile.type >= TILE_TYPE_WATER_TOP_LEFT && tile.type <= TILE_TYPE_WATER_VERTICAL) || (tile.type == TILE_TYPE_PILLAR || tile.type == TILE_TYPE_BROKEN_PILLAR))
    {
        return true;
    }

    //Npcs
    if(Player.GetZone() == ZONE_WORLD)
    {
        if(x == oldHermit.x && y == oldHermit.y) return true;
        else if(x == woundedKnight.x && y == woundedKnight.y) return true;
    }

    //items
    if(Player.GetZone() == ZONE_DUNGEON)
    {
        if(x == goldenRing.GetPosX() && y == goldenRing.GetPosY() && !goldenRing.IsPickedUp()) return true;
    }

    return false;
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
    else if(Player.GetZone() == ZONE_DUNGEON)
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

    
}

void EnterGates()
{
    if(Player.GetX() == dungeon_gate.x && Player.GetY() == dungeon_gate.y)
    {
        if(dungeonKey)
        {
            if(Player.GetZone() == ZONE_WORLD)
            {
                Player.SetZone(dungeon_gate.zone2);
                currentGameState = IN_DUNGEON;
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
        CheckIfDungeonCompleted();
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
            }
        }
        else
        {
            StartDialogue({"Defeat all enemies first to Enter."});
        }
        return;
    }
}

void InteractWithNPCs()
{
    if(abs(Player.GetX() - oldHermit.x) <= TILE_WIDTH && 
       abs(Player.GetY() - oldHermit.y) <= TILE_HEIGHT &&
        Player.GetZone() == oldHermit.zone1)
    {
        Act1_HermitLine();
        Player.SetHealthPotions(Player.GetRemainingHealthPotions() + 2);
    }
    else if(abs(Player.GetX() - woundedKnight.x) <= TILE_WIDTH && 
            abs(Player.GetY() - woundedKnight.y) <= TILE_HEIGHT &&
        Player.GetZone() == woundedKnight.zone1)
    {
        Act1_WoundedKnight();
        Player.SetEnergyFoods(Player.GetRemainingEnergyFoods() + 2);
    }
}

void CheckIfDungeonCompleted()
{
    //dungeon 1
    if(!plainsKey)
    {
        if((rat1->IsAlive() == false && rat2->IsAlive() == false) &&
            (vengefulSpirit1->IsAlive() == false && vengefulSpirit2->IsAlive() == false) &&
             (golem1->IsAlive() == false && golem2->IsAlive() == false))
        {
            plainsKey = true;
        }
    }

}

