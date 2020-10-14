#include <iostream>
#include <memory>

#include "boost/program_options.hpp"
#include "djp_analysis/analysis_manager.h"
#include "djp_analysis/task.h"
#include "djp_analysis/task_d.h"
#include "djp_data_model/event.h"

namespace po = boost::program_options;
namespace dta = djpythia::tree_analysis;
namespace dm = djpythia::data_model;

typedef std::unique_ptr<dta::Task> TaskPtr;
typedef std::vector<TaskPtr> TaskPtrVector;

/* Main program. */
int main(int argc, char **argv);

/* Given the variables of the program (input file) and the main program number
 * of arguments and argument values, configures the analysis.
 * Returns whether the program should run or not.*/
bool ConfigureProgram(std::string &input_file, char **argv, int argc) {

  po::options_description options("DJPythia analysis");

  options.add_options()("help", "Produce help message.")(
      "input", po::value(&input_file)->default_value("tree.root"),
      "Set file to read the tree from.");

  po::variables_map variables_map;
  po::store(po::parse_command_line(argc, argv, options), variables_map);
  po::notify(variables_map);

  if (variables_map.count("help")) {
    std::cout << options << "\n";
    return false;
  }
  return true;
}

/* Adds the tasks to be analysed. */
TaskPtrVector AddTasks() {
  TaskPtrVector tasks;

  TaskPtr dplus_task(new dta::TaskD("dplus", "D^{+}", 411));
  tasks.push_back(std::move(dplus_task));

  TaskPtr dstarplus_task(new dta::TaskD("dstarplus", "D^{*+}", 413));
  tasks.push_back(std::move(dstarplus_task));

  TaskPtr d0plus_task(new dta::TaskD("d0plus", "D_{0}(2400)^{+}", 10411));
  tasks.push_back(std::move(d0plus_task));

  TaskPtr d1plus_task(new dta::TaskD("d1plus", "D_{1}(2420)^{+}", 10413));
  tasks.push_back(std::move(d1plus_task));

  TaskPtr d1hplus_task(new dta::TaskD("d1hplus", "D_{1}(H)^{+}", 20413));
  tasks.push_back(std::move(d1hplus_task));

  TaskPtr d2plus_task(new dta::TaskD("d2plus", "D_{2}(2460)^{+}", 415));
  tasks.push_back(std::move(d2plus_task));

  return tasks;
}

int main(int argc, char **argv) {
  TH1::AddDirectory(false);

  std::string input_file;
  std::string tree_name("event_tree");
  std::string branch_name("event");

  bool run = ConfigureProgram(input_file, argv, argc);

  if (!run)
    return 0;

  dta::AnalysisManager analysis_manager(
      input_file, tree_name, branch_name,
      std::function<TaskPtrVector()>(&AddTasks));

  analysis_manager.PerformAnalysis();
}