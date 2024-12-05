#include "ImageRenderingStrategy.h"

//#include "imgui.h"

using namespace TEngine::Components::Graphics::Rendering::Gui::ControlRenderingStrategies;

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
    // if (!_isPositionSet){
    //     ImGui::SetCursorPos(ImVec2(_position.getX(), _position.getY()));

    //     _isPositionSet = true;
    // }

    // ImGui::Image(reinterpret_cast<void*>(_textureId), ImVec2(_size.getX(), _size.getY()));
}