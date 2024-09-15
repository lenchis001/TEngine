#include "AudioService.h"

#include <exception>
#include <cassert>

#include "AL/al.h"

#include "Sources/AudioSource.h"
#include "AlMacroses.h"

using namespace TEngine::Components::Audio::Services;
using namespace TEngine::Components::Audio::Services::Sources;

AudioService::AudioService(std::shared_ptr<IReader> reader) : _reader(reader)
{
}

AudioService::~AudioService()
{
    // Shut down context
    alcMakeContextCurrent(NULL);
    // Destroy context
    alcDestroyContext(_context);
    // Close sound device
    alcCloseDevice(_device);

    assert(_sources.empty() && "Not all sources were released");
}

void AudioService::initialize()
{
    // Position of the Listener.
    ALfloat ListenerPos[] = {0.0, 0.0, 0.0};

    // Velocity of the Listener.
    ALfloat ListenerVel[] = {0.0, 0.0, 0.0};

    // Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
    // Also note that these should be units of '1'.
    ALfloat ListenerOri[] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};

    // Open default sound device
    _device = alcOpenDevice(NULL);

    // Check for errors
    if (!_device)
    {
        throw std::exception();
    }
    // Creating rendering context
    _context = alcCreateContext(_device, NULL);

    alcMakeContextCurrent(_context);

    // Set listener properties
    alListenerfv(AL_POSITION, ListenerPos);
    alListenerfv(AL_VELOCITY, ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
}

std::shared_ptr<IAudioSource> AudioService::take(const std::string &path)
{
    ALuint sourceId;

    // Create source
    alGenSources(1, &sourceId);
    if (CHECK_ERROR())
        return nullptr;

    alSourcef(sourceId, AL_PITCH, 1.0f);
    alSourcef(sourceId, AL_GAIN, 1.0f);

    auto readingResult = _reader->take(path, sourceId);

    if (!readingResult)
    {
        alDeleteSources(1, &sourceId);
        return nullptr;
    }

    auto result = std::make_shared<AudioSource>(sourceId);

    _sources.insert(
        std::pair<std::shared_ptr<IAudioSource>, std::pair<std::string, ALuint>>(
            result,
            std::pair<std::string, ALuint>(path, sourceId)));

    return result;
}

void AudioService::release(const std::shared_ptr<IAudioSource> source)
{
    auto targetIterator = _sources.find(source);

    if (targetIterator == _sources.end())
    {
        throw std::exception();
    }

    alDeleteSources(1, &targetIterator->second.second);
    _reader->release(targetIterator->second.first);

    _sources.erase(targetIterator);
}

void AudioService::setListenerPosition(float x, float y, float z)
{
    ALfloat ListenerPos[] = {x, y, z};

    alListenerfv(AL_POSITION, ListenerPos);
}

void AudioService::setListenerRotation(float x, float y, float z)
{
    ALfloat ListenerOri[] = {x, y, z, 0.0, 1.0, 0.0};

    alListenerfv(AL_ORIENTATION, ListenerOri);
}