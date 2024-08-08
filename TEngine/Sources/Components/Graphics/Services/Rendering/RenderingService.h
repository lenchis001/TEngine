#ifndef TENGINE_RENDERINGSERVICE_H
#define TENGINE_RENDERINGSERVICE_H

#include "IRenderingService.h"

#include "GLFW/glfw3.h"

namespace TEngine::Components::Graphics::Services::Rendering
{
    class RenderingService : public IRenderingService
    {
    public:
        RenderingService();

        void initialize(RenderingParameters& parameters) override;

        void render() override;
    private:
        GLFWwindow *_window;
    };
}

#endif //TENGINE_RENDERINGSERVICE_H