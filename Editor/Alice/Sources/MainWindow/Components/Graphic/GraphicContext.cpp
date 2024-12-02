#include "GraphicContext.h"

#include "Events/SceneTree/UpdateSceneTreeEvent.h"

using namespace Alice::MainWindow::Components::Graphic;

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Physics;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;

using namespace Alice::MainWindow::Components::Graphic::Events::SceneTreeView;

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

void GraphicContext::_onResize(wxSizeEvent &event)
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

    event.Skip();
}

void GraphicContext::_onCreateScene(CreateSceneEvent &event)
{
    _currentScenePath.clear();

    addFunction(
        [&]()
        {
            auto graphicsService = _engine->getGraphicsService();
            graphicsService->getSceneService()->getRoot()->removeAllChildren();

            UpdateSceneTreeEvent event;

            queueEventToChildren(event);
        });
}

void GraphicContext::_onSaveScene(SaveSceneEvent &event)
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

void GraphicContext::_onSaveSceneAs(SaveSceneAsEvent &event)
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

void GraphicContext::_onOpenScene(OpenSceneEvent &event)
{
    _currentScenePath = event.getPath();

    addFunction(
        [&]()
        {
            auto deserializationService = _engine->getDeserializationService();
            auto graphicsService = _engine->getGraphicsService();

            auto sceneRoot = graphicsService->getSceneService()->getRoot();

            sceneRoot->removeAllChildren();

            deserializationService->deserializeFromFile(_currentScenePath, sceneRoot);

            auto event = UpdateSceneTreeEvent::fromRenderingStrategy(sceneRoot);
            queueEventToChildren(event);
        });
}

void GraphicContext::_onAddMesh(AddMeshEvent &event)
{
    auto meshPath = event.getPath();

    addFunction(
        [&, meshPath]()
        {
            auto graphicsService = _engine->getGraphicsService();
            auto sceneService = graphicsService->getSceneService();

            sceneService->addMesh(meshPath);

            auto sceneRoot = graphicsService->getSceneService()->getRoot();
            auto event = UpdateSceneTreeEvent::fromRenderingStrategy(sceneRoot);
            queueEventToChildren(event);
        });
}

void GraphicContext::_onAddCube(AddCubeEvent &event)
{
    addFunction(
        [&]()
        {
            auto graphicsService = _engine->getGraphicsService();
            auto sceneService = graphicsService->getSceneService();

            auto cube = sceneService->addCube();

            auto sceneRoot = graphicsService->getSceneService()->getRoot();
            auto event = UpdateSceneTreeEvent::fromRenderingStrategy(sceneRoot);
            queueEventToChildren(event);
        });
}

void GraphicContext::_onMouseMove(wxMouseEvent &event)
{
    auto position = event.GetPosition();

    addFunction(
        [&, position]()
        {
            auto eventService = _engine->getEventService();

            eventService->fireCursorMoveHandler(position.x, position.y);
        });
}

void GraphicContext::_onMouseButton(wxMouseEvent &event)
{
    auto targetButton = event.GetButton();
    auto isPressed = event.ButtonIsDown(static_cast<wxMouseButton>(targetButton));

    auto tengineButton = _toTEngineMouseButton(targetButton);
    auto tengineAction = isPressed ? KeyStates::PRESS : KeyStates::RELEASE;

    addFunction(
        [&, tengineButton, tengineAction]()
        {
            auto eventService = _engine->getEventService();

            eventService->fireMouseButtonHandler(tengineButton, tengineAction, 0);
        });
}

void GraphicContext::_onKey(wxKeyEvent &event)
{
    auto keyCode = event.GetKeyCode();
    auto isPressed = event.GetEventType() == wxEVT_KEY_DOWN;

    auto tengineKey = _toTEngineKey(keyCode);
    auto tengineAction = isPressed ? KeyStates::PRESS : KeyStates::RELEASE;

    addFunction(
        [&, keyCode, tengineAction]()
        {
            auto eventService = _engine->getEventService();

            eventService->fireKeyHandler(tengineKey, 0, tengineAction, 0);
        });
}

void GraphicContext::_initializeEngine()
{
    _engine = TEngine::createEngine(
#ifdef _WIN32
        (HWND)GetHWND()
#elif __APPLE__
        (void *)GetHandle()
#endif
            ,
        false);

    auto creationParameters = TEngine::Models::createEngineParameters();

    _engine->initialize(creationParameters);

    auto graphicsService = _engine->getGraphicsService();

    graphicsService->getSceneService()->setActiveCamera(BuildinCameraTypes::VIEWER);

    while (!_isShutdownRequested)
    {
        this->executeFunctions();

        graphicsService->render();
    }

    _engine->deinitialize();

    _engine = nullptr;
}

MouseButtons GraphicContext::_toTEngineMouseButton(int wxButtonId)
{
    switch (wxButtonId)
    {
    case wxMOUSE_BTN_LEFT:
        return MouseButtons::BUTTON_LEFT;
    case wxMOUSE_BTN_RIGHT:
        return MouseButtons::BUTTON_RIGHT;
    case wxMOUSE_BTN_MIDDLE:
        return MouseButtons::BUTTON_MIDDLE;
    default:
        return MouseButtons::BUTTON_UNKNOWN;
    }
}

KeyboardKeys GraphicContext::_toTEngineKey(int wxKeyCode)
{
    switch (wxKeyCode)
    {
    case WXK_RETURN:
        return KeyboardKeys::KEY_ENTER;
    case WXK_TAB:
        return KeyboardKeys::KEY_TAB;
    case WXK_ESCAPE:
        return KeyboardKeys::KEY_ESCAPE;
    case WXK_BACK:
        return KeyboardKeys::KEY_BACKSPACE;
    case WXK_DELETE:
        return KeyboardKeys::KEY_DELETE;
    case WXK_UP:
        return KeyboardKeys::KEY_UP;
    case WXK_DOWN:
        return KeyboardKeys::KEY_DOWN;
    case WXK_LEFT:
        return KeyboardKeys::KEY_LEFT;
    case WXK_RIGHT:
        return KeyboardKeys::KEY_RIGHT;
    case WXK_SHIFT:
        return KeyboardKeys::KEY_LEFT_SHIFT;
    default:
        return static_cast<KeyboardKeys>(wxKeyCode);
    }
}

wxBEGIN_EVENT_TABLE(GraphicContext, wxPanel)
    EVT_SIZE(GraphicContext::_onResize)
        EVT_CREATE_SCENE(GraphicContext::_onCreateScene)
            EVT_SAVE_SCENE(GraphicContext::_onSaveScene)
                EVT_SAVE_SCENE_AS(GraphicContext::_onSaveSceneAs)
                    EVT_OPEN_SCENE(GraphicContext::_onOpenScene)
                        EVT_MOTION(GraphicContext::_onMouseMove)
                            EVT_ADD_MESH(GraphicContext::_onAddMesh)
                                EVT_ADD_CUBE(GraphicContext::_onAddCube)
                                    EVT_LEFT_DOWN(GraphicContext::_onMouseButton)
                                        EVT_LEFT_UP(GraphicContext::_onMouseButton)
                                            EVT_RIGHT_DOWN(GraphicContext::_onMouseButton)
                                                EVT_RIGHT_UP(GraphicContext::_onMouseButton)
                                                    EVT_MIDDLE_DOWN(GraphicContext::_onMouseButton)
                                                        EVT_MIDDLE_UP(GraphicContext::_onMouseButton)
                                                            EVT_KEY_DOWN(GraphicContext::_onKey)
                                                                EVT_KEY_UP(GraphicContext::_onKey)
                                                                    wxEND_EVENT_TABLE()