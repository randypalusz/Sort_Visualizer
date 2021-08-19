#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include <functional>
#include <memory>
#include <unordered_map>

#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"

class SortAlgorithm;
enum class Algorithm;

using CreationFunction = std::function<std::unique_ptr<SortAlgorithm>()>;
class AlgorithmFactory {
 public:
  static std::unique_ptr<SortAlgorithm> generateSorter(Algorithm a);
  static const std::unordered_map<Algorithm, CreationFunction> creators;
};

#endif