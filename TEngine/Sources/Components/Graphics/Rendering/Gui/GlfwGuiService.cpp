#include "GlfwGuiService.h"

#include "ControlRenderingStrategies/WindowRenderingStrategy.h"
#include "ControlRenderingStrategies/ImageRenderingStrategy.h"
#include "ControlRenderingStrategies/InputRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Gui;

GlfwGuiService::GlfwGuiService(std::shared_ptr<IEventService> eventService, std::shared_ptr<ITexturesService> texturesService)
    : _eventService(eventService), 
    _texturesService(texturesService)
{

}

GlfwGuiService::~GlfwGuiService()
{
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();

    _eventService->unregisterCursorMoveHandler(std::bind(&GlfwGuiService::_onCursorMove, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->unregisterMouseButtonHandler(std::bind(&GlfwGuiService::_onMouseButtonClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    _eventService->unregisterScrollHandler(std::bind(&GlfwGuiService::_onScroll, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->unregisterKeyHandler(std::bind(&GlfwGuiService::_onKey, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    _eventService->unregisterCharHandler(std::bind(&GlfwGuiService::_onChar, this, std::placeholders::_1));
    _eventService->unregisterCursorEnterHandler(std::bind(&GlfwGuiService::_onCursorEnter, this, std::placeholders::_1));
}

void GlfwGuiService::initialize()
{
    _eventService->registerCursorMoveHandler(std::bind(&GlfwGuiService::_onCursorMove, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->registerMouseButtonHandler(std::bind(&GlfwGuiService::_onMouseButtonClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    _eventService->registerScrollHandler(std::bind(&GlfwGuiService::_onScroll, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->registerKeyHandler(std::bind(&GlfwGuiService::_onKey, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    _eventService->registerCharHandler(std::bind(&GlfwGuiService::_onChar, this, std::placeholders::_1));
    _eventService->registerCursorEnterHandler(std::bind(&GlfwGuiService::_onCursorEnter, this, std::placeholders::_1));
}

void GlfwGuiService::render()
{
    // for (auto &control : _controls)
    // {
    //     control->render();
    // }

    // ImGui::Render();
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

std::shared_ptr<IWindowRenderingStrategy> GlfwGuiService::addWindow()
{
    auto window = std::make_shared<WindowRenderingStrategy>();

    _controls.push_back(window);

    return window;
}

std::shared_ptr<IImageRenderingStrategy> GlfwGuiService::addImage(const std::string &path)
{
    auto image = std::make_shared<ImageRenderingStrategy>(_texturesService, path);

    return image;
}

std::shared_ptr<IInputRenderingStrategy> GlfwGuiService::addInput()
{
    auto input = std::make_shared<InputRenderingStrategy>();

    return input;
}

bool GlfwGuiService::_onCursorMove(int xpos, int ypos)
{
    // ImGui_ImplGlfw_CursorPosCallback(glfwGetCurrentContext(), xpos, ypos);

    return false;
}

bool GlfwGuiService::_onMouseButtonClick(MouseButtons button, KeyStates action, int mods)
{
    // ImGui_ImplGlfw_MouseButtonCallback(glfwGetCurrentContext(), static_cast<int>(button), static_cast<int>(action), mods);

    return false;
}

bool GlfwGuiService::_onScroll(float xoffset, float yoffset)
{
    // ImGui_ImplGlfw_ScrollCallback(glfwGetCurrentContext(), xoffset, yoffset);

    return false;
}

bool GlfwGuiService::_onKey(KeyboardKeys key, int scancode, KeyStates action, int mods)
{
    // ImGui_ImplGlfw_KeyCallback(glfwGetCurrentContext(), static_cast<int>(key), scancode, static_cast<int>(action), mods);

    return false;
}

bool GlfwGuiService::_onChar(unsigned int codepoint)
{
    // ImGui_ImplGlfw_CharCallback(glfwGetCurrentContext(), codepoint);

    return false;
}

bool GlfwGuiService::_onCursorEnter(bool entered)
{
    // ImGui_ImplGlfw_CursorEnterCallback(glfwGetCurrentContext(), entered);

    return false;
}
