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

#if defined(mainSelectorDT17B_h)
#define mainSelectorDT17_h
#endif // defined(mainSelectorDT17B_h)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#define STANDALONE
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

#include "roccor.Run2.v2/RoccoR.h"

class mainSelector : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   bool isWJetsToLNu    = false;
   bool isWGToLNuG      = false;
   bool isWGG           = false;
   bool isWGGJets       = false;

   bool isDYJetsToLL    = false;
   bool isZGTo2LG       = false;
   bool isZGGToLLGG     = false;
   bool isZGGJetsToLLGG = false;

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
   TH1D* h_W_ele_met_sign = 0;
   TH1D* h_W_muo0_pt = 0;
   TH1D* h_W_muo0_eta = 0;
   TH1D* h_W_muo0_phi = 0;
   TH1D* h_W_muo_met_pt = 0;
   TH1D* h_W_muo_met_phi = 0;
   TH1D* h_W_muo_met_sign = 0;

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
   TH1D* h_Z_ele_met_sign = 0;
   TH1D* h_Z_muo0_pt = 0;
   TH1D* h_Z_muo0_eta = 0;
   TH1D* h_Z_muo0_phi = 0;
   TH1D* h_Z_muo1_pt = 0;
   TH1D* h_Z_muo1_eta = 0;
   TH1D* h_Z_muo1_phi = 0;
   TH1D* h_Z_muo_met_pt = 0;
   TH1D* h_Z_muo_met_phi = 0;
   TH1D* h_Z_muo_met_sign = 0;

   TH2D* h_TrigObj = 0;

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
   TH1D* h_W_ele_pho0_pt = 0;
   TH1D* h_W_ele_pho0_eta = 0;
   TH1D* h_W_ele_pho0_phi = 0;
   TH1D* h_W_ele_pho0_r9 = 0;
   TH1D* h_W_ele_pho0_sieie = 0;
   TH1D* h_W_ele_pho1_pt = 0;
   TH1D* h_W_ele_pho1_eta = 0;
   TH1D* h_W_ele_pho1_phi = 0;
   TH1D* h_W_ele_pho1_r9 = 0;
   TH1D* h_W_ele_pho1_sieie = 0;
   TH1D* h_W_ele_diphoton_pt = 0;
   TH1D* h_W_muo_nphotons = 0;
   TH1D* h_W_muo_pho0_pt = 0;
   TH1D* h_W_muo_pho0_eta = 0;
   TH1D* h_W_muo_pho0_phi = 0;
   TH1D* h_W_muo_pho0_r9 = 0;
   TH1D* h_W_muo_pho0_sieie = 0;
   TH1D* h_W_muo_pho1_pt = 0;
   TH1D* h_W_muo_pho1_eta = 0;
   TH1D* h_W_muo_pho1_phi = 0;
   TH1D* h_W_muo_pho1_r9 = 0;
   TH1D* h_W_muo_pho1_sieie = 0;
   TH1D* h_W_muo_diphoton_pt = 0;

   TH1D* h_Z_ele_nphotons = 0;
   TH1D* h_Z_ele_pho0_pt = 0;
   TH1D* h_Z_ele_pho0_eta = 0;
   TH1D* h_Z_ele_pho0_phi = 0;
   TH1D* h_Z_ele_pho0_r9 = 0;
   TH1D* h_Z_ele_pho0_sieie = 0;
   TH1D* h_Z_ele_pho1_pt = 0;
   TH1D* h_Z_ele_pho1_eta = 0;
   TH1D* h_Z_ele_pho1_phi = 0;
   TH1D* h_Z_ele_pho1_r9 = 0;
   TH1D* h_Z_ele_pho1_sieie = 0;
   TH1D* h_Z_ele_diphoton_pt = 0;
   TH1D* h_Z_muo_nphotons = 0;
   TH1D* h_Z_muo_pho0_pt = 0;
   TH1D* h_Z_muo_pho0_eta = 0;
   TH1D* h_Z_muo_pho0_phi = 0;
   TH1D* h_Z_muo_pho0_r9 = 0;
   TH1D* h_Z_muo_pho0_sieie = 0;
   TH1D* h_Z_muo_pho1_pt = 0;
   TH1D* h_Z_muo_pho1_eta = 0;
   TH1D* h_Z_muo_pho1_phi = 0;
   TH1D* h_Z_muo_pho1_r9 = 0;
   TH1D* h_Z_muo_pho1_sieie = 0;
   TH1D* h_Z_muo_diphoton_pt = 0;

   TH1D* h_W_ele_pho0_dR = 0;
   TH1D* h_W_ele_pho1_dR = 0;
   TH1D* h_W_muo_pho0_dR = 0;
   TH1D* h_W_muo_pho1_dR = 0;
   TH1D* h_Z_ele_pho0_dR = 0;
   TH1D* h_Z_ele_pho1_dR = 0;
   TH1D* h_Z_muo_pho0_dR = 0;
   TH1D* h_Z_muo_pho1_dR = 0;

   TH1D* h_W_ele_pho0 = 0;
   TH1D* h_W_muo_pho0 = 0;
   TH1D* h_Z_ele_pho0 = 0;
   TH1D* h_Z_muo_pho0 = 0;

