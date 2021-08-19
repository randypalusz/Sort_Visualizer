#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <random>

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

template <typename T>
std::unique_ptr<T> getUniquePointer() {
  return std::make_unique<T>();
};

class Timing {
 public:
  static void preciseSleep(double seconds);
};

class VectorGenerator {
 public:
  static std::vector<int> loadFromFile(const std::string& fileName);
  static std::vector<int> generateGivenSize(size_t size, bool continuous);

 private:
  static std::vector<int> generateContinuousGivenSize(size_t size);
  static std::random_device rd;
  static std::mt19937 g;
};

#endif
