#ifndef TENGINE_RENDERINGSTRATEGYBASEDESERIALIZER_H
#define TENGINE_RENDERINGSTRATEGYBASEDESERIALIZER_H

#include "Components/State/Deserialization/Deserializers/DeserializerBase.h"
#include "Components/Graphics/Rendering/Scene/ISceneService.h"
#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"

using namespace TEngine::Components::State::Deserialization::Deserializers;
using namespace TEngine::Components::Graphics::Rendering::Scene;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::Models::Physics;

namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization
{
    class DeserializerMixin
    {
    public:
        DeserializerMixin(std::shared_ptr<ISceneService> sceneService);

    protected:
        void _deserializeBase(const boost::json::value &value, deserializeMember deserializeMember, std::shared_ptr<IRenderingStrategy> root);

        static Vector3df _deserializePosition(const boost::json::object &value);
        static Vector3df _deserializeRotation(const boost::json::object &value);
        static Vector3df _deserializeScale(const boost::json::object &value);

        template <class T>
        static Vector3d<T> _deserializeVecror3d(const boost::json::object &value)
        {
            auto x = value.at("x").as_double();
            auto y = value.at("y").as_double();
            auto z = value.at("z").as_double();

            return Vector3d<T>(x, y, z);
        }

        static PhysicsFlags _toPhysicsFlag(const std::string &value);

        std::shared_ptr<ISceneService> _sceneService;
    };
}

#endif // TENGINE_RENDERINGSTRATEGYBASEDESERIALIZER_H