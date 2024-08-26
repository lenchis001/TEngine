#include "GL/glew.h"

#include "algorithm"

#include "BigWorldService.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Optimization;

#define HIGH_PRIORITY 0
#define MEDIUM_PRIORITY 1
#define LOW_PRIORITY 2
#define VERY_LOW_PRIORITY 3

#define IS_PRIORITY_HIGHER_THAN(priority, minimalPriority) priority < minimalPriority

BigWorldService::BigWorldService() : _occlusionQueryResult(0),
                                     _visibilityTreshold(0),
                                     _framesToSkip(0),
                                     _frameNumber(0),
                                     _targetIndex(0),
                                     _occlusionQueryId(0)
{
}

void BigWorldService::initialize(std::shared_ptr<IBigWorldParameters> parameters)
{
    _visibilityTreshold = parameters->getVisibilityTreshold();

    _framesToSkip = 60 / parameters->getTrakingFrequency();
    if (!_framesToSkip)
    {
        _framesToSkip = 1;
    }

    _queriesAmount = parameters->getQueriesAmount();

    glGenQueriesARB(1, &_occlusionQueryId);
}

int frameCounter = 0;
int itemsRendered = 0;

void BigWorldService::render(
    const std::vector<std::shared_ptr<Components::Graphics::Rendering::Services::RenderingStrategies::IRenderingStrategy>> strategies,
    const Components::Graphics::Models::Matrix4x4f &vpMatrix)
{
    auto isOcclusionTestRequiredForFrame = !(_frameNumber % _framesToSkip);
    if (isOcclusionTestRequiredForFrame)
    {
        _targetIndex--;

        if (_targetIndex < 0 || _targetIndex >= strategies.size())
        {
            _targetIndex = strategies.size() - 1;
        }
    }

    std::size_t index = 0;

    for (const auto &strategy : strategies)
    {
        auto isOcclusionTestRequiredForTarget = index == _targetIndex;
        auto isOcclusionTestRequired = isOcclusionTestRequiredForFrame && isOcclusionTestRequiredForTarget;
        auto &currentPriority = priorityMap[strategy.get()];

        if (isOcclusionTestRequired)
        {
            glBeginQueryARB(GL_SAMPLES_PASSED, _occlusionQueryId);
        }

        if (isOcclusionTestRequired || IS_PRIORITY_HIGHER_THAN(currentPriority, MEDIUM_PRIORITY))
        {
            strategy->render(vpMatrix);
            itemsRendered++;
        }

        if (isOcclusionTestRequired)
        {
            glEndQueryARB(GL_SAMPLES_PASSED_ARB);
            glGetQueryObjectuivARB(_occlusionQueryId, GL_QUERY_RESULT_ARB, &_occlusionQueryResult);

            currentPriority = std::clamp(currentPriority + (_occlusionQueryResult > _visibilityTreshold ? -1 : 1), HIGH_PRIORITY, VERY_LOW_PRIORITY);
        }
    }

    frameCounter++;
    if (frameCounter == 200)
    {
        std::cout << "Items rendered: " << itemsRendered / frameCounter << std::endl;

        frameCounter = 0;
        itemsRendered = 0;
    }
}