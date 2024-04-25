#pragma once

#include "../filter.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

class SoapBubblesFilter : public Filter {
public:
    SoapBubblesFilter(int32_t bubbles_num, double max_radius) : bubbles_num_(bubbles_num), max_radius_(max_radius) {
    }

    void Apply(Image& image) override;

private:
    int32_t bubbles_num_;
    double max_radius_;

    void ApplySoapBubbleDistortion(Image& image, double x, double y, double radius);
};

std::unique_ptr<Filter> SoapBubblesFilterGenerator(const QueryParameters& query_parameters);
