#include "GuiService.h"

#include "GLFW/glfw3.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Gui;

GuiService::GuiService(std::shared_ptr<Events::Services::IEventService> eventService)
    : _eventService(eventService)
{
}

GuiService::~GuiService()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    _eventService->unregisterCursorMoveHandler(std::bind(&GuiService::_onCursorMove, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->unregisterMouseButtonHandler(std::bind(&GuiService::_onMouseButtonClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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
}

void GuiService::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

// bd->PrevUserCallbackWindowFocus = glfwSetWindowFocusCallback(window, ImGui_ImplGlfw_WindowFocusCallback);
// bd->PrevUserCallbackCursorEnter = glfwSetCursorEnterCallback(window, ImGui_ImplGlfw_CursorEnterCallback);
// +   bd->PrevUserCallbackCursorPos = glfwSetCursorPosCallback(window, ImGui_ImplGlfw_CursorPosCallback);
// bd->PrevUserCallbackMousebutton = glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
// bd->PrevUserCallbackScroll = glfwSetScrollCallback(window, ImGui_ImplGlfw_ScrollCallback);
// bd->PrevUserCallbackKey = glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
// bd->PrevUserCallbackChar = glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
// bd->PrevUserCallbackMonitor = glfwSetMonitorCallback(ImGui_ImplGlfw_MonitorCallback);