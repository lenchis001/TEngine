#ifndef TENGINE_GLFW_GUISERVICE_H
#define TENGINE_GLFW_GUISERVICE_H

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
using namespace TEngine::Components::Events::Models;

namespace TEngine::Components::Graphics::Rendering::Services::Gui
{
    class GlfwGuiService : public IGuiService
    {
    public:
        GlfwGuiService(std::shared_ptr<IEventService> eventService, std::shared_ptr<ITexturesService> texturesService);
        ~GlfwGuiService();

        void initialize() override;

        void render() override;

        std::shared_ptr<IWindowRenderingStrategy> addWindow() override;

        std::shared_ptr<IImageRenderingStrategy> addImage(const std::string &path) override;

        std::shared_ptr<IInputRenderingStrategy> addInput() override;

    private:
        bool _onCursorMove(int xpos, int ypos);
        bool _onMouseButtonClick(MouseButtons button, KeyStates action, int mods);
        bool _onScroll(float xoffset, float yoffset);
        bool _onKey(KeyboardKeys key, int scancode, KeyStates action, int mods);
        bool _onChar(unsigned int codepoint);
        bool _onCursorEnter(bool entered);

        std::shared_ptr<Events::Services::IEventService> _eventService;
        std::shared_ptr<ITexturesService> _texturesService;

        std::vector<std::shared_ptr<IControlRenderingStrategy>> _controls;
    };
}

#endif // TENGINE_GLFW_GUISERVICE_H