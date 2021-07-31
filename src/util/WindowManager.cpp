#include "Utility.hpp"
#include "AlgorithmEnums.hpp"

// TODO: implement rest of events
WindowEvent WindowManager::pollForEvents(sf::RenderWindow& window) {
  sf::Event event;
  while (window.pollEvent(event)) {
    // "close requested" event: we close the window
    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
        case sf::Keyboard::Q:
          return WindowEvent::CLOSE_WINDOW;
        case sf::Keyboard::S:
          return WindowEvent::NEXT_ALGORITHM;
        case sf::Keyboard::V:
          return WindowEvent::REGENERATE_VECTOR;
        default:
          break;
      }
    }
    if (event.type == sf::Event::Closed) {
      return WindowEvent::CLOSE_WINDOW;
    }
  }
  // no handled events found
  return WindowEvent::NO_EVENT;
}