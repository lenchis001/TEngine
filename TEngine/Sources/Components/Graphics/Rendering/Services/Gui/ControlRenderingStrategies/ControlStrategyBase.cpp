#include "ControlStrategyBase.h"

#include <cassert>
#include <algorithm>

using namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies;

ControlStrategyBase::ControlStrategyBase() : _isSizeSet(true),
                                             _size(0, 0),
                                             _isPositionSet(true),
                                             _position(0, 0)
{
}

void ControlStrategyBase::render()
{
    for (auto &child : _children)
    {
        child->render();
    }
}

void ControlStrategyBase::addChild(std::shared_ptr<IControlRenderingStrategy> value)
{
    assert(value != nullptr && "Child is null!");
    assert(std::find(_children.begin(), _children.end(), value) == _children.end() && "Child already exists!");

    _children.push_back(value);
}

void ControlStrategyBase::removeChild(std::shared_ptr<IControlRenderingStrategy> value)
{
    assert(value != nullptr && "Child is null!");

    auto it = std::find(_children.begin(), _children.end(), value);

    assert(it != _children.end() && "Child does not exist!");

    _children.erase(it);
}

void ControlStrategyBase::setSize(const Vector2di &value)
{
    _size = value;
    _isSizeSet = true;
}

void ControlStrategyBase::setPosition(const Vector2di &value)
{
    _position = value;
    _isPositionSet = true;
}