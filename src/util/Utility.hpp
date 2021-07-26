#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <algorithm>
#include <vector>
#include <string>

template <typename T>
T normalize(const T& val, const T& min, const T& max, const T& newMin,
            const T& newMax) {
  return (newMax - newMin) * ((val - min) / (max - min)) + newMin;
};

class VectorGenerator {
 public:
  static std::vector<int> loadFromFile(const std::string& fileName);
  static std::vector<int> generateGivenSize(size_t size, bool continuous);

 private:
  static std::vector<int> generateContinuousGivenSize(size_t size);
};

#endif
