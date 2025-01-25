#include "SceneParameters.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Models;

SceneParameters::SceneParameters()
    : _sequenceUpdateThreshold(10.0f)
{
}

float SceneParameters::getSequenceUpdateThreshold() const
{
    return _sequenceUpdateThreshold;
}

void SceneParameters::setSequenceUpdateThreshold(float sequenceUpdateThreshold)
{
    _sequenceUpdateThreshold = sequenceUpdateThreshold;
}