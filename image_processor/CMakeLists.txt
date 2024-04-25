add_executable(
    image_processor
        image_processor.cpp
        color_rgb.h color_rgb.h color_rgb.cpp bmp.h application.cpp application.h bmp.cpp image.cpp image.h converter_image_bmp.h converter_image_bmp.cpp filter.h filter.cpp command_line_parser.h command_line_parser.cpp pipeline.h pipeline.cpp filters/negative_filter.cpp application_settings.h query_parameters.h query_parameters.cpp application_settings.cpp filters/crop_filter.h filters/crop_filter.cpp filters/grayscale_filter.h filters/grayscale_filter.cpp filters/sharpening_filter.h filters/sharpening_filter.cpp filters/edge_detection_filter.cpp filters/gaussian_blur_filter.h filters/gaussian_blur_filter.cpp filters/soap_bubbles_filter.h filters/soap_bubbles_filter.cpp)
