#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

void QuickSort_Iterative::sort(GraphDisplay* display, std::vector<int>& in) {
  if (!SortAlgorithm::sortShouldContinue(in)) {
    return;
  }

  // covers case where vector is regenerated before sort completes
  if (m_thread.joinable()) {
    m_threadShouldEnd = false;
    m_thread.join();
    m_threadActive = false;
  }

  display->reset();
  m_threadActive = true;
  m_thread = std::thread(&QuickSort_Iterative::internalSort, this, display);
}

void QuickSort_Iterative::internalSort(GraphDisplay* display) {
#define MAX_LEVELS 300
  int piv, beg[MAX_LEVELS], end[MAX_LEVELS], i = 0, L, R, swap;

  beg[0] = 0;
  end[0] = display->getVecSize();
  display->watch(&piv);
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
          if (threadShouldStop()) return;
        }
        while (display->at(L) <= piv && L < R) L++;
        if (L < R) {
          display->swap(R--, L);
          if (threadShouldStop()) return;
        }
      }
      display->at(L) = piv;
      if (threadShouldStop()) return;
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
  m_threadActive = false;
}

void QuickSort::sort(GraphDisplay* display, std::vector<int>& in) {
  if (!SortAlgorithm::sortShouldContinue(in)) {
    return;
  }
  this->quicksort(display, in, 0, in.size() - 1);
}

bool QuickSort::quicksort(GraphDisplay* display, std::vector<int>& in, int lo,
                          int hi) {
  if (lo < hi) {
    int partitionIndex = this->partition(display, in, lo, hi);
    // if updateDisplay returns false (close event found), keep returning false
    // up the tree until back in main
    if (partitionIndex == -1) return false;
    if (!this->quicksort(display, in, lo, partitionIndex - 1)) return false;
    if (!this->quicksort(display, in, partitionIndex + 1, hi)) return false;
  }
  return true;
}

int QuickSort::partition(GraphDisplay* display, std::vector<int>& in, int lo,
                         int hi) {
  int pivot = in.at(hi);
  int leftPtr = lo;
  for (int rightPtr = lo; rightPtr <= hi; rightPtr++) {
    if (in.at(rightPtr) < pivot) {
      std::swap(in.at(leftPtr), in.at(rightPtr));
      m_activeIndices.insert({leftPtr, rightPtr});
      if (!this->updateDisplay(display, in, m_activeIndices)) return -1;
      leftPtr++;
    }
  }
  std::swap(in.at(leftPtr), in.at(hi));
  m_activeIndices.insert({leftPtr, hi});
  if (!this->updateDisplay(display, in, m_activeIndices)) return -1;
  return leftPtr;
}