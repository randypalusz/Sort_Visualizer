#include "AlgorithmFactory.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"
#include "util/Utility.hpp"

const std::unordered_map<Algorithm, CreationFunction> AlgorithmFactory::creators = {
    {Algorithm::BOGO, &getUniquePointer<BogoSort>},
    {Algorithm::BUBBLE, &getUniquePointer<BubbleSort>},
    {Algorithm::QUICK, &getUniquePointer<QuickSort>},
    {Algorithm::QUICK_ITERATIVE, &getUniquePointer<QuickSort_Iterative>},
    {Algorithm::SELECTION, &getUniquePointer<SelectionSort>},
    {Algorithm::COCKTAIL, &getUniquePointer<CocktailSort>}};

std::unique_ptr<SortAlgorithm> AlgorithmFactory::generateSorter(Algorithm a) {
  std::unique_ptr<SortAlgorithm> sorter;

  try {
    auto fn = creators.at(a);
    sorter = fn();
    return sorter;
  } catch (const std::exception& e) {
    std::cerr << "Error - implement enum type in AlgorithmFactory::generateSorter"
              << std::endl;
  }
  return nullptr;
}
