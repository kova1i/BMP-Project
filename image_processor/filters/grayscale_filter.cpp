#include "grayscale_filter.h"

void GrayscaleFilter::Apply(Image& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            double val = image(i, j).b_ * B_COEFF + image(i, j).g_ * G_COEFF + image(i, j).r_ * R_COEFF;
            image(i, j) = ColorReal{val, val, val};
        }
    }
}

std::unique_ptr<Filter> GrayscaleFilterGenerator(const QueryParameters& query_parameters) {
    if (query_parameters.name != "gs") {
        throw std::logic_error("Attempting to generate filter with another name.");
    }
    if (!query_parameters.parameters.empty()) {
        throw std::invalid_argument("Invalid number of parameters for some filter.");
    }

    return std::make_unique<GrayscaleFilter>();
}
