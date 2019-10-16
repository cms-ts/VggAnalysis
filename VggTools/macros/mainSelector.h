//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 18 12:07:23 2018 by ROOT version 6.14/00
// from TChain Events/
//////////////////////////////////////////////////////////

#ifndef mainSelector_h
#define mainSelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector

#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"

// #define NANOAODv4

#define NANOAODv5

// #define COMPUTE_EG_MISID

// #define RIVET

#if defined(NANOAODv5)
#undef NANOAODv4
#endif // defined(NANOAODv5)

#if defined(mainSelectorDT18_h) || defined(mainSelectorMC18_h)
#define __ROOTCLING__ 1
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#endif // defined(mainSelectorDT18_h) || defined(mainSelectorMC18_h)

#if defined(mainSelectorDT16_h) || defined(mainSelectorDT17_h) || defined(mainSelectorDT18_h)
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#endif // defined(mainSelectorDT16_h) || defined(mainSelectorDT17_h) || defined(mainSelectorDT18_h)

#if defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#endif // defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)

#include "roccor.Run2.v3/RoccoR.h"

#define QCD(H) ((TH1*)GetOutputList()->FindObject((TString(H->GetName()) + "_qcd").Data()))

class mainSelector : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   bool isWJetsToLNu = false;
   bool isWG = false;
   bool isWGG = false;
   bool isWTauNu = false;

   bool isDYJetsToLL = false;
   bool isZG = false;
   bool isZGG = false;
   bool isZTauTau = false;

   int iflag = -1;

   TH1D* h_nevt = 0;

   TH1D* h_W_ele = 0;
   TH1D* h_W_muo = 0;

   TH1D* h_W_ele_npvs = 0;
   TH1D* h_W_ele_npvs_w = 0;
   TH1D* h_W_muo_npvs = 0;
   TH1D* h_W_muo_npvs_w = 0;

   TH1D* h_W_ele0_pt = 0;
   TH1D* h_W_ele0_eta = 0;
   TH1D* h_W_ele0_phi = 0;
   TH1D* h_W_ele0_r9 = 0;
   TH1D* h_W_ele0_sieie = 0;
   TH1D* h_W_ele_met_pt = 0;
   TH1D* h_W_ele_met_phi = 0;

   TH1D* h_W_muo0_pt = 0;
   TH1D* h_W_muo0_eta = 0;
   TH1D* h_W_muo0_phi = 0;
   TH1D* h_W_muo_met_pt = 0;
   TH1D* h_W_muo_met_phi = 0;

   TH1D* h_W_ele0_mva = 0;

   TH1D* h_W_ele0_pf_iso_all = 0;
   TH1D* h_W_ele0_pf_iso_chg = 0;
   TH1D* h_W_muo0_pf_iso_all = 0;
   TH1D* h_W_muo0_pf_iso_chg = 0;

   TH1D* h_Z_ele = 0;
   TH1D* h_Z_muo = 0;

   TH1D* h_Z_ele_npvs = 0;
   TH1D* h_Z_ele_npvs_w = 0;
   TH1D* h_Z_muo_npvs = 0;
   TH1D* h_Z_muo_npvs_w = 0;

   TH1D* h_Z_ele0_pt = 0;
   TH1D* h_Z_ele0_eta = 0;
   TH1D* h_Z_ele0_phi = 0;
   TH1D* h_Z_ele0_r9 = 0;
   TH1D* h_Z_ele0_sieie = 0;
   TH1D* h_Z_ele1_pt = 0;
   TH1D* h_Z_ele1_eta = 0;
   TH1D* h_Z_ele1_phi = 0;
   TH1D* h_Z_ele1_r9 = 0;
   TH1D* h_Z_ele1_sieie = 0;
   TH1D* h_Z_ele_met_pt = 0;
   TH1D* h_Z_ele_met_phi = 0;

   TH1D* h_Z_muo0_pt = 0;
   TH1D* h_Z_muo0_eta = 0;
   TH1D* h_Z_muo0_phi = 0;
   TH1D* h_Z_muo1_pt = 0;
   TH1D* h_Z_muo1_eta = 0;
   TH1D* h_Z_muo1_phi = 0;
   TH1D* h_Z_muo_met_pt = 0;
   TH1D* h_Z_muo_met_phi = 0;

   TH1D* h_Z_ele0_mva = 0;
   TH1D* h_Z_ele1_mva = 0;

   TH1D* h_Z_ele0_pf_iso_all = 0;
   TH1D* h_Z_ele0_pf_iso_chg = 0;
   TH1D* h_Z_ele1_pf_iso_all = 0;
   TH1D* h_Z_ele1_pf_iso_chg = 0;
   TH1D* h_Z_muo0_pf_iso_all = 0;
   TH1D* h_Z_muo0_pf_iso_chg = 0;
   TH1D* h_Z_muo1_pf_iso_all = 0;
   TH1D* h_Z_muo1_pf_iso_chg = 0;

   TH1D* h_W_ele_njets = 0;
   TH1D* h_W_ele_jet0_pt = 0;
   TH1D* h_W_ele_jet0_eta = 0;
   TH1D* h_W_ele_jet0_phi = 0;
   TH1D* h_W_muo_njets = 0;
   TH1D* h_W_muo_jet0_pt = 0;
   TH1D* h_W_muo_jet0_eta = 0;
   TH1D* h_W_muo_jet0_phi = 0;

   TH1D* h_Z_ele_njets = 0;
   TH1D* h_Z_ele_jet0_pt = 0;
   TH1D* h_Z_ele_jet0_eta = 0;
   TH1D* h_Z_ele_jet0_phi = 0;
   TH1D* h_Z_muo_njets = 0;
   TH1D* h_Z_muo_jet0_pt = 0;
   TH1D* h_Z_muo_jet0_eta = 0;
   TH1D* h_Z_muo_jet0_phi = 0;

   TH1D* h_W_ele_nphotons = 0;
   TH1D* h_WG_ele_ele0_pt = 0;
   TH1D* h_WG_ele_pho0_pt = 0;
   TH1D* h_WG_ele_pho0_eta = 0;
   TH1D* h_WG_ele_pho0_phi = 0;
   TH1D* h_WG_ele_pho0_r9 = 0;
   TH1D* h_WG_ele_pho0_sieie = 0;
   TH1D* h_WG_ele_pho0_jet0_dR = 0;
   TH1D* h_WG_ele_pho0_mva = 0;
   TH1D* h_WG_ele_pho0_pf_iso_all = 0;
   TH1D* h_WG_ele_pho0_pf_iso_chg = 0;
   TH1D* h_WG_ele_pho0_dR = 0;

   TH1D* h_WGG_ele_pho1_pt = 0;
   TH1D* h_WGG_ele_pho1_eta = 0;
   TH1D* h_WGG_ele_pho1_phi = 0;
   TH1D* h_WGG_ele_pho1_r9 = 0;
   TH1D* h_WGG_ele_pho0_sieie = 0;
   TH1D* h_WGG_ele_pho1_sieie = 0;
   TH1D* h_WGG_ele_pho1_jet0_dR = 0;
   TH1D* h_WGG_ele_pho0_mva = 0;
   TH1D* h_WGG_ele_pho1_mva = 0;
   TH1D* h_WGG_ele_pho1_pf_iso_all = 0;
   TH1D* h_WGG_ele_pho1_pf_iso_chg = 0;
   TH1D* h_WGG_ele_pho1_dR = 0;
   TH1D* h_WGG_ele_pho0_pt = 0;
   TH1D* h_WGG_ele_ele0_pt = 0;
   TH1D* h_WGG_ele_pho0_pho1_dR = 0;

   TH1D* h_W_muo_nphotons = 0;
   TH1D* h_WG_muo_muo0_pt = 0;
   TH1D* h_WG_muo_pho0_pt = 0;
   TH1D* h_WG_muo_pho0_eta = 0;
   TH1D* h_WG_muo_pho0_phi = 0;
   TH1D* h_WG_muo_pho0_r9 = 0;
   TH1D* h_WG_muo_pho0_sieie = 0;
   TH1D* h_WG_muo_pho0_jet0_dR = 0;
   TH1D* h_WG_muo_pho0_mva = 0;
   TH1D* h_WG_muo_pho0_pf_iso_all = 0;
   TH1D* h_WG_muo_pho0_pf_iso_chg = 0;
   TH1D* h_WG_muo_pho0_dR = 0;

   TH1D* h_WGG_muo_pho1_pt = 0;
   TH1D* h_WGG_muo_pho1_eta = 0;
   TH1D* h_WGG_muo_pho1_phi = 0;
   TH1D* h_WGG_muo_pho1_r9 = 0;
   TH1D* h_WGG_muo_pho0_sieie = 0;
   TH1D* h_WGG_muo_pho1_sieie = 0;
   TH1D* h_WGG_muo_pho1_jet0_dR = 0;
   TH1D* h_WGG_muo_pho0_mva = 0;
   TH1D* h_WGG_muo_pho1_mva = 0;
   TH1D* h_WGG_muo_pho1_pf_iso_all = 0;
   TH1D* h_WGG_muo_pho1_pf_iso_chg = 0;
   TH1D* h_WGG_muo_pho1_dR = 0;
   TH1D* h_WGG_muo_pho0_pt = 0;
   TH1D* h_WGG_muo_muo0_pt = 0;
   TH1D* h_WGG_muo_pho0_pho1_dR = 0;

   TH1D* h_Z_ele_nphotons = 0;
   TH1D* h_ZG_ele_ele0_pt = 0;
   TH1D* h_ZG_ele_pho0_pt = 0;
   TH1D* h_ZG_ele_pho0_eta = 0;
   TH1D* h_ZG_ele_pho0_phi = 0;
   TH1D* h_ZG_ele_pho0_r9 = 0;
   TH1D* h_ZG_ele_pho0_sieie = 0;
   TH1D* h_ZG_ele_pho0_jet0_dR = 0;
   TH1D* h_ZG_ele_pho0_mva = 0;
   TH1D* h_ZG_ele_pho0_pf_iso_all = 0;
   TH1D* h_ZG_ele_pho0_pf_iso_chg = 0;
   TH1D* h_ZG_ele_pho0_dR = 0;

   TH1D* h_ZGG_ele_pho1_pt = 0;
   TH1D* h_ZGG_ele_pho1_eta = 0;
   TH1D* h_ZGG_ele_pho1_phi = 0;
   TH1D* h_ZGG_ele_pho1_r9 = 0;
   TH1D* h_ZGG_ele_pho0_sieie = 0;
   TH1D* h_ZGG_ele_pho1_sieie = 0;
   TH1D* h_ZGG_ele_pho1_jet0_dR = 0;
   TH1D* h_ZGG_ele_pho0_mva = 0;
   TH1D* h_ZGG_ele_pho1_mva = 0;
   TH1D* h_ZGG_ele_pho1_pf_iso_all = 0;
   TH1D* h_ZGG_ele_pho1_pf_iso_chg = 0;
   TH1D* h_ZGG_ele_pho1_dR = 0;
   TH1D* h_ZGG_ele_pho0_pt = 0;
   TH1D* h_ZGG_ele_ele0_pt = 0;
   TH1D* h_ZGG_ele_ele1_pt = 0;
   TH1D* h_ZGG_ele_pho0_pho1_dR = 0;

   TH1D* h_Z_muo_nphotons = 0;
   TH1D* h_ZG_muo_muo0_pt = 0;
   TH1D* h_ZG_muo_pho0_pt = 0;
   TH1D* h_ZG_muo_pho0_eta = 0;
   TH1D* h_ZG_muo_pho0_phi = 0;
   TH1D* h_ZG_muo_pho0_r9 = 0;
   TH1D* h_ZG_muo_pho0_sieie = 0;
   TH1D* h_ZG_muo_pho0_jet0_dR = 0;
   TH1D* h_ZG_muo_pho0_mva = 0;
   TH1D* h_ZG_muo_pho0_pf_iso_all = 0;
   TH1D* h_ZG_muo_pho0_pf_iso_chg = 0;
   TH1D* h_ZG_muo_pho0_dR = 0;

   TH1D* h_ZGG_muo_pho1_pt = 0;
   TH1D* h_ZGG_muo_pho1_eta = 0;
   TH1D* h_ZGG_muo_pho1_phi = 0;
   TH1D* h_ZGG_muo_pho1_r9 = 0;
   TH1D* h_ZGG_muo_pho0_sieie = 0;
   TH1D* h_ZGG_muo_pho1_sieie = 0;
   TH1D* h_ZGG_muo_pho1_jet0_dR = 0;
   TH1D* h_ZGG_muo_pho0_mva = 0;
   TH1D* h_ZGG_muo_pho1_mva = 0;
   TH1D* h_ZGG_muo_pho1_pf_iso_all = 0;
   TH1D* h_ZGG_muo_pho1_pf_iso_chg = 0;
   TH1D* h_ZGG_muo_pho1_dR = 0;
   TH1D* h_ZGG_muo_pho0_pt = 0;
   TH1D* h_ZGG_muo_muo0_pt = 0;
   TH1D* h_ZGG_muo_muo1_pt = 0;
   TH1D* h_ZGG_muo_pho0_pho1_dR = 0;

   TH1D* h_WG_ele = 0;
   TH1D* h_WG_muo = 0;
   TH1D* h_ZG_ele = 0;
   TH1D* h_ZG_muo = 0;

   TH1D* h_WGG_ele = 0;
   TH1D* h_WGG_muo = 0;
   TH1D* h_ZGG_ele = 0;
   TH1D* h_ZGG_muo = 0;

   TH1D* h_WG_ele_ele0_pho0 = 0;
   TH1D* h_WGG_ele_pho0_pho1_pt = 0;
   TH1D* h_WGG_ele_pho0_pho1 = 0;
   TH1D* h_WGG_ele_ele0_pho0 = 0;
   TH1D* h_WGG_ele_ele0_pho1 = 0;
   TH1D* h_WGG_ele_ele0_pho0_pho1 = 0;

   TH1D* h_WG_ele_ele0_pho0_fake = 0;

   TH1D* h_WG_muo_muo0_pho0 = 0;
   TH1D* h_WGG_muo_pho0_pho1_pt = 0;
   TH1D* h_WGG_muo_pho0_pho1 = 0;
   TH1D* h_WGG_muo_muo0_pho0 = 0;
   TH1D* h_WGG_muo_muo0_pho1 = 0;
   TH1D* h_WGG_muo_muo0_pho0_pho1 = 0;

   TH1D* h_WG_muo_muo0_pho0_fake = 0;

   TH1D* h_ZG_ele_ele0_pho0 = 0;
   TH1D* h_ZG_ele_ele1_pho0 = 0;
   TH1D* h_ZG_ele_ele0_ele1_pho0 = 0;
   TH1D* h_ZGG_ele_pho0_pho1_pt = 0;
   TH1D* h_ZGG_ele_pho0_pho1 = 0;
   TH1D* h_ZGG_ele_ele0_pho1 = 0;
   TH1D* h_ZGG_ele_ele1_pho1 = 0;
   TH1D* h_ZGG_ele_ele0_pho0_pho1 = 0;
   TH1D* h_ZGG_ele_ele1_pho0_pho1 = 0;
   TH1D* h_ZGG_ele_ele0_ele1_pho0_pho1 = 0;

   TH1D* h_ZG_muo_muo0_pho0 = 0;
   TH1D* h_ZG_muo_muo1_pho0 = 0;
   TH1D* h_ZG_muo_muo0_muo1_pho0 = 0;
   TH1D* h_ZGG_muo_pho0_pho1_pt = 0;
   TH1D* h_ZGG_muo_pho0_pho1 = 0;
   TH1D* h_ZGG_muo_muo0_pho1 = 0;
   TH1D* h_ZGG_muo_muo1_pho1 = 0;
   TH1D* h_ZGG_muo_muo0_pho0_pho1 = 0;
   TH1D* h_ZGG_muo_muo1_pho0_pho1 = 0;
   TH1D* h_ZGG_muo_muo0_muo1_pho0_pho1 = 0;

   TH1D* h_WG_ele_pho0_noiso_mva = 0;
   TH1D* h_WGG_ele_pho0_noiso_mva = 0;
   TH1D* h_WGG_ele_pho1_noiso_mva = 0;

   TH1D* h_WG_muo_pho0_noiso_mva = 0;
   TH1D* h_WGG_muo_pho0_noiso_mva = 0;
   TH1D* h_WGG_muo_pho1_noiso_mva = 0;

   TH1D* h_ZG_ele_pho0_noiso_mva = 0;
   TH1D* h_ZGG_ele_pho0_noiso_mva = 0;
   TH1D* h_ZGG_ele_pho1_noiso_mva = 0;

   TH1D* h_ZG_muo_pho0_noiso_mva = 0;
   TH1D* h_ZGG_muo_pho0_noiso_mva = 0;
   TH1D* h_ZGG_muo_pho1_noiso_mva = 0;

   TH1D* h_W_ele0_trig = 0;

   TH1D* h_W_muo0_trig = 0;

   TH1D* h_Z_ele0_trig = 0;
   TH1D* h_Z_ele1_trig = 0;

   TH1D* h_Z_muo0_trig = 0;
   TH1D* h_Z_muo1_trig = 0;

   TH2D* h_WG_ele_misid = 0;
   TH2D* h_WG_muo_misid = 0;
   TH2D* h_ZG_ele_misid = 0;
   TH2D* h_ZG_muo_misid = 0;

   TH1D* h_WG_ele_pho0_pt_cat1 = 0;
   TH1D* h_WG_muo_pho0_pt_cat1 = 0;
   TH1D* h_ZG_ele_pho0_pt_cat1 = 0;
   TH1D* h_ZG_muo_pho0_pt_cat1 = 0;
   TH1D* h_ZG_muo_muo0_muo1_pho0_cat1 = 0;

   TH1D* h_WG_ele_pho0_pt_cat2 = 0;
   TH1D* h_WG_muo_pho0_pt_cat2 = 0;
   TH1D* h_ZG_ele_pho0_pt_cat2 = 0;
   TH1D* h_ZG_muo_pho0_pt_cat2 = 0;
   TH1D* h_ZG_muo_muo0_muo1_pho0_cat2 = 0;

   TH1D* h_WG_ele_pho0_pt_cat3 = 0;
   TH1D* h_WG_muo_pho0_pt_cat3 = 0;
   TH1D* h_ZG_ele_pho0_pt_cat3 = 0;
   TH1D* h_ZG_muo_pho0_pt_cat3 = 0;
   TH1D* h_ZG_muo_muo0_muo1_pho0_cat3 = 0;

   TH3D* h_WGG_ele_pho0_pho1_pt_map = 0;
   TH3D* h_WGG_muo_pho0_pho1_pt_map = 0;
   TH3D* h_ZGG_ele_pho0_pho1_pt_map = 0;
   TH3D* h_ZGG_muo_pho0_pho1_pt_map = 0;

   TH3D* h_WGG_ele_pho0_pt_map = 0;
   TH3D* h_WGG_muo_pho0_pt_map = 0;
   TH3D* h_ZGG_ele_pho0_pt_map = 0;
   TH3D* h_ZGG_muo_pho0_pt_map = 0;

   TH3D* h_WGG_ele_pho1_pt_map = 0;
   TH3D* h_WGG_muo_pho1_pt_map = 0;
   TH3D* h_ZGG_ele_pho1_pt_map = 0;
   TH3D* h_ZGG_muo_pho1_pt_map = 0;

   TH3D* h_WGG_ele_pho0_pho1_map = 0;
   TH3D* h_WGG_muo_pho0_pho1_map = 0;
   TH3D* h_ZGG_ele_pho0_pho1_map = 0;
   TH3D* h_ZGG_muo_pho0_pho1_map = 0;

   TH3D* h_WGG_ele_ele0_pho0_pho1_map = 0;
   TH3D* h_WGG_muo_muo0_pho0_pho1_map = 0;
   TH3D* h_ZGG_ele_ele0_ele1_pho0_pho1_map = 0;
   TH3D* h_ZGG_muo_muo0_muo1_pho0_pho1_map = 0;

