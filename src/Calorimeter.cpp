#include "Calorimeter.h"

Calorimeter::Calorimeter(size_t numBlocks, size_t blockSize) {
    blocks.resize(numBlocks, std::vector<double>(blockSize));
}

std::vector<double>& Calorimeter::GetBlock(size_t index) {
    return blocks.at(index);
}
