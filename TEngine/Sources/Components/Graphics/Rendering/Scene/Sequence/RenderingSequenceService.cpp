#include "RenderingSequenceService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Scene::Sequence;
using namespace TEngine::Components::Graphics::Rendering::Models::Priority;

std::vector<std::shared_ptr<IRenderingStrategy>> RenderingSequenceService::generateSequence(
    std::shared_ptr<RenderingStrategies::IRenderingStrategy> root,
    const Graphics::Models::Vector3df &cameraPosition)
{
    std::vector<std::shared_ptr<RenderingStrategies::IRenderingStrategy>> sequence;
    _toPlainSequence(root, sequence);

    std::sort(
        sequence.begin(),
        sequence.end(),
        [&](const std::shared_ptr<RenderingStrategies::IRenderingStrategy> &a,
            const std::shared_ptr<RenderingStrategies::IRenderingStrategy> &b)
        {
            auto aDistance = a->getAbsolutePosition().distance(cameraPosition);
            auto bDistance = b->getAbsolutePosition().distance(cameraPosition);

            auto aPriority = a->getRenderingPriority();
            auto bPriority = b->getRenderingPriority();

            if (aPriority == bPriority)
            {
                return aDistance < bDistance;
            }

            return aPriority > bPriority;
        });

    return sequence;
}

void RenderingSequenceService::_toPlainSequence(std::shared_ptr<RenderingStrategies::IRenderingStrategy> root,
                                                std::vector<std::shared_ptr<RenderingStrategies::IRenderingStrategy>> &sequence)
{
    if (root->getRenderingPriority() != RenderingPriority::NONE)
    {
        sequence.push_back(root);
    }

    for (auto &child : root->getChildren())
    {
        _toPlainSequence(child, sequence);
    }
}