#if defined(COMPUTE_EG_MISID)
   TH1D* h_WG_ele_fake_1 = 0;
   TH1D* h_WG_ele_fake_2 = 0;
   TH1D* h_WG_ele_fake_3 = 0;
   TH1D* h_WG_ele_fake_4 = 0;
   TH1D* h_WG_ele_fake_5 = 0;
   TH1D* h_WG_ele_fake_6 = 0;
   TH1D* h_WG_ele_fake_7 = 0;
   TH1D* h_WG_ele_fake_8 = 0;
   TH1D* h_WG_ele_fake_9 = 0;
   TH1D* h_WG_ele_fake_10 = 0;
   TH1D* h_WG_ele_fake_11 = 0;
   TH1D* h_WG_ele_fake_12 = 0;
   TH1D* h_WG_ele_fake_13 = 0;
   TH1D* h_WG_ele_fake_14 = 0;
   TH1D* h_WG_ele_fake_15 = 0;
   TH1D* h_WG_ele_fake_16 = 0;
   TH1D* h_WG_ele_fake_17 = 0;
   TH1D* h_WG_ele_fake_18 = 0;
   TH1D* h_WG_ele_fake_19 = 0;
   TH1D* h_WG_ele_fake_20 = 0;

   TH1D* h_WG_ele_fake_truthmatch_1 = 0;
   TH1D* h_WG_ele_fake_truthmatch_2 = 0;
   TH1D* h_WG_ele_fake_truthmatch_3 = 0;
   TH1D* h_WG_ele_fake_truthmatch_4 = 0;
   TH1D* h_WG_ele_fake_truthmatch_5 = 0;
   TH1D* h_WG_ele_fake_truthmatch_6 = 0;
   TH1D* h_WG_ele_fake_truthmatch_7 = 0;
   TH1D* h_WG_ele_fake_truthmatch_8 = 0;
   TH1D* h_WG_ele_fake_truthmatch_9 = 0;
   TH1D* h_WG_ele_fake_truthmatch_10 = 0;
   TH1D* h_WG_ele_fake_truthmatch_11 = 0;
   TH1D* h_WG_ele_fake_truthmatch_12 = 0;
   TH1D* h_WG_ele_fake_truthmatch_13 = 0;
   TH1D* h_WG_ele_fake_truthmatch_14 = 0;
   TH1D* h_WG_ele_fake_truthmatch_15 = 0;
   TH1D* h_WG_ele_fake_truthmatch_16 = 0;
   TH1D* h_WG_ele_fake_truthmatch_17 = 0;
   TH1D* h_WG_ele_fake_truthmatch_18 = 0;
   TH1D* h_WG_ele_fake_truthmatch_19 = 0;
   TH1D* h_WG_ele_fake_truthmatch_20 = 0;
