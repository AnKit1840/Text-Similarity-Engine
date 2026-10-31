# Text Similarity Engine

A C++17 command-line tool that compares two text files and calculates how similar their content is.

The project uses token-based shingling, 64-bit polynomial rolling hashes, Jaccard similarity, and Longest Common Subsequence (LCS) to compare documents.

I built this project to explore how different algorithms can be combined to identify similarities between text documents, while keeping the implementation reasonably efficient.

---

## How It Works

The comparison follows these steps:

1. **Tokenization:** Read both documents, convert text to lowercase, and remove punctuation.
2. **Shingling:** Divide the token sequences into overlapping groups of four consecutive words.
3. **Rolling Hash:** Calculate a 64-bit hash for each shingle using a polynomial rolling hash.
4. **Hash Sets:** Store the shingle hashes in `unordered_set` containers to remove duplicates.
5. **Jaccard Similarity:** Compare the two sets to calculate the proportion of shared shingles.
6. **LCS Analysis:** Run a secondary Longest Common Subsequence analysis to examine how much of the word sequence is preserved between the documents.

---

## Algorithms and Design Decisions

### 1. Tokenization and Shingling

Before comparing documents, the text is normalized by converting it to lowercase and removing punctuation.

After tokenization, I use **4-word shingles**, which are groups of four consecutive words.

For example, the sentence:

`the quick brown fox jumps over`

produces these shingles:

- `the quick brown fox`
- `quick brown fox jumps`
- `brown fox jumps over`

Using groups of words instead of comparing individual words helps capture local context and reduces matches caused by common words appearing independently.

### 2. 64-bit Polynomial Rolling Hash

Each shingle is represented by a numerical hash instead of storing and comparing the complete word sequence repeatedly.

I used a polynomial rolling hash with `BASE = 31` and `uint64_t` for storing hash values.

The main advantage of a rolling hash is that the next window's hash can be calculated using the previous window's hash. This avoids recomputing the hash of all four words for every consecutive shingle.

The rolling hash formula is:

$$
H_{\text{next}} =
(H_{\text{prev}} - H_{\text{old}} \cdot BASE^{k-1})
\cdot BASE + H_{\text{new}}
$$

Unsigned 64-bit arithmetic wraps around modulo \(2^{64}\). This provides a large hash space and makes accidental collisions unlikely in typical use, although collisions are still possible.

### 3. Jaccard Similarity

Once the shingle hashes are generated, they are stored in `unordered_set` containers.

This is useful because Jaccard similarity compares unique elements, so repeated occurrences of the same shingle are counted only once.

The formula is:

$$
J(A,B) = \frac{|A \cap B|}{|A \cup B|} \times 100
$$

To calculate the intersection efficiently, the implementation iterates through the smaller set and checks whether each element exists in the larger set.

This requires an expected \(O(\min(|A|,|B|))\) time for the intersection-counting step, assuming average-case hash table lookups.

### 4. Longest Common Subsequence (LCS)

Jaccard similarity works well when documents share consecutive groups of words. However, inserting or changing a few words can break multiple shingles, even when much of the original text remains.

To get another perspective, I added Longest Common Subsequence (LCS) as a secondary comparison.

LCS finds the longest sequence of tokens that appears in both documents while preserving their relative order.

The standard DP approach uses an \(O(N \times M)\) matrix. However, each DP state only depends on the previous row and the current row's previous column.

Because of this, I implemented LCS using just two rows, `prev` and `curr`.

I also keep the shorter token sequence along the columns, reducing auxiliary space to \(O(\min(N,M))\).

---

## Complexity Analysis

Let \(N\) and \(M\) represent the number of tokens in the two documents.

| Component | Time Complexity | Space Complexity |
|---|---|---|
| Tokenization | \(O(N+M)\)* | \(O(N+M)\) |
| Rolling Hash | \(O(N+M)\)* | \(O(N+M)\) |
| Jaccard Similarity | \(O(N+M)\) average | \(O(N+M)\) |
| LCS Analysis | \(O(N \times M)\) | \(O(\min(N,M))\) |

\*These bounds treat token processing and hash calculations as constant-time per token, assuming bounded token lengths.

---

## Project Structure

```text
Text Similarity Engine/
├── include/
│   ├── Tokenizer.h
│   ├── RollingHash.h
│   ├── ShingleEngine.h
│   ├── LCSAnalyzer.h
│   └── Detector.h
├── src/
│   ├── main.cpp
│   ├── Tokenizer.cpp
│   ├── RollingHash.cpp
│   ├── ShingleEngine.cpp
│   ├── LCSAnalyzer.cpp
│   └── Detector.cpp
├── tests/
│   ├── sample1.txt
│   ├── sample2.txt
│   └── disjoint.txt
├── Makefile
└── README.md
```

---

## Building and Running

### Requirements

- A C++17-compatible compiler (`g++`, `clang++`, or MSVC).
- `make` (optional, if you want to use the Makefile).

### Build

Using Make:

```bash
make
```

Or compile directly using g++:

```bash
g++ -std=c++17 -O2 -Wall -Wextra src/*.cpp -Iinclude -o similarity_detector
```

### Run

Pass the paths of the two text files you want to compare:

```bash
./similarity_detector tests/sample1.txt tests/sample2.txt
```

You can also use:

```bash
make run
```

To remove generated build files:

```bash
make clean
```

---

## Sample Output

```text
================================================
         C++ TEXT SIMILARITY DETECTOR
================================================
File 1: tests/sample1.txt (169 tokens, 166 shingles)
File 2: tests/sample2.txt (171 tokens, 168 shingles)
------------------------------------------------
TEXT SIMILARITY SCORE: 54.12%
RISK LEVEL: Moderate Similarity
------------------------------------------------
SECONDARY LCS ANALYSIS (Two-Row DP):
- Longest Common Token Subsequence: 98 tokens
- Sequence Coverage Match: 57.31%
================================================
```

---

## Limitations

- The tool currently compares two documents at a time.
- Hash collisions are possible, even with 64-bit hashes.
- Small changes to a document can affect multiple overlapping shingles.
- LCS takes \(O(N \times M)\) time, which can become expensive for very large documents.
- The similarity score indicates textual overlap; it does not independently establish plagiarism.

---

## What I Learned

While building this project, I got practical experience with:

- Implementing polynomial rolling hashes and understanding how they can be used for efficient string matching.
- Using `unordered_set` for duplicate removal and average-case constant-time lookups.
- Applying Jaccard similarity to compare sets of text shingles.
- Optimizing dynamic programming space using a two-row LCS implementation.
- Organizing a C++ project into separate classes and source/header files.
- Using Makefiles to simplify compilation and execution.

