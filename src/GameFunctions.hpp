#ifndef GAME_FUNCTIONS_HPP
#define GAME_FUNCTIONS_HPP

#include <raylib.h>
#include <raymath.h>


//constants
const int screenWidth = 800;
const int screenHeight = 600;

//definitions
#define MAX_TEXTURES 1
#define TILE_WIDTH 8
#define TILE_HEIGHT  8
#define MAX_SOUNDS 5
#define MAX_MUSIC 2
#define WORLD_WIDTH 25
#define WORLD_HEIGHT 25

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
    MUSIC_LIGHT = 0,
    MUSIC_DARK,
} music_asset;

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
   ZONE_WORLD,
   ZONE_DUNGEON

} eZones;

typedef struct 
{
    int x;
    int y;
    eZones zone;
    bool isAlive;
    bool isPassable;
    int health;
    int damage;
    int money;
    int experience;

} sEntity;

//externs
extern Texture2D textures[MAX_TEXTURES];
extern Sound sounds[MAX_SOUNDS];
extern Music music[MAX_MUSIC];
extern sTile world[WORLD_WIDTH][WORLD_HEIGHT];
extern sTile dungeon[WORLD_WIDTH][WORLD_HEIGHT];
extern Camera2D camera;
extern sEntity player;
extern sEntity dungeon_gate;
extern sEntity orc;
extern sEntity chest;


//functions
void GameStartup();
void GameUpdate();
void GameRender();
void GameShutdown();

void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y);
void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y, float scale);
void BattleUpdate();
void BattleRender();


#endif