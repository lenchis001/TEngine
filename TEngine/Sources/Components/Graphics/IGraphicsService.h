#ifndef TENGINE_IGRAPHICSSERVICE_H
#define TENGINE_IGRAPHICSSERVICE_H

#include "future"
#include "memory"
#include "string"

#include "Models/DataActionResult.h"

#include "Models/IGraphicsParameters.h"
#include "MeshLoading/Models/ErrorCodes.h"
#include "Models/PrimitiveTypes.h"
#include "Rendering/Models/Cameras/BuildinCameraTypes.h"
#include "Rendering/Services/CameraStrategies/ICameraStrategy.h"
#include "Rendering/Services/RenderingStrategies/IRenderingStrategy.h"

namespace TEngine::Components::Graphics::Services
{
    class IGraphicsService
    {
    public:
        virtual void initialize(std::shared_ptr<TEngine::Components::Graphics::Models::IGraphicsParameters> parameters) = 0;

        virtual bool isShutdownRequested() const = 0;

        virtual double getTime() const = 0;

        virtual void render() = 0;

        virtual std::future<
            TEngine::Models::DataActionResult<
                TEngine::Components::Graphics::MeshLoading::Models::ErrorCodes,
                TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::IRenderingStrategy>>
        loadMesh(const std::wstring &path) = 0;

        virtual std::shared_ptr<
            TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::IRenderingStrategy>
        addPrimitive(
            TEngine::Components::Graphics::MeshLoading::Models::PrimitiveTypes type,
            std::string texturePath,
            std::shared_ptr<TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::IRenderingStrategy> parent = nullptr) = 0;

        virtual std::shared_ptr<Components::Graphics::Rendering::Services::CameraStrategies::ICameraStrategy>
            setActiveCamera(Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes cameraType) = 0;

        virtual void setActiveCamera(std::shared_ptr<Components::Graphics::Rendering::Services::CameraStrategies::ICameraStrategy> camera) = 0;

        virtual ~IGraphicsService() = default;
    };
}

#endif // TENGINE_IGRAPHICSSERVICE_H