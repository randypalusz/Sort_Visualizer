#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"
#include <memory>
#include <functional>

class SortAlgorithm;
enum class Algorithm;

using CreationFunction = std::function<SortAlgorithm*()>;
class AlgorithmFactory {
 public:
  static void generateSorter(Algorithm a, SortAlgorithm** sorter);
  static const std::unordered_map<Algorithm, CreationFunction> creators;
};

#endif