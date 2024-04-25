#include "converter_image_bmp.h"

#include <iostream>

BMP ConverterImageBMP::GetBMP(const Image& image, BMP::BMPHeader& bmp_header, BMP::DIBHeader dib_header) {
    BMP bmp;

    bmp.GetBMPHeader() = bmp_header;
    bmp.GetDIBHeader() = dib_header;

    bmp.SetWidth(static_cast<int32_t>(image.GetWidth()));
    bmp.SetHeight(static_cast<int32_t>(image.GetHeight()));

    bmp.GetData().resize(image.GetWidth() * image.GetHeight());
    for (size_t i = 0; i < bmp.GetData().size(); ++i) {
        bmp.GetData()[i] = static_cast<Color24>(image.GetData()[i]);
    }

    return bmp;
}

Image ConverterImageBMP::GetImage(const BMP& bmp) {
    Image image;

    image.GetWidth() = static_cast<size_t>(bmp.GetWidth());
    image.GetHeight() = static_cast<size_t>(bmp.GetHeight());

    image.GetData().resize(bmp.GetWidth() * bmp.GetHeight());
    for (size_t i = 0; i < image.GetData().size(); ++i) {
        image.GetData()[i] = static_cast<ColorReal>(bmp.GetData()[i]);
    }

    return image;
}
