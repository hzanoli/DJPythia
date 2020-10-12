#include <iostream>
#include <string>

#include "boost/program_options.hpp"

#include "djp_generate/generator.h"
#include "djp_generate/pythia_analysis.h"
#include "djp_data_model/d_meson.h"
#include "djp_data_model/event.h"
#include "djp_data_model/particle.h"

#include "TFile.h"
#include "TTree.h"

namespace po = boost::program_options;
namespace gen = djpythia::generator;
namespace dm = djpythia::data_model;
namespace pan = djpythia::pythia_analysis;
namespace pyt = Pythia8;

/* Main program. */
int main(int argc, char **argv);

/* Given the variables of the program (config, seed, n_events) and the main
 * program number of arguments and argument values, configures the generation
 * of the events. Returns whether the program should run or not.*/
bool ConfigureProgram(std::string &config, int &seed, int &n_events, int argc,
                      char **argv);

/* Given a value and a vector, returns whether abs(value) is in the vector. */
template <typename T> bool IsInAbs(const T &value, std::vector<T> vector) {
  return std::find(vector.begin(), vector.end(), abs(value)) != vector.end();
}

bool ConfigureProgram(std::string &config, int &seed, int &n_events, int argc,
                      char **argv) {

  po::options_description options("Program options");

  options.add_options()("help", "Produce help message.")(
      "config",
      po::value<std::string>(&config)->default_value("/DJPythia/default.cfg"),
      "Set file with the configurations from pythia.")(
      "seed", po::value<int>(&seed)->default_value(13),
      "Set seed to generate the events.")(
      "n_events", po::value<int>(&n_events)->default_value(10),
      "Set how many events should be generated.");

  po::variables_map variables_map;
  po::store(po::parse_command_line(argc, argv, options), variables_map);
  po::notify(variables_map);

  if (variables_map.count("help")) {
    std::cout << options << "\n";
    return false;
  }
  return true;
}

int main(int argc, char **argv) {
  std::string config_file;
  int seed;
  int n_events;

  bool run = ConfigureProgram(config_file, seed, n_events, argc, argv);
  if (!run)
    return 0;

  std::cout << "File: " << config_file << "\n";
  std::cout << "Seed: " << seed << "\n";
  std::cout << "Number of events: " << n_events << "\n";

  // Creates the TTree output
  TFile file("tree.root", "RECREATE");
  TTree tree("event_tree", "Tree with the generated events");
  dm::Event event_for_tree;
  tree.Branch("event", &event_for_tree);

  gen::PythiaGenerator pythia(config_file, seed, n_events);
  std::vector<int> particles_to_save = {411, 10411, 413, 10413, 20413, 415};

  for (const pyt::Event &event : pythia) {
    std::vector<dm::DMeson> dmesons;
    for (const pyt::Particle &particle : event) {
      if (IsInAbs(particle.id(), particles_to_save)) {
        auto part = pan::MakeParticle(particle, event);

        std::vector<dm::Particle> daughters;
        for (auto i : particle.daughterList()) {
          daughters.push_back(pan::MakeParticle(event[i], event));
        }
        dmesons.emplace_back(part, daughters);
      }
    }
    if (!dmesons.empty()) {
      event_for_tree = dm::Event(dmesons);
      tree.Fill();
    }
  }

  tree.Write();
  file.Close();
}
