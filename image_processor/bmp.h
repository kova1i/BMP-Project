#pragma once

#include "color_rgb.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

class BMP {
public:
    static const uint16_t BMP_TYPE = 0x4D42;
    static const uint16_t BMP_BITS_PER_PIXEL = 24;
    static const uint16_t BMP_COLOR_PLANES = 1;
    static const uint32_t BMP_COMPRESSION_METHOD = 0;

    struct BMPHeader {
        uint16_t type;
        uint32_t size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset;
    } __attribute__((packed));

    struct DIBHeader {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t color_planes;
        uint16_t bits_per_pixel;
        uint32_t compression_method;
        uint32_t image_size;
        int32_t horizontal_resolution;
        int32_t vertical_resolution;
        uint32_t colors_num;
        uint32_t important_colors_num;
    } __attribute__((packed));

    BMPHeader& GetBMPHeader();
    const BMPHeader& GetBMPHeader() const;

    DIBHeader& GetDIBHeader();
    const DIBHeader& GetDIBHeader() const;

    const int32_t GetWidth() const;
    void SetWidth(int32_t width);

    const int32_t GetHeight() const;
    void SetHeight(int32_t height);

    std::vector<Color24>& GetData();
    const std::vector<Color24>& GetData() const;

    void ReadFile(const std::string& file_path);
    void WriteFile(const std::string& file_path);

protected:
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    std::vector<Color24> data_;

    std::ifstream OpenForReading(const std::string& file_path);
    void ReadBMPHeader(std::ifstream& file);
    void ReadDIBHeader(std::ifstream& file);
    void ReadData(std::ifstream& file);

    std::ofstream OpenForWriting(const std::string& file_path);
    void WriteBMPHeader(std::ofstream& file);
    void WriteDIBHeader(std::ofstream& file);
    void WriteData(std::ofstream& file);
};
