#include "IEngine.h"

#include "Components/Graphics/Models/PrimitiveTypes.h"
#include "Components/Graphics/Models/Vector3d.h"

using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Models;

int main()
{
    auto engine = TEngine::createEngine();

    auto creationParameters = TEngine::Models::createEngineParameters();

    creationParameters->getGraphicsParameters()->getRenderingParameters()->setTitle("Demo");
    creationParameters->getGraphicsParameters()->getRenderingParameters()->setWidth(1024);
    creationParameters->getGraphicsParameters()->getRenderingParameters()->setHeight(768);

    engine->initialize(creationParameters);

    auto graphicsService = engine->getGraphicsService();

    graphicsService->setActiveCamera(TEngine::Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes::BASE);

    auto cube = graphicsService->addPrimitive(PrimitiveTypes::Cube);

    auto cube2 = graphicsService->addPrimitive(PrimitiveTypes::Cube, cube);
    cube2->setPosition(Vector3df(3.0f, 0.0f, 0.0f));
    cube2->setRotation(Vector3df(0.0f, 3.14f/2.f, 0.0f));

    auto yRotation = .0f;
    auto rotation = Vector3df(0.0f, 0.0f, 0.0f);

    while (true)
    {
        yRotation += .01f;
        rotation.setY(yRotation);

        cube->setRotation(rotation);
        cube2->setRotation(rotation);

        engine->getGraphicsService()->render();
    }

    return 0;
}