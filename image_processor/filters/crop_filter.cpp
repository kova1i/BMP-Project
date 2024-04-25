#include "crop_filter.h"

void CropFilter::Apply(Image& image) {
    std::vector<ColorReal> result;
    for (size_t i = 0; i < image.GetData().size(); ++i) {
        size_t row = image.GetHeight() - i / image.GetWidth() - 1;
        size_t column = i % image.GetWidth();

        if (row < height_ && column < width_) {
            result.push_back(image.GetData()[i]);
        }
    }

    image.GetWidth() = std::min(image.GetWidth(), width_);
    image.GetHeight() = std::min(image.GetHeight(), height_);
    image.GetData() = result;
}

std::unique_ptr<Filter> CropFilterGenerator(const QueryParameters& query_parameters) {
    if (query_parameters.name != "crop") {
        throw std::logic_error("Attempting to generate filter with another name.");
    }
    if (query_parameters.parameters.size() != 2) {
        throw std::invalid_argument("Invalid number of parameters for some filter.");
    }
    if (std::stoi(query_parameters.parameters[0]) < 0) {
        throw std::invalid_argument("Invalid parameter value for some filter.");
    }
    if (std::stoi(query_parameters.parameters[1]) < 0) {
        throw std::invalid_argument("Invalid parameter value for some filter.");
    }

    return std::make_unique<CropFilter>(std::stoi(query_parameters.parameters[0]),
                                        std::stoi(query_parameters.parameters[1]));
}
