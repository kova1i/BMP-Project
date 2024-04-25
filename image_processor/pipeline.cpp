#include "pipeline.h"

std::vector<std::unique_ptr<Filter>>& Pipeline::GetQueries() {
    return queries_;
}

const std::vector<std::unique_ptr<Filter>>& Pipeline::GetQueries() const {
    return queries_;
}

void Pipeline::ApplyPipeline(Image& image) {
    for (std::unique_ptr<Filter>& filter : queries_) {
        filter->Apply(image);
    }
}
