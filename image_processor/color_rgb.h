#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

class Color24;
class ColorReal;

class Color24 {
public:
    uint8_t b_;
    uint8_t g_;
    uint8_t r_;

    explicit operator ColorReal() const;
} __attribute__((packed));

class ColorReal {
public:
    static constexpr double MAX_COLOR_VALUE = 255;  // NOLINT

    double b_;
    double g_;
    double r_;

    explicit operator Color24() const;
};
