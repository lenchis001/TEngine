#include "PngLoadingPluginImplementation.h"

#include "Models/PngPluginImage.h"
#include <png.h>
#include <fstream>
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

std::shared_ptr<IPluginImage> PngLoadingPluginImplementation::load(const std::string &path)
{
    FILE *fp = fopen(path.c_str(), "rb");
    if (!fp) {
        return nullptr;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(fp);
        return nullptr;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, nullptr, nullptr);
        fclose(fp);
        return nullptr;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);
        return nullptr;
    }

    png_init_io(png, fp);
    png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

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

    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);

    fclose(fp);

    std::vector<char> imageData;
    for (int y = 0; y < height; y++) {
        imageData.insert(imageData.end(), row_pointers[y], row_pointers[y] + png_get_rowbytes(png, info));
        free(row_pointers[y]);
    }
    free(row_pointers);

    png_destroy_read_struct(&png, &info, nullptr);

    return std::make_shared<PngPluginImage>(width, height, imageData.data(), imageData.size());
}

std::shared_ptr<IImageLoadingPlugin> load() {
    return std::make_shared<PngLoadingPluginImplementation>();
}