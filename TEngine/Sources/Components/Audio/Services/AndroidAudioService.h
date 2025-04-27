#ifdef __ANDROID__

#ifndef TENGINE_ANDROID_AUDIOSERVICE_H
#define TENGINE_ANDROID_AUDIOSERVICE_H

#include <memory>
#include <map>

#include "IAudioService.h"

#include "Sources/IAudioSource.h"
#include "Readers/IReader.h"

using namespace TEngine::Components::Audio::Services::Sources;
using namespace TEngine::Components::Audio::Services::Readers;

namespace TEngine::Components::Audio::Services
{
    class AndroidAudioService : public IAudioService
    {
    public:
        AndroidAudioService(std::shared_ptr<IReader> reader);

        ~AndroidAudioService() override;

        void initialize() override;

        std::shared_ptr<IAudioSource> take(const std::string &path) override;

        void release(const std::shared_ptr<IAudioSource> source) override;

        void setListenerPosition(float x, float y, float z) override;

        void setListenerRotation(float x, float y, float z) override;

    private:
        std::shared_ptr<IReader> _reader;
    };
}

#endif // TENGINE_ANDROID_AUDIOSERVICE_H

#endif // __ANDROID__