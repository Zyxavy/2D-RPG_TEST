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
Sound sounds[MAX_SOUNDS];
sTile world[WORLD_WIDTH][WORLD_HEIGHT];
sTile dungeon[WORLD_WIDTH][WORLD_HEIGHT];
bool isInventory = false;
int count;


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

    LoadMusic();
}

void GameUpdate() {

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

        float x = Player.GetX();
        float y = Player.GetY();
        bool hasKeyPressed = false;
    
        if(IsKeyPressed(KEY_LEFT)) {
            if (!IsBarrierCollision(Player.GetX() - TILE_WIDTH, Player.GetY())) 
            { 
                x -= TILE_WIDTH;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_RIGHT)) {
            if (!IsBarrierCollision(Player.GetX() + TILE_WIDTH, Player.GetY()))
            {  
                x += TILE_WIDTH;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_UP)) {
            if (!IsBarrierCollision(Player.GetX(), Player.GetY() - TILE_HEIGHT))
            {  
                y -= TILE_HEIGHT;
                hasKeyPressed = true;
            }
        }
        else if(IsKeyPressed(KEY_DOWN)) {
            if (!IsBarrierCollision(Player.GetX(), Player.GetY() + TILE_HEIGHT))
            {  
                y += TILE_HEIGHT;
                hasKeyPressed = true;
            }
        }

        if (hasKeyPressed) {
            if(!orc.GetStunStatus())  orc.MoveAI(Player.GetX(), Player.GetY());
            else{
                
                orc.SetStunCounter(count);
                if(count > 3) 
                {
                    orc.SetStunStatus(false);
                    count = 0;
                    
                }
            }
            if(!wanderingEye.GetStunStatus()) wanderingEye.MoveAI(Player.GetX(), Player.GetY());
            else{
                
                wanderingEye.SetStunCounter(count);
                if(count > 3) 
                {
                    wanderingEye.SetStunStatus(false);
                    count = 0;
                }
            }
            if(wanderingEye.GetStunStatus() || orc.GetStunStatus() )
            {
                count++;
                std::cout << count;
            }
        }
        

        float wheel = GetMouseWheelMove();
        if(wheel != 0) { 
            const float zoomIncrement = 0.125f;
            camera.zoom += (wheel * zoomIncrement);
            if(camera.zoom < 3.0f) camera.zoom = 3.0f;
            if(camera.zoom > 9.0f) camera.zoom = 9.0f;
        }

        //CHECK Contact with enemies
        CheckContactWithEnemies();

            if(hasKeyPressed) 
            {
                if(Player.GetZone() == ZONE_WORLD) PlaySound(sounds[SOUND_FOOT_GRASS]);
                else if (Player.GetZone() == ZONE_DUNGEON) PlaySound(sounds[SOUND_FOOT_STONE]);

            }

            Player.SetX(x);
            Player.SetY(y);
            
            camera.target = (Vector2) {(float)Player.GetX(), (float)Player.GetY()};
        

    
        if(IsKeyPressed(KEY_E))
        {
            std::cout << "Key pressed to enter\n";
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
                else if(Player.GetX() == chest.x && Player.GetY() == chest.y && chest.isAlive)
                    {
                    Player.SetMoney(chest.money);
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
                if(Player.GetZone() == ZONE_WORLD)
                {
                    tile = world[i][j];
                }
                else if (Player.GetZone() == ZONE_DUNGEON)
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
        DrawText(TextFormat("Health: %d", Player.GetHealth()), 15, 30, 14, WHITE);
        DrawText(TextFormat("Player XP: %d", Player.GetExperience()), 15, 50, 14, WHITE);
        DrawText(TextFormat("Money: %d", Player.GetMoney()), 15, 70, 14, WHITE);

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

void CheckContactWithEnemies()
{
    if (Player.GetZone() == orc.GetZone() && Player.GetX() == orc.GetX() && Player.GetY() == orc.GetY() && orc.IsAlive() == true) {
        enemy = orc; 
        battleMode = true;
        
    }
    else if (Player.GetZone() == wanderingEye.GetZone() && Player.GetX() == wanderingEye.GetX() && Player.GetY() == wanderingEye.GetY() && wanderingEye.IsAlive() == true) {
        enemy = wanderingEye; 
        battleMode = true;
    }


}


