#ifndef SOUND_SERVICE_H
#define SOUND_SERVICE_H

#include <vector>
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h> // Include libsndfile for audio file loading
#include "VisualEffect.h"
#include "sound.h"
#define numberOfSounds 3
using namespace std;

class SoundService
{
private:
    // Sound file path
    std::vector<std::string> soundFilePaths = {"./src/sound-effects/collision1.mp3", "./src/sound-effects/explosion.mp3", "./src/sound-effects/shoot.mp3"};
    SoundEffect soundEffects[numberOfSounds];

public:
    // Function to initialize OpenAL for sound
    SoundService();
    void initSoundService();
    void playSound(string name);
    void deleteSounds();
    ~SoundService();
};

#endif // SHOOTEFFECT_H