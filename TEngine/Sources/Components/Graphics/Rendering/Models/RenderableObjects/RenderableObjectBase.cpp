#include "RenderableObjectBase.h"

#include "algorithm"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;

RenderableObjectBase::RenderableObjectBase() :
	_position(Vector3df(0.0f, 0.0f, 0.0f)),
	_rotation(Vector3df(0.0f, 0.0f, 0.0f)),
	_scale(Vector3df(1.0f, 1.0f, 1.0f))
{
}

RenderableObjectBase::RenderableObjectBase(const Vector3df& position, const Vector3df& rotation, const Vector3df& scale) : 
	_position(position),
	_rotation(rotation),
	_scale(scale)
{
}

RenderableObjectBase::~RenderableObjectBase()
{
	// Implementation goes here
}

const std::vector<std::shared_ptr<IRenderableObject>>& RenderableObjectBase::getChildren() const
{
	return _children;
}

void RenderableObjectBase::addChild(std::shared_ptr<IRenderableObject> child)
{
	_children.push_back(child);
}

void RenderableObjectBase::removeChild(std::shared_ptr<IRenderableObject> child)
{
	_children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
}

void RenderableObjectBase::setPosition(const Vector3df& position)
{
	_position = position;
}

void RenderableObjectBase::setRotation(const Vector3df& rotation)
{
	_rotation = rotation;
}

void RenderableObjectBase::setScale(const Vector3df& scale)
{
	_scale = scale;
}

Vector3df RenderableObjectBase::getPosition() const
{
	return _position;
}

Vector3df RenderableObjectBase::getRotation() const
{
	return _rotation;
}

Vector3df RenderableObjectBase::getScale() const
{
	return _scale;
}

const Matrix4x4f& RenderableObjectBase::getTransformationMatrix() const
{
	Matrix4x4f transformationMatrix;


	return transformationMatrix;
}