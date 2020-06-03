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

#if defined(__linux__)
#include "roccor.Run2.v3/RoccoR.cc"
#endif // defined(__linux__)

void mainSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   TDatime now;
   Info("Begin", "%s : options = %s", now.AsSQLString(), option.Data());

   if (option.Contains("WJetsToLNu"))                                               isWJetsToLNu = true;
   if (option.Contains("WG") && !option.Contains("WGG") && !option.Contains("WWG")) isWG         = true;
   if (option.Contains("WGG"))                                                      isWGG        = true;
   if (option.Contains("WTauNu"))                                                   isWTauNu     = true;

   if (option.Contains("DYJetsToLL"))                                               isDYJetsToLL = true;
   if (option.Contains("ZG") && !option.Contains("ZGG") && !option.Contains("WZG")) isZG         = true;
   if (option.Contains("ZGG"))                                                      isZGG        = true;
   if (option.Contains("ZTauTau"))                                                  isZTauTau    = true;

   if (option.Contains("ST_t-channel") && !option.Contains("ST_tW"))                isST         = true;
   if (option.Contains("TGJets") && !option.Contains("TTGJets"))                    isTGJets     = true;

   if (option.Contains("TTJets"))                                                   isTTJets     = true;
   if (option.Contains("TTGJets"))                                                  isTTGJets    = true;
   if (option.Contains("TTGG"))                                                     isTTGG       = true;

   if (option.Contains("WW") && !option.Contains("WWG"))                            isWW         = true;
   if (option.Contains("WWG"))                                                      isWWG        = true;

   if (option.Contains("WZ")&& !option.Contains("WZG"))                             isWZ         = true;
   if (option.Contains("WZG"))                                                      isWZG        = true;

   if (fInput && fInput->FindObject("flag")) {
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("reference")) iflag = 0;

     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("pileup_up")) iflag = 10;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("pileup_down")) iflag = 15;

     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jer_up_2016")) iflag = 21;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jer_up_2017")) iflag = 22;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jer_up_2018")) iflag = 23;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jer_down_2016")) iflag = 26;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jer_down_2017")) iflag = 27;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jer_down_2018")) iflag = 28;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jec_up_2016")) iflag = 31;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jec_up_2017")) iflag = 32;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jec_up_2018")) iflag = 33;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jec_down_2016")) iflag = 36;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jec_down_2017")) iflag = 37;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jec_down_2018")) iflag = 38;

     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_ele_eff_up")) iflag = 40;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_ele_eff_down")) iflag = 45;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_ele_reco_up")) iflag = 50;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_ele_reco_down")) iflag = 55;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_ele_trig_up")) iflag = 60;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_ele_trig_down")) iflag = 65;

     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_muo_id_up")) iflag = 70;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_muo_id_down")) iflag = 75;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_muo_iso_up")) iflag = 80;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_muo_iso_down")) iflag = 85;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_muo_trig_up")) iflag = 90;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_muo_trig_down")) iflag = 95;

     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_pho_eff_up")) iflag = 100;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_pho_eff_down")) iflag = 105;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_pho_veto_up_2016")) iflag = 111;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_pho_veto_up_2017")) iflag = 112;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_pho_veto_up_2018")) iflag = 113;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_pho_veto_down_2016")) iflag = 116;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_pho_veto_down_2017")) iflag = 117;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("sf_pho_veto_down_2018")) iflag = 118;

     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("l1prefiring_up")) iflag = 120;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("l1prefiring_down")) iflag = 125;

     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("eg_misid_up")) iflag = 130;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("eg_misid_down")) iflag = 135;

     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("jet_misid_syst")) iflag = 140;

     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("veto_ele_medium")) iflag = 150;
     if (TString(fInput->FindObject("flag")->GetTitle()).Contains("veto_muo_medium")) iflag = 155;

     if (iflag == -1) {
       Error("Begin", "%s : unknown flag = %s", now.AsSQLString(), fInput->FindObject("flag")->GetTitle());
       gSystem->Exit(1);
     }
   }
   if (iflag == -1) {
     Error("Begin", "%s : missing flag", now.AsSQLString());
     gSystem->Exit(1);
   }

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   string pileup_var = "";
   if (iflag == 10) pileup_var = "up_";
   if (iflag == 15) pileup_var = "down_";

#if defined(mainSelectorMC16_cxx)
#if defined(NANOAODv6)
   TFile* file_ele_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2016_SingleElectron_25Oct2019.root").c_str());
   TFile* file_muo_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2016_SingleMuon_25Oct2019.root").c_str());
#endif // defined(NANOAODv6)
#if defined(NANOAODv7)
   TFile* file_ele_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2016_SingleElectron_02Apr2020.root").c_str());
   TFile* file_muo_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2016_SingleMuon_02Apr2020.root").c_str());
#endif // defined(NANOAODv7)
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
#if defined(NANOAODv6)
   TFile* file_ele_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2017_SingleElectron_25Oct2019.root").c_str());
   TFile* file_muo_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2017_SingleMuon_25Oct2019.root").c_str());
#endif // defined(NANOAODv6)
#if defined(NANOAODv7)
   TFile* file_ele_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2017_SingleElectron_02Apr2020.root").c_str());
   TFile* file_muo_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2017_SingleMuon_02Apr2020.root").c_str());
#endif // defined(NANOAODv7)
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
#if defined(NANOAODv6)
   TFile* file_ele_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2018_EGamma_25Oct2019.root").c_str());
   TFile* file_muo_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2018_SingleMuon_25Oct2019.root").c_str());
#endif // defined(NANOAODv6)
#if defined(NANOAODv7)
   TFile* file_ele_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2018_EGamma_02Apr2020.root").c_str());
   TFile* file_muo_pu = new TFile(("root/ratio_pileup_" + pileup_var + "Run2018_SingleMuon_02Apr2020.root").c_str());
#endif // defined(NANOAODv7)
#endif // defined(mainSelectorMC18_cxx)

   pu_ele_weights = (TH1D*)file_ele_pu->Get("pu_weights");
   pu_muo_weights = (TH1D*)file_muo_pu->Get("pu_weights");
   pu_ele_weights->SetDirectory(0);
   pu_muo_weights->SetDirectory(0);

   file_ele_pu->Close();
   file_muo_pu->Close();
   delete file_ele_pu;
   delete file_muo_pu;

   if (fInput && fInput->FindObject("auto_pu")) {
     Info("Begin", "%s : using auto_pu weights", now.AsSQLString());
     delete pu_ele_weights;
     delete pu_muo_weights;
     pu_ele_weights = dynamic_cast<TH1D*>(fInput->FindObject("pu_ele_weights"));
     pu_muo_weights = dynamic_cast<TH1D*>(fInput->FindObject("pu_muo_weights"));
   }

#if defined(mainSelectorMC16_cxx)
   //TFile* file_ele_sf_eff = new TFile("root/sf_ele_2016_LegacyReReco_ElectronMVA80noiso_Fall17V2.root");
   TFile* file_ele_sf_eff = new TFile("root/sf_ele_2016_LegacyReReco_ElectronTight_Fall17V2.root");

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");
   sf_ele_eff->SetDirectory(0);

   file_ele_sf_eff->Close();
   delete file_ele_sf_eff;

   TFile* file_ele_sf_reco = new TFile("root/sf_ele_2016_EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root");

   sf_ele_reco = (TH2D*)file_ele_sf_reco->Get("EGamma_SF2D");
   sf_ele_reco->SetDirectory(0);

   file_ele_sf_reco->Close();
   delete file_ele_sf_reco;

   TFile* file_ele_sf_trig = new TFile("root/sf_ele_2016_trig_v6.root");

   sf_ele_trig = (TH2D*)file_ele_sf_trig->Get("EGamma_SF2D");
   sf_ele_trig->SetDirectory(0);

   file_ele_sf_trig->Close();
   delete file_ele_sf_trig;

   TFile* file_muo_sf_trig_1 = new TFile("root/sf_muo_2016_EfficienciesAndSF_RunBtoF.root");
   TFile* file_muo_sf_trig_2 = new TFile("root/sf_muo_2016_EfficienciesAndSF_Period4.root");

   TH2D* sf_muo_trig_1 = (TH2D*)file_muo_sf_trig_1->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio");
   TH2D* sf_muo_trig_2 = (TH2D*)file_muo_sf_trig_2->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio");
   sf_muo_trig_1->SetDirectory(0);
   sf_muo_trig_2->SetDirectory(0);

   file_muo_sf_trig_1->Close();
   file_muo_sf_trig_2->Close();
   delete file_muo_sf_trig_1;
   delete file_muo_sf_trig_2;

   sf_muo_trig = (TH2D*)sf_muo_trig_1->Clone();
   sf_muo_trig->Reset();
   sf_muo_trig->Add(sf_muo_trig_1, sf_muo_trig_2, 19.69/35.917, 16.227/35.917);
   delete sf_muo_trig_1;
   delete sf_muo_trig_2;

   TFile* file_muo_sf_id_1 = new TFile("root/sf_muo_2016_RunBCDEF_SF_ID.root");
   TFile* file_muo_sf_id_2 = new TFile("root/sf_muo_2016_RunGH_SF_ID.root");

   TH2D* sf_muo_id_1 = (TH2D*)file_muo_sf_id_1->Get("NUM_TightID_DEN_genTracks_eta_pt");
   TH2D* sf_muo_id_2 = (TH2D*)file_muo_sf_id_2->Get("NUM_TightID_DEN_genTracks_eta_pt");
   sf_muo_id_1->SetDirectory(0);
   sf_muo_id_2->SetDirectory(0);

   file_muo_sf_id_1->Close();
   file_muo_sf_id_2->Close();
   delete file_muo_sf_id_1;
   delete file_muo_sf_id_2;

   sf_muo_id = (TH2D*)sf_muo_id_1->Clone();
   sf_muo_id->Reset();
   sf_muo_id->Add(sf_muo_id_1, sf_muo_id_2, 19.69/35.917, 16.227/35.917);
   delete sf_muo_id_1;
   delete sf_muo_id_2;

   TFile* file_muo_sf_iso_1 = new TFile("root/sf_muo_2016_RunBCDEF_SF_ISO.root");
   TFile* file_muo_sf_iso_2 = new TFile("root/sf_muo_2016_RunGH_SF_ISO.root");

   TH2D* sf_muo_iso_1 = (TH2D*)file_muo_sf_iso_1->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");
   TH2D* sf_muo_iso_2 = (TH2D*)file_muo_sf_iso_2->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");
   sf_muo_iso_1->SetDirectory(0);
   sf_muo_iso_2->SetDirectory(0);

   file_muo_sf_iso_1->Close();
   file_muo_sf_iso_2->Close();
   delete file_muo_sf_iso_1;
   delete file_muo_sf_iso_2;

   sf_muo_iso = (TH2D*)sf_muo_iso_1->Clone();
   sf_muo_iso->Reset();
   sf_muo_iso->Add(sf_muo_iso_1, sf_muo_iso_2, 19.69/35.917, 16.227/35.917);
   delete sf_muo_iso_1;
   delete sf_muo_iso_2;

#if defined(NANOAODv6)
// Spring16V2 ID (80X|94X)
   //TFile* file_pho_sf_eff = new TFile("root/sf_pho_2016_LegacyReReco_PhotonMVAWP90.root");
   TFile* file_pho_sf_eff = new TFile("root/sf_pho_2016_LegacyReReco_PhotonCutBasedMedium.root");
#endif // defined(NANOAODv6)

#if defined(NANOAODv7)
#if defined (USE_SPRING16V2_PHOTON_ID)
// Spring16V2 ID (80X|94X)
   //TFile* file_pho_sf_eff = new TFile("root/sf_pho_2016_LegacyReReco_PhotonMVAWP90.root");
   TFile* file_pho_sf_eff = new TFile("root/sf_pho_2016_LegacyReReco_PhotonCutBasedMedium.root");
#else
// Fall17V2 ID (94X)
   //TFile* file_pho_sf_eff = new TFile("root/sf_pho_2016_LegacyReReco_PhotonsMVAwp90_Fall17V2.root");
   TFile* file_pho_sf_eff = new TFile("root/sf_pho_2016_Medium_photons_Fall17V2.root");
#endif // defined (USE_SPRING16V2_PHOTON_ID)
#endif // defined(NANOAODv7)

   sf_pho_eff = (TH2D*)file_pho_sf_eff->Get("EGamma_SF2D");
   sf_pho_eff->SetDirectory(0);

   file_pho_sf_eff->Close();
   delete file_pho_sf_eff;

#if defined(NANOAODv6)
   TFile* file_eg_misid = new TFile("root/sf_eg_misid_2016_v6.root");
#endif // defined(NANOAODv6)

#if defined(NANOAODv7)
#if defined (USE_SPRING16V2_PHOTON_ID)
   TFile* file_eg_misid = new TFile("root/sf_eg_misid_2016_v6.root");
#else
   TFile* file_eg_misid = new TFile("root/sf_eg_misid_2016_v7.root");
#endif // defined (USE_SPRING16V2_PHOTON_ID)
#endif // defined(NANOAODv7)

   sf_eg_misid = (TH2D*)file_eg_misid->Get("EGamma_SF2D");
   sf_eg_misid->SetDirectory(0);

   file_eg_misid->Close();
   delete file_eg_misid;

#if defined(NANOAODv6)
   TFile* file_eg_misid_qcd = new TFile("root/sf_eg_misid_qcd_2016_v6.root");
#endif // defined(NANOAODv6)

#if defined(NANOAODv7)
#if defined (USE_SPRING16V2_PHOTON_ID)
   TFile* file_eg_misid_qcd = new TFile("root/sf_eg_misid_qcd_2016_v6.root");
#else
   TFile* file_eg_misid_qcd = new TFile("root/sf_eg_misid_qcd_2016_v7.root");
#endif // defined (USE_SPRING16V2_PHOTON_ID)
#endif // defined(NANOAODv7)

   sf_eg_misid_qcd = (TH2D*)file_eg_misid_qcd->Get("EGamma_SF2D");
   sf_eg_misid_qcd->SetDirectory(0);

   file_eg_misid_qcd->Close();
   delete file_eg_misid_qcd;
#endif // defined(mainSelectorMC16_cxx)

#if defined(mainSelectorMC17_cxx)
   //TFile* file_ele_sf_eff = new TFile("root/sf_ele_2017_ElectronMVA80noiso_Fall17V2.root");
   TFile* file_ele_sf_eff = new TFile("root/sf_ele_2017_ElectronTight_Fall17V2.root");

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");
   sf_ele_eff->SetDirectory(0);

   file_ele_sf_eff->Close();
   delete file_ele_sf_eff;

   TFile* file_ele_sf_reco = new TFile("root/sf_ele_2017_EGM2D_runBCDEF_passingRECO.root");

   sf_ele_reco = (TH2D*)file_ele_sf_reco->Get("EGamma_SF2D");
   sf_ele_reco->SetDirectory(0);

   file_ele_sf_reco->Close();
   delete file_ele_sf_reco;

   TFile* file_ele_sf_trig = new TFile("root/sf_ele_2017_trig_v6.root");

   sf_ele_trig = (TH2D*)file_ele_sf_trig->Get("EGamma_SF2D");
   sf_ele_trig->SetDirectory(0);

   file_ele_sf_trig->Close();
   delete file_ele_sf_trig;

   TFile* file_muo_sf_trig = new TFile("root/sf_muo_2017_EfficienciesAndSF_RunBtoF_Nov17Nov2017.root");

   sf_muo_trig = (TH2D*)file_muo_sf_trig->Get("IsoMu27_PtEtaBins/pt_abseta_ratio");
   sf_muo_trig->SetDirectory(0);

   file_muo_sf_trig->Close();
   delete file_muo_sf_trig;

   TFile* file_muo_sf_id = new TFile("root/sf_muo_2017_RunBCDEF_SF_ID.root");

   sf_muo_id = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_genTracks_pt_abseta");
   sf_muo_id->SetDirectory(0);

   file_muo_sf_id->Close();
   delete file_muo_sf_id;

   TFile* file_muo_sf_iso = new TFile("root/sf_muo_2017_RunBCDEF_SF_ISO.root");

   sf_muo_iso = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");
   sf_muo_iso->SetDirectory(0);

   file_muo_sf_iso->Close();
   delete file_muo_sf_iso;

   //TFile* file_pho_sf_eff = new TFile("root/sf_pho_2017_PhotonsMVAwp90_Fall17V2.root");
   TFile* file_pho_sf_eff = new TFile("root/sf_pho_2017_PhotonsMedium_Fall17V2.root");

   sf_pho_eff = (TH2D*)file_pho_sf_eff->Get("EGamma_SF2D");
   sf_pho_eff->SetDirectory(0);

   file_pho_sf_eff->Close();
   delete file_pho_sf_eff;

   TFile* file_eg_misid = new TFile("root/sf_eg_misid_2017_v6.root");

   sf_eg_misid = (TH2D*)file_eg_misid->Get("EGamma_SF2D");
   sf_eg_misid->SetDirectory(0);

   file_eg_misid->Close();
   delete file_eg_misid;

   TFile* file_eg_misid_qcd = new TFile("root/sf_eg_misid_qcd_2017_v6.root");

   sf_eg_misid_qcd = (TH2D*)file_eg_misid_qcd->Get("EGamma_SF2D");
   sf_eg_misid_qcd->SetDirectory(0);

   file_eg_misid_qcd->Close();
   delete file_eg_misid_qcd;
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   //TFile* file_ele_sf_eff = new TFile("root/sf_ele_2018_ElectronMVA80noiso_Fall17V2.root");
   TFile* file_ele_sf_eff = new TFile("root/sf_ele_2018_ElectronTight_Fall17V2.root");

   sf_ele_eff = (TH2D*)file_ele_sf_eff->Get("EGamma_SF2D");
   sf_ele_eff->SetDirectory(0);

   file_ele_sf_eff->Close();
   delete file_ele_sf_eff;

   TFile* file_ele_sf_reco = new TFile("root/sf_ele_2018_EGM2D_passingRECO.root");

   sf_ele_reco = (TH2D*)file_ele_sf_reco->Get("EGamma_SF2D");
   sf_ele_reco->SetDirectory(0);

   file_ele_sf_reco->Close();
   delete file_ele_sf_reco;

   TFile* file_ele_sf_trig = new TFile("root/sf_ele_2018_trig_v6.root");

   sf_ele_trig = (TH2D*)file_ele_sf_trig->Get("EGamma_SF2D");
   sf_ele_trig->SetDirectory(0);

   file_ele_sf_trig->Close();
   delete file_ele_sf_trig;

   TFile* file_muo_sf_trig_1 = new TFile("root/sf_muo_2018_EfficienciesAndSF_2018Data_BeforeMuonHLTUpdate.root");
   TFile* file_muo_sf_trig_2 = new TFile("root/sf_muo_2018_EfficienciesAndSF_2018Data_AfterMuonHLTUpdate.root");

   TH2D* sf_muo_trig_1 = (TH2D*)file_muo_sf_trig_1->Get("IsoMu24_PtEtaBins/pt_abseta_ratio");
   TH2D* sf_muo_trig_2 = (TH2D*)file_muo_sf_trig_2->Get("IsoMu24_PtEtaBins/pt_abseta_ratio");
   sf_muo_trig_1->SetDirectory(0);
   sf_muo_trig_2->SetDirectory(0);

   file_muo_sf_trig_1->Close();
   file_muo_sf_trig_2->Close();
   delete file_muo_sf_trig_1;
   delete file_muo_sf_trig_2;

   sf_muo_trig = (TH2D*)sf_muo_trig_1->Clone();
   sf_muo_trig->Reset();
   sf_muo_trig->Add(sf_muo_trig_1, sf_muo_trig_2, 8.958/59.955, 50.997/59.955);
   delete sf_muo_trig_1;
   delete sf_muo_trig_2;

   TFile* file_muo_sf_id = new TFile("root/sf_muo_2018_RunABCD_SF_ID.root");

   sf_muo_id = (TH2D*)file_muo_sf_id->Get("NUM_TightID_DEN_TrackerMuons_pt_abseta");
   sf_muo_id->SetDirectory(0);

   file_muo_sf_id->Close();
   delete file_muo_sf_id;

   TFile* file_muo_sf_iso = new TFile("root/sf_muo_2018_RunABCD_SF_ISO.root");

   sf_muo_iso = (TH2D*)file_muo_sf_iso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");
   sf_muo_iso->SetDirectory(0);

   file_muo_sf_iso->Close();
   delete file_muo_sf_iso;

   //TFile* file_pho_sf_eff = new TFile("root/sf_pho_2018_PhotonsMVAwp90_Fall17V2.root");
   TFile* file_pho_sf_eff = new TFile("root/sf_pho_2018_PhotonsMedium_Fall17V2.root");

   sf_pho_eff = (TH2D*)file_pho_sf_eff->Get("EGamma_SF2D");
   sf_pho_eff->SetDirectory(0);

   file_pho_sf_eff->Close();
   delete file_pho_sf_eff;

   TFile* file_eg_misid = new TFile("root/sf_eg_misid_2018_v6.root");

   sf_eg_misid = (TH2D*)file_eg_misid->Get("EGamma_SF2D");
   sf_eg_misid->SetDirectory(0);

   file_eg_misid->Close();
   delete file_eg_misid;

   TFile* file_eg_misid_qcd = new TFile("root/sf_eg_misid_qcd_2018_v6.root");

   sf_eg_misid_qcd = (TH2D*)file_eg_misid_qcd->Get("EGamma_SF2D");
   sf_eg_misid_qcd->SetDirectory(0);

   file_eg_misid_qcd->Close();
   delete file_eg_misid_qcd;
#endif // defined(mainSelectorMC18_cxx)

#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

#if defined(__linux__)
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
   roccor = new RoccoR("roccor.Run2.v3/RoccoR2016.txt");
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
   roccor = new RoccoR("roccor.Run2.v3/RoccoR2017.txt");
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
   roccor = new RoccoR("roccor.Run2.v3/RoccoR2018.txt");
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)

#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
   if (fInput && fInput->FindObject("era")) {
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2016B")) jet_correction_unc = new JetCorrectionUncertainty("jme/Summer16_07Aug2017BCD_V11_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2016C")) jet_correction_unc = new JetCorrectionUncertainty("jme/Summer16_07Aug2017BCD_V11_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2016D")) jet_correction_unc = new JetCorrectionUncertainty("jme/Summer16_07Aug2017BCD_V11_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2016E")) jet_correction_unc = new JetCorrectionUncertainty("jme/Summer16_07Aug2017EF_V11_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2016F")) jet_correction_unc = new JetCorrectionUncertainty("jme/Summer16_07Aug2017EF_V11_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2016G")) jet_correction_unc = new JetCorrectionUncertainty("jme/Summer16_07Aug2017GH_V11_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2016H")) jet_correction_unc = new JetCorrectionUncertainty("jme/Summer16_07Aug2017GH_V11_DATA_Uncertainty_AK4PFchs.txt");

     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2017B")) jet_correction_unc = new JetCorrectionUncertainty("jme/Fall17_17Nov2017B_V32_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2017C")) jet_correction_unc = new JetCorrectionUncertainty("jme/Fall17_17Nov2017C_V32_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2017D")) jet_correction_unc = new JetCorrectionUncertainty("jme/Fall17_17Nov2017DE_V32_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2017E")) jet_correction_unc = new JetCorrectionUncertainty("jme/Fall17_17Nov2017DE_V32_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2017F")) jet_correction_unc = new JetCorrectionUncertainty("jme/Fall17_17Nov2017F_V32_DATA_Uncertainty_AK4PFchs.txt");

     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2018A")) jet_correction_unc = new JetCorrectionUncertainty("jme/Autumn18_RunA_V19_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2018B")) jet_correction_unc = new JetCorrectionUncertainty("jme/Autumn18_RunB_V19_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2018C")) jet_correction_unc = new JetCorrectionUncertainty("jme/Autumn18_RunC_V19_DATA_Uncertainty_AK4PFchs.txt");
     if (TString(fInput->FindObject("era")->GetTitle()).Contains("2018D")) jet_correction_unc = new JetCorrectionUncertainty("jme/Autumn18_RunD_V19_DATA_Uncertainty_AK4PFchs.txt");
     if (jet_correction_unc == 0) {
       Error("Begin", "%s : unknown era = %s", now.AsSQLString(), fInput->FindObject("era")->GetTitle());
       gSystem->Exit(1);
     }
   }
   if (jet_correction_unc == 0) {
     Error("Begin", "%s : missing era", now.AsSQLString());
     gSystem->Exit(1);
   }
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

#if defined(mainSelectorMC16_cxx)
   jet_resolution = new JME::JetResolution("jme/Summer16_25nsV1_MC_PtResolution_AK4PFchs.txt");
   jet_resolution_sf = new JME::JetResolutionScaleFactor("jme/Summer16_25nsV1_MC_SF_AK4PFchs.txt");
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   jet_resolution = new JME::JetResolution("jme/Fall17_V3_MC_PtResolution_AK4PFchs.txt");
   jet_resolution_sf = new JME::JetResolutionScaleFactor("jme/Fall17_V3_MC_SF_AK4PFchs.txt");
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   jet_resolution = new JME::JetResolution("jme/Autumn18_V7_MC_PtResolution_AK4PFchs.txt");
   jet_resolution_sf = new JME::JetResolutionScaleFactor("jme/Autumn18_V7_MC_SF_AK4PFchs.txt");
#endif // defined(mainSelectorMC18_cxx)
#endif // defined(__linux__)

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

   h_Z_ele = new TH1D("h_Z_ele", "h_Z_ele", 160, 55., 135.);
   h_Z_muo = new TH1D("h_Z_muo", "h_Z_muo", 160, 55., 135.);

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
   h_WG_ele_ele0_pt = new TH1D("h_WG_ele_ele0_pt", "h_WG_ele_ele0_pt", 60, 0., 300.);
   h_WG_ele_pho0_pt = new TH1D("h_WG_ele_pho0_pt", "h_WG_ele_pho0_pt", 60, 0., 300.);
   h_WG_ele_pho0_eta = new TH1D("h_WG_ele_pho0_eta", "h_WG_ele_pho0_eta", 50, -2.5, 2.5);
   h_WG_ele_pho0_phi = new TH1D("h_WG_ele_pho0_phi", "h_WG_ele_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_WG_ele_pho0_r9 = new TH1D("h_WG_ele_pho0_r9", "h_WG_ele_pho0_r9", 50, 0., 5.);
   h_WG_ele_pho0_sieie = new TH1D("h_WG_ele_pho0_sieie", "h_WG_ele_pho0_sieie", 50, 0., 0.05);
   h_WG_ele_pho0_jet0_dR = new TH1D("h_WG_ele_pho0_jet0_dR", "h_WG_ele_pho0_jet0_dR", 50, 0., 5.);
   h_WG_ele_pho0_mva = new TH1D("h_WG_ele_pho0_mva", "h_WG_ele_pho0_mva", 50, -1., 1.);
   h_WG_ele_pho0_pf_iso_all = new TH1D("h_WG_ele_pho0_pf_iso_all", "h_WG_ele_pho0_pf_iso_all", 50, 0.0, 0.2);
   h_WG_ele_pho0_pf_iso_chg = new TH1D("h_WG_ele_pho0_pf_iso_chg", "h_WG_ele_pho0_pf_iso_chg", 50, 0.0, 0.2);
   h_WG_ele_pho0_dR = new TH1D("h_WG_ele_pho0_dR", "h_WG_ele_pho0_dR", 50, 0., 5.);

   h_WG_ele_pho0_pf_iso_all_nocut_eb = new TH1D("h_WG_ele_pho0_pf_iso_all_nocut_eb", "h_WG_ele_pho0_pf_iso_all_nocut_eb", 50, 0.0, 1.);
   h_WG_ele_pho0_pf_iso_all_nocut_ee = new TH1D("h_WG_ele_pho0_pf_iso_all_nocut_ee", "h_WG_ele_pho0_pf_iso_all_nocut_ee", 50, 0.0, 1.);
   h_WG_ele_pho0_sieie_nocut_eb = new TH1D("h_WG_ele_pho0_sieie_nocut_eb", "h_WG_ele_pho0_sieie_nocut_eb", 50, 0., 0.05);
   h_WG_ele_pho0_sieie_nocut_ee = new TH1D("h_WG_ele_pho0_sieie_nocut_ee", "h_WG_ele_pho0_sieie_nocut_ee", 50, 0., 0.05);

   h_WGG_ele_ele0_pt = new TH1D("h_WGG_ele_ele0_pt", "h_WGG_ele_ele0_pt", 15, 0., 300.);
   h_WGG_ele_pho0_pt = new TH1D("h_WGG_ele_pho0_pt", "h_WGG_ele_pho0_pt", 15, 0., 300.);
   h_WGG_ele_pho0_eta = new TH1D("h_WGG_ele_pho0_eta", "h_WGG_ele_pho0_eta", 15, -2.5, 2.5);
   h_WGG_ele_pho0_phi = new TH1D("h_WGG_ele_pho0_phi", "h_WGG_ele_pho0_phi", 12, -TMath::Pi(), TMath::Pi());
   h_WGG_ele_pho0_sieie = new TH1D("h_WGG_ele_pho0_sieie", "h_WGG_ele_pho0_sieie", 25, 0., 0.05);
   h_WGG_ele_pho0_mva = new TH1D("h_WGG_ele_pho0_mva", "h_WGG_ele_pho0_mva", 15, -1., 1.);
   h_WGG_ele_pho1_pt = new TH1D("h_WGG_ele_pho1_pt", "h_WGG_ele_pho1_pt", 15, 0., 300.);
   h_WGG_ele_pho1_eta = new TH1D("h_WGG_ele_pho1_eta", "h_WGG_ele_pho1_eta", 15, -2.5, 2.5);
   h_WGG_ele_pho1_phi = new TH1D("h_WGG_ele_pho1_phi", "h_WGG_ele_pho1_phi", 12, -TMath::Pi(), TMath::Pi());
   h_WGG_ele_pho1_r9 = new TH1D("h_WGG_ele_pho1_r9", "h_WGG_ele_pho1_r9", 25, 0., 5.);
   h_WGG_ele_pho1_sieie = new TH1D("h_WGG_ele_pho1_sieie", "h_WGG_ele_pho1_sieie", 25, 0., 0.05);
   h_WGG_ele_pho1_jet0_dR = new TH1D("h_WGG_ele_pho1_jet0_dR", "h_WGG_ele_pho1_jet0_dR", 15, 0., 5.);
   h_WGG_ele_pho1_mva = new TH1D("h_WGG_ele_pho1_mva", "h_WGG_ele_pho1_mva", 15, -1., 1.);
   h_WGG_ele_pho1_pf_iso_all = new TH1D("h_WGG_ele_pho1_pf_iso_all", "h_WGG_ele_pho1_pf_iso_all", 15, 0.0, 0.2);
   h_WGG_ele_pho1_pf_iso_chg = new TH1D("h_WGG_ele_pho1_pf_iso_chg", "h_WGG_ele_pho1_pf_iso_chg", 15, 0.0, 0.2);
   h_WGG_ele_pho1_dR = new TH1D("h_WGG_ele_pho1_dR", "h_WGG_ele_pho1_dR", 15, 0., 5.);
   h_WGG_ele_pho0_pho1_dR = new TH1D("h_WGG_ele_pho0_pho1_dR", "h_WGG_ele_pho0_pho1_dR", 15, 0., 5.);

   h_W_muo_nphotons = new TH1D("h_W_muo_nphotons", "h_W_muo_nphotons", 6, -0.5, 5.5);
   h_WG_muo_muo0_pt = new TH1D("h_WG_muo_muo0_pt", "h_WG_muo_muo0_pt", 60, 0., 300.);
   h_WG_muo_pho0_pt = new TH1D("h_WG_muo_pho0_pt", "h_WG_muo_pho0_pt", 60, 0., 300.);
   h_WG_muo_pho0_eta = new TH1D("h_WG_muo_pho0_eta", "h_WG_muo_pho0_eta", 50, -2.5, 2.5);
   h_WG_muo_pho0_phi = new TH1D("h_WG_muo_pho0_phi", "h_WG_muo_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_WG_muo_pho0_r9 = new TH1D("h_WG_muo_pho0_r9", "h_WG_muo_pho0_r9", 50, 0., 5.);
   h_WG_muo_pho0_sieie = new TH1D("h_WG_muo_pho0_sieie", "h_WG_muo_pho0_sieie", 50, 0., 0.05);
   h_WG_muo_pho0_jet0_dR = new TH1D("h_WG_muo_pho0_jet0_dR", "h_WG_muo_pho0_jet0_dR", 50, 0., 5.);
   h_WG_muo_pho0_mva = new TH1D("h_WG_muo_pho0_mva", "h_WG_muo_pho0_mva", 50, -1., 1.);
   h_WG_muo_pho0_pf_iso_all = new TH1D("h_WG_muo_pho0_pf_iso_all", "h_WG_muo_pho0_pf_iso_all", 50, 0.0, 0.2);
   h_WG_muo_pho0_pf_iso_chg = new TH1D("h_WG_muo_pho0_pf_iso_chg", "h_WG_muo_pho0_pf_iso_chg", 50, 0.0, 0.2);
   h_WG_muo_pho0_dR = new TH1D("h_WG_muo_pho0_dR", "h_WG_muo_pho0_dR", 50, 0., 5.);

   h_WG_muo_pho0_pf_iso_all_nocut_eb = new TH1D("h_WG_muo_pho0_pf_iso_all_nocut_eb", "h_WG_muo_pho0_pf_iso_all_nocut_eb", 50, 0.0, 1.);
   h_WG_muo_pho0_pf_iso_all_nocut_ee = new TH1D("h_WG_muo_pho0_pf_iso_all_nocut_ee", "h_WG_muo_pho0_pf_iso_all_nocut_ee", 50, 0.0, 1.);
   h_WG_muo_pho0_sieie_nocut_eb = new TH1D("h_WG_muo_pho0_sieie_nocut_eb", "h_WG_muo_pho0_sieie_nocut_eb", 50, 0., 0.05);
   h_WG_muo_pho0_sieie_nocut_ee = new TH1D("h_WG_muo_pho0_sieie_nocut_ee", "h_WG_muo_pho0_sieie_nocut_ee", 50, 0., 0.05);

   h_WGG_muo_muo0_pt = new TH1D("h_WGG_muo_muo0_pt", "h_WGG_muo_muo0_pt", 15, 0., 300.);
   h_WGG_muo_pho0_pt = new TH1D("h_WGG_muo_pho0_pt", "h_WGG_muo_pho0_pt", 15, 0., 300.);
   h_WGG_muo_pho0_eta = new TH1D("h_WGG_muo_pho0_eta", "h_WGG_muo_pho0_eta", 15, -2.5, 2.5);
   h_WGG_muo_pho0_phi = new TH1D("h_WGG_muo_pho0_phi", "h_WGG_muo_pho0_phi", 12, -TMath::Pi(), TMath::Pi());
   h_WGG_muo_pho0_sieie = new TH1D("h_WGG_muo_pho0_sieie", "h_WGG_muo_pho0_sieie", 25, 0., 0.05);
   h_WGG_muo_pho0_mva = new TH1D("h_WGG_muo_pho0_mva", "h_WGG_muo_pho0_mva", 15, -1., 1.);
   h_WGG_muo_pho1_pt = new TH1D("h_WGG_muo_pho1_pt", "h_WGG_muo_pho1_pt", 15, 0., 300.);
   h_WGG_muo_pho1_eta = new TH1D("h_WGG_muo_pho1_eta", "h_WGG_muo_pho1_eta", 15, -2.5, 2.5);
   h_WGG_muo_pho1_phi = new TH1D("h_WGG_muo_pho1_phi", "h_WGG_muo_pho1_phi", 12, -TMath::Pi(), TMath::Pi());
   h_WGG_muo_pho1_r9 = new TH1D("h_WGG_muo_pho1_r9", "h_WGG_muo_pho1_r9", 25, 0., 5.);
   h_WGG_muo_pho1_sieie = new TH1D("h_WGG_muo_pho1_sieie", "h_WGG_muo_pho1_sieie", 25, 0., 0.05);
   h_WGG_muo_pho1_jet0_dR = new TH1D("h_WGG_muo_pho1_jet0_dR", "h_WGG_muo_pho1_jet0_dR", 15, 0., 5.);
   h_WGG_muo_pho1_mva = new TH1D("h_WGG_muo_pho1_mva", "h_WGG_muo_pho1_mva", 15, -1., 1.);
   h_WGG_muo_pho1_pf_iso_all = new TH1D("h_WGG_muo_pho1_pf_iso_all", "h_WGG_muo_pho1_pf_iso_all", 15, 0.0, 0.2);
   h_WGG_muo_pho1_pf_iso_chg = new TH1D("h_WGG_muo_pho1_pf_iso_chg", "h_WGG_muo_pho1_pf_iso_chg", 15, 0.0, 0.2);
   h_WGG_muo_pho1_dR = new TH1D("h_WGG_muo_pho1_dR", "h_WGG_muo_pho1_dR", 15, 0., 5.);
   h_WGG_muo_pho0_pho1_dR = new TH1D("h_WGG_muo_pho0_pho1_dR", "h_WGG_muo_pho0_pho1_dR", 15, 0., 5.);

   h_Z_ele_nphotons = new TH1D("h_Z_ele_nphotons", "h_Z_ele_nphotons", 6, -0.5, 5.5);
   h_ZG_ele_ele0_pt = new TH1D("h_ZG_ele_ele0_pt", "h_ZG_ele_ele0_pt", 50, 0., 300.);
   h_ZG_ele_pho0_pt = new TH1D("h_ZG_ele_pho0_pt", "h_ZG_ele_pho0_pt", 60, 0., 300.);
   h_ZG_ele_pho0_eta = new TH1D("h_ZG_ele_pho0_eta", "h_ZG_ele_pho0_eta", 50, -2.5, 2.5);
   h_ZG_ele_pho0_phi = new TH1D("h_ZG_ele_pho0_phi", "h_ZG_ele_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_ZG_ele_pho0_r9 = new TH1D("h_ZG_ele_pho0_r9", "h_ZG_ele_pho0_r9", 50, 0., 5.);
   h_ZG_ele_pho0_sieie = new TH1D("h_ZG_ele_pho0_sieie", "h_ZG_ele_pho0_sieie", 50, 0., 0.05);
   h_ZG_ele_pho0_jet0_dR = new TH1D("h_ZG_ele_pho0_jet0_dR", "h_ZG_ele_pho0_jet0_dR", 50, 0., 5.);
   h_ZG_ele_pho0_mva = new TH1D("h_ZG_ele_pho0_mva", "h_ZG_ele_pho0_mva", 50, -1., 1.);
   h_ZG_ele_pho0_pf_iso_all = new TH1D("h_ZG_ele_pho0_pf_iso_all", "h_ZG_ele_pho0_pf_iso_all", 50, 0.0, 0.4);
   h_ZG_ele_pho0_pf_iso_chg = new TH1D("h_ZG_ele_pho0_pf_iso_chg", "h_ZG_ele_pho0_pf_iso_chg", 50, 0.0, 0.4);
   h_ZG_ele_pho0_dR = new TH1D("h_ZG_ele_pho0_dR", "h_ZG_ele_pho0_dR", 50, 0., 5.);

   h_ZG_ele_pho0_pt_fsr_iso = new TH1D("h_ZG_ele_pho0_pt_fsr_iso", "h_ZG_ele_pho0_pt_fsr_iso", 60, 0., 300.);
   h_ZG_ele_pho0_pt_fsr_noiso = new TH1D("h_ZG_ele_pho0_pt_fsr_noiso", "h_ZG_ele_pho0_pt_fsr_noiso", 60, 0., 300.);

   h_ZG_ele_pho0_pf_iso_all_nocut_eb = new TH1D("h_ZG_ele_pho0_pf_iso_all_nocut_eb", "h_ZG_ele_pho0_pf_iso_all_nocut_eb", 50, 0.0, 1.);
   h_ZG_ele_pho0_pf_iso_all_nocut_ee = new TH1D("h_ZG_ele_pho0_pf_iso_all_nocut_ee", "h_ZG_ele_pho0_pf_iso_all_nocut_ee", 50, 0.0, 1.);
   h_ZG_ele_pho0_sieie_nocut_eb = new TH1D("h_ZG_ele_pho0_sieie_nocut_eb", "h_ZG_ele_pho0_sieie_nocut_eb", 50, 0., 0.05);
   h_ZG_ele_pho0_sieie_nocut_ee = new TH1D("h_ZG_ele_pho0_sieie_nocut_ee", "h_ZG_ele_pho0_sieie_nocut_ee", 50, 0., 0.05);

   h_ZGG_ele_ele0_pt = new TH1D("h_ZGG_ele_ele0_pt", "h_ZGG_ele_ele0_pt", 15, 0., 300.);
   h_ZGG_ele_ele1_pt = new TH1D("h_ZGG_ele_ele1_pt", "h_ZGG_ele_ele1_pt", 15, 0., 300.);
   h_ZGG_ele_pho0_pt = new TH1D("h_ZGG_ele_pho0_pt", "h_ZGG_ele_pho0_pt", 15, 0., 300.);
   h_ZGG_ele_pho0_eta = new TH1D("h_ZGG_ele_pho0_eta", "h_ZGG_ele_pho0_eta", 10, -2.5, 2.5);
   h_ZGG_ele_pho0_phi = new TH1D("h_ZGG_ele_pho0_phi", "h_ZGG_ele_pho0_phi", 12, -TMath::Pi(), TMath::Pi());
   h_ZGG_ele_pho0_sieie = new TH1D("h_ZGG_ele_pho0_sieie", "h_ZGG_ele_pho0_sieie", 25, 0., 0.05);
   h_ZGG_ele_pho0_mva = new TH1D("h_ZGG_ele_pho0_mva", "h_ZGG_ele_pho0_mva", 10, -1., 1.);
   h_ZGG_ele_pho1_pt = new TH1D("h_ZGG_ele_pho1_pt", "h_ZGG_ele_pho1_pt", 15, 0., 300.);
   h_ZGG_ele_pho1_eta = new TH1D("h_ZGG_ele_pho1_eta", "h_ZGG_ele_pho1_eta", 10, -2.5, 2.5);
   h_ZGG_ele_pho1_phi = new TH1D("h_ZGG_ele_pho1_phi", "h_ZGG_ele_pho1_phi", 12, -TMath::Pi(), TMath::Pi());
   h_ZGG_ele_pho1_r9 = new TH1D("h_ZGG_ele_pho1_r9", "h_ZGG_ele_pho1_r9", 25, 0., 5.);
   h_ZGG_ele_pho1_sieie = new TH1D("h_ZGG_ele_pho1_sieie", "h_ZGG_ele_pho1_sieie", 25, 0., 0.05);
   h_ZGG_ele_pho1_jet0_dR = new TH1D("h_ZGG_ele_pho1_jet0_dR", "h_ZGG_ele_pho1_jet0_dR", 10, 0., 5.);
   h_ZGG_ele_pho1_mva = new TH1D("h_ZGG_ele_pho1_mva", "h_ZGG_ele_pho1_mva", 10, -1., 1.);
   h_ZGG_ele_pho1_pf_iso_all = new TH1D("h_ZGG_ele_pho1_pf_iso_all", "h_ZGG_ele_pho1_pf_iso_all", 10, 0.0, 0.4);
   h_ZGG_ele_pho1_pf_iso_chg = new TH1D("h_ZGG_ele_pho1_pf_iso_chg", "h_ZGG_ele_pho1_pf_iso_chg", 10, 0.0, 0.4);
   h_ZGG_ele_pho1_dR = new TH1D("h_ZGG_ele_pho1_dR", "h_ZGG_ele_pho1_dR", 15, 0., 5.);
   h_ZGG_ele_pho0_pho1_dR = new TH1D("h_ZGG_ele_pho0_pho1_dR", "h_ZGG_ele_pho0_pho1_dR", 10, 0., 5.);

   h_Z_muo_nphotons = new TH1D("h_Z_muo_nphotons", "h_Z_muo_nphotons", 6, -0.5, 5.5);
   h_ZG_muo_muo0_pt = new TH1D("h_ZG_muo_muo0_pt", "h_ZG_muo_muo0_pt", 50, 0., 300.);
   h_ZG_muo_pho0_pt = new TH1D("h_ZG_muo_pho0_pt", "h_ZG_muo_pho0_pt", 60, 0., 300.);
   h_ZG_muo_pho0_eta = new TH1D("h_ZG_muo_pho0_eta", "h_ZG_muo_pho0_eta", 50, -2.5, 2.5);
   h_ZG_muo_pho0_phi = new TH1D("h_ZG_muo_pho0_phi", "h_ZG_muo_pho0_phi", 24, -TMath::Pi(), TMath::Pi());
   h_ZG_muo_pho0_r9 = new TH1D("h_ZG_muo_pho0_r9", "h_ZG_muo_pho0_r9", 50, 0., 5.);
   h_ZG_muo_pho0_sieie = new TH1D("h_ZG_muo_pho0_sieie", "h_ZG_muo_pho0_sieie", 50, 0., 0.05);
   h_ZG_muo_pho0_jet0_dR = new TH1D("h_ZG_muo_pho0_jet0_dR", "h_ZG_muo_pho0_jet0_dR", 50, 0., 5.);
   h_ZG_muo_pho0_mva = new TH1D("h_ZG_muo_pho0_mva", "h_ZG_muo_pho0_mva", 50, -1., 1.);
   h_ZG_muo_pho0_pf_iso_all = new TH1D("h_ZG_muo_pho0_pf_iso_all", "h_ZG_muo_pho0_pf_iso_all", 50, 0.0, 0.4);
   h_ZG_muo_pho0_pf_iso_chg = new TH1D("h_ZG_muo_pho0_pf_iso_chg", "h_ZG_muo_pho0_pf_iso_chg", 50, 0.0, 0.4);
   h_ZG_muo_pho0_dR = new TH1D("h_ZG_muo_pho0_dR", "h_ZG_muo_pho0_dR", 50, 0., 5.);

   h_ZG_muo_pho0_pt_fsr_iso = new TH1D("h_ZG_muo_pho0_pt_fsr_iso", "h_ZG_muo_pho0_pt_fsr_iso", 60, 0., 300.);
   h_ZG_muo_pho0_pt_fsr_noiso = new TH1D("h_ZG_muo_pho0_pt_fsr_noiso", "h_ZG_muo_pho0_pt_fsr_noiso", 60, 0., 300.);

   h_ZG_muo_pho0_pf_iso_all_nocut_eb = new TH1D("h_ZG_muo_pho0_pf_iso_all_nocut_eb", "h_ZG_muo_pho0_pf_iso_all_nocut_eb", 50, 0.0, 1.);
   h_ZG_muo_pho0_pf_iso_all_nocut_ee = new TH1D("h_ZG_muo_pho0_pf_iso_all_nocut_ee", "h_ZG_muo_pho0_pf_iso_all_nocut_ee", 50, 0.0, 1.);
   h_ZG_muo_pho0_sieie_nocut_eb = new TH1D("h_ZG_muo_pho0_sieie_nocut_eb", "h_ZG_muo_pho0_sieie_nocut_eb", 50, 0., 0.05);
   h_ZG_muo_pho0_sieie_nocut_ee = new TH1D("h_ZG_muo_pho0_sieie_nocut_ee", "h_ZG_muo_pho0_sieie_nocut_ee", 50, 0., 0.05);

   h_ZGG_muo_muo0_pt = new TH1D("h_ZGG_muo_muo0_pt", "h_ZGG_muo_muo0_pt", 15, 0., 300.);
   h_ZGG_muo_muo1_pt = new TH1D("h_ZGG_muo_muo1_pt", "h_ZGG_muo_muo1_pt", 15, 0., 300.);
   h_ZGG_muo_pho0_pt = new TH1D("h_ZGG_muo_pho0_pt", "h_ZGG_muo_pho0_pt", 15, 0., 300.);
   h_ZGG_muo_pho0_eta = new TH1D("h_ZGG_muo_pho0_eta", "h_ZGG_muo_pho0_eta", 10, -2.5, 2.5);
   h_ZGG_muo_pho0_phi = new TH1D("h_ZGG_muo_pho0_phi", "h_ZGG_muo_pho0_phi", 12, -TMath::Pi(), TMath::Pi());
   h_ZGG_muo_pho0_sieie = new TH1D("h_ZGG_muo_pho0_sieie", "h_ZGG_muo_pho0_sieie", 25, 0., 0.05);
   h_ZGG_muo_pho0_mva = new TH1D("h_ZGG_muo_pho0_mva", "h_ZGG_muo_pho0_mva", 10, -1., 1.);
   h_ZGG_muo_pho1_pt = new TH1D("h_ZGG_muo_pho1_pt", "h_ZGG_muo_pho1_pt", 15, 0., 300.);
   h_ZGG_muo_pho1_eta = new TH1D("h_ZGG_muo_pho1_eta", "h_ZGG_muo_pho1_eta", 10, -2.5, 2.5);
   h_ZGG_muo_pho1_phi = new TH1D("h_ZGG_muo_pho1_phi", "h_ZGG_muo_pho1_phi", 12, -TMath::Pi(), TMath::Pi());
   h_ZGG_muo_pho1_r9 = new TH1D("h_ZGG_muo_pho1_r9", "h_ZGG_muo_pho1_r9", 25, 0., 5.);
   h_ZGG_muo_pho1_sieie = new TH1D("h_ZGG_muo_pho1_sieie", "h_ZGG_muo_pho1_sieie", 25, 0., 0.05);
   h_ZGG_muo_pho1_jet0_dR = new TH1D("h_ZGG_muo_pho1_jet0_dR", "h_ZGG_muo_pho1_jet0_dR", 10, 0., 5.);
   h_ZGG_muo_pho1_mva = new TH1D("h_ZGG_muo_pho1_mva", "h_ZGG_muo_pho1_mva", 10, -1., 1.);
   h_ZGG_muo_pho1_pf_iso_all = new TH1D("h_ZGG_muo_pho1_pf_iso_all", "h_ZGG_muo_pho1_pf_iso_all", 10, 0.0, 0.4);
   h_ZGG_muo_pho1_pf_iso_chg = new TH1D("h_ZGG_muo_pho1_pf_iso_chg", "h_ZGG_muo_pho1_pf_iso_chg", 10, 0.0, 0.4);
   h_ZGG_muo_pho1_dR = new TH1D("h_ZGG_muo_pho1_dR", "h_ZGG_muo_pho1_dR", 15, 0., 5.);
   h_ZGG_muo_pho0_pho1_dR = new TH1D("h_ZGG_muo_pho0_pho1_dR", "h_ZGG_muo_pho0_pho1_dR", 10, 0., 5.);

   h_WG_ele = new TH1D("h_WG_ele", "h_WG_ele", 40, 0., 200.);
   h_WG_muo = new TH1D("h_WG_muo", "h_WG_muo", 40, 0., 200.);
   h_ZG_ele = new TH1D("h_ZG_ele", "h_ZG_ele", 40, 55., 135.);
   h_ZG_muo = new TH1D("h_ZG_muo", "h_ZG_muo", 40, 55., 135.);

   h_WGG_ele = new TH1D("h_WGG_ele", "h_WGG_ele", 10, 0., 200.);
   h_WGG_muo = new TH1D("h_WGG_muo", "h_WGG_muo", 10, 0., 200.);
   h_ZGG_ele = new TH1D("h_ZGG_ele", "h_ZGG_ele", 8, 55., 135.);
   h_ZGG_muo = new TH1D("h_ZGG_muo", "h_ZGG_muo", 8, 55., 135.);

   h_WG_ele_ele0_pho0 = new TH1D("h_WG_ele_ele0_pho0", "h_WG_ele_ele0_pho0", 40, 0., 200.);
   h_WGG_ele_pho0_pho1_pt = new TH1D("h_WGG_ele_pho0_pho1_pt", "h_WGG_ele_pho0_pho1_pt", 15, 0., 300.);
   h_WGG_ele_pho0_pho1 = new TH1D("h_WGG_ele_pho0_pho1", "h_WGG_ele_pho0_pho1", 15, 0., 300.);
   h_WGG_ele_ele0_pho0 = new TH1D("h_WGG_ele_ele0_pho0", "h_WGG_ele_ele0_pho0", 10, 0., 200.);
   h_WGG_ele_ele0_pho1 = new TH1D("h_WGG_ele_ele0_pho1", "h_WGG_ele_ele0_pho1", 10, 0., 200.);
   h_WGG_ele_ele0_pho0_pho1 = new TH1D("h_WGG_ele_ele0_pho0_pho1", "h_WGG_ele_ele0_pho0_pho1", 15, 0., 300.);

   h_WG_ele_ele0_pho0_fake = new TH1D("h_WG_ele_ele0_pho0_fake", "h_WG_ele_ele0_pho0_fake", 40, 71., 111.);

   h_WG_muo_muo0_pho0 = new TH1D("h_WG_muo_muo0_pho0", "h_WG_muo_muo0_pho0", 40, 0., 200.);
   h_WGG_muo_pho0_pho1_pt = new TH1D("h_WGG_muo_pho0_pho1_pt", "h_WGG_muo_pho0_pho1_pt", 15, 0., 300.);
   h_WGG_muo_pho0_pho1 = new TH1D("h_WGG_muo_pho0_pho1", "h_WGG_muo_pho0_pho1", 15, 0., 300.);
   h_WGG_muo_muo0_pho0 = new TH1D("h_WGG_muo_muo0_pho0", "h_WGG_muo_muo0_pho0", 10, 0., 200.);
   h_WGG_muo_muo0_pho1 = new TH1D("h_WGG_muo_muo0_pho1", "h_WGG_muo_muo0_pho1", 10, 0., 200.);
   h_WGG_muo_muo0_pho0_pho1 = new TH1D("h_WGG_muo_muo0_pho0_pho1", "h_WGG_muo_muo0_pho0_pho1", 15, 0., 300.);

   h_WG_muo_muo0_pho0_fake = new TH1D("h_WG_muo_muo0_pho0_fake", "h_WG_muo_muo0_pho0_fake", 40, 71., 111.);

   h_ZG_ele_ele0_pho0 = new TH1D("h_ZG_ele_ele0_pho0", "h_ZG_ele_ele0_pho0", 40, 40., 200.);
   h_ZG_ele_ele1_pho0 = new TH1D("h_ZG_ele_ele1_pho0", "h_ZG_ele_ele1_pho0", 40, 40., 200.);
   h_ZG_ele_ele0_ele1_pho0 = new TH1D("h_ZG_ele_ele0_ele1_pho0", "h_ZG_ele_ele0_ele1_pho0", 35, 60., 200.);
   h_ZGG_ele_pho0_pho1_pt = new TH1D("h_ZGG_ele_pho0_pho1_pt", "h_ZGG_ele_pho0_pho1_pt", 15, 0., 300.);
   h_ZGG_ele_pho0_pho1 = new TH1D("h_ZGG_ele_pho0_pho1", "h_ZGG_ele_pho0_pho1", 15, 0., 300.);
   h_ZGG_ele_ele0_pho1 = new TH1D("h_ZGG_ele_ele0_pho1", "h_ZGG_ele_ele0_pho1", 8, 30., 150.);
   h_ZGG_ele_ele1_pho1 = new TH1D("h_ZGG_ele_ele1_pho1", "h_ZGG_ele_ele1_pho1", 8, 30., 150.);
   h_ZGG_ele_ele0_pho0_pho1 = new TH1D("h_ZGG_ele_ele0_pho0_pho1", "h_ZGG_ele_ele0_pho0_pho1", 7, 60., 200.);
   h_ZGG_ele_ele1_pho0_pho1 = new TH1D("h_ZGG_ele_ele1_pho0_pho1", "h_ZGG_ele_ele1_pho0_pho1", 7, 60., 200.);
   h_ZGG_ele_ele0_ele1_pho0_pho1 = new TH1D("h_ZGG_ele_ele0_ele1_pho0_pho1", "h_ZGG_ele_ele0_ele1_pho0_pho1", 11, 80., 300.);

   h_ZG_muo_muo0_pho0 = new TH1D("h_ZG_muo_muo0_pho0", "h_ZG_muo_muo0_pho0", 40, 40., 200.);
   h_ZG_muo_muo1_pho0 = new TH1D("h_ZG_muo_muo1_pho0", "h_ZG_muo_muo1_pho0", 40, 40., 200.);
   h_ZG_muo_muo0_muo1_pho0 = new TH1D("h_ZG_muo_muo0_muo1_pho0", "h_ZG_muo_muo0_muo1_pho0", 35, 60., 200.);
   h_ZGG_muo_pho0_pho1_pt = new TH1D("h_ZGG_muo_pho0_pho1_pt", "h_ZGG_muo_pho0_pho1_pt", 15, 0., 300.);
   h_ZGG_muo_pho0_pho1 = new TH1D("h_ZGG_muo_pho0_pho1", "h_ZGG_muo_pho0_pho1", 15, 0., 300.);
   h_ZGG_muo_muo0_pho1 = new TH1D("h_ZGG_muo_muo0_pho1", "h_ZGG_muo_muo0_pho1", 8, 30., 150.);
   h_ZGG_muo_muo1_pho1 = new TH1D("h_ZGG_muo_muo1_pho1", "h_ZGG_muo_muo1_pho1", 8, 30., 150.);
   h_ZGG_muo_muo0_pho0_pho1 = new TH1D("h_ZGG_muo_muo0_pho0_pho1", "h_ZGG_muo_muo0_pho0_pho1", 7, 60., 200.);
   h_ZGG_muo_muo1_pho0_pho1 = new TH1D("h_ZGG_muo_muo1_pho0_pho1", "h_ZGG_muo_muo1_pho0_pho1", 7, 60., 200.);
   h_ZGG_muo_muo0_muo1_pho0_pho1 = new TH1D("h_ZGG_muo_muo0_muo1_pho0_pho1", "h_ZGG_muo_muo0_muo1_pho0_pho1", 11, 80., 300.);

   h_W_ele0_trig = new TH1D("h_W_ele0_trig", "h_W_ele0_trig", 32, 0., 32.);

   h_W_muo0_trig = new TH1D("h_W_muo0_trig", "h_W_muo0_trig", 32, 0., 32.);

   h_Z_ele0_trig = new TH1D("h_Z_ele0_trig", "h_Z_ele0_trig", 32, 0., 32.);
   h_Z_ele1_trig = new TH1D("h_Z_ele1_trig", "h_Z_ele1_trig", 32, 0., 32.);

   h_Z_muo0_trig = new TH1D("h_Z_muo0_trig", "h_Z_muo0_trig", 32, 0., 32.);
   h_Z_muo1_trig = new TH1D("h_Z_muo1_trig", "h_Z_muo1_trig", 32, 0., 32.);

   h_WG_ele_pho0_pt_noiso = new TH1D("h_WG_ele_pho0_pt_noiso", "h_WG_ele_pho0_pt_noiso", 60, 0., 300.);
   h_WG_muo_pho0_pt_noiso = new TH1D("h_WG_muo_pho0_pt_noiso", "h_WG_muo_pho0_pt_noiso", 60, 0., 300.);
   h_ZG_ele_pho0_pt_noiso = new TH1D("h_ZG_ele_pho0_pt_noiso", "h_ZG_ele_pho0_pt_noiso", 60, 0., 300.);
   h_ZG_muo_pho0_pt_noiso = new TH1D("h_ZG_muo_pho0_pt_noiso", "h_ZG_muo_pho0_pt_noiso", 60, 0., 300.);

   h_WGG_ele_pho0_pho1_pt_cat0_map = new TH3D("h_WGG_ele_pho0_pho1_pt_cat0_map", "h_WGG_ele_pho0_pho1_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_cat1_map = new TH3D("h_WGG_ele_pho0_pho1_pt_cat1_map", "h_WGG_ele_pho0_pho1_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_cat2_map = new TH3D("h_WGG_ele_pho0_pho1_pt_cat2_map", "h_WGG_ele_pho0_pho1_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_cat3_map = new TH3D("h_WGG_ele_pho0_pho1_pt_cat3_map", "h_WGG_ele_pho0_pho1_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_WGG_muo_pho0_pho1_pt_cat0_map = new TH3D("h_WGG_muo_pho0_pho1_pt_cat0_map", "h_WGG_muo_pho0_pho1_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_cat1_map = new TH3D("h_WGG_muo_pho0_pho1_pt_cat1_map", "h_WGG_muo_pho0_pho1_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_cat2_map = new TH3D("h_WGG_muo_pho0_pho1_pt_cat2_map", "h_WGG_muo_pho0_pho1_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_cat3_map = new TH3D("h_WGG_muo_pho0_pho1_pt_cat3_map", "h_WGG_muo_pho0_pho1_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_ZGG_ele_pho0_pho1_pt_cat0_map = new TH3D("h_ZGG_ele_pho0_pho1_pt_cat0_map", "h_ZGG_ele_pho0_pho1_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_cat1_map = new TH3D("h_ZGG_ele_pho0_pho1_pt_cat1_map", "h_ZGG_ele_pho0_pho1_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_cat2_map = new TH3D("h_ZGG_ele_pho0_pho1_pt_cat2_map", "h_ZGG_ele_pho0_pho1_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_cat3_map = new TH3D("h_ZGG_ele_pho0_pho1_pt_cat3_map", "h_ZGG_ele_pho0_pho1_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_ZGG_muo_pho0_pho1_pt_cat0_map = new TH3D("h_ZGG_muo_pho0_pho1_pt_cat0_map", "h_ZGG_muo_pho0_pho1_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_cat1_map = new TH3D("h_ZGG_muo_pho0_pho1_pt_cat1_map", "h_ZGG_muo_pho0_pho1_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_cat2_map = new TH3D("h_ZGG_muo_pho0_pho1_pt_cat2_map", "h_ZGG_muo_pho0_pho1_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_cat3_map = new TH3D("h_ZGG_muo_pho0_pho1_pt_cat3_map", "h_ZGG_muo_pho0_pho1_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_WGG_ele_pho0_pt_cat0_map = new TH3D("h_WGG_ele_pho0_pt_cat0_map", "h_WGG_ele_pho0_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_cat1_map = new TH3D("h_WGG_ele_pho0_pt_cat1_map", "h_WGG_ele_pho0_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_cat2_map = new TH3D("h_WGG_ele_pho0_pt_cat2_map", "h_WGG_ele_pho0_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_cat3_map = new TH3D("h_WGG_ele_pho0_pt_cat3_map", "h_WGG_ele_pho0_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_WGG_muo_pho0_pt_cat0_map = new TH3D("h_WGG_muo_pho0_pt_cat0_map", "h_WGG_muo_pho0_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_cat1_map = new TH3D("h_WGG_muo_pho0_pt_cat1_map", "h_WGG_muo_pho0_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_cat2_map = new TH3D("h_WGG_muo_pho0_pt_cat2_map", "h_WGG_muo_pho0_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_cat3_map = new TH3D("h_WGG_muo_pho0_pt_cat3_map", "h_WGG_muo_pho0_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_ZGG_ele_pho0_pt_cat0_map = new TH3D("h_ZGG_ele_pho0_pt_cat0_map", "h_ZGG_ele_pho0_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_cat1_map = new TH3D("h_ZGG_ele_pho0_pt_cat1_map", "h_ZGG_ele_pho0_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_cat2_map = new TH3D("h_ZGG_ele_pho0_pt_cat2_map", "h_ZGG_ele_pho0_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_cat3_map = new TH3D("h_ZGG_ele_pho0_pt_cat3_map", "h_ZGG_ele_pho0_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_ZGG_muo_pho0_pt_cat0_map = new TH3D("h_ZGG_muo_pho0_pt_cat0_map", "h_ZGG_muo_pho0_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_cat1_map = new TH3D("h_ZGG_muo_pho0_pt_cat1_map", "h_ZGG_muo_pho0_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_cat2_map = new TH3D("h_ZGG_muo_pho0_pt_cat2_map", "h_ZGG_muo_pho0_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_cat3_map = new TH3D("h_ZGG_muo_pho0_pt_cat3_map", "h_ZGG_muo_pho0_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_WGG_ele_pho1_pt_cat0_map = new TH3D("h_WGG_ele_pho1_pt_cat0_map", "h_WGG_ele_pho1_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_cat1_map = new TH3D("h_WGG_ele_pho1_pt_cat1_map", "h_WGG_ele_pho1_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_cat2_map = new TH3D("h_WGG_ele_pho1_pt_cat2_map", "h_WGG_ele_pho1_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_cat3_map = new TH3D("h_WGG_ele_pho1_pt_cat3_map", "h_WGG_ele_pho1_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_WGG_muo_pho1_pt_cat0_map = new TH3D("h_WGG_muo_pho1_pt_cat0_map", "h_WGG_muo_pho1_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_cat1_map = new TH3D("h_WGG_muo_pho1_pt_cat1_map", "h_WGG_muo_pho1_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_cat2_map = new TH3D("h_WGG_muo_pho1_pt_cat2_map", "h_WGG_muo_pho1_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_cat3_map = new TH3D("h_WGG_muo_pho1_pt_cat3_map", "h_WGG_muo_pho1_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_ZGG_ele_pho1_pt_cat0_map = new TH3D("h_ZGG_ele_pho1_pt_cat0_map", "h_ZGG_ele_pho1_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_cat1_map = new TH3D("h_ZGG_ele_pho1_pt_cat1_map", "h_ZGG_ele_pho1_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_cat2_map = new TH3D("h_ZGG_ele_pho1_pt_cat2_map", "h_ZGG_ele_pho1_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_cat3_map = new TH3D("h_ZGG_ele_pho1_pt_cat3_map", "h_ZGG_ele_pho1_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_ZGG_muo_pho1_pt_cat0_map = new TH3D("h_ZGG_muo_pho1_pt_cat0_map", "h_ZGG_muo_pho1_pt_cat0_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_cat1_map = new TH3D("h_ZGG_muo_pho1_pt_cat1_map", "h_ZGG_muo_pho1_pt_cat1_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_cat2_map = new TH3D("h_ZGG_muo_pho1_pt_cat2_map", "h_ZGG_muo_pho1_pt_cat2_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_cat3_map = new TH3D("h_ZGG_muo_pho1_pt_cat3_map", "h_ZGG_muo_pho1_pt_cat3_map", 60, 0., 300., 60, 0., 300., 15, 0., 300.);

   h_WGG_ele_pho0_pt_cat0 = new TH1D("h_WGG_ele_pho0_pt_cat0", "h_WGG_ele_pho0_pt_cat0", 15, 0., 300.);
   h_WGG_ele_pho0_pt_cat1 = new TH1D("h_WGG_ele_pho0_pt_cat1", "h_WGG_ele_pho0_pt_cat1", 15, 0., 300.);
   h_WGG_ele_pho0_pt_cat2 = new TH1D("h_WGG_ele_pho0_pt_cat2", "h_WGG_ele_pho0_pt_cat2", 15, 0., 300.);
   h_WGG_ele_pho0_pt_cat3 = new TH1D("h_WGG_ele_pho0_pt_cat3", "h_WGG_ele_pho0_pt_cat3", 15, 0., 300.);

   h_WGG_muo_pho0_pt_cat0 = new TH1D("h_WGG_muo_pho0_pt_cat0", "h_WGG_muo_pho0_pt_cat0", 15, 0., 300.);
   h_WGG_muo_pho0_pt_cat1 = new TH1D("h_WGG_muo_pho0_pt_cat1", "h_WGG_muo_pho0_pt_cat1", 15, 0., 300.);
   h_WGG_muo_pho0_pt_cat2 = new TH1D("h_WGG_muo_pho0_pt_cat2", "h_WGG_muo_pho0_pt_cat2", 15, 0., 300.);
   h_WGG_muo_pho0_pt_cat3 = new TH1D("h_WGG_muo_pho0_pt_cat3", "h_WGG_muo_pho0_pt_cat3", 15, 0., 300.);

   h_ZGG_ele_pho0_pt_cat0 = new TH1D("h_ZGG_ele_pho0_pt_cat0", "h_ZGG_ele_pho0_pt_cat0", 15, 0., 300.);
   h_ZGG_ele_pho0_pt_cat1 = new TH1D("h_ZGG_ele_pho0_pt_cat1", "h_ZGG_ele_pho0_pt_cat1", 15, 0., 300.);
   h_ZGG_ele_pho0_pt_cat2 = new TH1D("h_ZGG_ele_pho0_pt_cat2", "h_ZGG_ele_pho0_pt_cat2", 15, 0., 300.);
   h_ZGG_ele_pho0_pt_cat3 = new TH1D("h_ZGG_ele_pho0_pt_cat3", "h_ZGG_ele_pho0_pt_cat3", 15, 0., 300.);

   h_ZGG_muo_pho0_pt_cat0 = new TH1D("h_ZGG_muo_pho0_pt_cat0", "h_ZGG_muo_pho0_pt_cat0", 15, 0., 300.);
   h_ZGG_muo_pho0_pt_cat1 = new TH1D("h_ZGG_muo_pho0_pt_cat1", "h_ZGG_muo_pho0_pt_cat1", 15, 0., 300.);
   h_ZGG_muo_pho0_pt_cat2 = new TH1D("h_ZGG_muo_pho0_pt_cat2", "h_ZGG_muo_pho0_pt_cat2", 15, 0., 300.);
   h_ZGG_muo_pho0_pt_cat3 = new TH1D("h_ZGG_muo_pho0_pt_cat3", "h_ZGG_muo_pho0_pt_cat3", 15, 0., 300.);

   h_WGG_ele_pho1_pt_cat0 = new TH1D("h_WGG_ele_pho1_pt_cat0", "h_WGG_ele_pho1_pt_cat0", 15, 0., 300.);
   h_WGG_ele_pho1_pt_cat1 = new TH1D("h_WGG_ele_pho1_pt_cat1", "h_WGG_ele_pho1_pt_cat1", 15, 0., 300.);
   h_WGG_ele_pho1_pt_cat2 = new TH1D("h_WGG_ele_pho1_pt_cat2", "h_WGG_ele_pho1_pt_cat2", 15, 0., 300.);
   h_WGG_ele_pho1_pt_cat3 = new TH1D("h_WGG_ele_pho1_pt_cat3", "h_WGG_ele_pho1_pt_cat3", 15, 0., 300.);

   h_WGG_muo_pho1_pt_cat0 = new TH1D("h_WGG_muo_pho1_pt_cat0", "h_WGG_muo_pho1_pt_cat0", 15, 0., 300.);
   h_WGG_muo_pho1_pt_cat1 = new TH1D("h_WGG_muo_pho1_pt_cat1", "h_WGG_muo_pho1_pt_cat1", 15, 0., 300.);
   h_WGG_muo_pho1_pt_cat2 = new TH1D("h_WGG_muo_pho1_pt_cat2", "h_WGG_muo_pho1_pt_cat2", 15, 0., 300.);
   h_WGG_muo_pho1_pt_cat3 = new TH1D("h_WGG_muo_pho1_pt_cat3", "h_WGG_muo_pho1_pt_cat3", 15, 0., 300.);

   h_ZGG_ele_pho1_pt_cat0 = new TH1D("h_ZGG_ele_pho1_pt_cat0", "h_ZGG_ele_pho1_pt_cat0", 15, 0., 300.);
   h_ZGG_ele_pho1_pt_cat1 = new TH1D("h_ZGG_ele_pho1_pt_cat1", "h_ZGG_ele_pho1_pt_cat1", 15, 0., 300.);
   h_ZGG_ele_pho1_pt_cat2 = new TH1D("h_ZGG_ele_pho1_pt_cat2", "h_ZGG_ele_pho1_pt_cat2", 15, 0., 300.);
   h_ZGG_ele_pho1_pt_cat3 = new TH1D("h_ZGG_ele_pho1_pt_cat3", "h_ZGG_ele_pho1_pt_cat3", 15, 0., 300.);

   h_ZGG_muo_pho1_pt_cat0 = new TH1D("h_ZGG_muo_pho1_pt_cat0", "h_ZGG_muo_pho1_pt_cat0", 15, 0., 300.);
   h_ZGG_muo_pho1_pt_cat1 = new TH1D("h_ZGG_muo_pho1_pt_cat1", "h_ZGG_muo_pho1_pt_cat1", 15, 0., 300.);
   h_ZGG_muo_pho1_pt_cat2 = new TH1D("h_ZGG_muo_pho1_pt_cat2", "h_ZGG_muo_pho1_pt_cat2", 15, 0., 300.);
   h_ZGG_muo_pho1_pt_cat3 = new TH1D("h_ZGG_muo_pho1_pt_cat3", "h_ZGG_muo_pho1_pt_cat3", 15, 0., 300.);

   h_WG_ele_t = new TH3D("h_WG_ele_t", "h_WG_ele_t", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);
   h_WG_muo_t = new TH3D("h_WG_muo_t", "h_WG_muo_t", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);
   h_ZG_ele_t = new TH3D("h_ZG_ele_t", "h_ZG_ele_t", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);
   h_ZG_muo_t = new TH3D("h_ZG_muo_t", "h_ZG_muo_t", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);

   h_WG_ele_t_genmatch = new TH3D("h_WG_ele_t_genmatch", "h_WG_ele_t_genmatch", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);
   h_WG_muo_t_genmatch = new TH3D("h_WG_muo_t_genmatch", "h_WG_muo_t_genmatch", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);
   h_ZG_ele_t_genmatch = new TH3D("h_ZG_ele_t_genmatch", "h_ZG_ele_t_genmatch", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);
   h_ZG_muo_t_genmatch = new TH3D("h_ZG_muo_t_genmatch", "h_ZG_muo_t_genmatch", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);

   h_WG_ele_t_genmatch2 = new TH3D("h_WG_ele_t_genmatch2", "h_WG_ele_t_genmatch2", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);
   h_WG_muo_t_genmatch2 = new TH3D("h_WG_muo_t_genmatch2", "h_WG_muo_t_genmatch2", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);
   h_ZG_ele_t_genmatch2 = new TH3D("h_ZG_ele_t_genmatch2", "h_ZG_ele_t_genmatch2", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);
   h_ZG_muo_t_genmatch2 = new TH3D("h_ZG_muo_t_genmatch2", "h_ZG_muo_t_genmatch2", 15, 0., 300., 2, -0.5, 1.5, 2, -0.5, 1.5);

   h_WGG_ele_pho0_pho1_pt_bb_tt = new TH3D("h_WGG_ele_pho0_pho1_pt_bb_tt", "h_WGG_ele_pho0_pho1_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_bb_tl = new TH3D("h_WGG_ele_pho0_pho1_pt_bb_tl", "h_WGG_ele_pho0_pho1_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_bb_lt = new TH3D("h_WGG_ele_pho0_pho1_pt_bb_lt", "h_WGG_ele_pho0_pho1_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_bb_ll = new TH3D("h_WGG_ele_pho0_pho1_pt_bb_ll", "h_WGG_ele_pho0_pho1_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_be_tt = new TH3D("h_WGG_ele_pho0_pho1_pt_be_tt", "h_WGG_ele_pho0_pho1_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_be_tl = new TH3D("h_WGG_ele_pho0_pho1_pt_be_tl", "h_WGG_ele_pho0_pho1_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_be_lt = new TH3D("h_WGG_ele_pho0_pho1_pt_be_lt", "h_WGG_ele_pho0_pho1_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_be_ll = new TH3D("h_WGG_ele_pho0_pho1_pt_be_ll", "h_WGG_ele_pho0_pho1_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_eb_tt = new TH3D("h_WGG_ele_pho0_pho1_pt_eb_tt", "h_WGG_ele_pho0_pho1_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_eb_tl = new TH3D("h_WGG_ele_pho0_pho1_pt_eb_tl", "h_WGG_ele_pho0_pho1_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_eb_lt = new TH3D("h_WGG_ele_pho0_pho1_pt_eb_lt", "h_WGG_ele_pho0_pho1_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_eb_ll = new TH3D("h_WGG_ele_pho0_pho1_pt_eb_ll", "h_WGG_ele_pho0_pho1_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_ee_tt = new TH3D("h_WGG_ele_pho0_pho1_pt_ee_tt", "h_WGG_ele_pho0_pho1_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_ee_tl = new TH3D("h_WGG_ele_pho0_pho1_pt_ee_tl", "h_WGG_ele_pho0_pho1_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_ee_lt = new TH3D("h_WGG_ele_pho0_pho1_pt_ee_lt", "h_WGG_ele_pho0_pho1_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_ee_ll = new TH3D("h_WGG_ele_pho0_pho1_pt_ee_ll", "h_WGG_ele_pho0_pho1_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_ele_pho0_pho1_pt_bb_tt_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_bb_tt_genmatch2", "h_WGG_ele_pho0_pho1_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_bb_tl_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_bb_tl_genmatch2", "h_WGG_ele_pho0_pho1_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_bb_lt_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_bb_lt_genmatch2", "h_WGG_ele_pho0_pho1_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_bb_ll_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_bb_ll_genmatch2", "h_WGG_ele_pho0_pho1_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_be_tt_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_be_tt_genmatch2", "h_WGG_ele_pho0_pho1_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_be_tl_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_be_tl_genmatch2", "h_WGG_ele_pho0_pho1_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_be_lt_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_be_lt_genmatch2", "h_WGG_ele_pho0_pho1_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_be_ll_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_be_ll_genmatch2", "h_WGG_ele_pho0_pho1_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_eb_tt_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_eb_tt_genmatch2", "h_WGG_ele_pho0_pho1_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_eb_tl_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_eb_tl_genmatch2", "h_WGG_ele_pho0_pho1_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_eb_lt_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_eb_lt_genmatch2", "h_WGG_ele_pho0_pho1_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_eb_ll_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_eb_ll_genmatch2", "h_WGG_ele_pho0_pho1_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_ee_tt_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_ee_tt_genmatch2", "h_WGG_ele_pho0_pho1_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_ee_tl_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_ee_tl_genmatch2", "h_WGG_ele_pho0_pho1_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_ee_lt_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_ee_lt_genmatch2", "h_WGG_ele_pho0_pho1_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_ee_ll_genmatch2 = new TH3D("h_WGG_ele_pho0_pho1_pt_ee_ll_genmatch2", "h_WGG_ele_pho0_pho1_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_muo_pho0_pho1_pt_bb_tt = new TH3D("h_WGG_muo_pho0_pho1_pt_bb_tt", "h_WGG_muo_pho0_pho1_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_bb_tl = new TH3D("h_WGG_muo_pho0_pho1_pt_bb_tl", "h_WGG_muo_pho0_pho1_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_bb_lt = new TH3D("h_WGG_muo_pho0_pho1_pt_bb_lt", "h_WGG_muo_pho0_pho1_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_bb_ll = new TH3D("h_WGG_muo_pho0_pho1_pt_bb_ll", "h_WGG_muo_pho0_pho1_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_be_tt = new TH3D("h_WGG_muo_pho0_pho1_pt_be_tt", "h_WGG_muo_pho0_pho1_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_be_tl = new TH3D("h_WGG_muo_pho0_pho1_pt_be_tl", "h_WGG_muo_pho0_pho1_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_be_lt = new TH3D("h_WGG_muo_pho0_pho1_pt_be_lt", "h_WGG_muo_pho0_pho1_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_be_ll = new TH3D("h_WGG_muo_pho0_pho1_pt_be_ll", "h_WGG_muo_pho0_pho1_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_eb_tt = new TH3D("h_WGG_muo_pho0_pho1_pt_eb_tt", "h_WGG_muo_pho0_pho1_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_eb_tl = new TH3D("h_WGG_muo_pho0_pho1_pt_eb_tl", "h_WGG_muo_pho0_pho1_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_eb_lt = new TH3D("h_WGG_muo_pho0_pho1_pt_eb_lt", "h_WGG_muo_pho0_pho1_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_eb_ll = new TH3D("h_WGG_muo_pho0_pho1_pt_eb_ll", "h_WGG_muo_pho0_pho1_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_ee_tt = new TH3D("h_WGG_muo_pho0_pho1_pt_ee_tt", "h_WGG_muo_pho0_pho1_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_ee_tl = new TH3D("h_WGG_muo_pho0_pho1_pt_ee_tl", "h_WGG_muo_pho0_pho1_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_ee_lt = new TH3D("h_WGG_muo_pho0_pho1_pt_ee_lt", "h_WGG_muo_pho0_pho1_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_ee_ll = new TH3D("h_WGG_muo_pho0_pho1_pt_ee_ll", "h_WGG_muo_pho0_pho1_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_muo_pho0_pho1_pt_bb_tt_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_bb_tt_genmatch2", "h_WGG_muo_pho0_pho1_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_bb_tl_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_bb_tl_genmatch2", "h_WGG_muo_pho0_pho1_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_bb_lt_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_bb_lt_genmatch2", "h_WGG_muo_pho0_pho1_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_bb_ll_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_bb_ll_genmatch2", "h_WGG_muo_pho0_pho1_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_be_tt_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_be_tt_genmatch2", "h_WGG_muo_pho0_pho1_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_be_tl_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_be_tl_genmatch2", "h_WGG_muo_pho0_pho1_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_be_lt_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_be_lt_genmatch2", "h_WGG_muo_pho0_pho1_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_be_ll_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_be_ll_genmatch2", "h_WGG_muo_pho0_pho1_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_eb_tt_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_eb_tt_genmatch2", "h_WGG_muo_pho0_pho1_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_eb_tl_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_eb_tl_genmatch2", "h_WGG_muo_pho0_pho1_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_eb_lt_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_eb_lt_genmatch2", "h_WGG_muo_pho0_pho1_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_eb_ll_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_eb_ll_genmatch2", "h_WGG_muo_pho0_pho1_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_ee_tt_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_ee_tt_genmatch2", "h_WGG_muo_pho0_pho1_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_ee_tl_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_ee_tl_genmatch2", "h_WGG_muo_pho0_pho1_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_ee_lt_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_ee_lt_genmatch2", "h_WGG_muo_pho0_pho1_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_ee_ll_genmatch2 = new TH3D("h_WGG_muo_pho0_pho1_pt_ee_ll_genmatch2", "h_WGG_muo_pho0_pho1_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_ele_pho0_pho1_pt_bb_tt = new TH3D("h_ZGG_ele_pho0_pho1_pt_bb_tt", "h_ZGG_ele_pho0_pho1_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_bb_tl = new TH3D("h_ZGG_ele_pho0_pho1_pt_bb_tl", "h_ZGG_ele_pho0_pho1_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_bb_lt = new TH3D("h_ZGG_ele_pho0_pho1_pt_bb_lt", "h_ZGG_ele_pho0_pho1_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_bb_ll = new TH3D("h_ZGG_ele_pho0_pho1_pt_bb_ll", "h_ZGG_ele_pho0_pho1_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_be_tt = new TH3D("h_ZGG_ele_pho0_pho1_pt_be_tt", "h_ZGG_ele_pho0_pho1_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_be_tl = new TH3D("h_ZGG_ele_pho0_pho1_pt_be_tl", "h_ZGG_ele_pho0_pho1_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_be_lt = new TH3D("h_ZGG_ele_pho0_pho1_pt_be_lt", "h_ZGG_ele_pho0_pho1_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_be_ll = new TH3D("h_ZGG_ele_pho0_pho1_pt_be_ll", "h_ZGG_ele_pho0_pho1_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_eb_tt = new TH3D("h_ZGG_ele_pho0_pho1_pt_eb_tt", "h_ZGG_ele_pho0_pho1_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_eb_tl = new TH3D("h_ZGG_ele_pho0_pho1_pt_eb_tl", "h_ZGG_ele_pho0_pho1_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_eb_lt = new TH3D("h_ZGG_ele_pho0_pho1_pt_eb_lt", "h_ZGG_ele_pho0_pho1_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_eb_ll = new TH3D("h_ZGG_ele_pho0_pho1_pt_eb_ll", "h_ZGG_ele_pho0_pho1_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_ee_tt = new TH3D("h_ZGG_ele_pho0_pho1_pt_ee_tt", "h_ZGG_ele_pho0_pho1_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_ee_tl = new TH3D("h_ZGG_ele_pho0_pho1_pt_ee_tl", "h_ZGG_ele_pho0_pho1_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_ee_lt = new TH3D("h_ZGG_ele_pho0_pho1_pt_ee_lt", "h_ZGG_ele_pho0_pho1_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_ee_ll = new TH3D("h_ZGG_ele_pho0_pho1_pt_ee_ll", "h_ZGG_ele_pho0_pho1_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_ele_pho0_pho1_pt_bb_tt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_bb_tt_genmatch2", "h_ZGG_ele_pho0_pho1_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_bb_tl_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_bb_tl_genmatch2", "h_ZGG_ele_pho0_pho1_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_bb_lt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_bb_lt_genmatch2", "h_ZGG_ele_pho0_pho1_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_bb_ll_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_bb_ll_genmatch2", "h_ZGG_ele_pho0_pho1_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_be_tt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_be_tt_genmatch2", "h_ZGG_ele_pho0_pho1_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_be_tl_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_be_tl_genmatch2", "h_ZGG_ele_pho0_pho1_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_be_lt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_be_lt_genmatch2", "h_ZGG_ele_pho0_pho1_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_be_ll_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_be_ll_genmatch2", "h_ZGG_ele_pho0_pho1_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_eb_tt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_eb_tt_genmatch2", "h_ZGG_ele_pho0_pho1_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_eb_tl_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_eb_tl_genmatch2", "h_ZGG_ele_pho0_pho1_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_eb_lt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_eb_lt_genmatch2", "h_ZGG_ele_pho0_pho1_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_eb_ll_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_eb_ll_genmatch2", "h_ZGG_ele_pho0_pho1_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_ee_tt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_ee_tt_genmatch2", "h_ZGG_ele_pho0_pho1_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_ee_tl_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_ee_tl_genmatch2", "h_ZGG_ele_pho0_pho1_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_ee_lt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_ee_lt_genmatch2", "h_ZGG_ele_pho0_pho1_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_ee_ll_genmatch2 = new TH3D("h_ZGG_ele_pho0_pho1_pt_ee_ll_genmatch2", "h_ZGG_ele_pho0_pho1_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_muo_pho0_pho1_pt_bb_tt = new TH3D("h_ZGG_muo_pho0_pho1_pt_bb_tt", "h_ZGG_muo_pho0_pho1_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_bb_tl = new TH3D("h_ZGG_muo_pho0_pho1_pt_bb_tl", "h_ZGG_muo_pho0_pho1_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_bb_lt = new TH3D("h_ZGG_muo_pho0_pho1_pt_bb_lt", "h_ZGG_muo_pho0_pho1_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_bb_ll = new TH3D("h_ZGG_muo_pho0_pho1_pt_bb_ll", "h_ZGG_muo_pho0_pho1_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_be_tt = new TH3D("h_ZGG_muo_pho0_pho1_pt_be_tt", "h_ZGG_muo_pho0_pho1_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_be_tl = new TH3D("h_ZGG_muo_pho0_pho1_pt_be_tl", "h_ZGG_muo_pho0_pho1_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_be_lt = new TH3D("h_ZGG_muo_pho0_pho1_pt_be_lt", "h_ZGG_muo_pho0_pho1_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_be_ll = new TH3D("h_ZGG_muo_pho0_pho1_pt_be_ll", "h_ZGG_muo_pho0_pho1_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_eb_tt = new TH3D("h_ZGG_muo_pho0_pho1_pt_eb_tt", "h_ZGG_muo_pho0_pho1_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_eb_tl = new TH3D("h_ZGG_muo_pho0_pho1_pt_eb_tl", "h_ZGG_muo_pho0_pho1_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_eb_lt = new TH3D("h_ZGG_muo_pho0_pho1_pt_eb_lt", "h_ZGG_muo_pho0_pho1_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_eb_ll = new TH3D("h_ZGG_muo_pho0_pho1_pt_eb_ll", "h_ZGG_muo_pho0_pho1_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_ee_tt = new TH3D("h_ZGG_muo_pho0_pho1_pt_ee_tt", "h_ZGG_muo_pho0_pho1_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_ee_tl = new TH3D("h_ZGG_muo_pho0_pho1_pt_ee_tl", "h_ZGG_muo_pho0_pho1_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_ee_lt = new TH3D("h_ZGG_muo_pho0_pho1_pt_ee_lt", "h_ZGG_muo_pho0_pho1_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_ee_ll = new TH3D("h_ZGG_muo_pho0_pho1_pt_ee_ll", "h_ZGG_muo_pho0_pho1_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_muo_pho0_pho1_pt_bb_tt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_bb_tt_genmatch2", "h_ZGG_muo_pho0_pho1_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_bb_tl_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_bb_tl_genmatch2", "h_ZGG_muo_pho0_pho1_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_bb_lt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_bb_lt_genmatch2", "h_ZGG_muo_pho0_pho1_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_bb_ll_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_bb_ll_genmatch2", "h_ZGG_muo_pho0_pho1_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_be_tt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_be_tt_genmatch2", "h_ZGG_muo_pho0_pho1_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_be_tl_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_be_tl_genmatch2", "h_ZGG_muo_pho0_pho1_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_be_lt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_be_lt_genmatch2", "h_ZGG_muo_pho0_pho1_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_be_ll_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_be_ll_genmatch2", "h_ZGG_muo_pho0_pho1_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_eb_tt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_eb_tt_genmatch2", "h_ZGG_muo_pho0_pho1_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_eb_tl_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_eb_tl_genmatch2", "h_ZGG_muo_pho0_pho1_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_eb_lt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_eb_lt_genmatch2", "h_ZGG_muo_pho0_pho1_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_eb_ll_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_eb_ll_genmatch2", "h_ZGG_muo_pho0_pho1_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_ee_tt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_ee_tt_genmatch2", "h_ZGG_muo_pho0_pho1_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_ee_tl_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_ee_tl_genmatch2", "h_ZGG_muo_pho0_pho1_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_ee_lt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_ee_lt_genmatch2", "h_ZGG_muo_pho0_pho1_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_ee_ll_genmatch2 = new TH3D("h_ZGG_muo_pho0_pho1_pt_ee_ll_genmatch2", "h_ZGG_muo_pho0_pho1_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_ele_pho0_pt_bb_tt = new TH3D("h_WGG_ele_pho0_pt_bb_tt", "h_WGG_ele_pho0_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_bb_tl = new TH3D("h_WGG_ele_pho0_pt_bb_tl", "h_WGG_ele_pho0_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_bb_lt = new TH3D("h_WGG_ele_pho0_pt_bb_lt", "h_WGG_ele_pho0_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_bb_ll = new TH3D("h_WGG_ele_pho0_pt_bb_ll", "h_WGG_ele_pho0_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_be_tt = new TH3D("h_WGG_ele_pho0_pt_be_tt", "h_WGG_ele_pho0_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_be_tl = new TH3D("h_WGG_ele_pho0_pt_be_tl", "h_WGG_ele_pho0_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_be_lt = new TH3D("h_WGG_ele_pho0_pt_be_lt", "h_WGG_ele_pho0_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_be_ll = new TH3D("h_WGG_ele_pho0_pt_be_ll", "h_WGG_ele_pho0_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_eb_tt = new TH3D("h_WGG_ele_pho0_pt_eb_tt", "h_WGG_ele_pho0_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_eb_tl = new TH3D("h_WGG_ele_pho0_pt_eb_tl", "h_WGG_ele_pho0_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_eb_lt = new TH3D("h_WGG_ele_pho0_pt_eb_lt", "h_WGG_ele_pho0_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_eb_ll = new TH3D("h_WGG_ele_pho0_pt_eb_ll", "h_WGG_ele_pho0_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_ee_tt = new TH3D("h_WGG_ele_pho0_pt_ee_tt", "h_WGG_ele_pho0_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_ee_tl = new TH3D("h_WGG_ele_pho0_pt_ee_tl", "h_WGG_ele_pho0_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_ee_lt = new TH3D("h_WGG_ele_pho0_pt_ee_lt", "h_WGG_ele_pho0_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_ee_ll = new TH3D("h_WGG_ele_pho0_pt_ee_ll", "h_WGG_ele_pho0_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_ele_pho0_pt_bb_tt_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_bb_tt_genmatch2", "h_WGG_ele_pho0_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_bb_tl_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_bb_tl_genmatch2", "h_WGG_ele_pho0_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_bb_lt_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_bb_lt_genmatch2", "h_WGG_ele_pho0_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_bb_ll_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_bb_ll_genmatch2", "h_WGG_ele_pho0_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_be_tt_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_be_tt_genmatch2", "h_WGG_ele_pho0_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_be_tl_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_be_tl_genmatch2", "h_WGG_ele_pho0_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_be_lt_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_be_lt_genmatch2", "h_WGG_ele_pho0_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_be_ll_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_be_ll_genmatch2", "h_WGG_ele_pho0_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_eb_tt_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_eb_tt_genmatch2", "h_WGG_ele_pho0_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_eb_tl_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_eb_tl_genmatch2", "h_WGG_ele_pho0_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_eb_lt_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_eb_lt_genmatch2", "h_WGG_ele_pho0_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_eb_ll_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_eb_ll_genmatch2", "h_WGG_ele_pho0_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_ee_tt_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_ee_tt_genmatch2", "h_WGG_ele_pho0_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_ee_tl_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_ee_tl_genmatch2", "h_WGG_ele_pho0_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_ee_lt_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_ee_lt_genmatch2", "h_WGG_ele_pho0_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho0_pt_ee_ll_genmatch2 = new TH3D("h_WGG_ele_pho0_pt_ee_ll_genmatch2", "h_WGG_ele_pho0_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_muo_pho0_pt_bb_tt = new TH3D("h_WGG_muo_pho0_pt_bb_tt", "h_WGG_muo_pho0_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_bb_tl = new TH3D("h_WGG_muo_pho0_pt_bb_tl", "h_WGG_muo_pho0_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_bb_lt = new TH3D("h_WGG_muo_pho0_pt_bb_lt", "h_WGG_muo_pho0_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_bb_ll = new TH3D("h_WGG_muo_pho0_pt_bb_ll", "h_WGG_muo_pho0_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_be_tt = new TH3D("h_WGG_muo_pho0_pt_be_tt", "h_WGG_muo_pho0_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_be_tl = new TH3D("h_WGG_muo_pho0_pt_be_tl", "h_WGG_muo_pho0_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_be_lt = new TH3D("h_WGG_muo_pho0_pt_be_lt", "h_WGG_muo_pho0_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_be_ll = new TH3D("h_WGG_muo_pho0_pt_be_ll", "h_WGG_muo_pho0_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_eb_tt = new TH3D("h_WGG_muo_pho0_pt_eb_tt", "h_WGG_muo_pho0_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_eb_tl = new TH3D("h_WGG_muo_pho0_pt_eb_tl", "h_WGG_muo_pho0_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_eb_lt = new TH3D("h_WGG_muo_pho0_pt_eb_lt", "h_WGG_muo_pho0_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_eb_ll = new TH3D("h_WGG_muo_pho0_pt_eb_ll", "h_WGG_muo_pho0_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_ee_tt = new TH3D("h_WGG_muo_pho0_pt_ee_tt", "h_WGG_muo_pho0_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_ee_tl = new TH3D("h_WGG_muo_pho0_pt_ee_tl", "h_WGG_muo_pho0_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_ee_lt = new TH3D("h_WGG_muo_pho0_pt_ee_lt", "h_WGG_muo_pho0_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_ee_ll = new TH3D("h_WGG_muo_pho0_pt_ee_ll", "h_WGG_muo_pho0_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_muo_pho0_pt_bb_tt_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_bb_tt_genmatch2", "h_WGG_muo_pho0_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_bb_tl_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_bb_tl_genmatch2", "h_WGG_muo_pho0_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_bb_lt_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_bb_lt_genmatch2", "h_WGG_muo_pho0_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_bb_ll_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_bb_ll_genmatch2", "h_WGG_muo_pho0_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_be_tt_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_be_tt_genmatch2", "h_WGG_muo_pho0_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_be_tl_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_be_tl_genmatch2", "h_WGG_muo_pho0_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_be_lt_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_be_lt_genmatch2", "h_WGG_muo_pho0_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_be_ll_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_be_ll_genmatch2", "h_WGG_muo_pho0_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_eb_tt_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_eb_tt_genmatch2", "h_WGG_muo_pho0_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_eb_tl_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_eb_tl_genmatch2", "h_WGG_muo_pho0_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_eb_lt_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_eb_lt_genmatch2", "h_WGG_muo_pho0_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_eb_ll_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_eb_ll_genmatch2", "h_WGG_muo_pho0_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_ee_tt_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_ee_tt_genmatch2", "h_WGG_muo_pho0_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_ee_tl_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_ee_tl_genmatch2", "h_WGG_muo_pho0_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_ee_lt_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_ee_lt_genmatch2", "h_WGG_muo_pho0_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho0_pt_ee_ll_genmatch2 = new TH3D("h_WGG_muo_pho0_pt_ee_ll_genmatch2", "h_WGG_muo_pho0_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_ele_pho0_pt_bb_tt = new TH3D("h_ZGG_ele_pho0_pt_bb_tt", "h_ZGG_ele_pho0_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_bb_tl = new TH3D("h_ZGG_ele_pho0_pt_bb_tl", "h_ZGG_ele_pho0_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_bb_lt = new TH3D("h_ZGG_ele_pho0_pt_bb_lt", "h_ZGG_ele_pho0_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_bb_ll = new TH3D("h_ZGG_ele_pho0_pt_bb_ll", "h_ZGG_ele_pho0_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_be_tt = new TH3D("h_ZGG_ele_pho0_pt_be_tt", "h_ZGG_ele_pho0_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_be_tl = new TH3D("h_ZGG_ele_pho0_pt_be_tl", "h_ZGG_ele_pho0_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_be_lt = new TH3D("h_ZGG_ele_pho0_pt_be_lt", "h_ZGG_ele_pho0_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_be_ll = new TH3D("h_ZGG_ele_pho0_pt_be_ll", "h_ZGG_ele_pho0_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_eb_tt = new TH3D("h_ZGG_ele_pho0_pt_eb_tt", "h_ZGG_ele_pho0_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_eb_tl = new TH3D("h_ZGG_ele_pho0_pt_eb_tl", "h_ZGG_ele_pho0_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_eb_lt = new TH3D("h_ZGG_ele_pho0_pt_eb_lt", "h_ZGG_ele_pho0_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_eb_ll = new TH3D("h_ZGG_ele_pho0_pt_eb_ll", "h_ZGG_ele_pho0_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_ee_tt = new TH3D("h_ZGG_ele_pho0_pt_ee_tt", "h_ZGG_ele_pho0_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_ee_tl = new TH3D("h_ZGG_ele_pho0_pt_ee_tl", "h_ZGG_ele_pho0_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_ee_lt = new TH3D("h_ZGG_ele_pho0_pt_ee_lt", "h_ZGG_ele_pho0_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_ee_ll = new TH3D("h_ZGG_ele_pho0_pt_ee_ll", "h_ZGG_ele_pho0_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_ele_pho0_pt_bb_tt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_bb_tt_genmatch2", "h_ZGG_ele_pho0_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_bb_tl_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_bb_tl_genmatch2", "h_ZGG_ele_pho0_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_bb_lt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_bb_lt_genmatch2", "h_ZGG_ele_pho0_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_bb_ll_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_bb_ll_genmatch2", "h_ZGG_ele_pho0_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_be_tt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_be_tt_genmatch2", "h_ZGG_ele_pho0_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_be_tl_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_be_tl_genmatch2", "h_ZGG_ele_pho0_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_be_lt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_be_lt_genmatch2", "h_ZGG_ele_pho0_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_be_ll_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_be_ll_genmatch2", "h_ZGG_ele_pho0_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_eb_tt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_eb_tt_genmatch2", "h_ZGG_ele_pho0_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_eb_tl_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_eb_tl_genmatch2", "h_ZGG_ele_pho0_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_eb_lt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_eb_lt_genmatch2", "h_ZGG_ele_pho0_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_eb_ll_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_eb_ll_genmatch2", "h_ZGG_ele_pho0_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_ee_tt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_ee_tt_genmatch2", "h_ZGG_ele_pho0_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_ee_tl_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_ee_tl_genmatch2", "h_ZGG_ele_pho0_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_ee_lt_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_ee_lt_genmatch2", "h_ZGG_ele_pho0_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho0_pt_ee_ll_genmatch2 = new TH3D("h_ZGG_ele_pho0_pt_ee_ll_genmatch2", "h_ZGG_ele_pho0_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_muo_pho0_pt_bb_tt = new TH3D("h_ZGG_muo_pho0_pt_bb_tt", "h_ZGG_muo_pho0_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_bb_tl = new TH3D("h_ZGG_muo_pho0_pt_bb_tl", "h_ZGG_muo_pho0_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_bb_lt = new TH3D("h_ZGG_muo_pho0_pt_bb_lt", "h_ZGG_muo_pho0_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_bb_ll = new TH3D("h_ZGG_muo_pho0_pt_bb_ll", "h_ZGG_muo_pho0_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_be_tt = new TH3D("h_ZGG_muo_pho0_pt_be_tt", "h_ZGG_muo_pho0_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_be_tl = new TH3D("h_ZGG_muo_pho0_pt_be_tl", "h_ZGG_muo_pho0_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_be_lt = new TH3D("h_ZGG_muo_pho0_pt_be_lt", "h_ZGG_muo_pho0_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_be_ll = new TH3D("h_ZGG_muo_pho0_pt_be_ll", "h_ZGG_muo_pho0_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_eb_tt = new TH3D("h_ZGG_muo_pho0_pt_eb_tt", "h_ZGG_muo_pho0_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_eb_tl = new TH3D("h_ZGG_muo_pho0_pt_eb_tl", "h_ZGG_muo_pho0_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_eb_lt = new TH3D("h_ZGG_muo_pho0_pt_eb_lt", "h_ZGG_muo_pho0_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_eb_ll = new TH3D("h_ZGG_muo_pho0_pt_eb_ll", "h_ZGG_muo_pho0_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_ee_tt = new TH3D("h_ZGG_muo_pho0_pt_ee_tt", "h_ZGG_muo_pho0_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_ee_tl = new TH3D("h_ZGG_muo_pho0_pt_ee_tl", "h_ZGG_muo_pho0_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_ee_lt = new TH3D("h_ZGG_muo_pho0_pt_ee_lt", "h_ZGG_muo_pho0_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_ee_ll = new TH3D("h_ZGG_muo_pho0_pt_ee_ll", "h_ZGG_muo_pho0_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_muo_pho0_pt_bb_tt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_bb_tt_genmatch2", "h_ZGG_muo_pho0_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_bb_tl_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_bb_tl_genmatch2", "h_ZGG_muo_pho0_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_bb_lt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_bb_lt_genmatch2", "h_ZGG_muo_pho0_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_bb_ll_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_bb_ll_genmatch2", "h_ZGG_muo_pho0_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_be_tt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_be_tt_genmatch2", "h_ZGG_muo_pho0_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_be_tl_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_be_tl_genmatch2", "h_ZGG_muo_pho0_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_be_lt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_be_lt_genmatch2", "h_ZGG_muo_pho0_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_be_ll_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_be_ll_genmatch2", "h_ZGG_muo_pho0_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_eb_tt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_eb_tt_genmatch2", "h_ZGG_muo_pho0_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_eb_tl_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_eb_tl_genmatch2", "h_ZGG_muo_pho0_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_eb_lt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_eb_lt_genmatch2", "h_ZGG_muo_pho0_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_eb_ll_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_eb_ll_genmatch2", "h_ZGG_muo_pho0_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_ee_tt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_ee_tt_genmatch2", "h_ZGG_muo_pho0_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_ee_tl_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_ee_tl_genmatch2", "h_ZGG_muo_pho0_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_ee_lt_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_ee_lt_genmatch2", "h_ZGG_muo_pho0_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho0_pt_ee_ll_genmatch2 = new TH3D("h_ZGG_muo_pho0_pt_ee_ll_genmatch2", "h_ZGG_muo_pho0_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_ele_pho1_pt_bb_tt = new TH3D("h_WGG_ele_pho1_pt_bb_tt", "h_WGG_ele_pho1_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_bb_tl = new TH3D("h_WGG_ele_pho1_pt_bb_tl", "h_WGG_ele_pho1_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_bb_lt = new TH3D("h_WGG_ele_pho1_pt_bb_lt", "h_WGG_ele_pho1_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_bb_ll = new TH3D("h_WGG_ele_pho1_pt_bb_ll", "h_WGG_ele_pho1_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_be_tt = new TH3D("h_WGG_ele_pho1_pt_be_tt", "h_WGG_ele_pho1_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_be_tl = new TH3D("h_WGG_ele_pho1_pt_be_tl", "h_WGG_ele_pho1_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_be_lt = new TH3D("h_WGG_ele_pho1_pt_be_lt", "h_WGG_ele_pho1_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_be_ll = new TH3D("h_WGG_ele_pho1_pt_be_ll", "h_WGG_ele_pho1_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_eb_tt = new TH3D("h_WGG_ele_pho1_pt_eb_tt", "h_WGG_ele_pho1_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_eb_tl = new TH3D("h_WGG_ele_pho1_pt_eb_tl", "h_WGG_ele_pho1_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_eb_lt = new TH3D("h_WGG_ele_pho1_pt_eb_lt", "h_WGG_ele_pho1_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_eb_ll = new TH3D("h_WGG_ele_pho1_pt_eb_ll", "h_WGG_ele_pho1_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_ee_tt = new TH3D("h_WGG_ele_pho1_pt_ee_tt", "h_WGG_ele_pho1_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_ee_tl = new TH3D("h_WGG_ele_pho1_pt_ee_tl", "h_WGG_ele_pho1_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_ee_lt = new TH3D("h_WGG_ele_pho1_pt_ee_lt", "h_WGG_ele_pho1_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_ee_ll = new TH3D("h_WGG_ele_pho1_pt_ee_ll", "h_WGG_ele_pho1_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_ele_pho1_pt_bb_tt_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_bb_tt_genmatch2", "h_WGG_ele_pho1_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_bb_tl_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_bb_tl_genmatch2", "h_WGG_ele_pho1_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_bb_lt_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_bb_lt_genmatch2", "h_WGG_ele_pho1_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_bb_ll_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_bb_ll_genmatch2", "h_WGG_ele_pho1_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_be_tt_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_be_tt_genmatch2", "h_WGG_ele_pho1_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_be_tl_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_be_tl_genmatch2", "h_WGG_ele_pho1_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_be_lt_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_be_lt_genmatch2", "h_WGG_ele_pho1_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_be_ll_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_be_ll_genmatch2", "h_WGG_ele_pho1_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_eb_tt_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_eb_tt_genmatch2", "h_WGG_ele_pho1_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_eb_tl_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_eb_tl_genmatch2", "h_WGG_ele_pho1_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_eb_lt_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_eb_lt_genmatch2", "h_WGG_ele_pho1_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_eb_ll_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_eb_ll_genmatch2", "h_WGG_ele_pho1_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_ee_tt_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_ee_tt_genmatch2", "h_WGG_ele_pho1_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_ee_tl_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_ee_tl_genmatch2", "h_WGG_ele_pho1_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_ee_lt_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_ee_lt_genmatch2", "h_WGG_ele_pho1_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_ele_pho1_pt_ee_ll_genmatch2 = new TH3D("h_WGG_ele_pho1_pt_ee_ll_genmatch2", "h_WGG_ele_pho1_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_muo_pho1_pt_bb_tt = new TH3D("h_WGG_muo_pho1_pt_bb_tt", "h_WGG_muo_pho1_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_bb_tl = new TH3D("h_WGG_muo_pho1_pt_bb_tl", "h_WGG_muo_pho1_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_bb_lt = new TH3D("h_WGG_muo_pho1_pt_bb_lt", "h_WGG_muo_pho1_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_bb_ll = new TH3D("h_WGG_muo_pho1_pt_bb_ll", "h_WGG_muo_pho1_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_be_tt = new TH3D("h_WGG_muo_pho1_pt_be_tt", "h_WGG_muo_pho1_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_be_tl = new TH3D("h_WGG_muo_pho1_pt_be_tl", "h_WGG_muo_pho1_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_be_lt = new TH3D("h_WGG_muo_pho1_pt_be_lt", "h_WGG_muo_pho1_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_be_ll = new TH3D("h_WGG_muo_pho1_pt_be_ll", "h_WGG_muo_pho1_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_eb_tt = new TH3D("h_WGG_muo_pho1_pt_eb_tt", "h_WGG_muo_pho1_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_eb_tl = new TH3D("h_WGG_muo_pho1_pt_eb_tl", "h_WGG_muo_pho1_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_eb_lt = new TH3D("h_WGG_muo_pho1_pt_eb_lt", "h_WGG_muo_pho1_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_eb_ll = new TH3D("h_WGG_muo_pho1_pt_eb_ll", "h_WGG_muo_pho1_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_ee_tt = new TH3D("h_WGG_muo_pho1_pt_ee_tt", "h_WGG_muo_pho1_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_ee_tl = new TH3D("h_WGG_muo_pho1_pt_ee_tl", "h_WGG_muo_pho1_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_ee_lt = new TH3D("h_WGG_muo_pho1_pt_ee_lt", "h_WGG_muo_pho1_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_ee_ll = new TH3D("h_WGG_muo_pho1_pt_ee_ll", "h_WGG_muo_pho1_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_WGG_muo_pho1_pt_bb_tt_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_bb_tt_genmatch2", "h_WGG_muo_pho1_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_bb_tl_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_bb_tl_genmatch2", "h_WGG_muo_pho1_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_bb_lt_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_bb_lt_genmatch2", "h_WGG_muo_pho1_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_bb_ll_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_bb_ll_genmatch2", "h_WGG_muo_pho1_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_be_tt_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_be_tt_genmatch2", "h_WGG_muo_pho1_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_be_tl_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_be_tl_genmatch2", "h_WGG_muo_pho1_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_be_lt_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_be_lt_genmatch2", "h_WGG_muo_pho1_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_be_ll_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_be_ll_genmatch2", "h_WGG_muo_pho1_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_eb_tt_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_eb_tt_genmatch2", "h_WGG_muo_pho1_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_eb_tl_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_eb_tl_genmatch2", "h_WGG_muo_pho1_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_eb_lt_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_eb_lt_genmatch2", "h_WGG_muo_pho1_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_eb_ll_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_eb_ll_genmatch2", "h_WGG_muo_pho1_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_ee_tt_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_ee_tt_genmatch2", "h_WGG_muo_pho1_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_ee_tl_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_ee_tl_genmatch2", "h_WGG_muo_pho1_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_ee_lt_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_ee_lt_genmatch2", "h_WGG_muo_pho1_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_WGG_muo_pho1_pt_ee_ll_genmatch2 = new TH3D("h_WGG_muo_pho1_pt_ee_ll_genmatch2", "h_WGG_muo_pho1_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_ele_pho1_pt_bb_tt = new TH3D("h_ZGG_ele_pho1_pt_bb_tt", "h_ZGG_ele_pho1_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_bb_tl = new TH3D("h_ZGG_ele_pho1_pt_bb_tl", "h_ZGG_ele_pho1_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_bb_lt = new TH3D("h_ZGG_ele_pho1_pt_bb_lt", "h_ZGG_ele_pho1_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_bb_ll = new TH3D("h_ZGG_ele_pho1_pt_bb_ll", "h_ZGG_ele_pho1_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_be_tt = new TH3D("h_ZGG_ele_pho1_pt_be_tt", "h_ZGG_ele_pho1_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_be_tl = new TH3D("h_ZGG_ele_pho1_pt_be_tl", "h_ZGG_ele_pho1_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_be_lt = new TH3D("h_ZGG_ele_pho1_pt_be_lt", "h_ZGG_ele_pho1_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_be_ll = new TH3D("h_ZGG_ele_pho1_pt_be_ll", "h_ZGG_ele_pho1_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_eb_tt = new TH3D("h_ZGG_ele_pho1_pt_eb_tt", "h_ZGG_ele_pho1_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_eb_tl = new TH3D("h_ZGG_ele_pho1_pt_eb_tl", "h_ZGG_ele_pho1_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_eb_lt = new TH3D("h_ZGG_ele_pho1_pt_eb_lt", "h_ZGG_ele_pho1_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_eb_ll = new TH3D("h_ZGG_ele_pho1_pt_eb_ll", "h_ZGG_ele_pho1_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_ee_tt = new TH3D("h_ZGG_ele_pho1_pt_ee_tt", "h_ZGG_ele_pho1_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_ee_tl = new TH3D("h_ZGG_ele_pho1_pt_ee_tl", "h_ZGG_ele_pho1_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_ee_lt = new TH3D("h_ZGG_ele_pho1_pt_ee_lt", "h_ZGG_ele_pho1_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_ee_ll = new TH3D("h_ZGG_ele_pho1_pt_ee_ll", "h_ZGG_ele_pho1_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_ele_pho1_pt_bb_tt_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_bb_tt_genmatch2", "h_ZGG_ele_pho1_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_bb_tl_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_bb_tl_genmatch2", "h_ZGG_ele_pho1_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_bb_lt_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_bb_lt_genmatch2", "h_ZGG_ele_pho1_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_bb_ll_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_bb_ll_genmatch2", "h_ZGG_ele_pho1_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_be_tt_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_be_tt_genmatch2", "h_ZGG_ele_pho1_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_be_tl_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_be_tl_genmatch2", "h_ZGG_ele_pho1_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_be_lt_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_be_lt_genmatch2", "h_ZGG_ele_pho1_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_be_ll_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_be_ll_genmatch2", "h_ZGG_ele_pho1_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_eb_tt_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_eb_tt_genmatch2", "h_ZGG_ele_pho1_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_eb_tl_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_eb_tl_genmatch2", "h_ZGG_ele_pho1_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_eb_lt_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_eb_lt_genmatch2", "h_ZGG_ele_pho1_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_eb_ll_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_eb_ll_genmatch2", "h_ZGG_ele_pho1_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_ee_tt_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_ee_tt_genmatch2", "h_ZGG_ele_pho1_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_ee_tl_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_ee_tl_genmatch2", "h_ZGG_ele_pho1_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_ee_lt_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_ee_lt_genmatch2", "h_ZGG_ele_pho1_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_ele_pho1_pt_ee_ll_genmatch2 = new TH3D("h_ZGG_ele_pho1_pt_ee_ll_genmatch2", "h_ZGG_ele_pho1_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_muo_pho1_pt_bb_tt = new TH3D("h_ZGG_muo_pho1_pt_bb_tt", "h_ZGG_muo_pho1_pt_bb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_bb_tl = new TH3D("h_ZGG_muo_pho1_pt_bb_tl", "h_ZGG_muo_pho1_pt_bb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_bb_lt = new TH3D("h_ZGG_muo_pho1_pt_bb_lt", "h_ZGG_muo_pho1_pt_bb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_bb_ll = new TH3D("h_ZGG_muo_pho1_pt_bb_ll", "h_ZGG_muo_pho1_pt_bb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_be_tt = new TH3D("h_ZGG_muo_pho1_pt_be_tt", "h_ZGG_muo_pho1_pt_be_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_be_tl = new TH3D("h_ZGG_muo_pho1_pt_be_tl", "h_ZGG_muo_pho1_pt_be_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_be_lt = new TH3D("h_ZGG_muo_pho1_pt_be_lt", "h_ZGG_muo_pho1_pt_be_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_be_ll = new TH3D("h_ZGG_muo_pho1_pt_be_ll", "h_ZGG_muo_pho1_pt_be_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_eb_tt = new TH3D("h_ZGG_muo_pho1_pt_eb_tt", "h_ZGG_muo_pho1_pt_eb_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_eb_tl = new TH3D("h_ZGG_muo_pho1_pt_eb_tl", "h_ZGG_muo_pho1_pt_eb_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_eb_lt = new TH3D("h_ZGG_muo_pho1_pt_eb_lt", "h_ZGG_muo_pho1_pt_eb_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_eb_ll = new TH3D("h_ZGG_muo_pho1_pt_eb_ll", "h_ZGG_muo_pho1_pt_eb_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_ee_tt = new TH3D("h_ZGG_muo_pho1_pt_ee_tt", "h_ZGG_muo_pho1_pt_ee_tt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_ee_tl = new TH3D("h_ZGG_muo_pho1_pt_ee_tl", "h_ZGG_muo_pho1_pt_ee_tl", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_ee_lt = new TH3D("h_ZGG_muo_pho1_pt_ee_lt", "h_ZGG_muo_pho1_pt_ee_lt", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_ee_ll = new TH3D("h_ZGG_muo_pho1_pt_ee_ll", "h_ZGG_muo_pho1_pt_ee_ll", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

   h_ZGG_muo_pho1_pt_bb_tt_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_bb_tt_genmatch2", "h_ZGG_muo_pho1_pt_bb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_bb_tl_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_bb_tl_genmatch2", "h_ZGG_muo_pho1_pt_bb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_bb_lt_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_bb_lt_genmatch2", "h_ZGG_muo_pho1_pt_bb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_bb_ll_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_bb_ll_genmatch2", "h_ZGG_muo_pho1_pt_bb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_be_tt_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_be_tt_genmatch2", "h_ZGG_muo_pho1_pt_be_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_be_tl_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_be_tl_genmatch2", "h_ZGG_muo_pho1_pt_be_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_be_lt_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_be_lt_genmatch2", "h_ZGG_muo_pho1_pt_be_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_be_ll_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_be_ll_genmatch2", "h_ZGG_muo_pho1_pt_be_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_eb_tt_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_eb_tt_genmatch2", "h_ZGG_muo_pho1_pt_eb_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_eb_tl_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_eb_tl_genmatch2", "h_ZGG_muo_pho1_pt_eb_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_eb_lt_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_eb_lt_genmatch2", "h_ZGG_muo_pho1_pt_eb_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_eb_ll_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_eb_ll_genmatch2", "h_ZGG_muo_pho1_pt_eb_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_ee_tt_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_ee_tt_genmatch2", "h_ZGG_muo_pho1_pt_ee_tt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_ee_tl_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_ee_tl_genmatch2", "h_ZGG_muo_pho1_pt_ee_tl_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_ee_lt_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_ee_lt_genmatch2", "h_ZGG_muo_pho1_pt_ee_lt_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);
   h_ZGG_muo_pho1_pt_ee_ll_genmatch2 = new TH3D("h_ZGG_muo_pho1_pt_ee_ll_genmatch2", "h_ZGG_muo_pho1_pt_ee_ll_genmatch2", 15, 0., 300., 15, 0., 300., 15, 0., 300.);

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   h_W_ele_gen = new TH1D("h_W_ele_gen", "h_W_ele_gen", 100, 0., 200.);
   h_W_muo_gen = new TH1D("h_W_muo_gen", "h_W_muo_gen", 100, 0., 200.);

   h_Z_ele_gen = new TH1D("h_Z_ele_gen", "h_Z_ele_gen", 160, 55., 135.);
   h_Z_muo_gen = new TH1D("h_Z_muo_gen", "h_Z_muo_gen", 160, 55., 135.);

   h_WG_ele_gen = new TH1D("h_WG_ele_gen", "h_WG_ele_gen", 40, 0., 200.);
   h_WG_muo_gen = new TH1D("h_WG_muo_gen", "h_WG_muo_gen", 40, 0., 200.);

   h_ZG_ele_gen = new TH1D("h_ZG_ele_gen", "h_ZG_ele_gen", 40, 55., 135.);
   h_ZG_muo_gen = new TH1D("h_ZG_muo_gen", "h_ZG_muo_gen", 40, 55., 135.);

   h_WGG_ele_gen = new TH1D("h_WGG_ele_gen", "h_WGG_ele_gen", 10, 0., 200.);
   h_WGG_muo_gen = new TH1D("h_WGG_muo_gen", "h_WGG_muo_gen", 10, 0., 200.);

   h_ZGG_ele_gen = new TH1D("h_ZGG_ele_gen", "h_ZGG_ele_gen", 8, 55., 135.);
   h_ZGG_muo_gen = new TH1D("h_ZGG_muo_gen", "h_ZGG_muo_gen", 8, 55., 135.);

   h_WGG_ele_pho0_pt_gen = new TH1D("h_WGG_ele_pho0_pt_gen", "h_WGG_ele_pho0_pt_gen", 15, 0., 300.);
   h_WGG_ele_pho1_pt_gen = new TH1D("h_WGG_ele_pho1_pt_gen", "h_WGG_ele_pho1_pt_gen", 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_gen = new TH1D("h_WGG_ele_pho0_pho1_pt_gen", "h_WGG_ele_pho0_pho1_pt_gen", 15, 0., 300.);

   h_WGG_muo_pho0_pt_gen = new TH1D("h_WGG_muo_pho0_pt_gen", "h_WGG_muo_pho0_pt_gen", 15, 0., 300.);
   h_WGG_muo_pho1_pt_gen = new TH1D("h_WGG_muo_pho1_pt_gen", "h_WGG_muo_pho1_pt_gen", 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_gen = new TH1D("h_WGG_muo_pho0_pho1_pt_gen", "h_WGG_muo_pho0_pho1_pt_gen", 15, 0., 300.);

   h_ZGG_ele_pho0_pt_gen = new TH1D("h_ZGG_ele_pho0_pt_gen", "h_ZGG_ele_pho0_pt_gen", 15, 0., 300.);
   h_ZGG_ele_pho1_pt_gen = new TH1D("h_ZGG_ele_pho1_pt_gen", "h_ZGG_ele_pho1_pt_gen", 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_gen = new TH1D("h_ZGG_ele_pho0_pho1_pt_gen", "h_ZGG_ele_pho0_pho1_pt_gen", 15, 0., 300.);

   h_ZGG_muo_pho0_pt_gen = new TH1D("h_ZGG_muo_pho0_pt_gen", "h_ZGG_muo_pho0_pt_gen", 15, 0., 300.);
   h_ZGG_muo_pho1_pt_gen = new TH1D("h_ZGG_muo_pho1_pt_gen", "h_ZGG_muo_pho1_pt_gen", 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_gen = new TH1D("h_ZGG_muo_pho0_pho1_pt_gen", "h_ZGG_muo_pho0_pho1_pt_gen", 15, 0., 300.);

   h_WG_ele_pho0_pt_genmatch = new TH1D("h_WG_ele_pho0_pt_genmatch", "h_WG_ele_pho0_pt_genmatch", 60, 0., 300.);
   h_WGG_ele_pho0_pt_genmatch = new TH1D("h_WGG_ele_pho0_pt_genmatch", "h_WGG_ele_pho0_pt_genmatch", 15, 0., 300.);
   h_WGG_ele_pho1_pt_genmatch = new TH1D("h_WGG_ele_pho1_pt_genmatch", "h_WGG_ele_pho1_pt_genmatch", 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_genmatch = new TH1D("h_WGG_ele_pho0_pho1_pt_genmatch", "h_WGG_ele_pho0_pho1_pt_genmatch", 15, 0., 300.);

   h_WG_muo_pho0_pt_genmatch = new TH1D("h_WG_muo_pho0_pt_genmatch", "h_WG_muo_pho0_pt_genmatch", 60, 0., 300.);
   h_WGG_muo_pho0_pt_genmatch = new TH1D("h_WGG_muo_pho0_pt_genmatch", "h_WGG_muo_pho0_pt_genmatch", 15, 0., 300.);
   h_WGG_muo_pho1_pt_genmatch = new TH1D("h_WGG_muo_pho1_pt_genmatch", "h_WGG_muo_pho1_pt_genmatch", 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_genmatch = new TH1D("h_WGG_muo_pho0_pho1_pt_genmatch", "h_WGG_muo_pho0_pho1_pt_genmatch", 15, 0., 300.);

   h_ZG_ele_pho0_pt_genmatch = new TH1D("h_ZG_ele_pho0_pt_genmatch", "h_ZG_ele_pho0_pt_genmatch", 60, 0., 300.);
   h_ZGG_ele_pho0_pt_genmatch = new TH1D("h_ZGG_ele_pho0_pt_genmatch", "h_ZGG_ele_pho0_pt_genmatch", 15, 0., 300.);
   h_ZGG_ele_pho1_pt_genmatch = new TH1D("h_ZGG_ele_pho1_pt_genmatch", "h_ZGG_ele_pho1_pt_genmatch", 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_genmatch = new TH1D("h_ZGG_ele_pho0_pho1_pt_genmatch", "h_ZGG_ele_pho0_pho1_pt_genmatch", 15, 0., 300.);

   h_ZG_muo_pho0_pt_genmatch = new TH1D("h_ZG_muo_pho0_pt_genmatch", "h_ZG_muo_pho0_pt_genmatch", 60, 0., 300.);
   h_ZGG_muo_pho0_pt_genmatch = new TH1D("h_ZGG_muo_pho0_pt_genmatch", "h_ZGG_muo_pho0_pt_genmatch", 15, 0., 300.);
   h_ZGG_muo_pho1_pt_genmatch = new TH1D("h_ZGG_muo_pho1_pt_genmatch", "h_ZGG_muo_pho1_pt_genmatch", 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_genmatch = new TH1D("h_ZGG_muo_pho0_pho1_pt_genmatch", "h_ZGG_muo_pho0_pho1_pt_genmatch", 15, 0., 300.);

   h_WG_ele_pho0_pt_genmatch2 = new TH1D("h_WG_ele_pho0_pt_genmatch2", "h_WG_ele_pho0_pt_genmatch2", 60, 0., 300.);
   h_WGG_ele_pho0_pt_genmatch2 = new TH1D("h_WGG_ele_pho0_pt_genmatch2", "h_WGG_ele_pho0_pt_genmatch2", 15, 0., 300.);
   h_WGG_ele_pho1_pt_genmatch2 = new TH1D("h_WGG_ele_pho1_pt_genmatch2", "h_WGG_ele_pho1_pt_genmatch2", 15, 0., 300.);
   h_WGG_ele_pho0_pho1_pt_genmatch2 = new TH1D("h_WGG_ele_pho0_pho1_pt_genmatch2", "h_WGG_ele_pho0_pho1_pt_genmatch2", 15, 0., 300.);

   h_WG_muo_pho0_pt_genmatch2 = new TH1D("h_WG_muo_pho0_pt_genmatch2", "h_WG_muo_pho0_pt_genmatch2", 60, 0., 300.);
   h_WGG_muo_pho0_pt_genmatch2 = new TH1D("h_WGG_muo_pho0_pt_genmatch2", "h_WGG_muo_pho0_pt_genmatch2", 15, 0., 300.);
   h_WGG_muo_pho1_pt_genmatch2 = new TH1D("h_WGG_muo_pho1_pt_genmatch2", "h_WGG_muo_pho1_pt_genmatch2", 15, 0., 300.);
   h_WGG_muo_pho0_pho1_pt_genmatch2 = new TH1D("h_WGG_muo_pho0_pho1_pt_genmatch2", "h_WGG_muo_pho0_pho1_pt_genmatch2", 15, 0., 300.);

   h_ZG_ele_pho0_pt_genmatch2 = new TH1D("h_ZG_ele_pho0_pt_genmatch2", "h_ZG_ele_pho0_pt_genmatch2", 60, 0., 300.);
   h_ZGG_ele_pho0_pt_genmatch2 = new TH1D("h_ZGG_ele_pho0_pt_genmatch2", "h_ZGG_ele_pho0_pt_genmatch2", 15, 0., 300.);
   h_ZGG_ele_pho1_pt_genmatch2 = new TH1D("h_ZGG_ele_pho1_pt_genmatch2", "h_ZGG_ele_pho1_pt_genmatch2", 15, 0., 300.);
   h_ZGG_ele_pho0_pho1_pt_genmatch2 = new TH1D("h_ZGG_ele_pho0_pho1_pt_genmatch2", "h_ZGG_ele_pho0_pho1_pt_genmatch2", 15, 0., 300.);

   h_ZG_muo_pho0_pt_genmatch2 = new TH1D("h_ZG_muo_pho0_pt_genmatch2", "h_ZG_muo_pho0_pt_genmatch2", 60, 0., 300.);
   h_ZGG_muo_pho0_pt_genmatch2 = new TH1D("h_ZGG_muo_pho0_pt_genmatch2", "h_ZGG_muo_pho0_pt_genmatch2", 15, 0., 300.);
   h_ZGG_muo_pho1_pt_genmatch2 = new TH1D("h_ZGG_muo_pho1_pt_genmatch2", "h_ZGG_muo_pho1_pt_genmatch2", 15, 0., 300.);
   h_ZGG_muo_pho0_pho1_pt_genmatch2 = new TH1D("h_ZGG_muo_pho0_pho1_pt_genmatch2", "h_ZGG_muo_pho0_pho1_pt_genmatch2", 15, 0., 300.);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

#if defined(COMPUTE_EG_MISID)
   h_WG_ele_fake_1 = new TH1D("h_WG_ele_fake_1", "h_WG_ele_fake_1", 100, 40., 200.);
   h_WG_ele_fake_2 = new TH1D("h_WG_ele_fake_2", "h_WG_ele_fake_2", 100, 40., 200.);
   h_WG_ele_fake_3 = new TH1D("h_WG_ele_fake_3", "h_WG_ele_fake_3", 100, 40., 200.);
   h_WG_ele_fake_4 = new TH1D("h_WG_ele_fake_4", "h_WG_ele_fake_4", 100, 40., 200.);
   h_WG_ele_fake_5 = new TH1D("h_WG_ele_fake_5", "h_WG_ele_fake_5", 100, 40., 200.);
   h_WG_ele_fake_6 = new TH1D("h_WG_ele_fake_6", "h_WG_ele_fake_6", 100, 40., 200.);
   h_WG_ele_fake_7 = new TH1D("h_WG_ele_fake_7", "h_WG_ele_fake_7", 100, 40., 200.);
   h_WG_ele_fake_8 = new TH1D("h_WG_ele_fake_8", "h_WG_ele_fake_8", 100, 40., 200.);
   h_WG_ele_fake_9 = new TH1D("h_WG_ele_fake_9", "h_WG_ele_fake_9", 100, 40., 200.);
   h_WG_ele_fake_10 = new TH1D("h_WG_ele_fake_10", "h_WG_ele_fake_10", 100, 40., 200.);
   h_WG_ele_fake_11 = new TH1D("h_WG_ele_fake_11", "h_WG_ele_fake_11", 100, 40., 200.);
   h_WG_ele_fake_12 = new TH1D("h_WG_ele_fake_12", "h_WG_ele_fake_12", 100, 40., 200.);
   h_WG_ele_fake_13 = new TH1D("h_WG_ele_fake_13", "h_WG_ele_fake_13", 100, 40., 200.);
   h_WG_ele_fake_14 = new TH1D("h_WG_ele_fake_14", "h_WG_ele_fake_14", 100, 40., 200.);
   h_WG_ele_fake_15 = new TH1D("h_WG_ele_fake_15", "h_WG_ele_fake_15", 100, 40., 200.);
   h_WG_ele_fake_16 = new TH1D("h_WG_ele_fake_16", "h_WG_ele_fake_16", 100, 40., 200.);
   h_WG_ele_fake_17 = new TH1D("h_WG_ele_fake_17", "h_WG_ele_fake_17", 100, 40., 200.);
   h_WG_ele_fake_18 = new TH1D("h_WG_ele_fake_18", "h_WG_ele_fake_18", 100, 40., 200.);
   h_WG_ele_fake_19 = new TH1D("h_WG_ele_fake_19", "h_WG_ele_fake_19", 100, 40., 200.);
   h_WG_ele_fake_20 = new TH1D("h_WG_ele_fake_20", "h_WG_ele_fake_20", 100, 40., 200.);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   h_WG_ele_fake_truthmatch_1 = new TH1D("h_WG_ele_fake_truthmatch_1", "h_WG_ele_fake_truthmatch_1", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_2 = new TH1D("h_WG_ele_fake_truthmatch_2", "h_WG_ele_fake_truthmatch_2", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_3 = new TH1D("h_WG_ele_fake_truthmatch_3", "h_WG_ele_fake_truthmatch_3", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_4 = new TH1D("h_WG_ele_fake_truthmatch_4", "h_WG_ele_fake_truthmatch_4", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_5 = new TH1D("h_WG_ele_fake_truthmatch_5", "h_WG_ele_fake_truthmatch_5", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_6 = new TH1D("h_WG_ele_fake_truthmatch_6", "h_WG_ele_fake_truthmatch_6", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_7 = new TH1D("h_WG_ele_fake_truthmatch_7", "h_WG_ele_fake_truthmatch_7", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_8 = new TH1D("h_WG_ele_fake_truthmatch_8", "h_WG_ele_fake_truthmatch_8", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_9 = new TH1D("h_WG_ele_fake_truthmatch_9", "h_WG_ele_fake_truthmatch_9", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_10 = new TH1D("h_WG_ele_fake_truthmatch_10", "h_WG_ele_fake_truthmatch_10", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_11 = new TH1D("h_WG_ele_fake_truthmatch_11", "h_WG_ele_fake_truthmatch_11", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_12 = new TH1D("h_WG_ele_fake_truthmatch_12", "h_WG_ele_fake_truthmatch_12", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_13 = new TH1D("h_WG_ele_fake_truthmatch_13", "h_WG_ele_fake_truthmatch_13", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_14 = new TH1D("h_WG_ele_fake_truthmatch_14", "h_WG_ele_fake_truthmatch_14", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_15 = new TH1D("h_WG_ele_fake_truthmatch_15", "h_WG_ele_fake_truthmatch_15", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_16 = new TH1D("h_WG_ele_fake_truthmatch_16", "h_WG_ele_fake_truthmatch_16", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_17 = new TH1D("h_WG_ele_fake_truthmatch_17", "h_WG_ele_fake_truthmatch_17", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_18 = new TH1D("h_WG_ele_fake_truthmatch_18", "h_WG_ele_fake_truthmatch_18", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_19 = new TH1D("h_WG_ele_fake_truthmatch_19", "h_WG_ele_fake_truthmatch_19", 100, 40., 200.);
   h_WG_ele_fake_truthmatch_20 = new TH1D("h_WG_ele_fake_truthmatch_20", "h_WG_ele_fake_truthmatch_20", 100, 40., 200.);
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#endif // defined(COMPUTE_EG_MISID)

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

   // set random seed
   uint seed = (*run << 20) + (*luminosityBlock << 10) + (*event << 5) + (*nElectron) + (*nMuon) + (*nPhoton) + (*nJet);
   gRandom->SetSeed(seed);

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

#if defined(RIVET)
   weight_pu_ele = 1.;
   weight_pu_muo = 1.;
#endif // defined(RIVET)

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (isWJetsToLNu || isWG || isWGG || isWTauNu || isDYJetsToLL || isZG || isZGG || isZTauTau) {

     bool W_tau_sel_gen = false;
     bool Z_tau_sel_gen = false;

     for (uint i = 0; i < *nGenPart; i++) {
       if (fabs(GenPart_pdgId[i]) != 15) continue;
       if (GenPart_genPartIdxMother[i] >= 0 && (uint)GenPart_genPartIdxMother[i] < *nGenPart) {
         if (fabs(GenPart_pdgId[GenPart_genPartIdxMother[i]]) == 24) {
           if (isWJetsToLNu || isWG || isWGG) return kTRUE;
           if (isWTauNu) W_tau_sel_gen = true;
         }
         if (fabs(GenPart_pdgId[GenPart_genPartIdxMother[i]]) == 23) {
           if (isDYJetsToLL || isZG || isZGG) return kTRUE;
           if (isZTauTau) Z_tau_sel_gen = true;
         }
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

   if (isWJetsToLNu || isWG || isWGG || isDYJetsToLL || isZG || isZGG || isST || isTGJets || isTTJets || isTTGJets || isTTGG || isWW || isWWG || isWZ || isWZG) {

     for (uint i = 0; i < *nGenDressedLepton; i++) {
       if (fabs(GenDressedLepton_pdgId[i]) != 11) continue;
       if (GenDressedLepton_pt[i] < 15) continue;
       if (fabs(GenDressedLepton_eta[i]) > 2.500) continue;

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
       if (GenDressedLepton_pt[i] < 15) continue;
       if (fabs(GenDressedLepton_eta[i]) > 2.500) continue;

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
       if (*MET_fiducialGenPt > 0 && W_ele0_gen_mt > 0 && ele0_gen.Pt() > 30) {
         W_ele_sel_gen = true;
       }
     }

     float W_muo0_gen_mt = 0.;

     if (imuo0_gen != -1 && imuo1_gen == -1 && iele0_gen == -1) {
       W_muo0_gen_mt = TMath::Sqrt(2. * muo0_gen.Pt() * (*MET_fiducialGenPt) * (1. - TMath::Cos(muo0_gen.Phi() - (*MET_fiducialGenPhi))));
       if (*MET_fiducialGenPt > 0 && W_muo0_gen_mt > 0 && muo0_gen.Pt() > 30) {
         W_muo_sel_gen = true;
       }
     }

     float Z_ele0_ele1_gen_m = 0.;

     if (iele0_gen != -1 && iele1_gen != -1) {
       Z_ele0_ele1_gen_m = (ele0_gen + ele1_gen).M();
       if (Z_ele0_ele1_gen_m >= 55. && (ele0_gen.Pt() > 30 || ele1_gen.Pt() > 30)) {
         Z_ele_sel_gen = true;
       }
     }

     float Z_muo0_muo1_gen_m = 0.;

     if (imuo0_gen != -1 && imuo1_gen != -1) {
       Z_muo0_muo1_gen_m = (muo0_gen + muo1_gen).M();
       if (Z_muo0_muo1_gen_m >= 55. && (muo0_gen.Pt() > 30 || muo1_gen.Pt() > 30)) {
         Z_muo_sel_gen = true;
       }
     }

     for (uint i = 0; i < *nGenPart; i++) {
       if (GenPart_status[i] != 1) continue;
       if (fabs(GenPart_pdgId[i]) != 22) continue;
       if ((GenPart_statusFlags[i] & 1) != 1) continue;
       if (GenPart_pt[i] < 15) continue;
       if (fabs(GenPart_eta[i]) > 2.500) continue;

       bool skip = false;

       TLorentzVector tmp_pho_gen;
       tmp_pho_gen.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);

       for (uint j = 0; j < *nGenDressedLepton; j++) {
         if (skip) continue;
         if (fabs(GenDressedLepton_pdgId[j]) != 11 && fabs(GenDressedLepton_pdgId[j]) != 13) continue;
         if (GenDressedLepton_pt[j] < 15) continue;
         if (fabs(GenDressedLepton_eta[j]) > 2.500) continue;

         TLorentzVector tmp_lept_gen;
         tmp_lept_gen.SetPtEtaPhiM(GenDressedLepton_pt[j], GenDressedLepton_eta[j], GenDressedLepton_phi[j], GenDressedLepton_mass[j]);
         if (tmp_lept_gen.DeltaR(tmp_pho_gen) < 0.4) skip = true;
       }

       if (skip) continue;

       for (uint j = 0; j < *nGenPart; j++) {
         if (skip) continue;
#if 0
         if (fabs(GenPart_pdgId[j]) >= 6 && fabs(GenPart_pdgId[j]) != 21) continue;
#endif
#if 1
         if (GenPart_status[j] != 1) continue;
         if (fabs(GenPart_pdgId[j]) == 22) continue;
         if (fabs(GenPart_pdgId[j]) == 12) continue;
         if (fabs(GenPart_pdgId[j]) == 14) continue;
         if (fabs(GenPart_pdgId[j]) == 16) continue;
#endif
         if (GenPart_pt[j] < 15) continue;
         if (fabs(GenPart_eta[j]) > 2.500) continue;

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

     if (W_ele_sel_gen) {
       h_W_ele_gen->Fill(W_ele0_gen_mt, weight_gen * weight_pu_ele);
     }

     if (W_muo_sel_gen) {
       h_W_muo_gen->Fill(W_muo0_gen_mt, weight_gen * weight_pu_muo);
     }

     if (Z_ele_sel_gen) {
       h_Z_ele_gen->Fill(Z_ele0_ele1_gen_m, weight_gen * weight_pu_ele);
     }

     if (Z_muo_sel_gen) {
       h_Z_muo_gen->Fill(Z_muo0_muo1_gen_m, weight_gen * weight_pu_muo);
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

     if (isST) {
       if (n_photons_gen != 0) return kTRUE;
     }
     if (isTGJets) {
       if (n_photons_gen == 0) return kTRUE;
     }

     if (isTTJets) {
       if (n_photons_gen != 0) return kTRUE;
     }
     if (isTTGJets) {
       if (n_photons_gen != 1) return kTRUE;
     }
     if (isTTGG) {
       if (n_photons_gen == 0 || n_photons_gen == 1) return kTRUE;
     }

     if (isWW) {
       if (n_photons_gen != 0) return kTRUE;
     }
     if (isWWG) {
       if (n_photons_gen == 0) return kTRUE;
     }

     if (isWZ) {
       if (n_photons_gen != 0) return kTRUE;
     }
     if (isWZG) {
       if (n_photons_gen == 0) return kTRUE;
     }

     if (ipho0_gen != -1) {
       pho0_gen.SetPtEtaPhiM(GenPart_pt[ipho0_gen], GenPart_eta[ipho0_gen], GenPart_phi[ipho0_gen], GenPart_mass[ipho0_gen]);
     }
     if (ipho1_gen != -1) {
       pho1_gen.SetPtEtaPhiM(GenPart_pt[ipho1_gen], GenPart_eta[ipho1_gen], GenPart_phi[ipho1_gen], GenPart_mass[ipho1_gen]);
     }

     if (ipho0_gen != -1) {
       if (pho0_gen.Pt() < 20) {
         ipho0_gen = -1;
       }
     }
     if (ipho1_gen != -1) {
       if (pho1_gen.Pt() < 20) {
         ipho1_gen = -1;
       }
     }

     if (W_ele_sel_gen) {
       if (ipho0_gen != -1) {
         h_WG_ele_gen->Fill(W_ele0_gen_mt, weight_gen * weight_pu_ele);
       }
       if (ipho1_gen != -1) {
         h_WGG_ele_gen->Fill(W_ele0_gen_mt, weight_gen * weight_pu_ele);
         h_WGG_ele_pho0_pt_gen->Fill(pho0_gen.Pt(), weight_gen * weight_pu_ele);
         h_WGG_ele_pho1_pt_gen->Fill(pho1_gen.Pt(), weight_gen * weight_pu_ele);
         h_WGG_ele_pho0_pho1_pt_gen->Fill((pho0_gen + pho1_gen).Pt(), weight_gen * weight_pu_ele);
       }
     }

     if (W_muo_sel_gen) {
       if (ipho0_gen != -1) {
         h_WG_muo_gen->Fill(W_muo0_gen_mt, weight_gen * weight_pu_muo);
       }
       if (ipho1_gen != -1) {
         h_WGG_muo_gen->Fill(W_muo0_gen_mt, weight_gen * weight_pu_muo);
         h_WGG_muo_pho0_pt_gen->Fill(pho0_gen.Pt(), weight_gen * weight_pu_muo);
         h_WGG_muo_pho1_pt_gen->Fill(pho1_gen.Pt(), weight_gen * weight_pu_muo);
         h_WGG_muo_pho0_pho1_pt_gen->Fill((pho0_gen + pho1_gen).Pt(), weight_gen * weight_pu_muo);
       }
     }

     if (Z_ele_sel_gen) {
       if (ipho0_gen != -1) {
         h_ZG_ele_gen->Fill(Z_ele0_ele1_gen_m, weight_gen * weight_pu_ele);
       }
       if (ipho1_gen != -1) {
         h_ZGG_ele_gen->Fill(Z_ele0_ele1_gen_m, weight_gen * weight_pu_ele);
         h_ZGG_ele_pho0_pt_gen->Fill(pho0_gen.Pt(), weight_gen * weight_pu_ele);
         h_ZGG_ele_pho1_pt_gen->Fill(pho1_gen.Pt(), weight_gen * weight_pu_ele);
         h_ZGG_ele_pho0_pho1_pt_gen->Fill((pho0_gen + pho1_gen).Pt(), weight_gen * weight_pu_ele);
       }
     }

     if (Z_muo_sel_gen) {
       if (ipho0_gen != -1) {
         h_ZG_muo_gen->Fill(Z_muo0_muo1_gen_m, weight_gen * weight_pu_muo);
       }
       if (ipho1_gen != -1) {
         h_ZGG_muo_gen->Fill(Z_muo0_muo1_gen_m, weight_gen * weight_pu_muo);
         h_ZGG_muo_pho0_pt_gen->Fill(pho0_gen.Pt(), weight_gen * weight_pu_muo);
         h_ZGG_muo_pho1_pt_gen->Fill(pho1_gen.Pt(), weight_gen * weight_pu_muo);
         h_ZGG_muo_pho0_pho1_pt_gen->Fill((pho0_gen + pho1_gen).Pt(), weight_gen * weight_pu_muo);
       }
     }

   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   h_nevt->Fill(2.5, weight_gen);

   if (*Flag_goodVertices == 0) return kTRUE;
   if (*Flag_globalSuperTightHalo2016Filter == 0) return kTRUE;
   if (*Flag_HBHENoiseFilter == 0) return kTRUE;
   if (*Flag_HBHENoiseIsoFilter == 0) return kTRUE;
   if (*Flag_EcalDeadCellTriggerPrimitiveFilter == 0) return kTRUE;
   if (*Flag_BadPFMuonFilter == 0) return kTRUE;
   if (*Flag_eeBadScFilter == 0) return kTRUE;
   if (*Flag_ecalBadCalibFilter == 0) return kTRUE;

#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
   if (*Flag_ecalBadCalibFilterV2 == 0) return kTRUE;
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)

   h_nevt->Fill(3.5, weight_gen);

// electrons

   int iele0 = -1;
   int iele1 = -1;

   for (uint i = 0; i < *nElectron; i++) {
     float eCorr_ele = 1.;
     Electron_pt[i] = Electron_pt[i] * eCorr_ele;
     if (Electron_pt[i] < 15) continue;
     if (fabs(Electron_eta[i]) > 1.442 && fabs(Electron_eta[i]) < 1.566) continue;
     if (fabs(Electron_eta[i]) > 2.500) continue;

     if (fabs(Electron_eta[i]) < 1.442) {
       if (fabs(Electron_dxy[i]) > 0.05) continue;
       if (fabs(Electron_dz[i]) > 0.10) continue;
     }
     if (fabs(Electron_eta[i]) > 1.566 && fabs(Electron_eta[i]) < 2.500) {
       if (fabs(Electron_dxy[i]) > 0.10) continue;
       if (fabs(Electron_dz[i]) > 0.20) continue;
     }

     //if (Electron_mvaID_WP80[i] == 0) continue;
     if (iflag != 150 && Electron_Id_noIso(Electron_vidNestedWPBitmap[i], 4) == 0) continue;
     if (iflag == 150 && Electron_Id_noIso(Electron_vidNestedWPBitmap[i], 3) == 0) continue;

     //if (Electron_pfRelIso03_all[i] > 0.15) continue;
     if (iflag != 150 && Electron_Iso(Electron_vidNestedWPBitmap[i], 4) == 0) continue;
     if (iflag == 150 && Electron_Iso(Electron_vidNestedWPBitmap[i], 3) == 0) continue;

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
     if (Electron_pt[i] < 15) continue;
     if (fabs(Electron_eta[i]) > 1.442 && fabs(Electron_eta[i]) < 1.566) continue;
     if (fabs(Electron_eta[i]) > 2.500) continue;

     if (fabs(Electron_eta[i]) < 1.442) {
       if (fabs(Electron_dxy[i]) > 0.05) continue;
       if (fabs(Electron_dz[i]) > 0.10) continue;
     }
     if (fabs(Electron_eta[i]) > 1.566 && fabs(Electron_eta[i]) < 2.500) {
       if (fabs(Electron_dxy[i]) > 0.10) continue;
       if (fabs(Electron_dz[i]) > 0.20) continue;
     }

     //if (Electron_mvaID_WP80[i] == 0) continue;
     if (iflag != 150 && Electron_Id_noIso(Electron_vidNestedWPBitmap[i], 4) == 0) continue;
     if (iflag == 150 && Electron_Id_noIso(Electron_vidNestedWPBitmap[i], 3) == 0) continue;

     //if (Electron_pfRelIso03_all[i] < 0.15) continue;
     if (iflag != 150 && Electron_Iso(Electron_vidNestedWPBitmap[i], 4) != 0) continue;
     if (iflag == 150 && Electron_Iso(Electron_vidNestedWPBitmap[i], 3) != 0) continue;

     if (Electron_pfRelIso03_all[i] > 0.15) continue;

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
#if defined(__linux__)
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
     eCorr_muo = roccor->kScaleDT(Muon_charge[i], Muon_pt[i], Muon_eta[i], Muon_phi[i], 0, 0);
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
     if (Muon_genPartIdx[i] >= 0 && (uint)Muon_genPartIdx[i] < *nGenPart) {
       eCorr_muo = roccor->kSpreadMC(Muon_charge[i], Muon_pt[i], Muon_eta[i], Muon_phi[i], GenPart_pt[Muon_genPartIdx[i]], 0, 0);
     } else {
       eCorr_muo = roccor->kSmearMC(Muon_charge[i], Muon_pt[i], Muon_eta[i], Muon_phi[i], Muon_nTrackerLayers[i], gRandom->Rndm(), 0, 0);
       if (!TMath::Finite(eCorr_muo)) eCorr_muo = 1.;
     }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#endif // defined(__linux__)
     Muon_pt[i] = Muon_pt[i] * eCorr_muo;
     if (Muon_pt[i] < 15) continue;
     if (fabs(Muon_eta[i]) > 2.400) continue;

     if (iflag != 155 && Muon_tightId[i] == 0) continue;
     if (iflag == 155 && Muon_mediumId[i] == 0) continue;

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
     if (Muon_pt[i] < 15) continue;
     if (fabs(Muon_eta[i]) > 2.400) continue;

     if (iflag != 155 && Muon_tightId[i] == 0) continue;
     if (iflag == 155 && Muon_mediumId[i] == 0) continue;

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
     return kTRUE;
   }

// photons

   int n_photons = 0;
   int ipho0 = -1;
   int ipho1 = -1;
   int ipho0_fake = -1;

   for (uint i = 0; i < *nPhoton; i++) {
     float eCorr_pho = 1.;
     Photon_pt[i] = Photon_pt[i] * eCorr_pho;
     if (Photon_pt[i] < 20) continue;
     if (fabs(Photon_eta[i]) > 1.442 && fabs(Photon_eta[i]) < 1.566) continue;
     if (fabs(Photon_eta[i]) > 2.500) continue;

     //if (fabs(Photon_eta[i]) < 1.442) {
     //  if (Photon_mvaID[i] < -0.02) continue;
     //}
     //if (fabs(Photon_eta[i]) > 1.566 && fabs(Photon_eta[i]) < 2.500) {
     //  if (Photon_mvaID[i] < -0.26) continue;
     //}
     if (Photon_Id_noIso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     //if (Photon_electronVeto[i] == 0) continue;
     if (Photon_pixelSeed[i] != 0) continue;

     //if (Photon_pfRelIso03_all[i] > 0.15) continue;
     if (Photon_Iso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     bool skip = false;

     TLorentzVector tmp_pho;
     tmp_pho.SetPtEtaPhiM(Photon_pt[i], Photon_eta[i], Photon_phi[i], Photon_mass[i]);

     if (iele0 != -1 && ele0.DeltaR(tmp_pho) < 0.4) continue;
     if (iele1 != -1 && ele1.DeltaR(tmp_pho) < 0.4) continue;

     if (imuo0 != -1 && muo0.DeltaR(tmp_pho) < 0.4) continue;
     if (imuo1 != -1 && muo1.DeltaR(tmp_pho) < 0.4) continue;

     for (uint j = 0; j < *nElectron; j++) {
       if (skip) continue;
       if (Electron_pt[j] < 15) continue;
       if (fabs(Electron_eta[j]) > 1.442 && fabs(Electron_eta[j]) < 1.566) continue;
       if (fabs(Electron_eta[j]) > 2.500) continue;

       if (fabs(Electron_eta[j]) < 1.442) {
         if (fabs(Electron_dxy[j]) > 0.05) continue;
         if (fabs(Electron_dz[j]) > 0.10) continue;
       }
       if (fabs(Electron_eta[j]) > 1.566 && fabs(Electron_eta[j]) < 2.500) {
         if (fabs(Electron_dxy[j]) > 0.10) continue;
         if (fabs(Electron_dz[j]) > 0.20) continue;
       }

       //if (Electron_mvaID_WP80[j] == 0) continue;
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[j], 4) == 0) continue;

       TLorentzVector tmp_ele;
       tmp_ele.SetPtEtaPhiM(Electron_pt[j], Electron_eta[j], Electron_phi[j], Electron_mass[j]);
       if (tmp_ele.DeltaR(tmp_pho) < 0.4) skip = true;
     }

     for (uint j = 0; j < *nMuon; j++) {
       if (skip) continue;
       if (Muon_pt[j] < 15) continue;
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
     }

     if (ipho1 != -1) {
       TLorentzVector tmp_pho1;
       tmp_pho1.SetPtEtaPhiM(Photon_pt[ipho1], Photon_eta[ipho1], Photon_phi[ipho1], Photon_mass[ipho1]);
       if (tmp_pho1.DeltaR(tmp_pho) < 0.4) continue;
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

   TLorentzVector pho0;
   TLorentzVector pho1;

   if (ipho0 != -1) {
     pho0.SetPtEtaPhiM(Photon_pt[ipho0], Photon_eta[ipho0], Photon_phi[ipho0], Photon_mass[ipho0]);
   }
   if (ipho1 != -1) {
     pho1.SetPtEtaPhiM(Photon_pt[ipho1], Photon_eta[ipho1], Photon_phi[ipho1], Photon_mass[ipho1]);
   }

   TLorentzVector pho0_fake;

   if (ipho0 != -1 && ipho0_fake == -1) {
     ipho0_fake = ipho0;
     pho0_fake = pho0;
   }

   if (iele0 != -1 && iele1 == -1) {

     if (ipho0 != -1 && fabs((ele0+pho0).M()-91.2) < 5) {
       ipho0 = -1;
       ipho1 = -1;
       n_photons = n_photons - 2;
     }
     if (ipho1 != -1 && fabs((ele0+pho1).M()-91.2) < 5) {
       ipho1 = -1;
       n_photons = n_photons - 1;
     }
     if (ipho1 != -1 && fabs((ele0+pho0+pho1).M()-91.2) < 5) {
       ipho0 = -1;
       ipho1 = -1;
       n_photons = n_photons - 2;
     }

   }

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#if 0
   if (isWG || isWGG || isZG || isZGG || isTGJets || isTTGJets || isTTGG || isWWG || isWZG) {

     bool match0 = false;
     bool match1 = false;

     for (uint i = 0; i < *nGenPart; i++) {
       if (GenPart_status[i] != 1) continue;
       if (fabs(GenPart_pdgId[i]) != 22) continue;
       if ((GenPart_statusFlags[i] & 1) != 1) continue;
       if (GenPart_pt[i] < 20) continue;
       if (fabs(GenPart_eta[i]) > 2.500) continue;

       TLorentzVector tmp_pho_gen;
       tmp_pho_gen.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);
       if (ipho0 != -1 && tmp_pho_gen.DeltaR(pho0) < 0.2) match0 = true;
       if (ipho1 != -1 && tmp_pho_gen.DeltaR(pho1) < 0.2) match1 = true;
     }

     if (ipho0 != -1 && !match0) {
       ipho0 = -1;
       ipho1 = -1;
       n_photons = n_photons - 2;
     }
     if (ipho1 != -1 && !match1) {
       ipho1 = -1;
       n_photons = n_photons - 1;
     }

   }
#endif
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

// photons iso

   int n_photons_iso = 0;
   int ipho0_iso = -1;
   int ipho1_iso = -1;

   for (uint i = 0; i < *nPhoton; i++) {
     if (Photon_pt[i] < 20) continue;
     if (fabs(Photon_eta[i]) > 1.442 && fabs(Photon_eta[i]) < 1.566) continue;
     if (fabs(Photon_eta[i]) > 2.500) continue;

     //if (fabs(Photon_eta[i]) < 1.442) {
     //  if (Photon_mvaID[i] < -0.02) continue;
     //}
     //if (fabs(Photon_eta[i]) > 1.566 && fabs(Photon_eta[i]) < 2.500) {
     //  if (Photon_mvaID[i] < -0.26) continue;
     //}
     //if (Photon_Id_noIso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;
     if (iflag != 140 && Photon_Id_noIso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;
     if (iflag == 140 && Photon_Id_noSieie(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     //if (Photon_electronVeto[i] == 0) continue;
     if (Photon_pixelSeed[i] != 0) continue;

     //if (Photon_pfRelIso03_all[i] > 0.15) continue;
     //if (Photon_Iso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     bool skip = false;

     TLorentzVector tmp_pho_iso;
     tmp_pho_iso.SetPtEtaPhiM(Photon_pt[i], Photon_eta[i], Photon_phi[i], Photon_mass[i]);

     if (iele0 != -1 && ele0.DeltaR(tmp_pho_iso) < 0.4) continue;
     if (iele1 != -1 && ele1.DeltaR(tmp_pho_iso) < 0.4) continue;

     if (imuo0 != -1 && muo0.DeltaR(tmp_pho_iso) < 0.4) continue;
     if (imuo1 != -1 && muo1.DeltaR(tmp_pho_iso) < 0.4) continue;

     for (uint j = 0; j < *nElectron; j++) {
       if (skip) continue;
       if (Electron_pt[j] < 15) continue;
       if (fabs(Electron_eta[j]) > 1.442 && fabs(Electron_eta[j]) < 1.566) continue;
       if (fabs(Electron_eta[j]) > 2.500) continue;

       if (fabs(Electron_eta[j]) < 1.442) {
         if (fabs(Electron_dxy[j]) > 0.05) continue;
         if (fabs(Electron_dz[j]) > 0.10) continue;
       }
       if (fabs(Electron_eta[j]) > 1.566 && fabs(Electron_eta[j]) < 2.500) {
         if (fabs(Electron_dxy[j]) > 0.10) continue;
         if (fabs(Electron_dz[j]) > 0.20) continue;
       }

       //if (Electron_mvaID_WP80[j] == 0) continue;
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[j], 4) == 0) continue;

       TLorentzVector tmp_ele;
       tmp_ele.SetPtEtaPhiM(Electron_pt[j], Electron_eta[j], Electron_phi[j], Electron_mass[j]);
       if (tmp_ele.DeltaR(tmp_pho_iso) < 0.4) skip = true;
     }

     for (uint j = 0; j < *nMuon; j++) {
       if (skip) continue;
       if (Muon_pt[j] < 15) continue;
       if (fabs(Muon_eta[j]) > 2.400) continue;

       if (Muon_tightId[j] == 0) continue;

       TLorentzVector tmp_muo;
       tmp_muo.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
       if (tmp_muo.DeltaR(tmp_pho_iso) < 0.4) skip = true;
     }

     if (skip) continue;

     if (ipho0_iso != -1) {
       TLorentzVector tmp_pho0_iso;
       tmp_pho0_iso.SetPtEtaPhiM(Photon_pt[ipho0_iso], Photon_eta[ipho0_iso], Photon_phi[ipho0_iso], Photon_mass[ipho0_iso]);
       if (tmp_pho0_iso.DeltaR(tmp_pho_iso) < 0.4) continue;
     }

     if (ipho1_iso != -1) {
       TLorentzVector tmp_pho1_iso;
       tmp_pho1_iso.SetPtEtaPhiM(Photon_pt[ipho1_iso], Photon_eta[ipho1_iso], Photon_phi[ipho1_iso], Photon_mass[ipho1_iso]);
       if (tmp_pho1_iso.DeltaR(tmp_pho_iso) < 0.4) continue;
     }

     if (ipho0_iso != -1) {
       if (Photon_pt[i] > Photon_pt[ipho0_iso]) {
         ipho1_iso = ipho0_iso;
         ipho0_iso = i;
       } else {
         if (ipho1_iso == -1) {
           ipho1_iso = i;
         } else {
           if (Photon_pt[i] > Photon_pt[ipho1_iso]) {
             ipho1_iso = i;
           }
         }
       }
     }
     if (ipho0_iso == -1) ipho0_iso = i;

     n_photons_iso++;
   }

   TLorentzVector pho0_iso;
   TLorentzVector pho1_iso;

   if (ipho0_iso != -1) {
     pho0_iso.SetPtEtaPhiM(Photon_pt[ipho0_iso], Photon_eta[ipho0_iso], Photon_phi[ipho0_iso], Photon_mass[ipho0_iso]);
   }
   if (ipho1_iso != -1) {
     pho1_iso.SetPtEtaPhiM(Photon_pt[ipho1_iso], Photon_eta[ipho1_iso], Photon_phi[ipho1_iso], Photon_mass[ipho1_iso]);
   }

   if (iele0 != -1 && iele1 == -1) {

     if (ipho0_iso != -1 && fabs((ele0+pho0_iso).M()-91.2) < 5) {
       ipho0_iso = -1;
       ipho1_iso = -1;
       n_photons_iso = n_photons_iso - 2;
     }
     if (ipho1_iso != -1 && fabs((ele0+pho1_iso).M()-91.2) < 5) {
       ipho1_iso = -1;
       n_photons_iso = n_photons_iso - 1;
     }
     if (ipho1_iso != -1 && fabs((ele0+pho0_iso+pho1_iso).M()-91.2) < 5) {
       ipho0_iso = -1;
       ipho1_iso = -1;
       n_photons_iso = n_photons_iso - 2;
     }

   }

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#if 0
   if (isZG || isWG) {

     bool match = false;

     for (uint i = 0; i < *nGenPart; i++) {
       if (GenPart_status[i] != 1) continue;
       if (fabs(GenPart_pdgId[i]) != 22) continue;
       if ((GenPart_statusFlags[i] & 1) != 1) continue;
       if (GenPart_pt[i] < 20) continue;
       if (fabs(GenPart_eta[i]) > 2.500) continue;

       TLorentzVector tmp_pho_gen_iso;
       tmp_pho_gen_iso.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);
       if (ipho0_iso != -1 && tmp_pho_gen_iso.DeltaR(pho0_iso) < 0.2) match = true;
     }

     if (ipho0_iso != -1 && !match) {
       ipho0_iso = -1;
       ipho1_iso = -1;
       n_photons_iso = n_photons_iso - 2;
     }

   }
#endif
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   bool is_pho0_iso = false;
   bool is_pho1_iso = false;

   if (ipho0_iso != -1) {
     if (iflag != 140 && Photon_Iso(Photon_vidNestedWPBitmap[ipho0_iso], 2) != 0) is_pho0_iso = true;
     if (iflag == 140 && Photon_Id_noIso(Photon_vidNestedWPBitmap[ipho0_iso], 2) != 0) is_pho0_iso = true;
   }
   if (ipho1_iso != -1) {
     if (iflag != 140 && Photon_Iso(Photon_vidNestedWPBitmap[ipho1_iso], 2) != 0) is_pho1_iso = true;
     if (iflag == 140 && Photon_Id_noIso(Photon_vidNestedWPBitmap[ipho1_iso], 2) != 0) is_pho1_iso = true;
   }

// photons cat

   int ipho0_cat = -1;
   int ipho1_cat = -1;

   float category2d = -1;

   TLorentzVector pho0_cat;
   TLorentzVector pho1_cat;

   for (uint i = 0; i < *nPhoton; i++) {
     float eCorr_pho = 1.;
     Photon_pt[i] = Photon_pt[i] * eCorr_pho;
     if (Photon_pt[i] < 20) continue;
     if (fabs(Photon_eta[i]) > 1.442 && fabs(Photon_eta[i]) < 1.566) continue;
     if (fabs(Photon_eta[i]) > 2.500) continue;

     //if (fabs(Photon_eta[i]) < 1.442) {
     //  if (Photon_mvaID[i] < -0.02) continue;
     //}
     //if (fabs(Photon_eta[i]) > 1.566 && fabs(Photon_eta[i]) < 2.500) {
     //  if (Photon_mvaID[i] < -0.26) continue;
     //}
     if (Photon_Id_noIso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     //if (Photon_electronVeto[i] == 0) continue;
     if (Photon_pixelSeed[i] != 0) continue;

     //if (Photon_pfRelIso03_all[i] > 0.15) continue;
     //if (Photon_Iso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     bool skip = false;

     TLorentzVector tmp_pho;
     tmp_pho.SetPtEtaPhiM(Photon_pt[i], Photon_eta[i], Photon_phi[i], Photon_mass[i]);

     if (iele0 != -1 && ele0.DeltaR(tmp_pho) < 0.4) continue;
     if (iele1 != -1 && ele1.DeltaR(tmp_pho) < 0.4) continue;

     if (imuo0 != -1 && muo0.DeltaR(tmp_pho) < 0.4) continue;
     if (imuo1 != -1 && muo1.DeltaR(tmp_pho) < 0.4) continue;

     for (uint j = 0; j < *nElectron; j++) {
       if (skip) continue;
       if (Electron_pt[j] < 15) continue;
       if (fabs(Electron_eta[j]) > 1.442 && fabs(Electron_eta[j]) < 1.566) continue;
       if (fabs(Electron_eta[j]) > 2.500) continue;

       if (fabs(Electron_eta[j]) < 1.442) {
         if (fabs(Electron_dxy[j]) > 0.05) continue;
         if (fabs(Electron_dz[j]) > 0.10) continue;
       }
       if (fabs(Electron_eta[j]) > 1.566 && fabs(Electron_eta[j]) < 2.500) {
         if (fabs(Electron_dxy[j]) > 0.10) continue;
         if (fabs(Electron_dz[j]) > 0.20) continue;
       }

       //if (Electron_mvaID_WP80[j] == 0) continue;
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[j], 4) == 0) continue;

       TLorentzVector tmp_ele;
       tmp_ele.SetPtEtaPhiM(Electron_pt[j], Electron_eta[j], Electron_phi[j], Electron_mass[j]);
       if (tmp_ele.DeltaR(tmp_pho) < 0.4) skip = true;
     }

     for (uint j = 0; j < *nMuon; j++) {
       if (skip) continue;
       if (Muon_pt[j] < 15) continue;
       if (fabs(Muon_eta[j]) > 2.400) continue;

       if (Muon_tightId[j] == 0) continue;

       TLorentzVector tmp_muo;
       tmp_muo.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
       if (tmp_muo.DeltaR(tmp_pho) < 0.4) skip = true;
     }

     if (skip) continue;

     if (ipho0_cat != -1) {
       TLorentzVector tmp_pho0;
       tmp_pho0.SetPtEtaPhiM(Photon_pt[ipho0_cat], Photon_eta[ipho0_cat], Photon_phi[ipho0_cat], Photon_mass[ipho0_cat]);
       if (tmp_pho0.DeltaR(tmp_pho) < 0.4) continue;
     }

     if (ipho1_cat != -1) {
       TLorentzVector tmp_pho1;
       tmp_pho1.SetPtEtaPhiM(Photon_pt[ipho1_cat], Photon_eta[ipho1_cat], Photon_phi[ipho1_cat], Photon_mass[ipho1_cat]);
       if (tmp_pho1.DeltaR(tmp_pho) < 0.4) continue;
     }

     if (ipho0_cat != -1) {
       if (Photon_pt[i] > Photon_pt[ipho0_cat]) {
         ipho1_cat = ipho0_cat;
         ipho0_cat = i;
       } else {
         if (ipho1_cat == -1) {
           ipho1_cat = i;
         } else {
           if (Photon_pt[i] > Photon_pt[ipho1_cat]) {
             ipho1_cat = i;
           }
         }
       }
     }
     if (ipho0_cat == -1) ipho0_cat = i;

   }

   if (ipho0_cat != -1) {
     pho0_cat.SetPtEtaPhiM(Photon_pt[ipho0_cat], Photon_eta[ipho0_cat], Photon_phi[ipho0_cat], Photon_mass[ipho0_cat]);
   }
   if (ipho1_cat != -1) {
     pho1_cat.SetPtEtaPhiM(Photon_pt[ipho1_cat], Photon_eta[ipho1_cat], Photon_phi[ipho1_cat], Photon_mass[ipho1_cat]);
   }

   if (iele0 != -1 && iele1 == -1) {

     if (ipho0_cat != -1 && fabs((ele0+pho0_cat).M()-91.2) < 5) {
       ipho0_cat = -1;
       ipho1_cat = -1;
     }
     if (ipho1_cat != -1 && fabs((ele0+pho1_cat).M()-91.2) < 5) {
       ipho1_cat = -1;
     }
     if (ipho1_cat != -1 && fabs((ele0+pho0_cat+pho1_cat).M()-91.2) < 5) {
       ipho0_cat = -1;
       ipho1_cat = -1;
     }

   }

   bool is_iso_pho0 = false;
   bool is_iso_pho1 = false;

   if (ipho0_cat != -1) {
     if (Photon_Iso(Photon_vidNestedWPBitmap[ipho0_cat], 2) != 0) is_iso_pho0 = true;
   }

   if (ipho1_cat != -1) {

     if (Photon_Iso(Photon_vidNestedWPBitmap[ipho1_cat], 2) != 0) is_iso_pho1 = true;

     if (is_iso_pho0 && is_iso_pho1) category2d = 0;

     if (ipho1 == -1) {

       if (!is_iso_pho0 && is_iso_pho1) category2d = 1;
       if (is_iso_pho0 && !is_iso_pho1) category2d = 2;
       if (!is_iso_pho0 && !is_iso_pho1) category2d = 3;

     }

   }

// photons QCD

   int n_photons_qcd = 0;
   int ipho0_qcd = -1;
   int ipho1_qcd = -1;
   int ipho0_fake_qcd = -1;

   for (uint i = 0; i < *nPhoton; i++) {
     if (Photon_pt[i] < 20) continue;
     if (fabs(Photon_eta[i]) > 1.442 && fabs(Photon_eta[i]) < 1.566) continue;
     if (fabs(Photon_eta[i]) > 2.500) continue;

     //if (fabs(Photon_eta[i]) < 1.442) {
     //  if (Photon_mvaID[i] < -0.02) continue;
     //}
     //if (fabs(Photon_eta[i]) > 1.566 && fabs(Photon_eta[i]) < 2.500) {
     //  if (Photon_mvaID[i] < -0.26) continue;
     //}
     if (Photon_Id_noIso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     //if (Photon_electronVeto[i] == 0) continue;
     if (Photon_pixelSeed[i] != 0) continue;

     //if (Photon_pfRelIso03_all[i] > 0.15) continue;
     if (Photon_Iso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     bool skip = false;

     TLorentzVector tmp_pho_qcd;
     tmp_pho_qcd.SetPtEtaPhiM(Photon_pt[i], Photon_eta[i], Photon_phi[i], Photon_mass[i]);

     if (iele0_qcd != -1 && ele0_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
     if (iele1_qcd != -1 && ele1_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;

     if (imuo0_qcd != -1 && muo0_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
     if (imuo1_qcd != -1 && muo1_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;

     for (uint j = 0; j < *nElectron; j++) {
       if (skip) continue;
       if (Electron_pt[j] < 15) continue;
       if (fabs(Electron_eta[j]) > 1.442 && fabs(Electron_eta[j]) < 1.566) continue;
       if (fabs(Electron_eta[j]) > 2.500) continue;

       if (fabs(Electron_eta[j]) < 1.442) {
         if (fabs(Electron_dxy[j]) > 0.05) continue;
         if (fabs(Electron_dz[j]) > 0.10) continue;
       }
       if (fabs(Electron_eta[j]) > 1.566 && fabs(Electron_eta[j]) < 2.500) {
         if (fabs(Electron_dxy[j]) > 0.10) continue;
         if (fabs(Electron_dz[j]) > 0.20) continue;
       }

       //if (Electron_mvaID_WP80[j] == 0) continue;
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[j], 4) == 0) continue;

       TLorentzVector tmp_ele;
       tmp_ele.SetPtEtaPhiM(Electron_pt[j], Electron_eta[j], Electron_phi[j], Electron_mass[j]);
       if (tmp_ele.DeltaR(tmp_pho_qcd) < 0.4) skip = true;
     }

     for (uint j = 0; j < *nMuon; j++) {
       if (skip) continue;
       if (Muon_pt[j] < 15) continue;
       if (fabs(Muon_eta[j]) > 2.400) continue;

       if (Muon_tightId[j] == 0) continue;

       TLorentzVector tmp_muo;
       tmp_muo.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
       if (tmp_muo.DeltaR(tmp_pho_qcd) < 0.4) skip = true;
     }

     if (skip) continue;

     if (ipho0_qcd != -1) {
       TLorentzVector tmp_pho0_qcd;
       tmp_pho0_qcd.SetPtEtaPhiM(Photon_pt[ipho0_qcd], Photon_eta[ipho0_qcd], Photon_phi[ipho0_qcd], Photon_mass[ipho0_qcd]);
       if (tmp_pho0_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
     }

     if (ipho1_qcd != -1) {
       TLorentzVector tmp_pho1_qcd;
       tmp_pho1_qcd.SetPtEtaPhiM(Photon_pt[ipho1_qcd], Photon_eta[ipho1_qcd], Photon_phi[ipho1_qcd], Photon_mass[ipho1_qcd]);
       if (tmp_pho1_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
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

   TLorentzVector pho0_qcd;
   TLorentzVector pho1_qcd;

   if (ipho0_qcd != -1) {
     pho0_qcd.SetPtEtaPhiM(Photon_pt[ipho0_qcd], Photon_eta[ipho0_qcd], Photon_phi[ipho0_qcd], Photon_mass[ipho0_qcd]);
   }
   if (ipho1_qcd != -1) {
     pho1_qcd.SetPtEtaPhiM(Photon_pt[ipho1_qcd], Photon_eta[ipho1_qcd], Photon_phi[ipho1_qcd], Photon_mass[ipho1_qcd]);
   }

   TLorentzVector pho0_fake_qcd;

   if (ipho0_qcd != -1 && ipho0_fake_qcd == -1) {
     ipho0_fake_qcd = ipho0_qcd;
     pho0_fake_qcd = pho0_qcd;
   }

   if (iele0_qcd != -1 && iele1_qcd == -1) {

     if (ipho0_qcd != -1 && fabs((ele0_qcd+pho0_qcd).M()-91.2) < 5) {
       ipho0_qcd = -1;
       ipho1_qcd = -1;
       n_photons_qcd = n_photons_qcd - 2;
     }
     if (ipho1_qcd != -1 && fabs((ele0_qcd+pho1_qcd).M()-91.2) < 5) {
       ipho1_qcd = -1;
       n_photons_qcd = n_photons_qcd - 1;
     }
     if (ipho1_qcd != -1 && fabs((ele0_qcd+pho0_qcd+pho1_qcd).M()-91.2) < 5) {
       ipho0_qcd = -1;
       ipho1_qcd = -1;
       n_photons_qcd = n_photons_qcd - 2;
     }

   }

// photons iso qcd

   int n_photons_iso_qcd = 0;
   int ipho0_iso_qcd = -1;
   int ipho1_iso_qcd = -1;

   for (uint i = 0; i < *nPhoton; i++) {
     if (Photon_pt[i] < 20) continue;
     if (fabs(Photon_eta[i]) > 1.442 && fabs(Photon_eta[i]) < 1.566) continue;
     if (fabs(Photon_eta[i]) > 2.500) continue;

     //if (fabs(Photon_eta[i]) < 1.442) {
     //  if (Photon_mvaID[i] < -0.02) continue;
     //}
     //if (fabs(Photon_eta[i]) > 1.566 && fabs(Photon_eta[i]) < 2.500) {
     //  if (Photon_mvaID[i] < -0.26) continue;
     //}
     //if (Photon_Id_noIso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;
     if (iflag != 140 && Photon_Id_noIso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;
     if (iflag == 140 && Photon_Id_noSieie(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     //if (Photon_electronVeto[i] == 0) continue;
     if (Photon_pixelSeed[i] != 0) continue;

     //if (Photon_pfRelIso03_all[i] > 0.15) continue;
     //if (Photon_Iso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     bool skip = false;

     TLorentzVector tmp_pho_iso_qcd;
     tmp_pho_iso_qcd.SetPtEtaPhiM(Photon_pt[i], Photon_eta[i], Photon_phi[i], Photon_mass[i]);

     if (iele0_qcd != -1 && ele0_qcd.DeltaR(tmp_pho_iso_qcd) < 0.4) continue;
     if (iele1_qcd != -1 && ele1_qcd.DeltaR(tmp_pho_iso_qcd) < 0.4) continue;

     if (imuo0_qcd != -1 && muo0_qcd.DeltaR(tmp_pho_iso_qcd) < 0.4) continue;
     if (imuo1_qcd != -1 && muo1_qcd.DeltaR(tmp_pho_iso_qcd) < 0.4) continue;

     for (uint j = 0; j < *nElectron; j++) {
       if (skip) continue;
       if (Electron_pt[j] < 15) continue;
       if (fabs(Electron_eta[j]) > 1.442 && fabs(Electron_eta[j]) < 1.566) continue;
       if (fabs(Electron_eta[j]) > 2.500) continue;

       if (fabs(Electron_eta[j]) < 1.442) {
         if (fabs(Electron_dxy[j]) > 0.05) continue;
         if (fabs(Electron_dz[j]) > 0.10) continue;
       }
       if (fabs(Electron_eta[j]) > 1.566 && fabs(Electron_eta[j]) < 2.500) {
         if (fabs(Electron_dxy[j]) > 0.10) continue;
         if (fabs(Electron_dz[j]) > 0.20) continue;
       }

       //if (Electron_mvaID_WP80[j] == 0) continue;
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[j], 4) == 0) continue;

       TLorentzVector tmp_ele;
       tmp_ele.SetPtEtaPhiM(Electron_pt[j], Electron_eta[j], Electron_phi[j], Electron_mass[j]);
       if (tmp_ele.DeltaR(tmp_pho_iso_qcd) < 0.4) skip = true;
     }

     for (uint j = 0; j < *nMuon; j++) {
       if (skip) continue;
       if (Muon_pt[j] < 15) continue;
       if (fabs(Muon_eta[j]) > 2.400) continue;

       if (Muon_tightId[j] == 0) continue;

       TLorentzVector tmp_muo;
       tmp_muo.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
       if (tmp_muo.DeltaR(tmp_pho_iso_qcd) < 0.4) skip = true;
     }

     if (skip) continue;

     if (ipho0_iso_qcd != -1) {
       TLorentzVector tmp_pho0_iso_qcd;
       tmp_pho0_iso_qcd.SetPtEtaPhiM(Photon_pt[ipho0_iso_qcd], Photon_eta[ipho0_iso_qcd], Photon_phi[ipho0_iso_qcd], Photon_mass[ipho0_iso_qcd]);
       if (tmp_pho0_iso_qcd.DeltaR(tmp_pho_iso_qcd) < 0.4) continue;
     }

     if (ipho1_iso_qcd != -1) {
       TLorentzVector tmp_pho1_iso_qcd;
       tmp_pho1_iso_qcd.SetPtEtaPhiM(Photon_pt[ipho1_iso_qcd], Photon_eta[ipho1_iso_qcd], Photon_phi[ipho1_iso_qcd], Photon_mass[ipho1_iso_qcd]);
       if (tmp_pho1_iso_qcd.DeltaR(tmp_pho_iso_qcd) < 0.4) continue;
     }

     if (ipho0_iso_qcd != -1) {
       if (Photon_pt[i] > Photon_pt[ipho0_iso_qcd]) {
         ipho1_iso_qcd = ipho0_iso_qcd;
         ipho0_iso_qcd = i;
       } else {
         if (ipho1_iso_qcd == -1) {
           ipho1_iso_qcd = i;
         } else {
           if (Photon_pt[i] > Photon_pt[ipho1_iso_qcd]) {
             ipho1_iso_qcd = i;
           }
         }
       }
     }
     if (ipho0_iso_qcd == -1) ipho0_iso_qcd = i;

     n_photons_iso_qcd++;
   }

   TLorentzVector pho0_iso_qcd;
   TLorentzVector pho1_iso_qcd;

   if (ipho0_iso_qcd != -1) {
     pho0_iso_qcd.SetPtEtaPhiM(Photon_pt[ipho0_iso_qcd], Photon_eta[ipho0_iso_qcd], Photon_phi[ipho0_iso_qcd], Photon_mass[ipho0_iso_qcd]);
   }
   if (ipho1_iso_qcd != -1) {
     pho1_iso_qcd.SetPtEtaPhiM(Photon_pt[ipho1_iso_qcd], Photon_eta[ipho1_iso_qcd], Photon_phi[ipho1_iso_qcd], Photon_mass[ipho1_iso_qcd]);
   }

   if (iele0_qcd != -1 && iele1_qcd == -1) {

     if (ipho0_iso_qcd != -1 && fabs((ele0_qcd+pho0_iso_qcd).M()-91.2) < 5) {
       ipho0_iso_qcd = -1;
       ipho1_iso_qcd = -1;
       n_photons_iso_qcd = n_photons_iso_qcd - 2;
     }
     if (ipho1_iso_qcd != -1 && fabs((ele0_qcd+pho1_iso_qcd).M()-91.2) < 5) {
       ipho1_iso_qcd = -1;
       n_photons_iso_qcd = n_photons_iso_qcd - 1;
     }
     if (ipho1_iso_qcd != -1 && fabs((ele0_qcd+pho0_iso_qcd+pho1_iso_qcd).M()-91.2) < 5) {
       ipho0_iso_qcd = -1;
       ipho1_iso_qcd = -1;
       n_photons_iso_qcd = n_photons_iso_qcd - 2;
     }

   }

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#if 0
   if (isZG || isWG) {

     bool match = false;

     for (uint i = 0; i < *nGenPart; i++) {
       if (GenPart_status[i] != 1) continue;
       if (fabs(GenPart_pdgId[i]) != 22) continue;
       if ((GenPart_statusFlags[i] & 1) != 1) continue;
       if (GenPart_pt[i] < 20) continue;
       if (fabs(GenPart_eta[i]) > 2.500) continue;

       TLorentzVector tmp_pho_gen_iso_qcd;
       tmp_pho_gen_iso_qcd.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);
       if (ipho0_iso_qcd != -1 && tmp_pho_gen_iso_qcd.DeltaR(pho0_iso_qcd) < 0.2) match = true;
     }

     if (ipho0_iso_qcd != -1 && !match) {
       ipho0_iso_qcd = -1;
       ipho1_iso_qcd = -1;
       n_photons_iso_qcd = n_photons_iso_qcd - 2;
     }

   }
#endif
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   bool is_pho0_iso_qcd = false;
   bool is_pho1_iso_qcd = false;

   if (ipho0_iso_qcd != -1) {
     if (iflag != 140 && Photon_Iso(Photon_vidNestedWPBitmap[ipho0_iso_qcd], 2) != 0) is_pho0_iso_qcd = true;
     if (iflag == 140 && Photon_Id_noIso(Photon_vidNestedWPBitmap[ipho0_iso_qcd], 2) != 0) is_pho0_iso_qcd = true;
   }
   if (ipho1_iso_qcd != -1) {
     if (iflag != 140 && Photon_Iso(Photon_vidNestedWPBitmap[ipho1_iso_qcd], 2) != 0) is_pho1_iso_qcd = true;
     if (iflag == 140 && Photon_Id_noIso(Photon_vidNestedWPBitmap[ipho1_iso_qcd], 2) != 0) is_pho1_iso_qcd = true;
   }

// photons cat QCD

   int ipho0_cat_qcd = -1;
   int ipho1_cat_qcd = -1;

   float category2d_qcd = -1;

   TLorentzVector pho0_cat_qcd;
   TLorentzVector pho1_cat_qcd;

   for (uint i = 0; i < *nPhoton; i++) {
     float eCorr_pho = 1.;
     Photon_pt[i] = Photon_pt[i] * eCorr_pho;
     if (Photon_pt[i] < 20) continue;
     if (fabs(Photon_eta[i]) > 1.442 && fabs(Photon_eta[i]) < 1.566) continue;
     if (fabs(Photon_eta[i]) > 2.500) continue;

     //if (fabs(Photon_eta[i]) < 1.442) {
     //  if (Photon_mvaID[i] < -0.02) continue;
     //}
     //if (fabs(Photon_eta[i]) > 1.566 && fabs(Photon_eta[i]) < 2.500) {
     //  if (Photon_mvaID[i] < -0.26) continue;
     //}
     if (Photon_Id_noIso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     //if (Photon_electronVeto[i] == 0) continue;
     if (Photon_pixelSeed[i] != 0) continue;

     //if (Photon_pfRelIso03_all[i] > 0.15) continue;
     //if (Photon_Iso(Photon_vidNestedWPBitmap[i], 2) == 0) continue;

     bool skip = false;

     TLorentzVector tmp_pho_qcd;
     tmp_pho_qcd.SetPtEtaPhiM(Photon_pt[i], Photon_eta[i], Photon_phi[i], Photon_mass[i]);

     if (iele0_qcd != -1 && ele0_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
     if (iele1_qcd != -1 && ele1_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;

     if (imuo0_qcd != -1 && muo0_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
     if (imuo1_qcd != -1 && muo1_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;

     for (uint j = 0; j < *nElectron; j++) {
       if (skip) continue;
       if (Electron_pt[j] < 15) continue;
       if (fabs(Electron_eta[j]) > 1.442 && fabs(Electron_eta[j]) < 1.566) continue;
       if (fabs(Electron_eta[j]) > 2.500) continue;

       if (fabs(Electron_eta[j]) < 1.442) {
         if (fabs(Electron_dxy[j]) > 0.05) continue;
         if (fabs(Electron_dz[j]) > 0.10) continue;
       }
       if (fabs(Electron_eta[j]) > 1.566 && fabs(Electron_eta[j]) < 2.500) {
         if (fabs(Electron_dxy[j]) > 0.10) continue;
         if (fabs(Electron_dz[j]) > 0.20) continue;
       }

       //if (Electron_mvaID_WP80[j] == 0) continue;
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[j], 4) == 0) continue;

       TLorentzVector tmp_ele;
       tmp_ele.SetPtEtaPhiM(Electron_pt[j], Electron_eta[j], Electron_phi[j], Electron_mass[j]);
       if (tmp_ele.DeltaR(tmp_pho_qcd) < 0.4) skip = true;
     }

     for (uint j = 0; j < *nMuon; j++) {
       if (skip) continue;
       if (Muon_pt[j] < 15) continue;
       if (fabs(Muon_eta[j]) > 2.400) continue;

       if (Muon_tightId[j] == 0) continue;

       TLorentzVector tmp_muo;
       tmp_muo.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
       if (tmp_muo.DeltaR(tmp_pho_qcd) < 0.4) skip = true;
     }

     if (skip) continue;

     if (ipho0_cat_qcd != -1) {
       TLorentzVector tmp_pho0_qcd;
       tmp_pho0_qcd.SetPtEtaPhiM(Photon_pt[ipho0_cat_qcd], Photon_eta[ipho0_cat_qcd], Photon_phi[ipho0_cat_qcd], Photon_mass[ipho0_cat_qcd]);
       if (tmp_pho0_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
     }

     if (ipho1_cat_qcd != -1) {
       TLorentzVector tmp_pho1_qcd;
       tmp_pho1_qcd.SetPtEtaPhiM(Photon_pt[ipho1_cat_qcd], Photon_eta[ipho1_cat_qcd], Photon_phi[ipho1_cat_qcd], Photon_mass[ipho1_cat_qcd]);
       if (tmp_pho1_qcd.DeltaR(tmp_pho_qcd) < 0.4) continue;
     }

     if (ipho0_cat_qcd != -1) {
       if (Photon_pt[i] > Photon_pt[ipho0_cat_qcd]) {
         ipho1_cat_qcd = ipho0_cat_qcd;
         ipho0_cat_qcd = i;
       } else {
         if (ipho1_cat_qcd == -1) {
           ipho1_cat_qcd = i;
         } else {
           if (Photon_pt[i] > Photon_pt[ipho1_cat_qcd]) {
             ipho1_cat_qcd = i;
           }
         }
       }
     }
     if (ipho0_cat_qcd == -1) ipho0_cat_qcd = i;

   }

   if (ipho0_cat_qcd != -1) {
     pho0_cat_qcd.SetPtEtaPhiM(Photon_pt[ipho0_cat_qcd], Photon_eta[ipho0_cat_qcd], Photon_phi[ipho0_cat_qcd], Photon_mass[ipho0_cat_qcd]);
   }
   if (ipho1_cat_qcd != -1) {
     pho1_cat_qcd.SetPtEtaPhiM(Photon_pt[ipho1_cat_qcd], Photon_eta[ipho1_cat_qcd], Photon_phi[ipho1_cat_qcd], Photon_mass[ipho1_cat_qcd]);
   }

   if (iele0_qcd != -1 && iele1_qcd == -1) {

     if (ipho0_cat_qcd != -1 && fabs((ele0_qcd+pho0_cat_qcd).M()-91.2) < 5) {
       ipho0_cat_qcd = -1;
       ipho1_cat_qcd = -1;
     }
     if (ipho1_cat_qcd != -1 && fabs((ele0_qcd+pho1_cat_qcd).M()-91.2) < 5) {
       ipho1_cat_qcd = -1;
     }
     if (ipho1_cat_qcd != -1 && fabs((ele0_qcd+pho0_cat_qcd+pho1_cat_qcd).M()-91.2) < 5) {
       ipho0_cat_qcd = -1;
       ipho1_cat_qcd = -1;
     }

   }

   bool is_iso_pho0_qcd = false;
   bool is_iso_pho1_qcd = false;

   if (ipho0_cat_qcd != -1) {
     if (Photon_Iso(Photon_vidNestedWPBitmap[ipho0_cat_qcd], 2) != 0) is_iso_pho0_qcd = true;
   }

   if (ipho1_cat_qcd != -1) {

     if (Photon_Iso(Photon_vidNestedWPBitmap[ipho1_cat_qcd], 2) != 0) is_iso_pho1_qcd = true;

     if (is_iso_pho0_qcd && is_iso_pho1_qcd) category2d_qcd = 0;

     if (ipho1 == -1) {

       if (!is_iso_pho0_qcd && is_iso_pho1_qcd) category2d_qcd = 1;
       if (is_iso_pho0_qcd && !is_iso_pho1_qcd) category2d_qcd = 2;
       if (!is_iso_pho0_qcd && !is_iso_pho1_qcd) category2d_qcd = 3;

     }

   }

// jets & MET

   int n_jets = 0;
   int ijet0 = -1;

   float met_px = *MET_pt * TMath::Cos(*MET_phi);
   float met_py = *MET_pt * TMath::Sin(*MET_phi);

   for (uint i = 0; i < *nJet; i++) {

     float jet_pt_ref = Jet_pt[i];

#if defined(__linux__)
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)
     if (Jet_pt[i] > 10 && fabs(Jet_eta[i]) < 5.2) {
       jet_correction_unc->setJetPt(Jet_pt[i]);
       jet_correction_unc->setJetEta(Jet_eta[i]);
       float jet_unc = jet_correction_unc->getUncertainty(true);

       int jec_var = 0;
#if defined(mainSelectorDT16_cxx)
       jec_var = (iflag == 31) - (iflag == 36);
#endif // defined(mainSelectorDT16_cxx)
#if defined(mainSelectorDT17_cxx)
       jec_var = (iflag == 32) - (iflag == 37);
#endif // defined(mainSelectorDT17_cxx)
#if defined(mainSelectorDT18_cxx)
       jec_var = (iflag == 33) - (iflag == 38);
#endif // defined(mainSelectorDT18_cxx)

       Jet_pt[i] = Jet_pt[i] * (1. + jet_unc * jec_var);
     }
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorDT17_cxx) || defined(mainSelectorDT18_cxx)

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
       if (tmp_jet.DeltaR(tmp_jet_gen) < 0.2 && fabs(tmp_jet.Pt() - tmp_jet_gen.Pt()) < 3. * jet_resolution->getResolution(jer_parameters) * tmp_jet.Pt())  {
         jet_match = true;
       }
     }

     Variation jer_var = Variation::NOMINAL;
#if defined(mainSelectorMC16_cxx)
     if (iflag == 21) jer_var = Variation::UP;
     if (iflag == 26) jer_var = Variation::DOWN;
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
     if (iflag == 22) jer_var = Variation::UP;
     if (iflag == 27) jer_var = Variation::DOWN;
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
     if (iflag == 23) jer_var = Variation::UP;
     if (iflag == 28) jer_var = Variation::DOWN;
#endif // defined(mainSelectorMC18_cxx)

     float jet_smear = 1.;
     if (jet_match) {
       jet_smear = 1. + (jet_resolution_sf->getScaleFactor(jer_parameters, jer_var) - 1.) * (Jet_pt[i] - GenJet_pt[Jet_genJetIdx[i]]) / Jet_pt[i];
     } else {
       jet_smear = 1. + gRandom->Gaus(0., jet_resolution->getResolution(jer_parameters)) * TMath::Sqrt(TMath::Max(TMath::Power(jet_resolution_sf->getScaleFactor(jer_parameters, jer_var), 2) - 1., 0.));
     }

     if (Jet_pt[i] * jet_smear < 0.01) jet_smear = 0.01 / Jet_pt[i];

     if (!TMath::Finite(Jet_muonSubtrFactor[i])) Jet_muonSubtrFactor[i] = 0.;

     Jet_pt[i] = Jet_pt[i] * (1. - Jet_muonSubtrFactor[i]) * jet_smear + Jet_pt[i] * Jet_muonSubtrFactor[i];
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#endif // defined(__linux__)

     if (Jet_pt[i] > 15 && (Jet_chEmEF[i] + Jet_neEmEF[i]) < 0.9) {
       met_px = met_px - (Jet_pt[i] - jet_pt_ref) * TMath::Cos(Jet_phi[i]);
       met_py = met_py - (Jet_pt[i] - jet_pt_ref) * TMath::Sin(Jet_phi[i]);
     }

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

   *MET_pt = TMath::Sqrt(TMath::Power(met_px, 2) + TMath::Power(met_py, 2));
   *MET_phi = TMath::ATan2(met_py, met_px);

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

   float W_ele0_mt = 0.;

   if (iele0 != -1 && iele1 == -1 && imuo0 == -1 && iele0_qcd == -1 && imuo0_qcd == -1) {
     if (iflag == 150) {
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[iele0], 4) == 0) ele0.SetPtEtaPhiM(0., ele0.Eta(), ele0.Phi(), ele0.M());
       if (Electron_Iso(Electron_vidNestedWPBitmap[iele0], 4) == 0) ele0.SetPtEtaPhiM(0., ele0.Eta(), ele0.Phi(), ele0.M());
     }
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_Ele27_WPTight_Gsf) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_Ele32_WPTight_Gsf_L1DoubleEG) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Ele32_WPTight_Gsf) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       W_ele0_mt = TMath::Sqrt(2. * ele0.Pt() * (*MET_pt) * (1. - TMath::Cos(ele0.Phi() - (*MET_phi))));
       if (*MET_pt > 0 && W_ele0_mt > 0 && ele0.Pt() > 35) {
         W_ele_sel = true;
       }
     }
   }

// W -> ele nu QCD

   bool W_ele_sel_qcd = false;

   float W_ele0_mt_qcd = 0.;

   if (iele0_qcd != -1 && iele1_qcd == -1 && imuo0_qcd == -1 && iele0 == -1 && imuo0 == -1) {
     if (iflag == 150) {
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[iele0_qcd], 4) == 0) ele0_qcd.SetPtEtaPhiM(0., ele0_qcd.Eta(), ele0_qcd.Phi(), ele0_qcd.M());
       if (Electron_Iso(Electron_vidNestedWPBitmap[iele0_qcd], 4) != 0) ele0_qcd.SetPtEtaPhiM(0., ele0_qcd.Eta(), ele0_qcd.Phi(), ele0_qcd.M());
     }
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_Ele27_WPTight_Gsf) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_Ele32_WPTight_Gsf_L1DoubleEG) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Ele32_WPTight_Gsf) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       W_ele0_mt_qcd = TMath::Sqrt(2. * ele0_qcd.Pt() * (*MET_pt) * (1. - TMath::Cos(ele0_qcd.Phi() - (*MET_phi))));
       if (*MET_pt > 0 && W_ele0_mt_qcd > 0 && ele0_qcd.Pt() > 35) {
         W_ele_sel_qcd = true;
       }
     }
   }

// W -> muo nu

   bool W_muo_sel = false;

   float W_muo0_mt = 0.;

   if (imuo0 != -1 && imuo1 == -1 && iele0 == -1 && iele0_qcd == -1 && imuo0_qcd == -1) {
     if (iflag == 155) {
       if (Muon_tightId[imuo0] == 0) muo0.SetPtEtaPhiM(0., muo0.Eta(), muo0.Phi(), muo0.M());
     }
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
         W_muo_sel = true;
       }
     }
   }

// W -> muo nu QCD

   bool W_muo_sel_qcd = false;

   float W_muo0_mt_qcd = 0.;

   if (imuo0_qcd != -1 && imuo1_qcd == -1 && iele0_qcd == -1 && iele0 == -1 && imuo0 == -1) {
     if (iflag == 155) {
       if (Muon_tightId[imuo0_qcd] == 0) muo0_qcd.SetPtEtaPhiM(0., muo0_qcd.Eta(), muo0_qcd.Phi(), muo0_qcd.M());
     }
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
         W_muo_sel_qcd = true;
       }
     }
   }

// Z -> ele ele

   bool Z_ele_sel = false;

   float Z_ele0_ele1_m = 0.;

   if (iele0 != -1 && iele1 != -1) {
     if (iflag == 150) {
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[iele0], 4) == 0) ele0.SetPtEtaPhiM(0., ele0.Eta(), ele0.Phi(), ele0.M());
       if (Electron_Iso(Electron_vidNestedWPBitmap[iele0], 4) == 0) ele0.SetPtEtaPhiM(0., ele0.Eta(), ele0.Phi(), ele0.M());
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[iele1], 4) == 0) ele1.SetPtEtaPhiM(0., ele1.Eta(), ele1.Phi(), ele1.M());
       if (Electron_Iso(Electron_vidNestedWPBitmap[iele1], 4) == 0) ele1.SetPtEtaPhiM(0., ele1.Eta(), ele1.Phi(), ele1.M());
     }
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_Ele27_WPTight_Gsf) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_Ele32_WPTight_Gsf_L1DoubleEG) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Ele32_WPTight_Gsf) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       Z_ele0_ele1_m = (ele0 + ele1).M();
       if (Z_ele0_ele1_m >= 55. && (ele0.Pt() > 35 || ele1.Pt() > 35)) {
         Z_ele_sel = true;
       }
     }
   }

// Z -> ele ele QCD

   bool Z_ele_sel_qcd = false;

   float Z_ele0_ele1_m_qcd = 0.;

   if (iele0_qcd != -1 && iele1_qcd != -1) {
     if (iflag == 150) {
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[iele0_qcd], 4) == 0) ele0_qcd.SetPtEtaPhiM(0., ele0_qcd.Eta(), ele0_qcd.Phi(), ele0_qcd.M());
       if (Electron_Iso(Electron_vidNestedWPBitmap[iele0_qcd], 4) != 0) ele0_qcd.SetPtEtaPhiM(0., ele0_qcd.Eta(), ele0_qcd.Phi(), ele0_qcd.M());
       if (Electron_Id_noIso(Electron_vidNestedWPBitmap[iele1_qcd], 4) == 0) ele1_qcd.SetPtEtaPhiM(0., ele1_qcd.Eta(), ele1_qcd.Phi(), ele1_qcd.M());
       if (Electron_Iso(Electron_vidNestedWPBitmap[iele1_qcd], 4) != 0) ele1_qcd.SetPtEtaPhiM(0., ele1_qcd.Eta(), ele1_qcd.Phi(), ele1_qcd.M());
     }
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_Ele27_WPTight_Gsf) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_Ele32_WPTight_Gsf_L1DoubleEG) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_Ele32_WPTight_Gsf) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       Z_ele0_ele1_m_qcd = (ele0_qcd + ele1_qcd).M();
       if (Z_ele0_ele1_m_qcd >= 55. && (ele0_qcd.Pt() > 35 || ele1_qcd.Pt() > 35)) {
         Z_ele_sel_qcd = true;
       }
     }
   }

// Z -> muo muo

   bool Z_muo_sel = false;

   float Z_muo0_muo1_m = 0.;

   if (imuo0 != -1 && imuo1 != -1) {
     if (iflag == 155) {
       if (Muon_tightId[imuo0] == 0) muo0.SetPtEtaPhiM(0., muo0.Eta(), muo0.Phi(), muo0.M());
       if (Muon_tightId[imuo1] == 0) muo1.SetPtEtaPhiM(0., muo1.Eta(), muo1.Phi(), muo1.M());
     }
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_IsoMu24 || *HLT_IsoTkMu24) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_IsoMu24 || *HLT_IsoMu27) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_IsoMu24) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       Z_muo0_muo1_m = (muo0 + muo1).M();
       if (Z_muo0_muo1_m >= 55. && (muo0.Pt() > 30 || muo1.Pt() > 30)) {
         Z_muo_sel = true;
       }
     }
   }

// Z -> muo muo QCD

   bool Z_muo_sel_qcd = false;

   float Z_muo0_muo1_m_qcd = 0.;

   if (imuo0_qcd != -1 && imuo1_qcd != -1) {
     if (iflag == 155) {
       if (Muon_tightId[imuo0_qcd] == 0) muo0_qcd.SetPtEtaPhiM(0., muo0_qcd.Eta(), muo0_qcd.Phi(), muo0_qcd.M());
       if (Muon_tightId[imuo1_qcd] == 0) muo1_qcd.SetPtEtaPhiM(0., muo1_qcd.Eta(), muo1_qcd.Phi(), muo1_qcd.M());
     }
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
     if (*HLT_IsoMu24 || *HLT_IsoTkMu24) {
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
     if (*HLT_IsoMu24 || *HLT_IsoMu27) {
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
     if (*HLT_IsoMu24) {
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       Z_muo0_muo1_m_qcd = (muo0_qcd + muo1_qcd).M();
       if (Z_muo0_muo1_m_qcd >= 55. && (muo0_qcd.Pt() > 30 || muo1_qcd.Pt() > 30)) {
         Z_muo_sel_qcd = true;
       }
     }
   }

// electron(s) scale factors

   float weight_eff_ele0 = 1.;
   float weight_reco_ele0 = 1.;
   float weight_trig_ele0 = 1.;

   float weight_eff_ele1 = 1.;
   float weight_reco_ele1 = 1.;
   float weight_trig_ele1 = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (iele0 != -1) {
     weight_eff_ele0 = getWeight(sf_ele_eff, Electron_eta[iele0], Electron_pt[iele0], (iflag == 40) - (iflag == 45));
     weight_reco_ele0 = getWeight(sf_ele_reco, Electron_eta[iele0], Electron_pt[iele0], (iflag == 50) - (iflag == 55));
     weight_trig_ele0 = getWeight(sf_ele_trig, Electron_eta[iele0], Electron_pt[iele0], (iflag == 60) - (iflag == 65));
   }
   if (iele1 != -1) {
     weight_eff_ele1 = getWeight(sf_ele_eff, Electron_eta[iele1], Electron_pt[iele1], (iflag == 40) - (iflag == 45));
     weight_reco_ele1 = getWeight(sf_ele_reco, Electron_eta[iele1], Electron_pt[iele1], (iflag == 50) - (iflag == 55));
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_hlt_ele = 1.;

#if defined(mainSelectorMC17_cxx)
   weight_hlt_ele = 0.991 + ((iflag == 60) - (iflag == 65)) * 0.001;
#endif // defined(mainSelectorMC17_cxx)

// electron(s) scale factors QCD

   float weight_eff_ele0_qcd = 1.;
   float weight_reco_ele0_qcd = 1.;
   float weight_trig_ele0_qcd = 1.;

   float weight_eff_ele1_qcd = 1.;
   float weight_reco_ele1_qcd = 1.;
   float weight_trig_ele1_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (iele0_qcd != -1) {
     weight_eff_ele0_qcd = getWeight(sf_ele_eff, Electron_eta[iele0_qcd], Electron_pt[iele0_qcd], (iflag == 40) - (iflag == 45));
     weight_reco_ele0_qcd = getWeight(sf_ele_reco, Electron_eta[iele0_qcd], Electron_pt[iele0_qcd], (iflag == 50) - (iflag == 55));
     weight_trig_ele0_qcd = getWeight(sf_ele_trig, Electron_eta[iele0_qcd], Electron_pt[iele0_qcd], (iflag == 60) - (iflag == 65));
   }
   if (iele1_qcd != -1) {
     weight_eff_ele1_qcd = getWeight(sf_ele_eff, Electron_eta[iele1_qcd], Electron_pt[iele1_qcd], (iflag == 40) - (iflag == 45));
     weight_reco_ele1_qcd = getWeight(sf_ele_reco, Electron_eta[iele1_qcd], Electron_pt[iele1_qcd], (iflag == 50) - (iflag == 55));
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_hlt_ele_qcd = 1.;

#if defined(mainSelectorMC17_cxx)
   weight_hlt_ele_qcd = 0.991 + ((iflag == 60) - (iflag == 65)) * 0.001;
#endif // defined(mainSelectorMC17_cxx)

// muon(s) scale factors

   float weight_trig_muo0 = 1.;
   float weight_id_muo0 = 1.;
   float weight_iso_muo0 = 1.;

   float weight_trig_muo1 = 1.;
   float weight_id_muo1 = 1.;
   float weight_iso_muo1 = 1.;

#if defined(mainSelectorMC16_cxx)
   if (imuo0 != -1) {
     weight_trig_muo0 = getWeight(sf_muo_trig, Muon_pt[imuo0], fabs(Muon_eta[imuo0]), (iflag == 90) - (iflag == 95));
     weight_id_muo0 = getWeight(sf_muo_id, Muon_eta[imuo0], Muon_pt[imuo0], (iflag == 70) - (iflag == 75));
     weight_iso_muo0 = getWeight(sf_muo_iso, Muon_eta[imuo0], Muon_pt[imuo0], (iflag == 80) - (iflag == 85));
   }
   if (imuo1 != -1) {
     weight_id_muo1 = getWeight(sf_muo_id, Muon_eta[imuo1], Muon_pt[imuo1], (iflag == 70) - (iflag == 75));
     weight_iso_muo1 = getWeight(sf_muo_iso, Muon_eta[imuo1], Muon_pt[imuo1], (iflag == 80) - (iflag == 85));
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (imuo0 != -1) {
     weight_trig_muo0 = getWeight(sf_muo_trig, Muon_pt[imuo0], fabs(Muon_eta[imuo0]), (iflag == 90) - (iflag == 95));
     weight_id_muo0 = getWeight(sf_muo_id, Muon_pt[imuo0], fabs(Muon_eta[imuo0]), (iflag == 70) - (iflag == 75));
     weight_iso_muo0 = getWeight(sf_muo_iso, Muon_pt[imuo0], fabs(Muon_eta[imuo0]), (iflag == 80) - (iflag == 85));
   }
   if (imuo1 != -1) {
     weight_id_muo1 = getWeight(sf_muo_id, Muon_pt[imuo1], fabs(Muon_eta[imuo1]), (iflag == 70) - (iflag == 75));
     weight_iso_muo1 = getWeight(sf_muo_iso, Muon_pt[imuo1], fabs(Muon_eta[imuo1]), (iflag == 80) - (iflag == 85));
   }
#endif // defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

// muon(s) scale factors QCD

   float weight_trig_muo0_qcd = 1.;
   float weight_id_muo0_qcd = 1.;
   float weight_iso_muo0_qcd = 1.;

   float weight_trig_muo1_qcd = 1.;
   float weight_id_muo1_qcd = 1.;
   float weight_iso_muo1_qcd = 1.;

#if defined(mainSelectorMC16_cxx)
   if (imuo0_qcd != -1) {
     weight_trig_muo0_qcd = getWeight(sf_muo_trig, Muon_pt[imuo0_qcd], fabs(Muon_eta[imuo0_qcd]), (iflag == 90) - (iflag == 95));
     weight_id_muo0_qcd = getWeight(sf_muo_id, Muon_eta[imuo0_qcd], Muon_pt[imuo0_qcd], (iflag == 70) - (iflag == 75));
     weight_iso_muo0_qcd = getWeight(sf_muo_iso, Muon_eta[imuo0_qcd], Muon_pt[imuo0_qcd], (iflag == 80) - (iflag == 85));
   }
   if (imuo1_qcd != -1) {
     weight_id_muo1_qcd = getWeight(sf_muo_id, Muon_eta[imuo1_qcd], Muon_pt[imuo1_qcd], (iflag == 70) - (iflag == 75));
     weight_iso_muo1_qcd = getWeight(sf_muo_iso, Muon_eta[imuo1_qcd], Muon_pt[imuo1_qcd], (iflag == 80) - (iflag == 85));
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (imuo0_qcd != -1) {
     weight_trig_muo0_qcd = getWeight(sf_muo_trig, Muon_pt[imuo0_qcd], fabs(Muon_eta[imuo0_qcd]), (iflag == 90) - (iflag == 95));
     weight_id_muo0_qcd = getWeight(sf_muo_id, Muon_pt[imuo0_qcd], fabs(Muon_eta[imuo0_qcd]), (iflag == 70) - (iflag == 75));
     weight_iso_muo0_qcd = getWeight(sf_muo_iso, Muon_pt[imuo0_qcd], fabs(Muon_eta[imuo0_qcd]), (iflag == 80) - (iflag == 85));
   }
   if (imuo1_qcd != -1) {
     weight_id_muo1_qcd = getWeight(sf_muo_id, Muon_pt[imuo1_qcd], fabs(Muon_eta[imuo1_qcd]), (iflag == 70) - (iflag == 75));
     weight_iso_muo1_qcd = getWeight(sf_muo_iso, Muon_pt[imuo1_qcd], fabs(Muon_eta[imuo1_qcd]), (iflag == 80) - (iflag == 85));
   }
#endif // defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

// photon(s) scale factors

   float weight_eff_pho0 = 1.;
   float weight_reco_pho0 = 1.;

   float weight_eff_pho1 = 1.;
   float weight_reco_pho1 = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0 != -1) {
     weight_eff_pho0 = getWeight(sf_pho_eff, Photon_eta[ipho0], Photon_pt[ipho0], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11) {
         weight_eff_pho0 = getWeight(sf_pho_eff, Photon_eta[ipho0], Photon_pt[ipho0]);
       }
     }
   }
   if (ipho1 != -1) {
     weight_eff_pho1 = getWeight(sf_pho_eff, Photon_eta[ipho1], Photon_pt[ipho1], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 11) {
         weight_eff_pho1 = getWeight(sf_pho_eff, Photon_eta[ipho1], Photon_pt[ipho1]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_ele_veto_pho0 = 1.;
   float weight_ele_veto_pho1 = 1.;

#if defined(mainSelectorMC16_cxx)
   if (ipho0 != -1) {
     weight_ele_veto_pho0 = getWeight(Photon_eta[ipho0], Photon_r9[ipho0], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11) {
         weight_ele_veto_pho0 = getWeight(Photon_eta[ipho0], Photon_r9[ipho0]);
       }
     }
   }
   if (ipho1 != -1) {
     weight_ele_veto_pho1 = getWeight(Photon_eta[ipho1], Photon_r9[ipho1], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 11) {
         weight_ele_veto_pho1 = getWeight(Photon_eta[ipho1], Photon_r9[ipho1]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   if (ipho0 != -1) {
     weight_ele_veto_pho0 = getWeight(Photon_eta[ipho0], Photon_r9[ipho0], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11) {
         weight_ele_veto_pho0 = getWeight(Photon_eta[ipho0], Photon_r9[ipho0]);
       }
     }
   }
   if (ipho1 != -1) {
     weight_ele_veto_pho1 = getWeight(Photon_eta[ipho1], Photon_r9[ipho1], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 11) {
         weight_ele_veto_pho1 = getWeight(Photon_eta[ipho1], Photon_r9[ipho1], (iflag == 112) - (iflag == 117));
       }
     }
   }
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   if (ipho0 != -1) {
     weight_ele_veto_pho0 = getWeight(Photon_eta[ipho0], Photon_pt[ipho0], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11) {
         weight_ele_veto_pho0 = getWeight(Photon_eta[ipho0], Photon_pt[ipho0]);
       }
     }
   }
   if (ipho1 != -1) {
     weight_ele_veto_pho1 = getWeight(Photon_eta[ipho1], Photon_pt[ipho1], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 11) {
         weight_ele_veto_pho1 = getWeight(Photon_eta[ipho1], Photon_pt[ipho1]);
       }
     }
   }
#endif // defined(mainSelectorMC18_cxx)

   float weight_eg_misid_pho0 = 1.;
   float weight_eg_misid_pho1 = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)


   if (ipho0 != -1) {
     if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11) {
       weight_eg_misid_pho0 = getWeight(sf_eg_misid, fabs(Photon_eta[ipho0]), Photon_pt[ipho0], (iflag == 130) - (iflag == 135));
     }
   }

   if (ipho1 != -1) {
     if (Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 11) {
       weight_eg_misid_pho1 = getWeight(sf_eg_misid, fabs(Photon_eta[ipho1]), Photon_pt[ipho1], (iflag == 130) - (iflag == 135));
     }
   }

#if defined(COMPUTE_EG_MISID)
   weight_eg_misid_pho0 = 1.;
   weight_eg_misid_pho1 = 1.;
#endif // defined(COMPUTE_EG_MISID)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0 = weight_eff_pho0 * weight_reco_pho0 * weight_ele_veto_pho0 * weight_eg_misid_pho0;
   float weight_pho1 = weight_eff_pho1 * weight_reco_pho1 * weight_ele_veto_pho1 * weight_eg_misid_pho1;

// photon(s) scale factors iso

   float weight_eff_pho0_iso = 1.;
   float weight_reco_pho0_iso = 1.;

   float weight_eff_pho1_iso = 1.;
   float weight_reco_pho1_iso = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_iso != -1) {
     weight_eff_pho0_iso = getWeight(sf_pho_eff, Photon_eta[ipho0_iso], Photon_pt[ipho0_iso], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
         weight_eff_pho0_iso = getWeight(sf_pho_eff, Photon_eta[ipho0_iso], Photon_pt[ipho0_iso]);
       }
     }
   }
   if (ipho1_iso != -1) {
     weight_eff_pho1_iso = getWeight(sf_pho_eff, Photon_eta[ipho1_iso], Photon_pt[ipho1_iso], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11) {
         weight_eff_pho1_iso = getWeight(sf_pho_eff, Photon_eta[ipho1_iso], Photon_pt[ipho1_iso]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_ele_veto_pho0_iso = 1.;
   float weight_ele_veto_pho1_iso = 1.;

#if defined(mainSelectorMC16_cxx)
   if (ipho0_iso != -1) {
     weight_ele_veto_pho0_iso = getWeight(Photon_eta[ipho0_iso], Photon_r9[ipho0_iso], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
         weight_ele_veto_pho0_iso = getWeight(Photon_eta[ipho0_iso], Photon_r9[ipho0_iso]);
       }
     }
   }
   if (ipho1_iso != -1) {
     weight_ele_veto_pho1_iso = getWeight(Photon_eta[ipho1_iso], Photon_r9[ipho1_iso], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11) {
         weight_ele_veto_pho1_iso = getWeight(Photon_eta[ipho1_iso], Photon_r9[ipho1_iso]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   if (ipho0_iso != -1) {
     weight_ele_veto_pho0_iso = getWeight(Photon_eta[ipho0_iso], Photon_r9[ipho0_iso], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
         weight_ele_veto_pho0_iso = getWeight(Photon_eta[ipho0_iso], Photon_r9[ipho0_iso]);
       }
     }
   }
   if (ipho1_iso != -1) {
     weight_ele_veto_pho1_iso = getWeight(Photon_eta[ipho1_iso], Photon_r9[ipho1_iso], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11) {
         weight_ele_veto_pho1_iso = getWeight(Photon_eta[ipho1_iso], Photon_r9[ipho1_iso], (iflag == 112) - (iflag == 117));
       }
     }
   }
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   if (ipho0_iso != -1) {
     weight_ele_veto_pho0_iso = getWeight(Photon_eta[ipho0_iso], Photon_pt[ipho0_iso], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
         weight_ele_veto_pho0_iso = getWeight(Photon_eta[ipho0_iso], Photon_pt[ipho0_iso]);
       }
     }
   }
   if (ipho1_iso != -1) {
     weight_ele_veto_pho1_iso = getWeight(Photon_eta[ipho1_iso], Photon_pt[ipho1_iso], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11) {
         weight_ele_veto_pho1_iso = getWeight(Photon_eta[ipho1_iso], Photon_pt[ipho1_iso]);
       }
     }
   }
#endif // defined(mainSelectorMC18_cxx)

   float weight_eg_misid_pho0_iso = 1.;
   float weight_eg_misid_pho1_iso = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_iso != -1) {
     if (Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
       weight_eg_misid_pho0_iso = getWeight(sf_eg_misid, fabs(Photon_eta[ipho0_iso]), Photon_pt[ipho0_iso], (iflag == 130) - (iflag == 135));
     }
   }

   if (ipho1_iso != -1) {
     if (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11) {
       weight_eg_misid_pho1_iso = getWeight(sf_eg_misid, fabs(Photon_eta[ipho1_iso]), Photon_pt[ipho1_iso], (iflag == 130) - (iflag == 135));
     }
   }
#if defined(COMPUTE_EG_MISID)
   weight_eg_misid_pho0_iso = 1.;
   weight_eg_misid_pho1_iso = 1.;
#endif // defined(COMPUTE_EG_MISID)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0_iso = weight_eff_pho0_iso * weight_reco_pho0_iso * weight_ele_veto_pho0_iso * weight_eg_misid_pho0_iso;
   float weight_pho1_iso = weight_eff_pho1_iso * weight_reco_pho1_iso * weight_ele_veto_pho1_iso * weight_eg_misid_pho1_iso;

// photon(s) fake scale factors

   float weight_eff_pho0_fake = 1.;
   float weight_reco_pho0_fake = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_fake != -1) {
     weight_eff_pho0_fake = getWeight(sf_pho_eff, Photon_eta[ipho0_fake], Photon_pt[ipho0_fake], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho0_fake] >= 0 && (uint)Photon_genPartIdx[ipho0_fake] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake]]) == 11) {
         weight_eff_pho0_fake = getWeight(sf_pho_eff, Photon_eta[ipho0_fake], Photon_pt[ipho0_fake]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_ele_veto_pho0_fake = 1.;

#if defined(mainSelectorMC16_cxx)
   if (ipho0_fake != -1) {
     weight_ele_veto_pho0_fake = getWeight(Photon_eta[ipho0_fake], Photon_r9[ipho0_fake], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho0_fake] >= 0 && (uint)Photon_genPartIdx[ipho0_fake] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake]]) == 11) {
         weight_ele_veto_pho0_fake = getWeight(Photon_eta[ipho0_fake], Photon_r9[ipho0_fake]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   if (ipho0_fake != -1) {
     weight_ele_veto_pho0_fake = getWeight(Photon_eta[ipho0_fake], Photon_r9[ipho0_fake], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho0_fake] >= 0 && (uint)Photon_genPartIdx[ipho0_fake] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake]]) == 11) {
         weight_ele_veto_pho0_fake = getWeight(Photon_eta[ipho0_fake], Photon_r9[ipho0_fake]);
       }
     }
   }
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   if (ipho0_fake != -1) {
     weight_ele_veto_pho0_fake = getWeight(Photon_eta[ipho0_fake], Photon_pt[ipho0_fake], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho0_fake] >= 0 && (uint)Photon_genPartIdx[ipho0_fake] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake]]) == 11) {
         weight_ele_veto_pho0_fake = getWeight(Photon_eta[ipho0_fake], Photon_pt[ipho0_fake]);
       }
     }
   }
#endif // defined(mainSelectorMC18_cxx)

   float weight_eg_misid_pho0_fake = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_fake != -1) {
     if (Photon_genPartIdx[ipho0_fake] >= 0 && (uint)Photon_genPartIdx[ipho0_fake] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake]]) == 11) {
       weight_eg_misid_pho0_fake = getWeight(sf_eg_misid, fabs(Photon_eta[ipho0_fake]), Photon_pt[ipho0_fake], (iflag == 130) - (iflag == 135));
     }
   }
#if defined(COMPUTE_EG_MISID)
   weight_eg_misid_pho0_fake = 1.;
#endif // defined(COMPUTE_EG_MISID)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0_fake = weight_eff_pho0_fake * weight_reco_pho0_fake * weight_ele_veto_pho0_fake * weight_eg_misid_pho0_fake;

// photon(s) scale factors cat

   float weight_eff_pho0_cat = 1.;
   float weight_reco_pho0_cat = 1.;

   float weight_eff_pho1_cat = 1.;
   float weight_reco_pho1_cat = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_cat != -1) {
     weight_eff_pho0_cat = getWeight(sf_pho_eff, Photon_eta[ipho0_cat], Photon_pt[ipho0_cat], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho0_cat] >= 0 && (uint)Photon_genPartIdx[ipho0_cat] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_cat]]) == 11) {
         weight_eff_pho0_cat = getWeight(sf_pho_eff, Photon_eta[ipho0_cat], Photon_pt[ipho0_cat]);
       }
     }
   }
   if (ipho1_cat != -1) {
     weight_eff_pho1_cat = getWeight(sf_pho_eff, Photon_eta[ipho1_cat], Photon_pt[ipho1_cat], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho1_cat] >= 0 && (uint)Photon_genPartIdx[ipho1_cat] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_cat]]) == 11) {
         weight_eff_pho1_cat = getWeight(sf_pho_eff, Photon_eta[ipho1_cat], Photon_pt[ipho1_cat]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_ele_veto_pho0_cat = 1.;
   float weight_ele_veto_pho1_cat = 1.;

#if defined(mainSelectorMC16_cxx)
   if (ipho0_cat != -1) {
     weight_ele_veto_pho0_cat = getWeight(Photon_eta[ipho0_cat], Photon_r9[ipho0_cat], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho0_cat] >= 0 && (uint)Photon_genPartIdx[ipho0_cat] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_cat]]) == 11) {
         weight_ele_veto_pho0_cat = getWeight(Photon_eta[ipho0_cat], Photon_r9[ipho0_cat]);
       }
     }
   }
   if (ipho1_cat != -1) {
     weight_ele_veto_pho1_cat = getWeight(Photon_eta[ipho1_cat], Photon_r9[ipho1_cat], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho1_cat] >= 0 && (uint)Photon_genPartIdx[ipho1_cat] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_cat]]) == 11) {
         weight_ele_veto_pho1_cat = getWeight(Photon_eta[ipho1_cat], Photon_r9[ipho1_cat]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   if (ipho0_cat != -1) {
     weight_ele_veto_pho0_cat = getWeight(Photon_eta[ipho0_cat], Photon_r9[ipho0_cat], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho0_cat] >= 0 && (uint)Photon_genPartIdx[ipho0_cat] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_cat]]) == 11) {
         weight_ele_veto_pho0_cat = getWeight(Photon_eta[ipho0_cat], Photon_r9[ipho0_cat]);
       }
     }
   }
   if (ipho1_cat != -1) {
     weight_ele_veto_pho1_cat = getWeight(Photon_eta[ipho1_cat], Photon_r9[ipho1_cat], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho1_cat] >= 0 && (uint)Photon_genPartIdx[ipho1_cat] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_cat]]) == 11) {
         weight_ele_veto_pho1_cat = getWeight(Photon_eta[ipho1_cat], Photon_r9[ipho1_cat], (iflag == 112) - (iflag == 117));
       }
     }
   }
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   if (ipho0_cat != -1) {
     weight_ele_veto_pho0_cat = getWeight(Photon_eta[ipho0_cat], Photon_pt[ipho0_cat], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho0_cat] >= 0 && (uint)Photon_genPartIdx[ipho0_cat] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_cat]]) == 11) {
         weight_ele_veto_pho0_cat = getWeight(Photon_eta[ipho0_cat], Photon_pt[ipho0_cat]);
       }
     }
   }
   if (ipho1_cat != -1) {
     weight_ele_veto_pho1_cat = getWeight(Photon_eta[ipho1_cat], Photon_pt[ipho1_cat], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho1_cat] >= 0 && (uint)Photon_genPartIdx[ipho1_cat] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_cat]]) == 11) {
         weight_ele_veto_pho1_cat = getWeight(Photon_eta[ipho1_cat], Photon_pt[ipho1_cat]);
       }
     }
   }
#endif // defined(mainSelectorMC18_cxx)

   float weight_eg_misid_pho0_cat = 1.;
   float weight_eg_misid_pho1_cat = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_cat != -1) {
     if (Photon_genPartIdx[ipho0_cat] >= 0 && (uint)Photon_genPartIdx[ipho0_cat] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_cat]]) == 11) {
       weight_eg_misid_pho0_cat = getWeight(sf_eg_misid, fabs(Photon_eta[ipho0_cat]), Photon_pt[ipho0_cat], (iflag == 130) - (iflag == 135));
     }
   }

   if (ipho1_cat != -1) {
     if (Photon_genPartIdx[ipho1_cat] >= 0 && (uint)Photon_genPartIdx[ipho1_cat] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_cat]]) == 11) {
       weight_eg_misid_pho1_cat = getWeight(sf_eg_misid, fabs(Photon_eta[ipho1_cat]), Photon_pt[ipho1_cat], (iflag == 130) - (iflag == 135));
     }
   }
#if defined(COMPUTE_EG_MISID)
   weight_eg_misid_pho0_cat = 1.;
   weight_eg_misid_pho1_cat = 1.;
#endif // defined(COMPUTE_EG_MISID)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0_cat = weight_eff_pho0_cat * weight_reco_pho0_cat * weight_ele_veto_pho0_cat * weight_eg_misid_pho0_cat;
   float weight_pho1_cat = weight_eff_pho1_cat * weight_reco_pho1_cat * weight_ele_veto_pho1_cat * weight_eg_misid_pho1_cat;

// photon(s) scale factors QCD

   float weight_eff_pho0_qcd = 1.;
   float weight_reco_pho0_qcd = 1.;

   float weight_eff_pho1_qcd = 1.;
   float weight_reco_pho1_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_qcd != -1) {
     weight_eff_pho0_qcd = getWeight(sf_pho_eff, Photon_eta[ipho0_qcd], Photon_pt[ipho0_qcd], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho0_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_qcd]]) == 11) {
         weight_eff_pho0_qcd = getWeight(sf_pho_eff, Photon_eta[ipho0_qcd], Photon_pt[ipho0_qcd]);
       }
     }
   }
   if (ipho1_qcd != -1) {
     weight_eff_pho1_qcd = getWeight(sf_pho_eff, Photon_eta[ipho1_qcd], Photon_pt[ipho1_qcd], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho1_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_qcd]]) == 11) {
         weight_eff_pho1_qcd = getWeight(sf_pho_eff, Photon_eta[ipho1_qcd], Photon_pt[ipho1_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_ele_veto_pho0_qcd = 1.;
   float weight_ele_veto_pho1_qcd = 1.;

#if defined(mainSelectorMC16_cxx)
   if (ipho0_qcd != -1) {
     weight_ele_veto_pho0_qcd = getWeight(Photon_eta[ipho0_qcd], Photon_r9[ipho0_qcd], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho0_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_qcd]]) == 11) {
         weight_ele_veto_pho0_qcd = getWeight(Photon_eta[ipho0_qcd], Photon_r9[ipho0_qcd]);
       }
     }
   }
   if (ipho1_qcd != -1) {
     weight_ele_veto_pho1_qcd = getWeight(Photon_eta[ipho1_qcd], Photon_r9[ipho1_qcd], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho1_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_qcd]]) == 11) {
         weight_ele_veto_pho1_qcd = getWeight(Photon_eta[ipho1_qcd], Photon_r9[ipho1_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   if (ipho0_qcd != -1) {
     weight_ele_veto_pho0_qcd = getWeight(Photon_eta[ipho0_qcd], Photon_r9[ipho0_qcd], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho0_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_qcd]]) == 11) {
         weight_ele_veto_pho0_qcd = getWeight(Photon_eta[ipho0_qcd], Photon_r9[ipho0_qcd]);
       }
     }
   }
   if (ipho1_qcd != -1) {
     weight_ele_veto_pho1_qcd = getWeight(Photon_eta[ipho1_qcd], Photon_r9[ipho1_qcd], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho1_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_qcd]]) == 11) {
         weight_ele_veto_pho1_qcd = getWeight(Photon_eta[ipho1_qcd], Photon_r9[ipho1_qcd], (iflag == 112) - (iflag == 117));
       }
     }
   }
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   if (ipho0_qcd != -1) {
     weight_ele_veto_pho0_qcd = getWeight(Photon_eta[ipho0_qcd], Photon_pt[ipho0_qcd], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho0_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_qcd]]) == 11) {
         weight_ele_veto_pho0_qcd = getWeight(Photon_eta[ipho0_qcd], Photon_pt[ipho0_qcd]);
       }
     }
   }
   if (ipho1_qcd != -1) {
     weight_ele_veto_pho1_qcd = getWeight(Photon_eta[ipho1_qcd], Photon_pt[ipho1_qcd], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho1_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_qcd]]) == 11) {
         weight_ele_veto_pho1_qcd = getWeight(Photon_eta[ipho1_qcd], Photon_pt[ipho1_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC18_cxx)

   float weight_eg_misid_pho0_qcd = 1.;
   float weight_eg_misid_pho1_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_qcd != -1) {
     if (Photon_genPartIdx[ipho0_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_qcd]]) == 11) {
       weight_eg_misid_pho0_qcd = getWeight(sf_eg_misid_qcd, fabs(Photon_eta[ipho0_qcd]), Photon_pt[ipho0_qcd], (iflag == 130) - (iflag == 135));
     }
   }

   if (ipho1_qcd != -1) {
     if (Photon_genPartIdx[ipho1_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_qcd]]) == 11) {
       weight_eg_misid_pho1_qcd = getWeight(sf_eg_misid_qcd, fabs(Photon_eta[ipho1_qcd]), Photon_pt[ipho1_qcd], (iflag == 130) - (iflag == 135));
     }
   }
#if defined(COMPUTE_EG_MISID)
   weight_eg_misid_pho0_qcd = 1.;
   weight_eg_misid_pho1_qcd = 1.;
#endif // defined(COMPUTE_EG_MISID)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0_qcd = weight_eff_pho0_qcd * weight_reco_pho0_qcd * weight_ele_veto_pho0_qcd * weight_eg_misid_pho0_qcd;
   float weight_pho1_qcd = weight_eff_pho1_qcd * weight_reco_pho1_qcd * weight_ele_veto_pho1_qcd * weight_eg_misid_pho1_qcd;

// photon(s) scale factors iso qcd

   float weight_eff_pho0_iso_qcd = 1.;
   float weight_reco_pho0_iso_qcd = 1.;

   float weight_eff_pho1_iso_qcd = 1.;
   float weight_reco_pho1_iso_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_iso_qcd != -1) {
     weight_eff_pho0_iso_qcd = getWeight(sf_pho_eff, Photon_eta[ipho0_iso_qcd], Photon_pt[ipho0_iso_qcd], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho0_iso_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_iso_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso_qcd]]) == 11) {
         weight_eff_pho0_iso_qcd = getWeight(sf_pho_eff, Photon_eta[ipho0_iso_qcd], Photon_pt[ipho0_iso_qcd]);
       }
     }
   }
   if (ipho1_iso_qcd != -1) {
     weight_eff_pho1_iso_qcd = getWeight(sf_pho_eff, Photon_eta[ipho1_iso_qcd], Photon_pt[ipho1_iso_qcd], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho1_iso_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_iso_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso_qcd]]) == 11) {
         weight_eff_pho1_iso_qcd = getWeight(sf_pho_eff, Photon_eta[ipho1_iso_qcd], Photon_pt[ipho1_iso_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_ele_veto_pho0_iso_qcd = 1.;
   float weight_ele_veto_pho1_iso_qcd = 1.;

#if defined(mainSelectorMC16_cxx)
   if (ipho0_iso_qcd != -1) {
     weight_ele_veto_pho0_iso_qcd = getWeight(Photon_eta[ipho0_iso_qcd], Photon_r9[ipho0_iso_qcd], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho0_iso_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_iso_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso_qcd]]) == 11) {
         weight_ele_veto_pho0_iso_qcd = getWeight(Photon_eta[ipho0_iso_qcd], Photon_r9[ipho0_iso_qcd]);
       }
     }
   }
   if (ipho1_iso_qcd != -1) {
     weight_ele_veto_pho1_iso_qcd = getWeight(Photon_eta[ipho1_iso_qcd], Photon_r9[ipho1_iso_qcd], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho1_iso_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_iso_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso_qcd]]) == 11) {
         weight_ele_veto_pho1_iso_qcd = getWeight(Photon_eta[ipho1_iso_qcd], Photon_r9[ipho1_iso_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   if (ipho0_iso_qcd != -1) {
     weight_ele_veto_pho0_iso_qcd = getWeight(Photon_eta[ipho0_iso_qcd], Photon_r9[ipho0_iso_qcd], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho0_iso_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_iso_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso_qcd]]) == 11) {
         weight_ele_veto_pho0_iso_qcd = getWeight(Photon_eta[ipho0_iso_qcd], Photon_r9[ipho0_iso_qcd]);
       }
     }
   }
   if (ipho1_iso_qcd != -1) {
     weight_ele_veto_pho1_iso_qcd = getWeight(Photon_eta[ipho1_iso_qcd], Photon_r9[ipho1_iso_qcd], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho1_iso_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_iso_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso_qcd]]) == 11) {
         weight_ele_veto_pho1_iso_qcd = getWeight(Photon_eta[ipho1_iso_qcd], Photon_r9[ipho1_iso_qcd], (iflag == 112) - (iflag == 117));
       }
     }
   }
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   if (ipho0_iso_qcd != -1) {
     weight_ele_veto_pho0_iso_qcd = getWeight(Photon_eta[ipho0_iso_qcd], Photon_pt[ipho0_iso_qcd], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho0_iso_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_iso_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso_qcd]]) == 11) {
         weight_ele_veto_pho0_iso_qcd = getWeight(Photon_eta[ipho0_iso_qcd], Photon_pt[ipho0_iso_qcd]);
       }
     }
   }
   if (ipho1_iso_qcd != -1) {
     weight_ele_veto_pho1_iso_qcd = getWeight(Photon_eta[ipho1_iso_qcd], Photon_pt[ipho1_iso_qcd], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho1_iso_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_iso_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso_qcd]]) == 11) {
         weight_ele_veto_pho1_iso_qcd = getWeight(Photon_eta[ipho1_iso_qcd], Photon_pt[ipho1_iso_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC18_cxx)

   float weight_eg_misid_pho0_iso_qcd = 1.;
   float weight_eg_misid_pho1_iso_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_iso_qcd != -1) {
     if (Photon_genPartIdx[ipho0_iso_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_iso_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso_qcd]]) == 11) {
       weight_eg_misid_pho0_iso_qcd = getWeight(sf_eg_misid, fabs(Photon_eta[ipho0_iso_qcd]), Photon_pt[ipho0_iso_qcd], (iflag == 130) - (iflag == 135));
     }
   }

   if (ipho1_iso_qcd != -1) {
     if (Photon_genPartIdx[ipho1_iso_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_iso_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso_qcd]]) == 11) {
       weight_eg_misid_pho1_iso_qcd = getWeight(sf_eg_misid, fabs(Photon_eta[ipho1_iso_qcd]), Photon_pt[ipho1_iso_qcd], (iflag == 130) - (iflag == 135));
     }
   }
#if defined(COMPUTE_EG_MISID)
   weight_eg_misid_pho0_iso_qcd = 1.;
   weight_eg_misid_pho1_iso_qcd = 1.;
#endif // defined(COMPUTE_EG_MISID)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0_iso_qcd = weight_eff_pho0_iso_qcd * weight_reco_pho0_iso_qcd * weight_ele_veto_pho0_iso_qcd * weight_eg_misid_pho0_iso_qcd;
   float weight_pho1_iso_qcd = weight_eff_pho1_iso_qcd * weight_reco_pho1_iso_qcd * weight_ele_veto_pho1_iso_qcd * weight_eg_misid_pho1_iso_qcd;
// photon(s) fake scale factors QCD

   float weight_eff_pho0_fake_qcd = 1.;
   float weight_reco_pho0_fake_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_fake_qcd != -1) {
     weight_eff_pho0_fake_qcd = getWeight(sf_pho_eff, Photon_eta[ipho0_fake_qcd], Photon_pt[ipho0_fake_qcd], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho0_fake_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_fake_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake_qcd]]) == 11) {
         weight_eff_pho0_fake_qcd = getWeight(sf_pho_eff, Photon_eta[ipho0_fake_qcd], Photon_pt[ipho0_fake_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_ele_veto_pho0_fake_qcd = 1.;

#if defined(mainSelectorMC16_cxx)
   if (ipho0_fake_qcd != -1) {
     weight_ele_veto_pho0_fake_qcd = getWeight(Photon_eta[ipho0_fake_qcd], Photon_r9[ipho0_fake_qcd], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho0_fake_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_fake_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake_qcd]]) == 11) {
         weight_ele_veto_pho0_fake_qcd = getWeight(Photon_eta[ipho0_fake_qcd], Photon_r9[ipho0_fake_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   if (ipho0_fake_qcd != -1) {
     weight_ele_veto_pho0_fake_qcd = getWeight(Photon_eta[ipho0_fake_qcd], Photon_r9[ipho0_fake_qcd], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho0_fake_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_fake_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake_qcd]]) == 11) {
         weight_ele_veto_pho0_fake_qcd = getWeight(Photon_eta[ipho0_fake_qcd], Photon_r9[ipho0_fake_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   if (ipho0_fake_qcd != -1) {
     weight_ele_veto_pho0_fake_qcd = getWeight(Photon_eta[ipho0_fake_qcd], Photon_pt[ipho0_fake_qcd], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho0_fake_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_fake_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake_qcd]]) == 11) {
         weight_ele_veto_pho0_fake_qcd = getWeight(Photon_eta[ipho0_fake_qcd], Photon_pt[ipho0_fake_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC18_cxx)

   float weight_eg_misid_pho0_fake_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_fake_qcd != -1) {
     if (Photon_genPartIdx[ipho0_fake_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_fake_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake_qcd]]) == 11) {
       weight_eg_misid_pho0_fake_qcd = getWeight(sf_eg_misid_qcd, fabs(Photon_eta[ipho0_fake_qcd]), Photon_pt[ipho0_fake_qcd], (iflag == 130) - (iflag == 135));
     }
   }
#if defined(COMPUTE_EG_MISID)
   weight_eg_misid_pho0_fake_qcd = 1.;
#endif // defined(COMPUTE_EG_MISID)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0_fake_qcd = weight_eff_pho0_fake_qcd * weight_reco_pho0_fake_qcd * weight_ele_veto_pho0_fake_qcd * weight_eg_misid_pho0_fake_qcd;

// photon(s) scale factors cat QCD

   float weight_eff_pho0_cat_qcd = 1.;
   float weight_reco_pho0_cat_qcd = 1.;

   float weight_eff_pho1_cat_qcd = 1.;
   float weight_reco_pho1_cat_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_cat_qcd != -1) {
     weight_eff_pho0_cat_qcd = getWeight(sf_pho_eff, Photon_eta[ipho0_cat_qcd], Photon_pt[ipho0_cat_qcd], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho0_cat_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_cat_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_cat_qcd]]) == 11) {
         weight_eff_pho0_cat_qcd = getWeight(sf_pho_eff, Photon_eta[ipho0_cat_qcd], Photon_pt[ipho0_cat_qcd]);
       }
     }
   }
   if (ipho1_cat_qcd != -1) {
     weight_eff_pho1_cat_qcd = getWeight(sf_pho_eff, Photon_eta[ipho1_cat_qcd], Photon_pt[ipho1_cat_qcd], (iflag == 100) - (iflag == 105));
     if (iflag == 100 || iflag == 105) {
       if (Photon_genPartIdx[ipho1_cat_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_cat_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_cat_qcd]]) == 11) {
         weight_eff_pho1_cat_qcd = getWeight(sf_pho_eff, Photon_eta[ipho1_cat_qcd], Photon_pt[ipho1_cat_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_ele_veto_pho0_cat_qcd = 1.;
   float weight_ele_veto_pho1_cat_qcd = 1.;

#if defined(mainSelectorMC16_cxx)
   if (ipho0_cat_qcd != -1) {
     weight_ele_veto_pho0_cat_qcd = getWeight(Photon_eta[ipho0_cat_qcd], Photon_r9[ipho0_cat_qcd], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho0_cat_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_cat_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_cat_qcd]]) == 11) {
         weight_ele_veto_pho0_cat_qcd = getWeight(Photon_eta[ipho0_cat_qcd], Photon_r9[ipho0_cat_qcd]);
       }
     }
   }
   if (ipho1_cat_qcd != -1) {
     weight_ele_veto_pho1_cat_qcd = getWeight(Photon_eta[ipho1_cat_qcd], Photon_r9[ipho1_cat_qcd], (iflag == 111) - (iflag == 116));
     if (iflag == 111 || iflag == 116) {
       if (Photon_genPartIdx[ipho1_cat_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_cat_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_cat_qcd]]) == 11) {
         weight_ele_veto_pho1_cat_qcd = getWeight(Photon_eta[ipho1_cat_qcd], Photon_r9[ipho1_cat_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC16_cxx)
#if defined(mainSelectorMC17_cxx)
   if (ipho0_cat_qcd != -1) {
     weight_ele_veto_pho0_cat_qcd = getWeight(Photon_eta[ipho0_cat_qcd], Photon_r9[ipho0_cat_qcd], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho0_cat_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_cat_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_cat_qcd]]) == 11) {
         weight_ele_veto_pho0_cat_qcd = getWeight(Photon_eta[ipho0_cat_qcd], Photon_r9[ipho0_cat_qcd]);
       }
     }
   }
   if (ipho1_cat_qcd != -1) {
     weight_ele_veto_pho1_cat_qcd = getWeight(Photon_eta[ipho1_cat_qcd], Photon_r9[ipho1_cat_qcd], (iflag == 112) - (iflag == 117));
     if (iflag == 112 || iflag == 117) {
       if (Photon_genPartIdx[ipho1_cat_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_cat_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_cat_qcd]]) == 11) {
         weight_ele_veto_pho1_cat_qcd = getWeight(Photon_eta[ipho1_cat_qcd], Photon_r9[ipho1_cat_qcd], (iflag == 112) - (iflag == 117));
       }
     }
   }
#endif // defined(mainSelectorMC17_cxx)
#if defined(mainSelectorMC18_cxx)
   if (ipho0_cat_qcd != -1) {
     weight_ele_veto_pho0_cat_qcd = getWeight(Photon_eta[ipho0_cat_qcd], Photon_pt[ipho0_cat_qcd], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho0_cat_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_cat_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_cat_qcd]]) == 11) {
         weight_ele_veto_pho0_cat_qcd = getWeight(Photon_eta[ipho0_cat_qcd], Photon_pt[ipho0_cat_qcd]);
       }
     }
   }
   if (ipho1_cat_qcd != -1) {
     weight_ele_veto_pho1_cat_qcd = getWeight(Photon_eta[ipho1_cat_qcd], Photon_pt[ipho1_cat_qcd], (iflag == 113) - (iflag == 118));
     if (iflag == 113 || iflag == 118) {
       if (Photon_genPartIdx[ipho1_cat_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_cat_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_cat_qcd]]) == 11) {
         weight_ele_veto_pho1_cat_qcd = getWeight(Photon_eta[ipho1_cat_qcd], Photon_pt[ipho1_cat_qcd]);
       }
     }
   }
#endif // defined(mainSelectorMC18_cxx)

   float weight_eg_misid_pho0_cat_qcd = 1.;
   float weight_eg_misid_pho1_cat_qcd = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (ipho0_cat_qcd != -1) {
     if (Photon_genPartIdx[ipho0_cat_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_cat_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_cat_qcd]]) == 11) {
       weight_eg_misid_pho0_cat_qcd = getWeight(sf_eg_misid, fabs(Photon_eta[ipho0_cat_qcd]), Photon_pt[ipho0_cat_qcd], (iflag == 130) - (iflag == 135));
     }
   }

   if (ipho1_cat_qcd != -1) {
     if (Photon_genPartIdx[ipho1_cat_qcd] >= 0 && (uint)Photon_genPartIdx[ipho1_cat_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_cat_qcd]]) == 11) {
       weight_eg_misid_pho1_cat_qcd = getWeight(sf_eg_misid, fabs(Photon_eta[ipho1_cat_qcd]), Photon_pt[ipho1_cat_qcd], (iflag == 130) - (iflag == 135));
     }
   }
#if defined(COMPUTE_EG_MISID)
   weight_eg_misid_pho0_cat_qcd = 1.;
   weight_eg_misid_pho1_cat_qcd = 1.;
#endif // defined(COMPUTE_EG_MISID)
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)

   float weight_pho0_cat_qcd = weight_eff_pho0_cat_qcd * weight_reco_pho0_cat_qcd * weight_ele_veto_pho0_cat_qcd * weight_eg_misid_pho0_cat_qcd;
   float weight_pho1_cat_qcd = weight_eff_pho1_cat_qcd * weight_reco_pho1_cat_qcd * weight_ele_veto_pho1_cat_qcd * weight_eg_misid_pho1_cat_qcd;

// W scale factors

   float weight_W_ele = weight_gen * weight_pu_ele * weight_eff_ele0 * weight_reco_ele0 * weight_trig_ele0 * weight_hlt_ele;
   float weight_W_muo = weight_gen * weight_pu_muo * weight_trig_muo0 * weight_id_muo0 * weight_iso_muo0;

// W scale factors QCD

   float weight_W_ele_qcd = weight_gen * weight_pu_ele * weight_eff_ele0_qcd * weight_reco_ele0_qcd * weight_trig_ele0_qcd * weight_hlt_ele_qcd;
   float weight_W_muo_qcd = weight_gen * weight_pu_muo * weight_trig_muo0_qcd * weight_id_muo0_qcd * weight_iso_muo0_qcd;

// Z scale factors

   float weight_Z_ele = weight_gen * weight_pu_ele * weight_eff_ele0 * weight_eff_ele1 * weight_reco_ele0 * weight_reco_ele1 * weight_trig_ele0 * weight_trig_ele1 * weight_hlt_ele;
   float weight_Z_muo = weight_gen * weight_pu_muo * weight_trig_muo0 * weight_trig_muo1 * weight_id_muo0 * weight_id_muo1 * weight_iso_muo0 * weight_iso_muo1;

// Z scale factors QCD

   float weight_Z_ele_qcd = weight_gen * weight_pu_ele * weight_eff_ele0_qcd * weight_eff_ele1_qcd * weight_reco_ele0_qcd * weight_reco_ele1_qcd * weight_trig_ele0_qcd * weight_trig_ele1_qcd * weight_hlt_ele_qcd;
   float weight_Z_muo_qcd = weight_gen * weight_pu_muo * weight_trig_muo0_qcd * weight_trig_muo1_qcd * weight_id_muo0_qcd * weight_id_muo1_qcd * weight_iso_muo0_qcd * weight_iso_muo1_qcd;

   float weight_l1prefiring = 1.;

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx)
   weight_l1prefiring = *L1PreFiringWeight_Nom;
   if (iflag == 120) weight_l1prefiring = *L1PreFiringWeight_Up;
   if (iflag == 125) weight_l1prefiring = *L1PreFiringWeight_Dn;
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx)

   weight_W_ele = weight_W_ele * weight_l1prefiring;
   weight_W_muo = weight_W_muo * weight_l1prefiring;

   weight_W_ele_qcd = weight_W_ele_qcd * weight_l1prefiring;
   weight_W_muo_qcd = weight_W_muo_qcd * weight_l1prefiring;

   weight_Z_ele = weight_Z_ele * weight_l1prefiring;
   weight_Z_muo = weight_Z_muo * weight_l1prefiring;

   weight_Z_ele_qcd = weight_Z_ele_qcd * weight_l1prefiring;
   weight_Z_muo_qcd = weight_Z_muo_qcd * weight_l1prefiring;

// W -> ele nu trigger object matching

   if (W_ele_sel) {

     bool match0 = false;

     for (uint i = 0; i < *nTrigObj; i++) {
       if (match0) continue;
       if (TrigObj_id[i] != 11) continue;

       TLorentzVector tmp_trg;
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], ele0.M());
       if (ele0.DeltaR(tmp_trg) < 0.3) {
         for (uint j = 0; j < 32; j++) {
           if ((TrigObj_filterBits[i] & BIT(j)) == BIT(j)) h_W_ele0_trig->Fill(j+0.5, weight_W_ele);
         }
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
         if ((TrigObj_filterBits[i] & 2) == 2) match0 = true; // 2 = 1e
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
         if ((TrigObj_filterBits[i] & 1024) == 1024) match0 = true; // 1024 = 32_L1DoubleEG_AND_L1SingleEGOr
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
         if ((TrigObj_filterBits[i] & 2) == 2) match0 = true; // 2 = 1e
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       }
       if (ele0_qcd.DeltaR(tmp_trg) < 0.3) {
         for (uint j = 0; j < 32; j++) {
           if ((TrigObj_filterBits[i] & BIT(j)) == BIT(j)) QCD(h_W_ele0_trig)->Fill(j+0.5, weight_W_ele_qcd);
         }
       }
     }

     if (!match0) {
       W_ele_sel = false;
     }

   }

// W -> muo nu trigger object matching

   if (W_muo_sel) {

     bool match0 = false;

     for (uint i = 0; i < *nTrigObj; i++) {
       if (match0) continue;
       if (TrigObj_id[i] != 13) continue;

       TLorentzVector tmp_trg;
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], muo0.M());
       if (muo0.DeltaR(tmp_trg) < 0.1) {
         for (uint j = 0; j < 32; j++) {
           if ((TrigObj_filterBits[i] & BIT(j)) == BIT(j)) h_W_muo0_trig->Fill(j+0.5, weight_W_muo);
         }
         if ((TrigObj_filterBits[i] & 2) == 2) match0 = true; // 2 = Iso
         if ((TrigObj_filterBits[i] & 8) == 8) match0 = true; // 8 = 1mu
       }
       if (muo0_qcd.DeltaR(tmp_trg) < 0.1) {
         for (uint j = 0; j < 32; j++) {
           if ((TrigObj_filterBits[i] & BIT(j)) == BIT(j)) QCD(h_W_muo0_trig)->Fill(j+0.5, weight_W_muo_qcd);
         }
       }
     }

     if (!match0) {
       W_muo_sel = false;
     }

   }

// Z -> ele ele trigger objects matching

   if (Z_ele_sel) {

     bool match0 = false;

     for (uint i = 0; i < *nTrigObj; i++) {
       if (match0) continue;
       if (TrigObj_id[i] != 11) continue;

       TLorentzVector tmp_trg;
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], ele0.M());
       if (ele0.DeltaR(tmp_trg) < 0.3) {
         for (uint j = 0; j < 32; j++) {
           if ((TrigObj_filterBits[i] & BIT(j)) == BIT(j)) h_Z_ele0_trig->Fill(j+0.5, weight_Z_ele);
         }
#if defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
         if ((TrigObj_filterBits[i] & 2) == 2) match0 = true; // 2 = 1e
#endif // defined(mainSelectorDT16_cxx) || defined(mainSelectorMC16_cxx)
#if defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
         if ((TrigObj_filterBits[i] & 1024) == 1024) match0 = true; // 1024 = 32_L1DoubleEG_AND_L1SingleEGOr
#endif // defined(mainSelectorDT17_cxx) || defined(mainSelectorMC17_cxx)
#if defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
         if ((TrigObj_filterBits[i] & 2) == 2) match0 = true; // 2 = 1e
#endif // defined(mainSelectorDT18_cxx) || defined(mainSelectorMC18_cxx)
       }
       if (ele0_qcd.DeltaR(tmp_trg) < 0.3) {
         for (uint j = 0; j < 32; j++) {
           if ((TrigObj_filterBits[i] & BIT(j)) == BIT(j)) QCD(h_Z_ele0_trig)->Fill(j+0.5, weight_Z_ele_qcd);
         }
       }
     }

     if (!match0) {
       Z_ele_sel = false;
     }

   }

// Z -> muo muo trigger objects matching

   if (Z_muo_sel) {

     bool match0 = false;

     for (uint i = 0; i < *nTrigObj; i++) {
       if (match0) continue;
       if (TrigObj_id[i] != 13) continue;

       TLorentzVector tmp_trg;
       tmp_trg.SetPtEtaPhiM(TrigObj_pt[i], TrigObj_eta[i], TrigObj_phi[i], muo0.M());
       if (muo0.DeltaR(tmp_trg) < 0.1) {
         for (uint j = 0; j < 32; j++) {
           if ((TrigObj_filterBits[i] & BIT(j)) == BIT(j)) h_Z_muo0_trig->Fill(j+0.5, weight_Z_muo);
         }
         if ((TrigObj_filterBits[i] & 2) == 2) match0 = true; // 2 = Iso
         if ((TrigObj_filterBits[i] & 8) == 8) match0 = true; // 8 = 1mu
       }
       if (muo0_qcd.DeltaR(tmp_trg) < 0.1) {
         for (uint j = 0; j < 32; j++) {
           if ((TrigObj_filterBits[i] & BIT(j)) == BIT(j)) QCD(h_Z_muo0_trig)->Fill(j+0.5, weight_Z_muo_qcd);
         }
       }
     }

     if (!match0) {
       Z_muo_sel = false;
     }

   }

// W plots

   if (W_ele_sel) {
     h_W_ele->Fill(W_ele0_mt, weight_W_ele);
     h_W_ele_met_pt->Fill(*MET_pt, weight_W_ele);
     h_W_ele_met_phi->Fill(*MET_phi, weight_W_ele);
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

   if (W_muo_sel) {
     h_W_muo->Fill(W_muo0_mt, weight_W_muo);
     h_W_muo_met_pt->Fill(*MET_pt, weight_W_muo);
     h_W_muo_met_phi->Fill(*MET_phi, weight_W_muo);
     h_W_muo_npvs->Fill(*PV_npvsGood, weight_gen);
     h_W_muo_npvs_w->Fill(*PV_npvsGood, weight_W_muo);
     h_W_muo0_pt->Fill(Muon_pt[imuo0], weight_W_muo);
     h_W_muo0_eta->Fill(Muon_eta[imuo0], weight_W_muo);
     h_W_muo0_phi->Fill(Muon_phi[imuo0], weight_W_muo);
     h_W_muo0_pf_iso_all->Fill(Muon_pfRelIso03_all[imuo0], weight_W_muo);
     h_W_muo0_pf_iso_chg->Fill(Muon_pfRelIso03_chg[imuo0], weight_W_muo);
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
   }

// W photon(s) plots

   if (W_ele_sel) {
     h_W_ele_nphotons->Fill(n_photons, weight_W_ele);
     if (ipho0 != -1) {
       h_WG_ele->Fill(W_ele0_mt, weight_W_ele * weight_pho0);
       h_WG_ele_ele0_pt->Fill(Electron_pt[iele0], weight_W_ele * weight_pho0);
       h_WG_ele_pho0_pt->Fill(Photon_pt[ipho0], weight_W_ele * weight_pho0);
       h_WG_ele_pho0_eta->Fill(Photon_eta[ipho0], weight_W_ele * weight_pho0);
       h_WG_ele_pho0_phi->Fill(Photon_phi[ipho0], weight_W_ele * weight_pho0);
       h_WG_ele_pho0_r9->Fill(Photon_r9[ipho0], weight_W_ele * weight_pho0);
       h_WG_ele_pho0_sieie->Fill(Photon_sieie[ipho0], weight_W_ele * weight_pho0);
       h_WG_ele_pho0_mva->Fill(Photon_mvaID[ipho0], weight_W_ele * weight_pho0);
       h_WG_ele_pho0_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho0], weight_W_ele * weight_pho0);
       h_WG_ele_pho0_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho0], weight_W_ele * weight_pho0);
       h_WG_ele_pho0_dR->Fill(pho0.DeltaR(ele0), weight_W_ele * weight_pho0);
       h_WG_ele_ele0_pho0->Fill((ele0+pho0).M(), weight_W_ele * weight_pho0);
     }
     if (ipho0_fake != -1) {
       h_WG_ele_ele0_pho0_fake->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
#if defined(COMPUTE_EG_MISID)
       if (Photon_pt[ipho0_fake] > 20 && Photon_pt[ipho0_fake] < 30) {
         if (fabs(Photon_eta[ipho0_fake]) > 0 && fabs(Photon_eta[ipho0_fake]) < 0.5)     h_WG_ele_fake_1->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 0.5 && fabs(Photon_eta[ipho0_fake]) < 1.0)   h_WG_ele_fake_2->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 1.0 && fabs(Photon_eta[ipho0_fake]) < 1.442) h_WG_ele_fake_3->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 1.566 && fabs(Photon_eta[ipho0_fake]) < 2.0) h_WG_ele_fake_4->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 2.0 && fabs(Photon_eta[ipho0_fake]) < 2.5)   h_WG_ele_fake_5->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
       }
       if (Photon_pt[ipho0_fake] > 30 && Photon_pt[ipho0_fake] < 40) {
         if (fabs(Photon_eta[ipho0_fake]) > 0 && fabs(Photon_eta[ipho0_fake]) < 0.5)     h_WG_ele_fake_6->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 0.5 && fabs(Photon_eta[ipho0_fake]) < 1.0)   h_WG_ele_fake_7->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 1.0 && fabs(Photon_eta[ipho0_fake]) < 1.442) h_WG_ele_fake_8->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 1.566 && fabs(Photon_eta[ipho0_fake]) < 2.0) h_WG_ele_fake_9->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 2.0 && fabs(Photon_eta[ipho0_fake]) < 2.5)   h_WG_ele_fake_10->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
       }
       if (Photon_pt[ipho0_fake] > 40 && Photon_pt[ipho0_fake] < 50) {
         if (fabs(Photon_eta[ipho0_fake]) > 0 && fabs(Photon_eta[ipho0_fake]) < 0.5)     h_WG_ele_fake_11->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 0.5 && fabs(Photon_eta[ipho0_fake]) < 1.0)   h_WG_ele_fake_12->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 1.0 && fabs(Photon_eta[ipho0_fake]) < 1.442) h_WG_ele_fake_13->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 1.566 && fabs(Photon_eta[ipho0_fake]) < 2.0) h_WG_ele_fake_14->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 2.0 && fabs(Photon_eta[ipho0_fake]) < 2.5)   h_WG_ele_fake_15->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
       }
       if (Photon_pt[ipho0_fake] > 50) {
         if (fabs(Photon_eta[ipho0_fake]) > 0 && fabs(Photon_eta[ipho0_fake]) < 0.5)     h_WG_ele_fake_16->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 0.5 && fabs(Photon_eta[ipho0_fake]) < 1.0)   h_WG_ele_fake_17->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 1.0 && fabs(Photon_eta[ipho0_fake]) < 1.442) h_WG_ele_fake_18->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 1.566 && fabs(Photon_eta[ipho0_fake]) < 2.0) h_WG_ele_fake_19->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         if (fabs(Photon_eta[ipho0_fake]) > 2.0 && fabs(Photon_eta[ipho0_fake]) < 2.5)   h_WG_ele_fake_20->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
       }
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
       if (Photon_genPartIdx[ipho0_fake] >= 0 && (uint)Photon_genPartIdx[ipho0_fake] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake]]) == 11) {
         if (Photon_pt[ipho0_fake] > 20 && Photon_pt[ipho0_fake] < 30) {
           if (fabs(Photon_eta[ipho0_fake]) > 0 && fabs(Photon_eta[ipho0_fake]) < 0.5)     h_WG_ele_fake_truthmatch_1->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 0.5 && fabs(Photon_eta[ipho0_fake]) < 1.0)   h_WG_ele_fake_truthmatch_2->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 1.0 && fabs(Photon_eta[ipho0_fake]) < 1.442) h_WG_ele_fake_truthmatch_3->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 1.566 && fabs(Photon_eta[ipho0_fake]) < 2.0) h_WG_ele_fake_truthmatch_4->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 2.0 && fabs(Photon_eta[ipho0_fake]) < 2.5)   h_WG_ele_fake_truthmatch_5->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         }
         if (Photon_pt[ipho0_fake] > 30 && Photon_pt[ipho0_fake] < 40) {
           if (fabs(Photon_eta[ipho0_fake]) > 0 && fabs(Photon_eta[ipho0_fake]) < 0.5)     h_WG_ele_fake_truthmatch_6->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 0.5 && fabs(Photon_eta[ipho0_fake]) < 1.0)   h_WG_ele_fake_truthmatch_7->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 1.0 && fabs(Photon_eta[ipho0_fake]) < 1.442) h_WG_ele_fake_truthmatch_8->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 1.566 && fabs(Photon_eta[ipho0_fake]) < 2.0) h_WG_ele_fake_truthmatch_9->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 2.0 && fabs(Photon_eta[ipho0_fake]) < 2.5)   h_WG_ele_fake_truthmatch_10->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         }
         if (Photon_pt[ipho0_fake] > 40 && Photon_pt[ipho0_fake] < 50) {
           if (fabs(Photon_eta[ipho0_fake]) > 0 && fabs(Photon_eta[ipho0_fake]) < 0.5)     h_WG_ele_fake_truthmatch_11->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 0.5 && fabs(Photon_eta[ipho0_fake]) < 1.0)   h_WG_ele_fake_truthmatch_12->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 1.0 && fabs(Photon_eta[ipho0_fake]) < 1.442) h_WG_ele_fake_truthmatch_13->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 1.566 && fabs(Photon_eta[ipho0_fake]) < 2.0) h_WG_ele_fake_truthmatch_14->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 2.0 && fabs(Photon_eta[ipho0_fake]) < 2.5)   h_WG_ele_fake_truthmatch_15->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         }
         if (Photon_pt[ipho0_fake] > 50) {
           if (fabs(Photon_eta[ipho0_fake]) > 0 && fabs(Photon_eta[ipho0_fake]) < 0.5)     h_WG_ele_fake_truthmatch_16->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 0.5 && fabs(Photon_eta[ipho0_fake]) < 1.0)   h_WG_ele_fake_truthmatch_17->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 1.0 && fabs(Photon_eta[ipho0_fake]) < 1.442) h_WG_ele_fake_truthmatch_18->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 1.566 && fabs(Photon_eta[ipho0_fake]) < 2.0) h_WG_ele_fake_truthmatch_19->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
           if (fabs(Photon_eta[ipho0_fake]) > 2.0 && fabs(Photon_eta[ipho0_fake]) < 2.5)   h_WG_ele_fake_truthmatch_20->Fill((ele0+pho0_fake).M(), weight_W_ele * weight_pho0_fake);
         }
       }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#endif // defined(COMPUTE_EG_MISID)
     }

     if (ipho1 != -1) {
       h_WGG_ele->Fill(W_ele0_mt, weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_ele0_pt->Fill(ele0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho0_pt->Fill(pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho0_eta->Fill(Photon_eta[ipho0], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho0_phi->Fill(Photon_phi[ipho0], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho0_sieie->Fill(Photon_sieie[ipho0], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho0_mva->Fill(Photon_mvaID[ipho0], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho1_pt->Fill(Photon_pt[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho1_eta->Fill(Photon_eta[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho1_phi->Fill(Photon_phi[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho1_r9->Fill(Photon_r9[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho1_sieie->Fill(Photon_sieie[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho1_mva->Fill(Photon_mvaID[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho1_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho1_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho1], weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho1_dR->Fill(pho1.DeltaR(ele0), weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho0_pho1_pt->Fill((pho0+pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho0_pho1->Fill((pho0+pho1).M(), weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_ele0_pho0->Fill((ele0+pho0).M(), weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_ele0_pho1->Fill((ele0+pho1).M(), weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_ele0_pho0_pho1->Fill((ele0+pho0+pho1).M(), weight_W_ele * weight_pho0 * weight_pho1);
       h_WGG_ele_pho0_pho1_dR->Fill(pho0.DeltaR(pho1), weight_W_ele * weight_pho0 * weight_pho1);
     }
     if (ipho0_cat != -1 && ipho0 == -1) {
       if (is_iso_pho0 == false) h_WG_ele_pho0_pt_noiso->Fill(pho0_cat.Pt(), weight_W_ele * weight_pho0_cat);
     }
     if (ipho1_cat != -1) {
       if (category2d == 0) {
         h_WGG_ele_pho0_pho1_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho0_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho1_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho0_pt_cat0->Fill(pho0_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho1_pt_cat0->Fill(pho1_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 1) {
         h_WGG_ele_pho0_pho1_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho0_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho1_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho0_pt_cat1->Fill(pho0_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho1_pt_cat1->Fill(pho1_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 2) {
         h_WGG_ele_pho0_pho1_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho0_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho1_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho0_pt_cat2->Fill(pho0_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho1_pt_cat2->Fill(pho1_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 3) {
         h_WGG_ele_pho0_pho1_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho0_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho1_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho0_pt_cat3->Fill(pho0_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
         h_WGG_ele_pho1_pt_cat3->Fill(pho1_cat.Pt(), weight_W_ele * weight_pho0_cat * weight_pho1_cat);
       }
     }
     if (ipho0_iso != -1) {
       if (fabs(pho0_iso.Eta()) < 1.442) {
         h_WG_ele_pho0_pf_iso_all_nocut_eb->Fill(Photon_pfRelIso03_all[ipho0_iso], weight_W_ele * weight_pho0_iso);
         h_WG_ele_pho0_sieie_nocut_eb->Fill(Photon_sieie[ipho0_iso], weight_W_ele * weight_pho0_iso);
         if (is_pho0_iso) {
           h_WG_ele_t->Fill(pho0_iso.Pt(), 0., 0., weight_W_ele * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_WG_ele_t_genmatch2->Fill(pho0_iso.Pt(), 0., 0., weight_W_ele * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_WG_ele_t_genmatch->Fill(pho0_iso.Pt(), 0., 0., weight_W_ele * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_WG_ele_t->Fill(pho0_iso.Pt(), 0., 1., weight_W_ele * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_WG_ele_t_genmatch2->Fill(pho0_iso.Pt(), 0., 1., weight_W_ele * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_WG_ele_t_genmatch->Fill(pho0_iso.Pt(), 0., 1., weight_W_ele * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       } else {
         h_WG_ele_pho0_pf_iso_all_nocut_ee->Fill(Photon_pfRelIso03_all[ipho0_iso], weight_W_ele * weight_pho0_iso);
         h_WG_ele_pho0_sieie_nocut_ee->Fill(Photon_sieie[ipho0_iso], weight_W_ele * weight_pho0_iso);
         if (is_pho0_iso) {
           h_WG_ele_t->Fill(pho0_iso.Pt(), 1., 0., weight_W_ele * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_WG_ele_t_genmatch2->Fill(pho0_iso.Pt(), 1., 0., weight_W_ele * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_WG_ele_t_genmatch->Fill(pho0_iso.Pt(), 1., 0., weight_W_ele * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_WG_ele_t->Fill(pho0_iso.Pt(), 1., 1., weight_W_ele * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_WG_ele_t_genmatch2->Fill(pho0_iso.Pt(), 1., 1., weight_W_ele * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_WG_ele_t_genmatch->Fill(pho0_iso.Pt(), 1., 1., weight_W_ele * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       }
     }
     if (ipho1 != -1) {
       if (fabs(pho0.Eta()) < 1.442) {
         if (fabs(pho1.Eta()) < 1.442) {
           h_WGG_ele_pho0_pho1_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           h_WGG_ele_pho0_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           h_WGG_ele_pho1_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_WGG_ele_pho0_pho1_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
             h_WGG_ele_pho0_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
             h_WGG_ele_pho1_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_WGG_ele_pho0_pho1_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           h_WGG_ele_pho0_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           h_WGG_ele_pho1_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_WGG_ele_pho0_pho1_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
             h_WGG_ele_pho0_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
             h_WGG_ele_pho1_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       } else {
         if (fabs(pho1.Eta()) < 1.442) {
           h_WGG_ele_pho0_pho1_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           h_WGG_ele_pho0_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           h_WGG_ele_pho1_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_WGG_ele_pho0_pho1_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
             h_WGG_ele_pho0_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
             h_WGG_ele_pho1_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_WGG_ele_pho0_pho1_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           h_WGG_ele_pho0_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           h_WGG_ele_pho1_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_WGG_ele_pho0_pho1_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
             h_WGG_ele_pho0_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
             h_WGG_ele_pho1_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       }
     }
     if (ipho1_iso != -1) {
       if (fabs(pho0_iso.Eta()) < 1.442) {
         if (fabs(pho1_iso.Eta()) < 1.442) {
           if (is_pho0_iso && !is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         } else {
           if (is_pho0_iso && !is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_be_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         }
       } else {
         if (fabs(pho1_iso.Eta()) < 1.442) {
           if (is_pho0_iso && !is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         } else {
           if (is_pho0_iso && !is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_WGG_ele_pho0_pho1_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho0_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             h_WGG_ele_pho1_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_ele_pho0_pho1_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho0_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
               h_WGG_ele_pho1_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         }
       }
     }
   }

   if (W_muo_sel) {
     h_W_muo_nphotons->Fill(n_photons, weight_W_muo);
     if (ipho0 != -1) {
       h_WG_muo->Fill(W_muo0_mt, weight_W_muo * weight_pho0);
       h_WG_muo_muo0_pt->Fill(Muon_pt[imuo0], weight_W_muo * weight_pho0);
       h_WG_muo_pho0_pt->Fill(Photon_pt[ipho0], weight_W_muo * weight_pho0);
       h_WG_muo_pho0_eta->Fill(Photon_eta[ipho0], weight_W_muo * weight_pho0);
       h_WG_muo_pho0_phi->Fill(Photon_phi[ipho0], weight_W_muo * weight_pho0);
       h_WG_muo_pho0_r9->Fill(Photon_r9[ipho0], weight_W_muo * weight_pho0);
       h_WG_muo_pho0_sieie->Fill(Photon_sieie[ipho0], weight_W_muo * weight_pho0);
       h_WG_muo_pho0_mva->Fill(Photon_mvaID[ipho0], weight_W_muo * weight_pho0);
       h_WG_muo_pho0_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho0], weight_W_muo * weight_pho0);
       h_WG_muo_pho0_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho0], weight_W_muo * weight_pho0);
       h_WG_muo_pho0_dR->Fill(pho0.DeltaR(muo0), weight_W_muo * weight_pho0);
       h_WG_muo_muo0_pho0->Fill((muo0+pho0).M(), weight_W_muo * weight_pho0);
     }
     if (ipho0_fake != -1) {
       h_WG_muo_muo0_pho0_fake->Fill((muo0+pho0_fake).M(), weight_W_muo * weight_pho0_fake);
     }

     if (ipho1 != -1) {
       h_WGG_muo->Fill(W_muo0_mt, weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_muo0_pt->Fill(muo0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho0_pt->Fill(pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho0_eta->Fill(Photon_eta[ipho0], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho0_phi->Fill(Photon_phi[ipho0], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho0_sieie->Fill(Photon_sieie[ipho0], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho0_mva->Fill(Photon_mvaID[ipho0], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho1_pt->Fill(Photon_pt[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho1_eta->Fill(Photon_eta[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho1_phi->Fill(Photon_phi[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho1_r9->Fill(Photon_r9[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho1_sieie->Fill(Photon_sieie[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho1_mva->Fill(Photon_mvaID[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho1_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho1_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho1], weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho1_dR->Fill(pho1.DeltaR(muo0), weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho0_pho1_pt->Fill((pho0+pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho0_pho1->Fill((pho0+pho1).M(), weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_muo0_pho0->Fill((muo0+pho0).M(), weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_muo0_pho1->Fill((muo0+pho1).M(), weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_muo0_pho0_pho1->Fill((muo0+pho0+pho1).M(), weight_W_muo * weight_pho0 * weight_pho1);
       h_WGG_muo_pho0_pho1_dR->Fill(pho0.DeltaR(pho1), weight_W_muo * weight_pho0 * weight_pho1);
     }
     if (ipho0_cat != -1 && ipho0 == -1) {
       if (is_iso_pho0 == false) h_WG_muo_pho0_pt_noiso->Fill(pho0_cat.Pt(), weight_W_muo * weight_pho0_cat);
     }
     if (ipho1_cat != -1) {
       if (category2d == 0) {
         h_WGG_muo_pho0_pho1_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho0_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho1_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho0_pt_cat0->Fill(pho0_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho1_pt_cat0->Fill(pho1_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 1) {
         h_WGG_muo_pho0_pho1_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho0_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho1_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho0_pt_cat1->Fill(pho0_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho1_pt_cat1->Fill(pho1_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 2) {
         h_WGG_muo_pho0_pho1_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho0_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho1_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho0_pt_cat2->Fill(pho0_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho1_pt_cat2->Fill(pho1_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 3) {
         h_WGG_muo_pho0_pho1_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho0_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho1_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho0_pt_cat3->Fill(pho0_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
         h_WGG_muo_pho1_pt_cat3->Fill(pho1_cat.Pt(), weight_W_muo * weight_pho0_cat * weight_pho1_cat);
       }
     }
     if (ipho0_iso != -1) {
       if (fabs(pho0_iso.Eta()) < 1.442) {
         h_WG_muo_pho0_pf_iso_all_nocut_eb->Fill(Photon_pfRelIso03_all[ipho0_iso], weight_W_muo * weight_pho0_iso);
         h_WG_muo_pho0_sieie_nocut_eb->Fill(Photon_sieie[ipho0_iso], weight_W_muo * weight_pho0_iso);
         if (is_pho0_iso) {
           h_WG_muo_t->Fill(pho0_iso.Pt(), 0., 0., weight_W_muo * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_WG_muo_t_genmatch2->Fill(pho0_iso.Pt(), 0., 0., weight_W_muo * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_WG_muo_t_genmatch->Fill(pho0_iso.Pt(), 0., 0., weight_W_muo * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_WG_muo_t->Fill(pho0_iso.Pt(), 0., 1., weight_W_muo * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_WG_muo_t_genmatch2->Fill(pho0_iso.Pt(), 0., 1., weight_W_muo * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_WG_muo_t_genmatch->Fill(pho0_iso.Pt(), 0., 1., weight_W_muo * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       } else {
         h_WG_muo_pho0_pf_iso_all_nocut_ee->Fill(Photon_pfRelIso03_all[ipho0_iso], weight_W_muo * weight_pho0_iso);
         h_WG_muo_pho0_sieie_nocut_ee->Fill(Photon_sieie[ipho0_iso], weight_W_muo * weight_pho0_iso);
         if (is_pho0_iso) {
           h_WG_muo_t->Fill(pho0_iso.Pt(), 1., 0., weight_W_muo * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_WG_muo_t_genmatch2->Fill(pho0_iso.Pt(), 1., 0., weight_W_muo * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_WG_muo_t_genmatch->Fill(pho0_iso.Pt(), 1., 0., weight_W_muo * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_WG_muo_t->Fill(pho0_iso.Pt(), 1., 1., weight_W_muo * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_WG_muo_t_genmatch2->Fill(pho0_iso.Pt(), 1., 1., weight_W_muo * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_WG_muo_t_genmatch->Fill(pho0_iso.Pt(), 1., 1., weight_W_muo * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       }
     }

     if (ipho1 != -1) {
       if (fabs(pho0.Eta()) < 1.442) {
         if (fabs(pho1.Eta()) < 1.442) {
           h_WGG_muo_pho0_pho1_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           h_WGG_muo_pho0_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           h_WGG_muo_pho1_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_WGG_muo_pho0_pho1_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
             h_WGG_muo_pho0_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
             h_WGG_muo_pho1_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_WGG_muo_pho0_pho1_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           h_WGG_muo_pho0_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           h_WGG_muo_pho1_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_WGG_muo_pho0_pho1_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
             h_WGG_muo_pho0_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
             h_WGG_muo_pho1_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       } else {
         if (fabs(pho1.Eta()) < 1.442) {
           h_WGG_muo_pho0_pho1_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           h_WGG_muo_pho0_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           h_WGG_muo_pho1_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_WGG_muo_pho0_pho1_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
             h_WGG_muo_pho0_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
             h_WGG_muo_pho1_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_WGG_muo_pho0_pho1_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           h_WGG_muo_pho0_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           h_WGG_muo_pho1_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_WGG_muo_pho0_pho1_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
             h_WGG_muo_pho0_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
             h_WGG_muo_pho1_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       }
     }
     if (ipho1_iso != -1) {
       if (fabs(pho0_iso.Eta()) < 1.442) {
         if (fabs(pho1_iso.Eta()) < 1.442) {
           if (is_pho0_iso && !is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         } else {
           if (is_pho0_iso && !is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_be_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_be_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_be_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         }
       } else {
         if (fabs(pho1_iso.Eta()) < 1.442) {
           if (is_pho0_iso && !is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         } else {
           if (is_pho0_iso && !is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_WGG_muo_pho0_pho1_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho0_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             h_WGG_muo_pho1_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_WGG_muo_pho0_pho1_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho0_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
               h_WGG_muo_pho1_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_W_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         }
       }
     }
   }

// Z photon(s) plots

   if (Z_ele_sel) {
     h_Z_ele_nphotons->Fill(n_photons, weight_Z_ele);
     if (ipho0 != -1) {
       h_ZG_ele->Fill(Z_ele0_ele1_m, weight_Z_ele * weight_pho0);
       h_ZG_ele_ele0_pt->Fill(Electron_pt[iele0], weight_Z_ele * weight_pho0);
       h_ZG_ele_pho0_pt->Fill(Photon_pt[ipho0], weight_Z_ele * weight_pho0);
       if (fabs((ele0+ele1+pho0).M() - 91.2) < 5) h_ZG_ele_pho0_pt_fsr_iso->Fill(Photon_pt[ipho0], weight_Z_ele * weight_pho0);
       h_ZG_ele_pho0_eta->Fill(Photon_eta[ipho0], weight_Z_ele * weight_pho0);
       h_ZG_ele_pho0_phi->Fill(Photon_phi[ipho0], weight_Z_ele * weight_pho0);
       h_ZG_ele_pho0_r9->Fill(Photon_r9[ipho0], weight_Z_ele * weight_pho0);
       h_ZG_ele_pho0_sieie->Fill(Photon_sieie[ipho0], weight_Z_ele * weight_pho0);
       h_ZG_ele_pho0_mva->Fill(Photon_mvaID[ipho0], weight_Z_ele * weight_pho0);
       h_ZG_ele_pho0_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho0], weight_Z_ele * weight_pho0);
       h_ZG_ele_pho0_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho0], weight_Z_ele * weight_pho0);
       h_ZG_ele_pho0_dR->Fill(TMath::Min(pho0.DeltaR(ele0), pho0.DeltaR(ele1)), weight_Z_ele * weight_pho0);
       h_ZG_ele_ele0_pho0->Fill((ele0+pho0).M(), weight_Z_ele * weight_pho0);
       h_ZG_ele_ele1_pho0->Fill((ele1+pho0).M(), weight_Z_ele * weight_pho0);
       h_ZG_ele_ele0_ele1_pho0->Fill((ele0+ele1+pho0).M(), weight_Z_ele * weight_pho0);
     }

     if (ipho1 != -1) {
       h_ZGG_ele->Fill(Z_ele0_ele1_m, weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_ele0_pt->Fill(ele0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_ele1_pt->Fill(ele1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho0_pt->Fill(pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho0_eta->Fill(Photon_eta[ipho0], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho0_phi->Fill(Photon_phi[ipho0], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho0_sieie->Fill(Photon_sieie[ipho0], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho0_mva->Fill(Photon_mvaID[ipho0], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho1_pt->Fill(Photon_pt[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho1_eta->Fill(Photon_eta[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho1_phi->Fill(Photon_phi[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho1_r9->Fill(Photon_r9[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho1_sieie->Fill(Photon_sieie[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho1_mva->Fill(Photon_mvaID[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho1_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho1_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho1], weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho1_dR->Fill(TMath::Min(pho1.DeltaR(ele0), pho1.DeltaR(ele1)), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho0_pho1_pt->Fill((pho0+pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho0_pho1->Fill((pho0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_ele0_pho1->Fill((ele0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_ele1_pho1->Fill((ele1+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_ele0_pho0_pho1->Fill((ele0+pho0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_ele1_pho0_pho1->Fill((ele1+pho0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_ele0_ele1_pho0_pho1->Fill((ele0+ele1+pho0+pho1).M(), weight_Z_ele * weight_pho0 * weight_pho1);
       h_ZGG_ele_pho0_pho1_dR->Fill(pho0.DeltaR(pho1), weight_Z_ele * weight_pho0 * weight_pho1);
     }
     if (ipho0_cat != -1 && ipho0 == -1) {
       if (is_iso_pho0 == false) h_ZG_ele_pho0_pt_noiso->Fill(pho0_cat.Pt(), weight_Z_ele * weight_pho0_cat);
     }
     if (ipho1_cat != -1) {
       if (category2d == 0) {
         h_ZGG_ele_pho0_pho1_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho0_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho1_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho0_pt_cat0->Fill(pho0_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho1_pt_cat0->Fill(pho1_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 1) {
         h_ZGG_ele_pho0_pho1_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho0_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho1_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho0_pt_cat1->Fill(pho0_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho1_pt_cat1->Fill(pho1_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 2) {
         h_ZGG_ele_pho0_pho1_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho0_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho1_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho0_pt_cat2->Fill(pho0_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho1_pt_cat2->Fill(pho1_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 3) {
         h_ZGG_ele_pho0_pho1_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho0_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho1_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho0_pt_cat3->Fill(pho0_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_ele_pho1_pt_cat3->Fill(pho1_cat.Pt(), weight_Z_ele * weight_pho0_cat * weight_pho1_cat);
       }
     }
     if (ipho0_iso != -1) {
       if (!is_pho0_iso && (fabs((ele0+ele1+pho0_iso).M() - 91.2) < 5)) h_ZG_ele_pho0_pt_fsr_noiso->Fill(Photon_pt[ipho0_iso], weight_Z_ele * weight_pho0);
       if (fabs(pho0_iso.Eta()) < 1.442) {
         h_ZG_ele_pho0_pf_iso_all_nocut_eb->Fill(Photon_pfRelIso03_all[ipho0_iso], weight_Z_ele * weight_pho0_iso);
         h_ZG_ele_pho0_sieie_nocut_eb->Fill(Photon_sieie[ipho0_iso], weight_Z_ele * weight_pho0_iso);
         if (is_pho0_iso) {
           h_ZG_ele_t->Fill(pho0_iso.Pt(), 0., 0., weight_Z_ele * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_ZG_ele_t_genmatch2->Fill(pho0_iso.Pt(), 0., 0., weight_Z_ele * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_ZG_ele_t_genmatch->Fill(pho0_iso.Pt(), 0., 0., weight_Z_ele * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_ZG_ele_t->Fill(pho0_iso.Pt(), 0., 1., weight_Z_ele * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_ZG_ele_t_genmatch2->Fill(pho0_iso.Pt(), 0., 1., weight_Z_ele * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_ZG_ele_t_genmatch->Fill(pho0_iso.Pt(), 0., 1., weight_Z_ele * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       } else {
         h_ZG_ele_pho0_pf_iso_all_nocut_ee->Fill(Photon_pfRelIso03_all[ipho0_iso], weight_Z_ele * weight_pho0_iso);
         h_ZG_ele_pho0_sieie_nocut_ee->Fill(Photon_sieie[ipho0_iso], weight_Z_ele * weight_pho0_iso);
         if (is_pho0_iso) {
           h_ZG_ele_t->Fill(pho0_iso.Pt(), 1., 0., weight_Z_ele * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_ZG_ele_t_genmatch2->Fill(pho0_iso.Pt(), 1., 0., weight_Z_ele * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_ZG_ele_t_genmatch->Fill(pho0_iso.Pt(), 1., 0., weight_Z_ele * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_ZG_ele_t->Fill(pho0_iso.Pt(), 1., 1., weight_Z_ele * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_ZG_ele_t_genmatch2->Fill(pho0_iso.Pt(), 1., 1., weight_Z_ele * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_ZG_ele_t_genmatch->Fill(pho0_iso.Pt(), 1., 1., weight_Z_ele * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       }
     }

     if (ipho1 != -1) {
       if (fabs(pho0.Eta()) < 1.442) {
         if (fabs(pho1.Eta()) < 1.442) {
           h_ZGG_ele_pho0_pho1_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           h_ZGG_ele_pho0_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           h_ZGG_ele_pho1_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_ZGG_ele_pho0_pho1_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
             h_ZGG_ele_pho0_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
             h_ZGG_ele_pho1_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_ZGG_ele_pho0_pho1_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           h_ZGG_ele_pho0_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           h_ZGG_ele_pho1_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_ZGG_ele_pho0_pho1_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
             h_ZGG_ele_pho0_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
             h_ZGG_ele_pho1_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       } else {
         if (fabs(pho1.Eta()) < 1.442) {
           h_ZGG_ele_pho0_pho1_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           h_ZGG_ele_pho0_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           h_ZGG_ele_pho1_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_ZGG_ele_pho0_pho1_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
             h_ZGG_ele_pho0_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
             h_ZGG_ele_pho1_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_ZGG_ele_pho0_pho1_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           h_ZGG_ele_pho0_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           h_ZGG_ele_pho1_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_ZGG_ele_pho0_pho1_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
             h_ZGG_ele_pho0_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
             h_ZGG_ele_pho1_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       }
     }
     if (ipho1_iso != -1) {
       if (fabs(pho0_iso.Eta()) < 1.442) {
         if (fabs(pho1_iso.Eta()) < 1.442) {
           if (is_pho0_iso && !is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         } else {
           if (is_pho0_iso && !is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_be_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_be_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_be_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         }
       } else {
         if (fabs(pho1_iso.Eta()) < 1.442) {
           if (is_pho0_iso && !is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         } else {
           if (is_pho0_iso && !is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_ZGG_ele_pho0_pho1_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho0_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_ele_pho1_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_ele_pho0_pho1_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho0_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_ele_pho1_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_ele * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         }
       }
     }
   }

   if (Z_muo_sel) {
     h_Z_muo_nphotons->Fill(n_photons, weight_Z_muo);
     if (ipho0 != -1) {
       h_ZG_muo->Fill(Z_muo0_muo1_m, weight_Z_muo * weight_pho0);
       h_ZG_muo_muo0_pt->Fill(Muon_pt[imuo0], weight_Z_muo * weight_pho0);
       h_ZG_muo_pho0_pt->Fill(Photon_pt[ipho0], weight_Z_muo * weight_pho0);
       if (fabs((muo0+muo1+pho0).M() - 91.2) < 5) h_ZG_muo_pho0_pt_fsr_iso->Fill(Photon_pt[ipho0], weight_Z_muo * weight_pho0);
       h_ZG_muo_pho0_eta->Fill(Photon_eta[ipho0], weight_Z_muo * weight_pho0);
       h_ZG_muo_pho0_phi->Fill(Photon_phi[ipho0], weight_Z_muo * weight_pho0);
       h_ZG_muo_pho0_r9->Fill(Photon_r9[ipho0], weight_Z_muo * weight_pho0);
       h_ZG_muo_pho0_sieie->Fill(Photon_sieie[ipho0], weight_Z_muo * weight_pho0);
       h_ZG_muo_pho0_mva->Fill(Photon_mvaID[ipho0], weight_Z_muo * weight_pho0);
       h_ZG_muo_pho0_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho0], weight_Z_muo * weight_pho0);
       h_ZG_muo_pho0_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho0], weight_Z_muo * weight_pho0);
       h_ZG_muo_pho0_dR->Fill(TMath::Min(pho0.DeltaR(muo0), pho0.DeltaR(muo1)), weight_Z_muo * weight_pho0);
       h_ZG_muo_muo0_pho0->Fill((muo0+pho0).M(), weight_Z_muo * weight_pho0);
       h_ZG_muo_muo1_pho0->Fill((muo1+pho0).M(), weight_Z_muo * weight_pho0);
       h_ZG_muo_muo0_muo1_pho0->Fill((muo0+muo1+pho0).M(), weight_Z_muo * weight_pho0);
     }

     if (ipho1 != -1) {
       h_ZGG_muo->Fill(Z_muo0_muo1_m, weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_muo0_pt->Fill(muo0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_muo1_pt->Fill(muo1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho0_pt->Fill(pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho0_eta->Fill(Photon_eta[ipho0], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho0_phi->Fill(Photon_phi[ipho0], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho0_sieie->Fill(Photon_sieie[ipho0], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho0_mva->Fill(Photon_mvaID[ipho0], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho1_pt->Fill(Photon_pt[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho1_eta->Fill(Photon_eta[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho1_phi->Fill(Photon_phi[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho1_r9->Fill(Photon_r9[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho1_sieie->Fill(Photon_sieie[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho1_mva->Fill(Photon_mvaID[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho1_pf_iso_all->Fill(Photon_pfRelIso03_all[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho1_pf_iso_chg->Fill(Photon_pfRelIso03_chg[ipho1], weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho1_dR->Fill(TMath::Min(pho1.DeltaR(muo0), pho1.DeltaR(muo1)), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho0_pho1_pt->Fill((pho0+pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho0_pho1->Fill((pho0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_muo0_pho1->Fill((muo0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_muo1_pho1->Fill((muo1+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_muo0_pho0_pho1->Fill((muo0+pho0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_muo1_pho0_pho1->Fill((muo1+pho0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_muo0_muo1_pho0_pho1->Fill((muo0+muo1+pho0+pho1).M(), weight_Z_muo * weight_pho0 * weight_pho1);
       h_ZGG_muo_pho0_pho1_dR->Fill(pho0.DeltaR(pho1), weight_Z_muo * weight_pho0 * weight_pho1);
     }
     if (ipho0_cat != -1 && ipho0 == -1) {
       if (is_iso_pho0 == false) h_ZG_muo_pho0_pt_noiso->Fill(pho0_cat.Pt(), weight_Z_muo * weight_pho0_cat);
     }
     if (ipho1_cat != -1) {
       if (category2d == 0) {
         h_ZGG_muo_pho0_pho1_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho0_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho1_pt_cat0_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho0_pt_cat0->Fill(pho0_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho1_pt_cat0->Fill(pho1_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 1) {
         h_ZGG_muo_pho0_pho1_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho0_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho1_pt_cat1_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho0_pt_cat1->Fill(pho0_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho1_pt_cat1->Fill(pho1_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 2) {
         h_ZGG_muo_pho0_pho1_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho0_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho1_pt_cat2_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho0_pt_cat2->Fill(pho0_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho1_pt_cat2->Fill(pho1_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
       }
       if (category2d == 3) {
         h_ZGG_muo_pho0_pho1_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), (pho0_cat + pho1_cat).Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho0_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho0_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho1_pt_cat3_map->Fill(pho0_cat.Pt(), pho1_cat.Pt(), pho1_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho0_pt_cat3->Fill(pho0_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
         h_ZGG_muo_pho1_pt_cat3->Fill(pho1_cat.Pt(), weight_Z_muo * weight_pho0_cat * weight_pho1_cat);
       }
     }
     if (ipho0_iso != -1) {
       if (!is_pho0_iso && (fabs((muo0+muo1+pho0_iso).M() - 91.2) < 5)) h_ZG_muo_pho0_pt_fsr_noiso->Fill(Photon_pt[ipho0_iso], weight_Z_muo * weight_pho0);
       if (fabs(pho0_iso.Eta()) < 1.442) {
         h_ZG_muo_pho0_pf_iso_all_nocut_eb->Fill(Photon_pfRelIso03_all[ipho0_iso], weight_Z_muo * weight_pho0_iso);
         h_ZG_muo_pho0_sieie_nocut_eb->Fill(Photon_sieie[ipho0_iso], weight_Z_muo * weight_pho0_iso);
         if (is_pho0_iso) {
           h_ZG_muo_t->Fill(pho0_iso.Pt(), 0., 0., weight_Z_muo * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_ZG_muo_t_genmatch2->Fill(pho0_iso.Pt(), 0., 0., weight_Z_muo * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_ZG_muo_t_genmatch->Fill(pho0_iso.Pt(), 0., 0., weight_Z_muo * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_ZG_muo_t->Fill(pho0_iso.Pt(), 0., 1., weight_Z_muo * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_ZG_muo_t_genmatch2->Fill(pho0_iso.Pt(), 0., 1., weight_Z_muo * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_ZG_muo_t_genmatch->Fill(pho0_iso.Pt(), 0., 1., weight_Z_muo * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       } else {
         h_ZG_muo_pho0_pf_iso_all_nocut_ee->Fill(Photon_pfRelIso03_all[ipho0_iso], weight_Z_muo * weight_pho0_iso);
         h_ZG_muo_pho0_sieie_nocut_ee->Fill(Photon_sieie[ipho0_iso], weight_Z_muo * weight_pho0_iso);
         if (is_pho0_iso) {
           h_ZG_muo_t->Fill(pho0_iso.Pt(), 1., 0., weight_Z_muo * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_ZG_muo_t_genmatch2->Fill(pho0_iso.Pt(), 1., 0., weight_Z_muo * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_ZG_muo_t_genmatch->Fill(pho0_iso.Pt(), 1., 0., weight_Z_muo * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_ZG_muo_t->Fill(pho0_iso.Pt(), 1., 1., weight_Z_muo * weight_pho0_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if (ipho0_iso != -1 && Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart) {
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) {
               h_ZG_muo_t_genmatch2->Fill(pho0_iso.Pt(), 1., 1., weight_Z_muo * weight_pho0_iso);
             }
             if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 22) {
               h_ZG_muo_t_genmatch->Fill(pho0_iso.Pt(), 1., 1., weight_Z_muo * weight_pho0_iso);
             }
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       }
     }

     if (ipho1 != -1) {
       if (fabs(pho0.Eta()) < 1.442) {
         if (fabs(pho1.Eta()) < 1.442) {
           h_ZGG_muo_pho0_pho1_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           h_ZGG_muo_pho0_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           h_ZGG_muo_pho1_pt_bb_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_ZGG_muo_pho0_pho1_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
             h_ZGG_muo_pho0_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
             h_ZGG_muo_pho1_pt_bb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_ZGG_muo_pho0_pho1_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           h_ZGG_muo_pho0_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           h_ZGG_muo_pho1_pt_be_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_ZGG_muo_pho0_pho1_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
             h_ZGG_muo_pho0_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
             h_ZGG_muo_pho1_pt_be_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       } else {
         if (fabs(pho1.Eta()) < 1.442) {
           h_ZGG_muo_pho0_pho1_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           h_ZGG_muo_pho0_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           h_ZGG_muo_pho1_pt_eb_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_ZGG_muo_pho0_pho1_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
             h_ZGG_muo_pho0_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
             h_ZGG_muo_pho1_pt_eb_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         } else {
           h_ZGG_muo_pho0_pho1_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           h_ZGG_muo_pho0_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           h_ZGG_muo_pho1_pt_ee_tt->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
               (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
             h_ZGG_muo_pho0_pho1_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), (pho0 + pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
             h_ZGG_muo_pho0_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
             h_ZGG_muo_pho1_pt_ee_tt_genmatch2->Fill(pho0.Pt(), pho1.Pt(), pho1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
         }
       }
     }
     if (ipho1_iso != -1) {
       if (fabs(pho0_iso.Eta()) < 1.442) {
         if (fabs(pho1_iso.Eta()) < 1.442) {
           if (is_pho0_iso && !is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_bb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_bb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_bb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_bb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_bb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_bb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         } else {
           if (is_pho0_iso && !is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_be_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_be_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_be_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_be_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_be_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_be_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_be_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_be_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         }
       } else {
         if (fabs(pho1_iso.Eta()) < 1.442) {
           if (is_pho0_iso && !is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_eb_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_eb_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_eb_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_eb_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_eb_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_eb_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         } else {
           if (is_pho0_iso && !is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_ee_tl->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_ee_tl_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_ee_lt->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_ee_lt_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
           if (!is_pho0_iso && !is_pho1_iso) {
             h_ZGG_muo_pho0_pho1_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho0_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             h_ZGG_muo_pho1_pt_ee_ll->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
             if ((Photon_genPartIdx[ipho0_iso] >= 0 && (uint)Photon_genPartIdx[ipho0_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_iso]]) == 11) ||
                 (Photon_genPartIdx[ipho1_iso] >= 0 && (uint)Photon_genPartIdx[ipho1_iso] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1_iso]]) == 11)) {
               h_ZGG_muo_pho0_pho1_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), (pho0_iso + pho1_iso).Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho0_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho0_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
               h_ZGG_muo_pho1_pt_ee_ll_genmatch2->Fill(pho0_iso.Pt(), pho1_iso.Pt(), pho1_iso.Pt(), weight_Z_muo * weight_pho0_iso * weight_pho1_iso);
             }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
           }
         }
       }
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
         h_WG_ele_pho0_jet0_dR->Fill(pho0.DeltaR(jet0), weight_W_ele * weight_pho0);
       }
       if (ipho1 != -1) {
         h_WGG_ele_pho1_jet0_dR->Fill(pho1.DeltaR(jet0), weight_W_ele * weight_pho0 * weight_pho1);
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
         h_WG_muo_pho0_jet0_dR->Fill(pho0.DeltaR(jet0), weight_W_muo * weight_pho0);
       }
       if (ipho1 != -1) {
         h_WGG_muo_pho1_jet0_dR->Fill(pho1.DeltaR(jet0), weight_W_muo * weight_pho0 * weight_pho1);
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
         h_ZG_ele_pho0_jet0_dR->Fill(pho0.DeltaR(jet0), weight_Z_ele * weight_pho0);
       }
       if (ipho1 != -1) {
         h_ZGG_ele_pho1_jet0_dR->Fill(pho1.DeltaR(jet0), weight_Z_ele * weight_pho0 * weight_pho1);
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
         h_ZG_muo_pho0_jet0_dR->Fill(pho0.DeltaR(jet0), weight_Z_muo * weight_pho0);
       }
       if (ipho1 != -1) {
         h_ZGG_muo_pho1_jet0_dR->Fill(pho1.DeltaR(jet0), weight_Z_muo * weight_pho0 * weight_pho1);
       }
     }
   }

// W plots QCD

   if (W_ele_sel_qcd) {
     QCD(h_W_ele)->Fill(W_ele0_mt_qcd, weight_W_ele_qcd);
     QCD(h_W_ele_met_pt)->Fill(*MET_pt, weight_W_ele_qcd);
     QCD(h_W_ele_met_phi)->Fill(*MET_phi, weight_W_ele_qcd);
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

   if (W_muo_sel_qcd) {
     QCD(h_W_muo)->Fill(W_muo0_mt_qcd, weight_W_muo_qcd);
     QCD(h_W_muo_met_pt)->Fill(*MET_pt, weight_W_muo_qcd);
     QCD(h_W_muo_met_phi)->Fill(*MET_phi, weight_W_muo_qcd);
     QCD(h_W_muo_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_W_muo_npvs_w)->Fill(*PV_npvsGood, weight_W_muo_qcd);
     QCD(h_W_muo0_pt)->Fill(Muon_pt[imuo0_qcd], weight_W_muo_qcd);
     QCD(h_W_muo0_eta)->Fill(Muon_eta[imuo0_qcd], weight_W_muo_qcd);
     QCD(h_W_muo0_phi)->Fill(Muon_phi[imuo0_qcd], weight_W_muo_qcd);
     QCD(h_W_muo0_pf_iso_all)->Fill(Muon_pfRelIso03_all[imuo0_qcd], weight_W_muo_qcd);
     QCD(h_W_muo0_pf_iso_chg)->Fill(Muon_pfRelIso03_chg[imuo0_qcd], weight_W_muo_qcd);
   }

// Z plots QCD

   if (Z_ele_sel_qcd) {
     QCD(h_Z_ele)->Fill(Z_ele0_ele1_m_qcd, weight_Z_ele_qcd);
     QCD(h_Z_ele_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_Z_ele_npvs_w)->Fill(*PV_npvsGood, weight_Z_ele_qcd);
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

   if (Z_muo_sel_qcd) {
     QCD(h_Z_muo)->Fill(Z_muo0_muo1_m_qcd, weight_Z_muo_qcd);
     QCD(h_Z_muo_npvs)->Fill(*PV_npvsGood, weight_gen);
     QCD(h_Z_muo_npvs_w)->Fill(*PV_npvsGood, weight_Z_muo_qcd);
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

// W photon(s) plots QCD

   if (W_ele_sel_qcd) {
     QCD(h_W_ele_nphotons)->Fill(n_photons_qcd, weight_W_ele_qcd);
     if (ipho0_qcd != -1) {
       QCD(h_WG_ele)->Fill(W_ele0_mt_qcd, weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_ele0_pt)->Fill(Electron_pt[iele0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_pho0_pt)->Fill(Photon_pt[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_pho0_r9)->Fill(Photon_r9[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_pho0_dR)->Fill(pho0_qcd.DeltaR(ele0_qcd), weight_W_ele_qcd * weight_pho0_qcd);
       QCD(h_WG_ele_ele0_pho0)->Fill((ele0_qcd+pho0_qcd).M(), weight_W_ele_qcd * weight_pho0_qcd);
     }
     if (ipho0_fake_qcd != -1) {
       QCD(h_WG_ele_ele0_pho0_fake)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
#if defined(COMPUTE_EG_MISID)
       if (Photon_pt[ipho0_fake_qcd] > 20 && Photon_pt[ipho0_fake_qcd] < 30) {
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 0. && fabs(Photon_eta[ipho0_fake_qcd]) < 0.5)    QCD(h_WG_ele_fake_1)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 0.5 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.0)   QCD(h_WG_ele_fake_2)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.442) QCD(h_WG_ele_fake_3)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.566 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.0) QCD(h_WG_ele_fake_4)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 2.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.5)   QCD(h_WG_ele_fake_5)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
       }
       if (Photon_pt[ipho0_fake_qcd] > 30 && Photon_pt[ipho0_fake_qcd] < 40) {
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 0. && fabs(Photon_eta[ipho0_fake_qcd]) < 0.5)    QCD(h_WG_ele_fake_6)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 0.5 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.0)   QCD(h_WG_ele_fake_7)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.442) QCD(h_WG_ele_fake_8)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.566 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.0) QCD(h_WG_ele_fake_9)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 2.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.5)   QCD(h_WG_ele_fake_10)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
       }
       if (Photon_pt[ipho0_fake_qcd] > 40 && Photon_pt[ipho0_fake_qcd] < 50) {
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 0. && fabs(Photon_eta[ipho0_fake_qcd]) < 0.5)    QCD(h_WG_ele_fake_11)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 0.5 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.0)   QCD(h_WG_ele_fake_12)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.442) QCD(h_WG_ele_fake_13)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.566 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.0) QCD(h_WG_ele_fake_14)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 2.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.5)   QCD(h_WG_ele_fake_15)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
       }
       if (Photon_pt[ipho0_fake_qcd] > 50) {
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 0. && fabs(Photon_eta[ipho0_fake_qcd]) < 0.5)    QCD(h_WG_ele_fake_16)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 0.5 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.0)   QCD(h_WG_ele_fake_17)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.442) QCD(h_WG_ele_fake_18)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.566 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.0) QCD(h_WG_ele_fake_19)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         if (fabs(Photon_eta[ipho0_fake_qcd]) > 2.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.5)   QCD(h_WG_ele_fake_20)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
       }
#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
       if (Photon_genPartIdx[ipho0_fake_qcd] >= 0 && (uint)Photon_genPartIdx[ipho0_fake_qcd] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0_fake_qcd]]) == 11) {
         if (Photon_pt[ipho0_fake_qcd] > 20 && Photon_pt[ipho0_fake_qcd] < 30) {
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 0. && fabs(Photon_eta[ipho0_fake_qcd]) < 0.5)    QCD(h_WG_ele_fake_truthmatch_1)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 0.5 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.0)   QCD(h_WG_ele_fake_truthmatch_2)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.442) QCD(h_WG_ele_fake_truthmatch_3)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.566 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.0) QCD(h_WG_ele_fake_truthmatch_4)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 2.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.5)   QCD(h_WG_ele_fake_truthmatch_5)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         }
         if (Photon_pt[ipho0_fake_qcd] > 30 && Photon_pt[ipho0_fake_qcd] < 40) {
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 0. && fabs(Photon_eta[ipho0_fake_qcd]) < 0.5)    QCD(h_WG_ele_fake_truthmatch_6)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 0.5 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.0)   QCD(h_WG_ele_fake_truthmatch_7)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.442) QCD(h_WG_ele_fake_truthmatch_8)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.566 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.0) QCD(h_WG_ele_fake_truthmatch_9)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 2.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.5)   QCD(h_WG_ele_fake_truthmatch_10)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         }
         if (Photon_pt[ipho0_fake_qcd] > 40 && Photon_pt[ipho0_fake_qcd] < 50) {
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 0. && fabs(Photon_eta[ipho0_fake_qcd]) < 0.5)    QCD(h_WG_ele_fake_truthmatch_11)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 0.5 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.0)   QCD(h_WG_ele_fake_truthmatch_12)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.442) QCD(h_WG_ele_fake_truthmatch_13)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.566 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.0) QCD(h_WG_ele_fake_truthmatch_14)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 2.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.5)   QCD(h_WG_ele_fake_truthmatch_15)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         }
         if (Photon_pt[ipho0_fake_qcd] > 50) {
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 0. && fabs(Photon_eta[ipho0_fake_qcd]) < 0.5)    QCD(h_WG_ele_fake_truthmatch_16)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 0.5 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.0)   QCD(h_WG_ele_fake_truthmatch_17)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 1.442) QCD(h_WG_ele_fake_truthmatch_18)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 1.566 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.0) QCD(h_WG_ele_fake_truthmatch_19)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
           if (fabs(Photon_eta[ipho0_fake_qcd]) > 2.0 && fabs(Photon_eta[ipho0_fake_qcd]) < 2.5)   QCD(h_WG_ele_fake_truthmatch_20)->Fill((ele0_qcd+pho0_fake_qcd).M(), weight_W_ele_qcd * weight_pho0_fake_qcd);
         }
       }
#endif // defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
#endif // defined(COMPUTE_EG_MISID)
     }

     if (ipho1_qcd != -1) {
       QCD(h_WGG_ele)->Fill(W_ele0_mt_qcd, weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_ele0_pt)->Fill(ele0_qcd.Pt(), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho0_pt)->Fill(pho0_qcd.Pt(), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho1_pt)->Fill(Photon_pt[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho1_eta)->Fill(Photon_eta[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho1_phi)->Fill(Photon_phi[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho1_r9)->Fill(Photon_r9[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho1_sieie)->Fill(Photon_sieie[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho1_mva)->Fill(Photon_mvaID[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1_qcd], weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho1_dR)->Fill(pho1_qcd.DeltaR(ele0_qcd), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho0_pho1_pt)->Fill((pho0_qcd+pho1_qcd).Pt(), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho0_pho1)->Fill((pho0_qcd+pho1_qcd).M(), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_ele0_pho0)->Fill((ele0_qcd+pho0_qcd).M(), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_ele0_pho1)->Fill((ele0_qcd+pho1_qcd).M(), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_ele0_pho0_pho1)->Fill((ele0_qcd+pho0_qcd+pho1_qcd).M(), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_ele_pho0_pho1_dR)->Fill(pho0_qcd.DeltaR(pho1_qcd), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
     }
     if (ipho0_cat_qcd != -1 && ipho0_qcd == -1) {
       if (is_iso_pho0_qcd == false) QCD(h_WG_ele_pho0_pt_noiso)->Fill(pho0_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd);
     }
     if (ipho1_cat_qcd != -1) {
       if (category2d == 0) {
         QCD3(h_WGG_ele_pho0_pho1_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_ele_pho0_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_ele_pho1_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_ele_pho0_pt_cat0)->Fill(pho0_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_ele_pho1_pt_cat0)->Fill(pho1_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 1) {
         QCD3(h_WGG_ele_pho0_pho1_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_ele_pho0_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_ele_pho1_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_ele_pho0_pt_cat1)->Fill(pho0_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_ele_pho1_pt_cat1)->Fill(pho1_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 2) {
         QCD3(h_WGG_ele_pho0_pho1_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_ele_pho0_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_ele_pho1_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_ele_pho0_pt_cat2)->Fill(pho0_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_ele_pho1_pt_cat2)->Fill(pho1_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 3) {
         QCD3(h_WGG_ele_pho0_pho1_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_ele_pho0_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_ele_pho1_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_ele_pho0_pt_cat3)->Fill(pho0_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_ele_pho1_pt_cat3)->Fill(pho1_cat_qcd.Pt(), weight_W_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
     }
     if (ipho0_iso_qcd != -1) {
       if (fabs(pho0_iso_qcd.Eta()) < 1.442) {
         QCD(h_WG_ele_pho0_pf_iso_all_nocut_eb)->Fill(Photon_pfRelIso03_all[ipho0_iso_qcd], weight_W_ele_qcd * weight_pho0_iso_qcd);
         QCD(h_WG_ele_pho0_sieie_nocut_eb)->Fill(Photon_sieie[ipho0_iso_qcd], weight_W_ele_qcd * weight_pho0_iso_qcd);
       } else {
         QCD(h_WG_ele_pho0_pf_iso_all_nocut_ee)->Fill(Photon_pfRelIso03_all[ipho0_iso_qcd], weight_W_ele_qcd * weight_pho0_iso_qcd);
         QCD(h_WG_ele_pho0_sieie_nocut_ee)->Fill(Photon_sieie[ipho0_iso_qcd], weight_W_ele_qcd * weight_pho0_iso_qcd);
       }
     }
   }

   if (W_muo_sel_qcd) {
     QCD(h_W_muo_nphotons)->Fill(n_photons_qcd, weight_W_muo_qcd);
     if (ipho0_qcd != -1) {
       QCD(h_WG_muo)->Fill(W_muo0_mt_qcd, weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_muo0_pt)->Fill(Muon_pt[imuo0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_pho0_pt)->Fill(Photon_pt[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_pho0_r9)->Fill(Photon_r9[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_pho0_dR)->Fill(pho0_qcd.DeltaR(muo0_qcd), weight_W_muo_qcd * weight_pho0_qcd);
       QCD(h_WG_muo_muo0_pho0)->Fill((muo0_qcd+pho0_qcd).M(), weight_W_muo_qcd * weight_pho0_qcd);
     }
     if (ipho0_fake_qcd != -1) {
       QCD(h_WG_muo_muo0_pho0_fake)->Fill((muo0_qcd+pho0_fake_qcd).M(), weight_W_muo_qcd * weight_pho0_fake_qcd);
     }

     if (ipho1_qcd != -1) {
       QCD(h_WGG_muo)->Fill(W_muo0_mt_qcd, weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_muo0_pt)->Fill(muo0_qcd.Pt(), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho0_pt)->Fill(pho0_qcd.Pt(), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho1_pt)->Fill(Photon_pt[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho1_eta)->Fill(Photon_eta[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho1_phi)->Fill(Photon_phi[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho1_r9)->Fill(Photon_r9[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho1_sieie)->Fill(Photon_sieie[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho1_mva)->Fill(Photon_mvaID[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1_qcd], weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho1_dR)->Fill(pho1_qcd.DeltaR(muo0_qcd), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho0_pho1_pt)->Fill((pho0_qcd+pho1_qcd).Pt(), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho0_pho1)->Fill((pho0_qcd+pho1_qcd).M(), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_muo0_pho0)->Fill((muo0_qcd+pho0_qcd).M(), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_muo0_pho1)->Fill((muo0_qcd+pho1_qcd).M(), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_muo0_pho0_pho1)->Fill((muo0_qcd+pho0_qcd+pho1_qcd).M(), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_WGG_muo_pho0_pho1_dR)->Fill(pho0_qcd.DeltaR(pho1_qcd), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
     }
     if (ipho0_cat_qcd != -1 && ipho0_qcd == -1) {
       if (is_iso_pho0_qcd == false) QCD(h_WG_muo_pho0_pt_noiso)->Fill(pho0_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd);
     }
     if (ipho1_cat_qcd != -1) {
       if (category2d == 0) {
         QCD3(h_WGG_muo_pho0_pho1_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_muo_pho0_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_muo_pho1_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_muo_pho0_pt_cat0)->Fill(pho0_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_muo_pho1_pt_cat0)->Fill(pho1_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 1) {
         QCD3(h_WGG_muo_pho0_pho1_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_muo_pho0_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_muo_pho1_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_muo_pho0_pt_cat1)->Fill(pho0_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_muo_pho1_pt_cat1)->Fill(pho1_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 2) {
         QCD3(h_WGG_muo_pho0_pho1_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_muo_pho0_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_muo_pho1_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_muo_pho0_pt_cat2)->Fill(pho0_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_muo_pho1_pt_cat2)->Fill(pho1_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 3) {
         QCD3(h_WGG_muo_pho0_pho1_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_muo_pho0_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_WGG_muo_pho1_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_muo_pho0_pt_cat3)->Fill(pho0_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_WGG_muo_pho1_pt_cat3)->Fill(pho1_cat_qcd.Pt(), weight_W_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
     }
     if (ipho0_iso_qcd != -1) {
       if (fabs(pho0_iso_qcd.Eta()) < 1.442) {
         QCD(h_WG_muo_pho0_pf_iso_all_nocut_eb)->Fill(Photon_pfRelIso03_all[ipho0_iso_qcd], weight_W_muo_qcd * weight_pho0_iso_qcd);
         QCD(h_WG_muo_pho0_sieie_nocut_eb)->Fill(Photon_sieie[ipho0_iso_qcd], weight_W_muo_qcd * weight_pho0_iso_qcd);
       } else {
         QCD(h_WG_muo_pho0_pf_iso_all_nocut_ee)->Fill(Photon_pfRelIso03_all[ipho0_iso_qcd], weight_W_muo_qcd * weight_pho0_iso_qcd);
         QCD(h_WG_muo_pho0_sieie_nocut_ee)->Fill(Photon_sieie[ipho0_iso_qcd], weight_W_muo_qcd * weight_pho0_iso_qcd);
       }
     }
   }

// Z photon(s) plots QCD

   if (Z_ele_sel_qcd) {
     QCD(h_Z_ele_nphotons)->Fill(n_photons_qcd, weight_Z_ele_qcd);
     if (ipho0_qcd != -1) {
       QCD(h_ZG_ele)->Fill(Z_ele0_ele1_m_qcd, weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_ele0_pt)->Fill(Electron_pt[iele0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_pho0_pt)->Fill(Photon_pt[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_pho0_r9)->Fill(Photon_r9[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_pho0_dR)->Fill(TMath::Min(pho0_qcd.DeltaR(ele0_qcd), pho0_qcd.DeltaR(ele1_qcd)), weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_ele0_pho0)->Fill((ele0_qcd+pho0_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_ele1_pho0)->Fill((ele1_qcd+pho0_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd);
       QCD(h_ZG_ele_ele0_ele1_pho0)->Fill((ele0_qcd+ele1_qcd+pho0_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd);
     }
     if (ipho1_qcd != -1) {
       QCD(h_ZGG_ele)->Fill(Z_ele0_ele1_m_qcd, weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_ele0_pt)->Fill(ele0_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_ele1_pt)->Fill(ele1_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho0_pt)->Fill(pho0_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho1_pt)->Fill(Photon_pt[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho1_eta)->Fill(Photon_eta[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho1_phi)->Fill(Photon_phi[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho1_r9)->Fill(Photon_r9[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho1_sieie)->Fill(Photon_sieie[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho1_mva)->Fill(Photon_mvaID[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1_qcd], weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho1_dR)->Fill(TMath::Min(pho1_qcd.DeltaR(ele0_qcd), pho1_qcd.DeltaR(ele1_qcd)), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho0_pho1_pt)->Fill((pho0_qcd+pho1_qcd).Pt(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho0_pho1)->Fill((pho0_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_ele0_pho1)->Fill((ele0_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_ele1_pho1)->Fill((ele1_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_ele0_pho0_pho1)->Fill((ele0_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_ele1_pho0_pho1)->Fill((ele1_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_ele0_ele1_pho0_pho1)->Fill((ele0_qcd+ele1_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_ele_pho0_pho1_dR)->Fill(pho0_qcd.DeltaR(pho1_qcd), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
     }
     if (ipho0_cat_qcd != -1 && ipho0_qcd == -1) {
       if (is_iso_pho0_qcd == false) QCD(h_ZG_ele_pho0_pt_noiso)->Fill(pho0_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd);
     }
     if (ipho1_cat_qcd != -1) {
       if (category2d == 0) {
         QCD3(h_ZGG_ele_pho0_pho1_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_ele_pho0_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_ele_pho1_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_ele_pho0_pt_cat0)->Fill(pho0_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_ele_pho1_pt_cat0)->Fill(pho1_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 1) {
         QCD3(h_ZGG_ele_pho0_pho1_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_ele_pho0_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_ele_pho1_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_ele_pho0_pt_cat1)->Fill(pho0_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_ele_pho1_pt_cat1)->Fill(pho1_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 2) {
         QCD3(h_ZGG_ele_pho0_pho1_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_ele_pho0_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_ele_pho1_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_ele_pho0_pt_cat2)->Fill(pho0_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_ele_pho1_pt_cat2)->Fill(pho1_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 3) {
         QCD3(h_ZGG_ele_pho0_pho1_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_ele_pho0_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_ele_pho1_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_ele_pho0_pt_cat3)->Fill(pho0_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_ele_pho1_pt_cat3)->Fill(pho1_cat_qcd.Pt(), weight_Z_ele_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
     }
     if (ipho0_iso_qcd != -1) {
       if (fabs(pho0_iso_qcd.Eta()) < 1.442) {
         QCD(h_ZG_ele_pho0_pf_iso_all_nocut_eb)->Fill(Photon_pfRelIso03_all[ipho0_iso_qcd], weight_Z_ele_qcd * weight_pho0_iso_qcd);
         QCD(h_ZG_ele_pho0_sieie_nocut_eb)->Fill(Photon_sieie[ipho0_iso_qcd], weight_Z_ele_qcd * weight_pho0_iso_qcd);
       } else {
         QCD(h_ZG_ele_pho0_pf_iso_all_nocut_ee)->Fill(Photon_pfRelIso03_all[ipho0_iso_qcd], weight_Z_ele_qcd * weight_pho0_iso_qcd);
         QCD(h_ZG_ele_pho0_sieie_nocut_ee)->Fill(Photon_sieie[ipho0_iso_qcd], weight_Z_ele_qcd * weight_pho0_iso_qcd);
       }
     }
   }

   if (Z_muo_sel_qcd) {
     QCD(h_Z_muo_nphotons)->Fill(n_photons_qcd, weight_Z_muo_qcd);
     if (ipho0_qcd != -1) {
       QCD(h_ZG_muo)->Fill(Z_muo0_muo1_m_qcd, weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_muo0_pt)->Fill(Muon_pt[imuo0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_pho0_pt)->Fill(Photon_pt[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_pho0_r9)->Fill(Photon_r9[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_pho0_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_pho0_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_pho0_dR)->Fill(TMath::Min(pho0_qcd.DeltaR(muo0_qcd), pho0_qcd.DeltaR(muo1_qcd)), weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_muo0_pho0)->Fill((muo0_qcd+pho0_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_muo1_pho0)->Fill((muo1_qcd+pho0_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd);
       QCD(h_ZG_muo_muo0_muo1_pho0)->Fill((muo0_qcd+muo1_qcd+pho0_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd);
     }
     if (ipho1_qcd != -1) {
       QCD(h_ZGG_muo)->Fill(Z_muo0_muo1_m_qcd, weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_muo0_pt)->Fill(muo0_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_muo1_pt)->Fill(muo1_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho0_pt)->Fill(pho0_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho0_eta)->Fill(Photon_eta[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho0_phi)->Fill(Photon_phi[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho0_sieie)->Fill(Photon_sieie[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho0_mva)->Fill(Photon_mvaID[ipho0_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho1_pt)->Fill(Photon_pt[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho1_eta)->Fill(Photon_eta[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho1_phi)->Fill(Photon_phi[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho1_r9)->Fill(Photon_r9[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho1_sieie)->Fill(Photon_sieie[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho1_mva)->Fill(Photon_mvaID[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho1_pf_iso_all)->Fill(Photon_pfRelIso03_all[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho1_pf_iso_chg)->Fill(Photon_pfRelIso03_chg[ipho1_qcd], weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho1_dR)->Fill(TMath::Min(pho1_qcd.DeltaR(muo0_qcd), pho1_qcd.DeltaR(muo1_qcd)), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho0_pho1_pt)->Fill((pho0_qcd+pho1_qcd).Pt(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho0_pho1)->Fill((pho0_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_muo0_pho1)->Fill((muo0_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_muo1_pho1)->Fill((muo1_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_muo0_pho0_pho1)->Fill((muo0_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_muo1_pho0_pho1)->Fill((muo1_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_muo0_muo1_pho0_pho1)->Fill((muo0_qcd+muo1_qcd+pho0_qcd+pho1_qcd).M(), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       QCD(h_ZGG_muo_pho0_pho1_dR)->Fill(pho0_qcd.DeltaR(pho1_qcd), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
     }
     if (ipho0_cat_qcd != -1 && ipho0_qcd == -1) {
       if (is_iso_pho0_qcd == false) QCD(h_ZG_muo_pho0_pt_noiso)->Fill(pho0_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd);
     }
     if (ipho1_cat_qcd != -1) {
       if (category2d == 0) {
         QCD3(h_ZGG_muo_pho0_pho1_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_muo_pho0_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_muo_pho1_pt_cat0_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_muo_pho0_pt_cat0)->Fill(pho0_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_muo_pho1_pt_cat0)->Fill(pho1_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 1) {
         QCD3(h_ZGG_muo_pho0_pho1_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_muo_pho0_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_muo_pho1_pt_cat1_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_muo_pho0_pt_cat1)->Fill(pho0_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_muo_pho1_pt_cat1)->Fill(pho1_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 2) {
         QCD3(h_ZGG_muo_pho0_pho1_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_muo_pho0_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_muo_pho1_pt_cat2_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_muo_pho0_pt_cat2)->Fill(pho0_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_muo_pho1_pt_cat2)->Fill(pho1_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
       if (category2d == 3) {
         QCD3(h_ZGG_muo_pho0_pho1_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), (pho0_cat_qcd + pho1_cat_qcd).Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_muo_pho0_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho0_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD3(h_ZGG_muo_pho1_pt_cat3_map)->Fill(pho0_cat_qcd.Pt(), pho1_cat_qcd.Pt(), pho1_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_muo_pho0_pt_cat3)->Fill(pho0_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
         QCD(h_ZGG_muo_pho1_pt_cat3)->Fill(pho1_cat_qcd.Pt(), weight_Z_muo_qcd * weight_pho0_cat_qcd * weight_pho1_cat_qcd);
       }
     }
     if (ipho0_iso_qcd != -1) {
       if (fabs(pho0_iso_qcd.Eta()) < 1.442) {
         QCD(h_ZG_muo_pho0_pf_iso_all_nocut_eb)->Fill(Photon_pfRelIso03_all[ipho0_iso_qcd], weight_Z_muo_qcd * weight_pho0_iso_qcd);
         QCD(h_ZG_muo_pho0_sieie_nocut_eb)->Fill(Photon_sieie[ipho0_iso_qcd], weight_Z_muo_qcd * weight_pho0_iso_qcd);
       } else {
         QCD(h_ZG_muo_pho0_pf_iso_all_nocut_ee)->Fill(Photon_pfRelIso03_all[ipho0_iso_qcd], weight_Z_muo_qcd * weight_pho0_iso_qcd);
         QCD(h_ZG_muo_pho0_sieie_nocut_ee)->Fill(Photon_sieie[ipho0_iso_qcd], weight_Z_muo_qcd * weight_pho0_iso_qcd);
       }
     }
   }

// W jet(s) plots QCD

   if (W_ele_sel_qcd) {
     QCD(h_W_ele_njets)->Fill(n_jets_qcd, weight_W_ele_qcd);
     if (n_jets_qcd >= 1) {
       QCD(h_W_ele_jet0_pt)->Fill(Jet_pt[ijet0_qcd], weight_W_ele_qcd);
       QCD(h_W_ele_jet0_eta)->Fill(Jet_eta[ijet0_qcd], weight_W_ele_qcd);
       QCD(h_W_ele_jet0_phi)->Fill(Jet_phi[ijet0_qcd], weight_W_ele_qcd);
       if (ipho0_qcd != -1) {
         QCD(h_WG_ele_pho0_jet0_dR)->Fill(pho0_qcd.DeltaR(jet0_qcd), weight_W_ele_qcd * weight_pho0_qcd);
       }
       if (ipho1_qcd != -1) {
         QCD(h_WGG_ele_pho1_jet0_dR)->Fill(pho1_qcd.DeltaR(jet0_qcd), weight_W_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
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
         QCD(h_WG_muo_pho0_jet0_dR)->Fill(pho0_qcd.DeltaR(jet0_qcd), weight_W_muo_qcd * weight_pho0_qcd);
       }
       if (ipho1_qcd != -1) {
         QCD(h_WGG_muo_pho1_jet0_dR)->Fill(pho1_qcd.DeltaR(jet0_qcd), weight_W_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       }
     }
   }

// Z jet(s) plots QCD

   if (Z_ele_sel_qcd) {
     QCD(h_Z_ele_njets)->Fill(n_jets_qcd, weight_Z_ele_qcd);
     if (n_jets_qcd >= 1) {
       QCD(h_Z_ele_jet0_pt)->Fill(Jet_pt[ijet0_qcd], weight_Z_ele_qcd);
       QCD(h_Z_ele_jet0_eta)->Fill(Jet_eta[ijet0_qcd], weight_Z_ele_qcd);
       QCD(h_Z_ele_jet0_phi)->Fill(Jet_phi[ijet0_qcd], weight_Z_ele_qcd);
       if (ipho0_qcd != -1) {
         QCD(h_ZG_ele_pho0_jet0_dR)->Fill(pho0_qcd.DeltaR(jet0_qcd), weight_Z_ele_qcd * weight_pho0_qcd);
       }
       if (ipho1_qcd != -1) {
         QCD(h_ZGG_ele_pho1_jet0_dR)->Fill(pho1_qcd.DeltaR(jet0_qcd), weight_Z_ele_qcd * weight_pho0_qcd * weight_pho1_qcd);
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
         QCD(h_ZG_muo_pho0_jet0_dR)->Fill(pho0_qcd.DeltaR(jet0_qcd), weight_Z_muo_qcd * weight_pho0_qcd);
       }
       if (ipho1_qcd != -1) {
         QCD(h_ZGG_muo_pho1_jet0_dR)->Fill(pho1_qcd.DeltaR(jet0_qcd), weight_Z_muo_qcd * weight_pho0_qcd * weight_pho1_qcd);
       }
     }
   }

#if defined(mainSelectorMC16_cxx) || defined(mainSelectorMC17_cxx) || defined(mainSelectorMC18_cxx)
   if (W_ele_sel) {
     if (ipho0 != -1) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 22) {
         h_WG_ele_pho0_pt_genmatch->Fill(pho0.Pt(), weight_W_ele * weight_pho0);
       }
     }
     if (ipho1 != -1) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 22) {
         if (GenPart_pt[Photon_genPartIdx[ipho0]] > 20) {
           if (Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 22) {
             if (GenPart_pt[Photon_genPartIdx[ipho1]] > 20) {
               h_WGG_ele_pho0_pt_genmatch->Fill(pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
               h_WGG_ele_pho1_pt_genmatch->Fill(pho1.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
               h_WGG_ele_pho0_pho1_pt_genmatch->Fill((pho0+pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
             }
           }
         }
       }
     }
   }

   if (W_muo_sel) {
     if (ipho0 != -1) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 22) {
         h_WG_muo_pho0_pt_genmatch->Fill(pho0.Pt(), weight_W_muo * weight_pho0);
       }
     }
     if (ipho1 != -1) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 22) {
         if (GenPart_pt[Photon_genPartIdx[ipho0]] > 20) {
           if (Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 22) {
             if (GenPart_pt[Photon_genPartIdx[ipho1]] > 20) {
               h_WGG_muo_pho0_pt_genmatch->Fill(pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
               h_WGG_muo_pho1_pt_genmatch->Fill(pho1.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
               h_WGG_muo_pho0_pho1_pt_genmatch->Fill((pho0+pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
             }
           }
         }
       }
     }
   }

   if (Z_ele_sel) {
     if (ipho0 != -1) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 22) {
         h_ZG_ele_pho0_pt_genmatch->Fill(pho0.Pt(), weight_Z_ele * weight_pho0);
       }
     }
     if (ipho1 != -1) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 22) {
         if (GenPart_pt[Photon_genPartIdx[ipho0]] > 20) {
           if (Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 22) {
             if (GenPart_pt[Photon_genPartIdx[ipho1]] > 20) {
               h_ZGG_ele_pho0_pt_genmatch->Fill(pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
               h_ZGG_ele_pho1_pt_genmatch->Fill(pho1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
               h_ZGG_ele_pho0_pho1_pt_genmatch->Fill((pho0+pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
             }
           }
         }
       }
     }
   }

   if (Z_muo_sel) {
     if (ipho0 != -1) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 22) {
         h_ZG_muo_pho0_pt_genmatch->Fill(pho0.Pt(), weight_Z_muo * weight_pho0);
       }
     }
     if (ipho1 != -1) {
       if (Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 22) {
         if (GenPart_pt[Photon_genPartIdx[ipho0]] > 20) {
           if (Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart && fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 22) {
             if (GenPart_pt[Photon_genPartIdx[ipho1]] > 20) {
               h_ZGG_muo_pho0_pt_genmatch->Fill(pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
               h_ZGG_muo_pho1_pt_genmatch->Fill(pho1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
               h_ZGG_muo_pho0_pho1_pt_genmatch->Fill((pho0+pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
             }
           }
         }
       }
     }
   }

   if (W_ele_sel) {
     if (ipho0 != -1 && Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart) {
       if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11) {
         h_WG_ele_pho0_pt_genmatch2->Fill(pho0.Pt(), weight_W_ele * weight_pho0);
       }
     }
     if (ipho0 != -1 && Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart) {
       if (ipho1 != -1 && Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart) {
         if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11 || fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 11) {
           h_WGG_ele_pho0_pt_genmatch2->Fill(pho0.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           h_WGG_ele_pho1_pt_genmatch2->Fill(pho1.Pt(), weight_W_ele * weight_pho0 * weight_pho1);
           h_WGG_ele_pho0_pho1_pt_genmatch2->Fill((pho0+pho1).Pt(), weight_W_ele * weight_pho0 * weight_pho1);
         }
       }
     }
   }

   if (W_muo_sel) {
     if (ipho0 != -1 && Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart) {
       if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11) {
         h_WG_muo_pho0_pt_genmatch2->Fill(pho0.Pt(), weight_W_muo * weight_pho0);
       }
     }
     if (ipho0 != -1 && Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart) {
       if (ipho1 != -1 && Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart) {
         if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11 || fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 11) {
           h_WGG_muo_pho0_pt_genmatch2->Fill(pho0.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           h_WGG_muo_pho1_pt_genmatch2->Fill(pho1.Pt(), weight_W_muo * weight_pho0 * weight_pho1);
           h_WGG_muo_pho0_pho1_pt_genmatch2->Fill((pho0+pho1).Pt(), weight_W_muo * weight_pho0 * weight_pho1);
         }
       }
     }
   }

   if (Z_ele_sel) {
     if (ipho0 != -1 && Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart) {
       if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11) {
         h_ZG_ele_pho0_pt_genmatch2->Fill(pho0.Pt(), weight_Z_ele * weight_pho0);
       }
     }
     if (ipho0 != -1 && Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart) {
       if (ipho1 != -1 && Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart) {
         if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11 || fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 11) {
           h_ZGG_ele_pho0_pt_genmatch2->Fill(pho0.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           h_ZGG_ele_pho1_pt_genmatch2->Fill(pho1.Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
           h_ZGG_ele_pho0_pho1_pt_genmatch2->Fill((pho0+pho1).Pt(), weight_Z_ele * weight_pho0 * weight_pho1);
         }
       }
     }
   }

   if (Z_muo_sel) {
     if (ipho0 != -1 && Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart) {
       if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11) {
         h_ZG_muo_pho0_pt_genmatch2->Fill(pho0.Pt(), weight_Z_muo * weight_pho0);
       }
     }
     if (ipho0 != -1 && Photon_genPartIdx[ipho0] >= 0 && (uint)Photon_genPartIdx[ipho0] < *nGenPart) {
       if (ipho1 != -1 && Photon_genPartIdx[ipho1] >= 0 && (uint)Photon_genPartIdx[ipho1] < *nGenPart) {
         if (fabs(GenPart_pdgId[Photon_genPartIdx[ipho0]]) == 11 || fabs(GenPart_pdgId[Photon_genPartIdx[ipho1]]) == 11) {
           h_ZGG_muo_pho0_pt_genmatch2->Fill(pho0.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           h_ZGG_muo_pho1_pt_genmatch2->Fill(pho1.Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
           h_ZGG_muo_pho0_pho1_pt_genmatch2->Fill((pho0+pho1).Pt(), weight_Z_muo * weight_pho0 * weight_pho1);
         }
       }
     }
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
