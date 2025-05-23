#ifndef IENGINE_H
#define IENGINE_H

#include <memory>

#ifdef _WIN32
#include <windows.h>
#elif __ANDROID__
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif

#include "Configs/TEngineExport.h"

#include "Components/Graphics/IGraphicsService.h"
#include "Components/Events/Services/IEventService.h"
#include "Components/Audio/Services/IAudioService.h"
#include "Components/State/Serialization/ISerializationService.h"
#include "Components/State/Deserialization/IDeserializationService.h"
#include "Components/Network/Http/INetworkService.h"
#include "Components/Network/WebSocket/IWebSocketFactory.h"
#include "Components/Core/ICoreService.h"

#include "Models/IEngineParameters.h"

namespace TEngine
{
    class IEngine
    {
    public:
        virtual std::shared_ptr<TEngine::Components::Graphics::IGraphicsService> getGraphicsService() = 0;

        virtual std::shared_ptr<TEngine::Components::Events::Services::IEventService> getEventService() = 0;

        virtual std::shared_ptr<TEngine::Components::Audio::Services::IAudioService> getAudioService() = 0;

        virtual std::shared_ptr<TEngine::Components::State::Serialization::ISerializationService> getSerializationService() = 0;

        virtual std::shared_ptr<TEngine::Components::State::Deserialization::IDeserializationService> getDeserializationService() = 0;

        virtual std::shared_ptr<TEngine::Components::Network::Http::INetworkService> getNetworkService() = 0;

        virtual std::shared_ptr<TEngine::Components::Network::WebSocket::IWebSocketFactory> getWebSocketFactory() = 0;

        virtual std::shared_ptr<TEngine::Components::Core::ICoreService> getCoreService() = 0;

        virtual void initialize(std::shared_ptr<TEngine::Models::IEngineParameters> parameters) = 0;

        virtual void deinitialize() = 0;

        virtual ~IEngine() = default;
    };

    TENGINE_API std::shared_ptr<IEngine> createEngine(
#ifdef _WIN32
        HWND parent = nullptr
#elif __APPLE__
        void *parent = nullptr
#elif __ANDROID__
        android_app *parent = nullptr
#elif __linux__
        void *parent = nullptr
#endif
        ,
        bool isPhysicsEnabled = true);
}

#endif // IENGINE_H