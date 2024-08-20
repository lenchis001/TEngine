#include "IPluginImage.h"

using namespace TEngine::Components::Graphics::ImageLoading::Plugin;

namespace BmpImageLoadingPlugin::Models
{
    class BmpPluginImage : public IPluginImage
    {
    public:
        ~BmpPluginImage() = default;

        virtual void *getData() const;

        virtual int getWidth() const;
        virtual int getHeight() const;
    };
}