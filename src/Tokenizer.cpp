#include "Tokenizer.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>

using namespace std;

string Tokenizer::normalize(const string& word) {
    string result;
    result.reserve(word.size());

    for (char ch : word) {
        if (isalnum(static_cast<unsigned char>(ch))) {
            result += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }
    }

    return result;
}

vector<string> Tokenizer::tokenize(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open file '" + filepath + "'");
    }

    vector<string> tokens;
    string line;

    while (getline(file, line)) {
        istringstream stream(line);
        string word;

        while (stream >> word) {
            string cleaned = normalize(word);
            if (!cleaned.empty()) {
                tokens.push_back(move(cleaned));
            }
        }
    }

    file.close();
    return tokens;
}
