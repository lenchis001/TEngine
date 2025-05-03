#include "PngLoadingPluginImplementation.h"

#include "Models/PngPluginImage.h"
#include <png.h>

#include <cstring>
#include <vector>

using namespace PngLoadingPlugin;
using namespace PngLoadingPlugin::Models;

PngLoadingPluginImplementation::PngLoadingPluginImplementation()
{
}

PngLoadingPluginImplementation::~PngLoadingPluginImplementation()
{
}

std::vector<std::string> PngLoadingPluginImplementation::getSupportedExtensions() const
{
    return std::vector<std::string>{"png"};
}

std::shared_ptr<IPluginImage> PngLoadingPluginImplementation::load(const std::vector<uint8_t>& data) {
    // Проверяем, что данные не пустые
    if (data.empty()) {
        return nullptr;
    }

    // Создаем структуры libpng
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        return nullptr;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, nullptr, nullptr);
        return nullptr;
    }

    // Обработка ошибок через setjmp
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, nullptr);
        return nullptr;
    }

    // Пользовательская функция чтения
    struct PngReaderState {
        const uint8_t* data;
        size_t size;
        size_t offset;
    };

    PngReaderState readerState = { data.data(), data.size(), 0 };

    auto readData = [](png_structp pngPtr, png_bytep outBytes, png_size_t byteCountToRead) {
        PngReaderState* state = static_cast<PngReaderState*>(png_get_io_ptr(pngPtr));
        if (state->offset + byteCountToRead > state->size) {
            png_error(pngPtr, "Read beyond end of buffer");
        }
        memcpy(outBytes, state->data + state->offset, byteCountToRead);
        state->offset += byteCountToRead;
    };

    png_set_read_fn(png, &readerState, readData);

    // Читаем PNG информацию
    png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    // Преобразуем данные в удобный формат
    if (bit_depth == 16) {
        png_set_strip_16(png);
    }

    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png);
    }

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
        png_set_expand_gray_1_2_4_to_8(png);
    }

    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png);
    }

    png_read_update_info(png, info);

    // Читаем изображение построчно
    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);

    // Копируем данные в вектор
    std::vector<char> imageData;
    for (int y = 0; y < height; y++) {
        imageData.insert(imageData.end(), row_pointers[y], row_pointers[y] + png_get_rowbytes(png, info));
        free(row_pointers[y]);
    }
    free(row_pointers);

    // Освобождаем ресурсы libpng
    png_destroy_read_struct(&png, &info, nullptr);

    // Возвращаем результат
    return std::make_shared<PngPluginImage>(width, height, imageData);
}

std::shared_ptr<IImageLoadingPlugin> load() {
    return std::make_shared<PngLoadingPluginImplementation>();
}