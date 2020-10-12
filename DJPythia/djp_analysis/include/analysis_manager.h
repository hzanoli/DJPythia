#ifndef DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_ANALYSIS_MANAGER_H_
#define DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_ANALYSIS_MANAGER_H_

#include "task.h"
#include "tree_reader.h"
#include <memory>
#include <utility>
#include <vector>

namespace djpythia {
namespace tree_analysis {
/* Manages a series of analysis. The following protocol is followed:
 * 1.) The used should define a Task and derive it from
 *     djpythia::tree_analysis::Task.
 * 2.) The task should be passed to the Analysis manager in the initialization
 *      or using the function AddTask.
 * 3.) The analysis manager will execute the CreateOutput for each task.
 * 4.) The analysis manager will read each event from the tree reader.
 * 5.) The analysis manager will call Terminate for each task.
 *  */
template <typename Event> class AnalysisManager {
public:
  explicit AnalysisManager(const TreeReader<Event> &reader,
                  std::vector<std::unique_ptr<Task>> tasks =
                      std::vector<std::unique_ptr<Task>>())
      : reader_(reader), tasks_(std::move(tasks)) {}

private:
  djpythia::tree_analysis::TreeReader<Event> reader_;
  std::vector<std::unique_ptr<Task>> tasks_;
};
} // namespace tree_analysis
} // namespace djpythia

#endif // DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_ANALYSIS_MANAGER_H_
