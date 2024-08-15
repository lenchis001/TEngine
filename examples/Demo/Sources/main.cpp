#include "IEngine.h"

#include "Components/Graphics/Models/PrimitiveTypes.h"

using namespace TEngine::Components::Graphics::MeshLoading::Models;

int main() {
    auto engine = TEngine::createEngine();

    auto creationParameters = TEngine::Models::createEngineParameters();

    creationParameters->getGraphicsParameters()->getRenderingParameters()->setTitle("Demo");

    engine->initialize(creationParameters);

    auto graphicsService = engine->getGraphicsService();


    graphicsService->setActiveCamera(TEngine::Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes::BASE);
    auto cube = graphicsService->addPrimitive(PrimitiveTypes::Cube);

    while (true)
    {
        engine->getGraphicsService()->render();
    }
    
    return 0;
}