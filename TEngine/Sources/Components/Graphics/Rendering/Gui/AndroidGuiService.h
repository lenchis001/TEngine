#ifdef __ANDROID__

#ifndef TENGINE_WIN32_GUISERVICE_H
#define TENGINE_WIN32_GUISERVICE_H

#include "IGuiService.h"

using namespace TEngine::Components::Graphics::Rendering::Gui::ControlRenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Gui
{
    class AndroidGuiService : public IGuiService
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

#endif // __ANDROID__