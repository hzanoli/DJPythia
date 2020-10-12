#include "TMath.h"

#include "../include/task_d.h"
djpythia::tree_analysis::ParticleQA::ParticleQA(
    std::string name, std::vector<double> pt_bins, int n_eta_bins,
    int n_phi_bins, int n_bins_vertex, double vertex_min, double vertex_max)
    : h_pt_((name + " p_{T}").c_str(),
            (name + " p_{T}; p_{T} [GeV/c]; Counts").c_str(),
            int(pt_bins.size() - 1), &pt_bins[0]),
      h_eta_((name + " #eta").c_str(), (name + " #eta; #eta; Counts").c_str(),
             n_eta_bins, -10, 10),
      h_phi_((name + " #varphi").c_str(),
             (name + " #varphi; #varphi; Counts").c_str(), n_phi_bins,
             -TMath::Pi(), TMath::Pi()),
      h_vertex_x_((name + " Vx").c_str(),
                  (name + " Vx; Vx [mm]; Counts").c_str(), n_bins_vertex,
                  vertex_min, vertex_max),
      h_vertex_y_((name + " Vy").c_str(),
                  (name + " Vy; Vy [mm]; Counts").c_str(), n_bins_vertex,
                  vertex_min, vertex_max),
      h_vertex_z_((name + " Vz").c_str(),
                  (name + " Vz; Vz [mm]; Counts").c_str(), n_bins_vertex,
                  vertex_min, vertex_max),
      h_vertex_xy_((name + " Vx x Vy").c_str(),
                   (name + " Vx x Vy; Vx [mm]; Vy [mm]; Counts").c_str(),
                   n_bins_vertex, vertex_min, vertex_max, n_bins_vertex,
                   vertex_min, vertex_max) {}
