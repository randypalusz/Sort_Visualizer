#pragma once

#include "Command.hpp"
#include <memory>

// TODO: add command for increasing/decreasing delay;
//       need to add reference to GraphDisplay as input parameter
//       can possibly remove window and input vector as parameters
//       and replace with above
class InputHandler {
 public:
  std::shared_ptr<Command> pollForEvents(sf::RenderWindow& window);

 private:
  std::shared_ptr<Command> buttonV_ =
      std::make_shared<RegenerateVectorCommand>();
  std::shared_ptr<Command> buttonS_ =
      std::make_shared<ChooseNextAlgorithmCommand>();
  std::shared_ptr<Command> buttonQ_ = std::make_shared<EndApplicationCommand>();
  std::shared_ptr<Command> buttonP_ = std::make_shared<PauseCommand>();
  std::shared_ptr<Command> buttonRtArrow_ = std::make_shared<SendStepCommand>();
  std::shared_ptr<Command> buttonUpArrow_ =
      std::make_shared<ChangeDelayCommand>(false);
  std::shared_ptr<Command> buttonDnArrow_ =
      std::make_shared<ChangeDelayCommand>(true);
};