#endif // defined(COMPUTE_EG_MISID)

#if defined(mainSelectorDT16_h) || defined(mainSelectorDT17_h) || defined(mainSelectorDT18_h)
#endif // defined(mainSelectorDT16_h) || defined(mainSelectorDT17_h) || defined(mainSelectorDT18_h)

#if defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)
   TH1D* h_W_ele_nphotons_gen = 0;
   TH1D* h_W_muo_nphotons_gen = 0;

   TH1D* h_Z_ele_nphotons_gen = 0;
   TH1D* h_Z_muo_nphotons_gen = 0;

   TH1D* h_W_ele_gen = 0;
   TH1D* h_W_muo_gen = 0;

   TH1D* h_Z_ele_gen = 0;
   TH1D* h_Z_muo_gen = 0;

   TH1D* h_WG_ele_gen = 0;
   TH1D* h_WG_muo_gen = 0;

   TH1D* h_ZG_ele_gen = 0;
   TH1D* h_ZG_muo_gen = 0;

   TH1D* h_WGG_ele_gen = 0;
   TH1D* h_WGG_muo_gen = 0;

   TH1D* h_ZGG_ele_gen = 0;
   TH1D* h_ZGG_muo_gen = 0;

   TH1D* h_WGG_ele_pho0_pt_gen = 0;
   TH1D* h_WGG_ele_pho1_pt_gen = 0;
   TH1D* h_WGG_ele_pho0_pho1_pt_gen = 0;

   TH1D* h_WGG_muo_pho0_pt_gen = 0;
   TH1D* h_WGG_muo_pho1_pt_gen = 0;
   TH1D* h_WGG_muo_pho0_pho1_pt_gen = 0;

   TH1D* h_ZGG_ele_pho0_pt_gen = 0;
   TH1D* h_ZGG_ele_pho1_pt_gen = 0;
   TH1D* h_ZGG_ele_pho0_pho1_pt_gen = 0;

   TH1D* h_ZGG_muo_pho0_pt_gen = 0;
   TH1D* h_ZGG_muo_pho1_pt_gen = 0;
   TH1D* h_ZGG_muo_pho0_pho1_pt_gen = 0;

   TH1D* h_WGG_ele_pho0_pt_genmatch = 0;
   TH1D* h_WGG_ele_pho1_pt_genmatch = 0;
   TH1D* h_WGG_ele_pho0_pho1_pt_genmatch = 0;

   TH1D* h_WGG_muo_pho0_pt_genmatch = 0;
   TH1D* h_WGG_muo_pho1_pt_genmatch = 0;
   TH1D* h_WGG_muo_pho0_pho1_pt_genmatch = 0;

   TH1D* h_ZGG_ele_pho0_pt_genmatch = 0;
   TH1D* h_ZGG_ele_pho1_pt_genmatch = 0;
   TH1D* h_ZGG_ele_pho0_pho1_pt_genmatch = 0;

   TH1D* h_ZGG_muo_pho0_pt_genmatch = 0;
   TH1D* h_ZGG_muo_pho1_pt_genmatch = 0;
   TH1D* h_ZGG_muo_pho0_pho1_pt_genmatch = 0;

   TH1D* pu_ele_weights = 0;
   TH1D* pu_muo_weights = 0;

   TH2D* sf_ele_eff = 0;
   TH2D* sf_ele_reco = 0;
   TH2D* sf_ele_trig = 0;

   TH2D* sf_muo_trig = 0;
   TH2D* sf_muo_id = 0;
   TH2D* sf_muo_iso = 0;

   TH2D* sf_pho_eff = 0;

