#pragma once

#include <string>
#include <vector>

struct QueryParameters {
    std::string name;
    std::vector<std::string> parameters;

    bool operator<(const QueryParameters& other) const;

    bool operator==(const QueryParameters& other) const;
};
