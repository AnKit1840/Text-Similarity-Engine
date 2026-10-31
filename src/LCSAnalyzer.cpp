#include "LCSAnalyzer.h"
#include <algorithm>

using namespace std;

size_t LCSAnalyzer::computeLCS(
    const vector<string>& tokensA,
    const vector<string>& tokensB
) {
    if (tokensA.empty() || tokensB.empty()) {
        return 0;
    }

    // Use shorter sequence for columns to minimize memory
    const auto& rows = (tokensA.size() >= tokensB.size()) ? tokensA : tokensB;
    const auto& cols = (tokensA.size() >= tokensB.size()) ? tokensB : tokensA;

    size_t n = rows.size();
    size_t m = cols.size();

// Only two rows are needed because each DP state depends on
// the previous row and the current row's previous column.
// This reduces auxiliary space from O(n*m) to O(min(n,m)).
vector<size_t> prev(m + 1, 0), curr(m + 1, 0);

    for (size_t i = 1; i <= n; ++i) {
        fill(curr.begin(), curr.end(), 0);

        for (size_t j = 1; j <= m; ++j) {
            if (rows[i - 1] == cols[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        
        swap(prev, curr);
    }

    return prev[m];
}