#if defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h)
#if defined(NANOAODv4)
   TH2F* l1prefiring_pho = 0;
   TH2F* l1prefiring_jet = 0;
#endif // defined(NANOAODv4)
#endif // defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h)

   TH2D* sf_eg_misid = 0;
   TH2D* sf_eg_misid_qcd = 0;

#endif // defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)

   RoccoR* roccor = 0;

#if defined(mainSelectorDT18_h) || defined(mainSelectorMC18_h)
   FactorizedJetCorrector* jet_corrector = 0;
#endif // defined(mainSelectorDT18_h) || defined(mainSelectorMC18_h)

#if defined(mainSelectorDT16_h) || defined(mainSelectorDT17_h) || defined(mainSelectorDT18_h)
   JetCorrectionUncertainty* jet_correction_unc = 0;
#endif // defined(mainSelectorDT16_h) || defined(mainSelectorDT17_h) || defined(mainSelectorDT18_h)

#if defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)
   JME::JetResolution* jet_resolution = 0;
   JME::JetResolutionScaleFactor* jet_resolution_sf = 0;
#endif // defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)

   TTreeReaderValue<UInt_t> run = {fReader, "run"};
   TTreeReaderValue<UInt_t> luminosityBlock = {fReader, "luminosityBlock"};
   TTreeReaderValue<ULong64_t> event = {fReader, "event"};

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};

   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
   TTreeReaderArray<Float_t> Electron_dz = {fReader, "Electron_dz"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Float_t> Electron_r9 = {fReader, "Electron_r9"};
   TTreeReaderArray<Float_t> Electron_sieie = {fReader, "Electron_sieie"};

   TTreeReaderArray<Int_t> Electron_photonIdx = {fReader, "Electron_photonIdx"};

   TTreeReaderArray<Float_t> Electron_pfRelIso03_all = {fReader, "Electron_pfRelIso03_all"};
   TTreeReaderArray<Float_t> Electron_pfRelIso03_chg = {fReader, "Electron_pfRelIso03_chg"};

   TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WP80 = {fReader, "Electron_mvaFall17V2noIso_WP80"};
   TTreeReaderArray<Float_t> Electron_mvaFall17V2noIso = {fReader, "Electron_mvaFall17V2noIso"};
#define Electron_mvaID_WP80 Electron_mvaFall17V2noIso_WP80
#define Electron_mvaID Electron_mvaFall17V2noIso

   TTreeReaderArray<Int_t> Electron_vidNestedWPBitmap = {fReader, "Electron_vidNestedWPBitmap"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Int_t> Muon_nTrackerLayers = {fReader, "Muon_nTrackerLayers"};

   TTreeReaderArray<Float_t> Muon_pfRelIso03_all = {fReader, "Muon_pfRelIso03_all"};
   TTreeReaderArray<Float_t> Muon_pfRelIso03_chg = {fReader, "Muon_pfRelIso03_chg"};
   TTreeReaderArray<Float_t> Muon_pfRelIso04_all = {fReader, "Muon_pfRelIso04_all"};

   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};

   TTreeReaderValue<UInt_t> nPhoton = {fReader, "nPhoton"};
   TTreeReaderArray<Float_t> Photon_pt = {fReader, "Photon_pt"};
   TTreeReaderArray<Float_t> Photon_eta = {fReader, "Photon_eta"};
   TTreeReaderArray<Float_t> Photon_phi = {fReader, "Photon_phi"};
   TTreeReaderArray<Float_t> Photon_mass = {fReader, "Photon_mass"};
   TTreeReaderArray<Float_t> Photon_r9 = {fReader, "Photon_r9"};
   TTreeReaderArray<Float_t> Photon_sieie = {fReader, "Photon_sieie"};
   TTreeReaderArray<Bool_t> Photon_electronVeto = {fReader, "Photon_electronVeto"};
   TTreeReaderArray<Bool_t> Photon_pixelSeed = {fReader, "Photon_pixelSeed"};

   TTreeReaderArray<Float_t> Photon_pfRelIso03_all = {fReader, "Photon_pfRelIso03_all"};
   TTreeReaderArray<Float_t> Photon_pfRelIso03_chg = {fReader, "Photon_pfRelIso03_chg"};

   TTreeReaderArray<Float_t> Photon_mvaID = {fReader, "Photon_mvaID"};

   TTreeReaderArray<Int_t> Photon_vidNestedWPBitmap = {fReader, "Photon_vidNestedWPBitmap"};

   TTreeReaderValue<UInt_t> nJet = {fReader, "nJet"};
   TTreeReaderArray<Float_t> Jet_pt = {fReader, "Jet_pt"};
   TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
   TTreeReaderArray<Float_t> Jet_phi = {fReader, "Jet_phi"};
   TTreeReaderArray<Float_t> Jet_mass = {fReader, "Jet_mass"};
   TTreeReaderArray<Float_t> Jet_area = {fReader, "Jet_area"};
   TTreeReaderArray<Float_t> Jet_rawFactor = {fReader, "Jet_rawFactor"};
   TTreeReaderValue<Float_t> fixedGridRhoFastjetAll = {fReader, "fixedGridRhoFastjetAll"};

#if defined(mainSelectorDT17_h) || defined(mainSelectorMC17_h)
    TTreeReaderValue<Float_t> METFixEE2017_phi = {fReader, "METFixEE2017_phi"};
    TTreeReaderValue<Float_t> METFixEE2017_pt = {fReader, "METFixEE2017_pt"};
#define MET_phi METFixEE2017_phi
#define MET_pt METFixEE2017_pt
#else
    TTreeReaderValue<Float_t> MET_phi = {fReader, "MET_phi"};
    TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
#endif // defined(mainSelectorDT17_h) || defined(mainSelectorMC17_h)

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

   TTreeReaderValue<Bool_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
   TTreeReaderValue<Bool_t> Flag_globalSuperTightHalo2016Filter = {fReader, "Flag_globalSuperTightHalo2016Filter"};
   TTreeReaderValue<Bool_t> Flag_HBHENoiseFilter = {fReader, "Flag_HBHENoiseFilter"};
   TTreeReaderValue<Bool_t> Flag_HBHENoiseIsoFilter = {fReader, "Flag_HBHENoiseIsoFilter"};
   TTreeReaderValue<Bool_t> Flag_EcalDeadCellTriggerPrimitiveFilter = {fReader, "Flag_EcalDeadCellTriggerPrimitiveFilter"};
   TTreeReaderValue<Bool_t> Flag_BadPFMuonFilter = {fReader, "Flag_BadPFMuonFilter"};
   TTreeReaderValue<Bool_t> Flag_eeBadScFilter = {fReader, "Flag_eeBadScFilter"};
   TTreeReaderValue<Bool_t> Flag_ecalBadCalibFilter = {fReader, "Flag_ecalBadCalibFilter"};

#if defined(mainSelectorDT17_h) || defined(mainSelectorMC17_h)
#if defined(NANOAODv4)
   TTreeReaderValue<UChar_t> Flag_ecalBadCalibFilterV2 = {fReader, "Flag_ecalBadCalibFilterV2"};
#endif // defined(NANOAODv4)
#if defined(NANOAODv5)
   TTreeReaderValue<Bool_t> Flag_ecalBadCalibFilterV2 = {fReader, "Flag_ecalBadCalibFilterV2"};
#endif // defined(NANOAODv5)
#endif // defined(mainSelectorDT17_h) || defined(mainSelectorMC17_h)

#if defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h)
#if defined(NANOAODv5)
   TTreeReaderValue<Float_t> L1PreFiringWeight_Dn = {fReader, "L1PreFiringWeight_Dn"};
   TTreeReaderValue<Float_t> L1PreFiringWeight_Nom = {fReader, "L1PreFiringWeight_Nom"};
   TTreeReaderValue<Float_t> L1PreFiringWeight_Up = {fReader, "L1PreFiringWeight_Up"};
#endif // defined(NANOAODv5)
#endif // defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h)

#if defined(mainSelectorDT16_h) || defined(mainSelectorMC16_h)

   TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf = {fReader, "HLT_Ele27_WPTight_Gsf"};

   TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
   TTreeReaderValue<Bool_t> HLT_IsoTkMu24 = {fReader, "HLT_IsoTkMu24"};

#endif // defined(mainSelectorDT16_h) || defined(mainSelectorMC16_h)

#if defined(mainSelectorDT17_h) || defined(mainSelectorMC17_h)

#if defined(NANOAODv4)
   TTreeReaderValue<Bool_t> HLT_Ele35_WPTight_Gsf = {fReader, "HLT_Ele35_WPTight_Gsf"};
#endif // defined(NANOAODv4)
#if defined(NANOAODv5)
   TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf_L1DoubleEG = {fReader, "HLT_Ele32_WPTight_Gsf_L1DoubleEG"};
#endif // defined(NANOAODv5)

   TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
   TTreeReaderValue<Bool_t> HLT_IsoMu27 = {fReader, "HLT_IsoMu27"};

#endif // defined(mainSelectorDT17_h) || defined(mainSelectorMC17_h)

#if defined(mainSelectorDT18_h) || defined(mainSelectorMC18_h)

   TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf = {fReader, "HLT_Ele32_WPTight_Gsf"};

   TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};

