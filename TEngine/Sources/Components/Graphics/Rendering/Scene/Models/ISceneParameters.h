#ifndef TENGINE_ISCENEPARAMETERS_H
#define TENGINE_ISCENEPARAMETERS_H

#include <memory>
#include <string>

#include "Configs/TEngineExport.h"

namespace TEngine::Components::Graphics::Rendering::Scene::Models
{
	class TENGINE_API ISceneParameters
	{
	public:
		virtual ~ISceneParameters() = default;

		virtual float getSequenceUpdateThreshold() const = 0;

		virtual void setSequenceUpdateThreshold(float sequenceUpdateThreshold) = 0;
	};
}

#endif //TENGINE_ISCENEPARAMETERS_H