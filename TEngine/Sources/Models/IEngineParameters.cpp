#include "IEngineParameters.h"

#include "EngineParameters.h"

using namespace TEngine::Models;

std::shared_ptr<IEngineParameters> TEngine::Models::createEngineParameters()
{
	return std::make_shared<EngineParameters>();
}
