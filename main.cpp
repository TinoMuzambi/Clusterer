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
        dataset = argv[1];
    }
    else if (argc > 2) {
        dataset = argv[1];
        for (int i = 2; i < argc; i++) {
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
            else {
                cout << "Ignoring nonsensical input." << endl;
                break;
            }
        }
    }
    else {
        cout << "Please provide the necessary requirements." << endl;
        return 1;
    }

    MZMTIN002::Clusterer clusterer;
    clusterer.grayscale();

    return 0;
}
