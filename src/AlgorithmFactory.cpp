#include "AlgorithmFactory.hpp"

#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"

std::shared_ptr<SortAlgorithm> AlgorithmFactory::generateSorter(Algorithm a) {
  switch (a) {
    case Algorithm::BUBBLE:
      return std::make_shared<BubbleSort>();
    case Algorithm::BOGO:
      return std::make_shared<BogoSort>();
    case Algorithm::SELECTION:
      return std::make_shared<SelectionSort>();
    case Algorithm::QUICK:
      return std::make_shared<QuickSort>();
    case Algorithm::QUICK_ITERATIVE:
      return std::make_shared<QuickSort_Iterative>();
  }
  return nullptr;
}
