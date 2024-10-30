#ifndef TENGINE_CUBERENDERINGSTRATEGYDESERIALIZER_H
#define TENGINE_CUBERENDERINGSTRATEGYDESERIALIZER_H

#include "Components/Graphics/Rendering/Services/Scene/State/Deserialization/DeserializerMixin.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/IRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Deserialization;
using namespace TEngine::Components::State::Deserialization::Deserializers;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Deserialization::Primitives
{
    class CubeRenderingStrategyDeserializer : public DeserializerMixin, public DeserializerBase<IRenderingStrategy>
    {
    public:
        CubeRenderingStrategyDeserializer(std::shared_ptr<ISceneService> sceneService);

    protected:
        void _deserialize(const boost::json::value &value, deserializeMember deserializeMember, std::shared_ptr<IRenderingStrategy> root) override;
    };
}

#endif // TENGINE_CUBERENDERINGSTRATEGYDESERIALIZER_H