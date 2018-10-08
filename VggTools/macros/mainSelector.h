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

class mainSelector : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   TH1D* h_nevt = 0;
   TH1D* h_Z_ele = 0;
   TH1D* h_Z_muo = 0;

   TH1D* h_npvs_ele = 0;
   TH1D* h_npvs_ele_w = 0;
   TH1D* h_npvs_muo = 0;
   TH1D* h_npvs_muo_w = 0;

#if defined(mainSelectorDT16_h) || defined(mainSelectorDT17_h) || defined(mainSelectorDT18_h)
#endif // defined(mainSelectorDT16_h) || defined(mainSelectorDT17_h) || defined(mainSelectorDT18_h)

#if defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)
   TH1D* h_Z_ele_gen = 0;
   TH1D* h_Z_muo_gen = 0;

   TH1D* pu_ele_weights = 0;
   TH1D* pu_muo_weights = 0;

   TH2D* sf_ele_eff = 0;
   TH2D* sf_ele_reco = 0;

   TH2D* sf_muo_id = 0;
   TH2D* sf_muo_iso = 0;
#endif // defined(mainSelectorMC16_h) || defined(mainSelectorMC17_h) || defined(mainSelectorMC18_h)

#if defined(mainSelectorDT16_h) 

   TTreeReaderValue<UInt_t> run = {fReader, "run"};
   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaSpring16GP_WP80 = {fReader, "Electron_mvaSpring16GP_WP80"};
   TTreeReaderArray<Bool_t> Electron_mvaSpring16GP_WP90 = {fReader, "Electron_mvaSpring16GP_WP90"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};

   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};

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

#endif // defined(mainSelectorDT16_h)

#if defined(mainSelectorDT17_h)

   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17Iso_WP90 = {fReader, "Electron_mvaFall17Iso_WP90"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};

   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"};

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

#endif // defined(mainSelectorDT17_h)

#if defined(mainSelectorDT18_h)

   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP90 = {fReader, "Electron_mvaFall17V2Iso_WP90"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};

   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"};

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

#endif // defined(mainSelectorDT18_h)

#if defined(mainSelectorMC16_h)

   TTreeReaderValue<UInt_t> run = {fReader, "run"};
   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaSpring16GP_WP80 = {fReader, "Electron_mvaSpring16GP_WP80"};
   TTreeReaderArray<Bool_t> Electron_mvaSpring16GP_WP90 = {fReader, "Electron_mvaSpring16GP_WP90"};
   
   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};

   TTreeReaderValue<UInt_t> nGenDressedLepton = {fReader, "nGenDressedLepton"};
   TTreeReaderArray<Float_t> GenDressedLepton_eta = {fReader, "GenDressedLepton_eta"};
   TTreeReaderArray<Float_t> GenDressedLepton_mass = {fReader, "GenDressedLepton_mass"};
   TTreeReaderArray<Float_t> GenDressedLepton_phi = {fReader, "GenDressedLepton_phi"};
   TTreeReaderArray<Float_t> GenDressedLepton_pt = {fReader, "GenDressedLepton_pt"};
   TTreeReaderArray<Int_t> GenDressedLepton_pdgId = {fReader, "GenDressedLepton_pdgId"};
   
   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};
   TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};

   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};

   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL"};

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

#endif // defined(mainSelectorMC16_h)

#if defined(mainSelectorMC17_h)

   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17Iso_WP90 = {fReader, "Electron_mvaFall17Iso_WP90"};

   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};

   TTreeReaderValue<UInt_t> nGenDressedLepton = {fReader, "nGenDressedLepton"};
   TTreeReaderArray<Float_t> GenDressedLepton_eta = {fReader, "GenDressedLepton_eta"};
   TTreeReaderArray<Float_t> GenDressedLepton_mass = {fReader, "GenDressedLepton_mass"};
   TTreeReaderArray<Float_t> GenDressedLepton_phi = {fReader, "GenDressedLepton_phi"};
   TTreeReaderArray<Float_t> GenDressedLepton_pt = {fReader, "GenDressedLepton_pt"};
   TTreeReaderArray<Int_t> GenDressedLepton_pdgId = {fReader, "GenDressedLepton_pdgId"};

   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};
   TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};

   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"};

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

#endif // defined(mainSelectorMC17_h)

#if defined(mainSelectorMC18_h)

   TTreeReaderValue<UInt_t> nElectron = {fReader, "nElectron"};
   TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
   TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
   TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
   TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
   TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
   TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP90 = {fReader, "Electron_mvaFall17V2Iso_WP90"};
   
   TTreeReaderValue<UInt_t> nMuon = {fReader, "nMuon"};
   TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
   TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
   TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
   TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
   TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
   TTreeReaderArray<Bool_t> Muon_tightId = {fReader, "Muon_tightId"};

   TTreeReaderValue<UInt_t> nGenDressedLepton = {fReader, "nGenDressedLepton"};
   TTreeReaderArray<Float_t> GenDressedLepton_eta = {fReader, "GenDressedLepton_eta"};
   TTreeReaderArray<Float_t> GenDressedLepton_mass = {fReader, "GenDressedLepton_mass"};
   TTreeReaderArray<Float_t> GenDressedLepton_phi = {fReader, "GenDressedLepton_phi"};
   TTreeReaderArray<Float_t> GenDressedLepton_pt = {fReader, "GenDressedLepton_pt"};
   TTreeReaderArray<Int_t> GenDressedLepton_pdgId = {fReader, "GenDressedLepton_pdgId"};
   
   TTreeReaderValue<Int_t> PV_npvs = {fReader, "PV_npvs"};
   TTreeReaderValue<Int_t> PV_npvsGood = {fReader, "PV_npvsGood"};
   TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};

   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};
   TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"};
   TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"};

   TTreeReaderValue<UInt_t> nTrigObj = {fReader, "nTrigObj"};
   TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
   TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
   TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
   TTreeReaderArray<Int_t> TrigObj_id = {fReader, "TrigObj_id"};
   TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};

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

float getWeight(TH1 *histogram_, float x, float y){
  if(histogram_==NULL) {
    cout << "ERROR! The weights input histogram is not loaded. Returning weight 0!" << endl;
    return 0.;
  }
  if(!histogram_->InheritsFrom("TH2")) {
    int bin = max(1, min(histogram_->GetNbinsX(), histogram_->GetXaxis()->FindBin(x)));
    return histogram_->GetBinContent(bin);
  } else {
    int binx = max(1, min(histogram_->GetNbinsX(), histogram_->GetXaxis()->FindBin(x)));
    int biny = max(1, min(histogram_->GetNbinsY(), histogram_->GetYaxis()->FindBin(y)));
    return histogram_->GetBinContent(binx,biny);
  }
}

#endif // mainSelector_h
