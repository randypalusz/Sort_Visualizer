#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"
#include <memory>

class SortAlgorithm;

class AlgorithmFactory {
 public:
  static std::shared_ptr<SortAlgorithm> generateSorter(Algorithm a);
};

#endif