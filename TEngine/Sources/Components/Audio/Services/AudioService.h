#ifndef TENGINE_AUDIOSERVICE_H
#define TENGINE_AUDIOSERVICE_H

#include <memory>
#include <map>

#include "AL/alc.h"
#include "AL/al.h"

#include "IAudioService.h"

#include "Sources/IAudioSource.h"
#include "Readers/IReader.h"

using namespace TEngine::Components::Audio::Services::Sources;
using namespace TEngine::Components::Audio::Services::Readers;

namespace TEngine::Components::Audio::Services
{
    class AudioService : public IAudioService
    {
    public:
        AudioService(std::shared_ptr<IReader> reader);

        ~AudioService() override;

        void initialize() override;

        std::shared_ptr<IAudioSource> take(const std::string &path) override;

        void release(const std::shared_ptr<IAudioSource> source) override;

        void setListenerPosition(float x, float y, float z) override;

        void setListenerRotation(float x, float y, float z) override;

    private:
        ALCdevice *_device;
        ALCcontext *_context;

        std::shared_ptr<IReader> _reader;

        std::map<std::shared_ptr<IAudioSource>, std::pair<std::string, ALuint>> _sources;
    };
}

#endif // TENGINE_AUDIOSERVICE_H