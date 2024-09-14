#include "AudioSource.h"

using namespace TEngine::Components::Audio::Services::Sources;

AudioSource::AudioSource(ALuint sourceId) : _sourceId(sourceId)
{
}

AudioSource::~AudioSource()
{
    alDeleteSources(1, &_sourceId);
}

void AudioSource::play()
{
    alSourcePlay(_sourceId);
}

void AudioSource::pause()
{
    alSourcePause(_sourceId);
}

void AudioSource::stop()
{
    alSourceStop(_sourceId);
}

float AudioSource::getVolume()
{
    ALfloat volume;
    alGetSourcef(_sourceId, AL_GAIN, &volume);
    return volume;
}

void AudioSource::setVolume(float volume)
{
    alSourcef(_sourceId, AL_GAIN, volume);
}

bool AudioSource::getIsLooping()
{
    ALint looping;
    alGetSourcei(_sourceId, AL_LOOPING, &looping);
    return looping == AL_TRUE;
}

void AudioSource::setIsLooping(bool isLooping)
{
    alSourcei(_sourceId, AL_LOOPING, isLooping ? AL_TRUE : AL_FALSE);
}

void AudioSource::setPosition(float x, float y, float z)
{
    alSource3f(_sourceId, AL_POSITION, x, y, z);
}