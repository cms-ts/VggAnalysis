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

#if defined(mainSelectorDT17B_cxx)
#define mainSelectorDT17_cxx
#endif // defined(mainSelectorDT17B_cxx)

#include "roccor.Run2.v2/RoccoR.cc"

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

   h_W_ele = new TH1D("h_W_ele", "h_W_ele", 100, 20., 200.);
   h_W_muo = new TH1D("h_W_muo", "h_W_muo", 100, 20., 200.);

   h_W_ele_npvs = new TH1D("h_W_ele_npvs", "h_W_ele_npvs", 100, 0., 100.);
   h_W_ele_npvs_w = new TH1D("h_W_ele_npvs_w", "h_W_ele_npvs_w", 100, 0., 100.);
   h_W_muo_npvs = new TH1D("h_W_muo_npvs", "h_W_muo_npvs", 100, 0., 100.);
   h_W_muo_npvs_w = new TH1D("h_W_muo_npvs_w", "h_W_muo_npvs_w", 100, 0., 100.);

   h_W_ele0_pt = new TH1D("h_W_ele0_pt", "h_W_ele0_pt", 100, 0., 200.);
   h_W_ele0_eta = new TH1D("h_W_ele0_eta", "h_W_ele0_eta", 50, -2.5, 2.5);
   h_W_ele0_phi = new TH1D("h_W_ele0_phi", "h_W_ele0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_ele_met_pt = new TH1D("h_W_ele_met_pt", "h_W_ele_met_pt", 100, 0., 200.);
   h_W_ele_met_phi = new TH1D("h_W_ele_met_phi", "h_W_ele_met_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_ele_met_sign = new TH1D("h_W_ele_met_sign", "h_W_ele_met_sign", 100, 0., 100.);
   h_W_muo0_pt = new TH1D("h_W_muo0_pt", "h_W_muo0_pt", 100, 0., 200.);
   h_W_muo0_eta = new TH1D("h_W_muo0_eta", "h_W_muo0_eta", 50, -2.5, 2.5);
   h_W_muo0_phi = new TH1D("h_W_muo0_phi", "h_W_muo0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_met_pt = new TH1D("h_W_muo_met_pt", "h_W_muo_met_pt", 100, 0., 200.);
   h_W_muo_met_phi = new TH1D("h_W_muo_met_phi", "h_W_muo_met_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_met_sign = new TH1D("h_W_muo_met_sign", "h_W_muo_met_sign", 100, 0., 100.);

   h_Z_ele = new TH1D("h_Z_ele", "h_Z_ele", 100, 71., 111.);
   h_Z_muo = new TH1D("h_Z_muo", "h_Z_muo", 100, 71., 111.);

   h_Z_ele_npvs = new TH1D("h_Z_ele_npvs", "h_Z_ele_npvs", 100, 0., 100.);
   h_Z_ele_npvs_w = new TH1D("h_Z_ele_npvs_w", "h_Z_ele_npvs_w", 100, 0., 100.);
   h_Z_muo_npvs = new TH1D("h_Z_muo_npvs", "h_Z_muo_npvs", 100, 0., 100.);
   h_Z_muo_npvs_w = new TH1D("h_Z_muo_npvs_w", "h_Z_muo_npvs_w", 100, 0., 100.);

   h_Z_ele0_pt = new TH1D("h_Z_ele0_pt", "h_Z_ele0_pt", 100, 0., 200.);
   h_Z_ele0_eta = new TH1D("h_Z_ele0_eta", "h_Z_ele0_eta", 50, -2.5, 2.5);
   h_Z_ele0_phi = new TH1D("h_Z_ele0_phi", "h_Z_ele0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_ele1_pt = new TH1D("h_Z_ele1_pt", "h_Z_ele1_pt", 100, 0., 200.);
   h_Z_ele1_eta = new TH1D("h_Z_ele1_eta", "h_Z_ele1_eta", 50, -2.5, 2.5);
   h_Z_ele1_phi = new TH1D("h_Z_ele1_phi", "h_Z_ele1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo0_pt = new TH1D("h_Z_muo0_pt", "h_Z_muo0_pt", 100, 0., 200.);
   h_Z_muo0_eta = new TH1D("h_Z_muo0_eta", "h_Z_muo0_eta", 50, -2.5, 2.5);
   h_Z_muo0_phi = new TH1D("h_Z_muo0_phi", "h_Z_muo0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo1_pt = new TH1D("h_Z_muo1_pt", "h_Z_muo1_pt", 100, 0., 200.);
   h_Z_muo1_eta = new TH1D("h_Z_muo1_eta", "h_Z_muo1_eta", 50, -2.5, 2.5);
   h_Z_muo1_phi = new TH1D("h_Z_muo1_phi", "h_Z_muo1_phi", 24, -TMath::Pi(), TMath::Pi());

   h_TrigObj = new TH2D("h_TrigObj", "h_TrigObj", 65, -0.5, 64.5, 25, -0.5, 24.5);

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   h_Z_ele_gen = new TH1D("h_Z_ele_gen", "h_Z_ele_gen", 100, 71., 111.);
   h_Z_muo_gen = new TH1D("h_Z_muo_gen", "h_Z_muo_gen", 100, 71., 111.);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   // add all booked histograms to the selector output list
   GetOutputList()->Add(h_nevt);

   GetOutputList()->Add(h_W_ele);
   GetOutputList()->Add(h_W_muo);

   GetOutputList()->Add(h_W_ele_npvs);
   GetOutputList()->Add(h_W_ele_npvs_w);
   GetOutputList()->Add(h_W_muo_npvs);
   GetOutputList()->Add(h_W_muo_npvs_w);

   GetOutputList()->Add(h_W_ele0_pt);
   GetOutputList()->Add(h_W_ele0_eta);
   GetOutputList()->Add(h_W_ele0_phi);
   GetOutputList()->Add(h_W_ele_met_pt);
   GetOutputList()->Add(h_W_ele_met_phi);
   GetOutputList()->Add(h_W_ele_met_sign);
   GetOutputList()->Add(h_W_muo0_pt);
   GetOutputList()->Add(h_W_muo0_eta);
   GetOutputList()->Add(h_W_muo0_phi);
   GetOutputList()->Add(h_W_muo_met_pt);
   GetOutputList()->Add(h_W_muo_met_phi);
   GetOutputList()->Add(h_W_muo_met_sign);

   GetOutputList()->Add(h_Z_ele);
   GetOutputList()->Add(h_Z_muo);

   GetOutputList()->Add(h_Z_ele_npvs);
   GetOutputList()->Add(h_Z_ele_npvs_w);
   GetOutputList()->Add(h_Z_muo_npvs);
   GetOutputList()->Add(h_Z_muo_npvs_w);

   GetOutputList()->Add(h_Z_ele0_pt);
   GetOutputList()->Add(h_Z_ele0_eta);
   GetOutputList()->Add(h_Z_ele0_phi);
   GetOutputList()->Add(h_Z_ele1_pt);
   GetOutputList()->Add(h_Z_ele1_eta);
   GetOutputList()->Add(h_Z_ele1_phi);
   GetOutputList()->Add(h_Z_muo0_pt);
   GetOutputList()->Add(h_Z_muo0_eta);
   GetOutputList()->Add(h_Z_muo0_phi);
   GetOutputList()->Add(h_Z_muo1_pt);
   GetOutputList()->Add(h_Z_muo1_eta);
   GetOutputList()->Add(h_Z_muo1_phi);
   
   GetOutputList()->Add(h_TrigObj);

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   GetOutputList()->Add(h_Z_ele_gen);
   GetOutputList()->Add(h_Z_muo_gen);

   TFile* file_ele_pu;
   TFile* file_muo_pu;

#if defined(mainSelectorMC16_cxx)
   file_ele_pu = TFile::Open("root/ratio_pileup_Run2016_DoubleEG_05Feb2018.root");
   file_muo_pu = TFile::Open("root/ratio_pileup_Run2016_DoubleMuon_05Feb2018.root");
   //file_ele_pu = TFile::Open("root/ratio_pileup_Run2016_DoubleEG_22Aug2018.root");
   //file_muo_pu = TFile::Open("root/ratio_pileup_Run2016_DoubleMuon_22Aug2018.root");

   //file_ele_pu = TFile::Open("root/ratio_pileup_Run2016_SingleElectron_05Feb2018.root");
   //file_muo_pu = TFile::Open("root/ratio_pileup_Run2016_SingleMuon_05Feb2018.root");
   //file_ele_pu = TFile::Open("root/ratio_pileup_Run2016_SingleElectron_22Aug2018.root");
   //file_muo_pu = TFile::Open("root/ratio_pileup_Run2016_SingleMuon_22Aug2018.root");
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   file_ele_pu = TFile::Open("root/ratio_pileup_Run2017_DoubleEG_31Mar2018.root");
   file_muo_pu = TFile::Open("root/ratio_pileup_Run2017_DoubleMuon_31Mar2018.root");
   //file_ele_pu = TFile::Open("root/ratio_pileup_Run2017_SingleElectron_31Mar2018.root");
   //file_muo_pu = TFile::Open("root/ratio_pileup_Run2017_SingleMuon_31Mar2018.root");
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   file_ele_pu = TFile::Open("root/ratio_pileup_Run2018_EGamma_14Sep2018.root");
   file_muo_pu = TFile::Open("root/ratio_pileup_Run2018_DoubleMuon_14Sep2018.root");
   //file_ele_pu = TFile::Open("root/ratio_pileup_Run2018_EGamma_14Sep2018.root");
   //file_muo_pu = TFile::Open("root/ratio_pileup_Run2018_SingleMuon_14Sep2018.root");
#endif // defined(mainSelectorMC18_cxx)

   pu_ele_weights = (TH1D*)file_ele_pu->Get("pu_weights");
   pu_muo_weights = (TH1D*)file_muo_pu->Get("pu_weights");

   pu_ele_weights->SetDirectory(0);
   pu_muo_weights->SetDirectory(0);

   file_ele_pu->Close();
   file_muo_pu->Close();

   TFile* file_ele_sf_eff;
   TFile* file_ele_sf_reco;

   TFile* file_muo_sf_id;
   TFile* file_muo_sf_iso;

#if defined(mainSelectorMC16_cxx) 
   file_ele_sf_eff = TFile::Open("root/sf_EGM2D_WP90_2016.root");
   //file_ele_sf_eff = TFile::Open("root/sf_EGM2D_WP80_2016.root");

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");

   sf_ele_eff->SetDirectory(0);

   file_ele_sf_eff->Close();

   file_muo_sf_id = TFile::Open("root/sf_muo_RunBCDEF_ID_2016.root");
   file_muo_sf_iso = TFile::Open("root/sf_muo_RunBCDEF_ISO_2016.root");

   sf_muo_id = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_eta_pt");
   sf_muo_iso = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");

   sf_muo_id->SetDirectory(0);
   sf_muo_iso->SetDirectory(0);

   file_muo_sf_id->Close();
   file_muo_sf_iso->Close();
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   file_ele_sf_eff = TFile::Open("root/sf_EGM2D_runBCDEF_passingMVA94Xwp90iso_2017.root");
   file_ele_sf_reco = TFile::Open("root/sf_reco_EGM2D_runBCDEF_passingRECO_2017.root");

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");
   sf_ele_reco = (TH2D*)file_ele_sf_reco->Get("EGamma_SF2D");

   sf_ele_eff->SetDirectory(0);
   sf_ele_reco->SetDirectory(0);

   file_ele_sf_eff->Close();
   file_ele_sf_reco->Close();

   file_muo_sf_id = TFile::Open("root/sf_muo_RunBCDEF_ID_2017.root");
   file_muo_sf_iso = TFile::Open("root/sf_muo_RunBCDEF_ISO_2017.root");

   sf_muo_id = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_pt_abseta");
   sf_muo_iso = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

   sf_muo_id->SetDirectory(0);
   sf_muo_iso->SetDirectory(0);

   file_muo_sf_id->Close();
   file_muo_sf_iso->Close();
#endif // defined(mainSelectorMC17_cxx)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
   roccor = new RoccoR("roccor.Run2.v2/RoccoR2016.txt");
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
   roccor = new RoccoR("roccor.Run2.v2/RoccoR2017.txt");
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
// FIXME
   roccor = new RoccoR("roccor.Run2.v2/RoccoR2017.txt");
// FIXME
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)

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

   bool W_ele_sel = false;
   bool W_muo_sel = false;

   bool Z_ele_sel = false;
   bool Z_muo_sel = false;

   float weight_pu_ele = 1.0;
   float weight_pu_muo = 1.0;
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   weight_pu_ele = getWeight(pu_ele_weights, *Pileup_nTrueInt, 0);
   weight_pu_muo = getWeight(pu_muo_weights, *Pileup_nTrueInt, 0);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   TLorentzVector ele0;
   TLorentzVector ele1;

   int iele0 = -1;
   int iele1 = -1;

   for (uint i = 0; i < *nElectron; i++) {
     if (*Flag_goodVertices == 0) continue;
     if (*Flag_METFilters == 0) continue;
     float eCorr_ele = 1.;
     if (Electron_pt[i]*eCorr_ele < 25) continue;
     if (fabs(Electron_eta[i]) > 1.442 && fabs(Electron_eta[i]) < 1.566) continue;
     if (fabs(Electron_eta[i]) > 2.500) continue;

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (Electron_mvaSpring16GP_WP90[i] == 0) continue;
     //if (Electron_mvaSpring16GP_WP80[i] == 0) continue;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (Electron_mvaFall17Iso_WP90[i] == 0) continue;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (Electron_mvaFall17V2Iso_WP90[i] == 0) continue;
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)

//     bool ele_trg = false;

     for (uint j = 0; j < *nTrigObj; j++) {
//       if (TrigObj_id[j] != 11) continue; 
//       if ((TrigObj_filterBits[j] & 0x1) == 0) continue; // 1 = CaloIdL_TrackIdL_IsoVL
//       if (((TrigObj_filterBits[j] & 0x2) == 0) && ((TrigObj_filterBits[j] & 0x4) == 0)) continue; // 2 = 1e (WPTight) || 4 = 1e (WPLoose)
       TLorentzVector tmp_sel;
       TLorentzVector tmp_trg;
       tmp_sel.SetPtEtaPhiM(Electron_pt[i], Electron_eta[i], Electron_phi[i], Electron_mass[i]);
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[j], TrigObj_eta[j], TrigObj_phi[j], Electron_mass[i]);
       if (tmp_sel.DeltaR(tmp_trg) > 0.1) continue;
//         ele_trg = true;
         for (uint k = 0; k < 64; k++) {
           if (TrigObj_filterBits[j] & k) h_TrigObj->Fill(TrigObj_filterBits[j] & k, TrigObj_id[j]);
         }
       break;
     }

//     if (ele_trg == 0) continue;

     if (iele0 != -1 && iele1 == -1 && Electron_charge[iele0] != Electron_charge[i]) {
       iele1 = i;
       ele1.SetPtEtaPhiM(Electron_pt[i]*eCorr_ele, Electron_eta[i], Electron_phi[i], Electron_mass[i]);
     }
     if (iele0 == -1) {
       iele0 = i;
       ele0.SetPtEtaPhiM(Electron_pt[i]*eCorr_ele, Electron_eta[i], Electron_phi[i], Electron_mass[i]);
     }
   }

   float W_ele_mt = 0.;

   if (iele0 != -1 && iele1 == -1) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_Ele27_WPTight_Gsf) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_Ele35_WPTight_Gsf) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Ele35_WPTight_Gsf) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       W_ele_mt = TMath::Sqrt(2. * ele0.Pt() * (*MET_pt) * (1. - TMath::Cos(ele0.Phi() - (*MET_phi))));
       if (*MET_pt > 40 && W_ele_mt > 40 && ele0.Pt() > 30) {
         W_ele_sel = true;
       }
     }
   }

   TLorentzVector Z_ele0_ele1;

   if (iele0 != -1 && iele1 != -1) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL || *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL || *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       Z_ele0_ele1 = ele0 + ele1;
       if (Z_ele0_ele1.M() >= 71. && Z_ele0_ele1.M() <= 111.) {
         Z_ele_sel = true;
       }
     }
   }

   float weight_W_ele = 1.;

   if (W_ele_sel) {
#if defined(mainSelectorMC16_cxx)
     float weight_eff_ele0 = getWeight(sf_ele_eff, ele0.Eta(), ele0.Pt());
     weight_W_ele = weight_pu_ele * weight_eff_ele0;
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
     float weight_eff_ele0 = getWeight(sf_ele_eff, ele0.Eta(), ele0.Pt());
     float weight_reco_ele0 = getWeight(sf_ele_reco, ele0.Eta(), ele0.Pt());
     float weight_hlt_ele = 0.991;
     weight_W_ele = weight_pu_ele * weight_eff_ele0 * weight_reco_ele0 * weight_hlt_ele;
#endif // defined(mainSelectorMC17_cxx)
   }

   float weight_Z_ele = 1.;

   if (Z_ele_sel) {
#if defined(mainSelectorMC16_cxx)
     float weight_eff_ele0 = getWeight(sf_ele_eff, ele0.Eta(), ele0.Pt());
     float weight_eff_ele1 = getWeight(sf_ele_eff, ele1.Eta(), ele1.Pt());
     weight_Z_ele = weight_pu_ele * weight_eff_ele0 * weight_eff_ele1;
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
     float weight_eff_ele0 = getWeight(sf_ele_eff, ele0.Eta(), ele0.Pt());
     float weight_eff_ele1 = getWeight(sf_ele_eff, ele1.Eta(), ele1.Pt());
     float weight_reco_ele0 = getWeight(sf_ele_reco, ele0.Eta(), ele0.Pt());
     float weight_reco_ele1 = getWeight(sf_ele_reco, ele1.Eta(), ele1.Pt());
     float weight_hlt_ele = 0.991;
     weight_Z_ele = weight_pu_ele * weight_eff_ele0 * weight_eff_ele1 * weight_reco_ele0 * weight_reco_ele1 * weight_hlt_ele;
#endif // defined(mainSelectorMC17_cxx)
   }

   TLorentzVector muo0;
   TLorentzVector muo1;

   int imuo0 = -1;
   int imuo1 = -1;

   for (uint i = 0; i < *nMuon; i++) {
     if (*Flag_goodVertices == 0) continue;
     if (*Flag_METFilters == 0) continue;
     float eCorr_muo = 1.0;
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
     eCorr_muo = roccor->kScaleDT(Muon_charge[i], Muon_pt[i], Muon_eta[i], Muon_phi[i], 0, 0);
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
     eCorr_muo = roccor->kSmearMC(Muon_charge[i], Muon_pt[i], Muon_eta[i], Muon_phi[i], Muon_nTrackerLayers[i], gRandom->Rndm(), 0, 0);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
     if (Muon_pt[i]*eCorr_muo < 25) continue;
     if (fabs(Muon_eta[i]) > 1.442 && fabs(Muon_eta[i]) < 1.566) continue;
     if (fabs(Muon_eta[i]) > 2.500) continue;

     if (Muon_tightId[i] == 0) continue;

//      bool muo_trg = false;

     for (uint j = 0; j < *nTrigObj; j++){
//       if (TrigObj_id[j] != 13) continue;
//       if ((TrigObj_filterBits[j] & 0x1) == 0) continue; // 1 = TrkIsoVVL
       TLorentzVector tmp_sel;
       TLorentzVector tmp_trg;
       tmp_sel.SetPtEtaPhiM(Muon_pt[i], Muon_eta[i], Muon_phi[i], Muon_mass[i]);
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[j], TrigObj_eta[j], TrigObj_phi[j], Muon_mass[i]);
       if (tmp_sel.DeltaR(tmp_trg) > 0.1) continue;
//       muo_trg = true;
       for (uint k = 0; k < 64; k++) {
         if (TrigObj_filterBits[j] & k) h_TrigObj->Fill(TrigObj_filterBits[j] & k, TrigObj_id[j]);
       }
       break;
     }