#endif // defined(mainSelectorDT18_h)

#if defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)

   TTreeReaderValue<Float_t> Generator_weight = {fReader, "Generator_weight"};

   TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};

   TTreeReaderValue<UInt_t> nGenPart = {fReader, "nGenPart"};
   TTreeReaderArray<Float_t> GenPart_pt = {fReader, "GenPart_pt"};
   TTreeReaderArray<Float_t> GenPart_eta = {fReader, "GenPart_eta"};
   TTreeReaderArray<Float_t> GenPart_phi = {fReader, "GenPart_phi"};
   TTreeReaderArray<Float_t> GenPart_mass = {fReader, "GenPart_mass"};
   TTreeReaderArray<Int_t> GenPart_genPartIdxMother = {fReader, "GenPart_genPartIdxMother"};
   TTreeReaderArray<Int_t> GenPart_pdgId = {fReader, "GenPart_pdgId"};
   TTreeReaderArray<Int_t> GenPart_status = {fReader, "GenPart_status"};
   TTreeReaderArray<Int_t> GenPart_statusFlags = {fReader, "GenPart_statusFlags"};

   TTreeReaderValue<UInt_t> nGenDressedLepton = {fReader, "nGenDressedLepton"};
   TTreeReaderArray<Float_t> GenDressedLepton_pt = {fReader, "GenDressedLepton_pt"};
   TTreeReaderArray<Float_t> GenDressedLepton_eta = {fReader, "GenDressedLepton_eta"};
   TTreeReaderArray<Float_t> GenDressedLepton_phi = {fReader, "GenDressedLepton_phi"};
   TTreeReaderArray<Float_t> GenDressedLepton_mass = {fReader, "GenDressedLepton_mass"};
   TTreeReaderArray<Int_t> GenDressedLepton_pdgId = {fReader, "GenDressedLepton_pdgId"};

   TTreeReaderValue<UInt_t> nGenJet = {fReader, "nGenJet"};
   TTreeReaderArray<Float_t> GenJet_pt = {fReader, "GenJet_pt"};
   TTreeReaderArray<Float_t> GenJet_eta = {fReader, "GenJet_eta"};
   TTreeReaderArray<Float_t> GenJet_phi = {fReader, "GenJet_phi"};
   TTreeReaderArray<Float_t> GenJet_mass = {fReader, "GenJet_mass"};

   TTreeReaderArray<Int_t> Electron_genPartIdx = {fReader, "Electron_genPartIdx"};
   TTreeReaderArray<Int_t> Muon_genPartIdx = {fReader, "Muon_genPartIdx"};
   TTreeReaderArray<Int_t> Photon_genPartIdx = {fReader, "Photon_genPartIdx"};
   TTreeReaderArray<Int_t> Jet_genJetIdx = {fReader, "Jet_genJetIdx"};

   TTreeReaderValue<Float_t> MET_fiducialGenPhi = {fReader, "MET_fiducialGenPhi"};
   TTreeReaderValue<Float_t> MET_fiducialGenPt = {fReader, "MET_fiducialGenPt"};

