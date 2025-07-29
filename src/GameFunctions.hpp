#ifndef GAME_FUNCTIONS_HPP
#define GAME_FUNCTIONS_HPP

#include <raylib.h>
#include <raymath.h>
#include <string>


//constants
const int screenWidth = 800;
const int screenHeight = 600;


//definitions
#define MAX_TEXTURES 10
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
    TEXTURE_BOOK = 2,
    TEXTURE_SAND = 3,
    TEXTURE_BOAT_LEFT = 4,
    TEXTURE_BOAT_RIGHT = 5,
    TEXTURE_KNIGHT = 6,
    TEXTURE_WIZARD = 7,
    TEXTURE_ROGUE = 8,
    TEXTURE_FLOATING_CRAB = 9,
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
    TILE_TYPE_GRASS, // 1
    TILE_TYPE_TREE, // 2
    TILE_TYPE_STONE, // 3
    TILE_TYPE_STUMP, // 4
    //water
    TILE_TYPE_WATER_TOP_LEFT, // 5
    TILE_TYPE_WATER_TOP_MID,
    TILE_TYPE_WATER_TOP_RIGHT,
    TILE_TYPE_WATER_MID_LEFT,
    TILE_TYPE_WATER_MID_MID,
    TILE_TYPE_WATER_MID_RIGHT,
    TILE_TYPE_WATER_BOT_LEFT,
    TILE_TYPE_WATER_BOT_MID,
    TILE_TYPE_WATER_BOT_RIGHT,
    TILE_TYPE_WATER_HORIZONTAL,
    TILE_TYPE_WATER_VERTICAL,
    TILE_TYPE_WATER_WELL, 
    //dungeon misc
    TILE_TYPE_RAIL_STRAIGHT, // 17
    TILE_TYPE_RAIL_CURVE,
    TILE_TYPE_RAIL_BROKEN,
    TILE_TYPE_PILLAR,
    TILE_TYPE_BROKEN_PILLAR,
    TILE_TYPE_GRAVE,
    TILE_TYPE_CROSS,
    TILE_TYPE_TOP_LEFT_WALL_CORNER,
    TILE_TYPE_TOP1_WALL,
    TILE_TYPE_TOP2_WALL,
    TILE_TYPE_TOP_RIGHT_WALL_CORNER,
    TILE_TYPE_MID_LEFT_WALL_CORNER,
    TILE_TYPE_MID_WALL1,
    TILE_TYPE_MID_WALL2,
    TILE_TYPE_MID_RIGHT_WALL_CORNER,
    TILE_TYPE_BOT_LEFT_OUTER_WALL_CORNER,
    TILE_TYPE_BOT_OUTER_WALL1,
    TILE_TYPE_BOT_OUTER_WALL2,
    TILE_TYPE_BOT_RIGHT_OUTER_WALL_CORNER,
    //
    TILE_TYPE_HOUSE,
    TILE_TYPE_STAIRS_DOWN,
    // basement
    TILE_TYPE_CAULDRON,
    TILE_TYPE_BED,
    TILE_TYPE_DOOR_LOCKED,
    TILE_TYPE_DOOR_UNLOCEKD,
    TILE_TYPE_SQUARE_RAIL,
    //island
    TILE_TYPE_SAND = 99,
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
   ZONE_WORLD_PLAIN_LANDS ,
   ZONE_BASEMENT_DUNGEON,
   ZONE_ISLAND,

} eZones;

typedef enum
{
    HERO_SELECTION,
    IN_ZONE_1,
    IN_DUNGEON,
    IN_PLAINS,
    IN_DUNGEON_BASEMENT,
    IN_ISLAND,

    PICKING_UP_ITEM,
} GameState;


//externs

extern Texture2D textures[MAX_TEXTURES];
extern Texture2D pagePictures[MAX_PAGE_PICTURES];
extern Sound sounds[MAX_SOUNDS];
extern sTile world[WORLD_WIDTH][WORLD_HEIGHT];
extern sTile dungeon[WORLD_WIDTH][WORLD_HEIGHT];
extern sTile plainLands[WORLD_WIDTH][WORLD_HEIGHT];
extern sTile basementDungeon[WORLD_WIDTH][WORLD_HEIGHT];
extern sTile island[WORLD_WIDTH][WORLD_HEIGHT];
extern Camera2D camera;
extern bool isInventory;
extern int lastKeyPressed;
extern int count;
extern GameState currentGameState, prevGameState;
extern bool isRidingBoat; 
extern bool isBoatFacingRight; 


//functions
void GameStartup();
void GameUpdate();
void GameRender();
void RenderTile(const sTile &tile,int &texture_index_x, int &texture_index_y);
void GameShutdown();
void LoadAllPages();
void DeleteEnemies();

void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y);
void DrawTile(int pos_x, int pos_y, int texture_index_x, int texture_index_y, float scale);
bool IsBarrierCollision(int x, int y);

void DrawHotBar();
void CutDownTree();
void EnterGates();
void InteractWithNPCs();
void CheckIfDungeonCompleted();



#endif // GAME_FUNCTIONS_HPP