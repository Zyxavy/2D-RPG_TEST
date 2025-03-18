#ifndef MUSIC_FUNCTIONS_HPP
#define MUSIC_FUNCTIONS_HPP

#include "raylib.h"
#include "GameFunctions.hpp"
#include "BattleSystem.hpp"

//music
#define MAX_LIGHT_MUSIC 3
#define MAX_DARK_MUSIC 3
#define MAX_ACTION_MUSIC 3

//enums
enum MusicZone
{
    LIGHT,
    DARK,
    ACTION
};

//externs
extern Music musicLight[MAX_LIGHT_MUSIC];
extern Music musicDark[MAX_DARK_MUSIC];
extern Music musicAction[MAX_ACTION_MUSIC];
extern Music* currentMusic;
extern int currentMusicZone;
extern float masterVolume;
extern float musicVolume;
extern float soundFXVolume;

//functions
void LoadMusic();
void UnloadMusic();
void PlayRandomMusic(MusicZone zone);
void UpdateMusic();
void StopCurrentMusic();
void UpdateAudioVolumes();

#endif // MUSIC_FUNCTIONS_HPP
