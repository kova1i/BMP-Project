#include "edge_detection_filter.h"

void EdgeDetectionFilter::Apply(Image& image) {
    GrayscaleFilter grayscale_filter;
    grayscale_filter.Apply(image);

    std::vector<ColorReal> result(image.GetWidth() * image.GetHeight());

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            ColorReal value = ColorReal{0, 0, 0};

            for (int32_t di = -1; di <= 1; ++di) {
                for (int32_t dj = -1; dj <= 1; ++dj) {
                    int32_t ni = static_cast<int32_t>(i) + di;
                    int32_t nj = static_cast<int32_t>(j) + dj;

                    ni = std::clamp(ni, 0, static_cast<int32_t>(image.GetHeight()) - 1);
                    nj = std::clamp(nj, 0, static_cast<int32_t>(image.GetWidth()) - 1);

                    value.b_ += image(ni, nj).b_ * COEFF[di + 1][dj + 1];
                    value.g_ += image(ni, nj).g_ * COEFF[di + 1][dj + 1];
                    value.r_ += image(ni, nj).r_ * COEFF[di + 1][dj + 1];
                }
            }

            value.b_ = std::clamp(value.b_, 0.0, 1.0);
            value.g_ = std::clamp(value.b_, 0.0, 1.0);
            value.r_ = std::clamp(value.b_, 0.0, 1.0);

            if (value.b_ < threshold_) {
                value.b_ = 0;
            } else {
                value.b_ = 1;
            }
            if (value.g_ < threshold_) {
                value.g_ = 0;
            } else {
                value.g_ = 1;
            }
            if (value.r_ < threshold_) {
                value.r_ = 0;
            } else {
                value.r_ = 1;
            }

            result[i * image.GetWidth() + j] = value;
        }
    }
    image.GetData() = result;
}

std::unique_ptr<Filter> EdgeDetectionFilterGenerator(const QueryParameters& query_parameters) {
    if (query_parameters.name != "edge") {
        throw std::logic_error("Attempting to generate filter with another name.");
    }
    if (query_parameters.parameters.size() != 1) {
        throw std::invalid_argument("Invalid number of parameters for some filter.");
    }

    return std::make_unique<EdgeDetectionFilter>(std::stod(query_parameters.parameters[0]));
}
