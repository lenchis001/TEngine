#ifndef TENGINE_IENGINEPARAMETERS_H
#define TENGINE_IENGINEPARAMETERS_H

#include "memory"

#include "Configs/TEngineExport.h"

#include "Components/Graphics/Models/IGraphicsParameters.h"

namespace TEngine::Models
{
	class TENGINE_API IEngineParameters
	{
	public:
		virtual ~IEngineParameters() = default;

		virtual void setGraphicsParameters(std::shared_ptr<TEngine::Components::Graphics::Models::IGraphicsParameters> graphicsParameters) = 0;

		virtual std::shared_ptr<TEngine::Components::Graphics::Models::IGraphicsParameters> getGraphicsParameters() = 0;
	};

	TENGINE_API std::shared_ptr<IEngineParameters> createEngineParameters();
}

#endif //TENGINE_IENGINEPARAMETERS_H