#define mainSelector_cxx
// The class definition in mainSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("mainSelector.C")
// root> T->Process("mainSelector.C","some options")
// root> T->Process("mainSelector.C+")
//


#include "mainSelector.h"

#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TIterator.h>
#include <TFile.h>

void mainSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   Info("Begin", "options = %s", option.Data());

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

}

void mainSelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   // create the histograms
   h_nevt = new TH1D("h_nevt", "h_nevt", 10, 0., 10.);
   h_Z_ele = new TH1D("h_Z_ele", "h_Z_ele", 100, 60., 120.);
   h_Z_muo = new TH1D("h_Z_muo", "h_Z_muo", 100, 60., 120.);

   h_npvs = new TH1D("h_npvs", "h_npvs", 100, 0., 100.);
   h_npvs_w = new TH1D("h_npvs_w", "h_npvs_w", 100, 0., 100.);

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   h_Z_ele_gen = new TH1D("h_Z_ele_gen", "h_Z_ele_gen", 100, 60., 120.);
   h_Z_muo_gen = new TH1D("h_Z_muo_gen", "h_Z_muo_gen", 100, 60., 120.);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   // add all booked histograms to the selector output list
   GetOutputList()->Add(h_nevt);
   GetOutputList()->Add(h_Z_ele);
   GetOutputList()->Add(h_Z_muo);

   GetOutputList()->Add(h_npvs);
   GetOutputList()->Add(h_npvs_w);

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   GetOutputList()->Add(h_Z_ele_gen);
   GetOutputList()->Add(h_Z_muo_gen);

   TFile* file_ele;
   TFile* file_muo;
#if defined(mainSelectorMC16_cxx)
   file_ele = TFile::Open("root/ratio_pileup_Run2016_DoubleEG_22Aug2018.root");
   file_muo = TFile::Open("root/ratio_pileup_Run2016_DoubleMuon_22Aug2018.root");
   //file_ele = TFile::Open("root/ratio_pileup_Run2016_SingleElectron_22Aug2018.root");
   //file_muo = TFile::Open("root/ratio_pileup_Run2016_SingleMuon_22Aug2018.root");
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   file_ele = TFile::Open("root/ratio_pileup_Run2017_DoubleEG_31Mar2018.root");
   file_muo = TFile::Open("root/ratio_pileup_Run2017_DoubleMuon_31Mar2018.root");
   //file_ele = TFile::Open("root/ratio_pileup_Run2017_SingleElectron_31Mar2018.root");
   //file_muo = TFile::Open("root/ratio_pileup_Run2017_SingleMuon_31Mar2018.root");
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   file_ele = TFile::Open("root/ratio_pileup_Run2018_EGamma_14Sep2018.root");
   file_muo = TFile::Open("root/ratio_pileup_Run2018_DoubleMuon_14Sep2018.root");
   //file_ele = TFile::Open("root/ratio_pileup_Run2018_EGamma_14Sep2018.root");
   //file_muo = TFile::Open("root/ratio_pileup_Run2018_SingleMuon_14Sep2018.root");
#endif // defined(mainSelectorMC18_cxx)

   pu_ele_weights = (TH1D*)file_ele->Get("pu_weights");
   pu_muo_weights = (TH1D*)file_muo->Get("pu_weights");

   pu_ele_weights->SetDirectory(0);
   pu_muo_weights->SetDirectory(0);

   file_ele->Close();
   file_muo->Close();

#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
}

Bool_t mainSelector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetLocalEntry(entry);

   if (h_nevt) h_nevt->Fill(0.5);

   int weight = 1.0;
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   weight = 0.5*(getWeight(pu_ele_weights, *Pileup_nTrueInt, 0) +  getWeight(pu_muo_weights, *Pileup_nTrueInt, 0));
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   int iele0 = -1;
   int iele1 = -1;
   bool ele_sel = true;

   if (*nElectron < 2) ele_sel = false;
   for (uint i = 0; i < *nElectron; i++) {
     ele_sel = true;
     if (Electron_pt[i] < 20) ele_sel = false;
     if (fabs(Electron_eta[i]) > 1.442 && fabs(Electron_eta[i]) < 1.566) ele_sel = false;
     if (fabs(Electron_eta[i]) > 2.500) ele_sel = false;

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (Electron_mvaSpring16GP_WP90[i] == 0) ele_sel = false;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)

