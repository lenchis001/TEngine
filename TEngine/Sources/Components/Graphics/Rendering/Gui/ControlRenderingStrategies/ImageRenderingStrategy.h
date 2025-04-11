#ifndef TENGINE_IMAGE_RENDERING_STRATEGY_H
#define TENGINE_IMAGE_RENDERING_STRATEGY_H

#include "IImageRenderingStrategy.h"

#include <string>
#include <memory>

#ifdef __ANDROID__
#include <EGL/egl.h>
#else
#include <GL/gl.h>
#endif

#include "Components/Graphics/Rendering/Textures/ITexturesService.h"

#include "ControlStrategyBase.h"

using namespace TEngine::Components::Graphics::Rendering::Textures;
using namespace TEngine::Components::Graphics::Models;

namespace TEngine::Components::Graphics::Rendering::Gui::ControlRenderingStrategies
{
    class ImageRenderingStrategy : public ControlStrategyBase, public IImageRenderingStrategy
    {
    public:
        ImageRenderingStrategy(std::shared_ptr<ITexturesService> textureService, const std::string &path);
        ~ImageRenderingStrategy() override;

        void render() override;

    private:
        std::shared_ptr<ITexturesService> _textureService;
        GLuint _textureId;
    };
}

#endif // TENGINE_IMAGE_RENDERING_STRATEGY_H