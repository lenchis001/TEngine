#include "RenderingOptimizationDecorator.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies;

RenderingOptimizationDecorator::RenderingOptimizationDecorator(std::shared_ptr<IRenderingStrategy> strategy)
    : _strategy(strategy),
      _frameCounter(0),
      _distance(0.f)
{
}

void RenderingOptimizationDecorator::render(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
    if ((_frameCounter % 30) == 0)
    {
        const auto &cameraPosition = activeCameraStrategy->getPosition();
        _distance = cameraPosition.distance(_strategy->getAbsolutePosition());
    }

    if (_distance < 100.f)
    {
        _strategy->render(activeCameraStrategy);
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

Vector3df RenderingOptimizationDecorator::getAbsolutePosition() const
{
    return _strategy->getAbsolutePosition();
}

Vector3df RenderingOptimizationDecorator::getAbsoluteRotation() const
{
    return _strategy->getAbsoluteRotation();
}

Vector3df RenderingOptimizationDecorator::getAbsoluteScale() const
{
    return _strategy->getAbsoluteScale();
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

const std::vector<float> &RenderingOptimizationDecorator::getVertices() const
{
    return _strategy->getVertices();
}

const Matrix4x4f &RenderingOptimizationDecorator::getModelMatrix() const
{
    return _strategy->getModelMatrix();
}

void RenderingOptimizationDecorator::_updateModelMatrix(const Matrix4x4f &parentMatrix, bool isPrsUpdated)
{
    _strategy->_updateModelMatrix(parentMatrix, isPrsUpdated);
}

void RenderingOptimizationDecorator::_onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent)
{
    _strategy->_onAttachedToParent(parent);
}

void RenderingOptimizationDecorator::_onDetachedFromParent()
{
    _strategy->_onDetachedFromParent();
}
