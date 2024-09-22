#ifndef TENGINE_GUISERVICE_H
#define TENGINE_GUISERVICE_H

#include "IGuiService.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace TEngine::Components::Graphics::Rendering::Services::Gui
{
    class GuiService : public IGuiService
    {
    public:
        void initialize() override;

        void render() override;
    };
}

#endif // TENGINE_GUISERVICE_H