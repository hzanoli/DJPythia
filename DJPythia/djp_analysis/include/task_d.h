#ifndef DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_D_H_
#define DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_D_H_

#include "TH1D.h"
#include "TH2D.h"
#include "djp_data_model/particle.h"
#include "task.h"
#include <string>

namespace djpythia {
namespace tree_analysis {

/* Histograms for a check at single particle level */
class ParticleQA {
  ParticleQA() = default;
  explicit ParticleQA(std::string name,
             std::vector<double> pt_bins = {0, 1, 2, 3, 4, 6, 8, 16, 24, 36, 50,
                                            100},
             int n_eta_bins = 50, int n_phi_bins = 30, int n_bins_vertex = 100,
             double vertex_min = -10., double vertex_max = 10.);

private:
  TH1D h_pt_;
  TH1D h_eta_;
  TH1D h_phi_;

  TH1D h_vertex_x_;
  TH1D h_vertex_y_;
  TH1D h_vertex_z_;
  TH2D h_vertex_xy_;
};

class TaskD : public Task {
public:
  TaskD(std::string name, int pdg);
};
} // namespace tree_analysis
} // namespace djpythia

#endif // DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_D_H_
