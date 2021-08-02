#include "InputHandler.hpp"
#include <memory>

std::shared_ptr<Command> InputHandler::pollForEvents(sf::RenderWindow& window) {
  sf::Event event;
  while (window.pollEvent(event)) {
    // "close requested" event: we close the window
    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
        case sf::Keyboard::Q:
          return buttonQ_;
        case sf::Keyboard::S:
          return buttonS_;
        case sf::Keyboard::V:
          return buttonV_;
        default:
          break;
      }
    }
    if (event.type == sf::Event::Closed) {
      // return Command::CLOSE_WINDOW;
      return std::make_shared<CloseWindowCommand>();
    }
  }
  // no handled events found
  // return Command::NO_EVENT;
  return std::make_shared<DoNothingCommand>();
}