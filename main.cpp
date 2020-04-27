// MZMTIN002

using namespace std;
#include "iostream"
#include "string"

int main(int argc, char* argv[]) {
    string dataset;
    string output;
    int noClusters = 10;
    int binWidth = 1;
    if (argc == 2) {
        dataset = argv[1];
    }
    else if (argc == 3) {
        output = argv[2];
    }
    else if (argc == 4) {
        output = argv[2];
        noClusters = stoi(argv[3]);
    }
    else if (argc == 5) {
        output = argv[2];
        noClusters = stoi(argv[3]);
        binWidth = stoi(argv[4]);
    }
    else {
        cout << "Please provide the necessary requirements." << endl;
        return 1;
    }

    return 0;
}
