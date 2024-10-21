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
        boost::json::object _serialize(RenderingStrategyBase& value, serializeMember serializeMember) override;

        void setType(const std::string &type);
    private:
        std::string _type;
    };
}

#endif // TENGINE_RENDERINGSTRATEGYBASESERIALIZER_H