#include "Utility.hpp"

#include <vector>
#include <string>
#include <stdlib.h>

std::vector<int> VectorGenerator::generateGivenSize(size_t size) {
  const int max = 100;
  const int min = 1;
  std::vector<int> out{};
  for (int i = 0; i < size; i++) {
    out.push_back(rand() % max + min);
  }
  return out;
}