//   if (muo_trg == 0) continue;

     if (imuo0 != -1 && imuo1 == -1 && Muon_charge[imuo0] != Muon_charge[i]) {
       imuo1 = i;
       muo1.SetPtEtaPhiM(Muon_pt[i]*eCorr_muo, Muon_eta[i], Muon_phi[i], Muon_mass[i]);
     }
     if (imuo0 == -1) {
       imuo0 = i;
       muo0.SetPtEtaPhiM(Muon_pt[i]*eCorr_muo, Muon_eta[i], Muon_phi[i], Muon_mass[i]);
     }
   }

   float W_muo_mt = 0.;

   if (imuo0 != -1 && imuo1 == -1) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_IsoTkMu24 || *HLT_IsoMu24) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_IsoMu24 || *HLT_IsoMu27) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_IsoMu24) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       W_muo_mt = TMath::Sqrt(2. * muo0.Pt() * (*MET_pt) * (1. - TMath::Cos(muo0.Phi() - (*MET_phi))));
       if (*MET_pt > 20 && W_muo_mt > 40 && muo0.Pt() > 27) {
         W_muo_sel = true;
       }
     }
   }

   TLorentzVector Z_muo0_muo1;

   if (imuo0 != -1 && imuo1 != -1) {
#if defined(mainSelectorDT16_cxx)
     if ((*run <= 280385 && (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL    || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL   )) ||
         (*run >  280385 && (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ))) {
#endif // defined(mainSelectorDT16_cxx)
#if defined(mainSelectorMC16_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL) {
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17B_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ) {
#endif // defined(mainSelectorDT17B_cxx)
#if defined(mainSelectorDT17_cxx) && !defined(mainSelectorDT17B_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) {
#endif // defined(mainSelectorDT17_cxx) && !defined(mainSelectorDT17B_cxx)
#if defined(mainSelectorMC17_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) {
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       Z_muo0_muo1 = muo0 + muo1;
       if (Z_muo0_muo1.M() >= 71. && Z_muo0_muo1.M() <= 111.) {
         Z_muo_sel = true;
       }
     }
   }

   float weight_W_muo = 1.;

   if (W_muo_sel) {
#if defined(mainSelectorMC16_cxx)
     float weight_id_muo0 = getWeight(sf_muo_id, muo0.Eta(), muo0.Pt());
     float weight_iso_muo0 = getWeight(sf_muo_iso, muo0.Eta(), muo0.Pt());
     weight_W_muo = weight_pu_muo * weight_id_muo0 * weight_iso_muo0;
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
     float weight_id_muo0 = getWeight(sf_muo_id, muo0.Pt(), fabs(muo0.Eta()));
     float weight_iso_muo0 = getWeight(sf_muo_iso, muo0.Pt(), fabs(muo0.Eta()));
     weight_W_muo = weight_pu_muo * weight_id_muo0 * weight_iso_muo0;
#endif // defined(mainSelectorMC17_cxx)
   }

   float weight_Z_muo = 1.;

   if (Z_muo_sel) {
#if defined(mainSelectorMC16_cxx)
     float weight_id_muo0 = getWeight(sf_muo_id, muo0.Eta(), muo0.Pt());
     float weight_id_muo1 = getWeight(sf_muo_id, muo1.Eta(), muo1.Pt());
     float weight_iso_muo0 = getWeight(sf_muo_iso, muo0.Eta(), muo0.Pt());
     float weight_iso_muo1 = getWeight(sf_muo_iso, muo1.Eta(), muo1.Pt());
     weight_Z_muo = weight_pu_muo * weight_id_muo0 * weight_id_muo1 * weight_iso_muo0 * weight_iso_muo1;
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
     float weight_id_muo0 = getWeight(sf_muo_id, muo0.Pt(), fabs(muo0.Eta()));
     float weight_id_muo1 = getWeight(sf_muo_id, muo1.Pt(), fabs(muo1.Eta()));
     float weight_iso_muo0 = getWeight(sf_muo_iso, muo0.Pt(), fabs(muo0.Eta()));
     float weight_iso_muo1 = getWeight(sf_muo_iso, muo1.Pt(), fabs(muo1.Eta()));
     weight_Z_muo = weight_pu_muo * weight_id_muo0 * weight_id_muo1 * weight_iso_muo0 * weight_iso_muo1;
#endif // defined(mainSelectorMC17_cxx)
   }

   if (W_ele_sel) {
     if (h_W_ele) h_W_ele->Fill(W_ele_mt, weight_W_ele);
     if (h_W_ele_npvs) h_W_ele_npvs->Fill(*PV_npvsGood);
     if (h_W_ele_npvs_w) h_W_ele_npvs_w->Fill(*PV_npvsGood, weight_W_ele);
     if (h_W_ele0_pt) h_W_ele0_pt->Fill(ele0.Pt(), weight_W_ele);
     if (h_W_ele0_eta) h_W_ele0_eta->Fill(ele0.Eta(), weight_W_ele);
     if (h_W_ele0_phi) h_W_ele0_phi->Fill(ele0.Phi(), weight_W_ele);
     if (h_W_ele_met_pt) h_W_ele_met_pt->Fill(*MET_pt, weight_W_ele);
     if (h_W_ele_met_phi) h_W_ele_met_phi->Fill(*MET_phi, weight_W_ele);
     if (h_W_ele_met_sign) h_W_ele_met_sign->Fill(*MET_significance, weight_W_ele);
   }

   if (W_muo_sel) {
     if (h_W_muo) h_W_muo->Fill(W_muo_mt, weight_W_muo);
     if (h_W_muo_npvs) h_W_muo_npvs->Fill(*PV_npvsGood);
     if (h_W_muo_npvs_w) h_W_muo_npvs_w->Fill(*PV_npvsGood, weight_W_muo);
     if (h_W_muo0_pt) h_W_muo0_pt->Fill(muo0.Pt(), weight_W_muo);
     if (h_W_muo0_eta) h_W_muo0_eta->Fill(muo0.Eta(), weight_W_muo);
     if (h_W_muo0_phi) h_W_muo0_phi->Fill(muo0.Phi(), weight_W_muo);
     if (h_W_muo_met_pt) h_W_muo_met_pt->Fill(*MET_pt, weight_W_muo);
     if (h_W_muo_met_phi) h_W_muo_met_phi->Fill(*MET_phi, weight_W_muo);
     if (h_W_muo_met_sign) h_W_muo_met_sign->Fill(*MET_significance, weight_W_muo);
   }

   if (Z_ele_sel) {
     if (h_Z_ele) h_Z_ele->Fill(Z_ele0_ele1.M(), weight_Z_ele);
     if (h_Z_ele_npvs) h_Z_ele_npvs->Fill(*PV_npvsGood);
     if (h_Z_ele_npvs_w) h_Z_ele_npvs_w->Fill(*PV_npvsGood, weight_Z_ele);
     if (h_Z_ele0_pt) h_Z_ele0_pt->Fill(ele0.Pt(), weight_Z_ele);
     if (h_Z_ele0_eta) h_Z_ele0_eta->Fill(ele0.Eta(), weight_Z_ele);
     if (h_Z_ele0_phi) h_Z_ele0_phi->Fill(ele0.Phi(), weight_Z_ele);
     if (h_Z_ele1_pt) h_Z_ele1_pt->Fill(ele1.Pt(), weight_Z_ele);
     if (h_Z_ele1_eta) h_Z_ele1_eta->Fill(ele1.Eta(), weight_Z_ele);
     if (h_Z_ele1_phi) h_Z_ele1_phi->Fill(ele1.Phi(), weight_Z_ele);
   }

   if (Z_muo_sel) {
     if (h_Z_muo) h_Z_muo->Fill(Z_muo0_muo1.M(), weight_Z_muo);
     if (h_Z_muo_npvs) h_Z_muo_npvs->Fill(*PV_npvsGood);
     if (h_Z_muo_npvs_w) h_Z_muo_npvs_w->Fill(*PV_npvsGood, weight_Z_muo);
     if (h_Z_muo0_pt) h_Z_muo0_pt->Fill(muo0.Pt(), weight_Z_muo);
     if (h_Z_muo0_eta) h_Z_muo0_eta->Fill(muo0.Eta(), weight_Z_muo);
     if (h_Z_muo0_phi) h_Z_muo0_phi->Fill(muo0.Phi(), weight_Z_muo);
     if (h_Z_muo1_pt) h_Z_muo1_pt->Fill(muo1.Pt(), weight_Z_muo);
     if (h_Z_muo1_eta) h_Z_muo1_eta->Fill(muo1.Eta(), weight_Z_muo);
     if (h_Z_muo1_phi) h_Z_muo1_phi->Fill(muo1.Phi(), weight_Z_muo);
   }

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   bool Z_ele_sel_gen = false;
   bool Z_muo_sel_gen = false;

   TLorentzVector ele0_gen;
   TLorentzVector ele1_gen;
   TLorentzVector Z_ele0_ele1_gen;

   TLorentzVector muo0_gen;
   TLorentzVector muo1_gen;
   TLorentzVector Z_muo0_muo1_gen;

   int iele0_gen = -1;
   int iele1_gen = -1;
   int imuo0_gen = -1;
   int imuo1_gen = -1;

   for (uint i = 0; i < *nGenDressedLepton; i++) {
     if (fabs(GenDressedLepton_pdgId[i]) == 11) {
       if (GenDressedLepton_pt[i] < 20) continue;
       if (fabs(GenDressedLepton_eta[i]) > 1.442 && fabs(GenDressedLepton_eta[i]) < 1.566) continue;
       if (fabs(GenDressedLepton_eta[i]) > 2.500) continue;
       if (iele0_gen != -1 && iele1_gen == -1 && GenDressedLepton_pdgId[i] != GenDressedLepton_pdgId[iele0_gen]) {
         iele1_gen=i;
         ele1_gen.SetPtEtaPhiM(GenDressedLepton_pt[i], GenDressedLepton_eta[i], GenDressedLepton_phi[i], Electron_mass[i]);
       }
       if (iele0_gen == -1) {
         iele0_gen=i;
         ele0_gen.SetPtEtaPhiM(GenDressedLepton_pt[i], GenDressedLepton_eta[i], GenDressedLepton_phi[i], Electron_mass[i]);
       }
     }
     if (fabs(GenDressedLepton_pdgId[i]) == 13) {
       if (GenDressedLepton_pt[i] < 20) continue;
       if (fabs(GenDressedLepton_eta[i]) > 2.400) continue;
       if (imuo0_gen != -1 && imuo1_gen == -1 && GenDressedLepton_pdgId[i] != GenDressedLepton_pdgId[imuo0_gen]) {
         imuo1_gen=i;
         muo1_gen.SetPtEtaPhiM(GenDressedLepton_pt[i], GenDressedLepton_eta[i], GenDressedLepton_phi[i], Muon_mass[i]);
       }
       if (imuo0_gen == -1) {
         imuo0_gen=i;
         muo0_gen.SetPtEtaPhiM(GenDressedLepton_pt[i], GenDressedLepton_eta[i], GenDressedLepton_phi[i], Muon_mass[i]);
       }
     }
   }

   if (iele0_gen != -1 && iele1_gen != -1) {
     Z_ele0_ele1_gen = ele0_gen + ele1_gen;
     if (Z_ele0_ele1_gen.M() >= 71. && Z_ele0_ele1_gen.M() <= 111.) {
       Z_ele_sel_gen = true;
     }
   }

   if (imuo0_gen != -1 && imuo1_gen != -1) {
     Z_muo0_muo1_gen = muo0_gen + muo1_gen;
     if (Z_muo0_muo1_gen.M() >= 71. && Z_muo0_muo1_gen.M() <= 111.) {
       Z_muo_sel_gen = true;
     }
   }

   if (Z_ele_sel_gen) {
     if (h_Z_ele_gen) h_Z_ele_gen->Fill(Z_ele0_ele1_gen.M());
   }

   if (Z_muo_sel_gen) {
     if (h_Z_muo_gen) h_Z_muo_gen->Fill(Z_muo0_muo1_gen.M());
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

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

}
