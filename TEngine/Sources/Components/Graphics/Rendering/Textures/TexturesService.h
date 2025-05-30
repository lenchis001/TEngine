#ifndef TENGINE_TEXTURES_SERVICE_H
#define TENGINE_TEXTURES_SERVICE_H

#include "ITexturesService.h"

#include <unordered_map>
#include <string>
#include <memory>
#include <set>

#include "Components/Graphics/ImageLoading/Services/IImageLoadingService.h"

using namespace TEngine::Components::Graphics::ImageLoading::Services;
using namespace TEngine::Components::Graphics::ImageLoading::Models;

using EnginePixelType = TEngine::Components::Graphics::ImageLoading::Models::PixelType;

namespace TEngine::Components::Graphics::Rendering::Textures
{
    class TexturesService : public ITexturesService
    {
    public:
        TexturesService(std::shared_ptr<IImageLoadingService> imageLoadingService);
        ~TexturesService() override;

        void initialize() override;

        GLuint take(const std::string &textureFile) override;

        GLuint takeCubeMap(
            const std::string &rightTexturePath,
            const std::string &leftTexturePath,
            const std::string &topTexturePath,
            const std::string &bottomTexturePath,
            const std::string &frontTexturePath,
            const std::string &backTexturePath) override;

        void release(GLuint textureId) override;

        bool isAlphaChannelAware(GLuint textureId) override;

    private:
        GLuint _readTexture(const std::string& textureFile);

        void _loadCubeMapSide(GLenum side, const std::string& texturePath);

        static GLuint _toTextureInternalFormat(EnginePixelType pixelType);

        std::shared_ptr<IImageLoadingService> _imageLoadingService;

        std::unordered_map<std::string, std::size_t> _usagesCounter;
        std::unordered_map<std::string, GLuint> _textures;
        std::set<GLuint> _alphaTextures;
    };
}

#endif // TENGINE_TEXTURES_SERVICE_H