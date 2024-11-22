#ifndef TENGINE_IMESHRENDERINGSTRATEGY_H
#define TENGINE_IMESHRENDERINGSTRATEGY_H

#include "Components/Graphics/Rendering/Scene/RenderingMixins/IPhysicsRenderingAware.h"

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Meshes
{
    class IMeshRenderingStrategy : public virtual RenderingMixins::IPhysicsRenderingAware
    {
    public:
        const std::string &getPath() const;
    };
}

#endif // TENGINE_IMESHRENDERINGSTRATEGY_H