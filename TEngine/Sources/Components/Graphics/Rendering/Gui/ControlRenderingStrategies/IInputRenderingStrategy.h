#ifndef TENGINE_IINPUT_RENDERING_STRATEGY_H
#define TENGINE_IINPUT_RENDERING_STRATEGY_H

#include "IControlRenderingStrategy.h"

#include <string>

namespace TEngine::Components::Graphics::Rendering::Gui::ControlRenderingStrategies
{
    class IInputRenderingStrategy : virtual public IControlRenderingStrategy
    {
    public:
        virtual void setText(const std::string &text) = 0;

        virtual const std::string& getText() const = 0;
    };
}

#endif // TENGINE_IINPUT_RENDERING_STRATEGY_H