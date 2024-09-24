#ifndef TENGINE_WINDOW_RENDERING_STRATEGY_H
#define TENGINE_WINDOW_RENDERING_STRATEGY_H

#include "IWindowRenderingStrategy.h"
#include "ControlStrategyBase.h"

using namespace TEngine::Components::Graphics::Models;

namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies
{
    class WindowRenderingStrategy : public ControlStrategyBase, public IWindowRenderingStrategy
    {
    public:
        WindowRenderingStrategy();

        void setSize(const Vector2di &value) override;

        void setPosition(const Vector2di &value) override;

        void setTitle(const std::string &title) override;

        void setResizable(bool resizable) override;

        void setFullscreen(bool fullscreen) override;

        void render() override;

    private:
        bool _isSizeSet;
        Vector2di _size;
        bool _isPositionSet;
        Vector2di _position;
        std::string _title;
        bool _resizable;
        bool _fullscreen;
    };
}

#endif // TENGINE_WINDOW_RENDERING_STRATEGY_H