#endif // defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)

   mainSelector(TTree * /*tree*/ =0) { }
   virtual ~mainSelector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   //ClassDef(mainSelector,0);

};

#endif // mainSelector_h

#ifdef mainSelector_cxx
void mainSelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t mainSelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

float getWeight(TH1* h, float x, float y, float var = 0) {
   if (h) {
     if (h->InheritsFrom("TH2")) {
       int binx = max(1, min(h->GetNbinsX(), h->GetXaxis()->FindBin(x)));
       int biny = max(1, min(h->GetNbinsY(), h->GetYaxis()->FindBin(y)));
       return h->GetBinContent(binx,biny) + var * h->GetBinError(binx,biny);
     } else {
       int bin = max(1, min(h->GetNbinsX(), h->GetXaxis()->FindBin(x)));
       return h->GetBinContent(bin) + var * h->GetBinError(bin);
     }
   }
   cout << "ERROR: missing weight." << endl;
   return 1.;
}

#if defined(mainSelectorMC16_cxx)
float getWeight(float photon_eta, float photon_r9, float var = 0) {
   if (fabs(photon_eta) < 1.442) {
     if (photon_r9 < 0.94) return 1.00479 + var * 0.0164;
     if (photon_r9 > 0.94) return 0.985097 + var * 0.0086;
   }
   if (fabs(photon_eta) > 1.566 && fabs(photon_eta) < 2.400) {
     if (photon_r9 < 0.94) return 1.00703 + var * 0.0401;
     if (photon_r9 > 0.94) return 0.972969 + var * 0.006;
   }
   cout << "ERROR: missing weight." << endl;
   return 1.;
}
#endif // defined(mainSelectorMC16_cxx)

