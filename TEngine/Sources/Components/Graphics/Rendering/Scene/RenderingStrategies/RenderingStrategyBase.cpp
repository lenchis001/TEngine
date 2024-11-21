#include "RenderingStrategyBase.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;

RenderingStrategyBase::RenderingStrategyBase() : _position(Vector3df(0.0f, 0.0f, 0.0f)),
                                                 _rotation(Vector3df(0.0f, 0.0f, 0.0f)),
                                                 _scale(Vector3df(1.0f, 1.0f, 1.0f)),
                                                 _parentMatrix(Matrix4x4f(1.0f)),
                                                 _vpMatrix(Matrix4x4f(1.f)),
                                                 _mvpMatrix(Matrix4x4f(1.f)),
                                                 _translationMatrix(Matrix4x4f(1.f)),
                                                 _rotationMatrix(Matrix4x4f(1.f)),
                                                 _scaleMatrix(Matrix4x4f(1.f)),
                                                 _id(++_idCounter)
{
    _updateTranslationMatrix();
    _updateRotationMatrix();
    _updateScaleMatrix();
    _updateModelMatrix(_parentMatrix);
}

RenderingStrategyBase::~RenderingStrategyBase()
{
    removeAllChildren();
}

const std::vector<std::shared_ptr<IRenderingStrategy>> &RenderingStrategyBase::getChildren() const
{
    return _children;
}

void RenderingStrategyBase::addChild(std::shared_ptr<IRenderingStrategy> child)
{
    _children.push_back(child);

    child->_onAttachedToParent(shared_from_this());
}

void RenderingStrategyBase::removeChild(std::shared_ptr<IRenderingStrategy> child)
{
    auto childIterator = _children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());

    if (childIterator != _children.end())
    {
        child->_onDetachedFromParent();
    }
}

void RenderingStrategyBase::removeAllChildren()
{
    for (const auto child : _children)
    {
        child->_onDetachedFromParent();
    }

    _children.clear();
}

void RenderingStrategyBase::setPosition(const Vector3df &position)
{
    _position = position;

    _updateTranslationMatrix();
}

void RenderingStrategyBase::setRotation(const Vector3df &rotation)
{
    _rotation = rotation;

    _updateRotationMatrix();
}

void RenderingStrategyBase::setScale(const Vector3df &scale)
{
    _scale = scale;

    _updateScaleMatrix();
}

const Vector3df &RenderingStrategyBase::getPosition() const
{
    return _position;
}

const Vector3df &RenderingStrategyBase::getRotation() const
{
    return _rotation;
}

const Vector3df &RenderingStrategyBase::getScale() const
{
    return _scale;
}

void RenderingStrategyBase::setAbsolutePosition(const Vector3df &position)
{
    auto parentPosition = _parentMatrix.getPosition();

    auto diff = position - parentPosition;

    setPosition(diff);
}

void RenderingStrategyBase::setAbsoluteRotation(const Vector3df &rotation)
{
    auto parentRotation = _parentMatrix.getRotation();

    auto diff = rotation - parentRotation;

    setRotation(diff);
}

Vector3df RenderingStrategyBase::getAbsolutePosition() const
{
    return _modelMatrix.getPosition();
}

Vector3df RenderingStrategyBase::getAbsoluteRotation() const
{
    return _modelMatrix.getRotation();
}

Vector3df RenderingStrategyBase::getAbsoluteScale() const
{
    return _modelMatrix.getScale();
}

void RenderingStrategyBase::render(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
    const auto &vpMatrix = activeCameraStrategy->getVpMatrix();

    if (_vpMatrix != vpMatrix)
    {
        _vpMatrix = vpMatrix;

        _updateMvpMatrix();
    }

    for (const auto child : _children)
    {
        child->render(activeCameraStrategy);
    }
}

const std::string &RenderingStrategyBase::getName()
{
    if (_name.empty())
    {
        _name = _getDefaultName() + std::to_string(getId());
    }

    return _name;
}

void RenderingStrategyBase::setName(const std::string &name)
{
    _name = name;
}

int RenderingStrategyBase::getId() const
{
    return _id;
}

void RenderingStrategyBase::_updateTranslationMatrix()
{
    _translationMatrix.setTranslation(_position);

    _updateModelMatrix(_parentMatrix, true);
}

void RenderingStrategyBase::_updateRotationMatrix()
{
    _rotationMatrix.setRotation(_rotation);

    _updateModelMatrix(_parentMatrix, true);
}

void RenderingStrategyBase::_updateScaleMatrix()
{
    _scaleMatrix.setScale(_scale);

    _updateModelMatrix(_parentMatrix, true);
}

const Matrix4x4f &RenderingStrategyBase::getModelMatrix() const
{
    return _modelMatrix;
}

void RenderingStrategyBase::_updateModelMatrix(const Matrix4x4f &parentMatrix, bool isPrsUpdated)
{
    if (isPrsUpdated || _parentMatrix != parentMatrix)
    {
        _parentMatrix = parentMatrix;
        _modelMatrix.setMultiplyingResult(_parentMatrix, _translationMatrix, _rotationMatrix, _scaleMatrix);

        _updateMvpMatrix();

        for (const auto &child : _children)
        {
            child->_updateModelMatrix(_modelMatrix, false);
        }
    }
}

void RenderingStrategyBase::_onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent)
{
    _parentMatrix = parent->getModelMatrix();

    _updateModelMatrix(_parentMatrix);
}

void RenderingStrategyBase::_onDetachedFromParent()
{
    _parentMatrix = Matrix4x4f(1.0f);

    _updateModelMatrix(_parentMatrix);
}

void RenderingStrategyBase::_updateMvpMatrix()
{
    _mvpMatrix.setMultiplyingResult(_vpMatrix, _modelMatrix);
}

int RenderingStrategyBase::_idCounter = 0;