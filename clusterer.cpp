// MZMTIN002

#include "clusterer.h"

void MZMTIN002::Clusterer::grayscale() { // TODO skip header
    ifstream raw("Gradient_Numbers_PPMS/five_1.ppm", ios::binary);
    if (!raw) {
        cout << "Nah nigga" << endl;
        return;
    }
    unsigned char ** temp = nullptr;
    temp = new unsigned char*[32];
    for (auto y = 0; y < 32; y++) {
        temp[y] = new unsigned char[32];

        for (auto z = 0; z < 32; z++) {
            temp[y][z] = raw.get();
        }
    }
    raw.close();

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

