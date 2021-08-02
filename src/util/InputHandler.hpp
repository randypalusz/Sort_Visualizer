#pragma once

#include "Command.hpp"
#include <memory>

class InputHandler {
 public:
  std::shared_ptr<Command> pollForEvents(sf::RenderWindow& window);

 private:
  std::shared_ptr<Command> buttonV_ =
      std::make_shared<RegenerateVectorCommand>();
  std::shared_ptr<Command> buttonS_ =
      std::make_shared<ChooseNextAlgorithmCommand>();
  std::shared_ptr<Command> buttonQ_ = std::make_shared<CloseWindowCommand>();
};