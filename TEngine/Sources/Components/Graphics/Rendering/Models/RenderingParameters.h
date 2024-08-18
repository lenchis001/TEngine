#ifndef TENGINE_RENDERINGPARAMETERS_H
#define TENGINE_RENDERINGPARAMETERS_H

#include "IRenderingParameters.h"

namespace TEngine::Components::Graphics::Rendering::Models
{
    class RenderingParameters : public IRenderingParameters
    {
    public:
        RenderingParameters();

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

    private:
        int _width;
        int _height;
        int _openGlMajorVersion;
        int _openGlMinorVersion;
        std::string _title;
        bool _isVerticalSyncEnabled;
    };
}

#endif // TENGINE_RENDERINGPARAMETERS_H