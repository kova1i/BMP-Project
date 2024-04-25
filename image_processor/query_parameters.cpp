#include "query_parameters.h"

bool QueryParameters::operator<(const QueryParameters& other) const {
    return name < other.name;
}

bool QueryParameters::operator==(const QueryParameters& other) const {
    return name == other.name;
}
