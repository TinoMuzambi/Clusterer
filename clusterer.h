// MZMTIN002

#ifndef ASSIGNMENT_4_CLUSTERER_H
#define ASSIGNMENT_4_CLUSTERER_H

#endif //ASSIGNMENT_4_CLUSTERER_H

using namespace std;
#include "iostream"
#include <cmath>
#include <cstring>
#include <fstream>
#include <utility>
#include <vector>

namespace MZMTIN002 {

    class Clusterer {
    private:
        int noClusters, binWidth, w, h;
        string filename;
        char* pixelData{};
        struct pixel {
            unsigned char r;
            unsigned char g;
            unsigned char b;
        };
        vector<pixel> pixels;
    public:
        struct hist {
            vector<unsigned int> histogram;
            string name;
            int clusterID, noEntries;
            double minDistance;

            hist():
                    name(""),
                    clusterID(-1),
                    noEntries(-1),
                    minDistance(__DBL_MAX__) {}

            hist(vector<unsigned int> histogram, int noEntries, string name):
                    histogram(move(histogram)),
                    clusterID(-1),
                    noEntries(noEntries),
                    name(std::move(name)),
                    minDistance(__DBL_MAX__) {}

            double histDistance(const vector<unsigned int>& oHistogram) const {
                double sum = 0;
                for (int i = 0; i < noEntries; ++i) {
                    unsigned int diff = histogram[i] - oHistogram[i];
                    sum += pow(diff, 2.0);
                }
                return sqrt(sum);
            }
        };

        Clusterer();

        Clusterer(const string &filename, int noClusters, int binWidth); // constructor

        void setNoClusters(int noClustersToSet); // set method for noClusters

        vector<hist> clusters;

        friend ostream& operator<< (ostream& os, const Clusterer& kt);

        bool readImageData(); // read image data into vector of pixel.

        vector<unsigned char> makeGrayscale(); // convert image into grayscale and store in vector of unsigned chars.

        vector<unsigned int> generateHistogram(const vector<unsigned char>& grayPixels) const; // generate histogram to be used for clustering.

        void kMeans(vector<hist> hists, int noIterations);

        pixel& get(unsigned int a, unsigned int b, vector<pixel>& myPixel) const; // get pixel data at (a, b)

        int getSize() const; // return total number of pixels, width * height
    };
}