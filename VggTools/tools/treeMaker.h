//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 18 12:07:23 2018 by ROOT version 6.14/00
// from TChain Events/
//////////////////////////////////////////////////////////

#ifndef treeMaker_h
#define treeMaker_h

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

#define TAG_AND_PROBE_HLT

class treeMaker : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   float tag_Ele_pt = 0.;
   float tag_sc_eta = 0.;
   float tag_Ele_phi = 0.;
   float tag_Ele_q = 0.;
   float tag_Ele_trigMVA = 0.;

   float el_pt = 0.;
   float el_sc_eta = 0.;
   float el_q = 0.;

   float event_met_pfmet = 0.;
   float event_met_pfphi = 0.;

   int passingVeto94X = 0;
   int passingLoose94X = 0;
   int passingMedium94X = 0;
   int passingTight94X = 0;

   int HLTpath = 0;

   float totWeight = 0;
   float pair_mass = 0;
   float mcTrue = 0;

   TH1D* h_nevt = 0;

#if defined(treeMakerMC16_h) || defined(treeMakerMC17_h) || defined(treeMakerMC18_h)
   TH1D* pu_ele_weights = 0;
#endif // defined(treeMakerMC16_h) || defined(treeMakerMC17_h) || defined(treeMakerMC18_h)

   TTree* fitter_tree = 0;
   TFile* file = 0;

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};

   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Float_t> Electron_r9 = {fReader, "Electron_r9"};

   TTreeReaderArray<Int_t> Electron_cutBased = {fReader, "Electron_cutBased"};

   TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WP80 = {fReader, "Electron_mvaFall17V2noIso_WP80"};
   TTreeReaderArray<Float_t> Electron_mvaFall17V2noIso = {fReader, "Electron_mvaFall17V2noIso"};
#define Electron_mvaID_WP80 Electron_mvaFall17V2noIso_WP80
#define Electron_mvaID Electron_mvaFall17V2noIso

#if defined(NANOAODv4) && (defined(treeMakerDT17_h) || defined(treeMakerMC17_h))
    TTreeReaderValue<Float_t> METFixEE2017_phi = {fReader, "METFixEE2017_phi"};
    TTreeReaderValue<Float_t> METFixEE2017_pt = {fReader, "METFixEE2017_pt"};
#define MET_phi METFixEE2017_phi
#define MET_pt METFixEE2017_pt
#else
   TTreeReaderValue<Float_t> MET_phi = {fReader, "MET_phi"};
   TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
#endif // defined(NANOAODv4) && (defined(treeMakerDT17_h) || defined(treeMakerMC17_h))

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

   TTreeReaderValue<Bool_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
   TTreeReaderValue<Bool_t> Flag_METFilters = {fReader, "Flag_METFilters"};

#if defined(NANOAODv4) && (defined(treeMakerDT17_h) || defined(treeMakerMC17_h))
   TTreeReaderValue<UChar_t> Flag_ecalBadCalibFilterV2 = {fReader, "Flag_ecalBadCalibFilterV2"};
#endif // defined(NANOAODv4) && (defined(treeMakerDT17_h) || defined(treeMakerMC17_h))

#if defined(treeMakerDT16_h) || defined(treeMakerMC16_h)
   TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf = {fReader, "HLT_Ele27_WPTight_Gsf"};
#endif // defined(treeMakerDT16_h) || defined(treeMakerMC16_h)

#if defined(treeMakerDT17_h) || defined(treeMakerMC17_h)
   TTreeReaderValue<Bool_t> HLT_Ele35_WPTight_Gsf = {fReader, "HLT_Ele35_WPTight_Gsf"};
#endif // defined(treeMakerDT17_h) || defined(treeMakerMC17_h)

#if defined(treeMakerDT18_h) || defined(treeMakerMC18_h)
   TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf = {fReader, "HLT_Ele32_WPTight_Gsf"};
#endif // defined(treeMakerDT18_h) || defined(treeMakerMC18_h)

#if defined(treeMakerMC16_h) || defined(treeMakerMC17_h) || defined(treeMakerMC18_h)

   TTreeReaderValue<Float_t> Generator_weight = {fReader, "Generator_weight"};

   TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};

   TTreeReaderValue<UInt_t> nGenPart = {fReader, "nGenPart"};
   TTreeReaderArray<Float_t> GenPart_pt = {fReader, "GenPart_pt"};
   TTreeReaderArray<Float_t> GenPart_eta = {fReader, "GenPart_eta"};
   TTreeReaderArray<Float_t> GenPart_phi = {fReader, "GenPart_phi"};
   TTreeReaderArray<Float_t> GenPart_mass = {fReader, "GenPart_mass"};
   TTreeReaderArray<Int_t> GenPart_pdgId = {fReader, "GenPart_pdgId"};
   TTreeReaderArray<Int_t> GenPart_status = {fReader, "GenPart_status"};
   TTreeReaderArray<Int_t> GenPart_statusFlags = {fReader, "GenPart_statusFlags"};

#endif // defined(treeMakerMC16_h) || defined(treeMakerMC17_h) || defined(treeMakerMC18_h)

   treeMaker(TTree * /*tree*/ =0) { }
   virtual ~treeMaker() { }
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

   //ClassDef(treeMaker,0);

};

#endif // treeMaker_h

#ifdef treeMaker_cxx
void treeMaker::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t treeMaker::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

float getWeight(TH1* h, float x, float y, float variation = 0) {
   if (h) {
     if (h->InheritsFrom("TH2")) {
       int binx = max(1, min(h->GetNbinsX(), h->GetXaxis()->FindBin(x)));
       int biny = max(1, min(h->GetNbinsY(), h->GetYaxis()->FindBin(y)));
       return h->GetBinContent(binx,biny) + variation * h->GetBinError(binx,biny);
     } else {
       int bin = max(1, min(h->GetNbinsX(), h->GetXaxis()->FindBin(x)));
       return h->GetBinContent(bin) + variation * h->GetBinError(bin);
     }
   } else {
     cout << "ERROR! The weights input histogram is not loaded. Returning weight 0 !" << endl;
     return 0.;
  }
}

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
    }
    else if (cluster_r9 > 0. && cluster_r9 < 0.94) {
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
    }
    else if (cluster_r9 > 0. && cluster_r9 < 0.94){
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
    }
    else if (cluster_r9 > 0. && cluster_r9 < 0.94){
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
    }
    else if (cluster_r9 > 0. && cluster_r9 < 0.94){
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

#endif // treeMaker_cxx
