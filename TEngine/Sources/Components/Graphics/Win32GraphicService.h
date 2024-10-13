#ifdef _WIN32

#ifndef TENGINE_WIN32GRAPHICCONTEXT_H
#define TENGINE_WIN32GRAPHICCONTEXT_H

#include <windows.h>

#include "GraphicsServiceBase.h"

typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);

namespace TEngine::Components::Graphics::Services
{
    class Win32GraphicService : public GraphicsServiceBase
    {
    public:
        Win32GraphicService(
            std::shared_ptr<ISceneService> sceneService,
            std::shared_ptr<IGuiService> guiService,
            std::shared_ptr<IMeshLoadingService> meshLoadingService,
            std::shared_ptr<ITexturesService> texturesService,
            HWND parent);

        ~Win32GraphicService();

        void initialize(std::shared_ptr<IGraphicsParameters> parameters) override;

        void deinitialize() override;

        bool isShutdownRequested() const override;

        double getTime() const override;

        void render() override;

        private:
            HWND _parent;
            HGLRC _hglrc;
            HDC _hdc;
    };
}

#endif // TENGINE_WIN32GRAPHICCONTEXT_H

#endif // _WIN32