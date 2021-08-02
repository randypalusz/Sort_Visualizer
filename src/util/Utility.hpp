#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "AlgorithmEnums.hpp"
#include "Command.hpp"

template <typename T>
T normalize(const T& val, const T& min, const T& max, const T& newMin,
            const T& newMax) {
  return (newMax - newMin) * ((val - min) / (max - min)) + newMin;
};

template <typename T>
T* getPointer() {
  return new T();
};

// TODO: make this not static so random_device can be reused
class VectorGenerator {
 public:
  static std::vector<int> loadFromFile(const std::string& fileName);
  static std::vector<int> generateGivenSize(size_t size, bool continuous);

 private:
  static std::vector<int> generateContinuousGivenSize(size_t size);
};

#endif
