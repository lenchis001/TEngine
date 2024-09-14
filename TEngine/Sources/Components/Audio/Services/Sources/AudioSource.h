#ifndef TENGINE_AUDIOSOURCE_H
#define TENGINE_AUDIOSOURCE_H

#include "AL/al.h"

#include "IAudioSource.h"

namespace TEngine::Components::Audio::Services::Sources
{
    class AudioSource : public IAudioSource
    {
    public:
        AudioSource(ALuint sourceId);
        ~AudioSource() override;

        void play() override;

        void pause() override;

        void stop() override;

        float getVolume() override;

        void setVolume(float volume) override;

        bool getIsLooping() override;

        void setIsLooping(bool isLooping) override;

        void setPosition(float x, float y, float z) override;

    private:
        ALuint _sourceId;
    };
}

#endif // TENGINE_AUDIOSOURCE_H