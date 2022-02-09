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
        case sf::Keyboard::P:
          return buttonP_;
        case sf::Keyboard::Right:
          return buttonRtArrow_;
        case sf::Keyboard::Up:
          return buttonUpArrow_;
        case sf::Keyboard::Down:
          return buttonDnArrow_;
        default:
          break;
      }
    }
    if (event.type == sf::Event::Closed) {
      return std::make_shared<EndApplicationCommand>();
    }
  }
  // no handled events found
  return std::make_shared<DoNothingCommand>();
}