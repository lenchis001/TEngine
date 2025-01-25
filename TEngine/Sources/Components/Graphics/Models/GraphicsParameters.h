#ifndef TENGINE_GRAPHICSPARAMETERS_H
#define TENGINE_GRAPHICSPARAMETERS_H

#include "IGraphicsParameters.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Models;

namespace TEngine::Components::Graphics::Models
{
    class GraphicsParameters : public IGraphicsParameters
    {
    public:
        GraphicsParameters();

        int getWidth() const override;

        void setWidth(int width) override;

        int getHeight() const override;

        void setHeight(int height) override;

        int getOpenGlMajorVersion() const override;

        void setOpenGlMinorVersion(int openGlMinorVersion) override;

        int getOpenGlMinorVersion() const override;

        void setOpenGlMajorVersion(int openGlMajorVersion) override;

        const std::string &getTitle() const override;

        void setTitle(const std::string &title) override;

        bool getIsVerticalSyncEnabled() const override;

        void setIsVerticalSyncEnabled(bool value) override;

        std::shared_ptr<ISceneParameters> getSceneParameters() const override;

        void setSceneParameters(std::shared_ptr<ISceneParameters> sceneParameters) override;
    private:
        int _width;
        int _height;
        int _openGlMajorVersion;
        int _openGlMinorVersion;
        std::string _title;
        bool _isVerticalSyncEnabled;
        std::shared_ptr<ISceneParameters> _sceneParameters;
    };
}

#endif // TENGINE_GRAPHICSPARAMETERS_H