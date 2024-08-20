#ifndef TENGINE_IMAGE_H
#define TENGINE_IMAGE_H

namespace TEngine::Components::Graphics::ImageLoading::Models
{
    class Image
    {
    public:
        Image(void *data, int width, int height);

        void *getData() const;

        int getWidth() const;
        int getHeight() const;

    private:
        void *_data;
        int _width;
        int _height;
    };
};

#endif // TENGINE_IMAGE_H