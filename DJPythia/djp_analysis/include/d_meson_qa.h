#ifndef DJPYTHIA_TREE_ANALYSIS_D_MESON_QA_H_
#define DJPYTHIA_TREE_ANALYSIS_D_MESON_QA_H_

#include "TH1D.h"
#include <string>

class ParticleQAHistograms {
private:
  TH1D pt_;
  TH1D eta_;
  TH1D phi_;
  TH1D production_vertex_x_;
  TH1D production_vertex_y_;
  TH1D production_vertex_z_;
public:
  ParticleQAHistograms(std::string name);
};

class DMesonQAHistograms{
};



class DMesonQA {

};

#endif // DJPYTHIA_TREE_ANALYSIS_D_MESON_QA_H_
