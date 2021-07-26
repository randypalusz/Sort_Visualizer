#include "Utility.hpp"

#include <algorithm>
#include <random>
#include <string>
#include <stdlib.h>
#include <vector>

std::vector<int> VectorGenerator::generateGivenSize(size_t size,
                                                    bool continuous) {
  if (continuous) {
    return generateContinuousGivenSize(size);
  }
  const int max = 100;
  const int min = 1;
  std::vector<int> out{};
  for (int i = 0; i < size; i++) {
    out.push_back(rand() % max + min);
  }
  return out;
}

std::vector<int> VectorGenerator::generateContinuousGivenSize(size_t size) {
  std::vector<int> out{};
  for (int i = 0; i < size; i++) {
    out.push_back(i);
  }
  std::shuffle(out.begin(), out.end(), std::default_random_engine());
  return out;
}