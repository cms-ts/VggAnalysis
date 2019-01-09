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

#include <TDatime.h>
#include <TSystem.h>
#include <TRandom.h>
#include <TLorentzVector.h>

#if defined(mainSelectorDT16H_cxx)
#define mainSelectorDT16_cxx
#endif // defined(mainSelectorDT16H_cxx)

#if defined(mainSelectorDT17B_cxx)
#define mainSelectorDT17_cxx
#endif // defined(mainSelectorDT17B_cxx)

#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
#define AODv4
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)

#include "roccor.Run2.v2/RoccoR.cc"

void mainSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   TDatime now;
   Info("Begin", "%s : options = %s", now.AsSQLString(), option.Data());

   if (option.Contains("WJetsToLNu"))                    isWJetsToLNu = true;
   if (option.Contains("WG") && !option.Contains("WGG")) isWG         = true;
   if (option.Contains("WGG"))                           isWGG        = true;
   if (option.Contains("WTauNu"))                        isWTauNu     = true;

   if (option.Contains("DYJetsToLL"))                    isDYJetsToLL = true;
   if (option.Contains("ZG") && !option.Contains("ZGG")) isZG         = true;
   if (option.Contains("ZGG"))                           isZGG        = true;
   if (option.Contains("ZTauTau"))                       isZTauTau    = true;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   TFile* file_ele_pu;
   TFile* file_muo_pu;

#if defined(mainSelectorMC16_cxx)
   file_ele_pu = new TFile("root/ratio_pileup_Run2016_DoubleEG_22Aug2018.root");
   file_muo_pu = new TFile("root/ratio_pileup_Run2016_DoubleMuon_22Aug2018.root");
   //file_ele_pu = new TFile("root/ratio_pileup_Run2016_SingleElectron_22Aug2018.root");
   //file_muo_pu = new TFile("root/ratio_pileup_Run2016_SingleMuon_22Aug2018.root");
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   file_ele_pu = new TFile("root/ratio_pileup_Run2017_DoubleEG_31Mar2018.root");
   file_muo_pu = new TFile("root/ratio_pileup_Run2017_DoubleMuon_31Mar2018.root");
   //file_ele_pu = new TFile("root/ratio_pileup_Run2017_SingleElectron_31Mar2018.root");
   //file_muo_pu = new TFile("root/ratio_pileup_Run2017_SingleMuon_31Mar2018.root");
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   file_ele_pu = new TFile("root/ratio_pileup_Run2018_EGamma_14Sep2018.root");
   file_muo_pu = new TFile("root/ratio_pileup_Run2018_DoubleMuon_14Sep2018.root");
   //file_ele_pu = new TFile("root/ratio_pileup_Run2018_EGamma_14Sep2018.root");
   //file_muo_pu = new TFile("root/ratio_pileup_Run2018_SingleMuon_14Sep2018.root");
#endif // defined(mainSelectorMC18_cxx)

   pu_ele_weights = (TH1D*)file_ele_pu->Get("pu_weights");
   pu_muo_weights = (TH1D*)file_muo_pu->Get("pu_weights");

   pu_ele_weights->SetDirectory(0);
   pu_muo_weights->SetDirectory(0);

   file_ele_pu->Close();
   file_muo_pu->Close();

   delete file_ele_pu;
   delete file_muo_pu;

   TFile* file_ele_sf_eff;
   TFile* file_ele_sf_reco;

   TFile* file_muo_sf_id;
   TFile* file_muo_sf_iso;

   TFile* file_pho_sf_eff;

#if defined(mainSelectorMC16_cxx)
#if defined(AODv4)
   //file_ele_sf_eff = new TFile("root/sf_ele_2016_LegacyReReco_ElectronMVA80noiso_Fall17V2.root");
   file_ele_sf_eff = new TFile("root/sf_ele_2016_LegacyReReco_ElectronTight_Fall17V2.root");
#else
   //file_ele_sf_eff = new TFile("root/sf_ele_2016_LegacyReReco_ElectronMVAwp80.root");
   file_ele_sf_eff = new TFile("root/sf_ele_2016_LegacyReReco_ElectronTight.root");
#endif
   file_ele_sf_reco = new TFile("root/sf_ele_2016_EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root");

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");
   sf_ele_reco = (TH2D*)file_ele_sf_reco->Get("EGamma_SF2D");

   sf_ele_eff->SetDirectory(0);
   sf_ele_reco->SetDirectory(0);

   file_ele_sf_eff->Close();
   file_ele_sf_reco->Close();

   delete file_ele_sf_eff;
   delete file_ele_sf_reco;

   file_muo_sf_id = new TFile("root/sf_muo_2016_RunBCDEF_SF_ID.root");
   file_muo_sf_iso = new TFile("root/sf_muo_2016_RunBCDEF_SF_ISO.root");

   TH2D* sf_muo_id_RunBCDEF = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_eta_pt");
   TH2D* sf_muo_iso_RunBCDEF = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");

   sf_muo_id_RunBCDEF->SetDirectory(0);
   sf_muo_iso_RunBCDEF->SetDirectory(0);

   file_muo_sf_id->Close();
   file_muo_sf_iso->Close();

   delete file_muo_sf_id;
   delete file_muo_sf_iso;

   file_muo_sf_id = new TFile("root/sf_muo_2016_RunGH_SF_ID.root");
   file_muo_sf_iso = new TFile("root/sf_muo_2016_RunGH_SF_ISO.root");

   TH2D* sf_muo_id_RunGH = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_eta_pt");
   TH2D* sf_muo_iso_RunGH = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");

   sf_muo_id_RunGH->SetDirectory(0);
   sf_muo_iso_RunGH->SetDirectory(0);

   file_muo_sf_id->Close();
   file_muo_sf_iso->Close();

   delete file_muo_sf_id;
   delete file_muo_sf_iso;

   sf_muo_id = (TH2D*)sf_muo_id_RunBCDEF->Clone();
   sf_muo_iso = (TH2D*)sf_muo_iso_RunBCDEF->Clone();

   sf_muo_id->Add(sf_muo_id_RunBCDEF, sf_muo_id_RunGH, 19.69/35.917, 16.227/35.917);
   sf_muo_iso->Add(sf_muo_iso_RunBCDEF, sf_muo_iso_RunGH, 19.69/35.917, 16.227/35.917);

#if defined(AODv4)
   file_pho_sf_eff = new TFile("root/sf_pho_2016_LegacyReReco_PhotonsMVAwp90_Fall17V2.root");
#else
   file_pho_sf_eff = new TFile("root/sf_pho_2016_LegacyReReco_PhotonMVAWP90.root");
#endif

   sf_pho_eff = (TH2D*)file_pho_sf_eff->Get("EGamma_SF2D");

   sf_pho_eff->SetDirectory(0);

   file_pho_sf_eff->Close();

   delete file_pho_sf_eff;
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
#if defined(AODv4)
   //file_ele_sf_eff = new TFile("root/sf_ele_2017_ElectronMVA80noiso_Fall17V2.root");
   file_ele_sf_eff = new TFile("root/sf_ele_2017_ElectronTight_Fall17V2.root");
#else
   //file_ele_sf_eff = new TFile("root/sf_ele_2017_EGM2D_runBCDEF_passingMVA94Xwp80iso.root");
   file_ele_sf_eff = new TFile("root/sf_ele_2017_EGM2D_runBCDEF_passingTight94X.root");
#endif
   file_ele_sf_reco = new TFile("root/sf_ele_2017_EGM2D_runBCDEF_passingRECO.root");

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");
   sf_ele_reco = (TH2D*)file_ele_sf_reco->Get("EGamma_SF2D");

   sf_ele_eff->SetDirectory(0);
   sf_ele_reco->SetDirectory(0);

   file_ele_sf_eff->Close();
   file_ele_sf_reco->Close();

   delete file_ele_sf_eff;
   delete file_ele_sf_reco;

   file_muo_sf_id = new TFile("root/sf_muo_2017_RunBCDEF_SF_ID.root");
   file_muo_sf_iso = new TFile("root/sf_muo_2017_RunBCDEF_SF_ISO.root");

   sf_muo_id = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_pt_abseta");
   sf_muo_iso = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

   sf_muo_id->SetDirectory(0);
   sf_muo_iso->SetDirectory(0);

   file_muo_sf_id->Close();
   file_muo_sf_iso->Close();

   delete file_muo_sf_id;
   delete file_muo_sf_iso;

#if defined(AODv4)
   file_pho_sf_eff = new TFile("root/sf_pho_2017_PhotonsMVAwp90_Fall17V2.root");
#else
   file_pho_sf_eff = new TFile("root/sf_pho_2017_EGM2D_runBCDEF_passingMVA94Xwp90.root");
#endif

   sf_pho_eff = (TH2D*)file_pho_sf_eff->Get("EGamma_SF2D");

   sf_pho_eff->SetDirectory(0);

   file_pho_sf_eff->Close();

   delete file_pho_sf_eff;
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   //file_ele_sf_eff = new TFile("root/sf_ele_2018_ElectronMVA80noiso_Fall17V2.root");
   file_ele_sf_eff = new TFile("root/sf_ele_2018_ElectronTight_Fall17V2.root");
   file_ele_sf_reco = new TFile("root/sf_ele_2018_EGM2D_passingRECO.root");

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");
   sf_ele_reco = (TH2D*)file_ele_sf_reco->Get("EGamma_SF2D");

   sf_ele_eff->SetDirectory(0);
   sf_ele_reco->SetDirectory(0);

   file_ele_sf_eff->Close();
   file_ele_sf_reco->Close();

   delete file_ele_sf_eff;
   delete file_ele_sf_reco;

// FIXME
   file_muo_sf_id = new TFile("root/sf_muo_2017_RunBCDEF_SF_ID.root");
   file_muo_sf_iso = new TFile("root/sf_muo_2017_RunBCDEF_SF_ISO.root");
// FIXME

   sf_muo_id = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_pt_abseta");
   sf_muo_iso = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

   sf_muo_id->SetDirectory(0);
   sf_muo_iso->SetDirectory(0);

   file_muo_sf_id->Close();
   file_muo_sf_iso->Close();

   delete file_muo_sf_id;
   delete file_muo_sf_iso;

   file_pho_sf_eff = new TFile("root/sf_pho_2018_PhotonsMVAwp90_Fall17V2.root");

   sf_pho_eff = (TH2D*)file_pho_sf_eff->Get("EGamma_SF2D");

   sf_pho_eff->SetDirectory(0);

   file_pho_sf_eff->Close();

   delete file_pho_sf_eff;
#endif // defined(mainSelectorMC18_cxx)
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

#if defined(mainSelectorMC16_cxx)
   jet_resolution = new JME::JetResolution("jme/Summer16_25nsV1_MC_PtResolution_AK4PFchs.txt");
   jet_resolution_sf = new JME::JetResolutionScaleFactor("jme/Summer16_25nsV1_MC_SF_AK4PFchs.txt");
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   jet_resolution = new JME::JetResolution("jme/Fall17_V3_MC_PtResolution_AK4PFchs.txt");
   jet_resolution_sf = new JME::JetResolutionScaleFactor("jme/Fall17_V3_MC_SF_AK4PFchs.txt");
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
// FIXME
   jet_resolution = new JME::JetResolution("jme/Fall17_V3_MC_PtResolution_AK4PFchs.txt");
   jet_resolution_sf = new JME::JetResolutionScaleFactor("jme/Fall17_V3_MC_SF_AK4PFchs.txt");
// FIXME
#endif // defined(mainSelectorMC18_cxx)

}

