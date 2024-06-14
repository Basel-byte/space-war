#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h> // Include libsndfile for audio file loading
#include "VisualEffect.h"
using namespace std;

class SoundEffect
{
private:
    // Sound file path
    string soundFilePath = "village.mp3";

    // OpenAL variables
    ALCdevice *device;
    ALCcontext *context;
    ALuint source;
    ALuint buffer;

public:
    // Function to initialize OpenAL for sound
    void initOpenAL();
    void playSound();
    void deleteSound();
    SoundEffect(string soundFilePath);
    SoundEffect();
    ~SoundEffect();
};

#endif // SHOOTEFFECT_H