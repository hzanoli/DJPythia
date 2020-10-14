#ifndef DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_H_
#define DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_H_

#include "TFile.h"
#include "djp_data_model/event.h"

namespace djpythia {
namespace tree_analysis {
/* Class that represents an analysis Task, defining the basic interfaces with
 * the analysis manager.*/
class Task {
public:
  Task() = default;
  virtual void CreateOutput() {};
  virtual void Execute(const djpythia::data_model::Event& event){};
  virtual void Terminate() { };
  virtual void SaveOutput(TFile &file){ };
};
}
}


#endif // DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_H_
