#ifndef TENGINE_IMAGE_H
#define TENGINE_IMAGE_H

namespace TEngine::Components::Graphics::ImageLoading::Models
{
    class Image
    {
    public:
        Image(void *data, unsigned int dataSize, int width, int height);
        ~Image();

        unsigned int getDataSize() const;

        void *getData() const;

        int getWidth() const;
        int getHeight() const;

    private:
        void *_data;
        int _width;
        int _height;
        unsigned int _dataSize;
    };
};

#endif // TENGINE_IMAGE_H