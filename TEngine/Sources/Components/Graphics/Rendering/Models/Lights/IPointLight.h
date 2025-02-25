#ifndef TENGINE_IPOINTLIGHT_H
#define TENGINE_IPOINTLIGHT_H

#include "ILight.h"

namespace TEngine::Components::Graphics::Rendering::Models::Lights {
	class IPointLight : public ILight
	{
	public:
		virtual float getRadius() const = 0;
		virtual void setRadius(float radius) = 0;
	};
}

#endif // TENGINE_IPOINTLIGHT_H