
#include "GL/glew.h"

#include "TexturesService.h"

#include "cassert"

using namespace TEngine::Components::Graphics::Rendering::Services::Textures;

TexturesService::TexturesService(std::shared_ptr<IImageLoadingService> imageLoadingService)
    : _imageLoadingService(imageLoadingService)
{
}

TexturesService::~TexturesService()
{
    assert(_textures.empty() && "Textures are not empty!");
}

void TexturesService::initialize()
{
    _imageLoadingService->initialize();
}

GLuint TexturesService::take(const std::string &textureFile)
{
    if (_textures.find(textureFile) != _textures.end())
    {
        _usagesCounter[textureFile]++;

        return _textures[textureFile];
    }

    auto texture = _readTexture(textureFile);

    _textures[textureFile] = texture;
    _usagesCounter[textureFile] = 1;

    return texture;
}

void TexturesService::release(GLuint textureId)
{
    for (auto& texture : _textures)
    {
        if (texture.second == textureId)
        {
            _usagesCounter[texture.first]--;

            if (_usagesCounter[texture.first] == 0)
            {
                glDeleteTextures(1, &texture.second);

                _usagesCounter.erase(texture.first);
                _textures.erase(texture.first);
            }

            return;
        }
    }

    assert(false && "Texture not found!");
}

GLuint TexturesService::_readTexture(const std::string& textureFile)
{
    auto image = _imageLoadingService->load(textureFile);

    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getData());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}