// MZMTIN002

#ifndef ASSIGNMENT_4_CLUSTERER_H
#define ASSIGNMENT_4_CLUSTERER_H

#endif //ASSIGNMENT_4_CLUSTERER_H

using namespace std;
#include "iostream"
#include <cstring>
#include <fstream>
#include <vector>

namespace MZMTIN002 {

    class Clusterer {
    private:
        int noClusters, binWidth, w{}, h{};
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

        bool openFile();

        vector<pixel> grayscale();

        void histogram();

        pixel& get(unsigned int a, unsigned int b, vector<pixel>& myPixel);
    };
}