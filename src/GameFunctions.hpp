#ifndef GAME_FUNCTIONS_HPP
#define GAME_FUNCTIONS_HPP

#include <raylib.h>
#include <raymath.h>
#include <string>


//constants
const int screenWidth = 800;
const int screenHeight = 600;


//definitions
#define MAX_TEXTURES 3
#define MAX_PAGE_PICTURES 11
#define TILE_WIDTH 8
#define TILE_HEIGHT  8
#define MAX_SOUNDS 17
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
    TEXTURE_TILEMAP = 0,
    TEXTURE_STAR = 1,
    TEXTURE_BOOK = 2
} texture_asset;

typedef enum
{
    PAGE1 = 0, PAGE2, PAGE3, PAGE4, PAGE5, PAGE6, PAGE7, PAGE8, PAGE9, PAGE10, PAGE11
} page_pictures;

typedef enum 
{
    SOUND_FOOT_GRASS = 0,
    SOUND_FOOT_STONE,
    SOUNDS_ATTACK,
    SOUND_DEATH,
    SOUND_COINS,
    SOUND_HOVER_ITEMS,
    SOUNDS_LEVEL_UP,
    SOUNDS_TREE_CUTTING,
    SOUNDS_KNIGHT_SKILL1,
    SOUNDS_KNIGHT_SKILL2,
    SOUNDS_KNIGHT_SKILL3,
    SOUNDS_WIZARD_SKILL1,
    SOUNDS_WIZARD_SKILL2,
    SOUNDS_WIZARD_SKILL3,
    SOUNDS_ROGUE_SKILL1,
    SOUNDS_ROGUE_SKILL2,
    SOUNDS_ROGUE_SKILL3
} sound_asset;

typedef enum
{
    TILE_TYPE_DIRT = 0,
    TILE_TYPE_GRASS,
    TILE_TYPE_TREE,
    TILE_TYPE_STONE,
    TILE_TYPE_STUMP,

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
   ZONE_DUNGEON, 
   ZONE_TUTORIAL // WIP

} eZones;


//externs
extern Texture2D textures[MAX_TEXTURES];
extern Texture2D pagePictures[MAX_PAGE_PICTURES];
extern Sound sounds[MAX_SOUNDS];
extern sTile world[WORLD_WIDTH][WORLD_HEIGHT];
extern sTile dungeon[WORLD_WIDTH][WORLD_HEIGHT];
extern sTile tutorialWorld[WORLD_WIDTH][WORLD_HEIGHT]; // WIP
extern Camera2D camera;
extern bool isInventory;
extern int lastKeyPressed;

//functions
void GameStartup();
void GameUpdate();
void GameRender();
void GameShutdown();
void LoadAllPages();

void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y);
void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y, float scale);
bool IsBarrierCollision(int x, int y);

void CheckContactWithEnemies();
void DrawHotBar();
void CutDownTree();
void ExecuteEnemyBehaviors();



#endif // GAME_FUNCTIONS_HPP