#if defined(mainSelectorDT16_h) || defined(mainSelectorDT17_h) || defined(mainSelectorDT18_h)
#endif // defined(mainSelectorDT16_h) || defined(mainSelectorDT17_h) || defined(mainSelectorDT18_h)

#if defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)
   TH1D* h_W_ele_gen = 0;
   TH1D* h_W_muo_gen = 0;

   TH1D* h_Z_ele_gen = 0;
   TH1D* h_Z_muo_gen = 0;

   TH1D* pu_ele_weights = 0;
   TH1D* pu_muo_weights = 0;

   TH2D* sf_ele_eff = 0;
   TH2D* sf_ele_reco = 0;

   TH2D* sf_muo_id = 0;
   TH2D* sf_muo_iso = 0;

   TH2D* sf_pho_eff = 0;
#endif // defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)

   RoccoR* roccor;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   JME::JetResolution* jet_resolution;
   JME::JetResolutionScaleFactor* jet_resolution_sf;
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

#if defined(mainSelectorDT16_h)

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};

   TTreeReaderValue<UInt_t> run = {fReader, "run"};
   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
   TTreeReaderArray<Float_t> Electron_dz = {fReader, "Electron_dz"};
   TTreeReaderArray<Float_t> Electron_r9 = {fReader, "Electron_r9"};
   TTreeReaderArray<Float_t> Electron_sieie = {fReader, "Electron_sieie"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaSpring16GP_WP80 = {fReader, "Electron_mvaSpring16GP_WP80"};
   TTreeReaderArray<Bool_t> Electron_mvaSpring16GP_WP90 = {fReader, "Electron_mvaSpring16GP_WP90"};
   TTreeReaderArray<Int_t> Electron_jetIdx = {fReader, "Electron_jetIdx"};
   TTreeReaderArray<Int_t> Electron_photonIdx = {fReader, "Electron_photonIdx"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_dxy = {fReader, "Muon_dxy"};
   TTreeReaderArray<Float_t> Muon_dz = {fReader, "Muon_dz"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};
   TTreeReaderArray<Int_t> Muon_jetIdx = {fReader, "Muon_jetIdx"};

   TTreeReaderValue<UInt_t> nPhoton = {fReader, "nPhoton"};
   TTreeReaderArray<Float_t> Photon_pt = {fReader, "Photon_pt"};
   TTreeReaderArray<Float_t> Photon_eta = {fReader, "Photon_eta"};
   TTreeReaderArray<Float_t> Photon_phi = {fReader, "Photon_phi"};
   TTreeReaderArray<Float_t> Photon_mass = {fReader, "Photon_mass"};
   TTreeReaderArray<Float_t> Photon_r9 = {fReader, "Photon_r9"};
   TTreeReaderArray<Float_t> Photon_sieie = {fReader, "Photon_sieie"};
   TTreeReaderArray<Int_t> Photon_jetIdx = {fReader, "Photon_jetIdx"};
   TTreeReaderArray<Bool_t> Photon_electronVeto = {fReader, "Photon_electronVeto"};
   TTreeReaderArray<Bool_t> Photon_pixelSeed = {fReader, "Photon_pixelSeed"};
   TTreeReaderArray<Bool_t> Photon_mvaID_WP90 = {fReader, "Photon_mvaID_WP90"};

   TTreeReaderValue<UInt_t> nJet = {fReader, "nJet"};
   TTreeReaderArray<Float_t> Jet_pt = {fReader, "Jet_pt"};
   TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
   TTreeReaderArray<Float_t> Jet_phi = {fReader, "Jet_phi"};
   TTreeReaderArray<Float_t> Jet_mass = {fReader, "Jet_mass"};

   TTreeReaderValue<Float_t> MET_phi = {fReader, "MET_phi"};
   TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
   TTreeReaderValue<Float_t> MET_significance = {fReader, "MET_significance"};

   TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf = {fReader, "HLT_Ele27_WPTight_Gsf"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};

   TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
   TTreeReaderValue<Bool_t> HLT_IsoTkMu24 = {fReader, "HLT_IsoTkMu24"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ"};

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

   TTreeReaderValue<Bool_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
   TTreeReaderValue<Bool_t> Flag_METFilters = {fReader, "Flag_METFilters"};

#endif // defined(mainSelectorDT16_h)

#if defined(mainSelectorDT17_h)

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};

   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
   TTreeReaderArray<Float_t> Electron_dz = {fReader, "Electron_dz"};
   TTreeReaderArray<Float_t> Electron_r9 = {fReader, "Electron_r9"};
   TTreeReaderArray<Float_t> Electron_sieie = {fReader, "Electron_sieie"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17Iso_WP90 = {fReader, "Electron_mvaFall17Iso_WP90"};
   TTreeReaderArray<Int_t> Electron_jetIdx = {fReader, "Electron_jetIdx"};
   TTreeReaderArray<Int_t> Electron_photonIdx = {fReader, "Electron_photonIdx"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_dxy = {fReader, "Muon_dxy"};
   TTreeReaderArray<Float_t> Muon_dz = {fReader, "Muon_dz"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};
   TTreeReaderArray<Int_t> Muon_jetIdx = {fReader, "Muon_jetIdx"};

   TTreeReaderValue<UInt_t> nPhoton = {fReader, "nPhoton"};
   TTreeReaderArray<Float_t> Photon_pt = {fReader, "Photon_pt"};
   TTreeReaderArray<Float_t> Photon_eta = {fReader, "Photon_eta"};
   TTreeReaderArray<Float_t> Photon_phi = {fReader, "Photon_phi"};
   TTreeReaderArray<Float_t> Photon_mass = {fReader, "Photon_mass"};
   TTreeReaderArray<Float_t> Photon_r9 = {fReader, "Photon_r9"};
   TTreeReaderArray<Float_t> Photon_sieie = {fReader, "Photon_sieie"};
   TTreeReaderArray<Int_t> Photon_jetIdx = {fReader, "Photon_jetIdx"};
   TTreeReaderArray<Bool_t> Photon_electronVeto = {fReader, "Photon_electronVeto"};
   TTreeReaderArray<Bool_t> Photon_pixelSeed = {fReader, "Photon_pixelSeed"};
   TTreeReaderArray<Bool_t> Photon_mvaID_WP90 = {fReader, "Photon_mvaID_WP90"};

   TTreeReaderValue<UInt_t> nJet = {fReader, "nJet"};
   TTreeReaderArray<Float_t> Jet_pt = {fReader, "Jet_pt"};
   TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
   TTreeReaderArray<Float_t> Jet_phi = {fReader, "Jet_phi"};
   TTreeReaderArray<Float_t> Jet_mass = {fReader, "Jet_mass"};

   TTreeReaderValue<Float_t> MET_phi = {fReader, "MET_phi"};
   TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
   TTreeReaderValue<Float_t> MET_significance = {fReader, "MET_significance"};

   TTreeReaderValue<Bool_t> HLT_Ele35_WPTight_Gsf = {fReader, "HLT_Ele35_WPTight_Gsf"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};

   TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
   TTreeReaderValue<Bool_t> HLT_IsoMu27 = {fReader, "HLT_IsoMu27"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"};
#if !defined(mainSelectorDT17B_h)
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8"};
#endif // !defined(mainSelectorDT17B_h)

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

   TTreeReaderValue<Bool_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
   TTreeReaderValue<Bool_t> Flag_METFilters = {fReader, "Flag_METFilters"};

#endif // defined(mainSelectorDT17_h)

#if defined(mainSelectorDT18_h)

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};

   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
   TTreeReaderArray<Float_t> Electron_dz = {fReader, "Electron_dz"};
   TTreeReaderArray<Float_t> Electron_r9 = {fReader, "Electron_r9"};
   TTreeReaderArray<Float_t> Electron_sieie = {fReader, "Electron_sieie"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP90 = {fReader, "Electron_mvaFall17V2Iso_WP90"};
   TTreeReaderArray<Int_t> Electron_jetIdx = {fReader, "Electron_jetIdx"};
   TTreeReaderArray<Int_t> Electron_photonIdx = {fReader, "Electron_photonIdx"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_dxy = {fReader, "Muon_dxy"};
   TTreeReaderArray<Float_t> Muon_dz = {fReader, "Muon_dz"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};
   TTreeReaderArray<Int_t> Muon_jetIdx = {fReader, "Muon_jetIdx"};

   TTreeReaderValue<UInt_t> nPhoton = {fReader, "nPhoton"};
   TTreeReaderArray<Float_t> Photon_pt = {fReader, "Photon_pt"};
   TTreeReaderArray<Float_t> Photon_eta = {fReader, "Photon_eta"};
   TTreeReaderArray<Float_t> Photon_phi = {fReader, "Photon_phi"};
   TTreeReaderArray<Float_t> Photon_mass = {fReader, "Photon_mass"};
   TTreeReaderArray<Float_t> Photon_r9 = {fReader, "Photon_r9"};
   TTreeReaderArray<Float_t> Photon_sieie = {fReader, "Photon_sieie"};
   TTreeReaderArray<Int_t> Photon_jetIdx = {fReader, "Photon_jetIdx"};
   TTreeReaderArray<Bool_t> Photon_electronVeto = {fReader, "Photon_electronVeto"};
   TTreeReaderArray<Bool_t> Photon_pixelSeed = {fReader, "Photon_pixelSeed"};
   TTreeReaderArray<Bool_t> Photon_mvaID_WP90 = {fReader, "Photon_mvaID_WP90"};

   TTreeReaderValue<UInt_t> nJet = {fReader, "nJet"};
   TTreeReaderArray<Float_t> Jet_pt = {fReader, "Jet_pt"};
   TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
   TTreeReaderArray<Float_t> Jet_phi = {fReader, "Jet_phi"};
   TTreeReaderArray<Float_t> Jet_mass = {fReader, "Jet_mass"};

   TTreeReaderValue<Float_t> MET_phi = {fReader, "MET_phi"};
   TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
   TTreeReaderValue<Float_t> MET_significance = {fReader, "MET_significance"};

// FIXME
   TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf = {fReader, "HLT_Ele32_WPTight_Gsf"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};

   TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8"};
// FIXME

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

   TTreeReaderValue<Bool_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
   TTreeReaderValue<Bool_t> Flag_METFilters = {fReader, "Flag_METFilters"};

#endif // defined(mainSelectorDT18_h)

#if defined(mainSelectorMC16_h)

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};
   TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};

   TTreeReaderValue<UInt_t> run = {fReader, "run"};
   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
   TTreeReaderArray<Float_t> Electron_dz = {fReader, "Electron_dz"};
   TTreeReaderArray<Float_t> Electron_r9 = {fReader, "Electron_r9"};
   TTreeReaderArray<Float_t> Electron_sieie = {fReader, "Electron_sieie"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaSpring16GP_WP80 = {fReader, "Electron_mvaSpring16GP_WP80"};
   TTreeReaderArray<Bool_t> Electron_mvaSpring16GP_WP90 = {fReader, "Electron_mvaSpring16GP_WP90"};
   TTreeReaderArray<Int_t> Electron_jetIdx = {fReader, "Electron_jetIdx"};
   TTreeReaderArray<Int_t> Electron_genPartIdx = {fReader, "Electron_genPartIdx"};
   TTreeReaderArray<Int_t> Electron_photonIdx = {fReader, "Electron_photonIdx"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_dxy = {fReader, "Muon_dxy"};
   TTreeReaderArray<Float_t> Muon_dz = {fReader, "Muon_dz"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};
   TTreeReaderArray<Int_t> Muon_nTrackerLayers = {fReader, "Muon_nTrackerLayers"};
   TTreeReaderArray<Int_t> Muon_jetIdx = {fReader, "Muon_jetIdx"};
   TTreeReaderArray<Int_t> Muon_genPartIdx = {fReader, "Muon_genPartIdx"};

   TTreeReaderValue<UInt_t> nPhoton = {fReader, "nPhoton"};
   TTreeReaderArray<Float_t> Photon_pt = {fReader, "Photon_pt"};
   TTreeReaderArray<Float_t> Photon_eta = {fReader, "Photon_eta"};
   TTreeReaderArray<Float_t> Photon_phi = {fReader, "Photon_phi"};
   TTreeReaderArray<Float_t> Photon_mass = {fReader, "Photon_mass"};
   TTreeReaderArray<Float_t> Photon_r9 = {fReader, "Photon_r9"};
   TTreeReaderArray<Float_t> Photon_sieie = {fReader, "Photon_sieie"};
   TTreeReaderArray<Int_t> Photon_jetIdx = {fReader, "Photon_jetIdx"};
   TTreeReaderArray<Int_t> Photon_genPartIdx = {fReader, "Photon_genPartIdx"};
   TTreeReaderArray<Bool_t> Photon_electronVeto = {fReader, "Photon_electronVeto"};
   TTreeReaderArray<Bool_t> Photon_pixelSeed = {fReader, "Photon_pixelSeed"};
   TTreeReaderArray<Bool_t> Photon_mvaID_WP90 = {fReader, "Photon_mvaID_WP90"};

   TTreeReaderValue<UInt_t> nJet = {fReader, "nJet"};
   TTreeReaderArray<Float_t> Jet_pt = {fReader, "Jet_pt"};
   TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
   TTreeReaderArray<Float_t> Jet_phi = {fReader, "Jet_phi"};
   TTreeReaderArray<Float_t> Jet_mass = {fReader, "Jet_mass"};
   TTreeReaderArray<Int_t> Jet_electronIdx1 = {fReader, "Jet_electronIdx1"};
   TTreeReaderArray<Int_t> Jet_electronIdx2 = {fReader, "Jet_electronIdx2"};
   TTreeReaderArray<Int_t> Jet_muonIdx1 = {fReader, "Jet_muonIdx1"};
   TTreeReaderArray<Int_t> Jet_muonIdx2 = {fReader, "Jet_muonIdx2"};
   TTreeReaderArray<Int_t> Jet_genJetIdx = {fReader, "Jet_genJetIdx"};

   TTreeReaderValue<Float_t> fixedGridRhoFastjetAll = {fReader, "fixedGridRhoFastjetAll"};

   TTreeReaderValue<Float_t> MET_phi = {fReader, "MET_phi"};
   TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
   TTreeReaderValue<Float_t> MET_significance = {fReader, "MET_significance"};

   TTreeReaderValue<UInt_t> nGenPart = {fReader, "nGenPart"};
   TTreeReaderArray<Float_t> GenPart_pt = {fReader, "GenPart_pt"};
   TTreeReaderArray<Float_t> GenPart_eta = {fReader, "GenPart_eta"};
   TTreeReaderArray<Float_t> GenPart_phi = {fReader, "GenPart_phi"};
   TTreeReaderArray<Float_t> GenPart_mass = {fReader, "GenPart_mass"};
   TTreeReaderArray<Int_t> GenPart_genPartIdxMother = {fReader, "GenPart_genPartIdxMother"};
   TTreeReaderArray<Int_t> GenPart_pdgId = {fReader, "GenPart_pdgId"};
   TTreeReaderArray<Int_t> GenPart_status = {fReader, "GenPart_status"};
   TTreeReaderArray<Int_t> GenPart_statusFlags = {fReader, "GenPart_statusFlags"};

   TTreeReaderValue<Float_t> MET_fiducialGenPhi = {fReader, "MET_fiducialGenPhi"};
   TTreeReaderValue<Float_t> MET_fiducialGenPt = {fReader, "MET_fiducialGenPt"};

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

   TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf = {fReader, "HLT_Ele27_WPTight_Gsf"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};

   TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
   TTreeReaderValue<Bool_t> HLT_IsoTkMu24 = {fReader, "HLT_IsoTkMu24"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL"};

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

   TTreeReaderValue<Bool_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
   TTreeReaderValue<Bool_t> Flag_METFilters = {fReader, "Flag_METFilters"};

#endif // defined(mainSelectorMC16_h)

#if defined(mainSelectorMC17_h)

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};
   TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};

   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
   TTreeReaderArray<Float_t> Electron_dz = {fReader, "Electron_dz"};
   TTreeReaderArray<Float_t> Electron_r9 = {fReader, "Electron_r9"};
   TTreeReaderArray<Float_t> Electron_sieie = {fReader, "Electron_sieie"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17Iso_WP90 = {fReader, "Electron_mvaFall17Iso_WP90"};
   TTreeReaderArray<Int_t> Electron_jetIdx = {fReader, "Electron_jetIdx"};
   TTreeReaderArray<Int_t> Electron_genPartIdx = {fReader, "Electron_genPartIdx"};
   TTreeReaderArray<Int_t> Electron_photonIdx = {fReader, "Electron_photonIdx"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_dxy = {fReader, "Muon_dxy"};
   TTreeReaderArray<Float_t> Muon_dz = {fReader, "Muon_dz"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};
   TTreeReaderArray<Int_t> Muon_nTrackerLayers = {fReader, "Muon_nTrackerLayers"};
   TTreeReaderArray<Int_t> Muon_jetIdx = {fReader, "Muon_jetIdx"};
   TTreeReaderArray<Int_t> Muon_genPartIdx = {fReader, "Muon_genPartIdx"};

   TTreeReaderValue<UInt_t> nPhoton = {fReader, "nPhoton"};
   TTreeReaderArray<Float_t> Photon_pt = {fReader, "Photon_pt"};
   TTreeReaderArray<Float_t> Photon_eta = {fReader, "Photon_eta"};
   TTreeReaderArray<Float_t> Photon_phi = {fReader, "Photon_phi"};
   TTreeReaderArray<Float_t> Photon_mass = {fReader, "Photon_mass"};
   TTreeReaderArray<Float_t> Photon_r9 = {fReader, "Photon_r9"};
   TTreeReaderArray<Float_t> Photon_sieie = {fReader, "Photon_sieie"};
   TTreeReaderArray<Int_t> Photon_jetIdx = {fReader, "Photon_jetIdx"};
   TTreeReaderArray<Int_t> Photon_genPartIdx = {fReader, "Photon_genPartIdx"};
   TTreeReaderArray<Bool_t> Photon_electronVeto = {fReader, "Photon_electronVeto"};
   TTreeReaderArray<Bool_t> Photon_pixelSeed = {fReader, "Photon_pixelSeed"};
   TTreeReaderArray<Bool_t> Photon_mvaID_WP90 = {fReader, "Photon_mvaID_WP90"};

   TTreeReaderValue<UInt_t> nJet = {fReader, "nJet"};
   TTreeReaderArray<Float_t> Jet_pt = {fReader, "Jet_pt"};
   TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
   TTreeReaderArray<Float_t> Jet_phi = {fReader, "Jet_phi"};
   TTreeReaderArray<Float_t> Jet_mass = {fReader, "Jet_mass"};
   TTreeReaderArray<Int_t> Jet_electronIdx1 = {fReader, "Jet_electronIdx1"};
   TTreeReaderArray<Int_t> Jet_electronIdx2 = {fReader, "Jet_electronIdx2"};
   TTreeReaderArray<Int_t> Jet_muonIdx1 = {fReader, "Jet_muonIdx1"};
   TTreeReaderArray<Int_t> Jet_muonIdx2 = {fReader, "Jet_muonIdx2"};
   TTreeReaderArray<Int_t> Jet_genJetIdx = {fReader, "Jet_genJetIdx"};

   TTreeReaderValue<Float_t> fixedGridRhoFastjetAll = {fReader, "fixedGridRhoFastjetAll"};

   TTreeReaderValue<Float_t> MET_phi = {fReader, "MET_phi"};
   TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
   TTreeReaderValue<Float_t> MET_significance = {fReader, "MET_significance"};

   TTreeReaderValue<UInt_t> nGenPart = {fReader, "nGenPart"};
   TTreeReaderArray<Float_t> GenPart_pt = {fReader, "GenPart_pt"};
   TTreeReaderArray<Float_t> GenPart_eta = {fReader, "GenPart_eta"};
   TTreeReaderArray<Float_t> GenPart_phi = {fReader, "GenPart_phi"};
   TTreeReaderArray<Float_t> GenPart_mass = {fReader, "GenPart_mass"};
   TTreeReaderArray<Int_t> GenPart_genPartIdxMother = {fReader, "GenPart_genPartIdxMother"};
   TTreeReaderArray<Int_t> GenPart_pdgId = {fReader, "GenPart_pdgId"};
   TTreeReaderArray<Int_t> GenPart_status = {fReader, "GenPart_status"};
   TTreeReaderArray<Int_t> GenPart_statusFlags = {fReader, "GenPart_statusFlags"};

   TTreeReaderValue<Float_t> MET_fiducialGenPhi = {fReader, "MET_fiducialGenPhi"};
   TTreeReaderValue<Float_t> MET_fiducialGenPt = {fReader, "MET_fiducialGenPt"};

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

   TTreeReaderValue<Bool_t> HLT_Ele35_WPTight_Gsf = {fReader, "HLT_Ele35_WPTight_Gsf"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};

   TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
   TTreeReaderValue<Bool_t> HLT_IsoMu27 = {fReader, "HLT_IsoMu27"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8"};

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

   TTreeReaderValue<Bool_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
   TTreeReaderValue<Bool_t> Flag_METFilters = {fReader, "Flag_METFilters"};

#endif // defined(mainSelectorMC17_h)

#if defined(mainSelectorMC18_h)

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};
   TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};

   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
   TTreeReaderArray<Float_t> Electron_dz = {fReader, "Electron_dz"};
   TTreeReaderArray<Float_t> Electron_r9 = {fReader, "Electron_r9"};
   TTreeReaderArray<Float_t> Electron_sieie = {fReader, "Electron_sieie"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP90 = {fReader, "Electron_mvaFall17V2Iso_WP90"};
   TTreeReaderArray<Int_t> Electron_jetIdx = {fReader, "Electron_jetIdx"};
   TTreeReaderArray<Int_t> Electron_genPartIdx = {fReader, "Electron_genPartIdx"};
   TTreeReaderArray<Int_t> Electron_photonIdx = {fReader, "Electron_photonIdx"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_dxy = {fReader, "Muon_dxy"};
   TTreeReaderArray<Float_t> Muon_dz = {fReader, "Muon_dz"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};
   TTreeReaderArray<Int_t> Muon_nTrackerLayers = {fReader, "Muon_nTrackerLayers"};
   TTreeReaderArray<Int_t> Muon_jetIdx = {fReader, "Muon_jetIdx"};
   TTreeReaderArray<Int_t> Muon_genPartIdx = {fReader, "Muon_genPartIdx"};

   TTreeReaderValue<UInt_t> nPhoton = {fReader, "nPhoton"};
   TTreeReaderArray<Float_t> Photon_pt = {fReader, "Photon_pt"};
   TTreeReaderArray<Float_t> Photon_eta = {fReader, "Photon_eta"};
   TTreeReaderArray<Float_t> Photon_phi = {fReader, "Photon_phi"};
   TTreeReaderArray<Float_t> Photon_mass = {fReader, "Photon_mass"};
   TTreeReaderArray<Float_t> Photon_r9 = {fReader, "Photon_r9"};
   TTreeReaderArray<Float_t> Photon_sieie = {fReader, "Photon_sieie"};
   TTreeReaderArray<Int_t> Photon_jetIdx = {fReader, "Photon_jetIdx"};
   TTreeReaderArray<Int_t> Photon_genPartIdx = {fReader, "Photon_genPartIdx"};
   TTreeReaderArray<Bool_t> Photon_electronVeto = {fReader, "Photon_electronVeto"};
   TTreeReaderArray<Bool_t> Photon_pixelSeed = {fReader, "Photon_pixelSeed"};
   TTreeReaderArray<Bool_t> Photon_mvaID_WP90 = {fReader, "Photon_mvaID_WP90"};

   TTreeReaderValue<UInt_t> nJet = {fReader, "nJet"};
   TTreeReaderArray<Float_t> Jet_pt = {fReader, "Jet_pt"};
   TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
   TTreeReaderArray<Float_t> Jet_phi = {fReader, "Jet_phi"};
   TTreeReaderArray<Float_t> Jet_mass = {fReader, "Jet_mass"};
   TTreeReaderArray<Int_t> Jet_electronIdx1 = {fReader, "Jet_electronIdx1"};
   TTreeReaderArray<Int_t> Jet_electronIdx2 = {fReader, "Jet_electronIdx2"};
   TTreeReaderArray<Int_t> Jet_muonIdx1 = {fReader, "Jet_muonIdx1"};
   TTreeReaderArray<Int_t> Jet_muonIdx2 = {fReader, "Jet_muonIdx2"};
   TTreeReaderArray<Int_t> Jet_genJetIdx = {fReader, "Jet_genJetIdx"};

   TTreeReaderValue<Float_t> fixedGridRhoFastjetAll = {fReader, "fixedGridRhoFastjetAll"};

   TTreeReaderValue<Float_t> MET_phi = {fReader, "MET_phi"};
   TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
   TTreeReaderValue<Float_t> MET_significance = {fReader, "MET_significance"};

   TTreeReaderValue<UInt_t> nGenPart = {fReader, "nGenPart"};
   TTreeReaderArray<Float_t> GenPart_pt = {fReader, "GenPart_pt"};
   TTreeReaderArray<Float_t> GenPart_eta = {fReader, "GenPart_eta"};
   TTreeReaderArray<Float_t> GenPart_phi = {fReader, "GenPart_phi"};
   TTreeReaderArray<Float_t> GenPart_mass = {fReader, "GenPart_mass"};
   TTreeReaderArray<Int_t> GenPart_genPartIdxMother = {fReader, "GenPart_genPartIdxMother"};
   TTreeReaderArray<Int_t> GenPart_pdgId = {fReader, "GenPart_pdgId"};
   TTreeReaderArray<Int_t> GenPart_status = {fReader, "GenPart_status"};
   TTreeReaderArray<Int_t> GenPart_statusFlags = {fReader, "GenPart_statusFlags"};

   TTreeReaderValue<Float_t> MET_fiducialGenPhi = {fReader, "MET_fiducialGenPhi"};
   TTreeReaderValue<Float_t> MET_fiducialGenPt = {fReader, "MET_fiducialGenPt"};

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

// FIXME
   TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf = {fReader, "HLT_Ele32_WPTight_Gsf"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};

   TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8"};
// FIXME

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

   TTreeReaderValue<Bool_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
   TTreeReaderValue<Bool_t> Flag_METFilters = {fReader, "Flag_METFilters"};

#endif // defined(mainSelectorMC18_h)

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

#endif

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

float getWeight(TH1* h, float x, float y) {
   if (h) {
     if (h->InheritsFrom("TH2")) {
       int binx = max(1, min(h->GetNbinsX(), h->GetXaxis()->FindBin(x)));
       int biny = max(1, min(h->GetNbinsY(), h->GetYaxis()->FindBin(y)));
       return h->GetBinContent(binx,biny);
     } else {
       int bin = max(1, min(h->GetNbinsX(), h->GetXaxis()->FindBin(x)));
       return h->GetBinContent(bin);
     }
   } else {
     cout << "ERROR! The weights input histogram is not loaded. Returning weight 0 !" << endl;
     return 0.;
  }
}

#endif // mainSelector_h