#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (Electron_mvaFall17Iso_WP90[i] == 0) ele_sel = false;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)

#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (Electron_mvaFall17V2Iso_WP90[i] == 0) ele_sel = false;
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)

     if (ele_sel) {
       if (iele0 != -1 && iele1 == -1 && Electron_charge[iele0] != Electron_charge[i]) {
         iele1 = i;
       }
       if (iele0 == -1) {
         iele0 = i;
       }
     }
   }

   if (iele0 != -1 && iele1 != -1) {
     TLorentzVector ele0;
     ele0.SetPtEtaPhiM(Electron_pt[iele0], Electron_eta[iele0], Electron_phi[iele0], Electron_mass[iele0]);
     TLorentzVector ele1;
     ele1.SetPtEtaPhiM(Electron_pt[iele1], Electron_eta[iele1], Electron_phi[iele1], Electron_mass[iele1]);
     TLorentzVector Z_ele = ele0 + ele1;
     if (h_Z_ele) h_Z_ele->Fill(Z_ele.M(), weight);
   }

   int imuo0 = -1;
   int imuo1 = -1;
   bool muo_sel = true;

   if (*nMuon < 2) muo_sel = false;
     for (uint i = 0; i < *nMuon; i++) {
     muo_sel = true;
     if (Muon_pt[i] < 20) muo_sel = false;
     if (fabs(Muon_eta[i]) > 1.442 && fabs(Muon_eta[i]) < 1.566) muo_sel = false;
     if (fabs(Muon_eta[i]) > 2.500) muo_sel = false;

     if (Muon_tightId[i] == 0) muo_sel = false;

     if (muo_sel) {
       if (imuo0 != -1 && imuo1 == -1 && Muon_charge[imuo0] != Muon_charge[i]) {
         imuo1 = i;
       }
       if (imuo0 == -1) {
         imuo0 = i;
       }
     }
   }

   if (imuo0 != -1 && imuo1 != -1) {
     TLorentzVector muo0;
     muo0.SetPtEtaPhiM(Muon_pt[imuo0], Muon_eta[imuo0], Muon_phi[imuo0], Muon_mass[imuo0]);
     TLorentzVector muo1;
     muo1.SetPtEtaPhiM(Muon_pt[imuo1], Muon_eta[imuo1], Muon_phi[imuo1], Muon_mass[imuo1]);
     TLorentzVector Z_muo = muo0 + muo1;
     if (h_Z_muo) h_Z_muo->Fill(Z_muo.M(), weight);
   }

   if ((iele0 != -1 && iele1 != -1) || (imuo0 != -1 && imuo1 != -1)) {
     if (h_npvs) h_npvs->Fill(*PV_npvs);
     if (h_npvs_w) h_npvs_w->Fill(*PV_npvs, weight);
   }

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   TLorentzVector muo0_gen;
   TLorentzVector muo1_gen;
   TLorentzVector Z_muo_gen;

   int iele0_gen = -1;
   int iele1_gen = -1;
   int imuo0_gen = -1;
   int imuo1_gen = -1;

   for (unsigned int i = 0; i < *nGenDressedLepton; i++) {
     if (fabs(GenDressedLepton_pdgId[i]) == 11) {
       bool ele_sel_gen = true;
       if (GenDressedLepton_pt[i] < 20) ele_sel_gen = false;
       if (fabs(GenDressedLepton_eta[i]) > 1.442 && fabs(GenDressedLepton_eta[i]) < 1.566) ele_sel_gen = false;
       if (fabs(GenDressedLepton_eta[i]) > 2.500) ele_sel_gen = false;
       if (ele_sel_gen) {
         if (iele0_gen != -1 && iele1_gen == -1 && GenDressedLepton_pdgId[i] != GenDressedLepton_pdgId[iele0_gen]) {
           iele1_gen=i;
         }
         if (iele0_gen == -1) {
           iele0_gen=i;
         }
       }
     }
     if (fabs(GenDressedLepton_pdgId[i]) == 13) {
       bool muo_sel_gen = true;
       if (GenDressedLepton_pt[i] < 20) muo_sel_gen = false;
       if (fabs(GenDressedLepton_eta[i]) > 2.400) muo_sel_gen = false;
       if (muo_sel_gen) {
         if (imuo0_gen != -1 && imuo1_gen == -1 && GenDressedLepton_pdgId[i] != GenDressedLepton_pdgId[imuo0_gen]) {
           imuo1_gen=i;
         }
         if (imuo0_gen == -1) {
           imuo0_gen=i;
         }
       }
     }
   }

   if (iele0_gen != -1 && iele1_gen != -1) {
     TLorentzVector ele0_gen;
     TLorentzVector ele1_gen;
     ele0_gen.SetPtEtaPhiM(GenDressedLepton_pt[iele0_gen], GenDressedLepton_eta[iele0_gen], GenDressedLepton_phi[iele0_gen], Electron_mass[iele0_gen]);
     ele1_gen.SetPtEtaPhiM(GenDressedLepton_pt[iele1_gen], GenDressedLepton_eta[iele1_gen], GenDressedLepton_phi[iele1_gen], Electron_mass[iele1_gen]);
     TLorentzVector Z_ele_gen = ele0_gen + ele1_gen;
     if (h_Z_ele_gen) h_Z_ele_gen->Fill(Z_ele_gen.M());
   }

   if (imuo0_gen != -1 && imuo1_gen != -1) {
     TLorentzVector muo0_gen;
     TLorentzVector muo1_gen;
     muo0_gen.SetPtEtaPhiM(GenDressedLepton_pt[imuo0_gen], GenDressedLepton_eta[imuo0_gen], GenDressedLepton_phi[imuo0_gen], Electron_mass[imuo0_gen]);
     muo1_gen.SetPtEtaPhiM(GenDressedLepton_pt[imuo1_gen], GenDressedLepton_eta[imuo1_gen], GenDressedLepton_phi[imuo1_gen], Electron_mass[imuo1_gen]);
     TLorentzVector Z_muo_gen = muo0_gen + muo1_gen;
     if (h_Z_muo_gen) h_Z_muo_gen->Fill(Z_muo_gen.M());
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   return kTRUE;
}

void mainSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void mainSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   TCanvas* c1 = new TCanvas("c1", "c1", 0, 0, 500, 500);

   h_Z_ele = dynamic_cast<TH1D*>(fOutput->FindObject("h_Z_ele"));
   h_Z_muo = dynamic_cast<TH1D*>(fOutput->FindObject("h_Z_muo"));

   c1->Divide(0,2);

   c1->cd(1);
   if (h_Z_ele) {
     h_Z_ele->Draw();
   } else {
     Warning("Terminate", "histogram not found");
   }
   c1->cd(2);
   if (h_Z_muo) {
     h_Z_muo->Draw();
   } else {
     Warning("Terminate", "histogram not found");
   }
   c1->Update();

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   TCanvas* c3 = new TCanvas("c3", "c3", 0, 0, 500, 500);

   h_Z_ele_gen = dynamic_cast<TH1D*>(fOutput->FindObject("h_Z_ele_gen"));
   h_Z_muo_gen = dynamic_cast<TH1D*>(fOutput->FindObject("h_Z_muo_gen"));

   c3->Divide(0,2);

   c3->cd(1);
   if (h_Z_ele_gen) {
     h_Z_ele_gen->Draw();
   } else {
     Warning("Terminate", "histogram not found");
   }
   c3->cd(2);
   if (h_Z_muo_gen) {
     h_Z_muo_gen->Draw();
   } else {
     Warning("Terminate", "histogram not found");
   }
   c3->Update();
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

}
