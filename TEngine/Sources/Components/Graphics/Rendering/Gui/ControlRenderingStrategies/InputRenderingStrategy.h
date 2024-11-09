#ifndef TENGINE_INPUT_RENDERING_STRATEGY_H
#define TENGINE_INPUT_RENDERING_STRATEGY_H

#include "IInputRenderingStrategy.h"
#include "ControlStrategyBase.h"

namespace TEngine::Components::Graphics::Rendering::Gui::ControlRenderingStrategies
{
    class InputRenderingStrategy : public ControlStrategyBase, public IInputRenderingStrategy
    {
    public:
        InputRenderingStrategy();

        void setText(const std::string &text) override;

        const std::string& getText() const override;

        void render() override;

    private:
        char _text[256];
    };
}

#endif // TENGINE_INPUT_RENDERING_STRATEGY_H