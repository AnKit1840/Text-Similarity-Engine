#include "Detector.h"
#include "Tokenizer.h"
#include "RollingHash.h"
#include "ShingleEngine.h"
#include "LCSAnalyzer.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string Detector::getRiskLevel(double score) {
    if (score >= 75.0)  return "High Similarity Detected";
    if (score >= 50.0)  return "Moderate Similarity";
    if (score >= 25.0)  return "Low Similarity";
    return "Minimal / No Similarity";
}

void Detector::run(const string& fileA, const string& fileB) {
    // 1. Tokenize
    vector<string> tokensA = Tokenizer::tokenize(fileA);
    vector<string> tokensB = Tokenizer::tokenize(fileB);

    // 2. Rolling hash
    RollingHash hasher(K_GRAM_SIZE);
    vector<uint64_t> hashesA = hasher.computeHashes(tokensA);
    vector<uint64_t> hashesB = hasher.computeHashes(tokensB);

    // 3. Shingle sets
    auto setA = ShingleEngine::buildHashSet(hashesA);
    auto setB = ShingleEngine::buildHashSet(hashesB);

    // 4. Jaccard similarity
    double jaccard = ShingleEngine::jaccardSimilarity(setA, setB);
    double scorePercent = jaccard * 100.0;

    // 5. LCS analysis
    size_t lcsLength = LCSAnalyzer::computeLCS(tokensA, tokensB);
    double lcsCoverage = 0.0;
    if (!tokensA.empty() || !tokensB.empty()) {
        size_t maxTokens = max(tokensA.size(), tokensB.size());
        lcsCoverage = (static_cast<double>(lcsLength) / static_cast<double>(maxTokens)) * 100.0;
    }

    // 6. Report
    cout << fixed << setprecision(2);
    cout << "================================================" << endl;
    cout << "         C++ TEXT SIMILARITY DETECTOR          " << endl;
    cout << "================================================" << endl;
    cout << "File 1: " << fileA
         << " (" << tokensA.size() << " tokens, "
         << setA.size() << " shingles)" << endl;
    cout << "File 2: " << fileB
         << " (" << tokensB.size() << " tokens, "
         << setB.size() << " shingles)" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "TEXT SIMILARITY SCORE: " << scorePercent << "%" << endl;
    cout << "RISK LEVEL: " << getRiskLevel(scorePercent) << endl;
    cout << "------------------------------------------------" << endl;
    cout << "SECONDARY LCS ANALYSIS (Two-Row DP):" << endl;
    cout << "- Longest Common Token Subsequence: "
         << lcsLength << " tokens" << endl;
    cout << "- Sequence Coverage Match: "
         << lcsCoverage << "%" << endl;
    cout << "================================================" << endl;
}
