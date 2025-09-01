#include <raylib.h>
#include <iostream>
#include "MusicFunctions.hpp"
#include "GameFunctions.hpp"
#include "BattleSystem.hpp"


//music
Music musicLight[MAX_LIGHT_MUSIC];
Music musicDark[MAX_DARK_MUSIC];
Music musicAction[MAX_ACTION_MUSIC];

Music* currentMusic = nullptr;
int currentMusicZone = -1;

float masterVolume = 1.0f;
float musicVolume = 1.0f;
float soundFXVolume = 1.0f;

void LoadMusic()
{
    musicLight[0] = LoadMusicStream("assets/Light Ambience 3.wav");
    musicLight[1] = LoadMusicStream("assets/Light Ambience 1.wav");
    musicLight[2] = LoadMusicStream("assets/Light Ambience 5.wav");
    musicLight[3] = LoadMusicStream("assets/Ambient 1.wav"); 

    musicDark[0] = LoadMusicStream("assets/Dark Ambient 2.wav");
    musicDark[1] = LoadMusicStream("assets/Dark Ambient 4.wav");
    musicDark[2] = LoadMusicStream("assets/Dark Ambient 5.wav");
    musicDark[3] = LoadMusicStream("assets/Dark Ambient 3.wav");

    musicAction[0] = LoadMusicStream("assets/Action 1.wav");
    musicAction[1] = LoadMusicStream("assets/Action 2.wav");
    musicAction[2] = LoadMusicStream("assets/Action 3.wav");
    musicAction[2] = LoadMusicStream("assets/Action 5.wav");
}

void UnloadMusic()
{
    for(int i = 0; i < MAX_LIGHT_MUSIC; i++)
    {
        UnloadMusicStream(musicLight[i]);
        UnloadMusicStream(musicDark[i]);
        UnloadMusicStream(musicAction[i]);
        
    }
   
}

void StopCurrentMusic()
{
    if(currentMusic != nullptr)
    {
        StopMusicStream(*currentMusic);
        currentMusic = nullptr;
    }
}

void PlayRandomMusic(MusicZone zone)
{
    StopCurrentMusic();

    int random = GetRandomValue(0,2);

    switch (zone)
    {
    case LIGHT:
        currentMusic = &musicLight[random];
        break;
    case DARK:
        currentMusic = &musicDark[random];
        break;
    case ACTION:
        currentMusic = &musicAction[random];
        break;
    default:
        break;
    }

    if(currentMusic != nullptr)
    {
        PlayMusicStream(*currentMusic);
        std::cout << "Playing: zone" << zone << " music: " << random << "\n";

    }

    currentMusicZone = zone;
}

void UpdateMusic()
{
    if(currentMusic != nullptr)
    {
        UpdateMusicStream(*currentMusic);

        if(!IsMusicStreamPlaying(*currentMusic))
        {
            PlayRandomMusic((MusicZone) currentMusicZone);
        }
    }
}

void UpdateAudioVolumes()
{
    SetMasterVolume(masterVolume);
}

void PlaySoundWhenHoveringItem(bool &hoveringOverItems, double currentTime, double &lastHoverSoundTime, double cooldownDuration)
{
    if (!hoveringOverItems || (currentTime - lastHoverSoundTime >= cooldownDuration)) {
        PlaySound(sounds[SOUND_HOVER_ITEMS]);
        lastHoverSoundTime = currentTime;
        hoveringOverItems = true;
    }
}

