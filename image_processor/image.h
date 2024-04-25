#pragma once

#include "color_rgb.h"

#include <vector>

class Image {
public:
    size_t& GetWidth();
    const size_t& GetWidth() const;

    size_t& GetHeight();
    const size_t& GetHeight() const;

    std::vector<ColorReal>& GetData();
    const std::vector<ColorReal>& GetData() const;

    ColorReal& operator()(size_t i, size_t j);
    const ColorReal& operator()(size_t i, size_t j) const;

protected:
    size_t width_;
    size_t height_;
    std::vector<ColorReal> data_;
};
