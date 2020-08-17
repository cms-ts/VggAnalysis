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

  TFile * f_ref = new TFile(("../../macros/html/egamma_v7/reference/final_data" + sqcd + "_TP_DCB_" + std::to_string(year) + ".root").c_str());
  TFile * f_pileup_up = new TFile(("../../macros/html/egamma_v7/pileup_up/sf_egamma_misid_data_TP" + sqcd + "_" + std::to_string(year) + ".root").c_str());
  TFile * f_pileup_down = new TFile(("../../macros/html/egamma_v7/pileup_down/sf_egamma_misid_data_TP" + sqcd + "_" + std::to_string(year) + ".root").c_str());
  TFile * f_sf_pho_veto_up = new TFile(("../../macros/html/egamma_v7/sf_pho_veto_up/sf_egamma_misid_data_TP" + sqcd + "_" + std::to_string(year) + ".root").c_str());
  TFile * f_sf_pho_veto_down = new TFile(("../../macros/html/egamma_v7/sf_pho_veto_down/sf_egamma_misid_data_TP" + sqcd + "_" + std::to_string(year) + ".root").c_str());
  TFile * f_sf_pho_eff_up = new TFile(("../../macros/html/egamma_v7/sf_pho_eff_up/sf_egamma_misid_data_TP" + sqcd + "_" + std::to_string(year) + ".root").c_str());
  TFile * f_sf_pho_eff_down = new TFile(("../../macros/html/egamma_v7/sf_pho_eff_down/sf_egamma_misid_data_TP" + sqcd + "_" + std::to_string(year) + ".root").c_str());

  TH2D * h_ref = (TH2D*)f_ref->Get("EGamma_SF2D");
  TH2D * h_pileup_up = (TH2D*)f_pileup_up->Get("EGamma_SF2D");
  TH2D * h_pileup_down = (TH2D*)f_pileup_down->Get("EGamma_SF2D");
  TH2D * h_sf_pho_veto_up = (TH2D*)f_sf_pho_veto_up->Get("EGamma_SF2D");
  TH2D * h_sf_pho_veto_down = (TH2D*)f_sf_pho_veto_down->Get("EGamma_SF2D");
  TH2D * h_sf_pho_eff_up = (TH2D*)f_sf_pho_eff_up->Get("EGamma_SF2D");
  TH2D * h_sf_pho_eff_down = (TH2D*)f_sf_pho_eff_down->Get("EGamma_SF2D");

  string root_title = "../../macros/html/egamma_v7/scale_factors/sf_eg_misid" + sqcd + "_" + std::to_string(year) + "_v7.root";

  TFile * file_root = new TFile((root_title).c_str(), "RECREATE");
  h_ref->Write("EGamma_SF2D");
  h_pileup_up->Write("EGamma_SF2D_pileup_up");
  h_pileup_down->Write("EGamma_SF2D_pileup_down");
  h_sf_pho_veto_up->Write("EGamma_SF2D_sf_pho_veto_up");
  h_sf_pho_veto_down->Write("EGamma_SF2D_sf_pho_veto_down");
  h_sf_pho_eff_up->Write("EGamma_SF2D_sf_pho_eff_up");
  h_sf_pho_eff_down->Write("EGamma_SF2D_sf_pho_eff_down");
  file_root->Close();

}
