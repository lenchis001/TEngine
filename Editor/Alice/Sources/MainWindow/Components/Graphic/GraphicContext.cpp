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

    auto sceneService = graphicsService->getSceneService();
    sceneService->setActiveCamera(TEngine::Components::Graphics::Rendering::Models::Cameras::BuildinCameraTypes::BASE);

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