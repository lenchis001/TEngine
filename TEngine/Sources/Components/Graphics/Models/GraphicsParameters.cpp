#include "GraphicsParameters.h"

#include "Components/Graphics/Rendering/Scene/Models/SceneParameters.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::Models;

GraphicsParameters::GraphicsParameters()
{
    setWidth(1280);
    setHeight(720);
    setOpenGlMajorVersion(3);
    setOpenGlMinorVersion(3);
    setTitle("TEngine");
    setIsVerticalSyncEnabled(true);
    setSceneParameters(std::make_shared<SceneParameters>());
}

int GraphicsParameters::getWidth() const
{
    return _width;
}

void GraphicsParameters::setWidth(int width)
{
    _width = width;
}

int GraphicsParameters::getHeight() const
{
    return _height;
}

void GraphicsParameters::setHeight(int height)
{
    _height = height;
}

int GraphicsParameters::getOpenGlMajorVersion() const
{
    return _openGlMajorVersion;
}

void GraphicsParameters::setOpenGlMinorVersion(int openGlMinorVersion)
{
    _openGlMinorVersion = openGlMinorVersion;
}

int GraphicsParameters::getOpenGlMinorVersion() const
{
    return _openGlMinorVersion;
}

void GraphicsParameters::setOpenGlMajorVersion(int openGlMajorVersion)
{
    _openGlMajorVersion = openGlMajorVersion;
}

const std::string &GraphicsParameters::getTitle() const
{
    return _title;
}

void GraphicsParameters::setTitle(const std::string &title)
{
    _title = title;
}

bool GraphicsParameters::getIsVerticalSyncEnabled() const
{
    return _isVerticalSyncEnabled;
}

void GraphicsParameters::setIsVerticalSyncEnabled(bool value)
{
    _isVerticalSyncEnabled = value;
}

std::shared_ptr<ISceneParameters> GraphicsParameters::getSceneParameters() const
{
    return _sceneParameters;
}

void GraphicsParameters::setSceneParameters(std::shared_ptr<ISceneParameters> sceneParameters)
{
    _sceneParameters = sceneParameters;
}