#ifndef TENGINE_IGRAPHICSSERVICE_H
#define TENGINE_IGRAPHICSSERVICE_H

#include "future"
#include "memory"
#include "string"

#include "Models/DataActionResult.h"

#include "Models/IGraphicsParameters.h"
#include "Rendering/Services/Scene/ISceneService.h"
#include "Rendering/Services/Gui/IGuiService.h"

namespace TEngine::Components::Graphics::Services
{
    class IGraphicsService
    {
    public:
        virtual void initialize(std::shared_ptr<TEngine::Components::Graphics::Models::IGraphicsParameters> parameters) = 0;

        virtual bool isShutdownRequested() const = 0;

        virtual double getTime() const = 0;

        virtual void render() = 0;

        virtual std::shared_ptr<Rendering::Services::Scene::ISceneService> getSceneService() = 0;

        virtual std::shared_ptr<Rendering::Services::Gui::IGuiService> getGuiService() = 0;

        virtual ~IGraphicsService() = default;
    };
}

#endif // TENGINE_IGRAPHICSSERVICE_H