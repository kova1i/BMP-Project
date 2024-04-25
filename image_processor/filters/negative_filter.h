#pragma once

#include "../filter.h"

class NegativeFilter : public Filter {
public:
    NegativeFilter() {
    }
    void Apply(Image& image) override;
};

std::unique_ptr<Filter> NegativeFilterGenerator(const QueryParameters& query_parameters);
