#ifndef TENGINE_IGRAPHICSPARAMETERS_H
#define TENGINE_IGRAPHICSPARAMETERS_H

#include "memory"

#include "Configs/TEngineExport.h"

#include "Components/Graphics/Rendering/Models/IRenderingParameters.h"

namespace TEngine::Components::Graphics::Models
{
	class TENGINE_API IGraphicsParameters
	{
	public:
		virtual ~IGraphicsParameters() = default;

		virtual std::shared_ptr<TEngine::Components::Graphics::Rendering::Models::IRenderingParameters> getRenderingParameters() = 0;

		virtual void setRenderingParameters(std::shared_ptr<TEngine::Components::Graphics::Rendering::Models::IRenderingParameters> renderingParameters) = 0;
	};
}

#endif //TENGINE_IGRAPHICSPARAMETERS_H