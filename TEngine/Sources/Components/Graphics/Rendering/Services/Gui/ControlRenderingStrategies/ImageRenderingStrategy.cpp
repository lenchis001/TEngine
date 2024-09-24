#include "ImageRenderingStrategy.h"

#include "imgui.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies;

ImageRenderingStrategy::ImageRenderingStrategy(std::shared_ptr<ITexturesService> textureService, const std::string& path)
    : _textureService(textureService)
{
    _textureId = _textureService->take(path);
}

ImageRenderingStrategy::~ImageRenderingStrategy()
{
    _textureService->release(_textureId);
}

void ImageRenderingStrategy::render()
{
    ImGui::Image(reinterpret_cast<void*>(_textureId), ImVec2(720, 480));
}