#ifndef DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_D_H_
#define DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_D_H_
#include <string>
#include <utility>
#include <vector>

#include "TH1D.h"
#include "TH2D.h"

#include "djp_analysis/task.h"
#include "djp_data_model/particle.h"

namespace djpythia {
namespace tree_analysis {

/* Histograms for a check at single particle level */
class DMesonQA {
public:
  DMesonQA() = default;
  /* Given a name (the one used to represent the histogram on ROOT, eg. dplus)
   * and the verbose name (the actual name, e.g. D^{+}), and the configuration
   * for the binning to fht histograms, builds a new object. */
  DMesonQA(std::string name, std::string verbose_name,
           const std::vector<double>& pt_bins = {0, 1, 2, 3, 4, 6, 8, 16, 24, 36, 50,
                                          100},
           int n_bins_eta = 50, int n_bins_phi = 30, int n_bins_vertex = 100,
           double vertex_min = -10., double vertex_max = 10.,
           int n_bins_decay_length = 1000);
  void Fill(const data_model::DMeson &particle);
  void Save(TList &output_list);

  const std::string &Name() const { return name_; }
  const std::string &VerboseName() const {return verbose_name_;}
  TH1D &HistPt() { return h_pt_; }
  TH1D &HistEta() { return h_eta_; }
  TH1D &HistPhi() { return h_phi_; }
  TH1D &HistVertexX() { return h_vertex_x_; }
  TH1D &HistVertexY() { return h_vertex_y_; }
  TH1D &HistVertexZ() { return h_vertex_z_; }
  TH2D &HistVertexXY() { return h_vertex_x_y_; }
  TH1D &HistDecayLength() { return h_decay_length_; }

private:
  std::string name_;
  std::string verbose_name_;
  TH1D h_pt_;
  TH1D h_eta_;
  TH1D h_phi_;

  TH1D h_vertex_x_;
  TH1D h_vertex_y_;
  TH1D h_vertex_z_;
  TH2D h_vertex_x_y_;

  TH1D h_decay_length_;

  std::string GetHistName(const std::string& feature) const;
};

class TaskD : public Task {
public:
  TaskD(std::string name, std::string verbose_name, int pdg)
      : Task(), name_(std::move(name)), verbose_name_(std::move(verbose_name)),
        pdg_(pdg){};

  TaskD() = default;
  void CreateOutput() override;
  void Execute(const djpythia::data_model::Event &event) override;
  void SaveOutput(TFile &file) override;

  const std::string &Name() const { return name_; }
  const std::string &VerboseName() const { return verbose_name_; }

  int PDG() const { return pdg_; }
  int PDGCode() const { return PDG(); }
  int PdgCode() const { return PDG(); }

private:
  std::string name_;
  std::string verbose_name_;
  int pdg_{};
  DMesonQA dmeson_qa_;
};
} // namespace tree_analysis
} // namespace djpythia

#endif // DJPYTHIA_DJPYTHIA_TREE_ANALYSIS_TASK_D_H_
