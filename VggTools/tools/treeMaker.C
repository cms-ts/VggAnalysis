#define treeMaker_cxx
// The class definition in treeMaker.h has been generated automatically
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
// root> T->Process("treeMaker.C")
// root> T->Process("treeMaker.C","some options")
// root> T->Process("treeMaker.C+")
//


#include "treeMaker.h"

#include <TDatime.h>
#include <TSystem.h>
#include <TRandom.h>
#include <TLorentzVector.h>

#if defined(treeMakerDT16H_cxx)
#define treeMakerDT16_cxx
#endif // defined(treeMakerDT16H_cxx)

#if defined(treeMakerDT17B_cxx)
#define treeMakerDT17_cxx
#endif // defined(treeMakerDT17B_cxx)

void treeMaker::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TDatime now;
   Info("Begin", "%s", now.AsSQLString());

#if defined(treeMakerMC16_cxx) || defined(treeMakerMC17_cxx) || defined(treeMakerMC18_cxx)
   string pileup_var = "";

#if defined(treeMakerMC16_cxx)
   TFile* file_ele_pu = new TFile(("../macros/root/ratio_pileup_" + pileup_var + "Run2016_SingleElectron_14Dec2018.root").c_str());
#endif // defined(treeMakerMC16_cxx)
#if defined(treeMakerMC17_cxx)
   TFile* file_ele_pu = new TFile(("../macros/root/ratio_pileup_" + pileup_var + "Run2017_SingleElectron_14Dec2018.root").c_str());
#endif // defined(treeMakerMC17_cxx)
#if defined(treeMakerMC18_cxx)
   TFile* file_ele_pu = new TFile(("../macros/root/ratio_pileup_" + pileup_var + "Run2018_EGamma_14Dec2018.root").c_str());
#endif // defined(treeMakerMC18_cxx)

   pu_ele_weights = (TH1D*)file_ele_pu->Get("pu_weights");
   pu_ele_weights->SetDirectory(0);

   file_ele_pu->Close();
   delete file_ele_pu;

   if (fInput && fInput->FindObject("auto_pu")) {
     Info("Begin", "%s : using auto_pu weights", now.AsSQLString());
     delete pu_ele_weights;
     pu_ele_weights = dynamic_cast<TH1D*>(fInput->FindObject("pu_ele_weights"));
   }
#endif // defined(treeMakerMC16_cxx) || defined(treeMakerMC17_cxx) || defined(treeMakerMC18_cxx)
}

void treeMaker::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TDatime now;
   Info("SlaveBegin", "%s", now.AsSQLString());

   // set random seed
   gRandom->SetSeed(gSystem->GetPid());

   // create the histograms
   h_nevt = new TH1D("h_nevt", "h_nevt", 10, 0., 10.);
//   h_Electron_cutBased = new TH1D()

   GetOutputList()->Add(h_nevt);

   if (fInput && fInput->FindObject("output")) {
     TNamed* name = dynamic_cast<TNamed*>(fInput->FindObject("output"));
     file = dynamic_cast<TFile*>(fInput->FindObject(name->GetTitle()));
     file->cd();
     TDirectoryFile* dir = new TDirectoryFile("tnpEleIDs","tnpEleIDs");
     dir->cd();
   }

   fitter_tree = new TTree("fitter_tree","fitter_tree");
   fitter_tree->Branch("tag_Ele_pt",&tag_Ele_pt,"tag_Ele_pt/F");
   fitter_tree->Branch("tag_sc_eta",&tag_sc_eta,"tag_sc_eta/F");
   fitter_tree->Branch("tag_Ele_phi",&tag_Ele_phi,"tag_Ele_phi/F");
   fitter_tree->Branch("tag_Ele_q",&tag_Ele_q,"tag_Ele_q/F");
   fitter_tree->Branch("tag_Ele_trigMVA",&tag_Ele_trigMVA,"tag_Ele_trigMVA/F");

   fitter_tree->Branch("el_pt",&el_pt,"el_pt/F");
   fitter_tree->Branch("el_sc_eta",&el_sc_eta,"el_sc_eta/F");
   fitter_tree->Branch("el_q",&el_q,"el_q/F");

   fitter_tree->Branch("event_met_pfmet",&event_met_pfmet,"event_met_pfmet/F");
   fitter_tree->Branch("event_met_pfphi",&event_met_pfphi,"event_met_pfphi/F");

   fitter_tree->Branch("passingVeto94X",&passingVeto94X,"passingVeto94X/I");
   fitter_tree->Branch("passingLoose94X",&passingLoose94X,"passingLoose94X/I");
   fitter_tree->Branch("passingMedium94X",&passingMedium94X,"passingMedium94X/I");
   fitter_tree->Branch("passingTight94X",&passingTight94X,"passingTight94X/I");

   fitter_tree->Branch("HLTpath",&HLTpath,"HLTpath/I");

   fitter_tree->Branch("totWeight",&totWeight,"totWeight/F");
   fitter_tree->Branch("pair_mass",&pair_mass,"pair_mass/F");
   fitter_tree->Branch("mcTrue",&mcTrue,"mcTrue/F");

