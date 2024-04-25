#include "negative_filter.h"

void NegativeFilter::Apply(Image& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image(i, j) = ColorReal{1.0 - image(i, j).b_, 1.0 - image(i, j).g_, 1.0 - image(i, j).r_};
        }
    }
}

std::unique_ptr<Filter> NegativeFilterGenerator(const QueryParameters& query_parameters) {
    if (query_parameters.name != "neg") {
        throw std::logic_error("Attempting to generate filter with another name.");
    }
    if (!query_parameters.parameters.empty()) {
        throw std::invalid_argument("Invalid number of parameters for some filter.");
    }

    return std::make_unique<NegativeFilter>();
}
