#ifndef TENGINE_GRAPHICSSERVICE_H
#define TENGINE_GRAPHICSSERVICE_H

#include "GLFW/glfw3.h"

#include "Mixins/ContextAwareMixin.h"

#include "GraphicsServiceBase.h"

using namespace TEngine::Mixins;

namespace TEngine::Components::Graphics::Services
{
    class GlfwGraphicsService : public GraphicsServiceBase, public ContextAwareMixin<GlfwGraphicsService>
    {
    public:
        GlfwGraphicsService(
            std::shared_ptr<ISceneService> sceneService,
            std::shared_ptr<IGuiService> guiService,
            std::shared_ptr<IMeshLoadingService> meshLoadingService,
            std::shared_ptr<ITexturesService> texturesService);

        ~GlfwGraphicsService();

        void initialize(std::shared_ptr<IGraphicsParameters> parameters) override;

        void deinitialize() override;

        bool isShutdownRequested() const override;

        double getTime() const override;

        void render() override;

    private:
        void _initializeGlfw(std::shared_ptr<IGraphicsParameters> parameters);

        static void _onWindowResized(GLFWwindow* window, int width, int height);

        GLFWwindow *_window;
    };
}

#endif // TENGINE_GRAPHICSSERVICE_H