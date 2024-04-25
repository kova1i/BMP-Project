#include "image.h"

size_t& Image::GetWidth() {
    return width_;
}

const size_t& Image::GetWidth() const {
    return width_;
}

size_t& Image::GetHeight() {
    return height_;
}

const size_t& Image::GetHeight() const {
    return height_;
}

std::vector<ColorReal>& Image::GetData() {
    return data_;
}

const std::vector<ColorReal>& Image::GetData() const {
    return data_;
}

ColorReal& Image::operator()(size_t i, size_t j) {
    return data_[i * GetWidth() + j];
}

const ColorReal& Image::operator()(size_t i, size_t j) const {
    return data_[i * GetWidth() + j];
}
