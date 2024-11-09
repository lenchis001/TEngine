#include "InputRenderingStrategy.h"

#include "imgui.h"

using namespace TEngine::Components::Graphics::Rendering::Gui::ControlRenderingStrategies;

InputRenderingStrategy::InputRenderingStrategy() : _text("")
{
}

void InputRenderingStrategy::setText(const std::string &text)
{
    memcpy(_text, text.c_str(), text.size());
}

const std::string& InputRenderingStrategy::getText() const
{
    return _text;
}

void InputRenderingStrategy::render()
{
    ImGui::InputText("##input", _text, 256);
}