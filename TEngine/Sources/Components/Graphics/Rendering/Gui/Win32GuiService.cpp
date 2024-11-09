#ifdef _WIN32

#include "Win32GuiService.h"

using namespace TEngine::Components::Graphics::Rendering::Gui;

void Win32GuiService::initialize() {

}

void Win32GuiService::render() {

}

std::shared_ptr<IWindowRenderingStrategy> Win32GuiService::addWindow() {
    return nullptr;
}

std::shared_ptr<IImageRenderingStrategy> Win32GuiService::addImage(const std::string &path) {
    return nullptr;
}

std::shared_ptr<IInputRenderingStrategy> Win32GuiService::addInput() {
    return nullptr;
}

#endif // _WIN32