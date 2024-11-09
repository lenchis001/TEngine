#ifndef TENGINE_WINDOW_RENDERING_STRATEGY_H
#define TENGINE_WINDOW_RENDERING_STRATEGY_H

#include "IWindowRenderingStrategy.h"
#include "ControlStrategyBase.h"

using namespace TEngine::Components::Graphics::Models;

namespace TEngine::Components::Graphics::Rendering::Gui::ControlRenderingStrategies
{
    class WindowRenderingStrategy : public ControlStrategyBase, public IWindowRenderingStrategy
    {
    public:
        WindowRenderingStrategy();

        void setTitle(const std::string &title) override;

        void setResizable(bool resizable) override;

        void setFullscreen(bool fullscreen) override;

        void render() override;

    private:
        std::string _title;
        bool _resizable;
        bool _fullscreen;
    };
}

#endif // TENGINE_WINDOW_RENDERING_STRATEGY_H