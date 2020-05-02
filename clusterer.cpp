// MZMTIN002

#include "clusterer.h"

void MZMTIN002::Clusterer::grayscale() { // TODO skip header
    ifstream ppm;
    ppm.open(filename + "five_1.ppm", ios::binary);
    if (ppm.fail()) {
        cout << "Nah nigga" << endl;
        return;
    }
    string header;
    int w, h, b;
    ppm >> header;
    if (strcmp(header.c_str(), "P6") != 0) {
        return;
    }
    ppm >> w >> h >> b;
    ppm.ignore(256, '\n');

    pixel colours{};
    pixel ** image;
    for (auto y = 0; y < h; y++) {
        for (auto z = 0; z < w; z++) {
            ppm >> colours.r >> colours.g >> colours.b;
            image[z][y] = colours;
        }
    }
    ppm.close();

}

MZMTIN002::Clusterer::Clusterer(const string &filename, const int noClusters, const int binWidth) {
    this->noClusters = noClusters;
    this->binWidth = binWidth;
    this->filename = filename;
}

