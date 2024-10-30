#include "IEngine.h"

#include "iostream"
#include "memory"
#include "vector"
#include "fstream"

#include "Components/Graphics/Models/Vector3d.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Physics;

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

        sceneService->setActiveCamera(TEngine::Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes::BASE);

        auto solid = sceneService->addSolidbox();
        solid->setPosition(Vector3df(0.0f, -5.0f, 0.0f));
        solid->setRotation(Vector3df(.0f, .0f, .5f));
        solid->setScale(Vector3df(15.0f, 1.0f, 15.0f));

        for (int i = 1; i < 32; i++)
        {
            for (int j = 1; j < 32; j++)
            {
                auto cube = sceneService->addMesh("./DemoResources/test plane/plane.obj");
                cube->setPosition(Vector3df(2.0f * i, 0.0f, 2.0f * j));
            }

            auto cube3 = sceneService->addPrimitive(PrimitiveTypes::Cube, "./DemoResources/texture2.bmp", nullptr, PhysicsFlags::DYNAMIC);
            cube3->setPosition(Vector3df(2.0f * i, 4.f * i, i * 2.0f));

            auto cube = sceneService->addPrimitive(PrimitiveTypes::Cube, "./DemoResources/texture2.bmp", nullptr, PhysicsFlags::STATIC);
            cube->setPosition(Vector3df(-3.0f * i, 0.0f, 0.0f));

            auto cube2 = sceneService->addPrimitive(PrimitiveTypes::Cube, "./DemoResources/texture2.bmp", nullptr, PhysicsFlags::DYNAMIC);
            cube2->setPosition(Vector3df(-3.0f * i, 4.f * i, 0.0f));

            auto testCube = sceneService->addMesh("./DemoResources/test cube/cube.obj");
            testCube->setPosition(Vector3df(0.0f, 0.0f, 3.0f * i));

            auto sofa = sceneService->addMesh("./DemoResources/sofa.obj");
            sofa->setPosition(Vector3df(3.0f * i + 5.0f, 0.0f, 0.0f));
        }

        int framesCounter = 0;
        double previousCheckTime = graphicsService->getTime();

        auto audioService = engine->getAudioService();
        auto source = audioService->take("./DemoResources/birds.ogg");

        source->play();
        source->setPosition(0.0f, 0.0f, 0.0f);

        auto window1 = guiService->addWindow();
        window1->setSize(Vector2di(100, 100));

        auto image = guiService->addImage("./DemoResources/texture2.bmp");
        image->setSize(Vector2di(400, 100));
        window1->addChild(image);

        auto input1 = guiService->addInput();
        input1->setSize(Vector2di(400, 100));
        window1->addChild(input1);

        while (true)
        {
            auto time = graphicsService->getTime();
            if (time - previousCheckTime > 1.0)
            {
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
        engine->deinitialize();
    }

    return 0;
}