#include "sound.h"

#include <vector>
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h> // Include libsndfile for audio file loading
#include "VisualEffect.h"
SoundEffect::SoundEffect(string soundFilePath)
{
    this->soundFilePath = soundFilePath;

    // Initialize OpenAL
    initOpenAL();
}
SoundEffect::SoundEffect()
{
    // Initialize OpenAL
    initOpenAL();
}
void SoundEffect::initOpenAL()
{
    device = alcOpenDevice(nullptr); // open default device
    if (!device)
    {
        std::cerr << "Failed to open default audio device" << std::endl;
        exit(EXIT_FAILURE);
    }

    context = alcCreateContext(device, nullptr);
    if (!context)
    {
        std::cerr << "Failed to create OpenAL context" << std::endl;
        exit(EXIT_FAILURE);
    }

    alcMakeContextCurrent(context);

    // Generate buffer and source
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);
}
void SoundEffect::playSound()
{
    ALenum format;
    ALsizei size;
    ALvoid *data;

    // Open and load the audio file using libsndfile
    SF_INFO sfInfo;
    SNDFILE *sndFile = sf_open(soundFilePath.c_str(), SFM_READ, &sfInfo);
    if (!sndFile)
    {
        std::cerr << "Failed to open audio file: " << soundFilePath << std::endl;
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the audio data
    data = malloc(sfInfo.frames * sfInfo.channels * sizeof(short));
    cout << "after malloc";
    // Read the audio data
    sf_read_short(sndFile, (short *)data, sfInfo.frames * sfInfo.channels);
    cout << "after sf_read_short";

    // Determine the format based on the number of channels
    format = (sfInfo.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    size = sfInfo.frames * sfInfo.channels * sizeof(short);

    // Close the audio file
    sf_close(sndFile);
    cout << "after sf_close";

    // Generate buffer and attach data
    alBufferData(buffer, format, data, size, sfInfo.samplerate);

    // Attach buffer to source
    alSourcei(source, AL_BUFFER, buffer);

    // Play sound
    alSourcePlay(source);

    // Free allocated memory
    free(data);
    cout << "after free";
}
void SoundEffect::deleteSound()
{

    // Clean up OpenAL resources
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
SoundEffect::~SoundEffect()
{
    deleteSound();
}