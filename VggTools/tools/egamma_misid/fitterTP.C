#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "Riostream.h"
#include "TMath.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TLatex.h"
#include "rebin.h"

#include "RooRealVar.h"
#include "RooBinning.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooCBShape.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooFFTConvPdf.h"
#include "RooFitResult.h"
#include "RooAddPdf.h"
#include "RooDoubleCB.h"
#include "RooCMSShape.h"
#include "RooHistPdf.h"
#include "RooChi2Var.h"

#include "histoFromCurve.C"

void fitterTP(int number, int year, bool isQCD, string syst) {

   cout << "Analysing year " << year << endl;

   string sqcd = "";
   if (isQCD) sqcd = "_qcd";

   string h_fake_title = "h_WG_ele_fake_";
   h_fake_title += std::to_string(number);
   h_fake_title = h_fake_title + sqcd;

   string h_peak_title = "h_WG_ele_fake_truthmatch_";
   h_peak_title += std::to_string(number);
   h_peak_title = h_peak_title + sqcd;

   TFile * f1 = 0;
   TFile * f2 = 0;

   if (year == 2016) f1 = new TFile((syst + "/RunIISummer16NanoAODv7_DYToLL_13TeV-amcatnloFXFX-pythia8.root").c_str());
   if (year == 2017) f1 = new TFile((syst + "/RunIIFall17NanoAODv7_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8.root").c_str());
   if (year == 2018) f1 = new TFile((syst + "/RunIIAutumn18NanoAODv7_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8.root").c_str());

   TH1D * h_WG_ele_ele0_pho0_fake_MC_tmp = (TH1D*)f1->Get((h_fake_title).c_str());
   TH1D * h_Z_ele_MC = (TH1D*)f1->Get("h_Z_ele");
   TH1D * h_nevt = (TH1D*)f1->Get("h_nevt");
   TH1D * h_peak_tmp = (TH1D*)f1->Get((h_peak_title).c_str());

   cout << h_peak_title << endl;

   if (year == 2016) f2 = new TFile("reference/Run2016_SingleElectron_02Apr2020.root");
   if (year == 2017) f2 = new TFile("reference/Run2017_SingleElectron_02Apr2020.root");
   if (year == 2018) f2 = new TFile("reference/Run2018_EGamma_02Apr2020.root");

   TH1D * h_WG_ele_ele0_pho0_fake_DT_tmp = (TH1D*)f2->Get((h_fake_title).c_str());
   TH1D * h_Z_ele_DT = (TH1D*)f2->Get("h_Z_ele");

   TH1D * h_WG_ele_ele0_pho0_fake_MC = new TH1D("h_WG_ele_ele0_pho0_fake_MC","h_WG_ele_ele0_pho0_fake_MC",50,40,120);
   TH1D * h_WG_ele_ele0_pho0_fake_DT = new TH1D("h_WG_ele_ele0_pho0_fake_DT","h_WG_ele_ele0_pho0_fake_DT",50,40,120);
   TH1D * h_peak = new TH1D("h_peak","h_peak",50,40,120);

   for (int i = 1; i < h_WG_ele_ele0_pho0_fake_MC->GetNbinsX()+1; i++){
     h_WG_ele_ele0_pho0_fake_MC->SetBinContent(i, h_WG_ele_ele0_pho0_fake_MC_tmp->GetBinContent(i));
     h_WG_ele_ele0_pho0_fake_MC->SetBinError(i, h_WG_ele_ele0_pho0_fake_MC_tmp->GetBinError(i));
     h_WG_ele_ele0_pho0_fake_DT->SetBinContent(i, h_WG_ele_ele0_pho0_fake_DT_tmp->GetBinContent(i));
     h_WG_ele_ele0_pho0_fake_DT->SetBinError(i, h_WG_ele_ele0_pho0_fake_DT_tmp->GetBinError(i));
     h_peak->SetBinContent(i, h_peak_tmp->GetBinContent(i));
     h_peak->SetBinError(i, h_peak_tmp->GetBinError(i));
   }

   h_WG_ele_ele0_pho0_fake_MC = rebin(h_WG_ele_ele0_pho0_fake_MC);
   h_peak = rebin(h_peak);
   h_WG_ele_ele0_pho0_fake_DT = rebin(h_WG_ele_ele0_pho0_fake_DT);

   string txt_param_in_title = "parameters_" + syst + "/param_TP" + sqcd + "_";
   txt_param_in_title += std::to_string(year) + "_" + std::to_string(number) + ".txt";

   double CMSalpha_fake_MC_ave[3];
   double CMSbeta_fake_MC_ave[3];
   double CMSpeak_fake_MC_ave[3];
   double CMSgamma_fake_MC_ave[3];

   double CMSalpha_fake_DT_ave[3];
   double CMSbeta_fake_DT_ave[3];
   double CMSpeak_fake_DT_ave[3];
   double CMSgamma_fake_DT_ave[3];

   ifstream txt_param_in;
   txt_param_in.open((txt_param_in_title).c_str());
   txt_param_in >> CMSalpha_fake_MC_ave[1] >> CMSalpha_fake_MC_ave[0] >> CMSalpha_fake_MC_ave[2];
   txt_param_in >> CMSbeta_fake_MC_ave[1] >> CMSbeta_fake_MC_ave[0] >> CMSbeta_fake_MC_ave[2];
   txt_param_in >> CMSpeak_fake_MC_ave[1] >> CMSpeak_fake_MC_ave[0] >> CMSpeak_fake_MC_ave[2];
   txt_param_in >> CMSgamma_fake_MC_ave[1] >> CMSgamma_fake_MC_ave[0] >> CMSgamma_fake_MC_ave[2];

   txt_param_in >> CMSalpha_fake_DT_ave[1] >> CMSalpha_fake_DT_ave[0] >> CMSalpha_fake_DT_ave[2];
   txt_param_in >> CMSbeta_fake_DT_ave[1] >> CMSbeta_fake_DT_ave[0] >> CMSbeta_fake_DT_ave[2];
   txt_param_in >> CMSpeak_fake_DT_ave[1] >> CMSpeak_fake_DT_ave[0] >> CMSpeak_fake_DT_ave[2];
   txt_param_in >> CMSgamma_fake_DT_ave[1] >> CMSgamma_fake_DT_ave[0] >> CMSgamma_fake_DT_ave[2];
   txt_param_in.close();

   string txt_param_Z_title = "parameters_" + syst + "/param_Z" + sqcd + "_" + std::to_string(year) + ".txt";

   double DCBn1_Z_MC_ave[3];
   double DCBn2_Z_MC_ave[3];
   double DCBalpha1_Z_MC_ave[3];
   double DCBalpha2_Z_MC_ave[3];
   double DCBmean_Z_MC_ave[3];
   double DCBsigma_Z_MC_ave[3];
   double CMSalpha_Z_MC_ave[3];
   double CMSbeta_Z_MC_ave[3];
   double CMSpeak_Z_MC_ave[3];
   double CMSgamma_Z_MC_ave[3];

   double DCBn1_Z_DT_ave[3];
   double DCBn2_Z_DT_ave[3];
   double DCBalpha1_Z_DT_ave[3];
   double DCBalpha2_Z_DT_ave[3];
   double DCBmean_Z_DT_ave[3];
   double DCBsigma_Z_DT_ave[3];
   double CMSalpha_Z_DT_ave[3];
   double CMSbeta_Z_DT_ave[3];
   double CMSpeak_Z_DT_ave[3];
   double CMSgamma_Z_DT_ave[3];

   ifstream txt_param_Z;
   txt_param_Z.open((txt_param_Z_title).c_str());

   txt_param_Z >> DCBn1_Z_MC_ave[1] >> DCBn1_Z_MC_ave[0] >> DCBn1_Z_MC_ave[2];
   txt_param_Z >> DCBn2_Z_MC_ave[1] >> DCBn2_Z_MC_ave[0] >> DCBn2_Z_MC_ave[2];
   txt_param_Z >> DCBalpha1_Z_MC_ave[1] >> DCBalpha1_Z_MC_ave[0] >> DCBalpha1_Z_MC_ave[2];
   txt_param_Z >> DCBalpha2_Z_MC_ave[1] >> DCBalpha2_Z_MC_ave[0] >> DCBalpha2_Z_MC_ave[2];
   txt_param_Z >> DCBmean_Z_MC_ave[1] >> DCBmean_Z_MC_ave[0] >> DCBmean_Z_MC_ave[2];
   txt_param_Z >> DCBsigma_Z_MC_ave[1] >> DCBsigma_Z_MC_ave[0] >> DCBsigma_Z_MC_ave[2];
   txt_param_Z >> CMSalpha_Z_MC_ave[1] >> CMSalpha_Z_MC_ave[0] >> CMSalpha_Z_MC_ave[2];
   txt_param_Z >> CMSbeta_Z_MC_ave[1] >> CMSbeta_Z_MC_ave[0] >> CMSbeta_Z_MC_ave[2];
   txt_param_Z >> CMSpeak_Z_MC_ave[1] >> CMSpeak_Z_MC_ave[0] >> CMSpeak_Z_MC_ave[2];
   txt_param_Z >> CMSgamma_Z_MC_ave[1] >> CMSgamma_Z_MC_ave[0] >> CMSgamma_Z_MC_ave[2];
                                                                                    
   txt_param_Z >> DCBn1_Z_DT_ave[1] >> DCBn1_Z_DT_ave[0] >> DCBn1_Z_DT_ave[2];
   txt_param_Z >> DCBn2_Z_DT_ave[1] >> DCBn2_Z_DT_ave[0] >> DCBn2_Z_DT_ave[2];
   txt_param_Z >> DCBalpha1_Z_DT_ave[1] >> DCBalpha1_Z_DT_ave[0] >> DCBalpha1_Z_DT_ave[2];
   txt_param_Z >> DCBalpha2_Z_DT_ave[1] >> DCBalpha2_Z_DT_ave[0] >> DCBalpha2_Z_DT_ave[2];
   txt_param_Z >> DCBmean_Z_DT_ave[1] >> DCBmean_Z_DT_ave[0] >> DCBmean_Z_DT_ave[2];
   txt_param_Z >> DCBsigma_Z_DT_ave[1] >> DCBsigma_Z_DT_ave[0] >> DCBsigma_Z_DT_ave[2];
   txt_param_Z >> CMSalpha_Z_DT_ave[1] >> CMSalpha_Z_DT_ave[0] >> CMSalpha_Z_DT_ave[2];
   txt_param_Z >> CMSbeta_Z_DT_ave[1] >> CMSbeta_Z_DT_ave[0] >> CMSbeta_Z_DT_ave[2];
   txt_param_Z >> CMSpeak_Z_DT_ave[1] >> CMSpeak_Z_DT_ave[0] >> CMSpeak_Z_DT_ave[2];
   txt_param_Z >> CMSgamma_Z_DT_ave[1] >> CMSgamma_Z_DT_ave[0] >> CMSgamma_Z_DT_ave[2];

   txt_param_Z.close();

   gStyle->SetOptFit(kTRUE);

   RooRealVar m_fake_MC("m_fake_MC", "m(e#gamma)", 40, 200, "GeV");
   RooRealVar m_Z_MC("m_Z_MC", "m(e#gamma)", 51, 131, "GeV");
   RooRealVar m_fake_DT("m_fake_DT", "m(e#gamma)", 40, 200, "GeV");
   RooRealVar m_Z_DT("m_Z_DT", "m(e#gamma)", 51, 131, "GeV");

   RooDataHist data_fake_MC("data_fake_MC", "data_fake_MC", m_fake_MC, h_WG_ele_ele0_pho0_fake_MC);
   RooDataHist data_Z_MC("data_Z_MC", "data_Z_MC", m_Z_MC, h_Z_ele_MC);
   RooDataHist data_fake_DT("data_fake_DT", "data_fake_DT", m_fake_DT, h_WG_ele_ele0_pho0_fake_DT);
   RooDataHist data_Z_DT("data_Z_DT", "data_Z_DT", m_Z_DT, h_Z_ele_DT);

   cout << h_peak << endl;

   // FAKE_MC

   RooDataHist h_TP_fake_MC("h_TP_fake_MC", "h_TP_fake_MC", m_fake_MC, h_peak);
   RooHistPdf TP_fake_MC("TP_fake_MC", "TP_fake_MC", m_fake_MC, h_TP_fake_MC, 0);

   RooRealVar CMSalpha_fake_MC ("CMSalpha_fake_MC", "CMSalpha_fake_MC", CMSalpha_fake_MC_ave[1], CMSalpha_fake_MC_ave[0], CMSalpha_fake_MC_ave[2]);
   RooRealVar CMSbeta_fake_MC ("CMSbeta_fake_MC", "CMSbeta_fake_MC", CMSbeta_fake_MC_ave[1], CMSbeta_fake_MC_ave[0], CMSbeta_fake_MC_ave[2]);
   RooRealVar CMSpeak_fake_MC ("CMSpeak_fake_MC", "CMSpeak_fake_MC", CMSpeak_fake_MC_ave[1], CMSpeak_fake_MC_ave[0], CMSpeak_fake_MC_ave[2]);
   RooRealVar CMSgamma_fake_MC ("CMSgamma_fake_MC", "CMSgamma_fake_MC", CMSgamma_fake_MC_ave[1], CMSgamma_fake_MC_ave[0], CMSgamma_fake_MC_ave[2]);
   RooCMSShape CMS_fake_MC("CMS_fake_MC","CMS_fake_MC", m_fake_MC, CMSalpha_fake_MC, CMSbeta_fake_MC, CMSgamma_fake_MC, CMSpeak_fake_MC);

   RooRealVar bkgfrac_fake_MC("bkgfrac_fake_MC","bkgfrac_fake_MC", 0.3, 0., 1.) ;
   RooAddPdf  model_fake_MC("model_fake_MC","model_fake_MC",RooArgList(CMS_fake_MC,TP_fake_MC),bkgfrac_fake_MC) ;

   bool nullchi = false;
   for (int i = 1; i < h_WG_ele_ele0_pho0_fake_MC->GetNbinsX() + 1; i++) {
     if (h_WG_ele_ele0_pho0_fake_MC->GetBinError(i) == 0) nullchi = true;
   }
   RooFitResult* fit_fake_MC;
   if (nullchi) {
     fit_fake_MC = model_fake_MC.fitTo(data_fake_MC, RooFit::SumW2Error(kFALSE), RooFit::Range(40., 120.), RooFit::Save(kTRUE));
   } else {
     fit_fake_MC = model_fake_MC.chi2FitTo(data_fake_MC, RooFit::SumW2Error(kFALSE), RooFit::Range(40., 120.), RooFit::Save(kTRUE));
   }
   fit_fake_MC->SetName("fit_fake_MC");

   // Z MC

   RooRealVar DCBn1_Z_MC("DCBn1_Z_MC","DCBn1_Z_MC", DCBn1_Z_MC_ave[1], DCBn1_Z_MC_ave[0], DCBn1_Z_MC_ave[2]);
   RooRealVar DCBn2_Z_MC("DCBn2_Z_MC","DCBn2_Z_MC", DCBn2_Z_MC_ave[1], DCBn2_Z_MC_ave[0], DCBn2_Z_MC_ave[2]);
   RooRealVar DCBalpha1_Z_MC("DCBalpha1_Z_MC","DCBalpha1_Z_MC", DCBalpha1_Z_MC_ave[1], DCBalpha1_Z_MC_ave[0], DCBalpha1_Z_MC_ave[2]);
   RooRealVar DCBalpha2_Z_MC("DCBalpha2_Z_MC","DCBalpha2_Z_MC", DCBalpha2_Z_MC_ave[1], DCBalpha2_Z_MC_ave[0], DCBalpha2_Z_MC_ave[2]);
   RooRealVar DCBmean_Z_MC ("DCBmean_Z_MC", "DCBmean_Z_MC", DCBmean_Z_MC_ave[1], DCBmean_Z_MC_ave[0], DCBmean_Z_MC_ave[2]);
   RooRealVar DCBsigma_Z_MC("DCBsigma_Z_MC","DCBsigma_Z_MC", DCBsigma_Z_MC_ave[1], DCBsigma_Z_MC_ave[0], DCBsigma_Z_MC_ave[2]);
   RooDoubleCB DCB_Z_MC("DCB_Z_MC","DCB_Z_MC", m_Z_MC, DCBmean_Z_MC, DCBsigma_Z_MC, DCBalpha1_Z_MC, DCBn1_Z_MC, DCBalpha2_Z_MC, DCBn2_Z_MC);

   RooRealVar CMSalpha_Z_MC ("CMSalpha_Z_MC", "CMSalpha_Z_MC", CMSalpha_Z_MC_ave[1], CMSalpha_Z_MC_ave[0], CMSalpha_Z_MC_ave[2]);
   RooRealVar CMSbeta_Z_MC ("CMSbeta_Z_MC", "CMSbeta_Z_MC", CMSbeta_Z_MC_ave[1], CMSbeta_Z_MC_ave[0], CMSbeta_Z_MC_ave[2]);
   RooRealVar CMSpeak_Z_MC ("CMSpeak_Z_MC", "CMSpeak_Z_MC", CMSpeak_Z_MC_ave[1], CMSpeak_Z_MC_ave[0], CMSpeak_Z_MC_ave[2]);
   RooRealVar CMSgamma_Z_MC ("CMSgamma_Z_MC", "CMSgamma_Z_MC", CMSgamma_Z_MC_ave[1], CMSgamma_Z_MC_ave[0], CMSgamma_Z_MC_ave[2]);
   RooCMSShape CMS_Z_MC("CMS_Z_MC","CMS_Z_MC", m_Z_MC, CMSalpha_Z_MC, CMSbeta_Z_MC, CMSgamma_Z_MC, CMSpeak_Z_MC);

   RooRealVar bkgfrac_Z_MC("bkgfrac_Z_MC","bkgfrac_Z_MC", 0.1, 0., 1.) ;
   RooAddPdf  model_Z_MC("model_Z_MC","model_Z_MC",RooArgList(CMS_Z_MC,DCB_Z_MC),bkgfrac_Z_MC) ;

   RooFitResult* fit_Z_MC = model_Z_MC.chi2FitTo(data_Z_MC, RooFit::SumW2Error(kFALSE), RooFit::Range(51., 131.), RooFit::Save(kTRUE));
   fit_Z_MC->SetName("fit_Z_MC");

   //FAKE DT
   RooDataHist h_TP_fake_DT("h_TP_fake_DT", "h_TP_fake_DT", m_fake_DT, h_peak);
   RooHistPdf TP_fake_DT("TP_fake_DT", "TP_fake_DT", m_fake_DT, h_TP_fake_DT, 0);

   RooRealVar CMSalpha_fake_DT ("CMSalpha_fake_DT", "CMSalpha_fake_DT", CMSalpha_fake_DT_ave[1], CMSalpha_fake_DT_ave[0], CMSalpha_fake_DT_ave[2]);
   RooRealVar CMSbeta_fake_DT ("CMSbeta_fake_DT", "CMSbeta_fake_DT", CMSbeta_fake_DT_ave[1], CMSbeta_fake_DT_ave[0], CMSbeta_fake_DT_ave[2]);
   RooRealVar CMSpeak_fake_DT ("CMSpeak_fake_DT", "CMSpeak_fake_DT", CMSpeak_fake_DT_ave[1], CMSpeak_fake_DT_ave[0], CMSpeak_fake_DT_ave[2]);
   RooRealVar CMSgamma_fake_DT ("CMSgamma_fake_DT", "CMSgamma_fake_DT", CMSgamma_fake_DT_ave[1], CMSgamma_fake_DT_ave[0], CMSgamma_fake_DT_ave[2]);
   RooCMSShape CMS_fake_DT("CMS_fake_DT","CMS_fake_DT", m_fake_DT, CMSalpha_fake_DT, CMSbeta_fake_DT, CMSgamma_fake_DT, CMSpeak_fake_DT);

   RooRealVar bkgfrac_fake_DT("bkgfrac_fake_DT","bkgfrac_fake_DT",0.9, 0., 1.) ;
   RooAddPdf  model_fake_DT("model_fake_DT","model_fake_DT",RooArgList(CMS_fake_DT,TP_fake_DT),bkgfrac_fake_DT) ;

   bool nullchiDT = false;
   for (int i = 1; i < h_WG_ele_ele0_pho0_fake_DT->GetNbinsX() + 1; i++) {
     if (h_WG_ele_ele0_pho0_fake_DT->GetBinError(i) == 0) nullchiDT = true;
   }
   RooFitResult* fit_fake_DT;
   if (nullchiDT) {
     fit_fake_DT = model_fake_DT.fitTo(data_fake_DT, RooFit::SumW2Error(kFALSE), RooFit::Range(40., 120.), RooFit::Save(kTRUE));
   } else {
     fit_fake_DT = model_fake_DT.chi2FitTo(data_fake_DT, RooFit::SumW2Error(kFALSE), RooFit::Range(40., 120.), RooFit::Save(kTRUE));
   }
   fit_fake_DT->SetName("fit_fake_DT");

   // Z DT

   RooRealVar DCBn1_Z_DT("DCBn1_Z_DT","DCBn1_Z_DT", DCBn1_Z_DT_ave[1], DCBn1_Z_DT_ave[0], DCBn1_Z_DT_ave[2]);
   RooRealVar DCBn2_Z_DT("DCBn2_Z_DT","DCBn2_Z_DT", DCBn2_Z_DT_ave[1], DCBn2_Z_DT_ave[0], DCBn2_Z_DT_ave[2]);
   RooRealVar DCBalpha1_Z_DT("DCBalpha1_Z_DT","DCBalpha1_Z_DT", DCBalpha1_Z_DT_ave[1], DCBalpha1_Z_DT_ave[0], DCBalpha1_Z_DT_ave[2]);
   RooRealVar DCBalpha2_Z_DT("DCBalpha2_Z_DT","DCBalpha2_Z_DT", DCBalpha2_Z_DT_ave[1], DCBalpha2_Z_DT_ave[0], DCBalpha2_Z_DT_ave[2]);
   RooRealVar DCBmean_Z_DT ("DCBmean_Z_DT", "DCBmean_Z_DT", DCBmean_Z_DT_ave[1], DCBmean_Z_DT_ave[0], DCBmean_Z_DT_ave[2]);
   RooRealVar DCBsigma_Z_DT("DCBsigma_Z_DT","DCBsigma_Z_DT", DCBsigma_Z_DT_ave[1], DCBsigma_Z_DT_ave[0], DCBsigma_Z_DT_ave[2]);
   RooDoubleCB DCB_Z_DT("DCB_Z_DT","DCB_Z_DT", m_Z_DT, DCBmean_Z_DT, DCBsigma_Z_DT, DCBalpha1_Z_DT, DCBn1_Z_DT, DCBalpha2_Z_DT, DCBn2_Z_DT);

   RooRealVar CMSalpha_Z_DT ("CMSalpha_Z_DT", "CMSalpha_Z_DT", CMSalpha_Z_DT_ave[1], CMSalpha_Z_DT_ave[0], CMSalpha_Z_DT_ave[2]);
   RooRealVar CMSbeta_Z_DT ("CMSbeta_Z_DT", "CMSbeta_Z_DT", CMSbeta_Z_DT_ave[1], CMSbeta_Z_DT_ave[0], CMSbeta_Z_DT_ave[2]);
   RooRealVar CMSpeak_Z_DT ("CMSpeak_Z_DT", "CMSpeak_Z_DT", CMSpeak_Z_DT_ave[1], CMSpeak_Z_DT_ave[0], CMSpeak_Z_DT_ave[2]);
   RooRealVar CMSgamma_Z_DT ("CMSgamma_Z_DT", "CMSgamma_Z_DT", CMSgamma_Z_DT_ave[1], CMSgamma_Z_DT_ave[0], CMSgamma_Z_DT_ave[2]);
   RooCMSShape CMS_Z_DT("CMS_Z_DT","CMS_Z_DT", m_Z_DT, CMSalpha_Z_DT, CMSbeta_Z_DT, CMSgamma_Z_DT, CMSpeak_Z_DT);

   RooRealVar bkgfrac_Z_DT("bkgfrac_Z_DT","bkgfrac_Z_DT",0.1, 0., 0.2) ;
   RooAddPdf  model_Z_DT("model_Z_DT","model_Z_DT",RooArgList(CMS_Z_DT,DCB_Z_DT),bkgfrac_Z_DT) ;

   RooFitResult* fit_Z_DT = model_Z_DT.chi2FitTo(data_Z_DT, RooFit::SumW2Error(kFALSE), RooFit::Range(51., 131.), RooFit::Save(kTRUE));
   fit_Z_DT->SetName("fit_Z_DT");

   string pt_range = "";
   string eta_range = "";

   if (number >= 1 && number <= 5) {
     pt_range = "20 < p_{T} < 30";
   }
   if (number >= 6 && number <= 10) {
     pt_range = "30 < p_{T} < 40";
   }
   if (number >= 11 && number <= 15) {
     pt_range = "40 < p_{T} < 50";
   }
   if (number >= 16 && number <= 20) {
     pt_range = "50 < p_{T} < 200";
   }

   if (number == 1 || number == 6 || number == 11 || number == 16) {
     eta_range = "0 < |eta| < 0.5";
   }
   if (number == 2 || number == 7 || number == 12 || number == 17) {
     eta_range = "0.5 < |eta| < 1";
   }
   if (number == 3 || number == 8 || number == 13 || number == 18) {
     eta_range = "1 < |eta| < 1.442";
   }
   if (number == 4 || number == 9 || number == 14 || number == 19) {
     eta_range = "1.566 < |eta| < 2";
   }
   if (number == 5 || number == 10 || number == 15 || number == 20) {
     eta_range = "2 < |eta| < 2.4";
   }

   TCanvas * c = new TCanvas("c","c",0,0,1000,500);
   c->Divide(2,1);

   c->cd(1);
   RooPlot* plot_fake_MC = m_fake_MC.frame();
   data_fake_MC.plotOn(plot_fake_MC);
   model_fake_MC.plotOn(plot_fake_MC, RooFit::LineColor(kRed), RooFit::LineStyle(7));
   model_fake_MC.plotOn(plot_fake_MC, RooFit::Components(CMS_fake_MC), RooFit::LineColor(kBlue), RooFit::LineStyle(7), RooFit::Name("bkg_fake_MC")) ;
   model_fake_MC.plotOn(plot_fake_MC, RooFit::Components(TP_fake_MC), RooFit::LineColor(kGreen), RooFit::LineStyle(7), RooFit::Name("sgn_fake_MC")) ;
   plot_fake_MC->GetYaxis()->SetTitle("");
   string draw_title_MC = "Monte Carlo ";
   draw_title_MC += std::to_string(year);
   plot_fake_MC->SetTitle((draw_title_MC).c_str());
   plot_fake_MC->Draw();

   string chi_fake_MC = "#Chi^{2}/ndf = ";
   if (nullchi) {
     chi_fake_MC = chi_fake_MC + "NULL";
   } else {
     RooChi2Var chi2_MC_fake("chi2_MC_fake","chi2_MC_fake",model_fake_MC,data_fake_MC) ;
     double chival_MC_fake = chi2_MC_fake.getVal();
     chival_MC_fake = chival_MC_fake/(h_WG_ele_ele0_pho0_fake_MC->GetNbinsX() - 5.);
     chi_fake_MC += std::to_string(chival_MC_fake);
   }

   string status_fake_MC = "Fit status = ";
   status_fake_MC += std::to_string(fit_fake_MC->status());

   TLatex* label = new TLatex();
   label->SetTextFont(43);
   label->SetTextSize(16);
   label->SetLineWidth(2);
   label->SetNDC();
   label->DrawLatex(0.15, 0.85, "Template + CMS shape");
   label->DrawLatex(0.15, 0.80, (pt_range).c_str());
   label->DrawLatex(0.15, 0.75, (eta_range).c_str());
   label->DrawLatex(0.15, 0.70, (chi_fake_MC).c_str());
   label->DrawLatex(0.15, 0.65, (status_fake_MC).c_str());
   label->Draw("same");

   c->cd(2);
   RooPlot* plot_fake_DT = m_fake_DT.frame();
   data_fake_DT.plotOn(plot_fake_DT);
   model_fake_DT.plotOn(plot_fake_DT, RooFit::LineColor(kRed), RooFit::LineStyle(7));
   model_fake_DT.plotOn(plot_fake_DT, RooFit::Components(CMS_fake_DT), RooFit::LineColor(kBlue), RooFit::LineStyle(7), RooFit::Name("bkg_fake_DT")) ;
   model_fake_DT.plotOn(plot_fake_DT, RooFit::Components(TP_fake_DT), RooFit::LineColor(kGreen), RooFit::LineStyle(7), RooFit::Name("sgn_fake_DT"));
   plot_fake_DT->GetYaxis()->SetTitle("");
   string draw_title_DT = "Data ";
   draw_title_DT += std::to_string(year);
   plot_fake_DT->SetTitle((draw_title_DT).c_str());
   plot_fake_DT->Draw();

   string chi_fake_DT = "#Chi^{2}/ndf = ";
   if (nullchiDT) {
     chi_fake_DT = chi_fake_DT + "NULL";
   } else {
     RooChi2Var chi2_DT_fake("chi2_DT_fake","chi2_DT_fake",model_fake_DT,data_fake_DT) ;
     double chival_DT_fake = chi2_DT_fake.getVal();
     chival_DT_fake = chival_DT_fake/(h_WG_ele_ele0_pho0_fake_DT->GetNbinsX() - 5.);
     chi_fake_DT += std::to_string(chival_DT_fake);
   }

   string status_fake_DT = "Fit status = ";
   status_fake_DT += std::to_string(fit_fake_DT->status());

   label->DrawLatex(0.15, 0.85, "Template + CMS shape");
   label->DrawLatex(0.15, 0.80, (pt_range).c_str());
   label->DrawLatex(0.15, 0.75, (eta_range).c_str());
   label->DrawLatex(0.15, 0.70, (chi_fake_DT).c_str());
   label->DrawLatex(0.15, 0.65, (status_fake_DT).c_str());
   label->Draw("same");

   string plot_title = "../../macros/html/egamma_v7/" + syst + "/plot/TP_bin_";
   plot_title += std::to_string(year);
   plot_title = plot_title + sqcd + "_";
   plot_title += std::to_string(number);
   plot_title = plot_title + ".pdf";
   c->SaveAs((plot_title).c_str());

   if (number == 1) {

     TCanvas * cZ = new TCanvas("cZ","cZ",0,0,1000,500);
     cZ->Divide(2,1);
     cZ->cd(1);
     RooPlot* plot_Z_MC = m_Z_MC.frame();
     data_Z_MC.plotOn(plot_Z_MC);
     model_Z_MC.plotOn(plot_Z_MC, RooFit::LineColor(kRed), RooFit::LineStyle(7));
     model_Z_MC.plotOn(plot_Z_MC, RooFit::Components(CMS_Z_MC), RooFit::LineColor(kBlue), RooFit::LineStyle(7)) ;
     model_Z_MC.plotOn(plot_Z_MC, RooFit::Components(DCB_Z_MC), RooFit::LineColor(kGreen), RooFit::LineStyle(7)) ;
     plot_Z_MC->GetYaxis()->SetTitle("");
     string draw_title_MC = "Monte Carlo ";
     draw_title_MC += std::to_string(year);
     plot_Z_MC->SetTitle((draw_title_MC).c_str());
     plot_Z_MC->Draw();

     string chi_Z_MC = "#Chi^{2}/ndf = ";
     RooChi2Var chi2_Z_MC("chi2_Z_MC","chi2_Z_MC",model_Z_MC,data_Z_MC) ;
     double chival_Z_MC = chi2_Z_MC.getVal();
     chival_Z_MC = chival_Z_MC/149.;
     chi_Z_MC += std::to_string(chival_Z_MC);

     string status_Z_MC = "Fit status = ";
     status_Z_MC += std::to_string(fit_Z_MC->status());

     TLatex* label = new TLatex();
     label->SetTextFont(43);
     label->SetTextSize(16);
     label->SetLineWidth(2);
     label->SetNDC();
     label->DrawLatex(0.15, 0.85, "Double CB + CMS shape");
     label->DrawLatex(0.15, 0.80, (chi_Z_MC).c_str());
     label->DrawLatex(0.15, 0.75, (status_Z_MC).c_str());
     label->Draw("same");

     cZ->cd(2);
     RooPlot* plot_Z_DT = m_Z_DT.frame();
     data_Z_DT.plotOn(plot_Z_DT);
     model_Z_DT.plotOn(plot_Z_DT, RooFit::LineColor(kRed), RooFit::LineStyle(7));
     model_Z_DT.plotOn(plot_Z_DT, RooFit::Components(CMS_Z_DT), RooFit::LineColor(kBlue), RooFit::LineStyle(7)) ;
     model_Z_DT.plotOn(plot_Z_DT, RooFit::Components(DCB_Z_DT), RooFit::LineColor(kGreen), RooFit::LineStyle(7)) ;
     plot_Z_DT->GetYaxis()->SetTitle("");
     string draw_title_DT = "Data ";
     draw_title_DT += std::to_string(year);
     plot_Z_DT->SetTitle((draw_title_DT).c_str());
     plot_Z_DT->Draw();

     RooChi2Var chi2_Z_DT("chi2_Z_DT","chi2_Z_DT",model_Z_DT,data_Z_DT) ;
     double chival_Z_DT = chi2_Z_DT.getVal();
     chival_Z_DT = chival_Z_DT/149.;
     string chi_Z_DT = "#Chi^{2}/ndf = ";
     chi_Z_DT += std::to_string(chival_Z_DT);

     string status_Z_DT = "Fit status = ";
     status_Z_DT += std::to_string(fit_Z_DT->status());

     label->DrawLatex(0.15, 0.85, "Double CB + CMS shape");
     label->DrawLatex(0.15, 0.80, (chi_Z_DT).c_str());
     label->DrawLatex(0.15, 0.75, (status_Z_DT).c_str());
     label->Draw("same");

     string Zplot_title = "../../macros/html/egamma_v7/" + syst + "/plot/TP_Z_";
     Zplot_title += std::to_string(year);
     Zplot_title = Zplot_title + sqcd;
     Zplot_title = Zplot_title + ".pdf";
     cZ->SaveAs((Zplot_title).c_str());

   }

   TGraph * gr_sgn_MC = (TGraph*)plot_fake_MC->findObject("sgn_fake_MC");
   TGraph * gr_sgn_DT = (TGraph*)plot_fake_DT->findObject("sgn_fake_DT");

   float n_fake_MC = gr_sgn_MC->Integral();
   float n_Z_MC = h_Z_ele_MC->Integral(1, h_Z_ele_MC->GetNbinsX())*(1.-bkgfrac_Z_MC.getVal());
   float n_fake_DT = gr_sgn_DT->Integral();
   float n_Z_DT = h_Z_ele_DT->Integral(1, h_Z_ele_DT->GetNbinsX())*(1.-bkgfrac_Z_DT.getVal());

   float sf_error = (n_fake_DT/n_Z_DT) * (n_Z_MC/n_fake_MC) * TMath::Sqrt( 1./n_fake_DT + 1./n_fake_MC + 1./n_Z_DT + 1./n_Z_MC);

   cout << "Scale factor for bin number " << number << " = " << (n_fake_DT/n_Z_DT)/(n_fake_MC/n_Z_MC) << " +- " << sf_error<< endl;

   string txt_title = syst + "/sf_data_TP" + sqcd + "_";
   txt_title += std::to_string(year);
   txt_title = txt_title + ".txt";

   ofstream sf_data;
   sf_data.open((txt_title).c_str(), std::ios_base::app);
   sf_data << number << "\t" << (n_fake_DT/n_Z_DT)/(n_fake_MC/n_Z_MC) << "\t" << sf_error << endl;
   sf_data.close();

   ofstream txt_param;
   string txt_param_title ="parameters_" + syst + "/param_TP_out" + sqcd + "_";
   txt_param_title += std::to_string(year) + "_" + std::to_string(number) + ".txt";
   txt_param.open((txt_param_title).c_str());
   txt_param << CMSalpha_fake_MC.getVal() << endl;
   txt_param << CMSbeta_fake_MC.getVal() << endl;
   txt_param << CMSpeak_fake_MC.getVal() << endl;
   txt_param << CMSgamma_fake_MC.getVal() << endl;
   txt_param << CMSalpha_fake_DT.getVal() << endl;
   txt_param << CMSbeta_fake_DT.getVal() << endl;
   txt_param << CMSpeak_fake_DT.getVal() << endl;
   txt_param << CMSgamma_fake_DT.getVal() << endl;
   txt_param.close();

   TGraph * gr_bkg_MC = (TGraph*)plot_fake_MC->findObject("bkg_fake_MC");
   TGraph * gr_bkg_DT = (TGraph*)plot_fake_DT->findObject("bkg_fake_DT");

   TH1D* h_MC = histoFromCurve(h_WG_ele_ele0_pho0_fake_MC, gr_bkg_MC, CMSalpha_fake_MC.getVal(), CMSbeta_fake_MC.getVal(), CMSpeak_fake_MC.getVal(), CMSgamma_fake_MC.getVal());
   TH1D* h_DT = histoFromCurve(h_WG_ele_ele0_pho0_fake_DT, gr_bkg_DT, CMSalpha_fake_DT.getVal(), CMSbeta_fake_DT.getVal(), CMSpeak_fake_DT.getVal(), CMSgamma_fake_DT.getVal());

   string file_root_name = "parameters_" + syst + "/CMSshape" + sqcd + "_" + std::to_string(year) + "_" + std::to_string(number) + ".root";

   TFile * file_root = new TFile((file_root_name).c_str(), "RECREATE");
   h_MC->Write("h_MC");
   h_DT->Write("h_DT");
   file_root->Close();
}
