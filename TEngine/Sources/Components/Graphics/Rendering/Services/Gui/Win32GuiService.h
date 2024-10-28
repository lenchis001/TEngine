#ifdef _WIN32

#ifndef TENGINE_WIN32_GUISERVICE_H
#define TENGINE_WIN32_GUISERVICE_H

#include "IGuiService.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Services::Gui
{
    class Win32GuiService : public IGuiService
    {
    public:
        void initialize() override;

        void render() override;

        std::shared_ptr<IWindowRenderingStrategy> addWindow() override;

        std::shared_ptr<IImageRenderingStrategy> addImage(const std::string &path) override;

        std::shared_ptr<IInputRenderingStrategy> addInput() override;
    };
}

#endif // TENGINE_WIN32_GUISERVICE_H

#endif // _WIN32