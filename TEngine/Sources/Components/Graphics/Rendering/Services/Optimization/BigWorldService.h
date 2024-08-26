#include "IBigWorldService.h"

#include "map"

#include "GLFW/glfw3.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Models::Optimization;

namespace TEngine::Components::Graphics::Rendering::Services::Optimization
{
    class BigWorldService : public IBigWorldService
    {
    public:
        BigWorldService();
        ~BigWorldService() override = default;

        void initialize(std::shared_ptr<IBigWorldParameters> parameters) override;

        void render(
            const std::vector<std::shared_ptr<IRenderingStrategy>> strategies,
            const Components::Graphics::Models::Matrix4x4f &vpMatrix) override;

    private:
        GLuint _occlusionQueryId, _occlusionQueryResult;

        std::map<IRenderingStrategy*, int> priorityMap;
        std::size_t _targetIndex;

        unsigned int _visibilityTreshold;
        unsigned int _framesToSkip;
        unsigned int _queriesAmount;
        unsigned int _frameNumber;
    };
}