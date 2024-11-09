#ifndef TENGINE_ISCENESERVICE_H
#define TENGINE_ISCENESERVICE_H

#include <memory>

#include "Components/Graphics/Models/Vector3d.h"

#include "Components/Graphics/Rendering/Models/Cameras/BuildinCameraTypes.h"
#include "Components/Graphics/Rendering/Scene/CameraStrategies/ICameraStrategy.h"
#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"
#include "Components/Graphics/Rendering/Models/Meshes/PrimitiveTypes.h"
#include "Components/Graphics/Rendering/Models/Physics/PhysicsFlags.h"

namespace TEngine::Components::Graphics::Rendering::Scene
{
    class ISceneService
    {
    public:
        virtual ~ISceneService() = default;

        virtual void initialize() = 0;

        virtual void deinitialize() = 0;

        virtual void render(double time) = 0;

        virtual std::shared_ptr<RenderingStrategies::IRenderingStrategy> addPrimitive(
            Components::Graphics::Rendering::Models::Meshes::PrimitiveTypes type,
            std::string texturePath,
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr,
            Rendering::Models::Physics::PhysicsFlags physics = Rendering::Models::Physics::PhysicsFlags::NONE) = 0;

        virtual std::shared_ptr<RenderingStrategies::IRenderingStrategy> addMesh(
            std::string path,
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr,
            Rendering::Models::Physics::PhysicsFlags physics = Rendering::Models::Physics::PhysicsFlags::NONE) = 0;

        virtual std::shared_ptr<RenderingStrategies::IRenderingStrategy> addSolidbox(
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr) = 0;

        virtual std::shared_ptr<RenderingStrategies::IRenderingStrategy> addEmpty(
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr) = 0;

        virtual std::shared_ptr<CameraStrategies::ICameraStrategy> getActiveCamera() = 0;

        virtual std::shared_ptr<CameraStrategies::ICameraStrategy>
        setActiveCamera(Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes cameraType) = 0;

        virtual void setActiveCamera(std::shared_ptr<CameraStrategies::ICameraStrategy> camera) = 0;

        virtual std::shared_ptr<RenderingStrategies::IRenderingStrategy> getRoot() = 0;
    };
}

#endif // TENGINE_ISCENESERVICE_H