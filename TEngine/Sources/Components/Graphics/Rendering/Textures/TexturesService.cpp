
#include "GL/glew.h"

#include "TexturesService.h"

#include "cassert"

using namespace TEngine::Components::Graphics::Rendering::Textures;

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

    auto textureId = _readTexture(textureFile);

    _textures[textureFile] = textureId;
    _usagesCounter[textureFile] = 1;

    return textureId;
}

GLuint TexturesService::takeCubeMap(
    const std::string &rightTexturePath,
    const std::string &leftTexturePath,
    const std::string &topTexturePath,
    const std::string &bottomTexturePath,
    const std::string &frontTexturePath,
    const std::string &backTexturePath)
{
    auto texturePath = rightTexturePath + leftTexturePath + topTexturePath + bottomTexturePath + frontTexturePath + backTexturePath;

    if (_textures.find(texturePath) != _textures.end())
    {
        _usagesCounter[texturePath]++;

        return _textures[texturePath];
    }

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    auto rightImage = _imageLoadingService->load(rightTexturePath);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, rightImage->getWidth(), rightImage->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, rightImage->getData());

    auto leftImage = _imageLoadingService->load(leftTexturePath);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, leftImage->getWidth(), leftImage->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, leftImage->getData());

    auto topImage = _imageLoadingService->load(topTexturePath);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, topImage->getWidth(), topImage->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, topImage->getData());

    auto bottomImage = _imageLoadingService->load(bottomTexturePath);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, bottomImage->getWidth(), bottomImage->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, bottomImage->getData());

    auto frontImage = _imageLoadingService->load(frontTexturePath);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, frontImage->getWidth(), frontImage->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, frontImage->getData());

    auto backImage = _imageLoadingService->load(backTexturePath);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, backImage->getWidth(), backImage->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, backImage->getData());

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    _textures[texturePath] = textureId;
    _usagesCounter[texturePath] = 1;

    return textureId;
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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}