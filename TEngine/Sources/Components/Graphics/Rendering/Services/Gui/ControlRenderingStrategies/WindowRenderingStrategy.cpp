#include "WindowRenderingStrategy.h"

#include <cassert>

#include "imgui.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies;

WindowRenderingStrategy::WindowRenderingStrategy()
    : ControlStrategyBase(),
      _isSizeSet(true),
      _size(0, 0),
      _isPositionSet(true),
      _position(0, 0),
      _title("Window"),
      _resizable(true),
      _fullscreen(false)
{
}

void WindowRenderingStrategy::setSize(const Vector2di &value)
{
    assert(value.getX() > 0 && value.getY() > 0 && "Size must be greater than 0!");

    _size = value;
    _isSizeSet = false;
}

void WindowRenderingStrategy::setPosition(const Vector2di &value)
{
    _position = value;
    _isPositionSet = false;
}

void WindowRenderingStrategy::setTitle(const std::string &title)
{
    assert(!title.empty() && "Title cannot be empty!");

    _title = title;
}

void WindowRenderingStrategy::setResizable(bool resizable)
{
    _resizable = resizable;
}

void WindowRenderingStrategy::setFullscreen(bool fullscreen)
{
    _fullscreen = fullscreen;
}

void WindowRenderingStrategy::render()
{
    static int counter = 0;

    if (!_isSizeSet)
    {
        ImGui::SetNextWindowSize(ImVec2(_size.getX(), _size.getY()));
    }

    if (!_isPositionSet)
    {
        ImGui::SetNextWindowPos(ImVec2(_position.getX(), _position.getY()));
    }

    ImGuiWindowFlags flags = _resizable ? ImGuiWindowFlags_None : ImGuiWindowFlags_NoResize;

    if (_fullscreen)
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));

        flags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    ImGui::Begin(_title.c_str(), nullptr, flags);

    ControlStrategyBase::render();

    ImGui::End();
}