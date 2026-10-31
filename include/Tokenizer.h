#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer {
public:
    static vector<string> tokenize(const string& filepath);

private:
    static string normalize(const string& word);
};

#endif // TOKENIZER_H
