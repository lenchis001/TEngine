#ifndef TENGINE_RENDERINGSERVICE_H
#define TENGINE_RENDERINGSERVICE_H

#include "IRenderingService.h"

#include "vector"

#include "GLFW/glfw3.h"

#include "Strategies/IRenderingStrategy.h"
#include "Components/Graphics/Rendering/Services/Shaders/IShadersService.h"

using namespace TEngine::Components::Graphics::Rendering::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;
using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;

using namespace TEngine::Components::Graphics::Rendering::Services::Strategies;

namespace TEngine::Components::Graphics::Rendering::Services
{
    class RenderingService : public IRenderingService
    {
    public:
        RenderingService(std::shared_ptr<IShadersService> shadersService);

        void initialize(std::shared_ptr<IRenderingParameters> parameters) override;

        void addToRendering(std::shared_ptr<IRenderableObject> object, PrimitiveTypes type) override;

        void render() override;
    private:
        GLFWwindow *_window;

        std::vector<std::shared_ptr<IRenderingStrategy>> _strategies;
        std::shared_ptr<IShadersService> _shadersService;
    };
}

#endif //TENGINE_RENDERINGSERVICE_H