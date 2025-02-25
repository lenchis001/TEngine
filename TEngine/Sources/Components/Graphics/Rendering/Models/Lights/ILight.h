#ifndef TENGINE_ILIGHT_H
#define TENGINE_ILIGHT_H

#include <functional>

#include "Components/Graphics/Models/Vector3d.h"

namespace TEngine::Components::Graphics::Rendering::Models::Lights
{
	typedef std::function<void()> LightUpdateRequiredCallback;

	class ILight
	{
	public:
		virtual ~ILight() = default;

		virtual void setPosition(const Components::Graphics::Models::Vector3df& position) = 0;
		virtual const Components::Graphics::Models::Vector3df& getPosition() const = 0;

		virtual const Components::Graphics::Models::Vector3df& getDiffuseColor() const = 0;
	};
}

#endif // TENGINE_ILIGHT_H