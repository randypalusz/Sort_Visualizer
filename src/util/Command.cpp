#include "Command.hpp"

#include <iostream>

#include "AlgorithmFactory.hpp"
#include "ApplicationProperties.hpp"

bool EndApplicationCommand::execute(GraphDisplay* display,
                                    std::unique_ptr<SortAlgorithm>& sorter,
                                    std::vector<int>* in) {
  display->closeWindow();
  sorter->terminateSort();
  return false;
}

bool RegenerateVectorCommand::execute(GraphDisplay* display,
                                      std::unique_ptr<SortAlgorithm>& sorter,
                                      std::vector<int>* in) {
  if (in) {
    // if sort is running (not paused or killed or otherwise), do not regenerate and do
    // not restart the sort algorithm
    if (ApplicationProperties::vectorRegenRestartsSort) {
      sorter->terminateSort(false);
    }
    if (!ApplicationProperties::maintainPausedState) {
      sorter->setPaused(true);
    }
    std::vector<int> temp = VectorGenerator::generateGivenSize(in->size(), true);
    in->clear();
    in->insert(in->begin(), temp.begin(), temp.end());
    display->regenerateDisplayValues();
  }
  return true;
}

bool ChooseNextAlgorithmCommand::execute(GraphDisplay* display,
                                         std::unique_ptr<SortAlgorithm>& sorter,
                                         std::vector<int>* in) {
  if (sorter) {
    Algorithm a = sorter->getEnumType();
    bool wasPaused = sorter->isPaused();
    a++;
    sorter->terminateSort();
    // TODO: calling std::move seems unnecessary here
    sorter = std::move(AlgorithmFactory::generateSorter(a));
    if (ApplicationProperties::maintainPausedState) {
      sorter->setPaused(wasPaused);
    }
    display->setTitle(sorter->getName());

    // regenerate vector after sorter is generated
    std::vector<int> temp = VectorGenerator::generateGivenSize(in->size(), true);
    in->clear();
    in->insert(in->begin(), temp.begin(), temp.end());
    display->regenerateDisplayValues();
  }
  return true;
}

bool PauseCommand::execute(GraphDisplay* display, std::unique_ptr<SortAlgorithm>& sorter,
                           std::vector<int>* in) {
  sorter->togglePaused();
  return false;
}

bool SendStepCommand::execute(GraphDisplay* display,
                              std::unique_ptr<SortAlgorithm>& sorter,
                              std::vector<int>* in) {
  sorter->setStep();
  return true;
}

bool DoNothingCommand::execute(GraphDisplay* display,
                               std::unique_ptr<SortAlgorithm>& sorter,
                               std::vector<int>* in) {
  return true;
}

bool ChangeDelayCommand::execute(GraphDisplay* display,
                                 std::unique_ptr<SortAlgorithm>& sorter,
                                 std::vector<int>* in) {
  double modValue = (m_increaseDelay) ? 0.002 : -0.002;
  display->changeDelay(modValue);

  return true;
}