#ifndef TENGINE_ISCENESERVICE_H
#define TENGINE_ISCENESERVICE_H

#include "memory"

#include "Components/Graphics/Rendering/Models/Cameras/BuildinCameraTypes.h"
#include "Components/Graphics/Rendering/Services/Scene/CameraStrategies/ICameraStrategy.h"
#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/IRenderingStrategy.h"
#include "Components/Graphics/Models/PrimitiveTypes.h"

namespace TEngine::Components::Graphics::Rendering::Services::Scene
{
    class ISceneService
    {
    public:
        virtual ~ISceneService() = default;

        virtual double getTime() const = 0;

        virtual void render() = 0;

        virtual std::shared_ptr<RenderingStrategies::IRenderingStrategy> addToRendering(
            Components::Graphics::MeshLoading::Models::PrimitiveTypes type,
            std::string texturePath,
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr) = 0;

        virtual std::shared_ptr<RenderingStrategies::IRenderingStrategy> addMeshToRendering(
            std::string meshPath,
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr) = 0;

        virtual std::shared_ptr<CameraStrategies::ICameraStrategy> getActiveCamera() = 0;

        virtual std::shared_ptr<CameraStrategies::ICameraStrategy>
        setActiveCamera(Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes cameraType) = 0;

        virtual void setActiveCamera(std::shared_ptr<CameraStrategies::ICameraStrategy> camera) = 0;
    };
}

#endif // TENGINE_ISCENESERVICE_H