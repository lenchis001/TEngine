#ifdef __ANDROID__

#include "Components/Graphics/PlatformWrapping/GlWrapper.h"

#include "Components/Graphics/GraphicsServiceBase.h"

struct android_app;

namespace TEngine::Components::Graphics
{
    class AndroidGraphicsService : public GraphicsServiceBase
    {
    public:
        AndroidGraphicsService(
            std::shared_ptr<ISceneService> sceneService,
            std::shared_ptr<IGuiService> guiService,
            std::shared_ptr<IMeshLoadingService> meshLoadingService,
            std::shared_ptr<ITexturesService> texturesService,
            android_app *pApp);

        void initialize(std::shared_ptr<IGraphicsParameters> parameters) override;

        void deinitialize() override;

        bool isShutdownRequested() const override;

        double getTime() const override;

        void render() override;

    private:
        android_app *app_;
        EGLDisplay display_;
        EGLSurface surface_;
        EGLContext context_;
        EGLint width_;
        EGLint height_;
    };
}

#endif // __ANDROID__