#include "Components/State/Serialization/Serializers/SerializerBase.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/PhysicsRenderingDecorator.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization
{
    class PhysicsRenderingDecoratorSerializer : public SerializerBase<PhysicsRenderingDecorator>
    {
    protected:
        boost::json::object _serialize(PhysicsRenderingDecorator &value, serializeMember serializeMember) override;

    private:
        std::string _toString(PhysicsFlags flag);
    };
}