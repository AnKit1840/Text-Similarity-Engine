#ifndef DETECTOR_H
#define DETECTOR_H

#include <string>


class Detector {
public:
    static void run(const string& fileA, const string& fileB);

private:
    static constexpr size_t K_GRAM_SIZE = 4;
    static string getRiskLevel(double score);
};

#endif // DETECTOR_H
