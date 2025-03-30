#include "GameFunctions.hpp"
#include "BattleSystem.hpp"
#include "GameMenu.hpp"
#include "Entities.hpp"
#include <iostream>
#include "MusicFunctions.hpp"
#include "Enemy.hpp"


sEntity chest = { 0 };
Camera2D camera { 0 };

Texture2D textures[MAX_TEXTURES];
Sound sounds[MAX_SOUNDS];
sTile world[WORLD_WIDTH][WORLD_HEIGHT];
sTile dungeon[WORLD_WIDTH][WORLD_HEIGHT];
bool isInventory = false;


void GameStartup() {

    InitAudioDevice();

    Image image = LoadImage("assets/colored_tilemap_packed.png");
    textures[TEXTURE_TILEMAP] = LoadTextureFromImage(image);
    UnloadImage(image);

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

        }
    }

    //initialize entities
    EntitiesInit();

    //cameras
    camera.target = (Vector2) { (float)player.x, (float)player.y};
    camera.offset = (Vector2) { (float)screenWidth / 2, (float)screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 4.0f;

    //Sounds/Music
    sounds[SOUND_FOOT_GRASS]  = LoadSound("assets/GrassWalk.mp3");
    sounds[SOUND_FOOT_STONE]  = LoadSound("assets/Stonewalk.wav");
    sounds[SOUNDS_ATTACK]  = LoadSound("assets/hitHurt.wav");
    sounds[SOUND_DEATH]  = LoadSound("assets/death.wav");
    sounds[SOUND_COINS]  = LoadSound("assets/pickupCoin.wav");

    LoadMusic();
}

void GameUpdate() {

    UpdateMusic();
    if(player.zone == ZONE_WORLD && currentMusicZone != LIGHT) {PlayRandomMusic(LIGHT);}
    else if(player.zone == ZONE_DUNGEON && currentMusicZone != DARK) {PlayRandomMusic(DARK);}
    else if (player.zone == ZONE_BATTLE && currentMusicZone != ACTION){ PlayRandomMusic(ACTION);}

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

        float x = player.x;
        float y = player.y;
        bool hasKeyPressed = false;
    
        if(IsKeyPressed(KEY_LEFT)) {
            if (!IsBarrierCollision(player.x - TILE_WIDTH, player.y)) 
            { 
                x -= TILE_WIDTH;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_RIGHT)) {
            if (!IsBarrierCollision(player.x + TILE_WIDTH, player.y))
            {  
                x += TILE_WIDTH;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_UP)) {
            if (!IsBarrierCollision(player.x, player.y - TILE_HEIGHT))
            {  
                y -= TILE_HEIGHT;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_DOWN)) {
            if (!IsBarrierCollision(player.x, player.y + TILE_HEIGHT))
            {  
                y += TILE_HEIGHT;
                hasKeyPressed = true;
            }
        }

        if (hasKeyPressed) {
            orc.MoveAI(player.x, player.y);
            wanderingEye.MoveAI(player.x, player.y);
        }
        

        float wheel = GetMouseWheelMove();
        if(wheel != 0) { 
            const float zoomIncrement = 0.125f;
            camera.zoom += (wheel * zoomIncrement);
            if(camera.zoom < 3.0f) camera.zoom = 3.0f;
            if(camera.zoom > 9.0f) camera.zoom = 9.0f;
        }

        //CHECK Contact with enemies
        if (player.zone == orc.GetZone() && player.x == orc.GetX() && player.y == orc.GetY() && orc.IsAlive() == true) {
            enemy = orc; 
            battleMode = true;
            
        }
        else if (player.zone == wanderingEye.GetZone() && player.x == wanderingEye.GetX() && player.y == wanderingEye.GetY() && wanderingEye.IsAlive() == true) {
            enemy = wanderingEye; 
            battleMode = true;
        }

        else
        {
            if(hasKeyPressed) 
            {
                if(player.zone == ZONE_WORLD) PlaySound(sounds[SOUND_FOOT_GRASS]);
                else if (player.zone == ZONE_DUNGEON) PlaySound(sounds[SOUND_FOOT_STONE]);

            }
            player.x = x;
            player.y = y;
            
            camera.target = (Vector2) {(float)player.x, (float)player.y};
        }

    
        if(IsKeyPressed(KEY_E))
        {
            if(player.x == dungeon_gate.x &&
                player.y == dungeon_gate.y)
                {
                    if(player.zone == ZONE_WORLD)
                    {
                        player.zone = ZONE_DUNGEON; 
                    }
                    else if(player.zone == ZONE_DUNGEON)
                    {
                        player.zone = ZONE_WORLD;
                    }
                }
                else if(player.x == chest.x && player.y == chest.y && chest.isAlive)
                    {
                    player.money += chest.money;
                    chest.isAlive = false;
                    PlaySound(sounds[SOUND_COINS]);
                    }
        }
        else if(IsKeyPressed(KEY_Q))
        {
            if(isInventory == false) {isInventory = true;}
        }
    
    }

}

