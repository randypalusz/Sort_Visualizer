#include <iostream>
#include <thread>
#include <vector>

#include "GraphDisplay.hpp"
#include "SortAlgorithm.hpp"

void CocktailSort::startSortThread(GraphDisplay* display,
                                   std::vector<int>& in) {
  m_thread = std::thread(&CocktailSort::sort, this, display);
}

void CocktailSort::sort(GraphDisplay* display) {
  // TODO: basic case done, but use two pointers to keep shortening the area
  // traversed
  bool swapped = false;
  do {
    swapped = false;
    int i;
    for (i = 0; i < display->getVecSize() - 2; i++) {
      display->watch(&i, sf::Color::Red);
      if (display->at(i) > display->at(i + 1)) {
        display->mark(i + 1, sf::Color::Green);
        if (handleAtomics(display)) {
          return;
        }
        display->swap(i, i + 1, true);
        swapped = true;
      }
      if (handleAtomics(display)) {
        return;
      }
      display->unmark(i + 1);
    }
    if (!swapped) {
      break;
    }
    for (i = display->getVecSize() - 2; i >= 0; i--) {
      if (display->at(i) > display->at(i + 1)) {
        display->mark(i + 1, sf::Color::Green);
        if (handleAtomics(display)) {
          return;
        }
        display->swap(i, i + 1, true);
        swapped = true;
      }
      if (handleAtomics(display)) {
        return;
      }
      display->unmark(i + 1);
    }
  } while (swapped);
  display->unwatchAll();
  return;
}