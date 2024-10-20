#include "Components/Graphics/Models/Vector3d.h"

#include "Components/State/Serialization/Serializers/SerializerBase.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::State::Serialization::Serializers;

namespace TEngine::Components::Graphics::State::Serialization
{
    template<class T> class Vector3dSerializer : public SerializerBase<Vector3d<T>>
    {
    protected:
        boost::json::value _serialize(std::shared_ptr<Vector3d<T>> value, serializeMember serializeMember) override {
            boost::json::object obj;
            obj["x"] = value->getX();
            obj["y"] = value->getY();
            obj["z"] = value->getZ();
            return obj;
        }
    };
}