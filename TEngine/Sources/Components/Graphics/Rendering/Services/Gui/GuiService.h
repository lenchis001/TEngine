#ifndef TENGINE_GUISERVICE_H
#define TENGINE_GUISERVICE_H

#include "IGuiService.h"

#include <memory>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Components/Events/Services/IEventService.h"

namespace TEngine::Components::Graphics::Rendering::Services::Gui
{
    class GuiService : public IGuiService
    {
    public:
        GuiService(std::shared_ptr<Events::Services::IEventService> eventService);
        ~GuiService();

        void initialize() override;

        void render() override;

    private:
        bool _onCursorMove(float xpos, float ypos);
        bool _onMouseButtonClick(int button, int action, int mods);
        bool _onScroll(float xoffset, float yoffset);
        bool _onKey(int key, int scancode, int action, int mods);

        std::shared_ptr<Events::Services::IEventService> _eventService;
    };
}

#endif // TENGINE_GUISERVICE_H