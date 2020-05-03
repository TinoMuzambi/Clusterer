// MZMTIN002

#include "clusterer.h"

bool MZMTIN002::Clusterer::openFile() {
    ifstream ppm;
    ppm.open(filename + "test.ppm");
    if (ppm.fail()) {
        cout << "Nah nigga" << endl;
        return false;
    }
    string header;
    int b;
    ppm >> header;
    if (strcmp(header.c_str(), "P6") != 0) {
        cout << "Not P6" << endl;
        return false;
    }
    ppm >> w >> h >> b;
    ppm.ignore(256, '\n');

    int buffSize = 3 * w * h;
    pixelData = new char[buffSize];
    ppm.read(pixelData, buffSize);

    pixel colours{};
    pixels.clear();
    for (int i = 0; i < buffSize; i += 3) {
        colours.r = pixelData[i];
        colours.g = pixelData[i + 1];
        colours.b = pixelData[i + 2];

        pixels.push_back(colours);
    }

    delete[] pixelData;
    ppm.close();

    // Test code
    for (unsigned int i = 0; i < h; i++) {
        for (unsigned int j = 0; j < w; j++) {
            pixel& ref_colour = get(j, i, pixels);
            cout << "RGB {" << (int)ref_colour.r << ", " << (int)ref_colour.g << ", " << (int)ref_colour.b << "}" << endl;
        }
    }

    auto grayPixels = grayscale();
    for (int i = 0; i < w * h; ++i) {
        cout << int(grayPixels[i]) << " " << endl;
    }
//    for (unsigned int i = 0; i < h; i++) {
//        for (unsigned int j = 0; j < w; j++) {
//            pixel& ref_colour = get(j, i, grayPixels);
//            cout << "RGB {" << (int)ref_colour.r << ", " << (int)ref_colour.g << ", " << (int)ref_colour.b << "}" << endl;
//        }
//    }

    return true;
}

MZMTIN002::Clusterer::Clusterer(const string &filename, const int noClusters, const int binWidth) {
    this->noClusters = noClusters;
    this->binWidth = binWidth;
    this->filename = filename;
}

MZMTIN002::Clusterer::pixel &MZMTIN002::Clusterer::get(unsigned int a, unsigned int b, vector<pixel>& myPixel) {
    return myPixel[(b * w) + a];
}

unsigned char * MZMTIN002::Clusterer::grayscale() {
    unsigned char *grayPixels;
    pixel colours{};
    grayPixels = new unsigned char[w * h];
    for (int i = 0; i < w * h; ++i) {
        grayPixels[i] = (pixels[i].r * 0.21) + (pixels[i].g * 0.72) + (pixels[i].b * 0.07);
//        colours.r = pixels[i].r * 0.21; // Add these suckers into a single pixel value.
//        colours.g = pixels[i].g * 0.72;
//        colours.b = pixels[i].b * 0.07;
    }

    return grayPixels;
}

