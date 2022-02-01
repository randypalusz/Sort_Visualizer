#ifndef APPLICATION_PROPERTIES_HPP
#define APPLICATION_PROPERTIES_HPP

class ApplicationProperties {
 public:
  inline static bool vectorRegenRestartsSort = true;
  inline static int numElements = 100;
  inline static double delay = 0.01;

 private:
  ApplicationProperties() {}
};

#endif