# BMP Processor

## Overview
BMP Processor is a console application for applying various filters to images. It supports BMP images in 24-bit BMP format without compression or color table.

## Features
- **Supported Image Format**: Input and output images should be in BMP format.
- **Filter Application**: Filters are applied sequentially in the order specified in the command line arguments.
- **Basic Filters**: Included filters are Crop, Grayscale, Negative, Sharpening, Edge Detection, and Gaussian Blur.
- **Custom Filter**: Bubble Effect.

## Usage
```
{program name} {input file path} {output file path} [-{filter name 1} [filter parameter 1] [filter parameter 2] ...] [-{filter name 2} [filter parameter 1] [filter parameter 2] ...] ...
```

## Filters
1. **Crop**: Crops the image to the specified width and height.
2. **Grayscale**: Converts the image to grayscale.
3. **Negative**: Converts the image to its negative.
4. **Sharpening**: Increases image sharpness.
5. **Edge Detection**: Highlights edges in the image.
6. **Gaussian Blur**: Applies Gaussian blur to the image.
7. **Bubble Effect**: Applies Bubbles Effect to the image.

## Note
Ensure that test images are saved in 24-bit BMP format for proper testing.
