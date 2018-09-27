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

#ifdef mainSelectorDT_cxx
#endif // mainSelectorDT_cxx

#ifdef mainSelectorMC_cxx
#endif // mainSelectorMC_cxx

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

#ifdef mainSelectorDT_cxx
#endif // mainSelectorDT_cxx

#ifdef mainSelectorMC_cxx
   h_Z_ele_gen = new TH1D("h_Z_ele_gen", "h_Z_ele_gen", 100, 60., 120.);
   h_Z_muo_gen = new TH1D("h_Z_muo_gen", "h_Z_muo_gen", 100, 60., 120.);
#endif // mainSelectorMC_cxx

   // add all booked histograms to the selector output list
   GetOutputList()->Add(h_nevt);
   GetOutputList()->Add(h_Z_ele);
   GetOutputList()->Add(h_Z_muo);

#ifdef mainSelectorDT_cxx
#endif // mainSelectorDT_cxx

#ifdef mainSelectorMC_cxx
   GetOutputList()->Add(h_Z_ele_gen);
   GetOutputList()->Add(h_Z_muo_gen);
#endif // mainSelectorMC_cxx
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

   h_nevt->Fill(0.5);

   bool ele_sel = true;
   TLorentzVector ele0;
   TLorentzVector ele1;
   TLorentzVector Z_ele;

   if (*nElectron < 2) ele_sel = false;
   if (Electron_pt[0] < 20) ele_sel = false;
   if (Electron_pt[1] < 20) ele_sel = false;
   if (fabs(Electron_eta[0]) > 1.442 && fabs(Electron_eta[0]) < 1.566) ele_sel = false;
   if (fabs(Electron_eta[0]) > 2.500) ele_sel = false;
   if (fabs(Electron_eta[1]) > 1.442 && fabs(Electron_eta[1]) < 1.566) ele_sel = false;
   if (fabs(Electron_eta[1]) > 2.500) ele_sel = false;

   if (ele_sel) {
     ele0.SetPtEtaPhiM(Electron_pt[0],Electron_eta[0],Electron_phi[0],0.511/1000.);
     ele1.SetPtEtaPhiM(Electron_pt[1],Electron_eta[1],Electron_phi[1],0.511/1000.);
     Z_ele=ele0+ele1;
     if (h_Z_ele) h_Z_ele->Fill(Z_ele.M());
   }

   bool muo_sel = true;
   TLorentzVector muo0;
   TLorentzVector muo1;
   TLorentzVector Z_muo;

   if (*nMuon < 2) muo_sel = false;
   if (Muon_pt[0] < 20) muo_sel = false;
   if (Muon_pt[1] < 20) muo_sel = false;
   if (fabs(Muon_eta[0]) > 2.400) muo_sel = false;
   if (fabs(Muon_eta[1]) > 2.400) muo_sel = false;

   if (muo_sel) {
     muo0.SetPtEtaPhiM(Muon_pt[0],Muon_eta[0],Muon_phi[0],105.7/1000.);
     muo1.SetPtEtaPhiM(Muon_pt[1],Muon_eta[1],Muon_phi[1],105.7/1000.);
     Z_muo=muo0+muo1;
     if (h_Z_muo) h_Z_muo->Fill(Z_muo.M());
   }

#ifdef mainSelectorDT_cxx
#endif // mainSelectorDT_cxx

#ifdef mainSelectorMC_cxx

   bool ele_sel_gen = true;
   TLorentzVector ele0_gen;
   TLorentzVector ele1_gen;
   TLorentzVector Z_ele_gen;

   bool muo_sel_gen = true;
   TLorentzVector muo0_gen;
   TLorentzVector muo1_gen;
   TLorentzVector Z_muo_gen;

   int nElectron_gen=0;
   int nMuon_gen=0;

   for (unsigned int i = 0; i < *nGenDressedLepton; i++) {
     if (fabs(GenDressedLepton_pdgId[i]) == 11) {
       if (GenDressedLepton_pt[i] < 20) ele_sel_gen = false;
       if (fabs(GenDressedLepton_eta[i]) > 1.442 && fabs(GenDressedLepton_eta[i]) < 1.566) ele_sel_gen = false;
       if (fabs(GenDressedLepton_eta[i]) > 2.500) ele_sel_gen = false;
       if (ele_sel_gen) {
         if (nElectron_gen == 1) {
           ele1_gen.SetPtEtaPhiM(GenDressedLepton_pt[i],GenDressedLepton_eta[i],GenDressedLepton_phi[i],0.511/1000.);
           nElectron_gen++;
         }
         if (nElectron_gen == 0) {
           ele0_gen.SetPtEtaPhiM(GenDressedLepton_pt[i],GenDressedLepton_eta[i],GenDressedLepton_phi[i],0.511/1000.);
           nElectron_gen++;
         }
       }
     }
     if (fabs(GenDressedLepton_pdgId[i]) == 13) {
       if (GenDressedLepton_pt[i] < 20) muo_sel_gen = false;
       if (fabs(GenDressedLepton_eta[i]) > 2.400) muo_sel_gen = false;
       if (muo_sel_gen) {
         if (nMuon_gen == 1) {
           muo1_gen.SetPtEtaPhiM(GenDressedLepton_pt[i],GenDressedLepton_eta[i],GenDressedLepton_phi[i],105.7/1000.);
           nMuon_gen++;
         }
         if (nMuon_gen == 0) {
           muo0_gen.SetPtEtaPhiM(GenDressedLepton_pt[i],GenDressedLepton_eta[i],GenDressedLepton_phi[i],105.7/1000.);
           nMuon_gen++;
         }
       }
     }
   }

   if (nElectron_gen == 2) {
     Z_ele_gen=ele0_gen+ele1_gen;
     if (h_Z_ele_gen) h_Z_ele_gen->Fill(Z_ele_gen.M());
   }

   if (nMuon_gen == 2) {
     Z_muo_gen=muo0_gen+muo1_gen;
     if (h_Z_muo_gen) h_Z_muo_gen->Fill(Z_muo_gen.M());
   }
#endif // mainSelectorMC_cxx

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

#ifdef mainSelectorDT_cxx
#endif // mainSelectorDT_cxx

#ifdef mainSelectorMC_cxx
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
#endif // mainSelectorMC_cxx

}
