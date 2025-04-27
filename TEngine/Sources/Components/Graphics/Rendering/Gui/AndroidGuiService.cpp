#ifdef __ANDROID__

#include "AndroidGuiService.h"

using namespace TEngine::Components::Graphics::Rendering::Gui;

void AndroidGuiService::initialize() {

}

void AndroidGuiService::render() {

}

std::shared_ptr<IWindowRenderingStrategy> AndroidGuiService::addWindow() {
    return nullptr;
}

std::shared_ptr<IImageRenderingStrategy> AndroidGuiService::addImage(const std::string &path) {
    return nullptr;
}

std::shared_ptr<IInputRenderingStrategy> AndroidGuiService::addInput() {
    return nullptr;
}

#endif // __ANDROID__