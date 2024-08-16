#include "RenderableObjectBase.h"

#include "algorithm"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;

RenderableObjectBase::RenderableObjectBase() : _position(Vector3df(0.0f, 0.0f, 0.0f)),
											   _rotation(Vector3df(0.0f, 0.0f, 0.0f)),
											   _scale(Vector3df(1.0f, 1.0f, 1.0f)),
											   _parentMatrix(Matrix4x4f(1.0f))
{
	_updateTranslationMatrix();
	_updateRotationMatrix();
	_updateScaleMatrix();
	_updateModelMatrix(_parentMatrix);
}

RenderableObjectBase::RenderableObjectBase(
	const Vector3df &position,
	const Vector3df &rotation,
	const Vector3df &scale) : _position(position),
							  _rotation(rotation),
							  _scale(scale),
							  _parentMatrix(Matrix4x4f(1.0f))
{
	_updateTranslationMatrix();
	_updateRotationMatrix();
	_updateScaleMatrix();
	_updateModelMatrix(_parentMatrix);
}

RenderableObjectBase::~RenderableObjectBase()
{
	// Implementation goes here
}

const std::vector<std::shared_ptr<IRenderableObject>> &RenderableObjectBase::getChildren() const
{
	return _children;
}

void RenderableObjectBase::addChild(std::shared_ptr<IRenderableObject> child)
{
	_children.push_back(child);

	child->_updateModelMatrix(_modelMatrix);
}

void RenderableObjectBase::removeChild(std::shared_ptr<IRenderableObject> child)
{
	_children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
}

void RenderableObjectBase::setPosition(const Vector3df &position)
{
	_position = position;

	_updateTranslationMatrix();
}

void RenderableObjectBase::setRotation(const Vector3df &rotation)
{
	_rotation = rotation;

	_updateRotationMatrix();
}

void RenderableObjectBase::setScale(const Vector3df &scale)
{
	_scale = scale;

	_updateScaleMatrix();
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

const Matrix4x4f &RenderableObjectBase::getModelMatrix() const
{
	return _modelMatrix;
}

void RenderableObjectBase::_updateTranslationMatrix()
{
	_translationMatrix = Matrix4x4f(
		1.0f, 0.0f, 0.0f, _position.getX(),
		0.0f, 1.0f, 0.0f, _position.getY(),
		0.0f, 0.0f, 1.0f, _position.getZ(),
		0.0f, 0.0f, 0.0f, 1.0f);

	_updateModelMatrix(_parentMatrix, true);
}

void RenderableObjectBase::_updateRotationMatrix()
{
	float pitch = _rotation.getX();
	float yaw = _rotation.getY();
	float roll = _rotation.getZ();

	// Rotation matrix around the X-axis (pitch)
	Matrix4x4f rotationX(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(pitch), -sin(pitch), 0.0f,
		0.0f, sin(pitch), cos(pitch), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	// Rotation matrix around the Y-axis (yaw)
	Matrix4x4f rotationY(
		cos(yaw), 0.0f, sin(yaw), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin(yaw), 0.0f, cos(yaw), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	// Rotation matrix around the Z-axis (roll)
	Matrix4x4f rotationZ(
		cos(roll), -sin(roll), 0.0f, 0.0f,
		sin(roll), cos(roll), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	// Combine the rotation matrices
	_rotationMatrix = rotationZ * rotationY * rotationX;

	_updateModelMatrix(_parentMatrix, true);
}

void RenderableObjectBase::_updateScaleMatrix()
{
	_scaleMatrix = Matrix4x4f(
		_scale.getX(), 0.0f, 0.0f, 0.0f,
		0.0f, _scale.getY(), 0.0f, 0.0f,
		0.0f, 0.0f, _scale.getZ(), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	_updateModelMatrix(_parentMatrix, true);
}

void RenderableObjectBase::_updateModelMatrix(const Matrix4x4f &parentMatrix, bool force)
{
	if (force || _parentMatrix != parentMatrix)
	{
		_parentMatrix = parentMatrix;
		_modelMatrix = _parentMatrix * _translationMatrix * _rotationMatrix * _scaleMatrix;
	}

	for (const auto child : _children)
	{
		child->_updateModelMatrix(_modelMatrix);
	}
}