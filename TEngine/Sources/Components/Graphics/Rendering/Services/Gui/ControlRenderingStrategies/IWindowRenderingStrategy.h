#ifndef TENGINE_IWINDOW_RENDERING_STRATEGY_H
#define TENGINE_IWINDOW_RENDERING_STRATEGY_H

#include <string>

#include "IControlRenderingStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies
{
    class IWindowRenderingStrategy : virtual public IControlRenderingStrategy
    {
    public:
        virtual void setTitle(const std::string &title) = 0;

        virtual void setResizable(bool resizable) = 0;

        virtual void setFullscreen(bool fullscreen) = 0;
    };
}

#endif // TENGINE_IWINDOW_RENDERING_STRATEGY_H