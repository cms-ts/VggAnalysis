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

#include <TFile.h>
#include <TDatime.h>
#include <TRandom.h>
#include <TLorentzVector.h>

#if defined(mainSelectorDT16H_cxx)
#define mainSelectorDT16_cxx
#endif // defined(mainSelectorDT16H_cxx)

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
   file_ele_pu = TFile::Open("root/ratio_pileup_Run2016_DoubleEG_22Aug2018.root");
   file_muo_pu = TFile::Open("root/ratio_pileup_Run2016_DoubleMuon_22Aug2018.root");
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

   TFile* file_pho_sf_eff;
   TFile* file_pho_sf_reco;

#if defined(mainSelectorMC16_cxx)
// FIXME
   file_ele_sf_eff = TFile::Open("root/sf_ele_2016_LegacyReReco_ElectronMVAwp80.root");
   file_ele_sf_reco = TFile::Open("root/sf_ele_2016_LegacyReReco_EGM2D_RECO.root");
   //file_ele_sf_eff = TFile::Open("root/sf_ele_2016_EGM2D_runBCDEF_passingMVA94Xwp80.root");
   //file_ele_sf_reco = TFile::Open("root/sf_ele_2016_EGM2D_runBCDEF_passingRECO.root");
// FIXME

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");
   sf_ele_reco = (TH2D*)file_ele_sf_reco->Get("EGamma_SF2D");

   sf_ele_eff->SetDirectory(0);
   sf_ele_reco->SetDirectory(0);

   file_ele_sf_eff->Close();
   file_ele_sf_reco->Close();

   file_muo_sf_id = TFile::Open("root/sf_muo_2016_RunBCDEF_ID.root");
   file_muo_sf_iso = TFile::Open("root/sf_muo_2016_RunBCDEF_ISO.root");

   TH2D* sf_muo_id_RunBCDEF = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_eta_pt");
   TH2D* sf_muo_iso_RunBCDEF = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");

   sf_muo_id_RunBCDEF->SetDirectory(0);
   sf_muo_iso_RunBCDEF->SetDirectory(0);

   file_muo_sf_id->Close();
   file_muo_sf_iso->Close();

   file_muo_sf_id = TFile::Open("root/sf_muo_2016_RunGH_ID.root");
   file_muo_sf_iso = TFile::Open("root/sf_muo_2016_RunGH_ISO.root");

   TH2D* sf_muo_id_RunGH = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_eta_pt");
   TH2D* sf_muo_iso_RunGH = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");

   sf_muo_id_RunGH->SetDirectory(0);
   sf_muo_iso_RunGH->SetDirectory(0);

   file_muo_sf_id->Close();
   file_muo_sf_iso->Close();

   sf_muo_id = (TH2D*)sf_muo_id_RunBCDEF->Clone();
   sf_muo_iso = (TH2D*)sf_muo_iso_RunBCDEF->Clone();

   sf_muo_id->Add(sf_muo_id_RunBCDEF, sf_muo_id_RunGH, 19.69/35.917, 16.227/35.917);
   sf_muo_iso->Add(sf_muo_iso_RunBCDEF, sf_muo_iso_RunGH, 19.69/35.917, 16.227/35.917);

// FIXME
   file_pho_sf_eff = TFile::Open("root/sf_pho_2016_LegacyReReco_PhotonMVAwp80.root");
   //file_pho_sf_eff = TFile::Open("root/sf_pho_2016_EGM2D_runBCDEF_passingMVA94Xwp80iso.root");
// FIXME
   //file_pho_sf_reco = TFile::Open("root/sf_pho_2016_EGM2D_BtoH_GT20GeV_RecoSF_2018.root");
   sf_pho_eff = (TH2D*)file_pho_sf_eff->Get("EGamma_SF2D");
   //sf_pho_reco = (TH2D*)file_pho_sf_reco->Get("EGamma_SF2D");

   sf_pho_eff->SetDirectory(0);
   //sf_pho_reco->SetDirectory(0);

   file_pho_sf_eff->Close();
   //file_pho_sf_reco->Close();
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   file_ele_sf_eff = TFile::Open("root/sf_ele_2017_EGM2D_runBCDEF_passingMVA94Xwp80.root");
   file_ele_sf_reco = TFile::Open("root/sf_ele_2017_EGM2D_runBCDEF_passingRECO.root");

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");
   sf_ele_reco = (TH2D*)file_ele_sf_reco->Get("EGamma_SF2D");

   sf_ele_eff->SetDirectory(0);
   sf_ele_reco->SetDirectory(0);

   file_ele_sf_eff->Close();
   file_ele_sf_reco->Close();

   file_muo_sf_id = TFile::Open("root/sf_muo_2017_RunBCDEF_ID.root");
   file_muo_sf_iso = TFile::Open("root/sf_muo_2017_RunBCDEF_ISO.root");

   sf_muo_id = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_pt_abseta");
   sf_muo_iso = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

   sf_muo_id->SetDirectory(0);
   sf_muo_iso->SetDirectory(0);

   file_muo_sf_id->Close();
   file_muo_sf_iso->Close();

   file_pho_sf_eff = TFile::Open("root/sf_pho_2017_EGM2D_runBCDEF_passingMVA94Xwp80iso.root");
// FIXME
   //file_pho_sf_reco = TFile::Open("root/sf_pho_2017_EGM2D_BtoH_GT20GeV_RecoSF_2018.root");
   sf_pho_eff = (TH2D*)file_pho_sf_eff->Get("EGamma_SF2D");
   //sf_pho_reco = (TH2D*)file_pho_sf_reco->Get("EGamma_SF2D");

   sf_pho_eff->SetDirectory(0);
   //sf_pho_reco->SetDirectory(0);

   file_pho_sf_eff->Close();
   //file_pho_sf_reco->Close();
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   file_ele_sf_eff = TFile::Open("root/sf_ele_2018_ElectronMVA80.root");
   file_ele_sf_reco = TFile::Open("root/sf_ele_2018_EGM2D_RECO.root");

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");
   sf_ele_reco = (TH2D*)file_ele_sf_reco->Get("EGamma_SF2D");

   sf_ele_eff->SetDirectory(0);
   sf_ele_reco->SetDirectory(0);

   file_ele_sf_eff->Close();
   file_ele_sf_reco->Close();

// FIXME
   file_muo_sf_id = TFile::Open("root/sf_muo_2017_RunBCDEF_ID.root");
   file_muo_sf_iso = TFile::Open("root/sf_muo_2017_RunBCDEF_ISO.root");

   sf_muo_id = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_pt_abseta");
   sf_muo_iso = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

   sf_muo_id->SetDirectory(0);
   sf_muo_iso->SetDirectory(0);

   file_muo_sf_id->Close();
   file_muo_sf_iso->Close();
// FIXME

   file_pho_sf_eff = TFile::Open("root/sf_pho_2018_PhotonsMVAwp80.root");
