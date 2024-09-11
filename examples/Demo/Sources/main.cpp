#include "IEngine.h"

#include "iostream"
#include "memory"
#include "vector"

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

        auto eventService = engine->getEventService();

        auto graphicsService = engine->getGraphicsService();

        graphicsService->setActiveCamera(TEngine::Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes::FPS);

        auto cube = graphicsService->addPrimitive(PrimitiveTypes::Cube, "./DemoResources/texture2.bmp");

        for (int i = 0; i < 128; i++)
        {
            auto sofa = graphicsService->addMesh("./DemoResources/sofa.obj");
            sofa->setPosition(Vector3df(3.0f * i + 5.0f, 0.0f, 0.0f));
        }

        auto rotation = Vector3df(0.0f, 0.0f, 0.0f);

        int framesCounter = 0;
        double previousCheckTime = graphicsService->getTime();

        while (true)
        {
            auto time = graphicsService->getTime();
            if (time - previousCheckTime > 5.0)
            {
                std::cout << "FPS: " << framesCounter / 5 << std::endl;

                framesCounter = 0;
                previousCheckTime = time;

                if (graphicsService->isShutdownRequested())
                {
                    break;
                }
            }

            graphicsService->render();

            framesCounter++;
        }
    }

    return 0;
}