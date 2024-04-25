#include "command_line_parser.h"

#include <iostream>
#include <stdexcept>

bool IsFilterName(const char* name) {
    std::string s = std::string(name);
    if (s[0] != '-') {
        return false;
    }
    for (size_t i = 1; i < s.size(); ++i) {
        if (isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

void CommandLineParser::Parse(int argc, char** argv, ApplicationSettings& application_settings, Pipeline& pipeline) {
    if (argc < 3) {
        throw std::runtime_error("Input or output file is not given");
    }

    application_settings.GetInputFilePath() = argv[1];
    application_settings.GetOutputFilePath() = argv[2];

    size_t i = 3;
    while (i < argc) {
        if (!IsFilterName(argv[i])) {
            throw std::logic_error("Filter input is not correct");
        }

        QueryParameters query;
        query.name = std::string(argv[i]).substr(1);
        size_t j = i + 1;
        while (j < argc && !IsFilterName(argv[j])) {
            std::string parameter = std::string(argv[j]);
            query.parameters.push_back(parameter);
            ++j;
        }

        Generator& filter_generator = application_settings.GetFilterGenerator(query.name);
        pipeline.GetQueries().push_back(filter_generator(query));

        i = j;
    }
}
