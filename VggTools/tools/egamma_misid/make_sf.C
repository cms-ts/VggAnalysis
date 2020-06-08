#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TFile.h"
#include "Riostream.h"
#include "TMath.h"
#include "TROOT.h"

void make_sf(int year, bool isQCD) {

  string sqcd = "";
  if (isQCD) sqcd = "_qcd";

  TFile * f_ref = new TFile(("../../macros/html/egamma_v6/reference/final_data" + sqcd + "_TP_DCB_" + std::to_string(year) + ".root").c_str());
  TFile * f_pup = new TFile(("../../macros/html/egamma_v6/pileup_up/final_data" + sqcd + "_TP_DCB_" + std::to_string(year) + ".root").c_str());
  TFile * f_pdo = new TFile(("../../macros/html/egamma_v6/pileup_down/final_data" + sqcd + "_TP_DCB_" + std::to_string(year) + ".root").c_str());

  TH2D * h_ref = (TH2D*)f_ref->Get("EGamma_SF2D");
  TH2D * h_pup = (TH2D*)f_pup->Get("EGamma_SF2D");
  TH2D * h_pdo = (TH2D*)f_pdo->Get("EGamma_SF2D");

  string root_title = "../../macros/html/egamma_v6/scale_factors/sf_eg_misid" + sqcd + "_" + std::to_string(year) + "_v6.root";

  TFile * file_root = new TFile((root_title).c_str(), "RECREATE");
  h_ref->Write("EGamma_SF2D");
  h_pup->Write("EGamma_SF2D_pileup_up");
  h_pdo->Write("EGamma_SF2D_pileup_down");
  file_root->Close();

}