void mainSelector::SlaveBegin(TTree * /*tree*/)
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

   h_W_ele = new TH1D("h_W_ele", "h_W_ele", 100, 0., 200.);
   h_W_muo = new TH1D("h_W_muo", "h_W_muo", 100, 0., 200.);

   h_W_ele_npvs = new TH1D("h_W_ele_npvs", "h_W_ele_npvs", 100, 0., 100.);
   h_W_ele_npvs_w = new TH1D("h_W_ele_npvs_w", "h_W_ele_npvs_w", 100, 0., 100.);
   h_W_muo_npvs = new TH1D("h_W_muo_npvs", "h_W_muo_npvs", 100, 0., 100.);
   h_W_muo_npvs_w = new TH1D("h_W_muo_npvs_w", "h_W_muo_npvs_w", 100, 0., 100.);

   h_W_ele0_pt = new TH1D("h_W_ele0_pt", "h_W_ele0_pt", 150, 0., 300.);
   h_W_ele0_eta = new TH1D("h_W_ele0_eta", "h_W_ele0_eta", 50, -2.5, 2.5);
   h_W_ele0_phi = new TH1D("h_W_ele0_phi", "h_W_ele0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_ele0_r9 = new TH1D("h_W_ele0_r9", "h_W_ele0_r9", 50, 0., 5.);
   h_W_ele0_sieie = new TH1D("h_W_ele0_sieie", "h_W_ele0_sieie", 50, 0., 0.05);
   h_W_ele_met_pt = new TH1D("h_W_ele_met_pt", "h_W_ele_met_pt", 150, 0., 300.);
   h_W_ele_met_phi = new TH1D("h_W_ele_met_phi", "h_W_ele_met_phi", 24, -TMath::Pi(), TMath::Pi());

   h_W_muo0_pt = new TH1D("h_W_muo0_pt", "h_W_muo0_pt", 150, 0., 300.);
   h_W_muo0_eta = new TH1D("h_W_muo0_eta", "h_W_muo0_eta", 50, -2.5, 2.5);
   h_W_muo0_phi = new TH1D("h_W_muo0_phi", "h_W_muo0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_met_pt = new TH1D("h_W_muo_met_pt", "h_W_muo_met_pt", 150, 0., 300.);
   h_W_muo_met_phi = new TH1D("h_W_muo_met_phi", "h_W_muo_met_phi", 24, -TMath::Pi(), TMath::Pi());

   h_W_ele0_mva = new TH1D("h_W_ele0_mva", "h_W_ele0_mva", 100, 0., 1.);

   h_W_ele0_pf_iso_all = new TH1D("h_W_ele0_pf_iso_all", "h_W_ele0_pf_iso_all", 100, 0.0, 0.2);
   h_W_ele0_pf_iso_chg = new TH1D("h_W_ele0_pf_iso_chg", "h_W_ele0_pf_iso_chg", 100, 0.0, 0.2);
   h_W_muo0_pf_iso_all = new TH1D("h_W_muo0_pf_iso_all", "h_W_muo0_pf_iso_all", 100, 0.0, 0.2);
   h_W_muo0_pf_iso_chg = new TH1D("h_W_muo0_pf_iso_chg", "h_W_muo0_pf_iso_chg", 100, 0.0, 0.2);

   h_Z_ele = new TH1D("h_Z_ele", "h_Z_ele", 80, 71., 111.);
   h_Z_muo = new TH1D("h_Z_muo", "h_Z_muo", 80, 71., 111.);

   h_Z_ele_npvs = new TH1D("h_Z_ele_npvs", "h_Z_ele_npvs", 100, 0., 100.);
   h_Z_ele_npvs_w = new TH1D("h_Z_ele_npvs_w", "h_Z_ele_npvs_w", 100, 0., 100.);
   h_Z_muo_npvs = new TH1D("h_Z_muo_npvs", "h_Z_muo_npvs", 100, 0., 100.);
   h_Z_muo_npvs_w = new TH1D("h_Z_muo_npvs_w", "h_Z_muo_npvs_w", 100, 0., 100.);

   h_Z_ele0_pt = new TH1D("h_Z_ele0_pt", "h_Z_ele0_pt", 150, 0., 300.);
   h_Z_ele0_eta = new TH1D("h_Z_ele0_eta", "h_Z_ele0_eta", 50, -2.5, 2.5);
   h_Z_ele0_phi = new TH1D("h_Z_ele0_phi", "h_Z_ele0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_ele0_r9 = new TH1D("h_Z_ele0_r9", "h_Z_ele0_r9", 50, 0., 5.);
   h_Z_ele0_sieie = new TH1D("h_Z_ele0_sieie", "h_Z_ele0_sieie", 50, 0., 0.05);
   h_Z_ele1_pt = new TH1D("h_Z_ele1_pt", "h_Z_ele1_pt", 150, 0., 300.);
   h_Z_ele1_eta = new TH1D("h_Z_ele1_eta", "h_Z_ele1_eta", 50, -2.5, 2.5);
   h_Z_ele1_phi = new TH1D("h_Z_ele1_phi", "h_Z_ele1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_ele1_r9 = new TH1D("h_Z_ele1_r9", "h_Z_ele1_r9", 50, 0., 5.);
   h_Z_ele1_sieie = new TH1D("h_Z_ele1_sieie", "h_Z_ele1_sieie", 50, 0., 0.05);
   h_Z_ele_met_pt = new TH1D("h_Z_ele_met_pt", "h_Z_ele_met_pt", 150, 0., 300.);
   h_Z_ele_met_phi = new TH1D("h_Z_ele_met_phi", "h_Z_ele_met_phi", 24, -TMath::Pi(), TMath::Pi());

   h_Z_muo0_pt = new TH1D("h_Z_muo0_pt", "h_Z_muo0_pt", 150, 0., 300.);
   h_Z_muo0_eta = new TH1D("h_Z_muo0_eta", "h_Z_muo0_eta", 50, -2.5, 2.5);
   h_Z_muo0_phi = new TH1D("h_Z_muo0_phi", "h_Z_muo0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo1_pt = new TH1D("h_Z_muo1_pt", "h_Z_muo1_pt", 150, 0., 300.);
   h_Z_muo1_eta = new TH1D("h_Z_muo1_eta", "h_Z_muo1_eta", 50, -2.5, 2.5);
   h_Z_muo1_phi = new TH1D("h_Z_muo1_phi", "h_Z_muo1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo_met_pt = new TH1D("h_Z_muo_met_pt", "h_Z_muo_met_pt", 150, 0., 300.);
   h_Z_muo_met_phi = new TH1D("h_Z_muo_met_phi", "h_Z_muo_met_phi", 24, -TMath::Pi(), TMath::Pi());

   h_Z_ele0_mva = new TH1D("h_Z_ele0_mva", "h_Z_ele0_mva", 100, 0., 1.);
   h_Z_ele1_mva = new TH1D("h_Z_ele1_mva", "h_Z_ele1_mva", 100, 0., 1.);

   h_Z_ele0_pf_iso_all = new TH1D("h_Z_ele0_pf_iso_all", "h_Z_ele0_pf_iso_all", 100, 0.0, 0.2);
   h_Z_ele0_pf_iso_chg = new TH1D("h_Z_ele0_pf_iso_chg", "h_Z_ele0_pf_iso_chg", 100, 0.0, 0.2);
   h_Z_ele1_pf_iso_all = new TH1D("h_Z_ele1_pf_iso_all", "h_Z_ele1_pf_iso_all", 100, 0.0, 0.2);
   h_Z_ele1_pf_iso_chg = new TH1D("h_Z_ele1_pf_iso_chg", "h_Z_ele1_pf_iso_chg", 100, 0.0, 0.2);
   h_Z_muo0_pf_iso_all = new TH1D("h_Z_muo0_pf_iso_all", "h_Z_muo0_pf_iso_all", 100, 0.0, 0.2);
   h_Z_muo0_pf_iso_chg = new TH1D("h_Z_muo0_pf_iso_chg", "h_Z_muo0_pf_iso_chg", 100, 0.0, 0.2);
   h_Z_muo1_pf_iso_all = new TH1D("h_Z_muo1_pf_iso_all", "h_Z_muo1_pf_iso_all", 100, 0.0, 0.2);
   h_Z_muo1_pf_iso_chg = new TH1D("h_Z_muo1_pf_iso_chg", "h_Z_muo1_pf_iso_chg", 100, 0.0, 0.2);

   h_W_ele_njets = new TH1D("h_W_ele_njets", "h_W_ele_njets", 10, -0.5, 9.5);
   h_W_ele_jet0_pt = new TH1D("h_W_ele_jet0_pt", "h_W_ele_jet0_pt", 150, 0., 300.);
   h_W_ele_jet0_eta = new TH1D("h_W_ele_jet0_eta", "h_W_ele_jet0_eta", 50, -2.5, 2.5);
   h_W_ele_jet0_phi = new TH1D("h_W_ele_jet0_phi", "h_W_ele_jet0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_njets = new TH1D("h_W_muo_njets", "h_W_muo_njets", 10, -0.5, 9.5);
   h_W_muo_jet0_pt = new TH1D("h_W_muo_jet0_pt", "h_W_muo_jet0_pt", 150, 0., 300.);
   h_W_muo_jet0_eta = new TH1D("h_W_muo_jet0_eta", "h_W_muo_jet0_eta", 50, -2.5, 2.5);
   h_W_muo_jet0_phi = new TH1D("h_W_muo_jet0_phi", "h_W_muo_jet0_phi", 24, -TMath::Pi(), TMath::Pi());

   h_Z_ele_njets = new TH1D("h_Z_ele_njets", "h_Z_ele_njets", 10, -0.5, 9.5);
   h_Z_ele_jet0_pt = new TH1D("h_Z_ele_jet0_pt", "h_Z_ele_jet0_pt", 150, 0., 300.);
   h_Z_ele_jet0_eta = new TH1D("h_Z_ele_jet0_eta", "h_Z_ele_jet0_eta", 50, -2.5, 2.5);
   h_Z_ele_jet0_phi = new TH1D("h_Z_ele_jet0_phi", "h_Z_ele_jet0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo_njets = new TH1D("h_Z_muo_njets", "h_Z_muo_njets", 10, -0.5, 9.5);
   h_Z_muo_jet0_pt = new TH1D("h_Z_muo_jet0_pt", "h_Z_muo_jet0_pt", 150, 0., 300.);
   h_Z_muo_jet0_eta = new TH1D("h_Z_muo_jet0_eta", "h_Z_muo_jet0_eta", 50, -2.5, 2.5);
   h_Z_muo_jet0_phi = new TH1D("h_Z_muo_jet0_phi", "h_Z_muo_jet0_phi", 24, -TMath::Pi(), TMath::Pi());

   h_W_ele_nphotons = new TH1D("h_W_ele_nphotons", "h_W_ele_nphotons", 6, -0.5, 5.5);
   h_W_ele_pho0_pt = new TH1D("h_W_ele_pho0_pt", "h_W_ele_pho0_pt", 75, 0., 300.);
   h_W_ele_pho0_eta = new TH1D("h_W_ele_pho0_eta", "h_W_ele_pho0_eta", 50, -2.5, 2.5);
   h_W_ele_pho0_phi = new TH1D("h_W_ele_pho0_phi", "h_W_ele_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_ele_pho0_r9 = new TH1D("h_W_ele_pho0_r9", "h_W_ele_pho0_r9", 50, 0., 5.);
   h_W_ele_pho0_sieie = new TH1D("h_W_ele_pho0_sieie", "h_W_ele_pho0_sieie", 50, 0., 0.05);
   h_W_ele_pho1_pt = new TH1D("h_W_ele_pho1_pt", "h_W_ele_pho1_pt", 75, 0., 300.);
   h_W_ele_pho1_eta = new TH1D("h_W_ele_pho1_eta", "h_W_ele_pho1_eta", 50, -2.5, 2.5);
   h_W_ele_pho1_phi = new TH1D("h_W_ele_pho1_phi", "h_W_ele_pho1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_ele_pho1_r9 = new TH1D("h_W_ele_pho1_r9", "h_W_ele_pho1_r9", 50, 0., 5.);
   h_W_ele_pho1_sieie = new TH1D("h_W_ele_pho1_sieie", "h_W_ele_pho1_sieie", 50, 0., 0.05);
   h_W_muo_nphotons = new TH1D("h_W_muo_nphotons", "h_W_muo_nphotons", 6, -0.5, 5.5);
   h_W_muo_pho0_pt = new TH1D("h_W_muo_pho0_pt", "h_W_muo_pho0_pt", 75, 0., 300.);
   h_W_muo_pho0_eta = new TH1D("h_W_muo_pho0_eta", "h_W_muo_pho0_eta", 50, -2.5, 2.5);
   h_W_muo_pho0_phi = new TH1D("h_W_muo_pho0_phi", "h_W_muo_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_pho0_r9 = new TH1D("h_W_muo_pho0_r9", "h_W_muo_pho0_r9", 50, 0., 5.);
   h_W_muo_pho0_sieie = new TH1D("h_W_muo_pho0_sieie", "h_W_muo_pho0_sieie", 50, 0., 0.05);
   h_W_muo_pho1_pt = new TH1D("h_W_muo_pho1_pt", "h_W_muo_pho1_pt", 75, 0., 300.);
   h_W_muo_pho1_eta = new TH1D("h_W_muo_pho1_eta", "h_W_muo_pho1_eta", 50, -2.5, 2.5);
   h_W_muo_pho1_phi = new TH1D("h_W_muo_pho1_phi", "h_W_muo_pho1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_pho1_r9 = new TH1D("h_W_muo_pho1_r9", "h_W_muo_pho1_r9", 50, 0., 5.);
   h_W_muo_pho1_sieie = new TH1D("h_W_muo_pho1_sieie", "h_W_muo_pho1_sieie", 50, 0., 0.05);

   h_W_ele_pho0_jet0_dR = new TH1D("h_W_ele_pho0_jet0_dR", "h_W_ele_pho0_jet0_dR", 50, 0., 5.);
   h_W_ele_pho1_jet0_dR = new TH1D("h_W_ele_pho1_jet0_dR", "h_W_ele_pho1_jet0_dR", 50, 0., 5.);
   h_W_muo_pho0_jet0_dR = new TH1D("h_W_muo_pho0_jet0_dR", "h_W_muo_pho0_jet0_dR", 50, 0., 5.);
   h_W_muo_pho1_jet0_dR = new TH1D("h_W_muo_pho1_jet0_dR", "h_W_muo_pho1_jet0_dR", 50, 0., 5.);

   h_W_ele_pho0_mva = new TH1D("h_W_ele_pho0_mva", "h_W_ele_pho0_mva", 100, 0., 1.);
   h_W_ele_pho1_mva = new TH1D("h_W_ele_pho1_mva", "h_W_ele_pho1_mva", 100, 0., 1.);
   h_W_muo_pho0_mva = new TH1D("h_W_muo_pho0_mva", "h_W_muo_pho0_mva", 100, 0., 1.);
   h_W_muo_pho1_mva = new TH1D("h_W_muo_pho1_mva", "h_W_muo_pho1_mva", 100, 0., 1.);

   h_W_ele_pho0_pf_iso_all = new TH1D("h_W_ele_pho0_pf_iso_all", "h_W_ele_pho0_pf_iso_all", 100, 0.0, 0.2);
   h_W_ele_pho0_pf_iso_chg = new TH1D("h_W_ele_pho0_pf_iso_chg", "h_W_ele_pho0_pf_iso_chg", 100, 0.0, 0.2);
   h_W_ele_pho1_pf_iso_all = new TH1D("h_W_ele_pho1_pf_iso_all", "h_W_ele_pho1_pf_iso_all", 100, 0.0, 0.2);
   h_W_ele_pho1_pf_iso_chg = new TH1D("h_W_ele_pho1_pf_iso_chg", "h_W_ele_pho1_pf_iso_chg", 100, 0.0, 0.2);
   h_W_muo_pho0_pf_iso_all = new TH1D("h_W_muo_pho0_pf_iso_all", "h_W_muo_pho0_pf_iso_all", 100, 0.0, 0.2);
   h_W_muo_pho0_pf_iso_chg = new TH1D("h_W_muo_pho0_pf_iso_chg", "h_W_muo_pho0_pf_iso_chg", 100, 0.0, 0.2);
   h_W_muo_pho1_pf_iso_all = new TH1D("h_W_muo_pho1_pf_iso_all", "h_W_muo_pho1_pf_iso_all", 100, 0.0, 0.2);
   h_W_muo_pho1_pf_iso_chg = new TH1D("h_W_muo_pho1_pf_iso_chg", "h_W_muo_pho1_pf_iso_chg", 100, 0.0, 0.2);

   h_Z_ele_nphotons = new TH1D("h_Z_ele_nphotons", "h_Z_ele_nphotons", 6, -0.5, 5.5);
   h_Z_ele_pho0_pt = new TH1D("h_Z_ele_pho0_pt", "h_Z_ele_pho0_pt", 75, 0., 300.);
   h_Z_ele_pho0_eta = new TH1D("h_Z_ele_pho0_eta", "h_Z_ele_pho0_eta", 50, -2.5, 2.5);
   h_Z_ele_pho0_phi = new TH1D("h_Z_ele_pho0_phi", "h_Z_ele_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_ele_pho0_r9 = new TH1D("h_Z_ele_pho0_r9", "h_Z_ele_pho0_r9", 50, 0., 5.);
   h_Z_ele_pho0_sieie = new TH1D("h_Z_ele_pho0_sieie", "h_Z_ele_pho0_sieie", 50, 0., 0.05);
   h_Z_ele_pho1_pt = new TH1D("h_Z_ele_pho1_pt", "h_Z_ele_pho1_pt", 75, 0., 300.);
   h_Z_ele_pho1_eta = new TH1D("h_Z_ele_pho1_eta", "h_Z_ele_pho1_eta", 50, -2.5, 2.5);
   h_Z_ele_pho1_phi = new TH1D("h_Z_ele_pho1_phi", "h_Z_ele_pho1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_ele_pho1_r9 = new TH1D("h_Z_ele_pho1_r9", "h_Z_ele_pho1_r9", 50, 0., 5.);
   h_Z_ele_pho1_sieie = new TH1D("h_Z_ele_pho1_sieie", "h_Z_ele_pho1_sieie", 50, 0., 0.05);
   h_Z_muo_nphotons = new TH1D("h_Z_muo_nphotons", "h_Z_muo_nphotons", 6, -0.5, 5.5);
   h_Z_muo_pho0_pt = new TH1D("h_Z_muo_pho0_pt", "h_Z_muo_pho0_pt", 75, 0., 300.);
   h_Z_muo_pho0_eta = new TH1D("h_Z_muo_pho0_eta", "h_Z_muo_pho0_eta", 50, -2.5, 2.5);
   h_Z_muo_pho0_phi = new TH1D("h_Z_muo_pho0_phi", "h_Z_muo_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo_pho0_r9 = new TH1D("h_Z_muo_pho0_r9", "h_Z_muo_pho0_r9", 50, 0., 5.);
   h_Z_muo_pho0_sieie = new TH1D("h_Z_muo_pho0_sieie", "h_Z_muo_pho0_sieie", 50, 0., 0.05);
   h_Z_muo_pho1_pt = new TH1D("h_Z_muo_pho1_pt", "h_Z_muo_pho1_pt", 75, 0., 300.);
   h_Z_muo_pho1_eta = new TH1D("h_Z_muo_pho1_eta", "h_Z_muo_pho1_eta", 50, -2.5, 2.5);
   h_Z_muo_pho1_phi = new TH1D("h_Z_muo_pho1_phi", "h_Z_muo_pho1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo_pho1_r9 = new TH1D("h_Z_muo_pho1_r9", "h_Z_muo_pho1_r9", 50, 0., 5.);
   h_Z_muo_pho1_sieie = new TH1D("h_Z_muo_pho1_sieie", "h_Z_muo_pho1_sieie", 50, 0., 0.05);

   h_Z_ele_pho0_jet0_dR = new TH1D("h_Z_ele_pho0_jet0_dR", "h_Z_ele_pho0_jet0_dR", 50, 0., 5.);
   h_Z_ele_pho1_jet0_dR = new TH1D("h_Z_ele_pho1_jet0_dR", "h_Z_ele_pho1_jet0_dR", 50, 0., 5.);
   h_Z_muo_pho0_jet0_dR = new TH1D("h_Z_muo_pho0_jet0_dR", "h_Z_muo_pho0_jet0_dR", 50, 0., 5.);
   h_Z_muo_pho1_jet0_dR = new TH1D("h_Z_muo_pho1_jet0_dR", "h_Z_muo_pho1_jet0_dR", 50, 0., 5.);

   h_Z_ele_pho0_mva = new TH1D("h_Z_ele_pho0_mva", "h_Z_ele_pho0_mva", 100, 0., 1.);
   h_Z_ele_pho1_mva = new TH1D("h_Z_ele_pho1_mva", "h_Z_ele_pho1_mva", 100, 0., 1.);
   h_Z_muo_pho0_mva = new TH1D("h_Z_muo_pho0_mva", "h_Z_muo_pho0_mva", 100, 0., 1.);
   h_Z_muo_pho1_mva = new TH1D("h_Z_muo_pho1_mva", "h_Z_muo_pho1_mva", 100, 0., 1.);

   h_Z_ele_pho0_pf_iso_all = new TH1D("h_Z_ele_pho0_pf_iso_all", "h_Z_ele_pho0_pf_iso_all", 100, 0.0, 0.2);
   h_Z_ele_pho0_pf_iso_chg = new TH1D("h_Z_ele_pho0_pf_iso_chg", "h_Z_ele_pho0_pf_iso_chg", 100, 0.0, 0.2);
   h_Z_ele_pho1_pf_iso_all = new TH1D("h_Z_ele_pho1_pf_iso_all", "h_Z_ele_pho1_pf_iso_all", 100, 0.0, 0.2);
   h_Z_ele_pho1_pf_iso_chg = new TH1D("h_Z_ele_pho1_pf_iso_chg", "h_Z_ele_pho1_pf_iso_chg", 100, 0.0, 0.2);
   h_Z_muo_pho0_pf_iso_all = new TH1D("h_Z_muo_pho0_pf_iso_all", "h_Z_muo_pho0_pf_iso_all", 100, 0.0, 0.2);
   h_Z_muo_pho0_pf_iso_chg = new TH1D("h_Z_muo_pho0_pf_iso_chg", "h_Z_muo_pho0_pf_iso_chg", 100, 0.0, 0.2);
   h_Z_muo_pho1_pf_iso_all = new TH1D("h_Z_muo_pho1_pf_iso_all", "h_Z_muo_pho1_pf_iso_all", 100, 0.0, 0.2);
   h_Z_muo_pho1_pf_iso_chg = new TH1D("h_Z_muo_pho1_pf_iso_chg", "h_Z_muo_pho1_pf_iso_chg", 100, 0.0, 0.2);

   h_W_ele_pho0_dR = new TH1D("h_W_ele_pho0_dR", "h_W_ele_pho0_dR", 50, 0., 5.);
   h_W_ele_pho1_dR = new TH1D("h_W_ele_pho1_dR", "h_W_ele_pho1_dR", 50, 0., 5.);
   h_W_muo_pho0_dR = new TH1D("h_W_muo_pho0_dR", "h_W_muo_pho0_dR", 50, 0., 5.);
   h_W_muo_pho1_dR = new TH1D("h_W_muo_pho1_dR", "h_W_muo_pho1_dR", 50, 0., 5.);
   h_Z_ele_pho0_dR = new TH1D("h_Z_ele_pho0_dR", "h_Z_ele_pho0_dR", 50, 0., 5.);
   h_Z_ele_pho1_dR = new TH1D("h_Z_ele_pho1_dR", "h_Z_ele_pho1_dR", 50, 0., 5.);
   h_Z_muo_pho0_dR = new TH1D("h_Z_muo_pho0_dR", "h_Z_muo_pho0_dR", 50, 0., 5.);
   h_Z_muo_pho1_dR = new TH1D("h_Z_muo_pho1_dR", "h_Z_muo_pho1_dR", 50, 0., 5.);

   h_W_ele_pho0 = new TH1D("h_W_ele_pho0", "h_W_ele_pho0", 100, 0, 200);
   h_W_muo_pho0 = new TH1D("h_W_muo_pho0", "h_W_muo_pho0", 100, 0, 200);
   h_Z_ele_pho0 = new TH1D("h_Z_ele_pho0", "h_Z_ele_pho0", 40, 71, 111);
   h_Z_muo_pho0 = new TH1D("h_Z_muo_pho0", "h_Z_muo_pho0", 40, 71, 111);

   h_W_ele_pho0_pho1_pt = new TH1D("h_W_ele_pho0_pho1_pt", "h_W_ele_pho0_pho1_pt", 30, 0., 300.);
   h_W_ele_ele0_pho0 = new TH1D("h_W_ele_ele0_pho0", "h_W_ele_ele0_pho0", 100, 0., 200.);
   h_W_ele_ele0_pho1 = new TH1D("h_W_ele_ele0_pho1", "h_W_ele_ele0_pho1", 20, 0., 200.);
   h_W_ele_ele0_pho0_pho1 = new TH1D("h_W_ele_ele0_pho0_pho1", "h_W_ele_ele0_pho0_pho1", 20, 0., 200.);

   h_W_muo_pho0_pho1_pt = new TH1D("h_W_muo_pho0_pho1_pt", "h_W_muo_pho0_pho1_pt", 30, 0., 300.);
   h_W_muo_muo0_pho0 = new TH1D("h_W_muo_muo0_pho0", "h_W_muo_muo0_pho0", 100, 0., 200.);
   h_W_muo_muo0_pho1 = new TH1D("h_W_muo_muo0_pho1", "h_W_muo_muo0_pho1", 20, 0., 200.);
   h_W_muo_muo0_pho0_pho1 = new TH1D("h_W_muo_muo0_pho0_pho1", "h_W_muo_muo0_pho0_pho1", 20, 0., 200.);

   h_Z_ele_pho0_pho1_pt = new TH1D("h_Z_ele_pho0_pho1_pt", "h_Z_ele_pho0_pho1_pt", 30, 0., 300.);
   h_Z_ele_ele0_pho0 = new TH1D("h_Z_ele_ele0_pho0", "h_Z_ele_ele0_pho0", 40, 71., 111.);
   h_Z_ele_ele0_pho1 = new TH1D("h_Z_ele_ele0_pho1", "h_Z_ele_ele0_pho1", 40, 71., 111.);
   h_Z_ele_ele1_pho0 = new TH1D("h_Z_ele_ele1_pho0", "h_Z_ele_ele1_pho0", 40, 71., 111.);
   h_Z_ele_ele1_pho1 = new TH1D("h_Z_ele_ele1_pho1", "h_Z_ele_ele1_pho1", 40, 71., 111.);
   h_Z_ele_ele0_pho0_pho1 = new TH1D("h_Z_ele_ele0_pho0_pho1", "h_Z_ele_ele0_pho0_pho1", 40, 71., 111.);
   h_Z_ele_ele1_pho0_pho1 = new TH1D("h_Z_ele_ele1_pho0_pho1", "h_Z_ele_ele1_pho0_pho1", 40, 71., 111.);
   h_Z_ele_ele0_ele1_pho0_pho1 = new TH1D("h_Z_ele_ele0_ele1_pho0_pho1", "h_Z_ele_ele0_ele1_pho0_pho1", 40, 71., 111.);

   h_Z_muo_pho0_pho1_pt = new TH1D("h_Z_muo_pho0_pho1_pt", "h_Z_muo_pho0_pho1_pt", 30, 0., 300.);
   h_Z_muo_muo0_pho0 = new TH1D("h_Z_muo_muo0_pho0", "h_Z_muo_muo0_pho0", 40, 71., 111.);
   h_Z_muo_muo0_pho1 = new TH1D("h_Z_muo_muo0_pho1", "h_Z_muo_muo0_pho1", 40, 71., 111.);
   h_Z_muo_muo1_pho0 = new TH1D("h_Z_muo_muo1_pho0", "h_Z_muo_muo1_pho0", 40, 71., 111.);
   h_Z_muo_muo1_pho1 = new TH1D("h_Z_muo_muo1_pho1", "h_Z_muo_muo1_pho1", 40, 71., 111.);
   h_Z_muo_muo0_pho0_pho1 = new TH1D("h_Z_muo_muo0_pho0_pho1", "h_Z_muo_muo0_pho0_pho1", 40, 71., 111.);
   h_Z_muo_muo1_pho0_pho1 = new TH1D("h_Z_muo_muo1_pho0_pho1", "h_Z_muo_muo1_pho0_pho1", 40, 71., 111.);
   h_Z_muo_muo0_muo1_pho0_pho1 = new TH1D("h_Z_muo_muo0_muo1_pho0_pho1", "h_Z_muo_muo0_muo1_pho0_pho1", 40, 71., 111.);

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   h_W_ele_gen = new TH1D("h_W_ele_gen", "h_W_ele_gen", 100, 0., 200.);
   h_W_muo_gen = new TH1D("h_W_muo_gen", "h_W_muo_gen", 100, 0., 200.);

   h_Z_ele_gen = new TH1D("h_Z_ele_gen", "h_Z_ele_gen", 80, 71., 111.);
   h_Z_muo_gen = new TH1D("h_Z_muo_gen", "h_Z_muo_gen", 80, 71., 111.);

   h_W_ele_nphotons_gen = new TH1D("h_W_ele_nphotons_gen", "h_W_ele_nphotons_gen", 6, -0.5, 5.5);
   h_W_muo_nphotons_gen = new TH1D("h_W_muo_nphotons_gen", "h_W_muo_nphotons_gen", 6, -0.5, 5.5);

   h_Z_ele_nphotons_gen = new TH1D("h_Z_ele_nphotons_gen", "h_Z_ele_nphotons_gen", 6, -0.5, 5.5);
   h_Z_muo_nphotons_gen = new TH1D("h_Z_muo_nphotons_gen", "h_Z_muo_nphotons_gen", 6, -0.5, 5.5);

   h_W_ele_nphotons_rec_gen = new TH2D("h_W_ele_nphotons_rec_gen", "h_W_ele_nphotons_rec_gen", 6, -0.5, 5.5, 6, -0.5, 5.5);
   h_W_muo_nphotons_rec_gen = new TH2D("h_W_muo_nphotons_rec_gen", "h_W_muo_nphotons_rec_gen", 6, -0.5, 5.5, 6, -0.5, 5.5);

   h_Z_ele_nphotons_rec_gen = new TH2D("h_Z_ele_nphotons_rec_gen", "h_Z_ele_nphotons_rec_gen", 6, -0.5, 5.5, 6, -0.5, 5.5);
   h_Z_muo_nphotons_rec_gen = new TH2D("h_Z_muo_nphotons_rec_gen", "h_Z_muo_nphotons_rec_gen", 6, -0.5, 5.5, 6, -0.5, 5.5);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   TObject* obj = 0;
   TIter next(gDirectory->GetList());

   while ((obj = next())) {
     if (!TString(obj->ClassName()).Contains("TH")) continue;
     if (!TString(obj->GetName()).Contains("h_")) continue;
     if (TString(obj->GetName()).Contains("_gen")) continue;
     if (TString(obj->GetName()).Contains("_qcd")) continue;
     obj->Clone((TString(obj->GetName()) + "_qcd").Data());
   }
   next.Reset();

   // add all booked histograms to the selector output list
   while ((obj = next())) {
     if (!TString(obj->ClassName()).Contains("TH")) continue;
     if (!TString(obj->GetName()).Contains("h_")) continue;
     GetOutputList()->Add(obj);
   }

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

   float weight_gen = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   weight_gen = *Generator_weight;
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   h_nevt->Fill(1.5, weight_gen);

   float weight_pu_ele = 1.;
   float weight_pu_muo = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   weight_pu_ele = getWeight(pu_ele_weights, *Pileup_nTrueInt, 0);
   weight_pu_muo = getWeight(pu_muo_weights, *Pileup_nTrueInt, 0);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (isWJetsToLNu || isWG || isWGG || isWTauNu || isDYJetsToLL || isZG || isZGG || isZTauTau) {

     bool W_tau_sel_gen = false;
     bool Z_tau_sel_gen = false;

     for (uint i = 0; i < *nGenPart; i++) {
       if (fabs(GenPart_pdgId[i]) != 15) continue;
       if (GenPart_genPartIdxMother[i] == -1) continue;
       if (isWJetsToLNu || isWG || isWGG) {
         if (fabs(GenPart_pdgId[GenPart_genPartIdxMother[i]]) == 24) return kTRUE;
       }
       if (isDYJetsToLL || isZG || isZGG) {
         if (fabs(GenPart_pdgId[GenPart_genPartIdxMother[i]]) == 23) return kTRUE;
       }
       if (isWTauNu) {
         if (fabs(GenPart_pdgId[GenPart_genPartIdxMother[i]]) == 24) W_tau_sel_gen = true;
       }
       if (isZTauTau) {
         if (fabs(GenPart_pdgId[GenPart_genPartIdxMother[i]]) == 23) Z_tau_sel_gen = true;
       }
     }

     if (isWTauNu) {
       if (W_tau_sel_gen == false) return kTRUE;
     }
     if (isZTauTau) {
       if (Z_tau_sel_gen == false) return kTRUE;
     }

   }

   int iele0_gen = -1;
   int iele1_gen = -1;

   TLorentzVector ele0_gen;
   TLorentzVector ele1_gen;

   int imuo0_gen = -1;
   int imuo1_gen = -1;

   TLorentzVector muo0_gen;
   TLorentzVector muo1_gen;

   bool W_ele_sel_gen = false;
   bool W_muo_sel_gen = false;

   bool Z_ele_sel_gen = false;
   bool Z_muo_sel_gen = false;

   int n_photons_gen = 0;
   int ipho0_gen = -1;
   int ipho1_gen = -1;

   TLorentzVector pho0_gen;
   TLorentzVector pho1_gen;

   if (isWJetsToLNu || isWG || isWGG || isDYJetsToLL || isZG || isZGG) {

     for (uint i = 0; i < *nGenDressedLepton; i++) {
       if (fabs(GenDressedLepton_pdgId[i]) != 11) continue;
       if (GenDressedLepton_pt[i] < 25) continue;
       if (fabs(GenDressedLepton_eta[i]) > 2.400) continue;

       if (iele0_gen != -1) {
         if (GenDressedLepton_pdgId[i] == GenDressedLepton_pdgId[iele0_gen]) {
           if (GenDressedLepton_pt[i] > GenDressedLepton_pt[iele0_gen]) {
             iele0_gen = i;
           }
         } else {
           if (iele1_gen == -1) {
             iele1_gen = i;
           } else {
             if (GenDressedLepton_pt[i] > GenDressedLepton_pt[iele1_gen]) {
               iele1_gen = i;
             }
           }
         }
       }
       if (iele0_gen == -1) iele0_gen = i;
     }

     if (iele0_gen != -1) {
       ele0_gen.SetPtEtaPhiM(GenDressedLepton_pt[iele0_gen], GenDressedLepton_eta[iele0_gen], GenDressedLepton_phi[iele0_gen], GenDressedLepton_mass[iele0_gen]);
     }
     if (iele1_gen != -1) {
       ele1_gen.SetPtEtaPhiM(GenDressedLepton_pt[iele1_gen], GenDressedLepton_eta[iele1_gen], GenDressedLepton_phi[iele1_gen], GenDressedLepton_mass[iele1_gen]);
     }

     for (uint i = 0; i < *nGenDressedLepton; i++) {
       if (fabs(GenDressedLepton_pdgId[i]) != 13) continue;
       if (GenDressedLepton_pt[i] < 25) continue;
       if (fabs(GenDressedLepton_eta[i]) > 2.400) continue;

       if (imuo0_gen != -1) {
         if (GenDressedLepton_pdgId[i] == GenDressedLepton_pdgId[imuo0_gen]) {
           if (GenDressedLepton_pt[i] > GenDressedLepton_pt[imuo0_gen]) {
             imuo0_gen = i;
           }
         } else {
           if (imuo1_gen == -1) {
             imuo1_gen = i;
           } else {
             if (GenDressedLepton_pt[i] > GenDressedLepton_pt[imuo1_gen]) {
               imuo1_gen = i;
             }
           }
         }
       }
       if (imuo0_gen == -1) imuo0_gen = i;
     }

     if (imuo0_gen != -1) {
       muo0_gen.SetPtEtaPhiM(GenDressedLepton_pt[imuo0_gen], GenDressedLepton_eta[imuo0_gen], GenDressedLepton_phi[imuo0_gen], GenDressedLepton_mass[imuo0_gen]);
     }
     if (imuo1_gen != -1) {
       muo1_gen.SetPtEtaPhiM(GenDressedLepton_pt[imuo1_gen], GenDressedLepton_eta[imuo1_gen], GenDressedLepton_phi[imuo1_gen], GenDressedLepton_mass[imuo1_gen]);
     }

     float W_ele0_gen_mt = 0.;

     if (iele0_gen != -1 && iele1_gen == -1 && imuo0_gen == -1) {
       W_ele0_gen_mt = TMath::Sqrt(2. * ele0_gen.Pt() * (*MET_fiducialGenPt) * (1. - TMath::Cos(ele0_gen.Phi() - (*MET_fiducialGenPhi))));
       if (*MET_fiducialGenPt > 0 && W_ele0_gen_mt > 40 && ele0_gen.Pt() > 40) {
         W_ele_sel_gen = true;
       }
     }

     float W_muo0_gen_mt = 0.;

     if (imuo0_gen != -1 && imuo1_gen == -1 && iele0_gen == -1) {
       W_muo0_gen_mt = TMath::Sqrt(2. * muo0_gen.Pt() * (*MET_fiducialGenPt) * (1. - TMath::Cos(muo0_gen.Phi() - (*MET_fiducialGenPhi))));
       if (*MET_fiducialGenPt > 0 && W_muo0_gen_mt > 40 && muo0_gen.Pt() > 30) {
         W_muo_sel_gen = true;
       }
     }

     float Z_ele0_ele1_gen_m = 0.;

     if (iele0_gen != -1 && iele1_gen != -1) {
       Z_ele0_ele1_gen_m = (ele0_gen + ele1_gen).M();
       if (Z_ele0_ele1_gen_m >= 71. && Z_ele0_ele1_gen_m <= 111. && ele0_gen.Pt() > 28 && ele1_gen.Pt() > 28) {
         Z_ele_sel_gen = true;
       }
     }

     float Z_muo0_muo1_gen_m = 0.;

     if (imuo0_gen != -1 && imuo1_gen != -1) {
       Z_muo0_muo1_gen_m = (muo0_gen + muo1_gen).M();
       if (Z_muo0_muo1_gen_m >= 71. && Z_muo0_muo1_gen_m <= 111. && muo0_gen.Pt() > 28 && muo1_gen.Pt() > 28) {
         Z_muo_sel_gen = true;
       }
     }

     for (uint i = 0; i < *nGenPart; i++) {
       if (GenPart_status[i] != 1) continue;
       if (fabs(GenPart_pdgId[i]) != 22) continue;
       if ((GenPart_statusFlags[i] & 1) != 1) continue;
       if (GenPart_pt[i] < 15) continue;
       if (fabs(GenPart_eta[i]) > 2.400) continue;

       bool skip = false;

       TLorentzVector tmp_pho_gen;
       tmp_pho_gen.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);

       for (uint j = 0; j < *nGenDressedLepton; j++) {
         if (skip) continue;
         if (fabs(GenDressedLepton_pdgId[j]) != 11 && fabs(GenDressedLepton_pdgId[j]) != 13) continue;
         if (GenDressedLepton_pt[j] < 10) continue;
         if (fabs(GenDressedLepton_eta[j]) > 2.400) continue;

         TLorentzVector tmp_lept_gen;
         tmp_lept_gen.SetPtEtaPhiM(GenDressedLepton_pt[j], GenDressedLepton_eta[j], GenDressedLepton_phi[j], GenDressedLepton_mass[j]);
         if (tmp_lept_gen.DeltaR(tmp_pho_gen) < 0.4) skip = true;
       }

       if (skip) continue;

       for (uint j = 0; j < *nGenPart; j++) {
         if (skip) continue;
         if (fabs(GenPart_pdgId[j]) >= 6 && fabs(GenPart_pdgId[j]) != 21) continue;
         if (GenPart_pt[j] < 15) continue;
         if (fabs(GenPart_eta[j]) > 2.400) continue;

         TLorentzVector tmp_part_gen;
         tmp_part_gen.SetPtEtaPhiM(GenPart_pt[j], GenPart_eta[j], GenPart_phi[j], GenPart_mass[j]);
         if (tmp_part_gen.DeltaR(tmp_pho_gen) < 0.1) skip = true;
       }

       if (skip) continue;

       if (ipho0_gen != -1) {
         TLorentzVector tmp_pho0_gen;
         tmp_pho0_gen.SetPtEtaPhiM(GenPart_pt[ipho0_gen], GenPart_eta[ipho0_gen], GenPart_phi[ipho0_gen], GenPart_mass[ipho0_gen]);
         if (tmp_pho0_gen.DeltaR(tmp_pho_gen) < 0.4) continue;
       }

       if (ipho1_gen != -1) {
         TLorentzVector tmp_pho1_gen;
         tmp_pho1_gen.SetPtEtaPhiM(GenPart_pt[ipho1_gen], GenPart_eta[ipho1_gen], GenPart_phi[ipho1_gen], GenPart_mass[ipho1_gen]);
         if (tmp_pho1_gen.DeltaR(tmp_pho_gen) < 0.4) continue;
       }

       if (ipho0_gen != -1) {
         if (GenPart_pt[i] > GenPart_pt[ipho0_gen]) {
           ipho1_gen = ipho0_gen;
           ipho0_gen = i;
         } else {
           if (ipho1_gen == -1) {
             ipho1_gen = i;
           } else {
             if (GenPart_pt[i] > GenPart_pt[ipho1_gen]) {
               ipho1_gen = i;
             }
           }
         }
       }
       if (ipho0_gen == -1) ipho0_gen = i;

       n_photons_gen++;
     }

     if (ipho0_gen != -1 && GenPart_pt[ipho0_gen] < 20) {
       ipho0_gen = -1;
       ipho1_gen = -1;
       n_photons_gen = 0;
     }

     if (ipho0_gen != -1) {
       pho0_gen.SetPtEtaPhiM(GenPart_pt[ipho0_gen], GenPart_eta[ipho0_gen], GenPart_phi[ipho0_gen], GenPart_mass[ipho0_gen]);
     }
     if (ipho1_gen != -1) {
       pho1_gen.SetPtEtaPhiM(GenPart_pt[ipho1_gen], GenPart_eta[ipho1_gen], GenPart_phi[ipho1_gen], GenPart_mass[ipho1_gen]);
     }

     if (isWJetsToLNu) {
       if (n_photons_gen != 0) return kTRUE;
     }
     if (isWG) {
       if (n_photons_gen != 1) return kTRUE;
     }
     if (isWGG) {
       if (n_photons_gen == 0 || n_photons_gen == 1) return kTRUE;
     }

     if (isDYJetsToLL) {
       if (n_photons_gen != 0) return kTRUE;
     }
     if (isZG) {
       if (n_photons_gen != 1) return kTRUE;
     }
     if (isZGG) {
       if (n_photons_gen == 0 || n_photons_gen == 1) return kTRUE;
     }

     if (W_ele_sel_gen) {
       h_W_ele_gen->Fill(W_ele0_gen_mt, weight_gen * weight_pu_ele);
       h_W_ele_nphotons_gen->Fill(n_photons_gen, weight_gen * weight_pu_ele);
     }

     if (W_muo_sel_gen) {
       h_W_muo_gen->Fill(W_muo0_gen_mt, weight_gen * weight_pu_muo);
       h_W_muo_nphotons_gen->Fill(n_photons_gen, weight_gen * weight_pu_muo);
     }

     if (Z_ele_sel_gen) {
       h_Z_ele_gen->Fill(Z_ele0_ele1_gen_m, weight_gen * weight_pu_ele);
       h_Z_ele_nphotons_gen->Fill(n_photons_gen, weight_gen * weight_pu_ele);
     }

     if (Z_muo_sel_gen) {
       h_Z_muo_gen->Fill(Z_muo0_muo1_gen_m, weight_gen * weight_pu_muo);
       h_Z_muo_nphotons_gen->Fill(n_photons_gen, weight_gen * weight_pu_muo);
     }

   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   h_nevt->Fill(2.5, weight_gen);

   if (*Flag_goodVertices == 0) return kTRUE;
   if (*Flag_METFilters == 0) return kTRUE;

   h_nevt->Fill(3.5, weight_gen);

// electrons

   int iele0 = -1;
   int iele1 = -1;

   for (uint i = 0; i < *nElectron; i++) {
     float eCorr_ele = 1.;
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
// electron energy corrections not needed
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
// electron energy corrections not needed
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
     Electron_pt[i] = Electron_pt[i] * eCorr_ele;
     if (Electron_pt[i] < 25) continue;
     if (fabs(Electron_eta[i]) > 1.442 && fabs(Electron_eta[i]) < 1.566) continue;
     if (fabs(Electron_eta[i]) > 2.400) continue;

     if (fabs(Electron_eta[i]) < 1.442) {
       if (fabs(Electron_dxy[i]) > 0.05) continue;
       if (fabs(Electron_dz[i]) > 0.10) continue;
     }
     if (fabs(Electron_eta[i]) > 1.566 && fabs(Electron_eta[i]) < 2.400) {
       if (fabs(Electron_dxy[i]) > 0.10) continue;
       if (fabs(Electron_dz[i]) > 0.20) continue;
     }

     //if (Electron_mvaID_WP80[i] == 0) continue;
     if ((Electron_vidNestedWPBitmap[i] & 605178148) != 605178148) continue;

     //if (Electron_pfRelIso03_all[i] > 0.15) continue;
     if ((Electron_vidNestedWPBitmap[i] & 8388608) != 8388608) continue;

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

   TLorentzVector ele0;
   TLorentzVector ele1;

   if (iele0 != -1) {
     ele0.SetPtEtaPhiM(Electron_pt[iele0], Electron_eta[iele0], Electron_phi[iele0], Electron_mass[iele0]);
   }
   if (iele1 != -1) {
     ele1.SetPtEtaPhiM(Electron_pt[iele1], Electron_eta[iele1], Electron_phi[iele1], Electron_mass[iele1]);
   }

// electrons QCD

   int iele0_qcd = -1;
   int iele1_qcd = -1;

   for (uint i = 0; i < *nElectron; i++) {
     if (Electron_pt[i] < 25) continue;
     if (fabs(Electron_eta[i]) > 1.442 && fabs(Electron_eta[i]) < 1.566) continue;
     if (fabs(Electron_eta[i]) > 2.400) continue;

     if (fabs(Electron_eta[i]) < 1.442) {
       if (fabs(Electron_dxy[i]) > 0.05) continue;
       if (fabs(Electron_dz[i]) > 0.10) continue;
     }
     if (fabs(Electron_eta[i]) > 1.566 && fabs(Electron_eta[i]) < 2.400) {
       if (fabs(Electron_dxy[i]) > 0.10) continue;
       if (fabs(Electron_dz[i]) > 0.20) continue;
     }

     //if (Electron_mvaID_WP80[i] == 0) continue;
     if ((Electron_vidNestedWPBitmap[i] & 605178148) != 605178148) continue;

     //if (Electron_pfRelIso03_all[i] < 0.15) continue;
     if ((Electron_vidNestedWPBitmap[i] & 8388608) == 8388608) continue;

     if (iele0_qcd != -1) {
       if (Electron_charge[i] == Electron_charge[iele0_qcd]) {
         if (Electron_pt[i] > Electron_pt[iele0_qcd]) {
           iele0_qcd = i;
         }
       } else {
         if (iele1_qcd == -1) {
           iele1_qcd = i;
         } else {
           if (Electron_pt[i] > Electron_pt[iele1_qcd]) {
             iele1_qcd = i;
           }
         }
       }
     }
     if (iele0_qcd == -1) iele0_qcd = i;
   }

   TLorentzVector ele0_qcd;
   TLorentzVector ele1_qcd;

   if (iele0_qcd != -1) {
     ele0_qcd.SetPtEtaPhiM(Electron_pt[iele0_qcd], Electron_eta[iele0_qcd], Electron_phi[iele0_qcd], Electron_mass[iele0_qcd]);
   }
   if (iele1_qcd != -1) {
     ele1_qcd.SetPtEtaPhiM(Electron_pt[iele1_qcd], Electron_eta[iele1_qcd], Electron_phi[iele1_qcd], Electron_mass[iele1_qcd]);
   }

// muons

   int imuo0 = -1;
   int imuo1 = -1;

   for (uint i = 0; i < *nMuon; i++) {
     float eCorr_muo = 1.;
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
     eCorr_muo = roccor->kScaleDT(Muon_charge[i], Muon_pt[i], Muon_eta[i], Muon_phi[i], 0, 0);
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
     if (Muon_genPartIdx[i] >= 0 && (uint)Muon_genPartIdx[i] < *nGenPart) {
       eCorr_muo = roccor->kSpreadMC(Muon_charge[i], Muon_pt[i], Muon_eta[i], Muon_phi[i], GenPart_pt[Muon_genPartIdx[i]], 0, 0);
     } else {
       eCorr_muo = roccor->kSmearMC(Muon_charge[i], Muon_pt[i], Muon_eta[i], Muon_phi[i], Muon_nTrackerLayers[i], gRandom->Rndm(), 0, 0);
       if (TMath::IsNaN(eCorr_muo)) eCorr_muo = 1.;
     }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
     Muon_pt[i] = Muon_pt[i] * eCorr_muo;
     if (Muon_pt[i] < 25) continue;
     if (fabs(Muon_eta[i]) > 2.400) continue;

     if (Muon_tightId[i] == 0) continue;

     if (Muon_pfRelIso04_all[i] > 0.15) continue;

     if (imuo0 != -1) {
       if (Muon_charge[i] == Muon_charge[imuo0]) {
         if (Muon_pt[i] > Muon_pt[imuo0]) {
           imuo0 = i;
         }
       } else {
         if (imuo1 == -1) {
           imuo1 = i;
         } else {
           if (Muon_pt[i] > Muon_pt[imuo1]) {
             imuo1 = i;
           }
         }
       }
     }
     if (imuo0 == -1) imuo0 = i;
   }

   TLorentzVector muo0;
   TLorentzVector muo1;

   if (imuo0 != -1) {
     muo0.SetPtEtaPhiM(Muon_pt[imuo0], Muon_eta[imuo0], Muon_phi[imuo0], Muon_mass[imuo0]);
   }
   if (imuo1 != -1) {
     muo1.SetPtEtaPhiM(Muon_pt[imuo1], Muon_eta[imuo1], Muon_phi[imuo1], Muon_mass[imuo1]);
   }

// muons QCD

   int imuo0_qcd = -1;
   int imuo1_qcd = -1;

   for (uint i = 0; i < *nMuon; i++) {
     if (Muon_pt[i] < 25) continue;
     if (fabs(Muon_eta[i]) > 2.400) continue;

     if (Muon_tightId[i] == 0) continue;

     if (Muon_pfRelIso04_all[i] < 0.15) continue;

     if (imuo0_qcd != -1) {
       if (Muon_charge[i] == Muon_charge[imuo0_qcd]) {
         if (Muon_pt[i] > Muon_pt[imuo0_qcd]) {
           imuo0_qcd = i;
         }
       } else {
         if (imuo1_qcd == -1) {
           imuo1_qcd = i;
         } else {
           if (Muon_pt[i] > Muon_pt[imuo1_qcd]) {
             imuo1_qcd = i;
           }
         }
       }
     }
     if (imuo0_qcd == -1) imuo0_qcd = i;
   }

   TLorentzVector muo0_qcd;
   TLorentzVector muo1_qcd;

   if (imuo0_qcd != -1) {
     muo0_qcd.SetPtEtaPhiM(Muon_pt[imuo0_qcd], Muon_eta[imuo0_qcd], Muon_phi[imuo0_qcd], Muon_mass[imuo0_qcd]);
   }
   if (imuo1_qcd != -1) {
     muo1_qcd.SetPtEtaPhiM(Muon_pt[imuo1_qcd], Muon_eta[imuo1_qcd], Muon_phi[imuo1_qcd], Muon_mass[imuo1_qcd]);
   }

   if (iele0 == -1 && iele0_qcd == -1 && imuo0 == -1 && imuo0_qcd == -1) {
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
     if (W_ele_sel_gen) {
       h_W_ele_nphotons_rec_gen->Fill(-1, n_photons_gen, weight_gen * weight_pu_ele);
     }
     if (W_muo_sel_gen) {
       h_W_muo_nphotons_rec_gen->Fill(-1, n_photons_gen, weight_gen * weight_pu_muo);
     }
     if (Z_ele_sel_gen) {
       h_Z_ele_nphotons_rec_gen->Fill(-1, n_photons_gen, weight_gen * weight_pu_ele);
     }
     if (Z_muo_sel_gen) {
       h_Z_muo_nphotons_rec_gen->Fill(-1, n_photons_gen, weight_gen * weight_pu_muo);
     }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
     return kTRUE;
   }

// photons

   int n_photons = 0;
   int ipho0 = -1;
   int ipho1 = -1;

   for (uint i = 0; i < *nPhoton; i++) {
     if (Photon_pt[i] < 15) continue;
     if (fabs(Photon_eta[i]) > 1.442 && fabs(Photon_eta[i]) < 1.566) continue;
     if (fabs(Photon_eta[i]) > 2.400) continue;

#if defined(AODv4)
     if (fabs(Photon_eta[i]) < 1.442) {
       if (Photon_mvaID[i] < -0.02) continue;
     }
     if (fabs(Photon_eta[i]) > 1.566 && fabs(Photon_eta[i]) < 2.400) {
       if (Photon_mvaID[i] < -0.26) continue;
     }
#else
     if (fabs(Photon_eta[i]) < 1.442) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
       if (Photon_mvaID[i] < 0.20) continue;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
       if (Photon_mvaID[i] < 0.27) continue;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     }
     if (fabs(Photon_eta[i]) > 1.566 && fabs(Photon_eta[i]) < 2.400) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
       if (Photon_mvaID[i] < 0.20) continue;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
       if (Photon_mvaID[i] < 0.14) continue;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     }
#endif // defined(AODv4)

     //if (Photon_electronVeto[i] == 0) continue;
     if (Photon_pixelSeed[i] != 0) continue;

     if (Photon_pfRelIso03_all[i] > 0.15) continue;

     bool skip = false;

     TLorentzVector tmp_pho;
     tmp_pho.SetPtEtaPhiM(Photon_pt[i], Photon_eta[i], Photon_phi[i], Photon_mass[i]);

     if (iele0 != -1 && ele0.DeltaR(tmp_pho) < 0.4) continue;
     if (iele1 != -1 && ele1.DeltaR(tmp_pho) < 0.4) continue;

     if (imuo0 != -1 && muo0.DeltaR(tmp_pho) < 0.4) continue;
     if (imuo1 != -1 && muo1.DeltaR(tmp_pho) < 0.4) continue;

     if (iele0 != -1 && fabs((ele0+tmp_pho).M()-91.2) < 5) continue;
     if (iele1 != -1 && fabs((ele1+tmp_pho).M()-91.2) < 5) continue;
     if (iele0 != -1 && iele1 != -1 && fabs((ele0+ele1+tmp_pho).M()-91.2) < 5) continue;

     for (uint j = 0; j < *nElectron; j++) {
       if (skip) continue;
       if (Electron_pt[j] < 10) continue;
       if (fabs(Electron_eta[j]) > 1.442 && fabs(Electron_eta[j]) < 1.566) continue;
       if (fabs(Electron_eta[j]) > 2.400) continue;

       if (fabs(Electron_eta[j]) < 1.442) {
         if (fabs(Electron_dxy[j]) > 0.05) continue;
         if (fabs(Electron_dz[j]) > 0.10) continue;
       }
       if (fabs(Electron_eta[j]) > 1.566 && fabs(Electron_eta[j]) < 2.400) {
         if (fabs(Electron_dxy[j]) > 0.10) continue;
         if (fabs(Electron_dz[j]) > 0.20) continue;
       }

       if (Electron_mvaID_WP80[j] == 0) continue;

       if (Electron_photonIdx[j] == (int)i) continue;

       TLorentzVector tmp_ele;
       tmp_ele.SetPtEtaPhiM(Electron_pt[j], Electron_eta[j], Electron_phi[j], Electron_mass[j]);
       if (tmp_ele.DeltaR(tmp_pho) < 0.4) skip = true;
     }

     for (uint j = 0; j < *nMuon; j++) {
       if (skip) continue;
       if (Muon_pt[j] < 10) continue;
       if (fabs(Muon_eta[j]) > 2.400) continue;

       if (Muon_tightId[j] == 0) continue;

       TLorentzVector tmp_muo;
       tmp_muo.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
       if (tmp_muo.DeltaR(tmp_pho) < 0.4) skip = true;
     }

     if (skip) continue;

     if (ipho0 != -1) {
       TLorentzVector tmp_pho0;
       tmp_pho0.SetPtEtaPhiM(Photon_pt[ipho0], Photon_eta[ipho0], Photon_phi[ipho0], Photon_mass[ipho0]);
       if (tmp_pho0.DeltaR(tmp_pho) < 0.4) continue;
       if (iele0 != -1 && fabs((ele0+tmp_pho0+tmp_pho).M()-91.2) < 5) continue;
       if (iele1 != -1 && fabs((ele1+tmp_pho0+tmp_pho).M()-91.2) < 5) continue;
       if (iele0 != -1 && iele1 != -1 && fabs((ele0+ele1+tmp_pho).M()-91.2) < 5) continue;
       if (iele0 != -1 && iele1 != -1 && fabs((ele0+ele1+tmp_pho0+tmp_pho).M()-91.2) < 5) continue;
     }

     if (ipho1 != -1) {
       TLorentzVector tmp_pho1;
       tmp_pho1.SetPtEtaPhiM(Photon_pt[ipho1], Photon_eta[ipho1], Photon_phi[ipho1], Photon_mass[ipho1]);
       if (tmp_pho1.DeltaR(tmp_pho) < 0.4) continue;
       if (iele0 != -1 && fabs((ele0+tmp_pho1+tmp_pho).M()-91.2) < 5) continue;
       if (iele1 != -1 && fabs((ele1+tmp_pho1+tmp_pho).M()-91.2) < 5) continue;
       if (iele0 != -1 && iele1 != -1 && fabs((ele0+ele1+tmp_pho).M()-91.2) < 5) continue;
       if (iele0 != -1 && iele1 != -1 && fabs((ele0+ele1+tmp_pho1+tmp_pho).M()-91.2) < 5) continue;
     }

     if (ipho0 != -1) {
       if (Photon_pt[i] > Photon_pt[ipho0]) {
         ipho1 = ipho0;
         ipho0 = i;
       } else {
         if (ipho1 == -1) {
           ipho1 = i;
         } else {
           if (Photon_pt[i] > Photon_pt[ipho1]) {
             ipho1 = i;
           }
         }
       }
     }
     if (ipho0 == -1) ipho0 = i;

     n_photons++;
   }

   if (ipho0 != -1 && Photon_pt[ipho0] < 20) {
     ipho0 = -1;
     ipho1 = -1;
     n_photons = 0;
   }

   TLorentzVector pho0;
   TLorentzVector pho1;

   if (ipho0 != -1) {
     pho0.SetPtEtaPhiM(Photon_pt[ipho0], Photon_eta[ipho0], Photon_phi[ipho0], Photon_mass[ipho0]);
   }
   if (ipho1 != -1) {
     pho1.SetPtEtaPhiM(Photon_pt[ipho1], Photon_eta[ipho1], Photon_phi[ipho1], Photon_mass[ipho1]);
   }

// photons QCD

   int n_photons_qcd = 0;
   int ipho0_qcd = -1;
   int ipho1_qcd = -1;

   for (uint i = 0; i < *nPhoton; i++) {
     if (Photon_pt[i] < 15) continue;
     if (fabs(Photon_eta[i]) > 1.442 && fabs(Photon_eta[i]) < 1.566) continue;
     if (fabs(Photon_eta[i]) > 2.400) continue;

#if defined(AODv4)
     if (fabs(Photon_eta[i]) < 1.442) {
       if (Photon_mvaID[i] < -0.02) continue;
     }
     if (fabs(Photon_eta[i]) > 1.566 && fabs(Photon_eta[i]) < 2.400) {
       if (Photon_mvaID[i] < -0.26) continue;
     }
#else
     if (fabs(Photon_eta[i]) < 1.442) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
       if (Photon_mvaID[i] < 0.20) continue;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
       if (Photon_mvaID[i] < 0.27) continue;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     }
     if (fabs(Photon_eta[i]) > 1.566 && fabs(Photon_eta[i]) < 2.400) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
       if (Photon_mvaID[i] < 0.20) continue;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
       if (Photon_mvaID[i] < 0.14) continue;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     }
#endif // defined(AODv4)

     //if (Photon_electronVeto[i] == 0) continue;
     if (Photon_pixelSeed[i] != 0) continue;

     if (Photon_pfRelIso03_all[i] > 0.15) continue;

     bool skip = false;

     TLorentzVector tmp_pho_qcd;
     tmp_pho_qcd.SetPtEtaPhiM(Photon_pt[i], Photon_eta[i], Photon_phi[i], Photon_mass[i]);

     if (iele0_qcd != -1 && ele0_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
     if (iele1_qcd != -1 && ele1_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;

     if (imuo0_qcd != -1 && muo0_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
     if (imuo1_qcd != -1 && muo1_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;

     if (iele0_qcd != -1 && fabs((ele0_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;
     if (iele1_qcd != -1 && fabs((ele1_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;
     if (iele0_qcd != -1 && iele1_qcd != -1 && fabs((ele0_qcd+ele1_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;

     for (uint j = 0; j < *nElectron; j++) {
       if (skip) continue;
       if (Electron_pt[j] < 10) continue;
       if (fabs(Electron_eta[j]) > 1.442 && fabs(Electron_eta[j]) < 1.566) continue;
       if (fabs(Electron_eta[j]) > 2.400) continue;

       if (fabs(Electron_eta[j]) < 1.442) {
         if (fabs(Electron_dxy[j]) > 0.05) continue;
         if (fabs(Electron_dz[j]) > 0.10) continue;
       }
       if (fabs(Electron_eta[j]) > 1.566 && fabs(Electron_eta[j]) < 2.400) {
         if (fabs(Electron_dxy[j]) > 0.10) continue;
         if (fabs(Electron_dz[j]) > 0.20) continue;
       }

       if (Electron_mvaID_WP80[j] == 0) continue;

       if (Electron_photonIdx[j] == (int)i) continue;

       TLorentzVector tmp_ele_qcd;
       tmp_ele_qcd.SetPtEtaPhiM(Electron_pt[j], Electron_eta[j], Electron_phi[j], Electron_mass[j]);
       if (tmp_ele_qcd.DeltaR(tmp_pho_qcd) < 0.4) skip = true;
     }

     for (uint j = 0; j < *nMuon; j++) {
       if (skip) continue;
       if (Muon_pt[j] < 10) continue;
       if (fabs(Muon_eta[j]) > 2.400) continue;

       if (Muon_tightId[j] == 0) continue;

       TLorentzVector tmp_muo_qcd;
       tmp_muo_qcd.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
       if (tmp_muo_qcd.DeltaR(tmp_pho_qcd) < 0.4) skip = true;
     }

     if (skip) continue;

     if (ipho0_qcd != -1) {
       TLorentzVector tmp_pho0_qcd;
       tmp_pho0_qcd.SetPtEtaPhiM(Photon_pt[ipho0_qcd], Photon_eta[ipho0_qcd], Photon_phi[ipho0_qcd], Photon_mass[ipho0_qcd]);
       if (tmp_pho0_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
       if (iele0_qcd != -1 && fabs((ele0_qcd+tmp_pho0_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;
       if (iele1_qcd != -1 && fabs((ele1_qcd+tmp_pho0_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;
       if (iele0_qcd != -1 && iele1_qcd != -1 && fabs((ele0_qcd+ele1_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;
       if (iele0_qcd != -1 && iele1_qcd != -1 && fabs((ele0_qcd+ele1_qcd+tmp_pho0_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;
     }

     if (ipho1_qcd != -1) {
       TLorentzVector tmp_pho1_qcd;
       tmp_pho1_qcd.SetPtEtaPhiM(Photon_pt[ipho1_qcd], Photon_eta[ipho1_qcd], Photon_phi[ipho1_qcd], Photon_mass[ipho1_qcd]);
       if (tmp_pho1_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
       if (iele0_qcd != -1 && fabs((ele0_qcd+tmp_pho1_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;
       if (iele1_qcd != -1 && fabs((ele1_qcd+tmp_pho1_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;
       if (iele0_qcd != -1 && iele1_qcd != -1 && fabs((ele0_qcd+ele1_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;
       if (iele0_qcd != -1 && iele1_qcd != -1 && fabs((ele0_qcd+ele1_qcd+tmp_pho1_qcd+tmp_pho_qcd).M()-91.2) < 5) continue;
     }

     if (ipho0_qcd != -1) {
       if (Photon_pt[i] > Photon_pt[ipho0_qcd]) {
         ipho1_qcd = ipho0_qcd;
         ipho0_qcd = i;
       } else {
         if (ipho1_qcd == -1) {
           ipho1_qcd = i;
         } else {
           if (Photon_pt[i] > Photon_pt[ipho1_qcd]) {
             ipho1_qcd = i;
           }
         }
       }
     }
     if (ipho0_qcd == -1) ipho0_qcd = i;

     n_photons_qcd++;
   }

   if (ipho0_qcd != -1 && Photon_pt[ipho0_qcd] < 20) {
     ipho0_qcd = -1;
     ipho1_qcd = -1;
     n_photons_qcd = 0;
   }

   TLorentzVector pho0_qcd;
   TLorentzVector pho1_qcd;

   if (ipho0_qcd != -1) {
     pho0_qcd.SetPtEtaPhiM(Photon_pt[ipho0_qcd], Photon_eta[ipho0_qcd], Photon_phi[ipho0_qcd], Photon_mass[ipho0_qcd]);
   }
   if (ipho1_qcd != -1) {
     pho1_qcd.SetPtEtaPhiM(Photon_pt[ipho1_qcd], Photon_eta[ipho1_qcd], Photon_phi[ipho1_qcd], Photon_mass[ipho1_qcd]);
   }

// jets & MET

   int n_jets = 0;
   int ijet0 = -1;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   float met_px = *MET_pt * TMath::Cos(*MET_phi);
   float met_py = *MET_pt * TMath::Sin(*MET_phi);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   for (uint i = 0; i < *nJet; i++) {

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
     JME::JetParameters jer_parameters;
     jer_parameters.setJetPt(Jet_pt[i]);
     jer_parameters.setJetEta(Jet_eta[i]);
     jer_parameters.setRho(*fixedGridRhoFastjetAll);

     bool jet_match = false;
     if (Jet_genJetIdx[i] >= 0 && Jet_genJetIdx[i] < (int)*nGenJet) {
       TLorentzVector tmp_jet;
       tmp_jet.SetPtEtaPhiM(Jet_pt[i], Jet_eta[i], Jet_phi[i], Jet_mass[i]);
       TLorentzVector tmp_jet_gen;
       tmp_jet_gen.SetPtEtaPhiM(GenJet_pt[Jet_genJetIdx[i]], GenJet_eta[Jet_genJetIdx[i]], GenJet_phi[Jet_genJetIdx[i]], GenJet_mass[Jet_genJetIdx[i]]);
       if (tmp_jet.DeltaR(tmp_jet_gen) < 0.4 && fabs(tmp_jet.Pt() - tmp_jet_gen.Pt()) < 3 * jet_resolution->getResolution(jer_parameters) * tmp_jet.Pt())  {
         jet_match = true;
       }
     }

     float jet_smear = 1.;
     if (jet_match) {
       jet_smear = 1. + (jet_resolution_sf->getScaleFactor(jer_parameters) - 1.) * (Jet_pt[i] - GenJet_pt[Jet_genJetIdx[i]]) / Jet_pt[i];
     } else {
       jet_smear = gRandom->Gaus(1., jet_resolution->getResolution(jer_parameters) * TMath::Sqrt(TMath::Max(TMath::Power(jet_resolution_sf->getScaleFactor(jer_parameters), 2) - 1., 0.)));
     }

     if (jet_smear * Jet_pt[i] < 1.e-2) jet_smear = 1.e-2;

     if (jet_smear * Jet_pt[i] > 15) {
       met_px = met_px - (jet_smear - 1.) * Jet_pt[i] * TMath::Cos(Jet_phi[i]);
       met_py = met_py - (jet_smear - 1.) * Jet_pt[i] * TMath::Sin(Jet_phi[i]);
     }

     Jet_pt[i] = jet_smear * Jet_pt[i];
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

     if (Jet_pt[i] < 30) continue;
     if (fabs(Jet_eta[i]) > 2.400) continue;

     TLorentzVector tmp_jet;
     tmp_jet.SetPtEtaPhiM(Jet_pt[i], Jet_eta[i], Jet_phi[i], Jet_mass[i]);

     if (iele0 != -1) {
       if (ele0.DeltaR(tmp_jet) < 0.4) continue;
     }
     if (iele1 != -1) {
       if (ele1.DeltaR(tmp_jet) < 0.4) continue;
     }
     if (imuo0 != -1) {
       if (muo0.DeltaR(tmp_jet) < 0.4) continue;
     }
     if (imuo1 != -1) {
       if (muo1.DeltaR(tmp_jet) < 0.4) continue;
     }
     if (ipho0 != -1) {
       if (pho0.DeltaR(tmp_jet) < 0.4) continue;
     }
     if (ipho1 != -1) {
       if (pho1.DeltaR(tmp_jet) < 0.4) continue;
     }

     if (ijet0 != -1) {
       if (Jet_pt[i] > Jet_pt[ijet0]) {
         ijet0 = i;
       }
     }
     if (ijet0 == -1) ijet0 = i;
     n_jets++;
   }

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   *MET_pt = TMath::Sqrt(TMath::Power(met_px, 2) + TMath::Power(met_py, 2));
   *MET_phi = TMath::ATan2(met_py, met_px);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   TLorentzVector jet0;

   if (ijet0 != -1) {
     jet0.SetPtEtaPhiM(Jet_pt[ijet0], Jet_eta[ijet0], Jet_phi[ijet0], Jet_mass[ijet0]);
   }

// jets QCD

   int n_jets_qcd = 0;
   int ijet0_qcd = -1;

   for (uint i = 0; i < *nJet; i++) {

     if (Jet_pt[i] < 30) continue;
     if (fabs(Jet_eta[i]) > 2.400) continue;

     TLorentzVector tmp_jet_qcd;
     tmp_jet_qcd.SetPtEtaPhiM(Jet_pt[i], Jet_eta[i], Jet_phi[i], Jet_mass[i]);

     if (iele0_qcd != -1) {
       if (ele0_qcd.DeltaR(tmp_jet_qcd) < 0.4) continue;
     }
     if (iele1_qcd != -1) {
       if (ele1_qcd.DeltaR(tmp_jet_qcd) < 0.4) continue;
     }
     if (imuo0_qcd != -1) {
       if (muo0_qcd.DeltaR(tmp_jet_qcd) < 0.4) continue;
     }
     if (imuo1_qcd != -1) {
       if (muo1_qcd.DeltaR(tmp_jet_qcd) < 0.4) continue;
     }
     if (ipho0_qcd != -1) {
       if (pho0_qcd.DeltaR(tmp_jet_qcd) < 0.4) continue;
     }
     if (ipho1_qcd != -1) {
       if (pho1_qcd.DeltaR(tmp_jet_qcd) < 0.4) continue;
     }

     if (ijet0_qcd != -1) {
       if (Jet_pt[i] > Jet_pt[ijet0_qcd]) {
         ijet0_qcd = i;
       }
     }
     if (ijet0_qcd == -1) ijet0_qcd = i;
     n_jets_qcd++;
   }

   TLorentzVector jet0_qcd;

   if (ijet0_qcd != -1) {
     jet0_qcd.SetPtEtaPhiM(Jet_pt[ijet0_qcd], Jet_eta[ijet0_qcd], Jet_phi[ijet0_qcd], Jet_mass[ijet0_qcd]);
   }

// W -> ele nu

   bool W_ele_sel = false;
   bool W_ele_sel_wide = false;

   float W_ele0_mt = 0.;

   if (iele0 != -1 && iele1 == -1 && imuo0 == -1 && iele0_qcd == -1 && imuo0_qcd == -1) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_Ele27_WPTight_Gsf) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_Ele35_WPTight_Gsf) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Ele32_WPTight_Gsf) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       W_ele0_mt = TMath::Sqrt(2. * ele0.Pt() * (*MET_pt) * (1. - TMath::Cos(ele0.Phi() - (*MET_phi))));
       if (*MET_pt > 0 && W_ele0_mt > 0 && ele0.Pt() > 40) {
         W_ele_sel_wide = true;
         if (W_ele0_mt > 40) {
           W_ele_sel = true;
         }
       }
     }
   }

   if (W_ele_sel || W_ele_sel_wide) {

     bool match0 = false;

     for (uint i = 0; i < *nTrigObj; i++) {
       if (match0) continue;
       if (TrigObj_id[i] != 11) continue;

       TLorentzVector tmp_trg;
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], ele0.M());
       if (ele0.DeltaR(tmp_trg) < 0.3) {
         if ((TrigObj_filterBits[i] & 1) == 1) match0 = true; // 1 = CaloIdL_TrackIdL_IsoVL
         if ((TrigObj_filterBits[i] & 2) == 2) match0 = true; // 2 = WPTight
       }
     }

     if (!match0) {
       W_ele_sel = false;
       W_ele_sel_wide = false;
     }

   }

// W -> ele nu QCD

   bool W_ele_sel_qcd = false;
   bool W_ele_sel_wide_qcd = false;

   float W_ele0_mt_qcd = 0.;

   if (iele0_qcd != -1 && iele1_qcd == -1 && imuo0_qcd == -1 && iele0 == -1 && imuo0 == -1) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_Ele27_WPTight_Gsf) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_Ele35_WPTight_Gsf) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Ele32_WPTight_Gsf) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       W_ele0_mt_qcd = TMath::Sqrt(2. * ele0_qcd.Pt() * (*MET_pt) * (1. - TMath::Cos(ele0_qcd.Phi() - (*MET_phi))));
       if (*MET_pt > 0 && W_ele0_mt_qcd > 0 && ele0_qcd.Pt() > 40) {
         W_ele_sel_wide_qcd = true;
         if (W_ele0_mt_qcd > 40) {
           W_ele_sel_qcd = true;
         }
       }
     }
   }

// W -> muo nu

   bool W_muo_sel = false;
   bool W_muo_sel_wide = false;

   float W_muo0_mt = 0.;

   if (imuo0 != -1 && imuo1 == -1 && iele0 == -1 && iele0_qcd == -1 && imuo0_qcd == -1) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_IsoMu24 || *HLT_IsoTkMu24) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_IsoMu24 || *HLT_IsoMu27) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_IsoMu24) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       W_muo0_mt = TMath::Sqrt(2. * muo0.Pt() * (*MET_pt) * (1. - TMath::Cos(muo0.Phi() - (*MET_phi))));
       if (*MET_pt > 0 && W_muo0_mt > 0 && muo0.Pt() > 30) {
         W_muo_sel_wide = true;
         if (W_muo0_mt > 40) {
           W_muo_sel = true;
         }
       }
     }
   }

   if (W_muo_sel || W_muo_sel_wide) {

     bool match0 = false;

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     match0 = true;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)

     for (uint i = 0; i < *nTrigObj; i++) {
       if (match0) continue;
       if (TrigObj_id[i] != 13) continue;

       TLorentzVector tmp_trg;
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], muo0.M());
       if (muo0.DeltaR(tmp_trg) < 0.3) {
         if ((TrigObj_filterBits[i] & 1) == 1) match0 = true; // 1 = TrkIsoVVL
         if ((TrigObj_filterBits[i] & 2) == 2) match0 = true; // 2 = Iso
#if defined(AODv4) || defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
         if ((TrigObj_filterBits[i] & 8) == 8) match0 = true; // 8 = 1mu
#endif // defined(AODv4) || defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       }
     }

     if (!match0) {
       W_muo_sel = false;
       W_muo_sel_wide = false;
     }

   }

// W -> muo nu QCD

   bool W_muo_sel_qcd = false;
   bool W_muo_sel_wide_qcd = false;

   float W_muo0_mt_qcd = 0.;

   if (imuo0_qcd != -1 && imuo1_qcd == -1 && iele0_qcd == -1 && iele0 == -1 && imuo0 == -1) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_IsoMu24 || *HLT_IsoTkMu24) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_IsoMu24 || *HLT_IsoMu27) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_IsoMu24) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       W_muo0_mt_qcd = TMath::Sqrt(2. * muo0_qcd.Pt() * (*MET_pt) * (1. - TMath::Cos(muo0_qcd.Phi() - (*MET_phi))));
       if (*MET_pt > 0 && W_muo0_mt_qcd > 0 && muo0_qcd.Pt() > 30) {
         W_muo_sel_wide_qcd = true;
         if (W_muo0_mt_qcd > 40) {
           W_muo_sel_qcd = true;
         }
       }
     }
   }

// Z -> ele ele

   bool Z_ele_sel = false;

   float Z_ele0_ele1_m = 0.;

   if (iele0 != -1 && iele1 != -1) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       Z_ele0_ele1_m = (ele0 + ele1).M();
       if (Z_ele0_ele1_m >= 71. && Z_ele0_ele1_m <= 111. && ele0.Pt() > 28 && ele1.Pt() > 28) {
         Z_ele_sel = true;
       }
     }
   }

   if (Z_ele_sel) {

     bool match0 = false;
     bool match1 = false;

     for (uint i = 0; i < *nTrigObj; i++) {
       if (match0 && match1) continue;
       if (TrigObj_id[i] != 11) continue;

       TLorentzVector tmp_trg;
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], ele0.M());
       if (ele0.DeltaR(tmp_trg) < 0.3) {
         if ((TrigObj_filterBits[i] & 1) == 1) match0 = true; // 1 = CaloIdL_TrackIdL_IsoVL
         if ((TrigObj_filterBits[i] & 4) == 4) match0 = true; // 4 = WPLoose
#if defined(AODv4) || defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
         if ((TrigObj_filterBits[i] & 16) == 16) match0 = true; // 16 = 2e
#endif // defined(AODv4) || defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       }
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], ele1.M());
       if (ele1.DeltaR(tmp_trg) < 0.3) {
         if ((TrigObj_filterBits[i] & 1) == 1) match1 = true; // 1 = CaloIdL_TrackIdL_IsoVL
         if ((TrigObj_filterBits[i] & 4) == 4) match1 = true; // 4 = WPLoose
#if defined(AODv4) || defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
         if ((TrigObj_filterBits[i] & 16) == 16) match1 = true; // 16 = 2e
#endif // defined(AODv4) || defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       }
     }

     if (!match0 || !match1) {
       Z_ele_sel = false;
     }

   }

// Z -> ele ele QCD

   bool Z_ele_sel_qcd = false;

   float Z_ele0_ele1_m_qcd = 0.;

   if (iele0_qcd != -1 && iele1_qcd != -1) {
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       Z_ele0_ele1_m_qcd = (ele0_qcd + ele1_qcd).M();
       if (Z_ele0_ele1_m_qcd >= 71. && Z_ele0_ele1_m_qcd <= 111. && ele0_qcd.Pt() > 28 && ele1_qcd.Pt() > 28) {
         Z_ele_sel_qcd = true;
       }
     }
   }

// Z -> muo muo

   bool Z_muo_sel = false;

   float Z_muo0_muo1_m = 0.;

   if (imuo0 != -1 && imuo1 != -1) {
#if defined(mainSelectorDT16_cxx) && !defined(mainSelectorDT16H_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL ||
         *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ) {
#endif // defined(mainSelectorDT16_cxx) && !defined(mainSelectorDT16H_cxx)
#if defined(mainSelectorDT16H_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL ||
         *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ ||
         *HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL || *HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ) {
#endif // defined(mainSelectorDT16H_cxx)
#if defined(mainSelectorMC16_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL ||
         *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ ||
         *HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL || *HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ) {
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) && !defined(mainSelectorDT17B_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) {
#endif // defined(mainSelectorDT17_cxx) && !defined(mainSelectorDT17B_cxx)
#if defined(mainSelectorDT17B_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8) {
#endif // defined(mainSelectorDT17B_cxx)
#if defined(mainSelectorMC17_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) {
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       Z_muo0_muo1_m = (muo0 + muo1).M();
       if (Z_muo0_muo1_m >= 71. && Z_muo0_muo1_m <= 111. && muo0.Pt() > 28 && muo1.Pt() > 28) {
         Z_muo_sel = true;
       }
     }
   }

   if (Z_muo_sel) {

     bool match0 = false;
     bool match1 = false;

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     match0 = true;
     match1 = true;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)

     for (uint i = 0; i < *nTrigObj; i++) {
       if (match0 && match1) continue;
       if (TrigObj_id[i] != 13) continue;

       TLorentzVector tmp_trg;
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], muo0.M());
       if (muo0.DeltaR(tmp_trg) < 0.3) {
         if ((TrigObj_filterBits[i] & 1) == 1) match0 = true; // 1 = TrkIsoVVL
         if ((TrigObj_filterBits[i] & 2) == 2) match0 = true; // 2 = Iso
#if defined(AODv4) || defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
         if ((TrigObj_filterBits[i] & 16) == 16) match0 = true; // 16 = 2mu
#endif // defined(AODv4) || defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       }
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], muo1.M());
       if (muo1.DeltaR(tmp_trg) < 0.3) {
         if ((TrigObj_filterBits[i] & 1) == 1) match1 = true; // 1 = TrkIsoVVL
         if ((TrigObj_filterBits[i] & 2) == 2) match1 = true; // 2 = Iso
#if defined(AODv4) || defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
         if ((TrigObj_filterBits[i] & 16) == 16) match1 = true; // 16 = 2mu
#endif // defined(AODv4) || defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       }
     }

     if (!match0 || !match1) {
       Z_muo_sel = false;
     }

   }

// Z -> muo muo QCD

   bool Z_muo_sel_qcd = false;

   float Z_muo0_muo1_m_qcd = 0.;

   if (imuo0_qcd != -1 && imuo1_qcd != -1) {
#if defined(mainSelectorDT16_cxx) && !defined(mainSelectorDT16H_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL ||
         *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ) {
#endif // defined(mainSelectorDT16_cxx) && !defined(mainSelectorDT16H_cxx)
#if defined(mainSelectorDT16H_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL ||
         *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ ||
         *HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL || *HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ) {
#endif // defined(mainSelectorDT16H_cxx)
#if defined(mainSelectorMC16_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL ||
         *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ || *HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ ||
         *HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL || *HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ) {
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) && !defined(mainSelectorDT17B_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) {
#endif // defined(mainSelectorDT17_cxx) && !defined(mainSelectorDT17B_cxx)
#if defined(mainSelectorDT17B_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8) {
#endif // defined(mainSelectorDT17B_cxx)
#if defined(mainSelectorMC17_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) {
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       Z_muo0_muo1_m_qcd = (muo0_qcd + muo1_qcd).M();
       if (Z_muo0_muo1_m_qcd >= 71. && Z_muo0_muo1_m_qcd <= 111. && muo0_qcd.Pt() > 28 && muo1_qcd.Pt() > 28) {
         Z_muo_sel_qcd = true;
       }
     }
   }

// electron(s) scale factors

   float weight_eff_ele0 = 1.;
   float weight_reco_ele0 = 1.;

   float weight_eff_ele1 = 1.;
   float weight_reco_ele1 = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (iele0 != -1) {
     weight_eff_ele0 = getWeight(sf_ele_eff, Electron_eta[iele0], Electron_pt[iele0]);
     weight_reco_ele0 = getWeight(sf_ele_reco, Electron_eta[iele0], Electron_pt[iele0]);
   }
   if (iele1 != -1) {
     weight_eff_ele1 = getWeight(sf_ele_eff, Electron_eta[iele1], Electron_pt[iele1]);
     weight_reco_ele1 = getWeight(sf_ele_reco, Electron_eta[iele1], Electron_pt[iele1]);
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_hlt_ele = 1.;

#if defined(mainSelectorMC17_cxx)
   weight_hlt_ele = 0.991;
#endif // defined(mainSelectorMC17_cxx)

// electron(s) scale factors QCD

   float weight_eff_ele0_qcd = 1.;
   float weight_reco_ele0_qcd = 1.;

   float weight_eff_ele1_qcd = 1.;
   float weight_reco_ele1_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (iele0_qcd != -1) {
     weight_eff_ele0_qcd = getWeight(sf_ele_eff, Electron_eta[iele0_qcd], Electron_pt[iele0_qcd]);
     weight_reco_ele0_qcd = getWeight(sf_ele_reco, Electron_eta[iele0_qcd], Electron_pt[iele0_qcd]);
   }
   if (iele1_qcd != -1) {
     weight_eff_ele1_qcd = getWeight(sf_ele_eff, Electron_eta[iele1_qcd], Electron_pt[iele1_qcd]);
     weight_reco_ele1_qcd = getWeight(sf_ele_reco, Electron_eta[iele1_qcd], Electron_pt[iele1_qcd]);
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_hlt_ele_qcd = 1.;

#if defined(mainSelectorMC17_cxx)
   weight_hlt_ele_qcd = 0.991;
#endif // defined(mainSelectorMC17_cxx)

// muon(s) scale factors

   float weight_id_muo0 = 1.;
   float weight_iso_muo0 = 1.;

   float weight_id_muo1 = 1.;
   float weight_iso_muo1 = 1.;

#if defined(mainSelectorMC16_cxx)
   if (imuo0 != -1) {
     weight_id_muo0 = getWeight(sf_muo_id, Muon_eta[imuo0], Muon_pt[imuo0]);
     weight_iso_muo0 = getWeight(sf_muo_iso, Muon_eta[imuo0], Muon_pt[imuo0]);
   }
   if (imuo1 != -1) {
     weight_id_muo1 = getWeight(sf_muo_id, Muon_eta[imuo1], Muon_pt[imuo1]);
     weight_iso_muo1 = getWeight(sf_muo_iso, Muon_eta[imuo1], Muon_pt[imuo1]);
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (imuo0 != -1) {
     weight_id_muo0 = getWeight(sf_muo_id, Muon_pt[imuo0], fabs(Muon_eta[imuo0]));
     weight_iso_muo0 = getWeight(sf_muo_iso, Muon_pt[imuo0], fabs(Muon_eta[imuo0]));
   }
   if (imuo1 != -1) {
     weight_id_muo1 = getWeight(sf_muo_id, Muon_pt[imuo1], fabs(Muon_eta[imuo1]));
     weight_iso_muo1 = getWeight(sf_muo_iso, Muon_pt[imuo1], fabs(Muon_eta[imuo1]));
   }
#endif // defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

// muon(s) scale factors QCD

   float weight_id_muo0_qcd = 1.;
   float weight_iso_muo0_qcd = 1.;

   float weight_id_muo1_qcd = 1.;
   float weight_iso_muo1_qcd = 1.;

#if defined(mainSelectorMC16_cxx)
   if (imuo0_qcd != -1) {
     weight_id_muo0_qcd = getWeight(sf_muo_id, Muon_eta[imuo0_qcd], Muon_pt[imuo0_qcd]);
     weight_iso_muo0_qcd = getWeight(sf_muo_iso, Muon_eta[imuo0_qcd], Muon_pt[imuo0_qcd]);
   }
   if (imuo1_qcd != -1) {
     weight_id_muo1_qcd = getWeight(sf_muo_id, Muon_eta[imuo1_qcd], Muon_pt[imuo1_qcd]);
     weight_iso_muo1_qcd = getWeight(sf_muo_iso, Muon_eta[imuo1_qcd], Muon_pt[imuo1_qcd]);
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (imuo0_qcd != -1) {
     weight_id_muo0_qcd = getWeight(sf_muo_id, Muon_pt[imuo0_qcd], fabs(Muon_eta[imuo0_qcd]));
     weight_iso_muo0_qcd = getWeight(sf_muo_iso, Muon_pt[imuo0_qcd], fabs(Muon_eta[imuo0_qcd]));
   }
   if (imuo1_qcd != -1) {
     weight_id_muo1_qcd = getWeight(sf_muo_id, Muon_pt[imuo1_qcd], fabs(Muon_eta[imuo1_qcd]));
     weight_iso_muo1_qcd = getWeight(sf_muo_iso, Muon_pt[imuo1_qcd], fabs(Muon_eta[imuo1_qcd]));
   }
#endif // defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

// photon(s) scale factors

   float weight_eff_pho0 = 1.;
   float weight_reco_pho0 = 1.;

   float weight_eff_pho1 = 1.;
   float weight_reco_pho1 = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0 != -1) {
     weight_eff_pho0 = getWeight(sf_pho_eff, Photon_eta[ipho0], Photon_pt[ipho0]);
   }
   if (ipho1 != -1) {
     weight_eff_pho1 = getWeight(sf_pho_eff, Photon_eta[ipho1], Photon_pt[ipho1]);
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0 = weight_eff_pho0 * weight_reco_pho0;
   float weight_pho1 = weight_eff_pho1 * weight_reco_pho1;

// photon(s) scale factors QCD

   float weight_eff_pho0_qcd = 1.;
   float weight_reco_pho0_qcd = 1.;

   float weight_eff_pho1_qcd = 1.;
   float weight_reco_pho1_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_qcd != -1) {
     weight_eff_pho0_qcd = getWeight(sf_pho_eff, Photon_eta[ipho0_qcd], Photon_pt[ipho0_qcd]);
   }
   if (ipho1_qcd != -1) {
     weight_eff_pho1_qcd = getWeight(sf_pho_eff, Photon_eta[ipho1_qcd], Photon_pt[ipho1_qcd]);
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0_qcd = weight_eff_pho0_qcd * weight_reco_pho0_qcd;
   float weight_pho1_qcd = weight_eff_pho1_qcd * weight_reco_pho1_qcd;

// W scale factors

   float weight_W_ele = weight_gen * weight_pu_ele * weight_eff_ele0 * weight_reco_ele0 * weight_hlt_ele;
   float weight_W_muo = weight_gen * weight_pu_muo * weight_id_muo0 * weight_iso_muo0;

// W scale factors QCD

   float weight_W_ele_qcd = weight_gen * weight_pu_ele * weight_eff_ele0_qcd * weight_reco_ele0_qcd * weight_hlt_ele_qcd;
   float weight_W_muo_qcd = weight_gen * weight_pu_muo * weight_id_muo0_qcd * weight_iso_muo0_qcd;

// Z scale factors

   float weight_Z_ele = weight_gen * weight_pu_ele * weight_eff_ele0 * weight_eff_ele1 * weight_reco_ele0 * weight_reco_ele1 * weight_hlt_ele;
   float weight_Z_muo = weight_gen * weight_pu_muo * weight_id_muo0 * weight_id_muo1 * weight_iso_muo0 * weight_iso_muo1;

// Z scale factors QCD

   float weight_Z_ele_qcd = weight_gen * weight_pu_ele * weight_eff_ele0_qcd * weight_eff_ele1_qcd * weight_reco_ele0_qcd * weight_reco_ele1_qcd * weight_hlt_ele_qcd;
   float weight_Z_muo_qcd = weight_gen * weight_pu_muo * weight_id_muo0_qcd * weight_id_muo1_qcd * weight_iso_muo0_qcd * weight_iso_muo1_qcd;

// W plots

   if (W_ele_sel_wide) {
     h_W_ele->Fill(W_ele0_mt, weight_W_ele);
     h_W_ele_met_pt->Fill(*MET_pt, weight_W_ele);
     h_W_ele_met_phi->Fill(*MET_phi, weight_W_ele);
   }

   if (W_ele_sel) {
     h_W_ele_npvs->Fill(*PV_npvsGood, weight_gen);
     h_W_ele_npvs_w->Fill(*PV_npvsGood, weight_W_ele);
     h_W_ele0_pt->Fill(Electron_pt[iele0], weight_W_ele);
     h_W_ele0_eta->Fill(Electron_eta[iele0], weight_W_ele);
     h_W_ele0_phi->Fill(Electron_phi[iele0], weight_W_ele);
     h_W_ele0_r9->Fill(Electron_r9[iele0], weight_W_ele);
     h_W_ele0_sieie->Fill(Electron_sieie[iele0], weight_W_ele);
     h_W_ele0_mva->Fill(Electron_mvaID[iele0], weight_W_ele);
     h_W_ele0_pf_iso_all->Fill(Electron_pfRelIso03_all[iele0], weight_W_ele);
     h_W_ele0_pf_iso_chg->Fill(Electron_pfRelIso03_chg[iele0], weight_W_ele);
   }

   if (W_ele_sel_wide_qcd) {
     QCD(h_W_ele)->Fill(W_ele0_mt_qcd, weight_W_ele_qcd);
     QCD(h_W_ele_met_pt)->Fill(*MET_pt, weight_W_ele_qcd);
     QCD(h_W_ele_met_phi)->Fill(*MET_phi, weight_W_ele_qcd);
   }

   if (W_ele_sel_qcd) {
     QCD(h_W_ele_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_W_ele_npvs_w)->Fill(*PV_npvsGood, weight_W_ele_qcd);
     QCD(h_W_ele0_pt)->Fill(Electron_pt[iele0_qcd], weight_W_ele_qcd);
     QCD(h_W_ele0_eta)->Fill(Electron_eta[iele0_qcd], weight_W_ele_qcd);
     QCD(h_W_ele0_phi)->Fill(Electron_phi[iele0_qcd], weight_W_ele_qcd);
     QCD(h_W_ele0_r9)->Fill(Electron_r9[iele0_qcd], weight_W_ele_qcd);
     QCD(h_W_ele0_sieie)->Fill(Electron_sieie[iele0_qcd], weight_W_ele_qcd);
     QCD(h_W_ele0_mva)->Fill(Electron_mvaID[iele0_qcd], weight_W_ele_qcd);
     QCD(h_W_ele0_pf_iso_all)->Fill(Electron_pfRelIso03_all[iele0_qcd], weight_W_ele_qcd);
     QCD(h_W_ele0_pf_iso_chg)->Fill(Electron_pfRelIso03_chg[iele0_qcd], weight_W_ele_qcd);
   }

   if (W_muo_sel_wide) {
     h_W_muo->Fill(W_muo0_mt, weight_W_muo);
     h_W_muo_met_pt->Fill(*MET_pt, weight_W_muo);
     h_W_muo_met_phi->Fill(*MET_phi, weight_W_muo);
   }

   if (W_muo_sel) {
     h_W_muo_npvs->Fill(*PV_npvsGood, weight_gen);
     h_W_muo_npvs_w->Fill(*PV_npvsGood, weight_W_muo);
     h_W_muo0_pt->Fill(Muon_pt[imuo0], weight_W_muo);
     h_W_muo0_eta->Fill(Muon_eta[imuo0], weight_W_muo);
     h_W_muo0_phi->Fill(Muon_phi[imuo0], weight_W_muo);
     h_W_muo0_pf_iso_all->Fill(Muon_pfRelIso03_all[imuo0], weight_W_muo);
     h_W_muo0_pf_iso_chg->Fill(Muon_pfRelIso03_chg[imuo0], weight_W_muo);
   }

   if (W_muo_sel_wide_qcd) {
     QCD(h_W_muo)->Fill(W_muo0_mt_qcd, weight_W_muo_qcd);
     QCD(h_W_muo_met_pt)->Fill(*MET_pt, weight_W_muo_qcd);
     QCD(h_W_muo_met_phi)->Fill(*MET_phi, weight_W_muo_qcd);
   }

   if (W_muo_sel_qcd) {
     QCD(h_W_muo_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_W_muo_npvs_w)->Fill(*PV_npvsGood, weight_W_muo_qcd);
     QCD(h_W_muo0_pt)->Fill(Muon_pt[imuo0_qcd], weight_W_muo_qcd);
     QCD(h_W_muo0_eta)->Fill(Muon_eta[imuo0_qcd], weight_W_muo_qcd);
     QCD(h_W_muo0_phi)->Fill(Muon_phi[imuo0_qcd], weight_W_muo_qcd);
     QCD(h_W_muo0_pf_iso_all)->Fill(Muon_pfRelIso03_all[imuo0_qcd], weight_W_muo_qcd);
     QCD(h_W_muo0_pf_iso_chg)->Fill(Muon_pfRelIso03_chg[imuo0_qcd], weight_W_muo_qcd);
   }

// Z plots

   if (Z_ele_sel) {
     h_Z_ele_npvs->Fill(*PV_npvsGood, weight_gen);
     h_Z_ele_npvs_w->Fill(*PV_npvsGood, weight_Z_ele);
     h_Z_ele->Fill(Z_ele0_ele1_m, weight_Z_ele);
     h_Z_ele0_pt->Fill(Electron_pt[iele0], weight_Z_ele);
     h_Z_ele0_eta->Fill(Electron_eta[iele0], weight_Z_ele);
     h_Z_ele0_phi->Fill(Electron_phi[iele0], weight_Z_ele);
     h_Z_ele0_r9->Fill(Electron_r9[iele0], weight_Z_ele);
     h_Z_ele0_sieie->Fill(Electron_sieie[iele0], weight_Z_ele);
     h_Z_ele0_mva->Fill(Electron_mvaID[iele0], weight_Z_ele);
     h_Z_ele1_mva->Fill(Electron_mvaID[iele1], weight_Z_ele);
     h_Z_ele0_pf_iso_all->Fill(Electron_pfRelIso03_all[iele0], weight_Z_ele);
     h_Z_ele0_pf_iso_chg->Fill(Electron_pfRelIso03_chg[iele0], weight_Z_ele);
     h_Z_ele1_pt->Fill(Electron_pt[iele1], weight_Z_ele);
     h_Z_ele1_eta->Fill(Electron_eta[iele1], weight_Z_ele);
     h_Z_ele1_phi->Fill(Electron_phi[iele1], weight_Z_ele);
     h_Z_ele1_r9->Fill(Electron_r9[iele1], weight_Z_ele);
     h_Z_ele1_sieie->Fill(Electron_sieie[iele1], weight_Z_ele);
     h_Z_ele1_pf_iso_all->Fill(Electron_pfRelIso03_all[iele1], weight_Z_ele);
     h_Z_ele1_pf_iso_chg->Fill(Electron_pfRelIso03_chg[iele1], weight_Z_ele);
     h_Z_ele_met_pt->Fill(*MET_pt, weight_Z_ele);
     h_Z_ele_met_phi->Fill(*MET_phi, weight_Z_ele);
   }

   if (Z_ele_sel_qcd) {
     QCD(h_Z_ele_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_Z_ele_npvs_w)->Fill(*PV_npvsGood, weight_Z_ele_qcd);
     QCD(h_Z_ele)->Fill(Z_ele0_ele1_m_qcd, weight_Z_ele_qcd);
     QCD(h_Z_ele0_pt)->Fill(Electron_pt[iele0_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele0_eta)->Fill(Electron_eta[iele0_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele0_phi)->Fill(Electron_phi[iele0_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele0_r9)->Fill(Electron_r9[iele0_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele0_sieie)->Fill(Electron_sieie[iele0_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele0_mva)->Fill(Electron_mvaID[iele0_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele1_mva)->Fill(Electron_mvaID[iele1_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele0_pf_iso_all)->Fill(Electron_pfRelIso03_all[iele0_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele0_pf_iso_chg)->Fill(Electron_pfRelIso03_chg[iele0_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele1_pt)->Fill(Electron_pt[iele1_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele1_eta)->Fill(Electron_eta[iele1_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele1_phi)->Fill(Electron_phi[iele1_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele1_r9)->Fill(Electron_r9[iele1_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele1_sieie)->Fill(Electron_sieie[iele1_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele1_pf_iso_all)->Fill(Electron_pfRelIso03_all[iele1_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele1_pf_iso_chg)->Fill(Electron_pfRelIso03_chg[iele1_qcd], weight_Z_ele_qcd);
     QCD(h_Z_ele_met_pt)->Fill(*MET_pt, weight_Z_ele_qcd);
     QCD(h_Z_ele_met_phi)->Fill(*MET_phi, weight_Z_ele_qcd);
   }

   if (Z_muo_sel) {
     h_Z_muo_npvs->Fill(*PV_npvsGood, weight_gen);
     h_Z_muo_npvs_w->Fill(*PV_npvsGood, weight_Z_muo);
     h_Z_muo->Fill(Z_muo0_muo1_m, weight_Z_muo);
     h_Z_muo0_pt->Fill(Muon_pt[imuo0], weight_Z_muo);
     h_Z_muo0_eta->Fill(Muon_eta[imuo0], weight_Z_muo);
     h_Z_muo0_phi->Fill(Muon_phi[imuo0], weight_Z_muo);
     h_Z_muo0_pf_iso_all->Fill(Muon_pfRelIso03_all[imuo0], weight_Z_muo);
     h_Z_muo0_pf_iso_chg->Fill(Muon_pfRelIso03_chg[imuo0], weight_Z_muo);
     h_Z_muo1_pt->Fill(Muon_pt[imuo1], weight_Z_muo);
     h_Z_muo1_eta->Fill(Muon_eta[imuo1], weight_Z_muo);
     h_Z_muo1_phi->Fill(Muon_phi[imuo1], weight_Z_muo);
     h_Z_muo1_pf_iso_all->Fill(Muon_pfRelIso03_all[imuo1], weight_Z_muo);
     h_Z_muo1_pf_iso_chg->Fill(Muon_pfRelIso03_chg[imuo1], weight_Z_muo);
     h_Z_muo_met_pt->Fill(*MET_pt, weight_Z_muo);
     h_Z_muo_met_phi->Fill(*MET_phi, weight_Z_muo);
   }

   if (Z_muo_sel_qcd) {
     QCD(h_Z_muo_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_Z_muo_npvs_w)->Fill(*PV_npvsGood, weight_Z_muo_qcd);
     QCD(h_Z_muo)->Fill(Z_muo0_muo1_m_qcd, weight_Z_muo_qcd);
     QCD(h_Z_muo0_pt)->Fill(Muon_pt[imuo0_qcd], weight_Z_muo_qcd);
     QCD(h_Z_muo0_eta)->Fill(Muon_eta[imuo0_qcd], weight_Z_muo_qcd);
     QCD(h_Z_muo0_phi)->Fill(Muon_phi[imuo0_qcd], weight_Z_muo_qcd);
     QCD(h_Z_muo0_pf_iso_all)->Fill(Muon_pfRelIso03_all[imuo0_qcd], weight_Z_muo_qcd);
     QCD(h_Z_muo0_pf_iso_chg)->Fill(Muon_pfRelIso03_chg[imuo0_qcd], weight_Z_muo_qcd);
     QCD(h_Z_muo1_pt)->Fill(Muon_pt[imuo1_qcd], weight_Z_muo_qcd);
     QCD(h_Z_muo1_eta)->Fill(Muon_eta[imuo1_qcd], weight_Z_muo_qcd);
     QCD(h_Z_muo1_phi)->Fill(Muon_phi[imuo1_qcd], weight_Z_muo_qcd);
     QCD(h_Z_muo1_pf_iso_all)->Fill(Muon_pfRelIso03_all[imuo1_qcd], weight_Z_muo_qcd);
     QCD(h_Z_muo1_pf_iso_chg)->Fill(Muon_pfRelIso03_chg[imuo1_qcd], weight_Z_muo_qcd);
     QCD(h_Z_muo_met_pt)->Fill(*MET_pt, weight_Z_muo_qcd);
     QCD(h_Z_muo_met_phi)->Fill(*MET_phi, weight_Z_muo_qcd);
   }

// W photon(s) plots

   if (W_ele_sel_wide) {
     if (ipho0 != -1) {
       h_W_ele_pho0->Fill(W_ele0_mt, weight_W_ele * weight_pho0);
     }
   }

   if (W_ele_sel) {
     h_W_ele_nphotons->Fill(n_photons, weight_W_ele);
     if (ipho0 != -1) {
       h_W_ele_pho0_pt->Fill(Photon_pt[ipho0], weight_W_ele * weight_pho0);
       h_W_ele_pho0_eta->Fill(Photon_eta[ipho0], weight_W_ele * weight_pho0);
       h_W_ele_pho0_phi->Fill(Photon_phi[ipho0], weight_W_ele * weight_pho0);
       h_W_ele_pho0_r9->Fill(Photon_r9[ipho0], weight_W_ele * weight_pho0);
       h_W_ele_pho0_sieie->Fill(Photon_sieie[ipho0], weight_W_ele * weight_pho0);
       h_W_ele_pho0_mva->Fill(Photon_mvaID[ipho0], weight_W_ele * weight_pho0);
       h_W_ele_pho0_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho0], weight_W_ele * weight_pho0);
       h_W_ele_pho0_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho0], weight_W_ele * weight_pho0);
       h_W_ele_pho0_dR->Fill(pho0.DeltaR(ele0), weight_W_ele * weight_pho0);
       h_W_ele_ele0_pho0->Fill((ele0+pho0).M(), weight_W_ele * weight_pho0);
     }
     if (ipho1 != -1) {
       h_W_ele_pho1_pt->Fill(Photon_pt[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_W_ele_pho1_eta->Fill(Photon_eta[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_W_ele_pho1_phi->Fill(Photon_phi[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_W_ele_pho1_r9->Fill(Photon_r9[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_W_ele_pho1_sieie->Fill(Photon_sieie[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_W_ele_pho1_mva->Fill(Photon_mvaID[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_W_ele_pho1_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_W_ele_pho1_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_W_ele_pho1_dR->Fill(pho1.DeltaR(ele0), weight_W_ele * weight_pho0 * weight_pho1);
       h_W_ele_pho0_pho1_pt->Fill((pho0+pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
       h_W_ele_ele0_pho1->Fill((ele0+pho1).M(), weight_W_ele * weight_pho1);
       h_W_ele_ele0_pho0_pho1->Fill((ele0+pho0+pho1).M(), weight_W_ele * weight_pho0 * weight_pho1);
     }
   }

   if (W_ele_sel_wide_qcd) {
     if (ipho0_qcd != -1) {
       QCD(h_W_ele_pho0)->Fill(W_ele0_mt_qcd, weight_W_ele_qcd * weight_pho0_qcd);
     }
   }

   if (W_ele_sel_qcd) {
     QCD(h_W_ele_nphotons)->Fill(n_photons_qcd, weight_W_ele_qcd);
     if (ipho0_qcd != -1) {
       QCD(h_W_ele_pho0_pt)->Fill(Photon_pt[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_W_ele_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_W_ele_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_W_ele_pho0_r9)->Fill(Photon_r9[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_W_ele_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_W_ele_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_W_ele_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_W_ele_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_W_ele_pho0_dR)->Fill(pho0_qcd.DeltaR(ele0_qcd), weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_W_ele_ele0_pho0)->Fill((ele0_qcd+pho0_qcd).M(), weight_W_ele_qcd * weight_pho0_qcd);
     }
     if (ipho1_qcd != -1) {
       QCD(h_W_ele_pho1_pt)->Fill(Photon_pt[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_ele_pho1_eta)->Fill(Photon_eta[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_ele_pho1_phi)->Fill(Photon_phi[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_ele_pho1_r9)->Fill(Photon_r9[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_ele_pho1_sieie)->Fill(Photon_sieie[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_ele_pho1_mva)->Fill(Photon_mvaID[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_ele_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_ele_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_ele_pho1_dR)->Fill(pho1_qcd.DeltaR(ele0_qcd), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_ele_pho0_pho1_pt)->Fill((pho0_qcd+pho1_qcd).Pt(), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_ele_ele0_pho1)->Fill((ele0_qcd+pho1_qcd).M(), weight_W_ele_qcd * weight_pho1_qcd);
       QCD(h_W_ele_ele0_pho0_pho1)->Fill((ele0_qcd+pho0_qcd+pho1_qcd).M(), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
     }
   }

   if (W_muo_sel_wide) {
     if (ipho0 != -1) {
       h_W_muo_pho0->Fill(W_muo0_mt, weight_W_muo * weight_pho0);
     }
   }

   if (W_muo_sel) {
     h_W_muo_nphotons->Fill(n_photons, weight_W_muo);
     if (ipho0 != -1) {
       h_W_muo_pho0_pt->Fill(Photon_pt[ipho0], weight_W_muo * weight_pho0);
       h_W_muo_pho0_eta->Fill(Photon_eta[ipho0], weight_W_muo * weight_pho0);
       h_W_muo_pho0_phi->Fill(Photon_phi[ipho0], weight_W_muo * weight_pho0);
       h_W_muo_pho0_r9->Fill(Photon_r9[ipho0], weight_W_muo * weight_pho0);
       h_W_muo_pho0_sieie->Fill(Photon_sieie[ipho0], weight_W_muo * weight_pho0);
       h_W_muo_pho0_mva->Fill(Photon_mvaID[ipho0], weight_W_muo * weight_pho0);
       h_W_muo_pho0_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho0], weight_W_muo * weight_pho0);
       h_W_muo_pho0_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho0], weight_W_muo * weight_pho0);
       h_W_muo_pho0_dR->Fill(pho0.DeltaR(muo0), weight_W_muo * weight_pho0);
       h_W_muo_muo0_pho0->Fill((muo0+pho0).M(), weight_W_muo * weight_pho0);
     }
     if (ipho1 != -1) {
       h_W_muo_pho1_pt->Fill(Photon_pt[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_W_muo_pho1_eta->Fill(Photon_eta[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_W_muo_pho1_phi->Fill(Photon_phi[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_W_muo_pho1_r9->Fill(Photon_r9[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_W_muo_pho1_sieie->Fill(Photon_sieie[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_W_muo_pho1_mva->Fill(Photon_mvaID[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_W_muo_pho1_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_W_muo_pho1_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_W_muo_pho1_dR->Fill(pho1.DeltaR(muo0), weight_W_muo * weight_pho0 * weight_pho1);
       h_W_muo_pho0_pho1_pt->Fill((pho0+pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
       h_W_muo_muo0_pho1->Fill((muo0+pho1).M(), weight_W_muo * weight_pho1);
       h_W_muo_muo0_pho0_pho1->Fill((muo0+pho0+pho1).M(), weight_W_muo * weight_pho0 * weight_pho1);
     }
   }

   if (W_muo_sel_wide_qcd) {
     if (ipho0_qcd != -1) {
       QCD(h_W_muo_pho0)->Fill(W_muo0_mt_qcd, weight_W_muo_qcd * weight_pho0_qcd);
     }
   }

   if (W_muo_sel_qcd) {
     QCD(h_W_muo_nphotons)->Fill(n_photons_qcd, weight_W_muo_qcd);
     if (ipho0_qcd != -1) {
       QCD(h_W_muo_pho0_pt)->Fill(Photon_pt[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_W_muo_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_W_muo_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_W_muo_pho0_r9)->Fill(Photon_r9[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_W_muo_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_W_muo_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_W_muo_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_W_muo_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_W_muo_pho0_dR)->Fill(pho0_qcd.DeltaR(muo0_qcd), weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_W_muo_muo0_pho0)->Fill((muo0_qcd+pho0_qcd).M(), weight_W_muo_qcd * weight_pho0_qcd);
     }
     if (ipho1_qcd != -1) {
       QCD(h_W_muo_pho1_pt)->Fill(Photon_pt[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_muo_pho1_eta)->Fill(Photon_eta[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_muo_pho1_phi)->Fill(Photon_phi[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_muo_pho1_r9)->Fill(Photon_r9[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_muo_pho1_sieie)->Fill(Photon_sieie[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_muo_pho1_mva)->Fill(Photon_mvaID[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_muo_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_muo_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_muo_pho1_dR)->Fill(pho1_qcd.DeltaR(muo0_qcd), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_muo_pho0_pho1_pt)->Fill((pho0_qcd+pho1_qcd).Pt(), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_W_muo_muo0_pho1)->Fill((muo0_qcd+pho1_qcd).M(), weight_W_muo_qcd * weight_pho1_qcd);
       QCD(h_W_muo_muo0_pho0_pho1)->Fill((muo0_qcd+pho0_qcd+pho1_qcd).M(), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
     }
   }

// Z photon(s) plots

   if (Z_ele_sel) {
     h_Z_ele_nphotons->Fill(n_photons, weight_Z_ele);
     if (ipho0 != -1) {
       h_Z_ele_pho0_pt->Fill(Photon_pt[ipho0], weight_Z_ele * weight_pho0);
       h_Z_ele_pho0_eta->Fill(Photon_eta[ipho0], weight_Z_ele * weight_pho0);
       h_Z_ele_pho0_phi->Fill(Photon_phi[ipho0], weight_Z_ele * weight_pho0);
       h_Z_ele_pho0_r9->Fill(Photon_r9[ipho0], weight_Z_ele * weight_pho0);
       h_Z_ele_pho0_sieie->Fill(Photon_sieie[ipho0], weight_Z_ele * weight_pho0);
       h_Z_ele_pho0_mva->Fill(Photon_mvaID[ipho0], weight_Z_ele * weight_pho0);
       h_Z_ele_pho0_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho0], weight_Z_ele * weight_pho0);
       h_Z_ele_pho0_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho0], weight_Z_ele * weight_pho0);
       h_Z_ele_pho0_dR->Fill(TMath::Min(pho0.DeltaR(ele0), pho0.DeltaR(ele1)), weight_Z_ele * weight_pho0);
       h_Z_ele_pho0->Fill(Z_ele0_ele1_m, weight_Z_ele * weight_pho0);
       h_Z_ele_ele0_pho0->Fill((ele0+pho0).M(), weight_Z_ele * weight_pho0);
       h_Z_ele_ele1_pho0->Fill((ele1+pho0).M(), weight_Z_ele * weight_pho0);
     }
     if (ipho1 != -1) {
       h_Z_ele_pho1_pt->Fill(Photon_pt[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_pho1_eta->Fill(Photon_eta[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_pho1_phi->Fill(Photon_phi[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_pho1_r9->Fill(Photon_r9[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_pho1_sieie->Fill(Photon_sieie[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_pho1_mva->Fill(Photon_mvaID[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_pho1_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_pho1_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_pho1_dR->Fill(TMath::Min(pho1.DeltaR(ele0), pho1.DeltaR(ele1)), weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_pho0_pho1_pt->Fill((pho0+pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_ele0_pho1->Fill((ele0+pho1).M(), weight_Z_ele * weight_pho1);
       h_Z_ele_ele1_pho1->Fill((ele1+pho1).M(), weight_Z_ele * weight_pho1);
       h_Z_ele_ele0_pho0_pho1->Fill((ele0+pho0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_ele1_pho0_pho1->Fill((ele1+pho0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_Z_ele_ele0_ele1_pho0_pho1->Fill((ele0+ele1+pho0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
     }
   }

   if (Z_ele_sel_qcd) {
     QCD(h_Z_ele_nphotons)->Fill(n_photons_qcd, weight_Z_ele_qcd);
     if (ipho0_qcd != -1) {
       QCD(h_Z_ele_pho0_pt)->Fill(Photon_pt[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_pho0_r9)->Fill(Photon_r9[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_pho0_dR)->Fill(TMath::Min(pho0_qcd.DeltaR(ele0_qcd), pho0_qcd.DeltaR(ele1_qcd)), weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_pho0)->Fill(Z_ele0_ele1_m_qcd, weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_ele0_pho0)->Fill((ele0_qcd+pho0_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_Z_ele_ele1_pho0)->Fill((ele1_qcd+pho0_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd);
     }
     if (ipho1_qcd != -1) {
       QCD(h_Z_ele_pho1_pt)->Fill(Photon_pt[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_pho1_eta)->Fill(Photon_eta[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_pho1_phi)->Fill(Photon_phi[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_pho1_r9)->Fill(Photon_r9[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_pho1_sieie)->Fill(Photon_sieie[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_pho1_mva)->Fill(Photon_mvaID[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_pho1_dR)->Fill(TMath::Min(pho1_qcd.DeltaR(ele0_qcd), pho1_qcd.DeltaR(ele1_qcd)), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_pho0_pho1_pt)->Fill((pho0_qcd+pho1_qcd).Pt(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_ele0_pho1)->Fill((ele0_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_ele1_pho1)->Fill((ele1_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_ele0_pho0_pho1)->Fill((ele0_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_ele1_pho0_pho1)->Fill((ele1_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_ele_ele0_ele1_pho0_pho1)->Fill((ele0_qcd+ele1_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
     }
   }

   if (Z_muo_sel) {
     h_Z_muo_nphotons->Fill(n_photons, weight_Z_muo);
     if (ipho0 != -1) {
       h_Z_muo_pho0_pt->Fill(Photon_pt[ipho0], weight_Z_muo * weight_pho0);
       h_Z_muo_pho0_eta->Fill(Photon_eta[ipho0], weight_Z_muo * weight_pho0);
       h_Z_muo_pho0_phi->Fill(Photon_phi[ipho0], weight_Z_muo * weight_pho0);
       h_Z_muo_pho0_r9->Fill(Photon_r9[ipho0], weight_Z_muo * weight_pho0);
       h_Z_muo_pho0_sieie->Fill(Photon_sieie[ipho0], weight_Z_muo * weight_pho0);
       h_Z_muo_pho0_mva->Fill(Photon_mvaID[ipho0], weight_Z_muo * weight_pho0);
       h_Z_muo_pho0_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho0], weight_Z_muo * weight_pho0);
       h_Z_muo_pho0_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho0], weight_Z_muo * weight_pho0);
       h_Z_muo_pho0_dR->Fill(TMath::Min(pho0.DeltaR(muo0), pho0.DeltaR(muo1)), weight_Z_muo * weight_pho0);
       h_Z_muo_pho0->Fill(Z_muo0_muo1_m, weight_Z_muo * weight_pho0);
       h_Z_muo_muo0_pho0->Fill((muo0+pho0).M(), weight_Z_muo * weight_pho0);
       h_Z_muo_muo1_pho0->Fill((muo1+pho0).M(), weight_Z_muo * weight_pho0);
     }
     if (ipho1 != -1) {
       h_Z_muo_pho1_pt->Fill(Photon_pt[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_pho1_eta->Fill(Photon_eta[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_pho1_phi->Fill(Photon_phi[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_pho1_r9->Fill(Photon_r9[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_pho1_sieie->Fill(Photon_sieie[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_pho1_mva->Fill(Photon_mvaID[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_pho1_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_pho1_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_pho1_dR->Fill(TMath::Min(pho1.DeltaR(muo0), pho1.DeltaR(muo1)), weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_pho0_pho1_pt->Fill((pho0+pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_muo0_pho1->Fill((muo0+pho1).M(), weight_Z_muo * weight_pho1);
       h_Z_muo_muo1_pho1->Fill((muo1+pho1).M(), weight_Z_muo * weight_pho1);
       h_Z_muo_muo0_pho0_pho1->Fill((muo0+pho0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_muo1_pho0_pho1->Fill((muo1+pho0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_Z_muo_muo0_muo1_pho0_pho1->Fill((muo0+muo1+pho0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
     }
   }

   if (Z_muo_sel_qcd) {
     QCD(h_Z_muo_nphotons)->Fill(n_photons_qcd, weight_Z_muo_qcd);
     if (ipho0_qcd != -1) {
       QCD(h_Z_muo_pho0_pt)->Fill(Photon_pt[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_pho0_r9)->Fill(Photon_r9[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_pho0_dR)->Fill(TMath::Min(pho0_qcd.DeltaR(muo0_qcd), pho0_qcd.DeltaR(muo1_qcd)), weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_pho0)->Fill(Z_muo0_muo1_m_qcd, weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_muo0_pho0)->Fill((muo0_qcd+pho0_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_Z_muo_muo1_pho0)->Fill((muo1_qcd+pho0_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd);
     }
     if (ipho1_qcd != -1) {
       QCD(h_Z_muo_pho1_pt)->Fill(Photon_pt[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_pho1_eta)->Fill(Photon_eta[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_pho1_phi)->Fill(Photon_phi[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_pho1_r9)->Fill(Photon_r9[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_pho1_sieie)->Fill(Photon_sieie[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_pho1_mva)->Fill(Photon_mvaID[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_pho1_dR)->Fill(TMath::Min(pho1_qcd.DeltaR(muo0_qcd), pho1_qcd.DeltaR(muo1_qcd)), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_pho0_pho1_pt)->Fill((pho0_qcd+pho1_qcd).Pt(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_muo0_pho1)->Fill((muo0_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_muo1_pho1)->Fill((muo1_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_muo0_pho0_pho1)->Fill((muo0_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_muo1_pho0_pho1)->Fill((muo1_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_Z_muo_muo0_muo1_pho0_pho1)->Fill((muo0_qcd+muo1_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
     }
   }

// W jet(s) plots

   if (W_ele_sel) {
     h_W_ele_njets->Fill(n_jets, weight_W_ele);
     if (n_jets >= 1) {
       h_W_ele_jet0_pt->Fill(Jet_pt[ijet0], weight_W_ele);
       h_W_ele_jet0_eta->Fill(Jet_eta[ijet0], weight_W_ele);
       h_W_ele_jet0_phi->Fill(Jet_phi[ijet0], weight_W_ele);
       if (ipho0 != -1) {
         h_W_ele_pho0_jet0_dR->Fill(pho0.DeltaR(jet0), weight_W_ele * weight_pho0);
       }
       if (ipho1 != -1) {
         h_W_ele_pho1_jet0_dR->Fill(pho1.DeltaR(jet0), weight_W_ele * weight_pho1);
       }
     }
   }

   if (W_ele_sel_qcd) {
     QCD(h_W_ele_njets)->Fill(n_jets_qcd, weight_W_ele_qcd);
     if (n_jets_qcd >= 1) {
       QCD(h_W_ele_jet0_pt)->Fill(Jet_pt[ijet0_qcd], weight_W_ele_qcd);
       QCD(h_W_ele_jet0_eta)->Fill(Jet_eta[ijet0_qcd], weight_W_ele_qcd);
       QCD(h_W_ele_jet0_phi)->Fill(Jet_phi[ijet0_qcd], weight_W_ele_qcd);
       if (ipho0_qcd != -1) {
         QCD(h_W_ele_pho0_jet0_dR)->Fill(pho0_qcd.DeltaR(jet0_qcd), weight_W_ele_qcd * weight_pho0_qcd);
       }
       if (ipho1_qcd != -1) {
         QCD(h_W_ele_pho1_jet0_dR)->Fill(pho1_qcd.DeltaR(jet0_qcd), weight_W_ele_qcd * weight_pho1_qcd);
       }
     }
   }

   if (W_muo_sel) {
     h_W_muo_njets->Fill(n_jets, weight_W_muo);
     if (n_jets >= 1) {
       h_W_muo_jet0_pt->Fill(Jet_pt[ijet0], weight_W_muo);
       h_W_muo_jet0_eta->Fill(Jet_eta[ijet0], weight_W_muo);
       h_W_muo_jet0_phi->Fill(Jet_phi[ijet0], weight_W_muo);
       if (ipho0 != -1) {
         h_W_muo_pho0_jet0_dR->Fill(pho0.DeltaR(jet0), weight_W_muo * weight_pho0);
       }
       if (ipho1 != -1) {
         h_W_muo_pho1_jet0_dR->Fill(pho1.DeltaR(jet0), weight_W_muo * weight_pho1);
       }
     }
   }

   if (W_muo_sel_qcd) {
     QCD(h_W_muo_njets)->Fill(n_jets_qcd, weight_W_muo_qcd);
     if (n_jets_qcd >= 1) {
       QCD(h_W_muo_jet0_pt)->Fill(Jet_pt[ijet0_qcd], weight_W_muo_qcd);
       QCD(h_W_muo_jet0_eta)->Fill(Jet_eta[ijet0_qcd], weight_W_muo_qcd);
       QCD(h_W_muo_jet0_phi)->Fill(Jet_phi[ijet0_qcd], weight_W_muo_qcd);
       if (ipho0_qcd != -1) {
         QCD(h_W_muo_pho0_jet0_dR)->Fill(pho0_qcd.DeltaR(jet0_qcd), weight_W_muo_qcd * weight_pho0_qcd);
       }
       if (ipho1_qcd != -1) {
         QCD(h_W_muo_pho1_jet0_dR)->Fill(pho1_qcd.DeltaR(jet0_qcd), weight_W_muo_qcd * weight_pho1_qcd);
       }
     }
   }

// Z jet(s) plots

   if (Z_ele_sel) {
     h_Z_ele_njets->Fill(n_jets, weight_Z_ele);
     if (n_jets >= 1) {
       h_Z_ele_jet0_pt->Fill(Jet_pt[ijet0], weight_Z_ele);
       h_Z_ele_jet0_eta->Fill(Jet_eta[ijet0], weight_Z_ele);
       h_Z_ele_jet0_phi->Fill(Jet_phi[ijet0], weight_Z_ele);
       if (ipho0 != -1) {
         h_Z_ele_pho0_jet0_dR->Fill(pho0.DeltaR(jet0), weight_Z_ele * weight_pho0);
       }
       if (ipho1 != -1) {
         h_Z_ele_pho1_jet0_dR->Fill(pho1.DeltaR(jet0), weight_Z_ele * weight_pho1);
       }
     }
   }

   if (Z_ele_sel_qcd) {
     QCD(h_Z_ele_njets)->Fill(n_jets_qcd, weight_Z_ele_qcd);
     if (n_jets_qcd >= 1) {
       QCD(h_Z_ele_jet0_pt)->Fill(Jet_pt[ijet0_qcd], weight_Z_ele_qcd);
       QCD(h_Z_ele_jet0_eta)->Fill(Jet_eta[ijet0_qcd], weight_Z_ele_qcd);
       QCD(h_Z_ele_jet0_phi)->Fill(Jet_phi[ijet0_qcd], weight_Z_ele_qcd);
       if (ipho0_qcd != -1) {
         QCD(h_Z_ele_pho0_jet0_dR)->Fill(pho0_qcd.DeltaR(jet0_qcd), weight_Z_ele_qcd * weight_pho0_qcd);
       }
       if (ipho1_qcd != -1) {
         QCD(h_Z_ele_pho1_jet0_dR)->Fill(pho1_qcd.DeltaR(jet0_qcd), weight_Z_ele_qcd * weight_pho1_qcd);
       }
     }
   }

   if (Z_muo_sel) {
     h_Z_muo_njets->Fill(n_jets, weight_Z_muo);
     if (n_jets >= 1) {
       h_Z_muo_jet0_pt->Fill(Jet_pt[ijet0], weight_Z_muo);
       h_Z_muo_jet0_eta->Fill(Jet_eta[ijet0], weight_Z_muo);
       h_Z_muo_jet0_phi->Fill(Jet_phi[ijet0], weight_Z_muo);
       if (ipho0 != -1) {
         h_Z_muo_pho0_jet0_dR->Fill(pho0.DeltaR(jet0), weight_Z_muo * weight_pho0);
       }
       if (ipho1 != -1) {
         h_Z_muo_pho1_jet0_dR->Fill(pho1.DeltaR(jet0), weight_Z_muo * weight_pho1);
       }
     }
   }

   if (Z_muo_sel_qcd) {
     QCD(h_Z_muo_njets)->Fill(n_jets_qcd, weight_Z_muo_qcd);
     if (n_jets_qcd >= 1) {
       QCD(h_Z_muo_jet0_pt)->Fill(Jet_pt[ijet0_qcd], weight_Z_muo_qcd);
       QCD(h_Z_muo_jet0_eta)->Fill(Jet_eta[ijet0_qcd], weight_Z_muo_qcd);
       QCD(h_Z_muo_jet0_phi)->Fill(Jet_phi[ijet0_qcd], weight_Z_muo_qcd);
       if (ipho0_qcd != -1) {
         QCD(h_Z_muo_pho0_jet0_dR)->Fill(pho0_qcd.DeltaR(jet0_qcd), weight_Z_muo_qcd * weight_pho0_qcd);
       }
       if (ipho1_qcd != -1) {
         QCD(h_Z_muo_pho1_jet0_dR)->Fill(pho1_qcd.DeltaR(jet0_qcd), weight_Z_muo_qcd * weight_pho1_qcd);
       }
     }
   }

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (W_ele_sel && W_ele_sel_gen) {
     h_W_ele_nphotons_rec_gen->Fill(n_photons, n_photons_gen, weight_W_ele);
   }
   if (W_ele_sel && !W_ele_sel_gen) {
     h_W_ele_nphotons_rec_gen->Fill(n_photons, -1, weight_W_ele);
   }
   if (!W_ele_sel && W_ele_sel_gen) {
     h_W_ele_nphotons_rec_gen->Fill(-1, n_photons_gen, weight_gen * weight_pu_ele);
   }

   if (W_muo_sel && W_muo_sel_gen) {
     h_W_muo_nphotons_rec_gen->Fill(n_photons, n_photons_gen, weight_W_muo);
   }
   if (W_muo_sel && !W_muo_sel_gen) {
     h_W_muo_nphotons_rec_gen->Fill(n_photons, -1, weight_W_muo);
   }
   if (!W_muo_sel && W_muo_sel_gen) {
     h_W_muo_nphotons_rec_gen->Fill(-1, n_photons_gen, weight_gen * weight_pu_muo);
   }

   if (Z_ele_sel && Z_ele_sel_gen) {
     h_Z_ele_nphotons_rec_gen->Fill(n_photons, n_photons_gen, weight_Z_ele);
   }
   if (Z_ele_sel && !Z_ele_sel_gen) {
     h_Z_ele_nphotons_rec_gen->Fill(n_photons, -1, weight_Z_ele);
   }
   if (!Z_ele_sel && Z_ele_sel_gen) {
     h_Z_ele_nphotons_rec_gen->Fill(-1, n_photons_gen, weight_gen * weight_pu_ele);
   }

   if (Z_muo_sel && Z_muo_sel_gen) {
     h_Z_muo_nphotons_rec_gen->Fill(n_photons, n_photons_gen, weight_Z_muo);
   }
   if (Z_muo_sel && !Z_muo_sel_gen) {
     h_Z_muo_nphotons_rec_gen->Fill(n_photons, -1, weight_Z_muo);
   }
   if (!Z_muo_sel && Z_muo_sel_gen) {
     h_Z_muo_nphotons_rec_gen->Fill(-1, n_photons_gen, weight_gen * weight_pu_muo);
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   return kTRUE;
}

void mainSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

   TDatime now;
   Info("SlaveTerminate", "%s", now.AsSQLString());

}

void mainSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   TDatime now;
   Info("Terminate", "%s", now.AsSQLString());

}
