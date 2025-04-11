#ifdef __ANDROID__

#include <EGL/egl.h>

#include <android_native_app_glue.h>

namespace TEngine::Components::Graphics
{
    class AndroidGraphicsService : public GraphicsServiceBase
    {
    public:
        AndroidGraphicsService(android_app *pApp);

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