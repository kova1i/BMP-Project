#pragma once

#include "../filter.h"

#include <cmath>
#include <cstdint>

class CropFilter : public Filter {
public:
    CropFilter(size_t width, size_t height) : width_(width), height_(height) {
    }

    void Apply(Image& image) override;

protected:
    size_t width_;
    size_t height_;
};

std::unique_ptr<Filter> CropFilterGenerator(const QueryParameters& query_parameters);
