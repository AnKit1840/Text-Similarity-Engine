#include "Detector.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <file1.txt> <file2.txt>" << endl;
        cerr << "Example: " << argv[0] << " tests/sample1.txt tests/sample2.txt" << endl;
        return 1;
    }

    string fileA = argv[1];
    string fileB = argv[2];

    try {
        Detector::run(fileA, fileB);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
