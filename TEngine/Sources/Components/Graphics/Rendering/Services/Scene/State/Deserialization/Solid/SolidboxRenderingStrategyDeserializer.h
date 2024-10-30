#ifndef TENGINE_SOLIDBOXRENDERINGSTRATEGYDESERIALIZER_H
#define TENGINE_SOLIDBOXRENDERINGSTRATEGYDESERIALIZER_H

#include "Components/Graphics/Rendering/Services/Scene/State/Deserialization/DeserializerMixin.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/IRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Deserialization;
using namespace TEngine::Components::State::Deserialization::Deserializers;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Deserialization::Solid
{
    class SolidboxRenderingStrategyDeserializer : public DeserializerMixin, public DeserializerBase<IRenderingStrategy>
    {
    public:
        SolidboxRenderingStrategyDeserializer(std::shared_ptr<ISceneService> sceneService);

    protected:
        void _deserialize(const boost::json::value &value, deserializeMember deserializeMember, std::shared_ptr<IRenderingStrategy> root) override;
    };
}

#endif // TENGINE_SOLIDBOXRENDERINGSTRATEGYDESERIALIZER_H