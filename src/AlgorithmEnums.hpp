#pragma once

#include <algorithm>
#include <vector>

enum class Algorithm { BUBBLE, SELECTION, QUICK_ITERATIVE, BOGO, QUICK };

Algorithm& operator++(Algorithm&, int);
