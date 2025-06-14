#ifndef TENGINE_AUDIO_DUMMYAUDIO_SOURCE_H
#define TENGINE_AUDIO_DUMMYAUDIO_SOURCE_H

#include "IAudioSource.h"

namespace TEngine::Components::Audio::Services::Sources
{
    class DummyAudioSource : public IAudioSource
    {
    public:
        DummyAudioSource() = default;
        ~DummyAudioSource() override = default;

        void play() override {}
        void stop() override {}
        void pause() override {}
        float getVolume() override { return 0.0f; }
        void setVolume(float volume) override {}
        bool getIsLooping() override { return false; }
        void setIsLooping(bool isLooping) override {}
        void setPosition(float x, float y, float z) override {}
    };
} // namespace TEngine::Components::Audio::Services::Sources

#endif // TENGINE_AUDIO_DUMMYAUDIO_SOURCE_H