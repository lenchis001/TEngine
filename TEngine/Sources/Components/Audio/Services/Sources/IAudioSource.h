#ifndef TENGINE_IAUDIOSOURCE_H
#define TENGINE_IAUDIOSOURCE_H

namespace TEngine::Components::Audio::Services::Sources
{
    class IAudioSource
    {
    public:
        virtual ~IAudioSource() = default;

        virtual void play() = 0;

        virtual void pause() = 0;

        virtual void stop() = 0;

        virtual float getVolume() = 0;

        virtual void setVolume(float volume) = 0;

        virtual bool getIsLooping() = 0;

        virtual void setIsLooping(bool isLooping) = 0;

        virtual void setPosition(float x, float y, float z) = 0;
    };
}

#endif // TENGINE_IAUDIOSOURCE_H