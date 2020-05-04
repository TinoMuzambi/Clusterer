// MZMTIN002

#include "clusterer.h"

bool MZMTIN002::Clusterer::readImageData() {
    ifstream ppm;
    ppm.open(filename);
    if (ppm.fail()) {
        cout << "Nah nigga" << endl;
        return false;
    }
    string header;
    int b;
    ppm >> header;
    if (strcmp(header.c_str(), "P6") != 0) {
        cout << "Not P6 it's " << header << endl;
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
//    for (unsigned int i = 0; i < h; i++) {
//        for (unsigned int j = 0; j < w; j++) {
//            pixel& ref_colour = get(j, i, pixels);
//            cout << "RGB {" << (int)ref_colour.r << ", " << (int)ref_colour.g << ", " << (int)ref_colour.b << "}" << endl;
//        }
//    }

    return true;
}

MZMTIN002::Clusterer::Clusterer(const string &filename, const int noClusters, const int binWidth) {
    w = 0;
    h = 0;
    this->noClusters = noClusters;
    this->binWidth = binWidth;
    this->filename = filename;
}

MZMTIN002::Clusterer::pixel &MZMTIN002::Clusterer::get(unsigned int a, unsigned int b, vector<pixel>& myPixel) const {
    return myPixel[(b * w) + a];
}

vector<unsigned char> MZMTIN002::Clusterer::makeGrayscale() {
    vector<unsigned char> grayPixels;
    grayPixels.reserve(w * h);
for (int i = 0; i < w * h; ++i) {
        grayPixels.push_back((pixels[i].r * 0.21) + (pixels[i].g * 0.72) + (pixels[i].b * 0.07));
    }
    return grayPixels;
}

unsigned int * MZMTIN002::Clusterer::generateHistogram(const vector<unsigned char>& grayPixels) const {
    unsigned int* histogram;
    int noEntries = (256 % binWidth == 0) ? 256 / binWidth : 256 / binWidth + 1;
    histogram = new unsigned int[noEntries];
    for (int i = 0; i < noEntries; ++i) {
        histogram[i] = 0;
    }
    for (unsigned char grayPixel : grayPixels) {
        int pos = grayPixel / binWidth;
        histogram[pos] += 1;
    }

    return histogram;
}

int MZMTIN002::Clusterer::getSize() const {
    return w * h;
}

MZMTIN002::Clusterer::Clusterer() {

}

void MZMTIN002::Clusterer::kMeans(vector <hist> hists, int noIterations) {
    vector<hist> centroids; // Initialising the clusters

    srand(time(0));
    for (int i = 0; i < noClusters; ++i) {
        centroids.push_back(hists.at(rand() % noClusters));
    }

    for (auto iter = begin(centroids); iter != end(centroids); iter++) { // Assigning points to a cluster
        int clusterID = iter - begin(centroids);

        for (auto iter2 = hists.begin(); iter2 != hists.end(); iter2++) {
            hist hist = *iter2;
            double dist = iter->histDistance(hist);
            if (dist < hist.minDistance) {
                hist.minDistance = dist;
                hist.clusterID = clusterID;
            }
            *iter2 = hist;
        }

    }
}
