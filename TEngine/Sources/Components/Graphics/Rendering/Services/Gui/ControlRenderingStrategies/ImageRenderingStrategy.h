#ifndef TENGINE_IMAGE_RENDERING_STRATEGY_H
#define TENGINE_IMAGE_RENDERING_STRATEGY_H

#include "IImageRenderingStrategy.h"

#include <string>
#include <memory>

#include "GLFW/glfw3.h"

#include "Components/Graphics/Rendering/Services/Textures/ITexturesService.h"

#include "ControlStrategyBase.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Textures;

namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies
{
    class ImageRenderingStrategy : public ControlStrategyBase, public IImageRenderingStrategy
    {
    public:
        ImageRenderingStrategy(std::shared_ptr<ITexturesService> textureService, const std::string& path);
        ~ImageRenderingStrategy() override;

        void render() override;

        private:
            std::shared_ptr<ITexturesService> _textureService;
            GLuint _textureId;
    };
}

#endif // TENGINE_IMAGE_RENDERING_STRATEGY_H