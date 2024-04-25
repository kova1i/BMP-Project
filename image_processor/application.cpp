#include "application.h"

void Application::Setup() {
    application_settings_.AddFilterGenerator("neg", NegativeFilterGenerator);
    application_settings_.AddFilterGenerator("crop", CropFilterGenerator);
    application_settings_.AddFilterGenerator("gs", GrayscaleFilterGenerator);
    application_settings_.AddFilterGenerator("sharp", SharpeningFilterGenerator);
    application_settings_.AddFilterGenerator("edge", EdgeDetectionFilterGenerator);
    application_settings_.AddFilterGenerator("blur", GaussianBlurFilterGenerator);
    application_settings_.AddFilterGenerator("bubble", SoapBubblesFilterGenerator);
}

void Application::Start(int argc, char **argv) {
    try {
        command_line_parser_.Parse(argc, argv, application_settings_, pipeline_);

        BMP bmp;
        bmp.ReadFile(application_settings_.GetInputFilePath());

        Image image = converter_image_bmp_.GetImage(bmp);
        pipeline_.ApplyPipeline(image);

        bmp = converter_image_bmp_.GetBMP(image, bmp.GetBMPHeader(), bmp.GetDIBHeader());

        bmp.WriteFile(application_settings_.GetOutputFilePath());
    } catch (std::exception &e) {
        std::cout << e.what();
    } catch (...) {
        std::cout << "Undefined exception";
    }
}
