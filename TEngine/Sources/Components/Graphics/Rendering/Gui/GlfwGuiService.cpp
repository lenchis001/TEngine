#include "GlfwGuiService.h"

#include "ControlRenderingStrategies/WindowRenderingStrategy.h"
#include "ControlRenderingStrategies/ImageRenderingStrategy.h"
#include "ControlRenderingStrategies/InputRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Gui;

GlfwGuiService::GlfwGuiService(std::shared_ptr<IEventService> eventService, std::shared_ptr<ITexturesService> texturesService)
    : _eventService(eventService), 
    _texturesService(texturesService),
    _screen(new Screen()),
    _gui(new FormHelper(_screen))
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
    screen->initialize(glfwGetCurrentContext(), true);

    _eventService->registerCursorMoveHandler(std::bind(&GlfwGuiService::_onCursorMove, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->registerMouseButtonHandler(std::bind(&GlfwGuiService::_onMouseButtonClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    _eventService->registerScrollHandler(std::bind(&GlfwGuiService::_onScroll, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->registerKeyHandler(std::bind(&GlfwGuiService::_onKey, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    _eventService->registerCharHandler(std::bind(&GlfwGuiService::_onChar, this, std::placeholders::_1));
    _eventService->registerCursorEnterHandler(std::bind(&GlfwGuiService::_onCursorEnter, this, std::placeholders::_1));


    ref<Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Form helper example");
    gui->addGroup("Basic types");
    gui->addVariable("bool", bvar)->setTooltip("Test tooltip.");
    gui->addVariable("string", strval);

    gui->addGroup("Validating fields");
    gui->addVariable("int", ivar)->setSpinnable(true);
    gui->addVariable("float", fvar)->setTooltip("Test.");
    gui->addVariable("double", dvar)->setSpinnable(true);

    gui->addGroup("Complex types");
    gui->addVariable("Enumeration", enumval, enabled)->setItems({ "Item 1", "Item 2", "Item 3" });
    gui->addVariable("Color", colval)
       ->setFinalCallback([](const Color &c) {
             std::cout << "ColorPicker Final Callback: ["
                       << c.r() << ", "
                       << c.g() << ", "
                       << c.b() << ", "
                       << c.w() << "]" << std::endl;
         });

    gui->addGroup("Other widgets");
    gui->addButton("A button", []() { std::cout << "Button pressed." << std::endl; })->setTooltip("Testing a much longer tooltip, that will wrap around to new lines multiple times.");;

    screen->setVisible(true);
    screen->performLayout();
    nanoguiWindow->center();
}

void GlfwGuiService::render()
{
        // Draw nanogui
        screen->drawContents();
        screen->drawWidgets();

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
