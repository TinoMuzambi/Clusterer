// MZMTIN002

using namespace std;

#include <sstream>
#include "iostream"
#include "string"
#include "clusterer.h"

string exec(string command) {
    char buffer[128];
    string result = "";

    // Open pipe to file
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }

    // read till end of process:
    while (!feof(pipe)) {

        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != NULL)
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
        dataset = argv[1]; // Gradient_Numbers_PPMS/ -o data.txt -k 5 -bin 5
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

    string ls = exec("ls " + dataset);
    stringstream line (ls);
    string token;
    vector<string> files;
    while (getline(line, token, '\n')) {
        files.push_back(token);
    }

    vector<vector<unsigned int>> histograms;
    for (int i = 0; i < files.size(); ++i) {
        MZMTIN002::Clusterer clusterer(dataset + files[i], noClusters, binWidth);
        clusterer.readImageData();

        auto grayPixels = clusterer.makeGrayscale();
//        cout << "Grayscale image" << endl;
//        for (int i = 0; i < clusterer.getSize(); ++i) {
//            cout << int(grayPixels[i])<< " " << endl;
//        }

        vector<unsigned int> histogram = clusterer.generateHistogram(grayPixels);

        cout << "Histogram #" << i << endl;
        int noEntries = (256 % binWidth == 0) ? 256 / binWidth : 256 / binWidth + 1;
        for (int i = 0; i < noEntries; ++i) {
            cout << i << " - " << int(histogram[i]) << " " << endl;
        }

        histograms.push_back(histogram);
    }

    cout << "final histogram size: " << histograms.size() << endl;

    return 0;
}
