#include "application.h"
#include "converter_image_bmp.h"

#include <iostream>

int main(int argc, char** argv) {
    Application app;
    app.Setup();
    app.Start(argc, argv);
    return 0;
}
