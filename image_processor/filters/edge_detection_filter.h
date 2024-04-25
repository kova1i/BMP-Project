#pragma once

#include "../filter.h"
#include "grayscale_filter.h"

class EdgeDetectionFilter : public Filter {
public:
    explicit EdgeDetectionFilter(double threshold) : threshold_(threshold) {
    }
    void Apply(Image& image) override;

private:
    static constexpr double COEFF[3][3] = {{0.0, -1.0, 0.0}, {-1.0, 4.0, -1.0}, {0.0, -1.0, 0.0}};

    double threshold_;
};

std::unique_ptr<Filter> EdgeDetectionFilterGenerator(const QueryParameters& query_parameters);