//   fOutput->Add(fitter_tree);

//   fitter_tree->SetDirectory(dir);
//   fitter_tree->AutoSave();
}

Bool_t treeMaker::Process(Long64_t entry)
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

   float weight_gen = 1.;

#if defined(treeMakerMC16_cxx) || defined(treeMakerMC17_cxx) || defined(treeMakerMC18_cxx)
   weight_gen = *Generator_weight;
#endif // defined(treeMakerMC16_cxx) || defined(treeMakerMC17_cxx) || defined(treeMakerMC18_cxx)

   h_nevt->Fill(1.5, weight_gen);

   float weight_pu_ele = 1.;

#if defined(treeMakerMC16_cxx) || defined(treeMakerMC17_cxx) || defined(treeMakerMC18_cxx)
   weight_pu_ele = getWeight(pu_ele_weights, *Pileup_nTrueInt, 0);
#endif // defined(treeMakerMC16_cxx) || defined(treeMakerMC17_cxx) || defined(treeMakerMC18_cxx)

   h_nevt->Fill(2.5, weight_gen);

   if (*Flag_goodVertices == 0) return kTRUE;
   if (*Flag_METFilters == 0) return kTRUE;

#if defined(NANOAODv4) && (defined(treeMakerDT17_h) || defined(treeMakerMC17_h))
   if (*Flag_ecalBadCalibFilterV2 == 0) return kTRUE;
#endif // defined(NANOAODv4) && (defined(treeMakerDT17_h) || defined(treeMakerMC17_h))

   h_nevt->Fill(3.5, weight_gen);

