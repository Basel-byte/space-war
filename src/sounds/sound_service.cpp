#include "sound_service.h"

#include <vector>
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h> // Include libsndfile for audio file loading
#include "VisualEffect.h"

SoundService::SoundService()
{
    // Initialize OpenAL
    initSoundService();
}
void SoundService::initSoundService()
{
    for (int i = 0; i < numberOfSounds; i++)
    {
        cout << soundFilePaths[i] << endl;
        soundEffects[i] = SoundEffect(soundFilePaths[i]);
        // soundEffects[i].initOpenAL();
    }
}
void SoundService::playSound(string name)
{

    // convert that switch to if else
    if (name == "collision")
    {
        cout << 1 << endl;
        soundEffects[0].initOpenAL();
        soundEffects[0].playSound();
    }
    else if (name == "explosion")
    {
        cout << 2 << endl;
        soundEffects[1].initOpenAL();

        soundEffects[1].playSound();
    }
    else if (name == "shoot")
    {
        cout << 3 << endl;
        soundEffects[2].initOpenAL();

        soundEffects[2].playSound();
    }
}
void SoundService::deleteSounds()
{
    for (int i = 0; i < numberOfSounds; i++)
    {
        soundEffects[i].deleteSound();
    }
}
SoundService::~SoundService()
{
    deleteSounds();
}