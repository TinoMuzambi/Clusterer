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
        int noClusters, binWidth;
        string filename;

        struct pixel {
            int r; // red
            int g; // green
            int b; // blue
        };
    public:
        Clusterer(const string &filename, int noClusters, int binWidth); // constructor

        void grayscale();

        void histogram();
    };
}