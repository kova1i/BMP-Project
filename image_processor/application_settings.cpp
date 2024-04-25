#include "application_settings.h"

std::string& ApplicationSettings::GetInputFilePath() {
    return input_file_path_;
}

const std::string& ApplicationSettings::GetInputFilePath() const {
    return input_file_path_;
}
std::string& ApplicationSettings::GetOutputFilePath() {
    return output_file_path_;
}

const std::string& ApplicationSettings::GetOutputFilePath() const {
    return output_file_path_;
}

void ApplicationSettings::AddFilterGenerator(const std::string& name, const Generator& filter_generator) {
    if (filter_generators_.contains(name)) {
        throw std::logic_error("Filters should have different names");
    }
    filter_generators_[name] = filter_generator;
}

Generator& ApplicationSettings::GetFilterGenerator(const std::string& name) {
    if (!filter_generators_.contains(name)) {
        throw std::invalid_argument("This filter is not implemented");
    }
    return filter_generators_[name];
}
