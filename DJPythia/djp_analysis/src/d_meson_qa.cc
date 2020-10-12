#include "../include/d_meson_qa.h"

ParticleQAHistograms::ParticleQAHistograms(std::string name)
    : pt_{(name + "_pt").c_str(), (name + " p_{T};p_{T} [GeV/c];Counts").c_str(),
          200, 0, 100},
      eta_{(name + "_eta").c_str(), (name + " #eta;#eta;Counts").c_str(),
           200, 0, 100},

      production_vertex_x_{
          (name + "_production_vertex_x").c_str(),
          (name + " Production vertex X;Vertex_{X}[mm];Counts").c_str(), 200, 0,
          10},
      production_vertex_y_{
          (name + "_production_vertex_y").c_str(),
          (name + " Production vertex Y;Vertex_{Y}[mm];Counts").c_str(), 200, 0,
          10},
      production_vertex_z_{
          (name + "_production_vertex_Z").c_str(),
          (name + " Production vertex Z;Vertex_{Z}[mm];Counts").c_str(), 200, 0,
          10}
{}
