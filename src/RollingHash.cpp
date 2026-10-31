#include "RollingHash.h"

using namespace std;

RollingHash::RollingHash(size_t k) : k_(k) {}

uint64_t RollingHash::hashToken(const string& token) {
    uint64_t h = 0;
    for (char ch : token) {
        h = h * BASE + static_cast<uint64_t>(ch);
    }
    return h;
}

vector<uint64_t> RollingHash::computeHashes(const vector<string>& tokens) const {
    if (tokens.size() < k_) {
        return {};
    }

    vector<uint64_t> result;
    result.reserve(tokens.size() - k_ + 1);

    // Pre-hash individual tokens
    vector<uint64_t> tokenHashes(tokens.size());
    for (size_t i = 0; i < tokens.size(); ++i) {
        tokenHashes[i] = hashToken(tokens[i]);
    }

    // BASE^(k - 1)
    uint64_t highPow = 1;
    for (size_t i = 0; i < k_ - 1; ++i) {
        highPow *= BASE;
    }

    // Hash first window
    uint64_t currentHash = 0;
    for (size_t i = 0; i < k_; ++i) {
        currentHash = currentHash * BASE + tokenHashes[i];
    }
    result.push_back(currentHash);

    // Slide window in O(1)
    for (size_t i = 1; i <= tokens.size() - k_; ++i) {
        currentHash = (currentHash - tokenHashes[i - 1] * highPow) * BASE
                      + tokenHashes[i + k_ - 1];
        result.push_back(currentHash);
    }

    return result;
}
