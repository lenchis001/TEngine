#ifndef IENGINE_H
#define IENGINE_H

#include "memory"

#include "Configs/TEngineExport.h"

#include "Components/Graphics/IGraphicsService.h"
#include "Components/Events/Services/IEventService.h"
#include "Components/Audio/Services/IAudioService.h"

#include "Models/IEngineParameters.h"

namespace TEngine
{
    class IEngine
    {
    public:
        virtual std::shared_ptr<TEngine::Components::Graphics::Services::IGraphicsService> getGraphicsService() = 0;

        virtual std::shared_ptr<TEngine::Components::Events::Services::IEventService> getEventService() = 0;

        virtual std::shared_ptr<TEngine::Components::Audio::Services::IAudioService> getAudioService() = 0;

        virtual void initialize(std::shared_ptr<TEngine::Models::IEngineParameters> parameters) = 0;

        virtual void deinitialize() = 0;

        virtual ~IEngine() = default;
    };

    TENGINE_API std::shared_ptr<IEngine> createEngine();
}

#endif // IENGINE_H