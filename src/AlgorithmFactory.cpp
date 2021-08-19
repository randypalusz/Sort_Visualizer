#include "AlgorithmFactory.hpp"

#include <functional>
#include <unordered_map>
#include <memory>

#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"
#include "util/Utility.hpp"

const std::unordered_map<Algorithm, CreationFunction>
    AlgorithmFactory::creators = {
        {Algorithm::BOGO, &getUniquePointer<BogoSort>},
        {Algorithm::BUBBLE, &getUniquePointer<BubbleSort>},
        {Algorithm::QUICK, &getUniquePointer<QuickSort>},
        {Algorithm::QUICK_ITERATIVE, &getUniquePointer<QuickSort_Iterative>},
        {Algorithm::SELECTION, &getUniquePointer<SelectionSort>}};

std::unique_ptr<SortAlgorithm> AlgorithmFactory::generateSorter(Algorithm a) {
  // if (*sorter) delete *sorter;
  std::unique_ptr<SortAlgorithm> sorter;

  try {
    auto fn = creators.at(a);
    sorter = fn();
    return sorter;
  } catch (const std::exception& e) {
    std::cerr
        << "Error - implement enum type in AlgorithmFactory::generateSorter"
        << std::endl;
  }
  return nullptr;
}
