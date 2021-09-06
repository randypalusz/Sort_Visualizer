#include "Utility.hpp"

#include <algorithm>
#include <random>
#include <string>
#include <stdlib.h>
#include <vector>

// initializing static members
std::random_device VectorGenerator::rd{};
std::mt19937 VectorGenerator::g{rd()};

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
  std::shuffle(std::begin(out), std::end(out), g);
  return out;
}

std::vector<int> VectorGenerator::generateContinuousGivenSize(size_t size) {
  std::vector<int> out{};
  for (int i = 0; i < size; i++) {
    out.push_back(i);
  }
  std::shuffle(std::begin(out), std::end(out), g);
  return out;
}