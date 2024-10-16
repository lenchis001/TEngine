#ifdef __APPLE__

#include "GraphicsServiceBase.h"

namespace TEngine::Components::Graphics
{
    class CocoaGraphicsService : public GraphicsServiceBase
    {
    public:
        CocoaGraphicsService(
            std::shared_ptr<ISceneService> sceneService,
            std::shared_ptr<IGuiService> guiService,
            std::shared_ptr<IMeshLoadingService> meshLoadingService,
            std::shared_ptr<ITexturesService> texturesService,
            void *parent);
        ~CocoaGraphicsService() override;

        void initialize(std::shared_ptr<IGraphicsParameters> parameters) override;

        void deinitialize() override;

        bool isShutdownRequested() const override;

        double getTime() const override;

        void render() override;

        void resize(int width, int height) override;

    private:
        void *_parent;

        void *_openGlContext;
        void *_openGlView;
    };
}

#endif // __APPLE__