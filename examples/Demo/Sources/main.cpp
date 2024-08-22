#include "IEngine.h"

#include "iostream"

#include "Components/Graphics/Models/PrimitiveTypes.h"
#include "Components/Graphics/Models/Vector3d.h"

using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Models;

int main()
{
    {
        auto engine = TEngine::createEngine();

        auto creationParameters = TEngine::Models::createEngineParameters();

        auto renderingParameters = creationParameters->getGraphicsParameters()->getRenderingParameters();
        renderingParameters->setTitle("Demo");
        renderingParameters->setWidth(1024);
        renderingParameters->setHeight(768);
        renderingParameters->setIsVerticalSyncEnabled(true);

        engine->initialize(creationParameters);

        auto graphicsService = engine->getGraphicsService();

        graphicsService->setActiveCamera(TEngine::Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes::BASE);

        auto cube = graphicsService->addPrimitive(PrimitiveTypes::Cube, "./uvtemplate.bmp");

        auto cube2 = graphicsService->addPrimitive(PrimitiveTypes::Cube, "./uvtemplate.bmp", cube);
        cube2->setPosition(Vector3df(3.0f, 0.0f, 0.0f));
        cube2->setRotation(Vector3df(0.0f, 3.14f / 2.f, 0.0f));

        auto rotation = Vector3df(0.0f, 0.0f, 0.0f);

        int framesCounter = 0;
        double previousCheckTime = graphicsService->getTime();

        while (true)
        {
            auto time = graphicsService->getTime();
            if (time - previousCheckTime > 1.0)
            {
                std::cout << "FPS: " << framesCounter << std::endl;

                framesCounter = 0;
                previousCheckTime = time;
            }

            rotation.setY(time);

            cube->setRotation(rotation);
            cube2->setRotation(rotation);

            engine->getGraphicsService()->render();

            framesCounter++;
        }
    }

    return 0;
}