// electrons

   int iele0 = -1;
   int iele1 = -1;

   if (!*HLT_Ele27_WPTight_Gsf) return kTRUE;

   for (uint i = 0; i < *nElectron; i++) {
     float eCorr_ele = 1.;
#if defined(treeMakerDT16_cxx) || defined(treeMakerDT17_cxx) || defined(treeMakerDT18_cxx)
// electron energy corrections not needed
#endif // defined(treeMakerDT16_cxx) || defined(treeMakerDT17_cxx) || defined(treeMakerDT18_cxx)
#if defined(treeMakerMC16_cxx) || defined(treeMakerMC17_cxx)
// electron energy corrections not needed
#endif // defined(treeMakerMC16_cxx) || defined(treeMakerMC17_cxx)
#if defined(treeMakerMC18_cxx)
     eCorr_ele = ecalSmearMC(Electron_pt[i], Electron_eta[i], Electron_phi[i], Electron_mass[i], Electron_r9[i], gRandom->Gaus());
#endif // defined(treeMakerMC18_cxx)
     Electron_pt[i] = Electron_pt[i] * eCorr_ele;
     if (Electron_pt[i] < 10) continue;
     if (fabs(Electron_eta[i]) > 2.500) continue;

     if (iele0 != -1) {
       if (Electron_charge[i] == Electron_charge[iele0]) {
         if (Electron_pt[i] > Electron_pt[iele0]) {
           iele0 = i;
         }
       } else {
         if (iele1 == -1) {
           iele1 = i;
         } else {
           if (Electron_pt[i] > Electron_pt[iele1]) {
             iele1 = i;
           }
         }
       }
     }
     if (iele0 == -1) iele0 = i;
   }

   if (iele0 != -1 && iele1 != -1) {
     if (Electron_pt[iele0] < 30 || (fabs(Electron_eta[iele0]) > 1.4442 && fabs(Electron_eta[iele0]) < 1.566) || fabs(Electron_eta[iele0]) > 2.100 || Electron_cutBased[iele0] != 4) iele0 = -1;
     if (iele0 == -1) iele1 = -1;
   }

   TLorentzVector ele0;
   TLorentzVector ele1;

   if (iele0 != -1) {
     ele0.SetPtEtaPhiM(Electron_pt[iele0], Electron_eta[iele0], Electron_phi[iele0], Electron_mass[iele0]);
   }
   if (iele1 != -1) {
     ele1.SetPtEtaPhiM(Electron_pt[iele1], Electron_eta[iele1], Electron_phi[iele1], Electron_mass[iele1]);
   }

   float Z_ele0_ele1_m = 0.;

   if (iele0 != -1 && iele1 != -1) {
     Z_ele0_ele1_m = (ele0 + ele1).M();
     if (Z_ele0_ele1_m >= 60. && Z_ele0_ele1_m <= 120.) {
       tag_Ele_pt = 0.;
       tag_sc_eta = 0.;
       tag_Ele_phi = 0.;
       tag_Ele_q = 0.;
       tag_Ele_trigMVA = 0.;
       el_pt = 0.;
       el_sc_eta = 0.;
       el_q = 0;
       event_met_pfmet = 0.;
       event_met_pfphi = 0.;
       passingVeto94X = 0;
       passingLoose94X = 0;
       passingMedium94X = 0;
       passingTight94X = 0;
       HLTpath = 0;
       totWeight = 1.;
       pair_mass = 0.;
       mcTrue = 1.;

       tag_Ele_pt = ele0.Pt();
       tag_sc_eta = ele0.Eta();
       tag_Ele_phi = ele0.Phi();
       tag_Ele_q = Electron_charge[iele0];
       tag_Ele_trigMVA = Electron_mvaID[iele0];

       el_pt = ele1.Pt();
       el_sc_eta = ele1.Eta();
       el_q = Electron_charge[iele1];

       event_met_pfmet = *MET_pt;
       event_met_pfphi = *MET_phi;

       if (Electron_cutBased[iele1] >= 1) passingVeto94X = 1;
       if (Electron_cutBased[iele1] >= 2) passingLoose94X = 1;
       if (Electron_cutBased[iele1] >= 3) passingMedium94X = 1;
       if (Electron_cutBased[iele1] == 4) passingTight94X = 1;

#if defined(treeMakerDT16_cxx) || defined(treeMakerMC16_cxx)
       if (*HLT_Ele27_WPTight_Gsf) {
#endif // defined(treeMakerDT16_cxx) || defined(treeMakerMC16_cxx)
#if defined(treeMakerDT17_cxx) || defined(treeMakerMC17_cxx)
       if (*HLT_Ele35_WPTight_Gsf) {
#endif // defined(treeMakerDT17_cxx) || defined(treeMakerMC17_cxx)
#if defined(treeMakerDT18_cxx) || defined(treeMakerMC18_cxx)
       if (*HLT_Ele32_WPTight_Gsf) {
#endif // defined(treeMakerDT18_cxx) || defined(treeMakerMC18_cxx)
         for (uint i = 0; i < *nTrigObj; i++) {
           if (HLTpath == 1) continue;
           if (TrigObj_id[i] != 11) continue;

           TLorentzVector tmp_trg;
           tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], ele1.M());
           if (ele1.DeltaR(tmp_trg) < 0.3) {
             if ((TrigObj_filterBits[i] &  2) ==  2) HLTpath = 1; //  2 = WPTight or 1e
           }
         }
       }
       totWeight = weight_gen * weight_pu_ele;
       pair_mass = Z_ele0_ele1_m;

       mcTrue = 0;

#if defined(treeMakerMC16_cxx) || defined(treeMakerMC17_cxx) || defined(treeMakerMC18_cxx)
       bool match0 = false;
       bool match1 = false;

       for (uint i = 0; i < *nGenPart; i++) {
         if (match0 && match1) continue;
         if (GenPart_status[i] != 1) continue;
         if (fabs(GenPart_pdgId[i]) != 11) continue;
         if ((GenPart_statusFlags[i] & 1) != 1) continue;
         if (GenPart_pt[i] < 10) continue;
         if (fabs(GenPart_eta[i]) > 2.500) continue;

         TLorentzVector tmp_ele_gen;
         tmp_ele_gen.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);
         if (tmp_ele_gen.DeltaR(ele0) < 0.2) match0 = true;
         if (tmp_ele_gen.DeltaR(ele1) < 0.2) match1 = true;
       }

       if (match0 && match1) mcTrue = 1;
#endif // defined(treeMakerMC16_cxx) || defined(treeMakerMC17_cxx) || defined(treeMakerMC18_cxx)

     }
     fitter_tree->Fill();
   }

   return kTRUE;
}

void treeMaker::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

   TDatime now;
   Info("SlaveTerminate", "%s", now.AsSQLString());

}

void treeMaker::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   TDatime now;
   Info("Terminate", "%s", now.AsSQLString());

   fitter_tree->Write();
   file->Close();
}
