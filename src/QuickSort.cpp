#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

void QuickSort_Iterative::startSortThread(GraphDisplay* display, std::vector<int>& in) {
  m_thread = std::thread(&QuickSort_Iterative::sort, this, display);
}

void QuickSort_Iterative::sort(GraphDisplay* display) {
#define MAX_LEVELS 300
  int piv, beg[MAX_LEVELS], end[MAX_LEVELS], i = 0, L, R, swap;

  beg[0] = 0;
  end[0] = display->getVecSize();
  display->watch(&piv, sf::Color::Green);
  display->watch(&L, sf::Color::Red);
  display->watch(&R, sf::Color::Red);
  while (i >= 0) {
    L = beg[i];
    R = end[i] - 1;
    if (L < R) {
      piv = display->at(L);
      while (L < R) {
        while (display->at(R) >= piv && L < R) R--;
        if (L < R) {
          display->swap(L++, R);
          if (handleAtomics(display)) return;
        }
        while (display->at(L) <= piv && L < R) L++;
        if (L < R) {
          display->swap(R--, L);
          if (handleAtomics(display)) return;
        }
      }
      display->at(L) = piv;
      if (handleAtomics(display)) return;
      beg[i + 1] = L + 1;
      end[i + 1] = end[i];
      end[i++] = L;
      if (end[i] - beg[i] > end[i - 1] - beg[i - 1]) {
        swap = beg[i];
        beg[i] = beg[i - 1];
        beg[i - 1] = swap;
        swap = end[i];
        end[i] = end[i - 1];
        end[i - 1] = swap;
      }
    } else {
      i--;
    }
  }
  display->reset();
  setState(AlgorithmState::INACTIVE);
}

void QuickSort::startSortThread(GraphDisplay* display, std::vector<int>& in) {
  m_thread = std::thread(&QuickSort::sort, this, display);
}

void QuickSort::sort(GraphDisplay* display) {
  quicksort(display, 0, display->getVecSize() - 1);
  display->reset();
  setState(AlgorithmState::INACTIVE);
}

bool QuickSort::quicksort(GraphDisplay* display, int lo, int hi) {
  if (lo < hi) {
    int partitionIndex = this->partition(display, lo, hi);
    // if updateDisplay returns false (close event found), keep returning false
    // up the tree until back in main
    if (partitionIndex == -1) return false;
    if (!this->quicksort(display, lo, partitionIndex - 1)) return false;
    if (!this->quicksort(display, partitionIndex + 1, hi)) return false;
  }
  return true;
}

int QuickSort::partition(GraphDisplay* display, int lo, int hi) {
  int pivot = display->at(hi);
  display->mark(pivot, sf::Color::Green);
  int leftPtr = lo;
  int rightPtr = lo;
  display->watch(&leftPtr, sf::Color::Red);
  display->watch(&rightPtr, sf::Color::Red);
  for (; rightPtr <= hi; rightPtr++) {
    if (handleAtomics(display)) return -1;
    if (display->at(rightPtr) < pivot) {
      display->swap(leftPtr, rightPtr);
      if (handleAtomics(display)) return -1;
      leftPtr++;
    }
  }
  display->swap(leftPtr, hi);
  display->reset();
  return leftPtr;
}