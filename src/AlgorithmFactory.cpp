#include "AlgorithmFactory.hpp"
#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"

SortAlgorithm* AlgorithmFactory::generateSorter(Algorithm a) {
  switch (a) {
    case Algorithm::BUBBLE:
      return new BubbleSort();
    case Algorithm::BOGO:
      return new BogoSort();
    case Algorithm::SELECTION:
      return new SelectionSort();
    case Algorithm::QUICK:
      return new QuickSort();
    case Algorithm::QUICK_ITERATIVE:
      return new QuickSort_Iterative();
  }
  return nullptr;
}
