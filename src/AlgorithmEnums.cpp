#include "AlgorithmEnums.hpp"
#include "AlgorithmFactory.hpp"

Algorithm& operator++(Algorithm& a, int) {
  std::vector<Algorithm> algorithmVector{};
  for (const auto& kv : AlgorithmFactory::creators) {
    algorithmVector.push_back(kv.first);
  }
  auto it = std::find(algorithmVector.begin(), algorithmVector.end(), a);
  // if found
  if (it != algorithmVector.end()) {
    // if is last element
    if (std::distance(it, algorithmVector.end()) == 1) {
      a = algorithmVector.at(0);
    } else {
      a = *(++it);
    }
  }
  return a;
}