void GameRender() {
    
    if(battleMode)
    {
        BattleRender(enemy);
    }
    else if(isInventory)
    {
        Inventory();
    }
    else{
        BeginMode2D(camera);

        sTile tile;
        int texture_index_x = 0;
        int texture_index_y = 0;

        for(int i = 0; i < WORLD_WIDTH; i++){
            for (int j = 0; j < WORLD_HEIGHT; j++){
                if(player.zone == ZONE_WORLD)
                {
                    tile = world[i][j];
                }
                else if (player.zone == ZONE_DUNGEON)
                {
                    tile = dungeon[i][j];
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
                    case TILE_TYPE_TREE:
                        texture_index_x = 4;
                        texture_index_y = 5;
                        break;
                    case TILE_TYPE_STONE:
                        texture_index_x = 1;
                        texture_index_y = 6;
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

        DrawRectangle(5, 5, 330, 120, Fade(GRAY, 2.0f));
        DrawRectangleLines(5, 5, 330, 120, BLACK);
        DrawText(TextFormat("Coordinates: (X: %06.2f, Y: %06.2f)", camera.target.x, camera.target.y), 15, 10, 14, WHITE);
        DrawText(TextFormat("Health: %d", player.health), 15, 30, 14, WHITE);
        DrawText(TextFormat("Player XP: %d", player.experience), 15, 50, 14, WHITE);
        DrawText(TextFormat("Money: %d", player.money), 15, 70, 14, WHITE);

        DrawText(TextFormat("Arrow Keys to move "), 180, 30, 15, WHITE);
        DrawText(TextFormat("Press E to interact"), 180, 50, 15, WHITE);
        DrawText(TextFormat("Mouse Wheel to zoom"), 180, 70, 15, WHITE);
        DrawText(TextFormat("Press Q to Open Invetory"), 140, 90, 15, WHITE);

    }
}

void GameShutdown() {

    for(int i = 0; i < MAX_TEXTURES; i++){
        UnloadTexture(textures[i]);
    }

    for(int i = 0; i < MAX_SOUNDS; i++){
        UnloadSound(sounds[i]);
    }

    StopCurrentMusic();
    UnloadMusic();
    CloseAudioDevice();
    
}

void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y){
    Rectangle source = { (float)texture_index_x * TILE_WIDTH, (float)texture_index_y * TILE_HEIGHT, (float)TILE_WIDTH, (float)TILE_HEIGHT};
    Rectangle dest = { (float)(pos_x), (float)(pos_y), (float)TILE_WIDTH, (float)TILE_HEIGHT};
    Vector2 origin { 0, 0};
    DrawTexturePro(textures[TEXTURE_TILEMAP], source, dest, origin, 0.0f, WHITE );
}

void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y, float scale) {
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

    if (tileX < WORLD_LEFT + 1 || tileX > WORLD_RIGHT - 1 || tileY < WORLD_TOP + 1 || tileY > WORLD_BOTTOM - 1) {
        std::cout << "Barrier Collision!\n";
        return true; 
    }

    return false;
}

void Inventory()
{
    Vector2 mousePos = GetMousePosition();

    Rectangle outer {20, 20, 760, 560};
    Rectangle inner {40, 40, 720, 520};
    Rectangle header {270, 20, 250, 50};
    Rectangle exitButton {20, 20, 50, 50};
    Rectangle charBorder {530, 60, 220, 500};
    Rectangle health{ 535, 275, 25, 25};
    Rectangle defense{ 650, 280, 25, 25};
    Rectangle damage{ 535, 340, 25, 25};
    

    DrawRectangleRounded(outer, 0.2, 2, GRAY);
    DrawRectangleRounded(inner, 0.2, 2, LIGHTGRAY);
    DrawRectangleRounded(header, 0.1, 1, BLACK);
    DrawRectangleRounded(exitButton, 0.2, 4, WHITE);

    DrawRectangleLinesEx(charBorder, 4, BLACK);

    DrawText("INVENTORY", 300, 25, 30, WHITE); // header
    DrawText("X", 28, 22, 46, BLACK); // exit Buttoon
    
    if(player.name == Knight.name)  DrawTile(560, 80, 6, 0, 20.0f);
    else if(player.name == Wizard.name)  DrawTile(560, 80, 9, 0, 20.0f); 
    else if(player.name == Rouge.name)  DrawTile(560, 80, 8, 0, 20.0f);

    DrawText(TextFormat("Type: %s ", player.type.c_str()), 535, 240, 20, BLACK);

    DrawText(TextFormat("%d", player.health), 580, 290, 25, BLACK );
    DrawTile(535, 280, 6, 6, 5.0f);

    DrawText(TextFormat("%d", player.defense), 700, 290, 25, BLACK );
    DrawTile(650, 280, 9, 6, 5.0f);

    DrawText(TextFormat("Avg: %d", (player.damageMax + player.damageMin) / 2), 580, 340, 25, BLACK );
    DrawTile(535, 330, 6, 4, 5.0f);

    DrawText(TextFormat("Level: %d", player.level ), 580, 390, 25, BLACK );
    DrawTile(535, 390, 8, 5, 5.0f);
    

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if(CheckCollisionPointRec(mousePos, exitButton))
        {
            isInventory = false;
        }
    }

    if(CheckCollisionPointRec(mousePos, health))
    {
        DrawRectangle(500, 290, 200, 200, BLACK);
        DrawText(TextFormat("Current health: %d", player.health), 510, 300, 18, WHITE );
        DrawText(TextFormat("Max health: %d", player.maxHealth), 510, 320, 18, WHITE );
        DrawText(TextFormat("The amount of hits a \nHero can recieve"), 510, 345, 18, WHITE );
    } 
    else if (CheckCollisionPointRec(mousePos, defense))
    {
        DrawRectangle(550, 290, 200, 200, BLACK);
        DrawText(TextFormat("%d damage is reduced \nfrom enemy attacks", player.defense), 555, 300, 18, WHITE );
    }
    else if (CheckCollisionPointRec(mousePos, damage))
    {
        DrawRectangle(500, 300, 220, 200, BLACK);
        DrawText(TextFormat("Minimun Attack damage: %d", player.damageMin ), 510, 310, 15, WHITE );
        DrawText(TextFormat("Maximum Attack damage: %d", player.damageMax ), 510, 330, 15, WHITE );
        DrawText(TextFormat("The hero deals %d - %d \namount of damage \ndepending on RNG", player.damageMin, player.damageMax), 510, 370, 18, WHITE );
    }
    



}
