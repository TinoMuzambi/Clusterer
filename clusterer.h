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
        unsigned char* histogram;
    public:
        Clusterer(const string &filename, int noClusters, int binWidth); // constructor

        bool openFile();

        vector<unsigned char> grayscale();

        void generateHistogram(vector<unsigned char> grayPixels);

        bool inRange(int low, int high, int x);

        pixel& get(unsigned int a, unsigned int b, vector<pixel>& myPixel);
    };
}