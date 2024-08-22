#ifndef TENGINE_IRENDERINGSERVICE_H
#define TENGINE_IRENDERINGSERVICE_H

#include "memory"

#include "Components/Graphics/Rendering/Models/IRenderingParameters.h"
#include "Components/Graphics/Rendering/Models/Cameras/BuildinCameraTypes.h"
#include "Components/Graphics/Rendering/Models/RenderableObjects/IRenderableObject.h"
#include "Components/Graphics/Rendering/Services/CameraStrategies/ICameraStrategy.h"
#include "Components/Graphics/Models/PrimitiveTypes.h"
#include "Components/Graphics/ImageLoading/Models/Image.h"

namespace TEngine::Components::Graphics::Rendering::Services
{
    class IRenderingService
    {
    public:
        virtual ~IRenderingService() = default;

        virtual void initialize(std::shared_ptr<TEngine::Components::Graphics::Rendering::Models::IRenderingParameters> parameters) = 0;

        virtual double getTime() const = 0;

        virtual void render() = 0;

        virtual std::shared_ptr<Components::Graphics::Rendering::Models::RenderableObjects::IRenderableObject> addToRendering(
            Components::Graphics::MeshLoading::Models::PrimitiveTypes type,
            std::shared_ptr<Components::Graphics::ImageLoading::Models::Image> image,
            std::shared_ptr<Components::Graphics::Rendering::Models::RenderableObjects::IRenderableObject> parent = nullptr) = 0;

        virtual std::shared_ptr<Components::Graphics::Rendering::Services::CameraStrategies::ICameraStrategy>
        setActiveCamera(Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes cameraType) = 0;

        virtual void setActiveCamera(std::shared_ptr<Components::Graphics::Rendering::Services::CameraStrategies::ICameraStrategy> camera) = 0;
    };
}

#endif // TENGINE_IRENDERINGSERVICE_H