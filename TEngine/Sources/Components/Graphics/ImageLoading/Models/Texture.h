#ifndef TENGINE_TEXTURE_H
#define TENGINE_TEXTURE_H

namespace TEngine::Components::Graphics::ImageLoading::Models
{
    class Texture
    {
    public:
        Texture(void *data, int width, int height);

        void *getData() const;

        int getWidth() const;
        int getHeight() const;

    private:
        void *_data;
        int _width;
        int _height;
    };
};

#endif // TENGINE_TEXTURE_H