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
        renderingParameters->setIsVerticalSyncEnabled(false);
        renderingParameters->getBigWorldParameters()->setEnabled(true);
        renderingParameters->getBigWorldParameters()->setQueriesAmount(2);
        renderingParameters->getBigWorldParameters()->setTrakingFrequency(60);
        renderingParameters->getBigWorldParameters()->setVisibilityTreshold(256000);

        engine->initialize(creationParameters);

        auto graphicsService = engine->getGraphicsService();

        graphicsService->setActiveCamera(TEngine::Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes::BASE);

        auto cube = graphicsService->addPrimitive(PrimitiveTypes::Cube, "./DemoResources/texture2.bmp");

        std::vector<std::shared_ptr<TEngine::Components::Graphics::Rendering::Models::RenderableObjects::IRenderableObject>> cubes;

        for (int i = 0; i < 8192; i++)
        {
            auto cube2 = graphicsService->addPrimitive(PrimitiveTypes::Cube, "./DemoResources/texture1.bmp", cube);
            cube2->setPosition(Vector3df(0.0f, 0.0f, i * 4.0f + 4.0f));
            cubes.push_back(cube2);
        }

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

                if (graphicsService->isShutdownRequested())
                {
                    break;
                }
            }

            rotation.setY(time);
            cube->setRotation(rotation);
            for (auto &cube : cubes)
            {
                cube->setRotation(rotation);
            }

            engine->getGraphicsService()->render();

            framesCounter++;
        }
    }

    return 0;
}