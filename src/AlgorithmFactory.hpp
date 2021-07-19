#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"

class SortAlgorithm;

class AlgorithmFactory {
 public:
  static SortAlgorithm* generateSorter(Algorithm a);
};

#endif