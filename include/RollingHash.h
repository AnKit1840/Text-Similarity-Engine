#ifndef ROLLING_HASH_H
#define ROLLING_HASH_H

#include <cstdint>
#include <string>
#include <vector>

// 64-bit Rabin-Karp rolling hash for k-grams
class RollingHash {
public:
    explicit RollingHash(size_t k);

    vector<uint64_t> computeHashes(const vector<string>& tokens) const;

private:
    size_t k_;
    static constexpr uint64_t BASE = 31;

    static uint64_t hashToken(const string& token);
};

#endif // ROLLING_HASH_H
