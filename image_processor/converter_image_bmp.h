#pragma once

#include "bmp.h"
#include "image.h"

class ConverterImageBMP {
public:
    BMP GetBMP(const Image& image, BMP::BMPHeader& bmp_header, BMP::DIBHeader dib_header);
    Image GetImage(const BMP& bmp);
};
