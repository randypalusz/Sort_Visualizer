#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <vector>
#include <string>

class VectorGenerator {
 public:
  static std::vector<int> loadFromFile(const std::string& fileName);
  static std::vector<int> generateGivenSize(size_t size);
};

#endif
