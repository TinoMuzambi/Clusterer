// MZMTIN002

using namespace std;

#include <sstream>
#include "iostream"
#include "string"
#include "clusterer.h"

string exec(const string& command) {
    char buffer[128];
    string result;

    // Open pipe to file
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }

    // read till end of process:
    while (!feof(pipe)) {

        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != nullptr)
            result += buffer;
    }

    pclose(pipe);
    return result;
}

int main(int argc, char* argv[]) {
    string dataset;
    string output;
    int noClusters = 10;
    int binWidth = 1;
    if (argc == 2) {
        dataset = argv[1]; // Gradient_Numbers_PPMS/ -bin 70
    }
    else if (argc > 2) {
        dataset = argv[1];
        for (int i = 2; i < argc; i += 2) {
            char curr = string(argv[i])[1];
            if (curr== 'o') {
                output = string(argv[i + 1]);
            }
            else if (curr== 'k') {
                noClusters = stoi(string(argv[i + 1]));
            }
            else if (curr== 'b') {
                binWidth = stoi(string(argv[i + 1]));
            }
        }
    }
    else {
        cout << "Please provide the necessary requirements." << endl;
        return 1;
    }
    static const int noEntries = (256 % binWidth == 0) ? 256 / binWidth : 256 / binWidth + 1;

    string ls = exec("ls " + dataset);
    stringstream line (ls);
    string token;
    vector<string> files;
    while (getline(line, token, '\n')) {
        files.push_back(token);
    }

    MZMTIN002::Clusterer clusterer;
    vector<MZMTIN002::Clusterer::hist> histograms;
    for (const auto & file : files) {
        MZMTIN002::Clusterer clusterer(dataset + file, noClusters, binWidth);
        clusterer.readImageData();

        auto grayPixels = clusterer.makeGrayscale();
//        cout << "Grayscale image" << endl;
//        for (int i = 0; i < clusterer.getSize(); ++i) {
//            cout << int(grayPixels[i])<< " " << endl;
//        }

        unsigned int* histogram = clusterer.generateHistogram(grayPixels);

//        cout << "Histogram #" << i << endl;
//        for (int j = 0; j < noEntries; ++j) {
//            cout << j << " - " << int(histogram[j]) << " " << endl;
//        }

        histograms.emplace_back(MZMTIN002::Clusterer::hist(histogram, noEntries, file));
    }

    clusterer.setNoClusters(noClusters);
    vector<MZMTIN002::Clusterer::hist>  clusters = clusterer.kMeans(histograms, 4);

    cout << "After k-means" << endl;
    for (int i = 0; i < noClusters; ++i) {
        cout << "cluster" << i << ": ";
        for (auto& cluster : clusters) {
            if (cluster.clusterID == i) {
                cout << cluster.name << " ";
            }
        }
        cout << endl;
        cout << endl;
    }

    return 0;
}
