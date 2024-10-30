#ifndef TENGINE_RENDERINGSTRATEGYBASEMIXIN_H
#define TENGINE_RENDERINGSTRATEGYBASEMIXIN_H

#include <string>

#include "Components/State/Serialization/Serializers/SerializerBase.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/RenderingStrategyBase.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Physics;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization
{
    class SerializerMixin
    {
    public:
        SerializerMixin(const std::string& type);

    protected:
        boost::json::object _serializeBase(RenderingStrategyBase &value, serializeMember serializeMember);

        template <class T>
        boost::json::object _serializeVecror3d(const Vector3d<T> &value)
        {
            boost::json::object obj;
            obj["x"] = value.getX();
            obj["y"] = value.getY();
            obj["z"] = value.getZ();
            return obj;
        }

    private:
        std::string _type;
    };
}

#endif // TENGINE_RENDERINGSTRATEGYBASEMIXIN_H