#ifndef TENGINE_RENDERINGSERVICE_H
#define TENGINE_RENDERINGSERVICE_H

#include "IRenderingService.h"

#include "GLFW/glfw3.h"

using namespace TEngine::Components::Graphics::Models::Rendering;

namespace TEngine::Components::Graphics::Services::Rendering
{
    class RenderingService : public IRenderingService
    {
    public:
        RenderingService();

        void initialize(std::shared_ptr<IRenderingParameters> parameters) override;

        void render() override;
    private:
        GLFWwindow *_window;
    };
}

#endif //TENGINE_RENDERINGSERVICE_H