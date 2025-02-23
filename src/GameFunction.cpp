#include "GameFunctions.hpp"


sEntity chest = { 0 };
Camera2D camera { 0 };

bool battleMode = false;
bool playerTurn = true; 
bool playerDefending = false;

Texture2D textures[MAX_TEXTURES];
Sound sounds[MAX_SOUNDS];
Music music[MAX_MUSIC];
sTile world[WORLD_WIDTH][WORLD_HEIGHT];
sTile dungeon[WORLD_WIDTH][WORLD_HEIGHT];
sEntity player, dungeon_gate, orc;


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

    

    player = (sEntity)
    {
        .x = TILE_WIDTH * 3,
        .y = TILE_HEIGHT * 3,
        .zone = ZONE_WORLD,
        .isAlive = true,
        .isPassable = false,
        .health = 100,
        .damage = 0, 
        .money = 1000,
        .experience = 0,
    };

    dungeon_gate = (sEntity)
    {
        .x = TILE_WIDTH * 10,
        .y = TILE_HEIGHT * 10,
        .zone = ZONE_ALL,
    };

    orc = (sEntity)
    {
        .x = TILE_WIDTH * 5,
        .y = TILE_HEIGHT * 5,
        .zone = ZONE_DUNGEON,
        .isAlive = true,
        .isPassable = false,
        .health = 100,
        .damage = 0,
        .experience = GetRandomValue(10,100),
    };

    //cameras
    camera.target = (Vector2) { (float)player.x, (float)player.y};
    camera.offset = (Vector2) { (float)screenWidth / 2, (float)screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;

    //Sounds/Music
    sounds[SOUND_FOOT_GRASS]  = LoadSound("assets/GrassWalk.mp3");
    sounds[SOUND_FOOT_STONE]  = LoadSound("assets/Stonewalk.wav");
    sounds[SOUNDS_ATTACK]  = LoadSound("assets/hitHurt.wav");
    sounds[SOUND_DEATH]  = LoadSound("assets/death.wav");
    sounds[SOUND_COINS]  = LoadSound("assets/pickupCoin.wav");

    music[MUSIC_DARK] = LoadMusicStream("assets/Dark Ambient 2.wav");
    music[MUSIC_LIGHT] = LoadMusicStream("assets/Light Ambience 3.wav");

    PlayMusicStream(music[MUSIC_LIGHT]);
}

void GameUpdate() {

    if(player.zone == ZONE_WORLD) UpdateMusicStream(music[MUSIC_LIGHT]);
    else if(player.zone == ZONE_DUNGEON) UpdateMusicStream(music[MUSIC_DARK]);

    if(battleMode)
    {
        BattleUpdate();
    }
    else
    {

    float x = player.x;
    float y = player.y;
    bool hasKeyPressed = false;

    if(IsKeyPressed(KEY_LEFT))
    {
        x -= 1 * TILE_WIDTH;
        hasKeyPressed = true;
    }
    else if(IsKeyPressed(KEY_RIGHT))
    {
        x += 1 * TILE_WIDTH;
        hasKeyPressed = true;
    }
    else if(IsKeyPressed(KEY_UP))
    {
        y -= 1 * TILE_HEIGHT;
        hasKeyPressed = true;
    }
    else if(IsKeyPressed(KEY_DOWN))
    {
        y += 1 * TILE_HEIGHT;
        hasKeyPressed = true;
    }


    float wheel = GetMouseWheelMove();
    if(wheel != 0) { 
        const float zoomIncrement = 0.125f;
        camera.zoom += (wheel * zoomIncrement);
        if(camera.zoom < 3.0f) camera.zoom = 3.0f;
        if(camera.zoom > 9.0f) camera.zoom = 9.0f;
    }

    //CHECK BATTLE
    if (player.zone == orc.zone && orc.x == x && orc.y == y && orc.isAlive) {
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
                    StopMusicStream(music[MUSIC_LIGHT]);
                    PlayMusicStream(music[MUSIC_DARK]);
                }
                else if(player.zone == ZONE_DUNGEON)
                {
                    player.zone = ZONE_WORLD;
                    StopMusicStream(music[MUSIC_DARK]);
                    PlayMusicStream(music[MUSIC_LIGHT]);
                }
            }
            else if(player.x == chest.x &&
                player.y == chest.y)
                {
                   player.money += chest.money;
                   chest.isAlive = false;
                   PlaySound(sounds[SOUND_COINS]);
                }
    }
    
}

}

