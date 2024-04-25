#include "gaussian_blur_filter.h"

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
}

std::vector<double> GaussianBlurFilter::GenerateGaussianKernel(double sigma, size_t size) const {
    std::vector<double> kernel(size);

    double sum = 0.0;
    int32_t mid = static_cast<int32_t>(size) / 2;

    for (int i = 0; i < size; ++i) {
        double distance = static_cast<double>(i) - static_cast<double>(mid);
        kernel[i] = std::exp(-HALF * distance * distance / (sigma * sigma));
        sum += kernel[i];
    }

    for (int i = 0; i < size; ++i) {
        kernel[i] /= sum;
    }

    return kernel;
}

void GaussianBlurFilter::ApplyBlurHorizontal(Image& image, const std::vector<double>& kernel) {
    std::vector<ColorReal> result = image.GetData();

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            ColorReal value{0.0, 0.0, 0.0};

            for (size_t k = 0; k < kernel.size(); ++k) {
                int32_t pos =
                    static_cast<int32_t>(j) - static_cast<int32_t>(kernel.size()) / 2 + static_cast<int32_t>(k);

                pos = std::clamp(pos, 0, static_cast<int32_t>(image.GetWidth()) - 1);

                value.b_ += kernel[k] * image(i, pos).b_;
                value.g_ += kernel[k] * image(i, pos).g_;
                value.r_ += kernel[k] * image(i, pos).r_;
            }

            result[i * image.GetWidth() + j] = value;
        }
    }

    image.GetData() = result;
}

void GaussianBlurFilter::ApplyBlurVertical(Image& image, const std::vector<double>& kernel) {
    std::vector<ColorReal> result = image.GetData();

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            ColorReal value{0.0, 0.0, 0.0};

            for (size_t k = 0; k < kernel.size(); ++k) {
                int32_t pos =
                    static_cast<int32_t>(i) - static_cast<int32_t>(kernel.size()) / 2 + static_cast<int32_t>(k);

                pos = std::max(0, pos);
                pos = std::min(pos, static_cast<int32_t>(image.GetWidth()) - 1);

                value.b_ += kernel[k] * image(pos, j).b_;
                value.g_ += kernel[k] * image(pos, j).g_;
                value.r_ += kernel[k] * image(pos, j).r_;
            }

            result[i * image.GetWidth() + j] = value;
        }
    }

    image.GetData() = result;
}

void GaussianBlurFilter::Apply(Image& image) {
    size_t kernel_size = static_cast<size_t>(std::round(MAGIC_NUM * sigma_ + 1));

    std::vector<double> kernel = GenerateGaussianKernel(sigma_, kernel_size);

    ApplyBlurHorizontal(image, kernel);
    ApplyBlurVertical(image, kernel);
}

std::unique_ptr<Filter> GaussianBlurFilterGenerator(const QueryParameters& query_parameters) {
    if (query_parameters.name != "blur") {
        throw std::logic_error("Attempting to generate filter with another name.");
    }
    if (query_parameters.parameters.size() != 1) {
        throw std::invalid_argument("Invalid number of parameters for some filter.");
    }
    if (std::stod(query_parameters.parameters[0]) < 0) {
        throw std::invalid_argument("Invalid parameter value for some filter.");
    }

    return std::make_unique<GaussianBlurFilter>(std::stod(query_parameters.parameters[0]));
}
