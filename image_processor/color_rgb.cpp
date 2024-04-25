#include "color_rgb.h"

Color24::operator ColorReal() const {
    ColorReal res = ColorReal{static_cast<double>(b_) / ColorReal::MAX_COLOR_VALUE,
                              static_cast<double>(g_) / ColorReal::MAX_COLOR_VALUE,
                              static_cast<double>(r_) / ColorReal::MAX_COLOR_VALUE};
    return res;
}

ColorReal::operator Color24() const {
    Color24 res = Color24{static_cast<uint8_t>(std::round(b_ * ColorReal::MAX_COLOR_VALUE)),
                          static_cast<uint8_t>(std::round(g_ * ColorReal::MAX_COLOR_VALUE)),
                          static_cast<uint8_t>(std::round(r_ * ColorReal::MAX_COLOR_VALUE))};
    return res;
}
