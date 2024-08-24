#ifndef TENGINE_TEXTURES_SERVICE_H
#define TENGINE_TEXTURES_SERVICE_H

#include "ITexturesService.h"

#include "map"
#include "string"
#include "memory"

#include "Components/Graphics/ImageLoading/Services/IImageLoadingService.h"

using namespace TEngine::Components::Graphics::ImageLoading::Services;

namespace TEngine::Components::Graphics::Rendering::Services::Textures
{
    class TexturesService : public ITexturesService
    {
    public:
        TexturesService(std::shared_ptr<IImageLoadingService> imageLoadingService);
        ~TexturesService() override;

        void initialize() override;

        GLuint take(const std::string &textureFile) override;

        void release(GLuint textureId) override;

    private:
        GLuint _readTexture(const std::string& textureFile);

        std::shared_ptr<IImageLoadingService> _imageLoadingService;

        std::map<std::string, std::size_t> _usagesCounter;
        std::map<std::string, GLuint> _textures;
    };
}

#endif // TENGINE_TEXTURES_SERVICE_H