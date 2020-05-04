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
        Clusterer(const string &filename, int noClusters, int binWidth); // constructor

        bool readImageData(); // read image data into vector of pixel.

        vector<unsigned char> makeGrayscale(); // convert image into grayscale and store in vector of unsigned chars.

        unsigned int * generateHistogram(const vector<unsigned char>& grayPixels) const; // generate histogram to be used for clustering.

        pixel& get(unsigned int a, unsigned int b, vector<pixel>& myPixel) const; // get pixel data at (a, b)

        struct hist {
            vector<unsigned int> histogram;
            int cluster;
            double distance;
            double mean;

            hist():
                cluster(-1),
                distance(__DBL_MAX__) {}

            hist(vector<unsigned int> histogram):
                histogram(move(histogram)),
                cluster(-1),
                distance(__DBL_MAX__),
                mean(__DBL_MAX__) {}

            double histMean() {
                unsigned int sum = 0;
                for (auto i : histogram) {
                    sum += i;
                }

                return sum*(1.0) / histogram.size();
            }

            double histDistance(double otherMean) const {
                return abs(mean - otherMean);
            }
        };

        int getSize() const; // return total number of pixels, width * height
    };
}