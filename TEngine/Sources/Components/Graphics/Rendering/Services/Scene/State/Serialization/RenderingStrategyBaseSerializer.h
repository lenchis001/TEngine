#ifndef TENGINE_RENDERINGSTRATEGYBASESERIALIZER_H
#define TENGINE_RENDERINGSTRATEGYBASESERIALIZER_H

#include <string>

#include "Components/State/Serialization/Serializers/SerializerBase.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/RenderingStrategyBase.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization
{
    class RenderingStrategyBaseSerializer : public virtual SerializerBase<RenderingStrategyBase>
    {
    public:
        RenderingStrategyBaseSerializer();

    protected:
        boost::json::object _serialize(RenderingStrategyBase &value, serializeMember serializeMember) override;

        void setType(const std::string &type);

        template <class T>
        boost::json::object _serializeVecror3d(const T &value)
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

#endif // TENGINE_RENDERINGSTRATEGYBASESERIALIZER_H