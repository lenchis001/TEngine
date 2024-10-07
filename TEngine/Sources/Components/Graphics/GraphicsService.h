#ifndef TENGINE_GRAPHICSSERVICE_H
#define TENGINE_GRAPHICSSERVICE_H

#include <memory>
#include <vector>

#include "GLFW/glfw3.h"

#include "IGraphicsService.h"

#include "Mixins/ContextAwareMixin.h"

#include "MeshLoading/Services/IMeshLoadingService.h"
#include "Rendering/Services/Textures/ITexturesService.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;
using namespace TEngine::Mixins;

using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Gui;

namespace TEngine::Components::Graphics::Services
{
    class GraphicsService : public IGraphicsService, public ContextAwareMixin<GraphicsService>
    {
    public:
        GraphicsService(
            std::shared_ptr<ISceneService> sceneService,
            std::shared_ptr<IGuiService> guiService,
            std::shared_ptr<IMeshLoadingService> meshLoadingService,
            std::shared_ptr<ITexturesService> texturesService);

        ~GraphicsService();

        void initialize(std::shared_ptr<IGraphicsParameters> parameters) override;

        void deinitialize() override;

        bool isShutdownRequested() const override;

        double getTime() const override;

        void render() override;

        std::shared_ptr<ISceneService> getSceneService() override;

        std::shared_ptr<IGuiService> getGuiService() override;

    private:
        void _initializeGlfw(std::shared_ptr<IGraphicsParameters> parameters);

        static void _onWindowResized(GLFWwindow* window, int width, int height);

        GLFWwindow *_window;

        std::shared_ptr<ISceneService> _sceneService;
        std::shared_ptr<IGuiService> _guiService;
        std::shared_ptr<IMeshLoadingService> _meshLoadingService;
        std::shared_ptr<ITexturesService> _texturesService;
    };
}

#endif // TENGINE_GRAPHICSSERVICE_H