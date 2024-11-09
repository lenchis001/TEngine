#ifndef TENGINE_CONTROL_STRATEGY_BASE_H
#define TENGINE_CONTROL_STRATEGY_BASE_H

#include "IControlRenderingStrategy.h"

#include <memory>
#include <vector>

#include "Components/Graphics/Models/Vector2d.h"

using namespace TEngine::Components::Graphics::Models;

namespace TEngine::Components::Graphics::Rendering::Gui::ControlRenderingStrategies
{
    class ControlStrategyBase : virtual public IControlRenderingStrategy
    {
    public:
        ControlStrategyBase();

        void render() override;

        void addChild(std::shared_ptr<IControlRenderingStrategy> value) override;

        void removeChild(std::shared_ptr<IControlRenderingStrategy> value) override;

        void setSize(const Vector2di &value) override;

        void setPosition(const Vector2di &value) override;

    protected:
        bool _isSizeSet;
        Vector2di _size;
        bool _isPositionSet;
        Vector2di _position;

    private:
        std::vector<std::shared_ptr<IControlRenderingStrategy>> _children;
    };
}

#endif // TENGINE_CONTROL_STRATEGY_BASE_H