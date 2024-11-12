#ifdef _WIN32

#include "GL/glew.h"

#include "Win32GraphicService.h"

using namespace TEngine::Components::Graphics;

Win32GraphicService::Win32GraphicService(
    std::shared_ptr<ISceneService> sceneService,
    std::shared_ptr<IGuiService> guiService,
    std::shared_ptr<IMeshLoadingService> meshLoadingService,
    std::shared_ptr<ITexturesService> texturesService,
    HWND parent)
    : GraphicsServiceBase(sceneService, guiService, meshLoadingService, texturesService), _parent(parent)
{
}

Win32GraphicService::~Win32GraphicService()
{
}

void Win32GraphicService::initialize(std::shared_ptr<IGraphicsParameters> parameters)
{
    _hdc = GetDC(_parent);
    if (!_hdc)
    {
        throw std::runtime_error("Failed to get device context");
    }

    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR), // Size of this pfd
        3,                             // Version number
        PFD_DRAW_TO_WINDOW |           // Support window
            PFD_SUPPORT_OPENGL |       // Support OpenGL
            PFD_DOUBLEBUFFER,          // Double buffered
        PFD_TYPE_RGBA,                 // RGBA type
        24,                            // 24-bit color depth
        0, 0, 0, 0, 0, 0,              // Color bits ignored
        0,                             // No alpha buffer
        0,                             // Shift bit ignored
        0,                             // No accumulation buffer
        0, 0, 0, 0,                    // Accum bits ignored
        32,                            // 32-bit z-buffer
        0,                             // No stencil buffer
        0,                             // No auxiliary buffer
        PFD_MAIN_PLANE,                // Main layer
        0,                             // Reserved
        0, 0, 0                        // Layer masks ignored
    };

    int pixelFormat = ChoosePixelFormat(_hdc, &pfd);
    if (pixelFormat == 0)
    {
        ReleaseDC(_parent, _hdc);
        throw std::runtime_error("Failed to choose pixel format");
    }

    if (!SetPixelFormat(_hdc, pixelFormat, &pfd))
    {
        ReleaseDC(_parent, _hdc);

        throw std::runtime_error("Failed to set pixel format");
    }

    _hglrc = wglCreateContext(_hdc);
    if (!_hglrc)
    {
        ReleaseDC(_parent, _hdc);

        throw std::runtime_error("Failed to create OpenGL context");
    }

    if (!wglMakeCurrent(_hdc, _hglrc))
    {
        wglDeleteContext(_hglrc);
        ReleaseDC(_parent, _hdc);

        throw std::runtime_error("Failed to make OpenGL context current");
    }

    if (parameters->getIsVerticalSyncEnabled())
    {
        auto wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

        if (wglSwapIntervalEXT == nullptr)
        {
            throw std::runtime_error("Failed to load wglSwapIntervalEXT");
        }

        // Enable VSync
        auto result = wglSwapIntervalEXT(1);

        if (result == FALSE)
        {
            throw std::runtime_error("Failed to enable VSync");
        }
    }

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    GraphicsServiceBase::initialize(parameters);
}

void Win32GraphicService::deinitialize()
{
    GraphicsServiceBase::deinitialize();

    ReleaseDC(_parent, _hdc);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(_hglrc);
}

bool Win32GraphicService::isShutdownRequested() const
{
    return false;
}

double Win32GraphicService::getTime() const
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER currentTime;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&currentTime);

    return static_cast<double>(currentTime.QuadPart) / frequency.QuadPart;
}

void Win32GraphicService::render()
{
    GraphicsServiceBase::render();

    SwapBuffers(_hdc);
}

#endif // _WIN32