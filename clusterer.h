// MZMTIN002

#ifndef ASSIGNMENT_4_CLUSTERER_H
#define ASSIGNMENT_4_CLUSTERER_H

#endif //ASSIGNMENT_4_CLUSTERER_H

using namespace std;
#include "iostream"
#include <cmath>
#include <cstring>
#include <fstream>
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

        vector<unsigned int> generateHistogram(const vector<unsigned char>& grayPixels) const; // generate histogram to be used for clustering.

        pixel& get(unsigned int a, unsigned int b, vector<pixel>& myPixel) const; // get pixel data at (a, b)
    };
}