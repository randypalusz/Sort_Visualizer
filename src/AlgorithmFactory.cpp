#include "AlgorithmFactory.hpp"
#include "AlgorithmEnums.hpp"
#include "BubbleSort.hpp"
#include "SortAlgorithm.hpp"

SortAlgorithm* AlgorithmFactory::generateSorter(Algorithm a) {
  switch (a) {
    case Algorithm::BUBBLE:
      return new BubbleSort();
    case Algorithm::SELECTION:
    case Algorithm::QUICK:
      break;
  }
  return nullptr;
}