void GameRender() {
    
    if(battleMode)
    {
        BattleRender();
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

    //Gate
    DrawTile(dungeon_gate.x, dungeon_gate.y, 8, 9); 

    // orc
    if(orc.zone == player.zone)
    {
        if(orc.isAlive == true) DrawTile(orc.x, orc.y, 11, 0);

        //Draw chest
        if(chest.isAlive) { DrawTile(chest.x, chest.y, 9 ,3);}
    }
    // player
    DrawTile(camera.target.x, camera.target.y, 5, 0); 


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

    if(orc.isAlive) DrawText(TextFormat("Orc Health: %d", orc.health), 15, 90, 14, WHITE);
}
}

void GameShutdown() {

    for(int i = 0; i < MAX_TEXTURES; i++){
        UnloadTexture(textures[i]);
    }

    for(int i = 0; i < MAX_SOUNDS; i++){
        UnloadSound(sounds[i]);
    }

    for(int i = 0; i < MAX_MUSIC; i++){
        StopMusicStream(music[i]);
        UnloadMusicStream(music[i]);
    }

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

void BattleUpdate() {
    Vector2 mousePos = GetMousePosition();
    if(orc.health <= 0) 
    {   
        orc.isAlive = false;
        battleMode = false;
        player.experience += orc.experience;
        PlaySound(sounds[SOUND_DEATH]);

        chest.x = orc.x;
            chest.y = orc.y;
            chest.isAlive = true;
            chest.money = GetRandomValue(23, 205);
    } 
    else if(player.health <= 0)
    {
        player.isAlive = false;
        battleMode = false;
        PlaySound(sounds[SOUND_DEATH]);
        //Continue
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        //Attack 
        if (CheckCollisionPointRec(mousePos, (Rectangle){120, 500, 150, 40}) && playerTurn) {
            int damage = GetRandomValue(5, 15);
            orc.health -= damage;
            playerTurn = false;
            playerDefending = false;
            PlaySound(sounds[SOUNDS_ATTACK]);
        }
        //Defend
        else if (CheckCollisionPointRec(mousePos, (Rectangle){320, 500, 150, 40}) && playerTurn) {
            playerDefending = true;
            playerTurn = false;
        }
        //Run
        else if (CheckCollisionPointRec(mousePos, (Rectangle){520, 500, 150, 40}) && playerTurn) {
            if (GetRandomValue(0, 1) == 1) {  
                battleMode = false;
            }
            playerTurn = false;
        }
    }
    if (!playerTurn && orc.health > 0) {
        int orcDamage = GetRandomValue(3, 10);
        if (playerDefending) orcDamage /= 2;
        player.health -= orcDamage;
        playerTurn = true;
    }
}

void BattleRender() {
    DrawRectangle(0, 0, screenWidth, screenHeight, DARKGRAY);
    DrawText("BATTLE!", 350, 30, 20, WHITE);

    Rectangle rec {40, 50, (screenWidth - 40) - 40, (screenHeight-50) - 150};
    DrawRectangleLinesEx(rec, 4.5, BLACK);

    DrawTile(200, 350, 5, 0, 10.0f);   //Player 
    DrawTile(500, 350, 11, 0, 10.0f);  //Orc

    DrawText(TextFormat("Orc HP: %d", orc.health), 480, 330, 20, RED);
    DrawText(TextFormat("Player HP: %d", player.health), 180, 330, 20, GREEN);

    //Draw Buttons 
    DrawRectangle(20, 470, 760, 300, BLACK);
    DrawRectangle(120, 500, 150, 40, LIGHTGRAY);
    DrawRectangle(320, 500, 150, 40, LIGHTGRAY);
    DrawRectangle(520, 500, 150, 40, LIGHTGRAY);

    DrawText("ATTACK", 150, 510, 20, BLACK);
    DrawText("DEFEND", 350, 510, 20, BLACK);
    DrawText("RUN", 570, 510, 20, BLACK);
}


