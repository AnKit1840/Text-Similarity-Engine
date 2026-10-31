#include "ShingleEngine.h"

using namespace std;

unordered_set<uint64_t> ShingleEngine::buildHashSet(const vector<uint64_t>& hashes) {
    return unordered_set<uint64_t>(hashes.begin(), hashes.end());
}

double ShingleEngine::jaccardSimilarity(
    const unordered_set<uint64_t>& setA,
    const unordered_set<uint64_t>& setB
) {
    if (setA.empty() && setB.empty()) {
        return 0.0;
    }

    // Iterate through smaller set to minimize lookups
    const auto& smaller = (setA.size() <= setB.size()) ? setA : setB;
    const auto& larger  = (setA.size() <= setB.size()) ? setB : setA;

    size_t intersection = 0;
    for (const auto& hash : smaller) {
        if (larger.count(hash)) {
            ++intersection;
        }
    }

    size_t unionSize = setA.size() + setB.size() - intersection;
    if (unionSize == 0) {
        return 0.0;
    }

    return static_cast<double>(intersection) / static_cast<double>(unionSize);
}
