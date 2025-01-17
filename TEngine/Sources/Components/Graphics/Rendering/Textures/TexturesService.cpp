
#include "GL/glew.h"

#include "TexturesService.h"

#include <cassert>

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

    _loadCubeMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_X, rightTexturePath);
    _loadCubeMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, leftTexturePath);
    _loadCubeMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, topTexturePath);
    _loadCubeMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottomTexturePath);
    _loadCubeMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, frontTexturePath);
    _loadCubeMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, backTexturePath);

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
    for (auto &texture : _textures)
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

bool TexturesService::isAlphaChannelAware(GLuint textureId)
{
    glBindTexture(GL_TEXTURE_2D, textureId);

    GLint internalFormat;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);

    glBindTexture(GL_TEXTURE_2D, 0);

    return internalFormat == GL_RGBA;
}

GLuint TexturesService::_readTexture(const std::string &textureFile)
{
    auto image = _imageLoadingService->load(textureFile);

    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    auto internalFormat = _toTextureInternalFormat(image->getPixelType());

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        internalFormat,
        image->getWidth(),
        image->getHeight(),
        0,
        internalFormat,
        GL_UNSIGNED_BYTE,
        image->getData().data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void TexturesService::_loadCubeMapSide(GLenum side, const std::string &texturePath)
{
    auto image = _imageLoadingService->load(texturePath);

    auto internalFormat = _toTextureInternalFormat(image->getPixelType());

    glTexImage2D(
        side,
        0,
        internalFormat,
        image->getWidth(),
        image->getHeight(),
        0,
        internalFormat,
        GL_UNSIGNED_BYTE,
        image->getData().data());
}

GLuint TexturesService::_toTextureInternalFormat(EnginePixelType pixelType)
{
    switch (pixelType)
    {
    case PixelType::RGB:
        return GL_RGB;
    case PixelType::RGBA:
        return GL_RGBA;
    default:
        assert(false && "Unknown pixel type!");
        return GL_RGB;
    }
}