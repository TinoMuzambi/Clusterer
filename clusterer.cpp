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

MZMTIN002::Clusterer::Clusterer() {
    w = 0;
    h = 0;
    this->noClusters = 0;
    this->binWidth = 0;
    this->filename = "";
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

vector<unsigned int> MZMTIN002::Clusterer::generateHistogram(const vector<unsigned char>& grayPixels) const {
    vector<unsigned int> histogram;
    int noEntries = (256 % binWidth == 0) ? 256 / binWidth : 256 / binWidth + 1;
    histogram.reserve(noEntries);
    for (int i = 0; i < noEntries; ++i) {
        histogram.push_back(0);
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

vector<MZMTIN002::Clusterer::hist> MZMTIN002::Clusterer::kMeans(vector <hist> hists, int noIterations) {
    vector<vector<unsigned int>> centroids; // Initialising the clusters.
    srand(time(0));
    centroids.reserve(noClusters);

    for (int i = 0; i < noClusters; ++i) {
        hist tempHist = hists.at(rand() % hists.size());
        tempHist.clusterID = i;
        centroids.push_back(tempHist.histogram);
    }

    for (auto& hist : hists) { // Assign each data point to one of K clusters.
        hist.clusterID = rand() % noClusters;
    }

    cout << "Before k-means" << endl;
    for (int i = 0; i < noClusters; ++i) {
        cout << "cluster" << i << ": ";
        for (auto& cluster : hists) {
            if (cluster.clusterID == i) {
                cout << cluster.name << " ";
            }
        }
        cout << endl;
        cout << endl;
    }

    //BEGIN OF LOOP
    cout << "0" << endl;
    for (int i = 0; i < noIterations; ++i) {
        cout << "1" << endl;
        for (auto& hist : hists) {
            for (int j = 0; j < centroids.size(); ++j) {
                double dist = hist.histDistance(centroids[j]);
                if (dist < hist.minDistance) {
                    hist.minDistance = dist;
                    hist.clusterID = j;
                }
            }
        }

        vector<vector<unsigned int>> newCentroids; // here
        newCentroids.reserve(noClusters);
        vector<unsigned int> newCentroid; // essentially a new histogram
        newCentroid.reserve(centroids[0].size());
        vector<int> noCentroids;
        noCentroids.reserve(noClusters);
        cout << "2" << endl;
        for (int k = 0; k < centroids[0].size(); ++k) {
            newCentroid.push_back(0);
        }
        for (int l = 0; l < noClusters; ++l) {
            newCentroids.push_back(newCentroid);
        }
        for (int m = 0; m < noClusters; ++m) {
            noCentroids.push_back(0);
        }

        cout << "3" << endl;
        for (auto& hist : hists) {
            for (int j = 0; j < centroids.size(); ++j) {
                if (hist.clusterID == j) {
                    noCentroids[j]++;
                    for (int k = 0; k < centroids.size(); ++k) {
                        newCentroids[j][k] += hist.histogram[k];
                    }
                }
            }
        }

        cout << "4" << endl;
        for (auto& nCentroid : newCentroids) {
            for (int j = 0; j < nCentroid.size(); ++j) {
                if (noCentroids[j] != 0) {
                    nCentroid[j] /= noCentroids[j];
                }
            }
        }

        cout << "5" << endl;
        for (int n = 0; n < newCentroids.size(); ++n) {
            cout << n << endl;
            centroids.at(n) = newCentroids[n];
        }
        cout << "6" << endl;
    }

    cout << "7" << endl;

    return hists;
}

void MZMTIN002::Clusterer::setNoClusters(int noClustersToSet) {
    this->noClusters = noClustersToSet;
}
