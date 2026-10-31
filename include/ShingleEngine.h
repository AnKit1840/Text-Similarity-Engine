#ifndef SHINGLE_ENGINE_H
#define SHINGLE_ENGINE_H

#include <cstdint>
#include <unordered_set>
#include <vector>

class ShingleEngine {
public:
    static unordered_set<uint64_t> buildHashSet(const vector<uint64_t>& hashes);

    // Jaccard similarity: |A ∩ B| / |A ∪ B|
    static double jaccardSimilarity(
        const unordered_set<uint64_t>& setA,
        const unordered_set<uint64_t>& setB
    );
};

#endif // SHINGLE_ENGINE_H
