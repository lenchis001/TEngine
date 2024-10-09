#include "GraphicContext.h"

using namespace Alice::MainWindow::Components;

#ifdef _WIN32
void closeWindow(HWND windowHandler)
{
    PostMessage(windowHandler, WM_CLOSE, 0, 0);
}

void resizeByParent(HWND child, HWND parent)
{
    RECT parentRect;
    GetClientRect(parent, &parentRect);
    SetWindowPos(child, nullptr, 0, 0, parentRect.right - parentRect.left, parentRect.bottom - parentRect.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

// This function cannot be a part of GraphicContext because of a conflict with the wxWidgets library
// (wxWidgets has a class level "SetParent" function with the same name)
void setWin32Parent(HWND child, HWND parent)
{
    // Remove window borders
    LONG style = GetWindowLong(child, GWL_STYLE);
    style &= ~(WS_OVERLAPPEDWINDOW); // Remove all borders and title bar
    SetWindowLong(child, GWL_STYLE, style);

    // Set the parent window
    SetParent(child, parent);

    // Adjust the size of the GLFW window to match the parent window
    resizeByParent(child, parent);
}
#endif // _WIN32

GraphicContext::GraphicContext(wxWindow *parent)
    : IGraphicContext(parent)
{
    _engine = TEngine::createEngine();

    SetBackgroundColour(wxColour(128, 0, 0));
}

GraphicContext::~GraphicContext()
{
    if (_renderThread.joinable())
    {
        addFunction([this]()
                    {
#ifdef _WIN32
                        auto windowHandler = _engine->getGraphicsService()->getWindowHandler();
                        closeWindow(windowHandler);
#endif // _WIN32        
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

    addFunction([this]()
                {
#ifdef _WIN32
                    auto windowHandler = _engine->getGraphicsService()->getWindowHandler();
                    resizeByParent(windowHandler, (HWND)GetHWND());
#endif // _WIN32
                });
}

void GraphicContext::_initializeEngine()
{
    auto creationParameters = TEngine::Models::createEngineParameters();
    _engine->initialize(creationParameters);

#ifdef _WIN32
    auto windowHandler = _engine->getGraphicsService()->getWindowHandler();

    setWin32Parent(windowHandler, (HWND)GetHWND());
    ShowWindow(windowHandler, SW_SHOW);
#endif // _WIN32

    auto graphicsService = _engine->getGraphicsService();

    graphicsService->getGuiService()->addWindow();

    while (!graphicsService->isShutdownRequested())
    {
        this->executeFunctions();

        graphicsService->render();
    }

    _engine->deinitialize();

    _engine = nullptr;
}

wxBEGIN_EVENT_TABLE(GraphicContext, wxPanel)
    EVT_SIZE(GraphicContext::OnResize)
        wxEND_EVENT_TABLE()