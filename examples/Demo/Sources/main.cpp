#include "IEngine.h"

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <thread>

#include "Components/Graphics/Models/Vector3d.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::Models::Physics;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;
using namespace TEngine::Components::Graphics::Rendering::Scene;
using namespace TEngine::Components::Network::Http;
using namespace TEngine::Components::Network::WebSocket;
using namespace TEngine::Components::Network::WebSocket::Client;

void setupScene(std::shared_ptr<ISceneService> sceneService)
{
    sceneService->setActiveCamera(BuildinCameraTypes::FPS);
    
    sceneService->addMesh("./DemoResources/glb_test/model.glb")->setPosition(Vector3df(1.0f, 1.0f, 1.0f));
    sceneService->addMesh("./DemoResources/test cube/cube.obj")->setPosition(Vector3df(5.0f, 1.0f, 1.0f));

    auto sidesTextures = std::vector<std::string>
    {
        "./DemoResources/skybox/right.bmp",
        "./DemoResources/skybox/left.bmp",
        "./DemoResources/skybox/top.bmp",
        "./DemoResources/skybox/bottom.bmp",
        "./DemoResources/skybox/front.bmp",
        "./DemoResources/skybox/back.bmp"
    };
    sceneService->addSkyCude(sidesTextures);

    return;

    auto solid = sceneService->addSolidbox();
    solid->setPosition(Vector3df(5.0f, -10.0f, 0.0f));
    solid->setRotation(Vector3df(.0f, .0f, .1f));
    solid->setScale(Vector3df(35.0f, 1.0f, 15.0f));
    solid->setIsVisualizationEnabled(true);

    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 32; j++)
        {
            auto cube = sceneService->addMesh("./DemoResources/test plane/plane.obj");
            cube->setPosition(Vector3df(2.0f * i, 0.0f, 2.0f * j));
        }

        if (i > 5)
        {
            auto cube = sceneService->addCube("./DemoResources/texture2.bmp", nullptr, PhysicsFlags::STATIC);
            cube->setPosition(Vector3df(i, 0.0f, 0.0f));
        }

        auto cube2 = sceneService->addCube("./DemoResources/texture2.bmp", nullptr, PhysicsFlags::DYNAMIC);
        cube2->setPosition(Vector3df(i, 2.f * i, 0.0f));

        auto testCube = sceneService->addMesh("./DemoResources/test cube/cube.obj");
        testCube->setPosition(Vector3df(0.0f, 0.0f, 3.0f * i));

        auto sofa = sceneService->addMesh("./DemoResources/sofa.obj");
        sofa->setPosition(Vector3df(0.f, 0.f, -3.0f * i - 5.0f));
    }
}

void sendTestRequest(std::shared_ptr<INetworkService> networkService)
{
    // auto request = TEngine::Components::Network::Http::Models::Request(
    //     "http://www.example.com",
    //     "",
    //     TEngine::Components::Network::Http::Models::Methods::GET,
    //     {});
    // auto response = networkService->send(request);

    // std::cout << "Status: " << response.getStatus() << std::endl;
    // std::cout << "Body: " << response.getBody() << std::endl;
}

void testWs(std::shared_ptr<IWebSocketFactory> webSocketFactory)
{
    // auto client = webSocketFactory->createClient();
    // client->connect("ws://localhost:8080", {}).wait();
    // client->setOnMessageCallback([](const std::string &message) {
    //     std::cout << "Message: " << message << std::endl;
    // });
    // client->send("Hello");

    // std::this_thread::sleep_for(std::chrono::seconds(3));

    // client->close();
}

int main()
{
    auto engine = TEngine::createEngine();

    auto creationParameters = TEngine::Models::createEngineParameters();

    auto graphicsParameters = creationParameters->getGraphicsParameters();
    graphicsParameters->setTitle("Demo");
    graphicsParameters->setIsVerticalSyncEnabled(false);
    graphicsParameters->getSceneParameters()->setSequenceUpdateThreshold(20.f);

    engine->initialize(creationParameters);

    auto graphicsService = engine->getGraphicsService();
    auto sceneService = graphicsService->getSceneService();
    setupScene(sceneService);

    auto networkService = engine->getNetworkService();
    sendTestRequest(networkService);

    auto webSocketFactory = engine->getWebSocketFactory();
    testWs(webSocketFactory);

    double previousCheckTime = graphicsService->getTime();
    int fpsCounter = 0;

    auto audioService = engine->getAudioService();
    auto source = audioService->take("./DemoResources/birds.ogg");

    source->play();
    source->setPosition(0.0f, 0.0f, 0.0f);

    auto coreService = engine->getCoreService();

    while (true)
    {
        auto time = graphicsService->getTime();
        auto diff = time - previousCheckTime;
        fpsCounter++;
        if (diff >= 1.0)
        {
            std::cout << "FPS: " << fpsCounter << std::endl;

            fpsCounter = 0;
            previousCheckTime = time;

            if (graphicsService->isShutdownRequested())
            {
                break;
            }
        }

        //coreService->processQueue(TEngine::Components::Core::Models::ThreadType::RENDERING);

        graphicsService->render();
    }

    audioService->release(source);
    engine->deinitialize();

    return 0;
}