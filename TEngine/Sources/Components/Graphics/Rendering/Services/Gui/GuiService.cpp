#include "GuiService.h"

#include "ControlRenderingStrategies/WindowRenderingStrategy.h"
#include "ControlRenderingStrategies/ImageRenderingStrategy.h"
#include "ControlRenderingStrategies/InputRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Gui;

GuiService::GuiService(std::shared_ptr<IEventService> eventService, std::shared_ptr<ITexturesService> texturesService)
    : _eventService(eventService), _texturesService(texturesService)
{
}

GuiService::~GuiService()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    _eventService->unregisterCursorMoveHandler(std::bind(&GuiService::_onCursorMove, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->unregisterMouseButtonHandler(std::bind(&GuiService::_onMouseButtonClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    _eventService->unregisterScrollHandler(std::bind(&GuiService::_onScroll, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->unregisterKeyHandler(std::bind(&GuiService::_onKey, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    _eventService->unregisterCharHandler(std::bind(&GuiService::_onChar, this, std::placeholders::_1));
    _eventService->unregisterCursorEnterHandler(std::bind(&GuiService::_onCursorEnter, this, std::placeholders::_1));
}

void GuiService::initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), false);
    ImGui_ImplOpenGL3_Init("#version 330");

    _eventService->registerCursorMoveHandler(std::bind(&GuiService::_onCursorMove, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->registerMouseButtonHandler(std::bind(&GuiService::_onMouseButtonClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    _eventService->registerScrollHandler(std::bind(&GuiService::_onScroll, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->registerKeyHandler(std::bind(&GuiService::_onKey, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    _eventService->registerCharHandler(std::bind(&GuiService::_onChar, this, std::placeholders::_1));
    _eventService->registerCursorEnterHandler(std::bind(&GuiService::_onCursorEnter, this, std::placeholders::_1));
}

void GuiService::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto &control : _controls)
    {
        control->render();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

std::shared_ptr<IWindowRenderingStrategy> GuiService::addWindow()
{
    auto window = std::make_shared<WindowRenderingStrategy>();

    _controls.push_back(window);

    return window;
}

std::shared_ptr<IImageRenderingStrategy> GuiService::addImage(const std::string &path)
{
    auto image = std::make_shared<ImageRenderingStrategy>(_texturesService, path);

    return image;
}

std::shared_ptr<IInputRenderingStrategy> GuiService::addInput()
{
    auto input = std::make_shared<InputRenderingStrategy>();

    return input;
}

bool GuiService::_onCursorMove(float xpos, float ypos)
{
    ImGui_ImplGlfw_CursorPosCallback(glfwGetCurrentContext(), xpos, ypos);

    return false;
}

bool GuiService::_onMouseButtonClick(int button, int action, int mods)
{
    ImGui_ImplGlfw_MouseButtonCallback(glfwGetCurrentContext(), button, action, mods);

    return false;
}

bool GuiService::_onScroll(float xoffset, float yoffset)
{
    ImGui_ImplGlfw_ScrollCallback(glfwGetCurrentContext(), xoffset, yoffset);

    return false;
}

bool GuiService::_onKey(int key, int scancode, int action, int mods)
{
    ImGui_ImplGlfw_KeyCallback(glfwGetCurrentContext(), key, scancode, action, mods);

    return false;
}

bool GuiService::_onChar(unsigned int codepoint)
{
    ImGui_ImplGlfw_CharCallback(glfwGetCurrentContext(), codepoint);

    return false;
}

bool GuiService::_onCursorEnter(bool entered)
{
    ImGui_ImplGlfw_CursorEnterCallback(glfwGetCurrentContext(), entered);

    return false;
}

// bd->PrevUserCallbackWindowFocus = glfwSetWindowFocusCallback(window, ImGui_ImplGlfw_WindowFocusCallback);
// bd->PrevUserCallbackCursorEnter = glfwSetCursorEnterCallback(window, ImGui_ImplGlfw_CursorEnterCallback);
// +   bd->PrevUserCallbackCursorPos = glfwSetCursorPosCallback(window, ImGui_ImplGlfw_CursorPosCallback);
// +   bd->PrevUserCallbackMousebutton = glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
// +   bd->PrevUserCallbackScroll = glfwSetScrollCallback(window, ImGui_ImplGlfw_ScrollCallback);
// +   bd->PrevUserCallbackKey = glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
// +   bd->PrevUserCallbackChar = glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
// bd->PrevUserCallbackMonitor = glfwSetMonitorCallback(ImGui_ImplGlfw_MonitorCallback);