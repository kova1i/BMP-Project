#pragma once

#include "application_settings.h"
#include "command_line_parser.h"
#include "converter_image_bmp.h"
#include "filters/crop_filter.h"
#include "filters/edge_detection_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/gaussian_blur_filter.h"
#include "filters/negative_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/soap_bubbles_filter.h"
#include "pipeline.h"

#include <iostream>

class Application {
public:
    void Setup();
    void Start(int argc, char* argv[]);

protected:
    ApplicationSettings application_settings_;
    CommandLineParser command_line_parser_;
    Pipeline pipeline_;
    ConverterImageBMP converter_image_bmp_;
};
