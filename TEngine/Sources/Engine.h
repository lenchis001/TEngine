#ifndef Engine_H
#define Engine_H

#include "IEngine.h"

#include "GLFW/glfw3.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::Services;

namespace TEngine
{
    class Engine : public IEngine
    {
    public:
        Engine(std::shared_ptr<IGraphicsService> graphicsService);
        ~Engine();

        void initialize(std::shared_ptr<IEngineParameters> parameters) override;

        std::shared_ptr<IGraphicsService> getGraphicsService() override;

    private:
        std::shared_ptr<IGraphicsService> _graphicsService;

        GLFWwindow* _window;
    };
}

#endif // Engine_H