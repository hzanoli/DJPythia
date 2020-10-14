#include "djp_analysis/analysis_manager.h"

namespace dm = djpythia::data_model;
namespace dta = djpythia::tree_analysis;

void djpythia::tree_analysis::AnalysisManager::PerformAnalysis() {

  for (const std::unique_ptr<dta::Task>& task: tasks_) {
    task->CreateOutput();
  }

  for (const dm::Event& event: reader_) {
    for (const std::unique_ptr<dta::Task>& task: tasks_) {
      task->Execute(event);
    }
  }

  for (const std::unique_ptr<dta::Task>& task: tasks_) {
    task->Terminate();
  }

  for (const std::unique_ptr<dta::Task>& task: tasks_) {
    task->SaveOutput(output_file_);
  }
}
