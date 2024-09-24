#ifndef TENGINE_IGUISERVICE_H
#define TENGINE_IGUISERVICE_H

#include <memory>

#include "ControlRenderingStrategies/IControlRenderingStrategy.h"
#include "ControlRenderingStrategies/IWindowRenderingStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Services::Gui
{
    class IGuiService
    {
    public:
        virtual ~IGuiService() = default;

        virtual void initialize() = 0;

        virtual void render() = 0;

        virtual std::shared_ptr<ControlRenderingStrategies::IWindowRenderingStrategy> addWindow() = 0;
    };
}

#endif // TENGINE_IGUISERVICE_H