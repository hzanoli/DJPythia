#ifndef DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_H_
#define DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_H_

namespace djpythia {
namespace tree_analysis {
/* Class that represents an analysis Task, defining the basic interfaces with
 * the analysis manager.*/
class Task {
public:
  Task() = default;
  void virtual CreateOutput() {};
  void virtual Execute() {};
  void virtual Terminate() {};
};
}
}


#endif // DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_H_
