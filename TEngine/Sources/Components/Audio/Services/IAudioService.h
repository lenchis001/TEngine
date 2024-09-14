#ifndef TENGINE_IAUDIOSERVICE_H
#define TENGINE_IAUDIOSERVICE_H

#include "string"
#include "memory"

#include "Sources/IAudioSource.h"

namespace TEngine::Components::Audio::Services
{
    class IAudioService
    {
    public:
        virtual ~IAudioService() = default;

        virtual void initialize() = 0;

        virtual std::shared_ptr<Sources::IAudioSource> take(const std::string &path) = 0;

        virtual void release(const std::shared_ptr<Sources::IAudioSource> source) = 0;

        virtual void setListenerPosition(float x, float y, float z) = 0;

        virtual void setListenerRotation(float x, float y, float z) = 0;
    };
}

#endif //TENGINE_IAUDIOSERVICE_H