#if defined(mainSelectorMC17_cxx)
float getWeight(float photon_eta, float photon_r9, float var = 0) {
   if (fabs(photon_eta) < 1.442) {
     if (photon_r9 < 0.94) return 0.960239 + var * 0.005568;
     if (photon_r9 > 0.94) return 0.974239 + var * 0.003711;
   }
   if (fabs(photon_eta) > 1.566 && fabs(photon_eta) < 2.400) {
     if (photon_r9 < 0.94) return 0.919658 + var * 0.015263;
     if (photon_r9 > 0.94) return 0.917715 + var * 0.012046;
   }
   cout << "ERROR: missing weight." << endl;
   return 1.;
}
#endif // defined(mainSelectorMC17_cxx)

#if defined(mainSelectorMC18_cxx)
float getWeight(float photon_eta, float photon_pt, float var = 0) {
   if (fabs(photon_eta) < 1.442) {
     if (photon_pt > 10 && photon_pt < 30) return 0.9619 + var * 0.0044;
     if (photon_pt > 30 && photon_pt < 60) return 0.9719 + var * 0.0130;
     if (photon_pt > 60) return 0.9875 + var * 0.0964;
   }
   if (fabs(photon_eta) > 1.566 && fabs(photon_eta) < 2.400) {
     if (photon_pt > 10 && photon_pt < 30) return 0.8663 + var * 0.0199;
     if (photon_pt > 30 && photon_pt < 60) return 0.9184 + var * 0.0258;
     if (photon_pt > 60) return 0.9680 + var * 0.1063;
   }
   cout << "ERROR: missing weight." << endl;
   return 1.;
}
#endif // defined(mainSelectorMC18_cxx)

