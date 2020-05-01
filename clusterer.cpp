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

    unsigned char ** temp = nullptr;
    temp = new unsigned char*[w];
    for (auto y = 0; y < w; y++) {
        temp[y] = new unsigned char[h];

        for (auto z = 0; z < h; z++) {
            temp[y][z] = ppm.get();
        }
    }
    ppm.close();

    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            cout << int(temp[i][j]) << " ";
        }
        cout << endl;
    }
}

MZMTIN002::Clusterer::Clusterer(const string &filename, const int noClusters, const int binWidth) {
    this->noClusters = noClusters;
    this->binWidth = binWidth;
    this->filename = filename;
}

