#pragma once

#include "filter.h"
#include "image.h"

#include <memory>
#include <string>

class Pipeline {
public:
    std::vector<std::unique_ptr<Filter>>& GetQueries();
    const std::vector<std::unique_ptr<Filter>>& GetQueries() const;

    void ApplyPipeline(Image& image);

protected:
    std::vector<std::unique_ptr<Filter>> queries_;
};
