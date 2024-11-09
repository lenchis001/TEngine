#ifndef TENGINE_IGRAPHICSSERVICE_H
#define TENGINE_IGRAPHICSSERVICE_H

#include <memory>
#include <string>

#include "Models/DataActionResult.h"

#include "Models/IGraphicsParameters.h"
#include "Rendering/Scene/ISceneService.h"
#include "Rendering/Gui/IGuiService.h"

namespace TEngine::Components::Graphics
{
    class IGraphicsService
    {
    public:
        virtual void initialize(std::shared_ptr<TEngine::Components::Graphics::Models::IGraphicsParameters> parameters) = 0;

        virtual void deinitialize() = 0;

        virtual bool isShutdownRequested() const = 0;

        virtual double getTime() const = 0;

        virtual void render() = 0;

        virtual void resize(int width, int height) = 0;

        virtual std::shared_ptr<Rendering::Scene::ISceneService> getSceneService() = 0;

        virtual std::shared_ptr<Rendering::Gui::IGuiService> getGuiService() = 0;

        virtual ~IGraphicsService() = default;
    };
}

#endif // TENGINE_IGRAPHICSSERVICE_H