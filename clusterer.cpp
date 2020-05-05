// MZMTIN002

#include "clusterer.h"

/**
 * Default constructor.
 */
MZMTIN002::Clusterer::Clusterer() {
    w = 0;
    h = 0;
    MZMTIN002::Clusterer::noClusters = 0;
    this->binWidth = 0;
    this->filename = "";
}

/**
 * Constructor used to create a Clusterer object.
 * @param filename path to an image file.
 * @param noClusters number of clusters to cluster the images into.
 * @param binWidth number of images per histogram.
 */
MZMTIN002::Clusterer::Clusterer(const string &filename, const int noClusters, const int binWidth) {
    w = 0;
    h = 0;
    MZMTIN002::Clusterer::noClusters = noClusters;
    this->binWidth = binWidth;
    this->filename = filename;
}

/**
 * Read binary image data into vector<pixel>.
 * @return true if successful, else false.
 */
bool MZMTIN002::Clusterer::readImageData() {
    ifstream ppm;
    ppm.open(filename);
    if (ppm.fail()) {
        cout << "Unable to open file." << endl;
        return false;
    }
    string header;
    int maxSize;
    ppm >> header;
    if (strcmp(header.c_str(), "P6") != 0) {
        cout << "Not P6 it's " << header << endl;
        return false;
    }
    ppm >> w >> h >> maxSize;
    ppm.ignore(256, '\n'); // Ignore data till the binary block.

    int buffSize = 3 * w * h;
    pixelData = new char[buffSize];
    ppm.read(pixelData, buffSize);

    pixel colours{};
    pixels.clear();
    for (int i = 0; i < buffSize; i += 3) { // reading pixel data into vector of pixels.
        colours.r = pixelData[i];
        colours.g = pixelData[i + 1];
        colours.b = pixelData[i + 2];

        pixels.push_back(colours);
    }

    delete[] pixelData;
    ppm.close();

    return true;
}

/**
 * Convert RGB image into grayscale.
 * @return vector containing converted pixel data.
 */
vector<unsigned int> MZMTIN002::Clusterer::makeGrayscale() {
    vector<unsigned int> grayPixels;
    grayPixels.resize(w * h);
for (int i = 0; i < w * h; ++i) {
        grayPixels.push_back((pixels[i].r * 0.21) + (pixels[i].g * 0.72) + (pixels[i].b * 0.07));
    }
    return grayPixels;
}

/**
 * Use pixel data to generate a histogram of frequencies.
 * @param grayPixels vector of pixel data to make histogram from.
 * @return vector containing frequencies in the histogram.
 */
vector<unsigned int> MZMTIN002::Clusterer::generateHistogram(vector<unsigned int> &grayPixels) const {
    vector<unsigned int> histogram;
    int noEntries = (256 % binWidth == 0) ? 256 / binWidth : 256 / binWidth + 1;
    histogram.resize(noEntries);
    for (int i = 0; i < noEntries; ++i) {
        histogram.push_back(0);
    }
    for (unsigned char grayPixel : grayPixels) {
        int pos = grayPixel / binWidth;
        histogram[pos] += 1;
    }

    return histogram;
}

/**
 * Performs k-means clustering to cluster similar images into clusters.
 * @param hists vector containing histograms of the images that are being clustered.
 */
void MZMTIN002::Clusterer::kMeans(vector <hist> hists) {
    vector<vector<unsigned int>> centroids; // Initialising the clusters.
    srand(time(0));
    centroids.resize(noClusters);

    for (int i = 0; i < noClusters; ++i) {
        hist tempHist = hists.at(rand() % hists.size());
        tempHist.clusterID = i;
        centroids.at(i) = tempHist.histogram;
    }

    for (auto& hist : hists) { // Assign each data point to one of K clusters.
        hist.clusterID = rand() % noClusters;
    }

    clusters = hists;
    cout << "Before k-means" << endl;
    cout << *this << endl;

    //BEGIN OF LOOP
    for (int i = 0; i < 20; ++i) {
        for (auto& hist : hists) {
            for (int j = 0; j < centroids.size(); ++j) {
                double dist = hist.histDistance(centroids[j]);
                if (dist < hist.minDistance) {
                    hist.minDistance = dist;
                    hist.clusterID = j;
                }
            }
        }

        vector<vector<unsigned int>> newCentroids; // here. setting up vectors for new centroids.
        newCentroids.resize(noClusters);
        vector<unsigned int> newCentroid; // essentially a new histogram
        newCentroid.resize(centroids[0].size());
        vector<int> noCentroids;
        noCentroids.resize(noClusters);
        for (int k = 0; k < centroids[0].size(); ++k) {
            newCentroid.at(k) = 0;
        }
        for (int l = 0; l < noClusters; ++l) {
            newCentroids.at(l) = newCentroid;
        }
        for (int m = 0; m < noClusters; ++m) {
            noCentroids.at(m) = 0;
        }

        for (auto& hist : hists) { // summing up values.
            for (int j = 0; j < centroids.size(); ++j) {
                if (hist.clusterID == j) {
                    noCentroids[j]++;
                    for (int k = 0; k < centroids.size(); ++k) {
                        newCentroids.at(j)[k] += hist.histogram[k];
                    }
                }
            }
        }

        for (auto& nCentroid : newCentroids) { // getting the means.
            for (int j = 0; j < nCentroid.size(); ++j) {
                if (noCentroids[j] != 0) {
                    nCentroid[j] /= noCentroids[j];
                }
            }
        }

        newCentroids.swap(centroids);
    }

    clusters = hists; // updating the current clustering.
}

/**
 * Setter method for noClusters instance variable.
 * @param noClustersToSet the updated value.
 */
void MZMTIN002::Clusterer::setNoClusters(int noClustersToSet) {
    this->noClusters = noClustersToSet;
}

/**
 * Overloading the << operator to print out the current clustering of images.
 * @param os the stream to output the data to.
 * @param kt reference to the clusterer object.
 * @return ostream with the data to be printed.
 */
ostream &MZMTIN002::operator<<(ostream &os, const MZMTIN002::Clusterer &kt) {
    for (int i = 0; i < kt.noClusters; ++i) {
        os << "cluster" << i << ": ";
        for (auto& cluster : kt.clusters) {
            if (cluster.clusterID == i) {
                cout << cluster.name << " ";
            }
        }
        os << endl;
        os << endl;
    }
    return os;
}

