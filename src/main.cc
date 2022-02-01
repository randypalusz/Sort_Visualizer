#include <stdlib.h>
#include <iostream>

#include "Application.hpp"
#include "ApplicationProperties.hpp"

int main(int argc, char** argv) {
  if (argc > 1) {
    ApplicationProperties::numElements = atoi(argv[1]);
    ApplicationProperties::delay = atof(argv[2]);
  }
  Application app{};
  app.run();
}