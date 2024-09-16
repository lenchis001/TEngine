#ifndef MESH_SERVICE_H
#define MESH_SERVICE_H

#include <map>
#include <memory>

#include "IMeshService.h"

#include "Components/Graphics/Rendering/Services/Shaders/IShadersService.h"
#include "Components/Graphics/Rendering/Services/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Services/Textures/ITexturesService.h"

#include "Components/Graphics/MeshLoading/Services/IMeshLoadingService.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Services::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;

namespace TEngine::Components::Graphics::Rendering::Services::Meshes
{
    class MeshService : public IMeshService
    {
    public:
        MeshService(
            std::shared_ptr<IMeshLoadingService> meshLoadingService,
            std::shared_ptr<IBuffersService> buffersService,
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<ITexturesService> texturesService);
        ~MeshService() override;

        std::shared_ptr<IRenderableMesh> take(const std::string &path) override;

        void release(std::shared_ptr<IRenderableMesh> renderableMesh) override;

    private:
        std::shared_ptr<IRenderableShape> _toRenderableShape(std::shared_ptr<IShape> shape, const std::string &path);

        std::map<std::string, std::pair<std::size_t, std::shared_ptr<IRenderableMesh>>> _renderableMeshes;

        std::shared_ptr<IMeshLoadingService> _meshLoadingService;
        std::shared_ptr<IBuffersService> _buffersService;
        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<ITexturesService> _texturesService;
    };
}

#endif // MESH_SERVICE_H