#if defined(NANOAODv4)
#include "TMath.h"
#include "TLorentzVector.h"
float ecalSmearMC(float cluster_pt, float cluster_eta, float cluster_phi, float cluster_mass, float cluster_r9, float gauss) {
   float eMean = 0.;
   float err_Emean = 0.;
   float rho = 0.;
   float phi = 0.;
   float rhoErr = 0.;
   float phiErr = 0.;
   if (fabs(cluster_eta) > 0. && fabs(cluster_eta) < 1) {
     if (cluster_r9 > 0.94 && cluster_r9 < 1.) {
       eMean = 6.60;
       err_Emean = 0.;
       rho = 0.0106;
       rhoErr = 0.;
       phi = TMath::PiOver2();
       phiErr = TMath::PiOver2();
     } else if (cluster_r9 > 0. && cluster_r9 < 0.94) {
       eMean = 6.73;
       err_Emean = 0.;
       rho = 0.0129;
       rhoErr = 0.;
       phi = TMath::PiOver2();
       phiErr = TMath::PiOver2();
     }
   }
   if (fabs(cluster_eta) > 1. && fabs(cluster_eta) < 1.4442) {
     if (cluster_r9 > 0.94 && cluster_r9 < 1.){
       eMean = 6.52;
       err_Emean = 0.;
       rho = 0.0168;
       rhoErr = 0.0014;
       phi = TMath::PiOver2();
       phiErr = TMath::PiOver2();
     } else if (cluster_r9 > 0. && cluster_r9 < 0.94){
       eMean = 6.72;
       err_Emean = 0.;
       rho = 0.0233;
       rhoErr = 0.0005;
       phi = TMath::PiOver2();
       phiErr = TMath::PiOver2();
     }
   }
   if (fabs(cluster_eta) > 1.566 && fabs(cluster_eta) < 2) {
     if (cluster_r9 > 0.94 && cluster_r9 < 1.) {
       eMean = 6.76;
       err_Emean = 0.;
       rho = 0.0206;
       rhoErr = 0.0002;
       phi = TMath::PiOver2();
       phiErr = TMath::PiOver2();
     } else if (cluster_r9 > 0. && cluster_r9 < 0.94){
       eMean = 6.77;
       err_Emean = 0.;
       rho = 0.0262;
       rhoErr = 0.0001;
       phi = TMath::PiOver2();
       phiErr = TMath::PiOver2();
     }
   }
   if (fabs(cluster_eta) > 2. && fabs(cluster_eta) < 2.5) {
     if (cluster_r9 > 0.94 && cluster_r9 < 1.){
       eMean = 6.54;
       err_Emean = 0.;
       rho = 0.0393;
       rhoErr = 0.0001;
       phi = TMath::PiOver2();
       phiErr = TMath::PiOver2();
     } else if (cluster_r9 > 0. && cluster_r9 < 0.94){
       eMean = 6.73;
       err_Emean = 0.;
       rho = 0.0315;
       rhoErr = 0.0002;
       phi = TMath::PiOver2();
       phiErr = TMath::PiOver2();
     }
   }
   TLorentzVector cluster;
   cluster.SetPtEtaPhiM(cluster_pt, cluster_eta, cluster_phi, cluster_mass);
   float et = cluster.Et();
   float nrSigmaRho = 0.;
   float nrSigmaPhi = 0.;
   float rhoVal = rho + rhoErr * nrSigmaRho;
   float phiVal = phi + phiErr * nrSigmaRho;
   float constTerm = rhoVal * TMath::Sin(phiVal);
   float alpha = rhoVal * eMean * TMath::Cos(phiVal);
   float sigma = TMath::Sqrt(constTerm * constTerm + alpha * alpha / et);
   return (1.0 + sigma * gauss);
}
#endif // defined(NANOAODv4)

#endif // mainSelector_cxx
