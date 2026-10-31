#ifndef LCS_ANALYZER_H
#define LCS_ANALYZER_H

#include <string>
#include <vector>

// Space-optimized LCS: O(min(N, M)) auxiliary space
class LCSAnalyzer {
public:
    static size_t computeLCS(
        const vector<string>& tokensA,
        const vector<string>& tokensB
    );
};

#endif // LCS_ANALYZER_H
