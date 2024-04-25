#pragma once

#include "application_settings.h"
#include "pipeline.h"
#include "query_parameters.h"

#include <string>
#include <vector>

bool IsFilterName(const char* name);

class CommandLineParser {
public:
    void Parse(int argc, char* argv[], ApplicationSettings& application_settings, Pipeline& pipeline);
};
