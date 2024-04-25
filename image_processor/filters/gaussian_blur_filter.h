#pragma once

#include "../image.h"
#include "../filter.h"

#include <algorithm>
#include <cmath>

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(double sigma);
    void Apply(Image& image) override;

protected:
    const double HALF = 0.5;     // NOLINT
    const double MAGIC_NUM = 6;  // NOLINT

    std::vector<double> GenerateGaussianKernel(double sigma, size_t size) const;
    void ApplyBlurHorizontal(Image& image, const std::vector<double>& kernel);
    void ApplyBlurVertical(Image& image, const std::vector<double>& kernel);

    double sigma_;
};

std::unique_ptr<Filter> GaussianBlurFilterGenerator(const QueryParameters& query_parameters);
