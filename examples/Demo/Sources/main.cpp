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

        auto graphicsParameters = creationParameters->getGraphicsParameters();
        graphicsParameters->setTitle("Demo");
        graphicsParameters->setIsVerticalSyncEnabled(true);

        engine->initialize(creationParameters);

        auto eventService = engine->getEventService();

        auto graphicsService = engine->getGraphicsService();
        auto sceneService = graphicsService->getSceneService();
        auto guiService = graphicsService->getGuiService();

        sceneService->setActiveCamera(TEngine::Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes::FPS);

        for (int i = 1; i < 32; i++)
        {
            for (int j = 1; j < 32; j++)
            {
                auto cube = sceneService->addMeshToRendering("./DemoResources/test plane/plane.obj");
                cube->setPosition(Vector3df(2.0f * i, 0.0f, 2.0f * j));
            }

            auto cube = sceneService->addToRendering(PrimitiveTypes::Cube, "./DemoResources/texture2.bmp");
            cube->setPosition(Vector3df(-3.0f * i, 0.0f, 0.0f));

            auto testCube = sceneService->addMeshToRendering("./DemoResources/test cube/cube.obj");
            testCube->setPosition(Vector3df(0.0f, 0.0f, 3.0f * i));

            auto sofa = sceneService->addMeshToRendering("./DemoResources/sofa.obj");
            sofa->setPosition(Vector3df(3.0f * i + 5.0f, 0.0f, 0.0f));
        }

        int framesCounter = 0;
        double previousCheckTime = graphicsService->getTime();

        auto audioService = engine->getAudioService();
        auto source = audioService->take("./DemoResources/birds.ogg");

        source->play();
        source->setPosition(0.0f, 0.0f, 0.0f);

        auto window1 = guiService->addWindow();
        auto image = guiService->addImage("./DemoResources/texture2.bmp");
        image->setSize(Vector2di(100, 100));
        window1->addChild(image);

        while (true)
        {
            auto time = graphicsService->getTime();
            if (time - previousCheckTime > 1.0)
            {
                std::cout << "FPS: " << framesCounter / 1 << std::endl;

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

        audioService->release(source);
    }

    return 0;
}