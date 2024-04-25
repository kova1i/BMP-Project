#pragma once

#include "../filter.h"

class GrayscaleFilter : public Filter {
public:
    GrayscaleFilter() {
    }
    void Apply(Image& image) override;

protected:
    static constexpr double B_COEFF = 0.114;  // NOLINT
    static constexpr double G_COEFF = 0.587;  // NOLINT
    static constexpr double R_COEFF = 0.299;  // NOLINT
};

std::unique_ptr<Filter> GrayscaleFilterGenerator(const QueryParameters& query_parameters);
