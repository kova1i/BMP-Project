#pragma once

#include "../filter.h"

class SharpeningFilter : public Filter {
public:
    SharpeningFilter() {
    }
    void Apply(Image& image) override;

private:
    static constexpr double COEFF[3][3] = {{0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}};
};

std::unique_ptr<Filter> SharpeningFilterGenerator(const QueryParameters& query_parameters);
