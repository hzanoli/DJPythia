#include <algorithm>
#include <cmath>
#include <string>
#include <utility>

#include "TMath.h"

#include "djp_analysis/task_d.h"

namespace dm = djpythia::data_model;

djpythia::tree_analysis::DMesonQA::DMesonQA(
    std::string name, std::string verbose_name,
    const std::vector<double> &pt_bins, int n_bins_eta, int n_bins_phi,
    int n_bins_vertex, double vertex_min, double vertex_max,
    int n_bins_decay_length)
    : name_(std::move(name)), verbose_name_(std::move(verbose_name)) {
  const std::string pt_name = GetHistName("pt");
  const std::string pt_title = VerboseName() + " p_{T}; p_{T} [GeV/c]; Counts";
  h_pt_ = TH1D(pt_name.c_str(), pt_title.c_str(), int(pt_bins.size() - 1),
               &pt_bins[0]);

  const std::string eta_name = GetHistName("eta");
  const std::string eta_title = VerboseName() + " #eta; #eta; Counts";
  h_eta_ = TH1D(eta_name.c_str(), eta_title.c_str(), n_bins_eta, -10, 10);

  const std::string phi_name = GetHistName("phi");
  const std::string phi_title = (VerboseName() + " #varphi; #varphi; Counts");
  h_phi_ = TH1D(phi_name.c_str(), phi_title.c_str(), n_bins_phi, -TMath::Pi(),
                TMath::Pi());

  const std::string vertex_x_name = GetHistName("vertex_x");
  const std::string vertex_x_title =
      VerboseName() + " Vertex X; Vertex X [mm]; Counts";
  h_vertex_x_ = TH1D(vertex_x_name.c_str(), vertex_x_title.c_str(),
                     n_bins_vertex, vertex_min, vertex_max);

  const std::string vertex_y_name = GetHistName("vertex_y");
  const std::string vertex_y_title =
      VerboseName() + " Vertex Y; Vertex Y [mm]; Counts";
  h_vertex_y_ = TH1D(vertex_y_name.c_str(), vertex_y_title.c_str(),
                     n_bins_vertex, vertex_min, vertex_max);

  const std::string vertex_z_name = GetHistName("vertex_z");
  const std::string vertex_z_title =
      verbose_name + " Vertex Z; Vertex Z [mm]; Counts";
  h_vertex_z_ = TH1D(vertex_z_name.c_str(), vertex_z_title.c_str(),
                     n_bins_vertex, vertex_min, vertex_max);

  const std::string vertex_x_y_name = GetHistName("vertex_xy");
  const std::string vertex_x_y_title =
      VerboseName() +
      " Vertex X vs Vertex Y; Vertex X [mm]; Vertex Y [mm]; Counts";
  h_vertex_x_y_ =
      TH2D(vertex_x_y_name.c_str(), vertex_x_y_title.c_str(), n_bins_vertex,
           vertex_min, vertex_max, n_bins_vertex, vertex_min, vertex_max);

  const std::string decay_length_name = GetHistName("decay_length");
  const std::string decay_length_title =
      VerboseName() + " Decay Length; Decay Length [mm]; Counts";
  h_decay_length_ = TH1D(decay_length_name.c_str(), decay_length_title.c_str(),
                         n_bins_decay_length, 0, 100);

  h_decay_length_primary_vertex_ =
      TH1D(decay_length_name.c_str(), decay_length_title.c_str(),
           n_bins_decay_length, 0, 100);
}

void djpythia::tree_analysis::DMesonQA::Fill(
    const data_model::DMeson &particle) {
  HistPt().Fill(particle.Pt());
  HistEta().Fill(particle.Eta());
  HistPhi().Fill(particle.Phi());

  HistVertexX().Fill(particle.VertexX());
  HistVertexY().Fill(particle.VertexY());
  HistVertexZ().Fill(particle.VertexZ());

  HistVertexXY().Fill(particle.VertexX(), particle.VertexY());

  HistDecayLength().Fill(particle.DecayLength());
  HistDecayLengthPrimary().Fill(particle.DecayLengthToPrimaryVertex());
}

void djpythia::tree_analysis::DMesonQA::Save(TList &output_list) {
  output_list.Add(&HistPt());
  output_list.Add(&HistEta());
  output_list.Add(&HistPhi());
  output_list.Add(&HistVertexX());
  output_list.Add(&HistVertexY());
  output_list.Add(&HistVertexZ());
  output_list.Add(&HistVertexXY());
  output_list.Add(&HistDecayLength());
}
std::string djpythia::tree_analysis::DMesonQA::GetHistName(
    const std::string &feature) const {
  return Name() + "_" + feature;
}

void djpythia::tree_analysis::TaskD::CreateOutput() {
  dmeson_qa_ = DMesonQA(Name(), VerboseName());
}
void djpythia::tree_analysis::TaskD::Execute(
    const djpythia::data_model::Event &event) {
  Task::Execute(event);

  std::vector<dm::DMeson> d_mesons;

  for (const dm::DMeson &d : event.Dmesons()) {
    if (std::abs(d.PdgCode()) == PDGCode())
      d_mesons.push_back(d);
  }

  for (const dm::DMeson &d : d_mesons) {
    dmeson_qa_.Fill(d);
  }
}
void djpythia::tree_analysis::TaskD::SaveOutput(TFile &file) {
  Task::SaveOutput(file);
  file.cd();
  TList output;
  dmeson_qa_.Save(output);
  output.Write(Name().c_str(), 1);
}
