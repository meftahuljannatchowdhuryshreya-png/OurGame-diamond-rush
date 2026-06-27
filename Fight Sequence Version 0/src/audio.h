#pragma once
#include "raylib.h"

Music bgMusic;

void InitAudio()
{
    InitAudioDevice();

    bgMusic = LoadMusicStream("epicTitanFight.mp3"); // Change path if needed
    SetMusicVolume(bgMusic, 0.5f);

    PlayMusicStream(bgMusic);
}

void UpdateAudio()
{
    UpdateMusicStream(bgMusic);
}

void CloseAudio()
{
    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
}