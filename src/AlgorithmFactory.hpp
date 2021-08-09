#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include <functional>
#include <memory>
#include <unordered_map>

#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"

class SortAlgorithm;
enum class Algorithm;

using CreationFunction = std::function<SortAlgorithm*()>;
class AlgorithmFactory {
 public:
  static void generateSorter(Algorithm a, SortAlgorithm** sorter);
  static const std::unordered_map<Algorithm, CreationFunction> creators;
};

#endif