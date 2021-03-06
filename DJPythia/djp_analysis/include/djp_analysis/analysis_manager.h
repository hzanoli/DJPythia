#ifndef DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_ANALYSIS_MANAGER_H_
#define DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_ANALYSIS_MANAGER_H_

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "djp_data_model/event.h"

#include "djp_analysis/task.h"
#include "djp_analysis/tree_reader.h"

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
 * 6.) The analysis manager will call Save for each task.
 *  */
class AnalysisManager {
public:
  explicit AnalysisManager(
      const std::string &file_path, const std::string &tree_name,
      const std::string &branch_name,
      const std::function<std::vector<std::unique_ptr<Task>>()> &add_tasks)
      : reader_(file_path, tree_name, branch_name), tasks_(add_tasks()),
        output_file_("results.root", "RECREATE") {}

  void PerformAnalysis();

private:
  djpythia::tree_analysis::TreeReader<djpythia::data_model::Event> reader_;
  std::vector<std::unique_ptr<Task>> tasks_;
  TFile output_file_;
};

} // namespace tree_analysis
} // namespace djpythia

#endif // DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_ANALYSIS_MANAGER_H_
