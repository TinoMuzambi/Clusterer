// MZMTIN002

using namespace std;

#include <sstream>
#include "iostream"
#include "string"
#include "clusterer.h"

/**
 * Execute terminal commands from within program and return result.
 * In this case, being used to get the names of all the files in the
 * dataset directory.
 * @param command command to be executed in terminal
 * @return output from running command.
 */
string exec(const string& command) {
    char buffer[128];
    string result;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed";
    }

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
        dataset = argv[1];
    }
    else if (argc > 2) {
        dataset = argv[1];
        for (int i = 2; i < argc; i += 2) { // Sorting out i/o.
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
    static const int noEntries = (256 % binWidth == 0)
            ? 256 / binWidth : 256 / binWidth + 1; // number of entries per histogram.

    string ls = exec("ls " + dataset);
    stringstream line (ls);
    string token;
    vector<string> files;
    while (getline(line, token, '\n')) { // populating vector with names of images in the directory.
        if (token.substr(token.length() - 4, token.length()) == ".ppm")
            files.push_back(token);
    }

    MZMTIN002::Clusterer clusterer;
    vector<MZMTIN002::Clusterer::hist> histograms;
    for (const auto & file : files) {
        MZMTIN002::Clusterer clusterer(dataset + file, noClusters, binWidth);
        clusterer.readImageData();

        auto grayPixels = clusterer.makeGrayscale();

        vector<unsigned int> histogram = clusterer.generateHistogram(grayPixels);

        histograms.emplace_back(MZMTIN002::Clusterer::hist(histogram, noEntries, file)); // populating vector of
                                                                            // histograms to perform k-means on
    }

    clusterer.setNoClusters(noClusters);
    clusterer.kMeans(histograms);
    cout << "8" << endl;

    cout << "After k-means" << endl;
    cout << clusterer << endl;

    return 0;
}
