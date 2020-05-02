// MZMTIN002

#include "clusterer.h"

void MZMTIN002::Clusterer::grayscale() {
    ifstream ppm;
    ppm.open(filename + "eight_1.ppm", ios::binary);
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

    cout << w << h << b << endl;
    pixel colours{};
    auto** image = new pixel* [w];

    for (int i = 0; i < w; i++) {
        image[i] = new pixel[h];
    }
    for (auto i = 0; i < h; i++) {
        for (auto j = 0; j < w; j++) {
            ppm >> colours.r >> colours.g >> colours.b;
            cout << colours.r << colours.g << colours.b << endl;
            image[j][i] = colours;
        }
    }
    ppm.close();

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cout << image[i][j].r << " " << image[i][j].g << " " << image[i][j].b;
        }
        cout << endl;
    }

    for (int j = 0; j < w; j++) {
        delete [] image[j];
    }

    //Delete image.
    delete [] image;
}

MZMTIN002::Clusterer::Clusterer(const string &filename, const int noClusters, const int binWidth) {
    this->noClusters = noClusters;
    this->binWidth = binWidth;
    this->filename = filename;
}

