#include "GameFunctions.hpp"
#include "BattleSystem.hpp"
#include "GameMenu.hpp"
#include "Entities.hpp"
#include "MusicFunctions.hpp"
#include "Enemy.hpp"
#include "Heroes.hpp"
#include <iostream>


sEntity chest = { 0 };
Camera2D camera { 0 };

Texture2D textures[MAX_TEXTURES];
Texture2D pagePictures[MAX_PAGE_PICTURES];
Sound sounds[MAX_SOUNDS];
sTile world[WORLD_WIDTH][WORLD_HEIGHT];
sTile dungeon[WORLD_WIDTH][WORLD_HEIGHT];
sTile tutorialWorld[WORLD_WIDTH][WORLD_HEIGHT]; // WIP
bool isInventory = false;
int count;
int lastKeyPressed;

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
    for(int i = 0; i < WORLD_WIDTH; i++){
        for(int j = 0; j < WORLD_HEIGHT; j++){
            world[i][j] = (sTile)
            {
                .x = i,
                .y = j,
                .type = GetRandomValue(TILE_TYPE_DIRT, TILE_TYPE_TREE)
            };

            dungeon[i][j] = (sTile)
            {
                .x = i,
                .y = j,
                .type = TILE_TYPE_DIRT
            };

            tutorialWorld[i][j] = (sTile) // WIP
            {
                .x = i,
                .y = j,
                .type = GetRandomValue(TILE_TYPE_DIRT, TILE_TYPE_GRASS)
            };

        }
    }

    //initialize entities
    EntitiesInit();

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

        else if (IsKeyPressed(KEY_TAB))
        {
            int num = GetRandomValue(1,4);
            std::cout << "Tab was pressed\n";
            switch (num)
            {
            case 1:
                y -= TILE_HEIGHT;
                break;
            case 2:
                y += TILE_HEIGHT;
                break;
            case 3: 
                x -= TILE_WIDTH;
                break;
            case 4:
                x += TILE_WIDTH;
                break;
            }

        }

        if(IsKeyPressed(KEY_R))
        {
            CutDownTree();
        }

        if(Player.GetX() == chest.x && Player.GetY() == chest.y && chest.isAlive) //interact with chest
        {
            Player.SetMoney(Player.GetMoney() + chest.money);
            Player.SetHealthPotions(Player.GetRemainingHealthPotions() + chest.healthPotions);
            Player.SetEnergyFoods(Player.GetRemainingEnergyFoods() + chest.energyFoods );
            chest.isAlive = false;
            PlaySound(sounds[SOUND_COINS]);
        }

        //Player Escapes and stuns enemy
        if (hasKeyPressed) {

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
                if(Player.GetZone() == ZONE_WORLD) PlaySound(sounds[SOUND_FOOT_GRASS]);
                else if (Player.GetZone() == ZONE_DUNGEON) PlaySound(sounds[SOUND_FOOT_STONE]);

            }

            //confirm and set the X&Y coords
            Player.SetX(x);
            Player.SetY(y);

            //Camera Follows Player
            camera.target = (Vector2) {(float)Player.GetX(), (float)Player.GetY()};
        

    
        if(IsKeyPressed(KEY_E))
        {
            //Enter dungeon
            if(Player.GetX() == dungeon_gate.x &&
                Player.GetY() == dungeon_gate.y)
                {
                    if(Player.GetZone() == ZONE_WORLD)
                    {
                        Player.SetZone(ZONE_DUNGEON);
                    }
                    else if(Player.GetZone() == ZONE_DUNGEON)
                    {
                        Player.SetZone(ZONE_WORLD);
                    }
                }
                
        }
        else if(IsKeyPressed(KEY_Q))
        {
            if(isInventory == false) {isInventory = true;}
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
                else if (Player.GetZone() == ZONE_TUTORIAL) // WIP
                {
                    tile = tutorialWorld[i][j];
                }

                switch (tile.type)
                {
                    case TILE_TYPE_DIRT:
                        texture_index_x = 4;
                        texture_index_y = 4;
                        break;
                    case TILE_TYPE_GRASS:
                        texture_index_x = 5;
                        texture_index_y = 4;
                        break;
                    case TILE_TYPE_TREE:  //This is tree
                        texture_index_x = 4;
                        texture_index_y = 5;
                        break;
                    case TILE_TYPE_STONE:
                        texture_index_x = 1;
                        texture_index_y = 6;
                        break;
                    case TILE_TYPE_STUMP:
                        texture_index_x = 8;
                        texture_index_y = 3;
                        break;
                    default:
                        break;
                }

                DrawTile(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, texture_index_x, texture_index_y);
            }
            
        }

        //Borders
        for (int x = 0; x < WORLD_WIDTH; x++) {
            DrawTile(x * TILE_WIDTH, WORLD_TOP * TILE_HEIGHT, 13, 1); // Top 
            DrawTile(x * TILE_WIDTH, WORLD_BOTTOM * TILE_HEIGHT, 13, 1); // Bottom 
        }
        for (int y = 0; y < WORLD_HEIGHT; y++) {
            DrawTile(WORLD_LEFT * TILE_WIDTH, y * TILE_HEIGHT, 13, 1); // Left 
            DrawTile(WORLD_RIGHT * TILE_WIDTH, y * TILE_HEIGHT, 13, 1); // Right 
        }

        //Gate
        DrawTile(dungeon_gate.x, dungeon_gate.y, 8, 9); 
        // enemies
        EnemyRender();
        // player
        PlayerRender();

        EndMode2D();

        // Top-left thingy
        DrawHotBar();

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

    for(int i = 0; i < MAX_ORCS_INSTANCES; i++)
    {
        delete orcArr[i];
    }
    
    for(int i = 0; i < MAX_WANDERING_EYE_INSTANCES; i++)
    {
        delete eyeArr[i];
    }

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

    // Check for trees
    if (tile.type == TILE_TYPE_TREE) 
    {
        std::cout << "Tree Collision at (" << tileX << ", " << tileY << ")\n";
        return true;
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