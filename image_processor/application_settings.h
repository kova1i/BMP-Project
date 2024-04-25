#pragma once

#include "filter.h"
#include "query_parameters.h"

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

using Generator = std::function<std::unique_ptr<Filter>(const QueryParameters&)>;

struct ApplicationSettings {
public:
    void AddFilterGenerator(const std::string& name, const Generator& generator);
    Generator& GetFilterGenerator(const std::string& name);

    std::string& GetInputFilePath();
    const std::string& GetInputFilePath() const;

    std::string& GetOutputFilePath();
    const std::string& GetOutputFilePath() const;

protected:
    std::string input_file_path_;
    std::string output_file_path_;

    std::map<std::string, Generator> filter_generators_;
};
