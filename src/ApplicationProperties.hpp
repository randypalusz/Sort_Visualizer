#ifndef APPLICATION_PROPERTIES_HPP
#define APPLICATION_PROPERTIES_HPP

// TODO: add json parsing utility to get these at runtime via a txt file
class ApplicationProperties {
 public:
  inline static bool vectorRegenRestartsSort = true;
  inline static bool maintainPausedState = true;
  inline static int numElements = 100;
  inline static double delay = 0.01;

 private:
  ApplicationProperties() {}
};

#endif