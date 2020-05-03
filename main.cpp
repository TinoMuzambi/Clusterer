// MZMTIN002

using namespace std;
#include "iostream"
#include "string"
#include "clusterer.h"

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

    MZMTIN002::Clusterer clusterer(dataset, noClusters, binWidth);
    clusterer.readImageData();

    return 0;
}
