#ifndef TENGINE_IRENDERINGPARAMETERS_H
#define TENGINE_IRENDERINGPARAMETERS_H

#include "string"
#include "memory"

#include "Configs/TEngineExport.h"

#include "Optimization/IBigWorldParameters.h"

namespace TEngine::Components::Graphics::Rendering::Models
{
	class TENGINE_API IRenderingParameters
	{
	public:
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

		virtual std::shared_ptr<Optimization::IBigWorldParameters> getBigWorldParameters() const = 0;

		virtual void setBigWorldParameters(std::shared_ptr<Optimization::IBigWorldParameters> bigWorldParameters) = 0;

		virtual ~IRenderingParameters() = default;
	};
}

#endif //TENGINE_IRENDERINGPARAMETERS_H