#include "BigWorldParameters.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Optimization;

BigWorldParameters::BigWorldParameters()
{
    _visibilityTreshold = 64;
    _trakingFrequency = 2;
    _queriesAmount = 1;
    _isEnabled = false;
}

void BigWorldParameters::setVisibilityTreshold(unsigned int value)
{
    _visibilityTreshold = value;
}

unsigned int BigWorldParameters::getVisibilityTreshold() const
{
    return _visibilityTreshold;
}

void BigWorldParameters::setTrakingFrequency(unsigned int value)
{
    _trakingFrequency = value;
}

unsigned int BigWorldParameters::getTrakingFrequency() const
{
    return _trakingFrequency;
}

void BigWorldParameters::setQueriesAmount(unsigned int value)
{
    _queriesAmount = value;
}

unsigned int BigWorldParameters::getQueriesAmount() const
{
    return _queriesAmount;
}

void BigWorldParameters::setEnabled(bool value)
{
    _isEnabled = value;
}

bool BigWorldParameters::isEnabled() const
{
    return _isEnabled;
}
