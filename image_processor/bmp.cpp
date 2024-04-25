#include "bmp.h"

BMP::BMPHeader& BMP::GetBMPHeader() {
    return bmp_header_;
}

const BMP::BMPHeader& BMP::GetBMPHeader() const {
    return bmp_header_;
}

BMP::DIBHeader& BMP::GetDIBHeader() {
    return dib_header_;
}

const BMP::DIBHeader& BMP::GetDIBHeader() const {
    return dib_header_;
}

const int32_t BMP::GetWidth() const {
    return dib_header_.width;
}

void BMP::SetWidth(int32_t width) {
    dib_header_.width = width;
}

const int32_t BMP::GetHeight() const {
    return dib_header_.height;
}

void BMP::SetHeight(int32_t height) {
    dib_header_.height = height;
}

std::vector<Color24>& BMP::GetData() {
    return data_;
}

const std::vector<Color24>& BMP::GetData() const {
    return data_;
}

void BMP::ReadFile(const std::string& file_path) {
    std::ifstream file = OpenForReading(file_path);

    file.seekg(0);
    ReadBMPHeader(file);
    ReadDIBHeader(file);
    ReadData(file);

    file.close();
}

std::ifstream BMP::OpenForReading(const std::string& file_path) {
    if (file_path.empty()) {
        throw std::invalid_argument("File path should not be empty.");
    }
    std::ifstream file(file_path);
    if (!file) {
        throw std::runtime_error("Error opening file for reading.");
    }

    return file;
}

void BMP::ReadBMPHeader(std::ifstream& file) {
    if (!file) {
        throw std::runtime_error("Error reading file.");
    }
    file.read(reinterpret_cast<char*>(&bmp_header_), sizeof(BMPHeader));
    if (!file) {
        throw std::runtime_error("Error reading file.");
    }

    if (bmp_header_.type != BMP_TYPE) {
        throw std::runtime_error("BMP file is not correct.");
    }
}

void BMP::ReadDIBHeader(std::ifstream& file) {
    if (!file) {
        throw std::runtime_error("Error reading file.");
    }
    file.read(reinterpret_cast<char*>(&dib_header_), sizeof(DIBHeader));
    if (!file) {
        throw std::runtime_error("Error reading file.");
    }

    if (dib_header_.bits_per_pixel != BMP_BITS_PER_PIXEL) {
        throw std::runtime_error("BMP file is not correct.");
    }
    if (dib_header_.color_planes != BMP_COLOR_PLANES) {
        throw std::runtime_error("BMP file is not correct.");
    }
    if (dib_header_.compression_method != BMP_COMPRESSION_METHOD) {
        throw std::runtime_error("BMP file is not correct.");
    }
}

void BMP::ReadData(std::ifstream& file) {
    if (!file) {
        throw std::runtime_error("Error reading file.");
    }

    file.seekg(bmp_header_.offset);
    data_.resize(GetWidth() * GetHeight());

    std::vector<uint8_t> alignment;
    if ((GetWidth() * 3) % 4 != 0) {
        int32_t alignment_size = 4 - (GetWidth() * 3) % 4;
        alignment.resize(alignment_size, 0);
    }

    for (size_t i = 0; i < GetHeight(); ++i) {
        if (!file) {
            throw std::runtime_error("Error reading file.");
        }
        file.read(reinterpret_cast<char*>(data_.data() + i * GetWidth()), GetWidth() * 3);
        if (!file) {
            throw std::runtime_error("Error reading file.");
        }
        file.read(reinterpret_cast<char*>(alignment.data()), static_cast<int32_t>(alignment.size()));
        if (!file) {
            throw std::runtime_error("Error reading file.");
        }
    }
}

void BMP::WriteFile(const std::string& file_path) {
    std::ofstream file = OpenForWriting(file_path);

    file.seekp(0);
    WriteBMPHeader(file);
    WriteDIBHeader(file);
    WriteData(file);

    file.close();
}

std::ofstream BMP::OpenForWriting(const std::string& file_path) {
    if (file_path.empty()) {
        throw std::invalid_argument("File path should not be empty.");
    }
    std::ofstream file(file_path);
    if (!file) {
        throw std::runtime_error("Error opening file for writing.");
    }

    return file;
}

void BMP::WriteBMPHeader(std::ofstream& file) {
    if (!file) {
        throw std::runtime_error("Error writing file.");
    }
    file.write(reinterpret_cast<char*>(&bmp_header_), sizeof(BMPHeader));
    if (!file) {
        throw std::runtime_error("Error writing file.");
    }
}

void BMP::WriteDIBHeader(std::ofstream& file) {
    if (!file) {
        throw std::runtime_error("Error writing file.");
    }
    file.write(reinterpret_cast<char*>(&dib_header_), sizeof(DIBHeader));
    if (!file) {
        throw std::runtime_error("Error writing file.");
    }
}

void BMP::WriteData(std::ofstream& file) {
    if (!file) {
        throw std::runtime_error("Error writing file.");
    }

    file.seekp(bmp_header_.offset);
    data_.resize(GetWidth() * GetHeight());

    std::vector<uint8_t> alignment;
    if ((GetWidth() * 3) % 4 != 0) {
        int32_t alignment_size = 4 - (GetWidth() * 3) % 4;
        alignment.resize(alignment_size, 0);
    }

    for (size_t i = 0; i < GetHeight(); ++i) {
        if (!file) {
            throw std::runtime_error("Error writing file.");
        }
        file.write(reinterpret_cast<char*>(data_.data() + i * GetWidth()), GetWidth() * 3);
        if (!file) {
            throw std::runtime_error("Error writing file.");
        }
        file.write(reinterpret_cast<char*>(alignment.data()), static_cast<int32_t>(alignment.size()));
        if (!file) {
            throw std::runtime_error("Error writing file.");
        }
    }
}
