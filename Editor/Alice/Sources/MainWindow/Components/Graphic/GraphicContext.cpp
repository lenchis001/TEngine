#include "GraphicContext.h"

using namespace Alice::MainWindow::Components::Graphic;

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Physics;

GraphicContext::GraphicContext(wxWindow *parent)
    : IGraphicContext(parent), _isShutdownRequested(false)
{
    SetBackgroundColour(wxColour(128, 0, 0));
}

GraphicContext::~GraphicContext()
{
    if (_renderThread.joinable())
    {
        addFunction(
            [this]()
            {
                _isShutdownRequested = true;
            });

        _renderThread.join();
    }
}

void GraphicContext::OnResize(wxSizeEvent &event)
{
    if (!_renderThread.joinable())
    {
        _renderThread = std::thread(std::bind(&GraphicContext::_initializeEngine, this));
    }

    auto size = event.GetSize();

    addFunction(
        [this, size]()
        {
            auto graphicsService = _engine->getGraphicsService();

            graphicsService->resize(size.GetWidth(), size.GetHeight());
        });
}

void GraphicContext::OnCreateScene(CreateSceneEvent &event)
{
    _currentScenePath.clear();

    addFunction(
        [&]()
        {
            auto graphicsService = _engine->getGraphicsService();
            graphicsService->getSceneService()->getRoot()->removeAllChildren();
        });
}

void GraphicContext::OnSaveScene(SaveSceneEvent &event)
{
    auto location = _currentScenePath.empty() ? showSaveSceneDialog() : _currentScenePath;

    if (!location.empty())
    {
        _currentScenePath = location;

        addFunction(
            [&]()
            {
                auto serializationService = _engine->getSerializationService();
                auto graphicsService = _engine->getGraphicsService();

                auto sceneRoot = graphicsService->getSceneService()->getRoot();

                serializationService->serializeToFile(sceneRoot, _currentScenePath);
            });
    }
}

void GraphicContext::OnSaveSceneAs(SaveSceneAsEvent &event)
{
    auto location = event.getPath();

    _currentScenePath = location;

    addFunction(
        [&]()
        {
            auto serializationService = _engine->getSerializationService();
            auto graphicsService = _engine->getGraphicsService();

            auto sceneRoot = graphicsService->getSceneService()->getRoot();

            serializationService->serializeToFile(sceneRoot, _currentScenePath);
        });
}

void GraphicContext::OnOpenScene(OpenSceneEvent &event)
{
    auto location = event.getPath();

    _currentScenePath = location;

    addFunction(
        [&]()
        {
            auto deserializationService = _engine->getDeserializationService();
            auto graphicsService = _engine->getGraphicsService();

            auto sceneRoot = graphicsService->getSceneService()->getRoot();

            deserializationService->deserializeFromFile(_currentScenePath, sceneRoot);
        });
}

void GraphicContext::_initializeEngine()
{
#ifdef _WIN32
    _engine = TEngine::createEngine((HWND)GetHWND());
#elif __APPLE__
    _engine = TEngine::createEngine((void *)GetHandle());
#endif

    auto creationParameters = TEngine::Models::createEngineParameters();
    _engine->initialize(creationParameters);

    auto graphicsService = _engine->getGraphicsService();

    graphicsService->getGuiService()->addWindow();

    auto sceneService = graphicsService->getSceneService();
    sceneService->setActiveCamera(TEngine::Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes::BASE);

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

    while (!_isShutdownRequested)
    {
        this->executeFunctions();

        graphicsService->render();
    }

    _engine->deinitialize();

    sceneService = nullptr;
    _engine = nullptr;
}

wxBEGIN_EVENT_TABLE(GraphicContext, wxPanel)
    EVT_SIZE(GraphicContext::OnResize)
        EVT_CREATE_SCENE(GraphicContext::OnCreateScene)
            EVT_SAVE_SCENE(GraphicContext::OnSaveScene)
                EVT_SAVE_SCENE_AS(GraphicContext::OnSaveSceneAs)
                    EVT_OPEN_SCENE(GraphicContext::OnOpenScene)
                        wxEND_EVENT_TABLE()