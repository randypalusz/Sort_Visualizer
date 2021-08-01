#include "AlgorithmFactory.hpp"

#include <functional>
#include <unordered_map>

#include "AlgorithmEnums.hpp"
#include "SortAlgorithm.hpp"

std::shared_ptr<SortAlgorithm> AlgorithmFactory::generateSorter(Algorithm a) {
  using CreationFunction = std::function<std::shared_ptr<SortAlgorithm>()>;

  std::unordered_map<Algorithm, CreationFunction> creators{
      {Algorithm::BOGO, []() { return std::make_shared<BogoSort>(); }},
      {Algorithm::BUBBLE, []() { return std::make_shared<BubbleSort>(); }},
      {Algorithm::QUICK, []() { return std::make_shared<QuickSort>(); }},
      {Algorithm::QUICK_ITERATIVE,
       []() { return std::make_shared<QuickSort_Iterative>(); }},
      {Algorithm::SELECTION, []() { return std::make_shared<SelectionSort>(); }},
  };

  try {
    auto fn = creators.at(a);
    return fn();
  } catch (const std::exception& e) {
    std::cerr << "Error - implement enum type in AlgorithmFactory::generateSorter"
              << std::endl;
    return nullptr;
  }

  // switch (a) {
  //   case Algorithm::BUBBLE:
  //     return std::make_shared<BubbleSort>();
  //   case Algorithm::BOGO:
  //     return std::make_shared<BogoSort>();
  //   case Algorithm::SELECTION:
  //     return std::make_shared<SelectionSort>();
  //   case Algorithm::QUICK:
  //     return std::make_shared<QuickSort>();
  //   case Algorithm::QUICK_ITERATIVE:
  //     return std::make_shared<QuickSort_Iterative>();
  // }
  return nullptr;
}
