#include "IRenderingSequenceService.h"

namespace TEngine::Components::Graphics::Rendering::Scene::Sequence
{
    class RenderingSequenceService : public IRenderingSequenceService
    {
    public:
        RenderingSequenceService() = default;

        std::vector<std::shared_ptr<RenderingStrategies::IRenderingStrategy>> generateSequence(
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> root,
            const Graphics::Models::Vector3df &cameraPosition) override;

    private:
        void _toPlainSequence(std::shared_ptr<RenderingStrategies::IRenderingStrategy> root,
                               std::vector<std::shared_ptr<RenderingStrategies::IRenderingStrategy>> &sequence);
    };
}