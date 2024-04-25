#pragma once

#include "image.h"
#include "query_parameters.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Filter {
public:
    virtual ~Filter() = default;
    virtual void Apply(Image& image) = 0;
};