// FIXME
   //file_pho_sf_reco = TFile::Open("root/sf_pho_2018_EGM2D_BtoH_GT20GeV_RecoSF_2018.root");

   sf_pho_eff = (TH2D*)file_pho_sf_eff->Get("EGamma_SF2D");
   //sf_pho_reco = (TH2D*)file_pho_sf_reco->Get("EGamma_SF2D");

   sf_pho_eff->SetDirectory(0);
   //sf_pho_reco->SetDirectory(0);

   file_pho_sf_eff->Close();
   //file_pho_sf_reco->Close();
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
   jet_resolution = new JME::JetResolution("jme/Fall17_25nsV1_MC_PtResolution_AK4PFchs.txt");
   jet_resolution_sf = new JME::JetResolutionScaleFactor("jme/Fall17_25nsV1_MC_SF_AK4PFchs.txt");
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
// FIXME
   jet_resolution = new JME::JetResolution("jme/Fall17_25nsV1_MC_PtResolution_AK4PFchs.txt");
   jet_resolution_sf = new JME::JetResolutionScaleFactor("jme/Fall17_25nsV1_MC_SF_AK4PFchs.txt");
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

   // create the histograms
   h_nevt = new TH1D("h_nevt", "h_nevt", 10, 0., 10.);

   h_W_ele = new TH1D("h_W_ele", "h_W_ele", 100, 0., 200.);
   h_W_muo = new TH1D("h_W_muo", "h_W_muo", 100, 0., 200.);

   h_W_ele_npvs = new TH1D("h_W_ele_npvs", "h_W_ele_npvs", 100, 0., 100.);
   h_W_ele_npvs_w = new TH1D("h_W_ele_npvs_w", "h_W_ele_npvs_w", 100, 0., 100.);
   h_W_muo_npvs = new TH1D("h_W_muo_npvs", "h_W_muo_npvs", 100, 0., 100.);
   h_W_muo_npvs_w = new TH1D("h_W_muo_npvs_w", "h_W_muo_npvs_w", 100, 0., 100.);

   h_W_ele0_pt = new TH1D("h_W_ele0_pt", "h_W_ele0_pt", 100, 0., 200.);
   h_W_ele0_eta = new TH1D("h_W_ele0_eta", "h_W_ele0_eta", 50, -2.5, 2.5);
   h_W_ele0_phi = new TH1D("h_W_ele0_phi", "h_W_ele0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_ele0_r9 = new TH1D("h_W_ele0_r9", "h_W_ele0_r9", 50, 0., 5.);
   h_W_ele0_sieie = new TH1D("h_W_ele0_sieie", "h_W_ele0_sieie", 50, 0., 0.05);
   h_W_ele_met_pt = new TH1D("h_W_ele_met_pt", "h_W_ele_met_pt", 100, 0., 200.);
   h_W_ele_met_phi = new TH1D("h_W_ele_met_phi", "h_W_ele_met_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_ele_met_sign = new TH1D("h_W_ele_met_sign", "h_W_ele_met_sign", 100, 0., 100.);
   h_W_muo0_pt = new TH1D("h_W_muo0_pt", "h_W_muo0_pt", 100, 0., 200.);
   h_W_muo0_eta = new TH1D("h_W_muo0_eta", "h_W_muo0_eta", 50, -2.5, 2.5);
   h_W_muo0_phi = new TH1D("h_W_muo0_phi", "h_W_muo0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_met_pt = new TH1D("h_W_muo_met_pt", "h_W_muo_met_pt", 100, 0., 200.);
   h_W_muo_met_phi = new TH1D("h_W_muo_met_phi", "h_W_muo_met_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_met_sign = new TH1D("h_W_muo_met_sign", "h_W_muo_met_sign", 100, 0., 100.);

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

   h_Z_ele0_pt = new TH1D("h_Z_ele0_pt", "h_Z_ele0_pt", 100, 0., 200.);
   h_Z_ele0_eta = new TH1D("h_Z_ele0_eta", "h_Z_ele0_eta", 50, -2.5, 2.5);
   h_Z_ele0_phi = new TH1D("h_Z_ele0_phi", "h_Z_ele0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_ele0_r9 = new TH1D("h_Z_ele0_r9", "h_Z_ele0_r9", 50, 0., 5.);
   h_Z_ele0_sieie = new TH1D("h_Z_ele0_sieie", "h_Z_ele0_sieie", 50, 0., 0.05);
   h_Z_ele1_pt = new TH1D("h_Z_ele1_pt", "h_Z_ele1_pt", 100, 0., 200.);
   h_Z_ele1_eta = new TH1D("h_Z_ele1_eta", "h_Z_ele1_eta", 50, -2.5, 2.5);
   h_Z_ele1_phi = new TH1D("h_Z_ele1_phi", "h_Z_ele1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_ele1_r9 = new TH1D("h_Z_ele1_r9", "h_Z_ele1_r9", 50, 0., 5.);
   h_Z_ele1_sieie = new TH1D("h_Z_ele1_sieie", "h_Z_ele1_sieie", 50, 0., 0.05);
   h_Z_ele_met_pt = new TH1D("h_Z_ele_met_pt", "h_Z_ele_met_pt", 100, 0., 200.);
   h_Z_ele_met_phi = new TH1D("h_Z_ele_met_phi", "h_Z_ele_met_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_ele_met_sign = new TH1D("h_Z_ele_met_sign", "h_Z_ele_met_sign", 100, 0., 100.);
   h_Z_muo0_pt = new TH1D("h_Z_muo0_pt", "h_Z_muo0_pt", 100, 0., 200.);
   h_Z_muo0_eta = new TH1D("h_Z_muo0_eta", "h_Z_muo0_eta", 50, -2.5, 2.5);
   h_Z_muo0_phi = new TH1D("h_Z_muo0_phi", "h_Z_muo0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo1_pt = new TH1D("h_Z_muo1_pt", "h_Z_muo1_pt", 100, 0., 200.);
   h_Z_muo1_eta = new TH1D("h_Z_muo1_eta", "h_Z_muo1_eta", 50, -2.5, 2.5);
   h_Z_muo1_phi = new TH1D("h_Z_muo1_phi", "h_Z_muo1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo_met_pt = new TH1D("h_Z_muo_met_pt", "h_Z_muo_met_pt", 100, 0., 200.);
   h_Z_muo_met_phi = new TH1D("h_Z_muo_met_phi", "h_Z_muo_met_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo_met_sign = new TH1D("h_Z_muo_met_sign", "h_Z_muo_met_sign", 100, 0., 100.);

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

   h_TrigObj = new TH2D("h_TrigObj", "h_TrigObj", 34, -1.5, 32.5, 25, -0.5, 24.5);

   h_W_ele_njets = new TH1D("h_W_ele_njets", "h_W_ele_njets", 10, -0.5, 9.5);
   h_W_ele_jet0_pt = new TH1D("h_W_ele_jet0_pt", "h_W_ele_jet0_pt", 100, 0., 200.);
   h_W_ele_jet0_eta = new TH1D("h_W_ele_jet0_eta", "h_W_ele_jet0_eta", 50, -2.5, 2.5);
   h_W_ele_jet0_phi = new TH1D("h_W_ele_jet0_phi", "h_W_ele_jet0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_njets = new TH1D("h_W_muo_njets", "h_W_muo_njets", 10, -0.5, 9.5);
   h_W_muo_jet0_pt = new TH1D("h_W_muo_jet0_pt", "h_W_muo_jet0_pt", 100, 0., 200.);
   h_W_muo_jet0_eta = new TH1D("h_W_muo_jet0_eta", "h_W_muo_jet0_eta", 50, -2.5, 2.5);
   h_W_muo_jet0_phi = new TH1D("h_W_muo_jet0_phi", "h_W_muo_jet0_phi", 24, -TMath::Pi(), TMath::Pi());

   h_Z_ele_njets = new TH1D("h_Z_ele_njets", "h_Z_ele_njets", 10, -0.5, 9.5);
   h_Z_ele_jet0_pt = new TH1D("h_Z_ele_jet0_pt", "h_Z_ele_jet0_pt", 100, 0., 200.);
   h_Z_ele_jet0_eta = new TH1D("h_Z_ele_jet0_eta", "h_Z_ele_jet0_eta", 50, -2.5, 2.5);
   h_Z_ele_jet0_phi = new TH1D("h_Z_ele_jet0_phi", "h_Z_ele_jet0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo_njets = new TH1D("h_Z_muo_njets", "h_Z_muo_njets", 10, -0.5, 9.5);
   h_Z_muo_jet0_pt = new TH1D("h_Z_muo_jet0_pt", "h_Z_muo_jet0_pt", 100, 0., 200.);
   h_Z_muo_jet0_eta = new TH1D("h_Z_muo_jet0_eta", "h_Z_muo_jet0_eta", 50, -2.5, 2.5);
   h_Z_muo_jet0_phi = new TH1D("h_Z_muo_jet0_phi", "h_Z_muo_jet0_phi", 24, -TMath::Pi(), TMath::Pi());

   h_W_ele_nphotons = new TH1D("h_W_ele_nphotons", "h_W_ele_nphotons", 6, -0.5, 5.5);
   h_W_ele_pho0_pt = new TH1D("h_W_ele_pho0_pt", "h_W_ele_pho0_pt", 50, 0., 200.);
   h_W_ele_pho0_eta = new TH1D("h_W_ele_pho0_eta", "h_W_ele_pho0_eta", 50, -2.5, 2.5);
   h_W_ele_pho0_phi = new TH1D("h_W_ele_pho0_phi", "h_W_ele_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_ele_pho0_r9 = new TH1D("h_W_ele_pho0_r9", "h_W_ele_pho0_r9", 50, 0., 5.);
   h_W_ele_pho0_sieie = new TH1D("h_W_ele_pho0_sieie", "h_W_ele_pho0_sieie", 50, 0., 0.05);
   h_W_ele_pho1_pt = new TH1D("h_W_ele_pho1_pt", "h_W_ele_pho1_pt", 50, 0., 200.);
   h_W_ele_pho1_eta = new TH1D("h_W_ele_pho1_eta", "h_W_ele_pho1_eta", 50, -2.5, 2.5);
   h_W_ele_pho1_phi = new TH1D("h_W_ele_pho1_phi", "h_W_ele_pho1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_ele_pho1_r9 = new TH1D("h_W_ele_pho1_r9", "h_W_ele_pho1_r9", 50, 0., 5.);
   h_W_ele_pho1_sieie = new TH1D("h_W_ele_pho1_sieie", "h_W_ele_pho1_sieie", 50, 0., 0.05);
   h_W_muo_nphotons = new TH1D("h_W_muo_nphotons", "h_W_muo_nphotons", 6, -0.5, 5.5);
   h_W_muo_pho0_pt = new TH1D("h_W_muo_pho0_pt", "h_W_muo_pho0_pt", 50, 0., 200.);
   h_W_muo_pho0_eta = new TH1D("h_W_muo_pho0_eta", "h_W_muo_pho0_eta", 50, -2.5, 2.5);
   h_W_muo_pho0_phi = new TH1D("h_W_muo_pho0_phi", "h_W_muo_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_pho0_r9 = new TH1D("h_W_muo_pho0_r9", "h_W_muo_pho0_r9", 50, 0., 5.);
   h_W_muo_pho0_sieie = new TH1D("h_W_muo_pho0_sieie", "h_W_muo_pho0_sieie", 50, 0., 0.05);
   h_W_muo_pho1_pt = new TH1D("h_W_muo_pho1_pt", "h_W_muo_pho1_pt", 50, 0., 200.);
   h_W_muo_pho1_eta = new TH1D("h_W_muo_pho1_eta", "h_W_muo_pho1_eta", 50, -2.5, 2.5);
   h_W_muo_pho1_phi = new TH1D("h_W_muo_pho1_phi", "h_W_muo_pho1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_W_muo_pho1_r9 = new TH1D("h_W_muo_pho1_r9", "h_W_muo_pho1_r9", 50, 0., 5.);
   h_W_muo_pho1_sieie = new TH1D("h_W_muo_pho1_sieie", "h_W_muo_pho1_sieie", 50, 0., 0.05);

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
   h_Z_ele_pho0_pt = new TH1D("h_Z_ele_pho0_pt", "h_Z_ele_pho0_pt", 50, 0., 200.);
   h_Z_ele_pho0_eta = new TH1D("h_Z_ele_pho0_eta", "h_Z_ele_pho0_eta", 50, -2.5, 2.5);
   h_Z_ele_pho0_phi = new TH1D("h_Z_ele_pho0_phi", "h_Z_ele_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_ele_pho0_r9 = new TH1D("h_Z_ele_pho0_r9", "h_Z_ele_pho0_r9", 50, 0., 5.);
   h_Z_ele_pho0_sieie = new TH1D("h_Z_ele_pho0_sieie", "h_Z_ele_pho0_sieie", 50, 0., 0.05);
   h_Z_ele_pho1_pt = new TH1D("h_Z_ele_pho1_pt", "h_Z_ele_pho1_pt", 50, 0., 200.);
   h_Z_ele_pho1_eta = new TH1D("h_Z_ele_pho1_eta", "h_Z_ele_pho1_eta", 50, -2.5, 2.5);
   h_Z_ele_pho1_phi = new TH1D("h_Z_ele_pho1_phi", "h_Z_ele_pho1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_ele_pho1_r9 = new TH1D("h_Z_ele_pho1_r9", "h_Z_ele_pho1_r9", 50, 0., 5.);
   h_Z_ele_pho1_sieie = new TH1D("h_Z_ele_pho1_sieie", "h_Z_ele_pho1_sieie", 50, 0., 0.05);
   h_Z_muo_nphotons = new TH1D("h_Z_muo_nphotons", "h_Z_muo_nphotons", 6, -0.5, 5.5);
   h_Z_muo_pho0_pt = new TH1D("h_Z_muo_pho0_pt", "h_Z_muo_pho0_pt", 50, 0., 200.);
   h_Z_muo_pho0_eta = new TH1D("h_Z_muo_pho0_eta", "h_Z_muo_pho0_eta", 50, -2.5, 2.5);
   h_Z_muo_pho0_phi = new TH1D("h_Z_muo_pho0_phi", "h_Z_muo_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo_pho0_r9 = new TH1D("h_Z_muo_pho0_r9", "h_Z_muo_pho0_r9", 50, 0., 5.);
   h_Z_muo_pho0_sieie = new TH1D("h_Z_muo_pho0_sieie", "h_Z_muo_pho0_sieie", 50, 0., 0.05);
   h_Z_muo_pho1_pt = new TH1D("h_Z_muo_pho1_pt", "h_Z_muo_pho1_pt", 50, 0., 200.);
   h_Z_muo_pho1_eta = new TH1D("h_Z_muo_pho1_eta", "h_Z_muo_pho1_eta", 50, -2.5, 2.5);
   h_Z_muo_pho1_phi = new TH1D("h_Z_muo_pho1_phi", "h_Z_muo_pho1_phi", 24, -TMath::Pi(), TMath::Pi());
   h_Z_muo_pho1_r9 = new TH1D("h_Z_muo_pho1_r9", "h_Z_muo_pho1_r9", 50, 0., 5.);
   h_Z_muo_pho1_sieie = new TH1D("h_Z_muo_pho1_sieie", "h_Z_muo_pho1_sieie", 50, 0., 0.05);

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

   h_W_ele_pho0 = new TH1D("h_W_ele_pho0", "h_W_ele_pho0", 90, 20, 200);
   h_W_muo_pho0 = new TH1D("h_W_muo_pho0", "h_W_muo_pho0", 90, 20, 200);
   h_Z_ele_pho0 = new TH1D("h_Z_ele_pho0", "h_Z_ele_pho0", 40, 71, 111);
   h_Z_muo_pho0 = new TH1D("h_Z_muo_pho0", "h_Z_muo_pho0", 40, 71, 111);

   h_W_ele_pho0_pho1_pt = new TH1D("h_W_ele_pho0_pho1_pt", "h_W_ele_pho0_pho1_pt", 20, 0., 200.);
   h_W_ele_ele0_pho0 = new TH1D("h_W_ele_ele0_pho0", "h_W_ele_ele0_pho0", 100, 0., 200.);
   h_W_ele_ele0_pho1 = new TH1D("h_W_ele_ele0_pho1", "h_W_ele_ele0_pho1", 20, 0., 200.);
   h_W_ele_ele0_pho0_pho1 = new TH1D("h_W_ele_ele0_pho0_pho1", "h_W_ele_ele0_pho0_pho1", 20, 0., 200.);

   h_W_muo_pho0_pho1_pt = new TH1D("h_W_muo_pho0_pho1_pt", "h_W_muo_pho0_pho1_pt", 20, 0., 200.);
   h_W_muo_muo0_pho0 = new TH1D("h_W_muo_muo0_pho0", "h_W_muo_muo0_pho0", 100, 0., 200.);
   h_W_muo_muo0_pho1 = new TH1D("h_W_muo_muo0_pho1", "h_W_muo_muo0_pho1", 20, 0., 200.);
   h_W_muo_muo0_pho0_pho1 = new TH1D("h_W_muo_muo0_pho0_pho1", "h_W_muo_muo0_pho0_pho1", 20, 0., 200.);

   h_Z_ele_pho0_pho1_pt = new TH1D("h_Z_ele_pho0_pho1_pt", "h_Z_ele_pho0_pho1_pt", 20, 0., 200.);
   h_Z_ele_ele0_pho0 = new TH1D("h_Z_ele_ele0_pho0", "h_Z_ele_ele0_pho0", 40, 71., 111.);
   h_Z_ele_ele0_pho1 = new TH1D("h_Z_ele_ele0_pho1", "h_Z_ele_ele0_pho1", 40, 71., 111.);
   h_Z_ele_ele1_pho0 = new TH1D("h_Z_ele_ele1_pho0", "h_Z_ele_ele1_pho0", 40, 71., 111.);
   h_Z_ele_ele1_pho1 = new TH1D("h_Z_ele_ele1_pho1", "h_Z_ele_ele1_pho1", 40, 71., 111.);
   h_Z_ele_ele0_pho0_pho1 = new TH1D("h_Z_ele_ele0_pho0_pho1", "h_Z_ele_ele0_pho0_pho1", 40, 71., 111.);
   h_Z_ele_ele1_pho0_pho1 = new TH1D("h_Z_ele_ele1_pho0_pho1", "h_Z_ele_ele1_pho0_pho1", 40, 71., 111.);
   h_Z_ele_ele0_ele1_pho0_pho1 = new TH1D("h_Z_ele_ele0_ele1_pho0_pho1", "h_Z_ele_ele0_ele1_pho0_pho1", 40, 71., 111.);

   h_Z_muo_pho0_pho1_pt = new TH1D("h_Z_muo_pho0_pho1_pt", "h_Z_muo_pho0_pho1_pt", 20, 0., 200.);
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

   if (isWJetsToLNu || isWG || isWGG || isDYJetsToLL || isZG || isZGG) {

     int iele0_gen = -1;
     int iele1_gen = -1;

     for (uint i = 0; i < *nGenDressedLepton; i++) {
       if (fabs(GenDressedLepton_pdgId[i]) != 11) continue;
       if (GenDressedLepton_pt[i] < 15) continue;
       if (fabs(GenDressedLepton_eta[i]) > 2.500) continue;
       if (iele0_gen != -1 && iele1_gen == -1 && GenDressedLepton_pdgId[iele0_gen] != GenDressedLepton_pdgId[i]) {
         iele1_gen = i;
       }
       if (iele0_gen == -1) {
         iele0_gen = i;
       }
     }

     TLorentzVector ele0_gen;
     TLorentzVector ele1_gen;

     if (iele0_gen != -1) {
       ele0_gen.SetPtEtaPhiM(GenDressedLepton_pt[iele0_gen], GenDressedLepton_eta[iele0_gen], GenDressedLepton_phi[iele0_gen], GenDressedLepton_mass[iele0_gen]);
     }
     if (iele1_gen != -1) {
       ele1_gen.SetPtEtaPhiM(GenDressedLepton_pt[iele1_gen], GenDressedLepton_eta[iele1_gen], GenDressedLepton_phi[iele1_gen], GenDressedLepton_mass[iele1_gen]);
     }

     int imuo0_gen = -1;
     int imuo1_gen = -1;

     for (uint i = 0; i < *nGenDressedLepton; i++) {
       if (fabs(GenDressedLepton_pdgId[i]) != 13) continue;
       if (GenDressedLepton_pt[i] < 15) continue;
       if (fabs(GenDressedLepton_eta[i]) > 2.500) continue;
       if (imuo0_gen != -1 && imuo1_gen == -1 && GenDressedLepton_pdgId[imuo0_gen] != GenDressedLepton_pdgId[i]) {
         imuo1_gen = i;
       }
       if (imuo0_gen == -1) {
         imuo0_gen = i;
       }
     }

     TLorentzVector muo0_gen;
     TLorentzVector muo1_gen;

     if (imuo0_gen != -1) {
       muo0_gen.SetPtEtaPhiM(GenDressedLepton_pt[imuo0_gen], GenDressedLepton_eta[imuo0_gen], GenDressedLepton_phi[imuo0_gen], GenDressedLepton_mass[imuo0_gen]);
     }
     if (imuo1_gen != -1) {
       muo1_gen.SetPtEtaPhiM(GenDressedLepton_pt[imuo1_gen], GenDressedLepton_eta[imuo1_gen], GenDressedLepton_phi[imuo1_gen], GenDressedLepton_mass[imuo1_gen]);
     }

     bool W_ele_sel_gen = false;

     float W_ele0_gen_mt = 0.;

     if (iele0_gen != -1 && iele1_gen == -1 && imuo0_gen == -1 && imuo1_gen == -1) {
       W_ele0_gen_mt = TMath::Sqrt(2. * ele0_gen.Pt() * (*MET_fiducialGenPt) * (1. - TMath::Cos(ele0_gen.Phi() - (*MET_fiducialGenPhi))));
       if (*MET_fiducialGenPt > 0 && W_ele0_gen_mt > 40 && ele0_gen.Pt() > 40) {
         W_ele_sel_gen = true;
       }
     }

     bool W_muo_sel_gen = false;

     float W_muo0_gen_mt = 0.;

     if (imuo0_gen != -1 && imuo1_gen == -1 && iele0_gen == -1 && iele1_gen == -1) {
       W_muo0_gen_mt = TMath::Sqrt(2. * muo0_gen.Pt() * (*MET_fiducialGenPt) * (1. - TMath::Cos(muo0_gen.Phi() - (*MET_fiducialGenPhi))));
       if (*MET_fiducialGenPt > 0 && W_muo0_gen_mt > 40 && muo0_gen.Pt() > 30) {
         W_muo_sel_gen = true;
       }
     }

     bool Z_ele_sel_gen = false;

     float Z_ele0_ele1_gen_m = 0.;

     if (iele0_gen != -1 && iele1_gen != -1) {
       Z_ele0_ele1_gen_m = (ele0_gen + ele1_gen).M();
       if (Z_ele0_ele1_gen_m >= 71. && Z_ele0_ele1_gen_m <= 111. && ele0_gen.Pt() > 25 && ele1_gen.Pt() > 25) {
         Z_ele_sel_gen = true;
       }
     }

     bool Z_muo_sel_gen = false;

     float Z_muo0_muo1_gen_m = 0.;

     if (imuo0_gen != -1 && imuo1_gen != -1) {
       Z_muo0_muo1_gen_m = (muo0_gen + muo1_gen).M();
       if (Z_muo0_muo1_gen_m >= 71. && Z_muo0_muo1_gen_m <= 111. && muo0_gen.Pt() > 25 && muo1_gen.Pt() > 25) {
         Z_muo_sel_gen = true;
       }
     }

     if (W_ele_sel_gen) {
       h_W_ele_gen->Fill(W_ele0_gen_mt);
     }

     if (W_muo_sel_gen) {
       h_W_muo_gen->Fill(W_muo0_gen_mt);
     }

     if (Z_ele_sel_gen) {
       h_Z_ele_gen->Fill(Z_ele0_ele1_gen_m);
     }

     if (Z_muo_sel_gen) {
       h_Z_muo_gen->Fill(Z_muo0_muo1_gen_m);
     }

     int n_photons_gen = 0;
     int ipho0_gen = -1;
     int ipho1_gen = -1;

     for (uint i = 0; i < *nGenPart; i++) {
       if (GenPart_status[i] != 1) continue;
       if (fabs(GenPart_pdgId[i]) != 22) continue;
       if ((GenPart_statusFlags[i] & 1) == 0) continue;
       if (GenPart_pt[i] < 10) continue;
       if (fabs(GenPart_eta[i]) > 2.500) continue;

       if (ipho0_gen != -1 && ipho1_gen == -1) {
         ipho1_gen = i;
         TLorentzVector tmp_pho1_gen;
         tmp_pho1_gen.SetPtEtaPhiM(GenPart_pt[ipho1_gen], GenPart_eta[ipho1_gen], GenPart_phi[ipho1_gen], GenPart_mass[ipho1_gen]);
         if (iele0_gen != -1) {
           if (tmp_pho1_gen.DeltaR(ele0_gen) < 0.4) {
             ipho1_gen = -1;
             continue;
           }
         }
         if (iele1_gen != -1) {
           if (tmp_pho1_gen.DeltaR(ele1_gen) < 0.4) {
             ipho1_gen = -1;
             continue;
           }
         }
         if (imuo0_gen != -1) {
           if (tmp_pho1_gen.DeltaR(muo0_gen) < 0.4) {
             ipho1_gen = -1;
             continue;
           }
         }
         if (imuo1_gen != -1) {
           if (tmp_pho1_gen.DeltaR(muo1_gen) < 0.4) {
             ipho1_gen = -1;
             continue;
           }
         }
         TLorentzVector tmp_pho0_gen;
         tmp_pho0_gen.SetPtEtaPhiM(GenPart_pt[ipho0_gen], GenPart_eta[ipho0_gen], GenPart_phi[ipho0_gen], GenPart_mass[ipho0_gen]);
         if (tmp_pho1_gen.DeltaR(tmp_pho0_gen) < 0.4) {
           ipho1_gen = -1;
           continue;
         }
       }
       if (ipho0_gen == -1) {
         ipho0_gen = i;
         TLorentzVector tmp_pho0_gen;
         tmp_pho0_gen.SetPtEtaPhiM(GenPart_pt[ipho0_gen], GenPart_eta[ipho0_gen], GenPart_phi[ipho0_gen], GenPart_mass[ipho0_gen]);
         if (iele0_gen != -1) {
           if (tmp_pho0_gen.DeltaR(ele0_gen) < 0.4) {
             ipho0_gen = -1;
             continue;
           }
         }
         if (iele1_gen != -1) {
           if (tmp_pho0_gen.DeltaR(ele1_gen) < 0.4) {
             ipho0_gen = -1;
             continue;
           }
         }
         if (imuo0_gen != -1) {
           if (tmp_pho0_gen.DeltaR(muo0_gen) < 0.4) {
             ipho0_gen = -1;
             continue;
           }
         }
         if (imuo1_gen != -1) {
           if (tmp_pho0_gen.DeltaR(muo1_gen) < 0.4) {
             ipho0_gen = -1;
             continue;
           }
         }
       }
       n_photons_gen++;
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

   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   h_nevt->Fill(2.5, weight_gen);

   if (*Flag_goodVertices == 0) return kTRUE;
   if (*Flag_METFilters == 0) return kTRUE;

   h_nevt->Fill(3.5, weight_gen);

   float weight_pu_ele = 1.;
   float weight_pu_muo = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   weight_pu_ele = getWeight(pu_ele_weights, *Pileup_nTrueInt, 0);
   weight_pu_muo = getWeight(pu_muo_weights, *Pileup_nTrueInt, 0);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

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
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
       if (Electron_pfRelIso03_all[i] > 0.0361) continue;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
       if (Electron_pfRelIso03_all[i] > 0.0361) continue;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       if (Electron_pfRelIso03_all[i] > 0.0287 + 0.506/Electron_pt[i]) continue;
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     }
     if (fabs(Electron_eta[i]) > 1.566 && fabs(Electron_eta[i]) < 2.400) {
       if (fabs(Electron_dxy[i]) > 0.10) continue;
       if (fabs(Electron_dz[i]) > 0.20) continue;
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
       if (Electron_pfRelIso03_all[i] > 0.094) continue;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
       if (Electron_pfRelIso03_all[i] > 0.094) continue;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       if (Electron_pfRelIso03_all[i] > 0.0445 + 0.963/Electron_pt[i]) continue;
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     }

     if (Electron_mvaID_WP80[i] == 0) continue;

     bool ele_trg = false;

     for (uint j = 0; j < *nTrigObj; j++) {
       TLorentzVector tmp_sel;
       TLorentzVector tmp_trg;
       tmp_sel.SetPtEtaPhiM(Electron_pt[i], Electron_eta[i], Electron_phi[i], Electron_mass[i]);
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[j], TrigObj_eta[j], TrigObj_phi[j], Electron_mass[i]);
       if (tmp_sel.DeltaR(tmp_trg) > 0.1) continue;
       for (uint k = 0; k < 32; k++) {
         h_TrigObj->Fill(-1, TrigObj_id[i]);
         if ((TrigObj_filterBits[j] >> k) & 1) h_TrigObj->Fill(k, TrigObj_id[j]);
       }
       if (TrigObj_id[j] != 11) continue;
       if ((TrigObj_filterBits[j] & 0x1) == 0) continue; // 1 = CaloIdL_TrackIdL_IsoVL
       if (((TrigObj_filterBits[j] & 0x2) == 0) && ((TrigObj_filterBits[j] & 0x4) == 0)) continue; // 2 = 1e (WPTight) || 4 = 1e (WPLoose)
       ele_trg = true;
       break;
     }

//     if (ele_trg == 0) continue;

     if (iele0 != -1 && iele1 == -1 && Electron_charge[iele0] != Electron_charge[i]) {
       iele1 = i;
     }
     if (iele0 == -1) {
       iele0 = i;
     }
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
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
       if (Electron_pfRelIso03_all[i] < 0.0361) continue;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
       if (Electron_pfRelIso03_all[i] < 0.0361) continue;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       if (Electron_pfRelIso03_all[i] < 0.0287 + 0.506/Electron_pt[i]) continue;
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     }
     if (fabs(Electron_eta[i]) > 1.566 && fabs(Electron_eta[i]) < 2.400) {
       if (fabs(Electron_dxy[i]) > 0.10) continue;
       if (fabs(Electron_dz[i]) > 0.20) continue;
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
       if (Electron_pfRelIso03_all[i] < 0.094) continue;
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
       if (Electron_pfRelIso03_all[i] < 0.094) continue;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       if (Electron_pfRelIso03_all[i] < 0.0445 + 0.963/Electron_pt[i]) continue;
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     }

     if (Electron_mvaID_WP80[i] == 0) continue;

     if (iele0_qcd != -1 && iele1_qcd == -1 && Electron_charge[iele0_qcd] != Electron_charge[i]) {
       iele1_qcd = i;
     }
     if (iele0_qcd == -1) {
       iele0_qcd = i;
     }
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

     if (fabs(Muon_dxy[i]) > 0.20) continue;
     if (fabs(Muon_dz[i]) > 0.50) continue;

     if (Muon_pfRelIso03_all[i] > 0.15) continue;

     if (Muon_tightId[i] == 0) continue;

     bool muo_trg = false;

     for (uint j = 0; j < *nTrigObj; j++) {
       TLorentzVector tmp_sel;
       TLorentzVector tmp_trg;
       tmp_sel.SetPtEtaPhiM(Muon_pt[i], Muon_eta[i], Muon_phi[i], Muon_mass[i]);
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[j], TrigObj_eta[j], TrigObj_phi[j], Muon_mass[i]);
       if (tmp_sel.DeltaR(tmp_trg) > 0.1) continue;
       for (uint k = 0; k < 32; k++) {
         h_TrigObj->Fill(-1, TrigObj_id[i]);
         if ((TrigObj_filterBits[j] >> k) & 1) h_TrigObj->Fill(k, TrigObj_id[j]);
       }
       if (TrigObj_id[j] != 13) continue;
       if ((TrigObj_filterBits[j] & 0x1) == 0) continue; // 1 = TrkIsoVVL
       muo_trg = true;
       break;
     }

//   if (muo_trg == 0) continue;

     if (imuo0 != -1 && imuo1 == -1 && Muon_charge[imuo0] != Muon_charge[i]) {
       imuo1 = i;
     }
     if (imuo0 == -1) {
       imuo0 = i;
     }
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

     if (fabs(Muon_dxy[i]) > 0.20) continue;
     if (fabs(Muon_dz[i]) > 0.50) continue;

     if (Muon_pfRelIso03_all[i] < 0.15) continue;

     if (Muon_tightId[i] == 0) continue;

     if (imuo0_qcd != -1 && imuo1_qcd == -1 && Muon_charge[imuo0_qcd] != Muon_charge[i]) {
       imuo1_qcd = i;
     }
     if (imuo0_qcd == -1) {
       imuo0_qcd = i;
     }
   }

   TLorentzVector muo0_qcd;
   TLorentzVector muo1_qcd;

   if (imuo0_qcd != -1) {
     muo0_qcd.SetPtEtaPhiM(Muon_pt[imuo0_qcd], Muon_eta[imuo0_qcd], Muon_phi[imuo0_qcd], Muon_mass[imuo0_qcd]);
   }
   if (imuo1_qcd != -1) {
     muo1_qcd.SetPtEtaPhiM(Muon_pt[imuo1_qcd], Muon_eta[imuo1_qcd], Muon_phi[imuo1_qcd], Muon_mass[imuo1_qcd]);
   }

// photons

   int n_photons = 0;
   int ipho0 = -1;
   int ipho1 = -1;

   for (uint i = 0; i < *nPhoton; i++) {
     if (Photon_pt[i] < 20) continue;
     if (fabs(Photon_eta[i]) > 1.442 && fabs(Photon_eta[i]) < 1.566) continue;
     if (fabs(Photon_eta[i]) > 2.400) continue;

     if (Photon_pfRelIso03_all[i] > 0.15) continue;

     if (Photon_mvaID_WP80[i] == 0) continue;
     if (Photon_electronVeto[i] == 0) continue;

     if (ipho0 != -1 && ipho1 == -1) {
       ipho1 = i;
       TLorentzVector tmp_pho1;
       tmp_pho1.SetPtEtaPhiM(Photon_pt[ipho1], Photon_eta[ipho1], Photon_phi[ipho1], Photon_mass[ipho1]);
       if (iele0 != -1) {
         if (tmp_pho1.DeltaR(ele0) < 0.4 || fabs((ele0+tmp_pho1).M()-91.2) < 5) {
           ipho1 = -1;
           continue;
         }
       }
       if (iele1 != -1) {
         if (tmp_pho1.DeltaR(ele1) < 0.4 || fabs((ele1+tmp_pho1).M()-91.2) < 5) {
           ipho1 = -1;
           continue;
         }
       }
       if (imuo0 != -1) {
         if (tmp_pho1.DeltaR(muo0) < 0.4) {
           ipho1 = -1;
           continue;
         }
       }
       if (imuo1 != -1) {
         if (tmp_pho1.DeltaR(muo1) < 0.4) {
           ipho1 = -1;
           continue;
         }
       }
       TLorentzVector tmp_pho0;
       tmp_pho0.SetPtEtaPhiM(Photon_pt[ipho0], Photon_eta[ipho0], Photon_phi[ipho0], Photon_mass[ipho0]);
       if (tmp_pho1.DeltaR(tmp_pho0) < 0.4 || fabs((ele0+tmp_pho0+tmp_pho1).M()-91.2) < 5 || fabs((ele1+tmp_pho0+tmp_pho1).M()-91.2) < 5) {
         ipho1 = -1;
         continue;
       }
     }
     if (ipho0 == -1) {
       ipho0 = i;
       TLorentzVector tmp_pho0;
       tmp_pho0.SetPtEtaPhiM(Photon_pt[ipho0], Photon_eta[ipho0], Photon_phi[ipho0], Photon_mass[ipho0]);
       if (iele0 != -1) {
         if (tmp_pho0.DeltaR(ele0) < 0.4 || fabs((ele0+tmp_pho0).M()-91.2) < 5) {
           ipho0 = -1;
           continue;
         }
       }
       if (iele1 != -1) {
         if (tmp_pho0.DeltaR(ele1) < 0.4 || fabs((ele1+tmp_pho0).M()-91.2) < 5) {
           ipho0 = -1;
           continue;
         }
       }
       if (imuo0 != -1) {
         if (tmp_pho0.DeltaR(muo0) < 0.4) {
           ipho0 = -1;
           continue;
         }
       }
       if (imuo1 != -1) {
         if (tmp_pho0.DeltaR(muo1) < 0.4) {
           ipho0 = -1;
           continue;
         }
       }
     }
     n_photons++;
   }

   TLorentzVector pho0;
   TLorentzVector pho1;

   if (ipho0 != -1) {
     pho0.SetPtEtaPhiM(Photon_pt[ipho0], Photon_eta[ipho0], Photon_phi[ipho0], Photon_mass[ipho0]);
   }
   if (ipho1 != -1) {
     pho1.SetPtEtaPhiM(Photon_pt[ipho1], Photon_eta[ipho1], Photon_phi[ipho1], Photon_mass[ipho1]);
   }

// jets & MET

   int n_jets = 0;
   int ijet0 = -1;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   float met_px = *MET_pt * TMath::Cos(*MET_phi);
   float met_py = *MET_pt * TMath::Sin(*MET_phi);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   for (uint i = 0; i < *nJet; i++) {

     if (iele0 != -1 && (uint)Electron_jetIdx[iele0] == i) continue;
     if (iele1 != -1 && (uint)Electron_jetIdx[iele1] == i) continue;
     if (imuo0 != -1 && (uint)Muon_jetIdx[imuo0] == i) continue;
     if (imuo1 != -1 && (uint)Muon_jetIdx[imuo1] == i) continue;
     if (ipho0 != -1 && (uint)Photon_jetIdx[ipho0] == i) continue;
     if (ipho1 != -1 && (uint)Photon_jetIdx[ipho1] == i) continue;

#if defined(mainSelectorMC16_cxx)
// MC jets smearing not needed
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
     JME::JetParameters jer_parameters;
     jer_parameters.setJetPt(Jet_pt[i]);
     jer_parameters.setJetEta(Jet_eta[i]);
     jer_parameters.setRho(*fixedGridRhoFastjetAll);

     bool jet_match = false;
     if (Jet_genJetIdx[i] >= 0 && (uint)Jet_genJetIdx[i] < *nGenJet) {
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
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
// MC jets smearing not needed
#endif // defined(mainSelectorMC18_cxx)

     if (Jet_pt[i] < 30) continue;
     if (fabs(Jet_eta[i]) > 2.400) continue;

     if (ijet0 == -1) {
       ijet0 = i;
     }

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

// W -> ele nu

   bool W_ele_sel = false;
   bool W_ele_sel_wide = false;

   float W_ele0_mt = 0.;

   if (iele0 != -1 && iele1 == -1 && imuo0 == -1 && imuo1 == -1) {
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

// W -> ele nu QCD

   bool W_ele_sel_qcd = false;
   bool W_ele_sel_wide_qcd = false;

   float W_ele0_mt_qcd = 0.;

   if (iele0_qcd != -1 && iele1_qcd == -1 && imuo0_qcd == -1 && imuo1_qcd == -1) {
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

   if (imuo0 != -1 && imuo1 == -1 && iele0 == -1 && iele1 == -1) {
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

// W -> muo nu QCD

   bool W_muo_sel_qcd = false;
   bool W_muo_sel_wide_qcd = false;

   float W_muo0_mt_qcd = 0.;

   if (imuo0_qcd != -1 && imuo1_qcd == -1 && iele0_qcd == -1 && iele1_qcd == -1) {
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
       if (Z_ele0_ele1_m >= 71. && Z_ele0_ele1_m <= 111. && ele0.Pt() > 25 && ele1.Pt() > 25) {
         Z_ele_sel = true;
       }
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
       if (Z_ele0_ele1_m_qcd >= 71. && Z_ele0_ele1_m_qcd <= 111. && ele0_qcd.Pt() > 25 && ele1_qcd.Pt() > 25) {
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
       if (Z_muo0_muo1_m >= 71. && Z_muo0_muo1_m <= 111. && muo0.Pt() > 25 && muo1.Pt() > 25) {
         Z_muo_sel = true;
       }
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
       if (Z_muo0_muo1_m_qcd >= 71. && Z_muo0_muo1_m_qcd <= 111. && muo0_qcd.Pt() > 25 && muo1_qcd.Pt() > 25) {
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

// muon(s) scale factors

   float weight_id_muo0 = 1.;
   float weight_iso_muo0 = 1.;

   float weight_id_muo1 =  1.;
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

// photon(s) scale factors

   float weight_eff_pho0 = 1.;
   float weight_reco_pho0 = 1.;

   float weight_eff_pho1 = 1.;
   float weight_reco_pho1 = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0 != -1) {
     weight_eff_pho0 = getWeight(sf_pho_eff, Photon_eta[ipho0], Photon_pt[ipho0]);
// FIXME
//     weight_reco_pho0 = getWeight(sf_pho_reco, Photon_eta[ipho0], Photon_pt[ipho0]);
// FIXME
   }
   if (ipho1 != -1) {
     weight_eff_pho1 = getWeight(sf_pho_eff, Photon_eta[ipho1], Photon_pt[ipho1]);
// FIXME
//     weight_reco_pho1 = getWeight(sf_pho_reco, Photon_eta[ipho1], Photon_pt[ipho1]);
// FIXME
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0 = weight_eff_pho0 * weight_reco_pho0;
   float weight_pho1 = weight_eff_pho1 * weight_reco_pho1;

// W scale factors

   float weight_W_ele = weight_gen * weight_pu_ele * weight_eff_ele0 * weight_reco_ele0 * weight_hlt_ele;
   float weight_W_muo = weight_gen * weight_pu_muo * weight_id_muo0 * weight_iso_muo0;

// Z scale factors

   float weight_Z_ele = weight_gen * weight_pu_ele * weight_eff_ele0 * weight_eff_ele1 * weight_reco_ele0 * weight_reco_ele1 * weight_hlt_ele;
   float weight_Z_muo = weight_gen * weight_pu_muo * weight_id_muo0 * weight_id_muo1 * weight_iso_muo0 * weight_iso_muo1;

// W plots

   if (W_ele_sel_wide) {
     h_W_ele->Fill(W_ele0_mt, weight_W_ele);
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
     h_W_ele_met_pt->Fill(*MET_pt, weight_W_ele);
     h_W_ele_met_phi->Fill(*MET_phi, weight_W_ele);
     h_W_ele_met_sign->Fill(*MET_significance, weight_W_ele);
   }

   if (W_ele_sel_wide_qcd) {
     QCD(h_W_ele)->Fill(W_ele0_mt_qcd, weight_pu_ele);
   }

   if (W_ele_sel_qcd) {
     QCD(h_W_ele_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_W_ele_npvs_w)->Fill(*PV_npvsGood, weight_pu_ele);
     QCD(h_W_ele0_pt)->Fill(Electron_pt[iele0_qcd], weight_pu_ele);
     QCD(h_W_ele0_eta)->Fill(Electron_eta[iele0_qcd], weight_pu_ele);
     QCD(h_W_ele0_phi)->Fill(Electron_phi[iele0_qcd], weight_pu_ele);
     QCD(h_W_ele0_r9)->Fill(Electron_r9[iele0_qcd], weight_pu_ele);
     QCD(h_W_ele0_sieie)->Fill(Electron_sieie[iele0_qcd], weight_pu_ele);
     QCD(h_W_ele0_mva)->Fill(Electron_mvaID[iele0_qcd], weight_pu_ele);
     QCD(h_W_ele0_pf_iso_all)->Fill(Electron_pfRelIso03_all[iele0_qcd], weight_pu_ele);
     QCD(h_W_ele0_pf_iso_chg)->Fill(Electron_pfRelIso03_chg[iele0_qcd], weight_pu_ele);
     QCD(h_W_ele_met_pt)->Fill(*MET_pt, weight_pu_ele);
     QCD(h_W_ele_met_phi)->Fill(*MET_phi, weight_pu_ele);
     QCD(h_W_ele_met_sign)->Fill(*MET_significance, weight_pu_ele);
   }

   if (W_muo_sel_wide) {
     h_W_muo->Fill(W_muo0_mt, weight_W_muo);
   }

   if (W_muo_sel) {
     h_W_muo_npvs->Fill(*PV_npvsGood, weight_gen);
     h_W_muo_npvs_w->Fill(*PV_npvsGood, weight_W_muo);
     h_W_muo0_pt->Fill(Muon_pt[imuo0], weight_W_muo);
     h_W_muo0_eta->Fill(Muon_eta[imuo0], weight_W_muo);
     h_W_muo0_phi->Fill(Muon_phi[imuo0], weight_W_muo);
     h_W_muo0_pf_iso_all->Fill(Muon_pfRelIso03_all[imuo0], weight_W_muo);
     h_W_muo0_pf_iso_chg->Fill(Muon_pfRelIso03_chg[imuo0], weight_W_muo);
     h_W_muo_met_pt->Fill(*MET_pt, weight_W_muo);
     h_W_muo_met_phi->Fill(*MET_phi, weight_W_muo);
     h_W_muo_met_sign->Fill(*MET_significance, weight_W_muo);
   }

   if (W_muo_sel_wide_qcd) {
     QCD(h_W_muo)->Fill(W_muo0_mt_qcd, weight_pu_muo);
   }

   if (W_muo_sel_qcd) {
     QCD(h_W_muo_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_W_muo_npvs_w)->Fill(*PV_npvsGood, weight_pu_muo);
     QCD(h_W_muo0_pt)->Fill(Muon_pt[imuo0_qcd], weight_pu_muo);
     QCD(h_W_muo0_eta)->Fill(Muon_eta[imuo0_qcd], weight_pu_muo);
     QCD(h_W_muo0_phi)->Fill(Muon_phi[imuo0_qcd], weight_pu_muo);
     QCD(h_W_muo0_pf_iso_all)->Fill(Muon_pfRelIso03_all[imuo0_qcd], weight_pu_muo);
     QCD(h_W_muo0_pf_iso_chg)->Fill(Muon_pfRelIso03_chg[imuo0_qcd], weight_pu_muo);
     QCD(h_W_muo_met_pt)->Fill(*MET_pt, weight_pu_muo);
     QCD(h_W_muo_met_phi)->Fill(*MET_phi, weight_pu_muo);
     QCD(h_W_muo_met_sign)->Fill(*MET_significance, weight_pu_muo);
   }

// Z plots

   if (Z_ele_sel) {
     h_Z_ele->Fill(Z_ele0_ele1_m, weight_Z_ele);
     h_Z_ele_npvs->Fill(*PV_npvsGood, weight_gen);
     h_Z_ele_npvs_w->Fill(*PV_npvsGood, weight_Z_ele);
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
     h_Z_ele_met_sign->Fill(*MET_significance, weight_Z_ele);
   }

   if (Z_ele_sel_qcd) {
     QCD(h_Z_ele)->Fill(Z_ele0_ele1_m_qcd, weight_pu_ele);
     QCD(h_Z_ele_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_Z_ele_npvs_w)->Fill(*PV_npvsGood, weight_pu_ele);
     QCD(h_Z_ele0_pt)->Fill(Electron_pt[iele0_qcd], weight_pu_ele);
     QCD(h_Z_ele0_eta)->Fill(Electron_eta[iele0_qcd], weight_pu_ele);
     QCD(h_Z_ele0_phi)->Fill(Electron_phi[iele0_qcd], weight_pu_ele);
     QCD(h_Z_ele0_r9)->Fill(Electron_r9[iele0_qcd], weight_pu_ele);
     QCD(h_Z_ele0_sieie)->Fill(Electron_sieie[iele0_qcd], weight_pu_ele);
     QCD(h_Z_ele0_mva)->Fill(Electron_mvaID[iele0_qcd], weight_pu_ele);
     QCD(h_Z_ele1_mva)->Fill(Electron_mvaID[iele1_qcd], weight_pu_ele);
     QCD(h_Z_ele0_pf_iso_all)->Fill(Electron_pfRelIso03_all[iele0_qcd], weight_pu_ele);
     QCD(h_Z_ele0_pf_iso_chg)->Fill(Electron_pfRelIso03_chg[iele0_qcd], weight_pu_ele);
     QCD(h_Z_ele1_pt)->Fill(Electron_pt[iele1_qcd], weight_pu_ele);
     QCD(h_Z_ele1_eta)->Fill(Electron_eta[iele1_qcd], weight_pu_ele);
     QCD(h_Z_ele1_phi)->Fill(Electron_phi[iele1_qcd], weight_pu_ele);
     QCD(h_Z_ele1_r9)->Fill(Electron_r9[iele1_qcd], weight_pu_ele);
     QCD(h_Z_ele1_sieie)->Fill(Electron_sieie[iele1_qcd], weight_pu_ele);
     QCD(h_Z_ele1_pf_iso_all)->Fill(Electron_pfRelIso03_all[iele1_qcd], weight_pu_ele);
     QCD(h_Z_ele1_pf_iso_chg)->Fill(Electron_pfRelIso03_chg[iele1_qcd], weight_pu_ele);
     QCD(h_Z_ele_met_pt)->Fill(*MET_pt, weight_pu_ele);
     QCD(h_Z_ele_met_phi)->Fill(*MET_phi, weight_pu_ele);
     QCD(h_Z_ele_met_sign)->Fill(*MET_significance, weight_pu_ele);
   }

   if (Z_muo_sel) {
     h_Z_muo->Fill(Z_muo0_muo1_m, weight_Z_muo);
     h_Z_muo_npvs->Fill(*PV_npvsGood, weight_gen);
     h_Z_muo_npvs_w->Fill(*PV_npvsGood, weight_Z_muo);
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
     h_Z_muo_met_sign->Fill(*MET_significance, weight_Z_muo);
   }

   if (Z_muo_sel_qcd) {
     QCD(h_Z_muo)->Fill(Z_muo0_muo1_m_qcd, weight_pu_muo);
     QCD(h_Z_muo_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_Z_muo_npvs_w)->Fill(*PV_npvsGood, weight_pu_muo);
     QCD(h_Z_muo0_pt)->Fill(Muon_pt[imuo0_qcd], weight_pu_muo);
     QCD(h_Z_muo0_eta)->Fill(Muon_eta[imuo0_qcd], weight_pu_muo);
     QCD(h_Z_muo0_phi)->Fill(Muon_phi[imuo0_qcd], weight_pu_muo);
     QCD(h_Z_muo0_pf_iso_all)->Fill(Muon_pfRelIso03_all[imuo0_qcd], weight_pu_muo);
     QCD(h_Z_muo0_pf_iso_chg)->Fill(Muon_pfRelIso03_chg[imuo0_qcd], weight_pu_muo);
     QCD(h_Z_muo1_pt)->Fill(Muon_pt[imuo1_qcd], weight_pu_muo);
     QCD(h_Z_muo1_eta)->Fill(Muon_eta[imuo1_qcd], weight_pu_muo);
     QCD(h_Z_muo1_phi)->Fill(Muon_phi[imuo1_qcd], weight_pu_muo);
     QCD(h_Z_muo1_pf_iso_all)->Fill(Muon_pfRelIso03_all[imuo1_qcd], weight_pu_muo);
     QCD(h_Z_muo1_pf_iso_chg)->Fill(Muon_pfRelIso03_chg[imuo1_qcd], weight_pu_muo);
     QCD(h_Z_muo_met_pt)->Fill(*MET_pt, weight_pu_muo);
     QCD(h_Z_muo_met_phi)->Fill(*MET_phi, weight_pu_muo);
     QCD(h_Z_muo_met_sign)->Fill(*MET_significance, weight_pu_muo);
   }

// W photon(s) plots

   if (W_ele_sel_wide) {
     if (n_photons >= 1) {
       h_W_ele_pho0->Fill(W_ele0_mt, weight_W_ele * weight_pho0);
     }
   }

   if (W_ele_sel) {
     h_W_ele_nphotons->Fill(n_photons, weight_W_ele);
     if (n_photons >= 1) {
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
     if (n_photons >= 2) {
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
     if (n_photons >= 1) {
       QCD(h_W_ele_pho0)->Fill(W_ele0_mt_qcd, weight_pu_ele * weight_pho0);
     }
   }

   if (W_ele_sel_qcd) {
     QCD(h_W_ele_nphotons)->Fill(n_photons, weight_pu_ele);
     if (n_photons >= 1) {
       QCD(h_W_ele_pho0_pt)->Fill(Photon_pt[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_W_ele_pho0_eta)->Fill(Photon_eta[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_W_ele_pho0_phi)->Fill(Photon_phi[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_W_ele_pho0_r9)->Fill(Photon_r9[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_W_ele_pho0_sieie)->Fill(Photon_sieie[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_W_ele_pho0_mva)->Fill(Photon_mvaID[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_W_ele_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_W_ele_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_W_ele_pho0_dR)->Fill(pho0.DeltaR(ele0_qcd), weight_pu_ele * weight_pho0);
       QCD(h_W_ele_ele0_pho0)->Fill((ele0+pho0).M(), weight_W_ele * weight_pho0);
     }
     if (n_photons >= 2) {
       QCD(h_W_ele_pho1_pt)->Fill(Photon_pt[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_W_ele_pho1_eta)->Fill(Photon_eta[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_W_ele_pho1_phi)->Fill(Photon_phi[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_W_ele_pho1_r9)->Fill(Photon_r9[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_W_ele_pho1_sieie)->Fill(Photon_sieie[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_W_ele_pho1_mva)->Fill(Photon_mvaID[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_W_ele_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_W_ele_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_W_ele_pho1_dR)->Fill(pho1.DeltaR(ele0_qcd), weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_W_ele_pho0_pho1_pt)->Fill((pho0+pho1).Pt(), weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_W_ele_ele0_pho1)->Fill((ele0+pho1).M(), weight_W_ele * weight_pho1);
       QCD(h_W_ele_ele0_pho0_pho1)->Fill((ele0+pho0+pho1).M(), weight_W_ele * weight_pho0 * weight_pho1);
     }
   }

   if (W_muo_sel_wide) {
     if (n_photons >= 1) {
       h_W_muo_pho0->Fill(W_muo0_mt, weight_W_muo * weight_pho0);
     }
   }

   if (W_muo_sel) {
     h_W_muo_nphotons->Fill(n_photons, weight_W_muo);
     if (n_photons >= 1) {
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
     if (n_photons >= 2) {
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
     if (n_photons >= 1) {
       QCD(h_W_muo_pho0)->Fill(W_muo0_mt_qcd, weight_pu_muo * weight_pho0);
     }
   }

   if (W_muo_sel_qcd) {
     QCD(h_W_muo_nphotons)->Fill(n_photons, weight_pu_muo);
     if (n_photons >= 1) {
       QCD(h_W_muo_pho0_pt)->Fill(Photon_pt[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_W_muo_pho0_eta)->Fill(Photon_eta[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_W_muo_pho0_phi)->Fill(Photon_phi[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_W_muo_pho0_r9)->Fill(Photon_r9[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_W_muo_pho0_sieie)->Fill(Photon_sieie[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_W_muo_pho0_mva)->Fill(Photon_mvaID[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_W_muo_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_W_muo_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_W_muo_pho0_dR)->Fill(pho0.DeltaR(muo0_qcd), weight_pu_muo * weight_pho0);
       QCD(h_W_muo_muo0_pho0)->Fill((muo0+pho0).M(), weight_W_muo * weight_pho0);
     }
     if (n_photons >= 2) {
       QCD(h_W_muo_pho1_pt)->Fill(Photon_pt[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_W_muo_pho1_eta)->Fill(Photon_eta[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_W_muo_pho1_phi)->Fill(Photon_phi[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_W_muo_pho1_r9)->Fill(Photon_r9[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_W_muo_pho1_sieie)->Fill(Photon_sieie[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_W_muo_pho1_mva)->Fill(Photon_mvaID[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_W_muo_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_W_muo_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_W_muo_pho1_dR)->Fill(pho1.DeltaR(muo0_qcd), weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_W_muo_pho0_pho1_pt)->Fill((pho0+pho1).Pt(), weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_W_muo_muo0_pho1)->Fill((muo0+pho1).M(), weight_W_muo * weight_pho1);
       QCD(h_W_muo_muo0_pho0_pho1)->Fill((muo0+pho0+pho1).M(), weight_W_muo * weight_pho0 * weight_pho1);
     }
   }

// Z photon(s) plots

   if (Z_ele_sel) {
     h_Z_ele_nphotons->Fill(n_photons, weight_Z_ele);
     if (n_photons >= 1) {
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
     if (n_photons >= 2) {
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
     QCD(h_Z_ele_nphotons)->Fill(n_photons, weight_pu_ele);
     if (n_photons >= 1) {
       QCD(h_Z_ele_pho0_pt)->Fill(Photon_pt[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_Z_ele_pho0_eta)->Fill(Photon_eta[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_Z_ele_pho0_phi)->Fill(Photon_phi[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_Z_ele_pho0_r9)->Fill(Photon_r9[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_Z_ele_pho0_sieie)->Fill(Photon_sieie[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_Z_ele_pho0_mva)->Fill(Photon_mvaID[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_Z_ele_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_Z_ele_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0], weight_pu_ele * weight_pho0);
       QCD(h_Z_ele_pho0_dR)->Fill(TMath::Min(pho0.DeltaR(ele0_qcd), pho0.DeltaR(ele1_qcd)), weight_pu_ele * weight_pho0);
       QCD(h_Z_ele_pho0)->Fill(Z_ele0_ele1_m_qcd, weight_pu_ele * weight_pho0);
       QCD(h_Z_ele_ele0_pho0)->Fill((ele0+pho0).M(), weight_Z_ele * weight_pho0);
       QCD(h_Z_ele_ele1_pho0)->Fill((ele1+pho0).M(), weight_Z_ele * weight_pho0);
     }
     if (n_photons >= 2) {
       QCD(h_Z_ele_pho1_pt)->Fill(Photon_pt[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_pho1_eta)->Fill(Photon_eta[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_pho1_phi)->Fill(Photon_phi[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_pho1_r9)->Fill(Photon_r9[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_pho1_sieie)->Fill(Photon_sieie[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_pho1_mva)->Fill(Photon_mvaID[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1], weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_pho1_dR)->Fill(TMath::Min(pho1.DeltaR(ele0_qcd), pho1.DeltaR(ele1_qcd)), weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_pho0_pho1_pt)->Fill((pho0+pho1).Pt(), weight_pu_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_ele0_pho1)->Fill((ele0+pho1).M(), weight_Z_ele * weight_pho1);
       QCD(h_Z_ele_ele1_pho1)->Fill((ele1+pho1).M(), weight_Z_ele * weight_pho1);
       QCD(h_Z_ele_ele0_pho0_pho1)->Fill((ele0+pho0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_ele1_pho0_pho1)->Fill((ele1+pho0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
       QCD(h_Z_ele_ele0_ele1_pho0_pho1)->Fill((ele0+ele1+pho0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
     }
   }

   if (Z_muo_sel) {
     h_Z_muo_nphotons->Fill(n_photons, weight_Z_muo);
     if (n_photons >= 1) {
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
     if (n_photons >= 2) {
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
     QCD(h_Z_muo_nphotons)->Fill(n_photons, weight_pu_muo);
     if (n_photons >= 1) {
       QCD(h_Z_muo_pho0_pt)->Fill(Photon_pt[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_Z_muo_pho0_eta)->Fill(Photon_eta[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_Z_muo_pho0_phi)->Fill(Photon_phi[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_Z_muo_pho0_r9)->Fill(Photon_r9[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_Z_muo_pho0_sieie)->Fill(Photon_sieie[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_Z_muo_pho0_mva)->Fill(Photon_mvaID[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_Z_muo_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_Z_muo_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0], weight_pu_muo * weight_pho0);
       QCD(h_Z_muo_pho0_dR)->Fill(TMath::Min(pho0.DeltaR(muo0_qcd), pho0.DeltaR(muo1_qcd)), weight_pu_muo * weight_pho0);
       QCD(h_Z_muo_pho0)->Fill(Z_muo0_muo1_m_qcd, weight_pu_muo * weight_pho0);
       QCD(h_Z_muo_muo0_pho0)->Fill((muo0+pho0).M(), weight_Z_muo * weight_pho0);
       QCD(h_Z_muo_muo1_pho0)->Fill((muo1+pho0).M(), weight_Z_muo * weight_pho0);
     }
     if (n_photons >= 2) {
       QCD(h_Z_muo_pho1_pt)->Fill(Photon_pt[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_pho1_eta)->Fill(Photon_eta[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_pho1_phi)->Fill(Photon_phi[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_pho1_r9)->Fill(Photon_r9[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_pho1_sieie)->Fill(Photon_sieie[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_pho1_mva)->Fill(Photon_mvaID[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1], weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_pho1_dR)->Fill(TMath::Min(pho1.DeltaR(muo0_qcd), pho1.DeltaR(muo1_qcd)), weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_pho0_pho1_pt)->Fill((pho0+pho1).Pt(), weight_pu_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_muo0_pho1)->Fill((muo0+pho1).M(), weight_Z_muo * weight_pho1);
       QCD(h_Z_muo_muo1_pho1)->Fill((muo1+pho1).M(), weight_Z_muo * weight_pho1);
       QCD(h_Z_muo_muo0_pho0_pho1)->Fill((muo0+pho0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_muo1_pho0_pho1)->Fill((muo1+pho0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
       QCD(h_Z_muo_muo0_muo1_pho0_pho1)->Fill((muo0+muo1+pho0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
     }
   }

// W jet(s) plots

   if (W_ele_sel) {
     h_W_ele_njets->Fill(n_jets, weight_W_ele);
     if (n_jets >= 1) {
       h_W_ele_jet0_pt->Fill(Jet_pt[ijet0], weight_W_ele);
       h_W_ele_jet0_eta->Fill(Jet_eta[ijet0], weight_W_ele);
       h_W_ele_jet0_phi->Fill(Jet_phi[ijet0], weight_W_ele);
     }
   }

   if (W_ele_sel_qcd) {
     QCD(h_W_ele_njets)->Fill(n_jets, weight_pu_ele);
     if (n_jets >= 1) {
       QCD(h_W_ele_jet0_pt)->Fill(Jet_pt[ijet0], weight_pu_ele);
       QCD(h_W_ele_jet0_eta)->Fill(Jet_eta[ijet0], weight_pu_ele);
       QCD(h_W_ele_jet0_phi)->Fill(Jet_phi[ijet0], weight_pu_ele);
     }
   }

   if (W_muo_sel) {
     h_W_muo_njets->Fill(n_jets, weight_W_muo);
     if (n_jets >= 1) {
       h_W_muo_jet0_pt->Fill(Jet_pt[ijet0], weight_W_muo);
       h_W_muo_jet0_eta->Fill(Jet_eta[ijet0], weight_W_muo);
       h_W_muo_jet0_phi->Fill(Jet_phi[ijet0], weight_W_muo);
     }
   }

   if (W_muo_sel_qcd) {
     QCD(h_W_muo_njets)->Fill(n_jets, weight_pu_muo);
     if (n_jets >= 1) {
       QCD(h_W_muo_jet0_pt)->Fill(Jet_pt[ijet0], weight_pu_muo);
       QCD(h_W_muo_jet0_eta)->Fill(Jet_eta[ijet0], weight_pu_muo);
       QCD(h_W_muo_jet0_phi)->Fill(Jet_phi[ijet0], weight_pu_muo);
     }
   }

// Z jet(s) plots

   if (Z_ele_sel) {
     h_Z_ele_njets->Fill(n_jets, weight_Z_ele);
     if (n_jets >= 1) {
       h_Z_ele_jet0_pt->Fill(Jet_pt[ijet0], weight_Z_ele);
       h_Z_ele_jet0_eta->Fill(Jet_eta[ijet0], weight_Z_ele);
       h_Z_ele_jet0_phi->Fill(Jet_phi[ijet0], weight_Z_ele);
     }
   }

   if (Z_ele_sel_qcd) {
     QCD(h_Z_ele_njets)->Fill(n_jets, weight_pu_ele);
     if (n_jets >= 1) {
       QCD(h_Z_ele_jet0_pt)->Fill(Jet_pt[ijet0], weight_pu_ele);
       QCD(h_Z_ele_jet0_eta)->Fill(Jet_eta[ijet0], weight_pu_ele);
       QCD(h_Z_ele_jet0_phi)->Fill(Jet_phi[ijet0], weight_pu_ele);
     }
   }

   if (Z_muo_sel) {
     h_Z_muo_njets->Fill(n_jets, weight_Z_muo);
     if (n_jets >= 1) {
       h_Z_muo_jet0_pt->Fill(Jet_pt[ijet0], weight_Z_muo);
       h_Z_muo_jet0_eta->Fill(Jet_eta[ijet0], weight_Z_muo);
       h_Z_muo_jet0_phi->Fill(Jet_phi[ijet0], weight_Z_muo);
     }
   }

   if (Z_muo_sel_qcd) {
     QCD(h_Z_muo_njets)->Fill(n_jets, weight_pu_muo);
     if (n_jets >= 1) {
       QCD(h_Z_muo_jet0_pt)->Fill(Jet_pt[ijet0], weight_pu_muo);
       QCD(h_Z_muo_jet0_eta)->Fill(Jet_eta[ijet0], weight_pu_muo);
       QCD(h_Z_muo_jet0_phi)->Fill(Jet_phi[ijet0], weight_pu_muo);
     }
   }

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
