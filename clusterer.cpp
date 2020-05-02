// MZMTIN002

#include "clusterer.h"

void MZMTIN002::Clusterer::grayscale() {
    ifstream ppm;
    ppm.open(filename + "eight_1.ppm");
    if (ppm.fail()) {
        cout << "Nah nigga" << endl;
        return;
    }
    string header;
    int b;
    ppm >> header;
    if (strcmp(header.c_str(), "P6") != 0) {
        cout << "Not P6" << endl;
        return;
    }
    ppm >> w >> h >> b;
    ppm.ignore(256, '\n');

//    cout << w << h << b << endl;

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

    ppm.close();

    // Test code
    for (unsigned int i = 0; i < h; i++) {
        for (unsigned int j = 0; j < w; j++) {
            pixel& ref_colour = get(j, i);
            cout << "RGB {" << (int)ref_colour.r << ", " << (int)ref_colour.g << ", " << (int)ref_colour.b << "}" << endl;
        }
    }
}

MZMTIN002::Clusterer::Clusterer(const string &filename, const int noClusters, const int binWidth) {
    this->noClusters = noClusters;
    this->binWidth = binWidth;
    this->filename = filename;
}

MZMTIN002::Clusterer::pixel &MZMTIN002::Clusterer::get(unsigned int a, unsigned int b) {
    return pixels[(b * w) + a];
}

