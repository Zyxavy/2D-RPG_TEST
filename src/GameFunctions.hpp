#ifndef GAME_FUNCTIONS_HPP
#define GAME_FUNCTIONS_HPP

#include <raylib.h>
#include <raymath.h>
#include <string>


//constants
const int screenWidth = 800;
const int screenHeight = 600;


//definitions
#define MAX_TEXTURES 1
#define TILE_WIDTH 8
#define TILE_HEIGHT  8
#define MAX_SOUNDS 5
#define WORLD_WIDTH 25
#define WORLD_HEIGHT 25

//border definitions
#define WORLD_LEFT 0
#define WORLD_RIGHT 24
#define WORLD_TOP 0
#define WORLD_BOTTOM 24


//typedef & enums
typedef enum 
{
    TEXTURE_TILEMAP = 0
} texture_asset;

typedef enum 
{
    SOUND_FOOT_GRASS = 0,
    SOUND_FOOT_STONE,
    SOUNDS_ATTACK,
    SOUND_DEATH,
    SOUND_COINS,
} sound_asset;

typedef enum
{
    TILE_TYPE_DIRT = 0,
    TILE_TYPE_GRASS,
    TILE_TYPE_TREE,
    TILE_TYPE_STONE,

} tile_type;

typedef struct
{
    int x;
    int y;
    int type;

} sTile;

typedef enum
{
   ZONE_ALL = 0,
   ZONE_BATTLE,
   ZONE_WORLD,
   ZONE_DUNGEON

} eZones;


//externs
extern Texture2D textures[MAX_TEXTURES];
extern Sound sounds[MAX_SOUNDS];
extern sTile world[WORLD_WIDTH][WORLD_HEIGHT];
extern sTile dungeon[WORLD_WIDTH][WORLD_HEIGHT];
extern Camera2D camera;
extern bool isInventory;

//functions
void GameStartup();
void GameUpdate();
void GameRender();
void GameShutdown();

void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y);
void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y, float scale);
bool IsBarrierCollision(int x, int y);
void Inventory();
void CheckContactWithEnemies();


#endif // GAME_FUNCTIONS_HPP