#ifndef TENGINE_RENDERINGPARAMETERS_H
#define TENGINE_RENDERINGPARAMETERS_H

#include "IRenderingParameters.h"

namespace TEngine::Components::Graphics::Rendering::Models
{
    class RenderingParameters : public IRenderingParameters
    {
    public:
        RenderingParameters();

        int getWidth() const;

        void setWidth(int width);

        int getHeight() const;

        void setHeight(int height);

        int getOpenGlMajorVersion() const;

        void setOpenGlMinorVersion(int openGlMinorVersion);

        int getOpenGlMinorVersion() const;

        void setOpenGlMajorVersion(int openGlMajorVersion);

        const std::string &getTitle() const;

        void setTitle(const std::string &title);
    private:
        int _width;
        int _height;
        int _openGlMajorVersion;
        int _openGlMinorVersion;
        std::string _title;
    };
}

#endif //TENGINE_RENDERINGPARAMETERS_H