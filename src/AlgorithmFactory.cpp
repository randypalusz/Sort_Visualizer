#include "AlgorithmFactory.hpp"

#include <functional>
#include <unordered_map>

#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"
#include "util/Utility.hpp"

const std::unordered_map<Algorithm, CreationFunction>
    AlgorithmFactory::creators = {
        {Algorithm::BOGO, &getPointer<BogoSort>},
        {Algorithm::BUBBLE, &getPointer<BubbleSort>},
        {Algorithm::QUICK, &getPointer<QuickSort>},
        {Algorithm::QUICK_ITERATIVE, &getPointer<QuickSort_Iterative>},
        {Algorithm::SELECTION, &getPointer<SelectionSort>}};

void AlgorithmFactory::generateSorter(Algorithm a, SortAlgorithm** sorter) {
  if (*sorter) delete *sorter;

  try {
    auto fn = creators.at(a);
    *sorter = fn();
    return;
  } catch (const std::exception& e) {
    std::cerr
        << "Error - implement enum type in AlgorithmFactory::generateSorter"
        << std::endl;
  }
}
