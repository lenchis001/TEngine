#ifndef TENGINE_GUISERVICE_H
#define TENGINE_GUISERVICE_H

#include "IGuiService.h"

#include <memory>
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Components/Events/Services/IEventService.h"
#include "Components/Graphics/Rendering/Services/Textures/ITexturesService.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;
using namespace TEngine::Components::Events::Services;

namespace TEngine::Components::Graphics::Rendering::Services::Gui
{
    class GuiService : public IGuiService
    {
    public:
        GuiService(std::shared_ptr<IEventService> eventService, std::shared_ptr<ITexturesService> texturesService);
        ~GuiService();

        void initialize() override;

        void render() override;

        std::shared_ptr<IWindowRenderingStrategy> addWindow() override;

        std::shared_ptr<IImageRenderingStrategy> addImage(const std::string &path) override;

    private:
        bool _onCursorMove(float xpos, float ypos);
        bool _onMouseButtonClick(int button, int action, int mods);
        bool _onScroll(float xoffset, float yoffset);
        bool _onKey(int key, int scancode, int action, int mods);

        std::shared_ptr<Events::Services::IEventService> _eventService;
        std::shared_ptr<ITexturesService> _texturesService;

        std::vector<std::shared_ptr<IControlRenderingStrategy>> _controls;
    };
}

#endif // TENGINE_GUISERVICE_H