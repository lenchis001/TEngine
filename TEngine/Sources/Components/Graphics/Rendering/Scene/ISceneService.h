#ifndef TENGINE_ISCENESERVICE_H
#define TENGINE_ISCENESERVICE_H

#include <memory>

#include "Components/Graphics/Models/Vector3d.h"

#include "Components/Graphics/Rendering/Models/Cameras/BuildinCameraTypes.h"
#include "Components/Graphics/Rendering/Scene/Models/Physics/PhysicsFlags.h"
#include "CameraStrategies/ICameraStrategy.h"
#include "RenderingStrategies/IRenderingStrategy.h"
#include "RenderingStrategies/Meshes/IMeshRenderingStrategy.h"
#include "RenderingStrategies/Primitives/ICubeRenderingStrategy.h"
#include "RenderingStrategies/Solid/ISolidboxRenderingStrategy.h"
#include "Models/ISceneParameters.h"
#include "Components/Graphics/Rendering/Scene/Lights/ILightService.h"

namespace TEngine::Components::Graphics::Rendering::Scene
{
    class ISceneService
    {
    public:
        virtual ~ISceneService() = default;

        virtual void initialize(std::shared_ptr<Models::ISceneParameters> parameters) = 0;

        virtual void deinitialize() = 0;

        virtual void render(double time) = 0;

        virtual std::shared_ptr<RenderingStrategies::Primitives::ICubeRenderingStrategy> addCube(
            std::string texturePath = "",
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr,
            Models::Physics::PhysicsFlags physics = Models::Physics::PhysicsFlags::NONE) = 0;

        virtual std::shared_ptr<RenderingStrategies::Meshes::IMeshRenderingStrategy> addMesh(
            std::string path,
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr,
            Models::Physics::PhysicsFlags physics = Models::Physics::PhysicsFlags::NONE) = 0;

        virtual std::shared_ptr<RenderingStrategies::Solid::ISolidboxRenderingStrategy> addSolidbox(
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr) = 0;

        virtual std::shared_ptr<RenderingStrategies::IRenderingStrategy> addEmpty(
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr) = 0;

        virtual std::shared_ptr<RenderingStrategies::IRenderingStrategy> addSkySphere(
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> parent = nullptr) = 0;

        virtual std::shared_ptr<CameraStrategies::ICameraStrategy> getActiveCamera() = 0;

        virtual std::shared_ptr<CameraStrategies::ICameraStrategy>
        setActiveCamera(Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes cameraType) = 0;

        virtual void setActiveCamera(std::shared_ptr<CameraStrategies::ICameraStrategy> camera) = 0;

        virtual std::shared_ptr<RenderingStrategies::IRenderingStrategy> getRoot() = 0;

        virtual std::shared_ptr<Lights::ILightService> getLightService() = 0;
    };
}

#endif // TENGINE_ISCENESERVICE_H