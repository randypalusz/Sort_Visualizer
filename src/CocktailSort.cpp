#include <iostream>
#include <thread>
#include <vector>

#include "GraphDisplay.hpp"
#include "SortAlgorithm.hpp"

void CocktailSort::startSortThread(GraphDisplay* display) {
  m_thread = std::thread(&CocktailSort::sort, this, display);
}

void CocktailSort::sort(GraphDisplay* display) {
  try {
    bool swapped = false;
    int lowerBound = 0;
    int upperBound = display->getVecSize() - 2;
    int i;
    do {
      swapped = false;
      for (i = lowerBound; i < upperBound; i++) {
        display->watch(&i, sf::Color::Red);
        if (display->at(i) > display->at(i + 1)) {
          display->mark(i + 1, sf::Color::Green);
          handleAtomics(display);
          display->swap(i, i + 1, true);
          swapped = true;
        }
        handleAtomics(display);
        display->unmark(i + 1);
      }
      if (!swapped) {
        break;
      }
      for (i = upperBound; i >= lowerBound; i--) {
        if (display->at(i) > display->at(i + 1)) {
          display->mark(i + 1, sf::Color::Green);
          handleAtomics(display);
          display->swap(i, i + 1, true);
          swapped = true;
        }
        handleAtomics(display);
        display->unmark(i + 1);
      }
      lowerBound++;
      upperBound--;
    } while (swapped);
    tearDown(display);
  } catch (AlgorithmException) {
    return;
  }
}