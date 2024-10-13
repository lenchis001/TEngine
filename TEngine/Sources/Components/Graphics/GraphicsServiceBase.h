#ifndef TENGINE_GRAPHICSSERVICEBASE_H
#define TENGINE_GRAPHICSSERVICEBASE_H

#include <memory>
#include <vector>

#include "IGraphicsService.h"

#include "MeshLoading/Services/IMeshLoadingService.h"
#include "Rendering/Services/Textures/ITexturesService.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;

using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Gui;

namespace TEngine::Components::Graphics::Services
{
    class GraphicsServiceBase : public IGraphicsService
    {
    public:
        GraphicsServiceBase(
            std::shared_ptr<ISceneService> sceneService,
            std::shared_ptr<IGuiService> guiService,
            std::shared_ptr<IMeshLoadingService> meshLoadingService,
            std::shared_ptr<ITexturesService> texturesService);

        ~GraphicsServiceBase();

        void initialize(std::shared_ptr<IGraphicsParameters> parameters) override;

        void deinitialize() override;

        void render() override;

        void resize(int width, int height) override;

        std::shared_ptr<ISceneService> getSceneService() override;

        std::shared_ptr<IGuiService> getGuiService() override;

    private:
        std::shared_ptr<ISceneService> _sceneService;
        std::shared_ptr<IGuiService> _guiService;
        std::shared_ptr<IMeshLoadingService> _meshLoadingService;
        std::shared_ptr<ITexturesService> _texturesService;
    };
}

#endif // TENGINE_GRAPHICSSERVICEBASE_H