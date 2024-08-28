#include "RenderingParameters.h"

using namespace TEngine::Components::Graphics::Rendering::Models;

RenderingParameters::RenderingParameters()
{
    setWidth(1280);
    setHeight(720);
    setOpenGlMajorVersion(3);
    setOpenGlMinorVersion(3);
    setTitle("TEngine");
    _isVerticalSyncEnabled = true;
}

int RenderingParameters::getWidth() const
{
    return _width;
}

int RenderingParameters::getHeight() const
{
    return _height;
}

void RenderingParameters::setWidth(int width)
{
    _width = width;
}

void RenderingParameters::setHeight(int height)
{
    _height = height;
}

int RenderingParameters::getOpenGlMajorVersion() const
{
    return _openGlMajorVersion;
}

void RenderingParameters::setOpenGlMajorVersion(int openGlMajorVersion)
{
    _openGlMajorVersion = openGlMajorVersion;
}

int RenderingParameters::getOpenGlMinorVersion() const
{
    return _openGlMinorVersion;
}

void RenderingParameters::setOpenGlMinorVersion(int openGlMinorVersion)
{
    _openGlMinorVersion = openGlMinorVersion;
}

const std::string &RenderingParameters::getTitle() const
{
    return _title;
}

void RenderingParameters::setTitle(const std::string &title)
{
    _title = title;
}

bool RenderingParameters::getIsVerticalSyncEnabled() const
{
    return _isVerticalSyncEnabled;
}

void RenderingParameters::setIsVerticalSyncEnabled(bool value)
{
    _isVerticalSyncEnabled = value;
}
