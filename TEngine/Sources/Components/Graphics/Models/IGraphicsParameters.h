#ifndef TENGINE_IGRAPHICSPARAMETERS_H
#define TENGINE_IGRAPHICSPARAMETERS_H

#include <memory>
#include <string>

#include "Configs/TEngineExport.h"

#include "Components/Graphics/Rendering/Scene/Models/ISceneParameters.h"

namespace TEngine::Components::Graphics::Models
{
	class TENGINE_API IGraphicsParameters
	{
	public:
		virtual ~IGraphicsParameters() = default;

		virtual int getWidth() const = 0;

		virtual void setWidth(int width) = 0;

		virtual int getHeight() const = 0;

		virtual void setHeight(int height) = 0;

		virtual int getOpenGlMajorVersion() const = 0;

		virtual void setOpenGlMinorVersion(int openGlMinorVersion) = 0;

		virtual int getOpenGlMinorVersion() const = 0;

		virtual void setOpenGlMajorVersion(int openGlMajorVersion) = 0;

		virtual const std::string& getTitle() const = 0;

		virtual void setTitle(const std::string& title) = 0;

		virtual bool getIsVerticalSyncEnabled() const = 0;

		virtual void setIsVerticalSyncEnabled(bool value) = 0;

		virtual std::shared_ptr<Rendering::Scene::Models::ISceneParameters> getSceneParameters() const = 0;

		virtual void setSceneParameters(std::shared_ptr<Rendering::Scene::Models::ISceneParameters> sceneParameters) = 0;
	};
}

#endif //TENGINE_IGRAPHICSPARAMETERS_H