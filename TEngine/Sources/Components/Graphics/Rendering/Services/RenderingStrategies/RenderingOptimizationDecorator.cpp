#include "RenderingOptimizationDecorator.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies;

RenderingOptimizationDecorator::RenderingOptimizationDecorator(std::shared_ptr<IRenderingStrategy> strategy)
    : _strategy(strategy),
      _frameCounter(0),
      _distance(0.f)
{
}

void RenderingOptimizationDecorator::render(
    const Matrix4x4f &vpMatrix,
    const Vector3df &cameraPosition)
{
    if (_frameCounter % 10 == 0)
    {
        _distance = cameraPosition.distance(_strategy->getAbsolutePosition());
    }

    if (_distance < 100.f)
    {
        _strategy->render(vpMatrix, cameraPosition);
    }

    _frameCounter++;
}

void RenderingOptimizationDecorator::setPosition(const Vector3df &position)
{
    _strategy->setPosition(position);
}

void RenderingOptimizationDecorator::setRotation(const Vector3df &rotation)
{
    _strategy->setRotation(rotation);
}

void RenderingOptimizationDecorator::setScale(const Vector3df &scale)
{
    _strategy->setScale(scale);
}

const Vector3df &RenderingOptimizationDecorator::getPosition() const
{
    return _strategy->getPosition();
}

const Vector3df &RenderingOptimizationDecorator::getRotation() const
{
    return _strategy->getRotation();
}

const Vector3df &RenderingOptimizationDecorator::getScale() const
{
    return _strategy->getScale();
}

Vector3df RenderingOptimizationDecorator::getAbsolutePosition()
{
    return _strategy->getAbsolutePosition();
}

const std::vector<std::shared_ptr<IRenderingStrategy>> &RenderingOptimizationDecorator::getChildren() const
{
    return _strategy->getChildren();
}

void RenderingOptimizationDecorator::addChild(std::shared_ptr<IRenderingStrategy> child)
{
    _strategy->addChild(child);
}

void RenderingOptimizationDecorator::removeChild(std::shared_ptr<IRenderingStrategy> child)
{
    _strategy->removeChild(child);
}

void RenderingOptimizationDecorator::_updateModelMatrix(const Matrix4x4f &parentMatrix, bool isPrsUpdated)
{
    _strategy->_updateModelMatrix(parentMatrix, isPrsUpdated);
}
