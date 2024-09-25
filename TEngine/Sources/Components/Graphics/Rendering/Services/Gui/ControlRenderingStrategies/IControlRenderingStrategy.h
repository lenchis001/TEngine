#ifndef TENGINE_ICONTROL_RENDERING_STRATEGY_H
#define TENGINE_ICONTROL_RENDERING_STRATEGY_H

#include <memory>

#include "Components/Graphics/Models/Vector2d.h"

namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies
{
    class IControlRenderingStrategy
    {
    public:
        virtual ~IControlRenderingStrategy() = default;

        virtual void render() = 0;

        virtual void addChild(std::shared_ptr<IControlRenderingStrategy> value) = 0;

        virtual void removeChild(std::shared_ptr<IControlRenderingStrategy> value) = 0;

        virtual void setSize(const Graphics::Models::Vector2di &value) = 0;

        virtual void setPosition(const Graphics::Models::Vector2di &value) = 0;
    };
}

#endif // TENGINE_ICONTROL_RENDERING_STRATEGY_H