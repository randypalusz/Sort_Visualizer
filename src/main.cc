#include <stdlib.h>
#include <iostream>

#include "Application.hpp"
#include "ApplicationProperties.hpp"

int main(int argc, char** argv) {
  const int numElements = atoi(argv[1]);
  const double delay = atof(argv[2]);
  Application app{};
  app.run(numElements, delay);
}