#include "soap_bubbles_filter.h"

void SoapBubblesFilter::Apply(Image& image) {
    std::random_device rd;
    std::mt19937 rnd(rd());

    std::uniform_int_distribution<> gen_x(0, static_cast<int32_t>(image.GetWidth()) - 1);
    std::uniform_int_distribution<> gen_y(0, static_cast<int32_t>(image.GetHeight()) - 1);
    std::uniform_real_distribution<> gen_radius(0, max_radius_);

    for (int i = 0; i < bubbles_num_; ++i) {
        ApplySoapBubbleDistortion(image, gen_x(rnd), gen_y(rnd), gen_radius(rnd));
    }
}

void SoapBubblesFilter::ApplySoapBubbleDistortion(Image& image, double x, double y, double radius) {
    Image result = image;

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            double distance =
                std::sqrt(std::pow(static_cast<double>(j) - x, 2) + std::pow(static_cast<double>(i) - y, 2));

            if (distance < radius) {
                double ratio = distance / radius;
                double angle = std::atan2(static_cast<double>(i) - y, static_cast<double>(j) - x);

                double distorted_distance = std::sqrt(radius * radius - distance * distance);
                int32_t distorted_x = static_cast<int32_t>(std::round(x + distorted_distance * std::cos(angle)));
                int32_t distorted_y = static_cast<int32_t>(std::round(y + distorted_distance * std::sin(angle)));

                distorted_x = std::clamp(distorted_x, 0, static_cast<int32_t>(image.GetWidth()) - 1);
                distorted_y = std::clamp(distorted_y, 0, static_cast<int32_t>(image.GetHeight()) - 1);

                result(i, j).b_ = image(i, j).b_ * (1.0 - ratio) + image(distorted_y, distorted_x).b_ * ratio;
                result(i, j).g_ = image(i, j).g_ * (1.0 - ratio) + image(distorted_y, distorted_x).g_ * ratio;
                result(i, j).r_ = image(i, j).r_ * (1.0 - ratio) + image(distorted_y, distorted_x).r_ * ratio;
            }
        }
    }

    image = result;
}

std::unique_ptr<Filter> SoapBubblesFilterGenerator(const QueryParameters& query_parameters) {
    if (query_parameters.name != "bubble") {
        throw std::logic_error("Attempting to generate filter with another name.");
    }
    if (query_parameters.parameters.size() != 2) {
        throw std::invalid_argument("Invalid number of parameters for some filter.");
    }

    return std::make_unique<SoapBubblesFilter>(std::stoi(query_parameters.parameters[0]),
                                               std::stod(query_parameters.parameters[1]));
}
