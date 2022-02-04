#pragma once

#include <algorithm>
#include <vector>

enum class Algorithm { BUBBLE, SELECTION, QUICK_ITERATIVE, BOGO, QUICK, COCKTAIL };
enum class AlgorithmState {
  SHOULD_END,  // used as a flag from the caller that the sort should end
  INACTIVE,    // state reserved for before the sorting occurs, or when the
               // algorithm completes
  KILLED,      // occurs after SHOULD_END, when the current sort has been
               // terminated preemptively
  PAUSED,      // set when pause command is called
  RUNNING      // set when sort thread is running
};

Algorithm& operator++(Algorithm&, int);

enum class AlgorithmException { END_SORT };