#ifndef CALORIMETER_H
#define CALORIMETER_H

#include <vector>

using namespace::std;

class Calorimeter {
public:
    Calorimeter(size_t numBlocks, size_t blockSize);

    std::vector<double>& GetBlock(size_t index);

private:
    std::vector<std::vector<double>> blocks;
};

#endif // CALORIMETER_H
