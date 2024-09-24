#ifndef TENGINE_CONTROL_STRATEGY_BASE_H
#define TENGINE_CONTROL_STRATEGY_BASE_H

#include "IControlRenderingStrategy.h"

#include <memory>
#include <vector>

namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies
{
    class ControlStrategyBase : virtual public IControlRenderingStrategy
    {
    public:
        void render() override;

        void addChild(std::shared_ptr<IControlRenderingStrategy> value) override;

        void removeChild(std::shared_ptr<IControlRenderingStrategy> value) override;

    private:
        std::vector<std::shared_ptr<IControlRenderingStrategy>> _children;
    };
}

#endif // TENGINE_CONTROL_STRATEGY_BASE_H