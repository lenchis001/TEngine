#include "vector"
#include "string"
#include "future"

#include "Models/DataActionResult.h"
#include "Components/Graphics/Models/MeshLoading/Plugins/ErrorCodes.h"
#include "Components/Graphics/Models/MeshLoading/Plugins/IStaticMesh.h"

namespace TEngine::Components::Graphics::MeshLoading::Services::Plugins
{
    class IMeshLoadingPlugin
    {
    public:
        virtual std::vector<std::wstring> getSupportedExtensions() const = 0;

        virtual std::future<TEngine::Models::DataActionResult<Models::MeshLoading::Plugins::ErrorCodes, Models::MeshLoading::Plugins::IStaticMesh>> loadMesh(const std::wstring &path) = 0;

        virtual ~IMeshLoadingPlugin() = default;
    };
}