#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "Riostream.h"
#include "TMath.h"
#include "TStyle.h"
#include "TROOT.h"

#include "RooRealVar.h"
#include "RooBinning.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooCBShape.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooBreitWigner.h"
#include "RooFFTConvPdf.h"
#include "RooFitResult.h"
#include "RooAddPdf.h"
#include "RooDoubleCB.h"
#include "RooCMSShape.h"
#include "RooCBShape.h"
#include "RooHistPdf.h"

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

   if (year == 2016) f1 = new TFile((syst + "/RunIISummer16NanoAODv5_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root").c_str());
   if (year == 2017) f1 = new TFile((syst + "/RunIIFall17NanoAODv5_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root").c_str());
   if (year == 2018) f1 = new TFile((syst + "/RunIIAutumn18NanoAODv5_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root").c_str());

   TH1D * h_WG_ele_ele0_pho0_fake_MC = (TH1D*)f1->Get((h_fake_title).c_str());
   TH1D * h_Z_ele_MC = (TH1D*)f1->Get("h_Z_ele");
   TH1D * h_nevt = (TH1D*)f1->Get("h_nevt");
   TH1D * h_peak = (TH1D*)f1->Get((h_peak_title).c_str());

   cout << h_peak_title << endl;

   if (year == 2016) f2 = new TFile("reference/Run2016_SingleElectron_1June2019.root");
   if (year == 2017) f2 = new TFile("reference/Run2017_SingleElectron_1June2019.root");
   if (year == 2018) f2 = new TFile("reference/Run2018_EGamma_1June2019.root");

   TH1D * h_WG_ele_ele0_pho0_fake_DT = (TH1D*)f2->Get((h_fake_title).c_str());
   TH1D * h_Z_ele_DT = (TH1D*)f2->Get("h_Z_ele");

   for (int i = 0; i < h_WG_ele_ele0_pho0_fake_MC->GetNbinsX(); i++) {
     if (h_WG_ele_ele0_pho0_fake_MC->GetBinContent(i) < 0) {
        h_WG_ele_ele0_pho0_fake_MC->SetBinContent(i, 0.);
        h_WG_ele_ele0_pho0_fake_MC->SetBinError(i, 0.);
     }
   }
   for (int i = 0; i < h_Z_ele_MC->GetNbinsX(); i++) {
     if (h_Z_ele_MC->GetBinContent(i) < 0) {
       h_Z_ele_MC->SetBinContent(i, 0.);
       h_Z_ele_MC->SetBinError(i, 0.);
     }
   }
   for (int i = 0; i < h_peak->GetNbinsX(); i++) {
     if (h_peak->GetBinContent(i) < 0) {
       h_peak->SetBinContent(i, 0.);
       h_peak->SetBinError(i, 0.);
     }
   }

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

   RooRealVar CMSalpha_fake_MC ("CMSalpha_fake_MC", "CMSalpha_fake_MC", 60.,50.,80.);
   RooRealVar CMSbeta_fake_MC ("CMSbeta_fake_MC", "CMSbeta_fake_MC", 0.4,0.,5.);
   RooRealVar CMSpeak_fake_MC ("CMSpeak_fake_MC", "CMSpeak_fake_MC", 70.,50.,90.);
   RooRealVar CMSgamma_fake_MC ("CMSgamma_fake_MC", "CMSgamma_fake_MC", 0.2,0.,1.);
   RooCMSShape CMS_fake_MC("CMS_fake_MC","CMS_fake_MC", m_fake_MC, CMSalpha_fake_MC, CMSbeta_fake_MC, CMSgamma_fake_MC, CMSpeak_fake_MC);

   RooRealVar bkgfrac_fake_MC("bkgfrac_fake_MC","bkgfrac_fake_MC", 0.3, 0., 1.) ;
   RooAddPdf  model_fake_MC("model_fake_MC","model_fake_MC",RooArgList(CMS_fake_MC,TP_fake_MC),bkgfrac_fake_MC) ;

   RooFitResult* fit_fake_MC = model_fake_MC.fitTo(data_fake_MC, RooFit::SumW2Error(kFALSE), RooFit::Range(40., 200.), RooFit::Save(kTRUE));
   fit_fake_MC->SetName("fit_fake_MC");


   // Z MC

   RooRealVar CBn1_Z_MC("CBn1_Z_MC","CBn1_Z_MC",1.5,0.,3.);
   RooRealVar CBn2_Z_MC("CBn2_Z_MC","CBn2_Z_MC",7.,0.,10.);
   RooRealVar CBalpha1_Z_MC("CBalpha1_Z_MC","CBalpha1_Z_MC",1.3,0.,3.);
   RooRealVar CBalpha2_Z_MC("CBalpha2_Z_MC","CBalpha2_Z_MC",3.,0.,5.);
   RooRealVar CBmean_Z_MC ("CBmean_Z_MC", "CBmean_Z_MC", 88.,80., 100.);
   RooRealVar CBsigma_Z_MC("CBsigma_Z_MC","CBsigma_Z_MC", 4., 0., 7.);
   RooDoubleCB CB_Z_MC("CB_Z_MC","CB_Z_MC", m_Z_MC, CBmean_Z_MC, CBsigma_Z_MC, CBalpha1_Z_MC, CBn1_Z_MC, CBalpha2_Z_MC, CBn2_Z_MC);

   RooRealVar CMSalpha_Z_MC ("CMSalpha_Z_MC", "CMSalpha_Z_MC", 60.,50.,80.);
   RooRealVar CMSbeta_Z_MC ("CMSbeta_Z_MC", "CMSbeta_Z_MC", 0.4,0.,5.);
   RooRealVar CMSpeak_Z_MC ("CMSpeak_Z_MC", "CMSpeak_Z_MC", 70.,50.,90.);
   RooRealVar CMSgamma_Z_MC ("CMSgamma_Z_MC", "CMSgamma_Z_MC", 0.2,0.,1.);
   RooCMSShape CMS_Z_MC("CMS_Z_MC","CMS_Z_MC", m_Z_MC, CMSalpha_Z_MC, CMSbeta_Z_MC, CMSgamma_Z_MC, CMSpeak_Z_MC);

   RooRealVar bkgfrac_Z_MC("bkgfrac_Z_MC","bkgfrac_Z_MC", 0.1, 0., 1.) ;
   RooAddPdf  model_Z_MC("model_Z_MC","model_Z_MC",RooArgList(CMS_Z_MC,CB_Z_MC),bkgfrac_Z_MC) ;

   RooFitResult* fit_Z_MC = model_Z_MC.fitTo(data_Z_MC, RooFit::SumW2Error(kFALSE), RooFit::Range(40., 200.), RooFit::Save(kTRUE));
   fit_Z_MC->SetName("fit_Z_MC");

   //FAKE DT
   RooDataHist h_TP_fake_DT("h_TP_fake_DT", "h_TP_fake_DT", m_fake_DT, h_peak);
   RooHistPdf TP_fake_DT("TP_fake_DT", "TP_fake_DT", m_fake_DT, h_TP_fake_DT, 0); 

   RooRealVar CMSalpha_fake_DT ("CMSalpha_fake_DT", "CMSalpha_fake_DT", 75.,65.,85.);
   RooRealVar CMSbeta_fake_DT ("CMSbeta_fake_DT", "CMSbeta_fake_DT", 0.07,0.,1.);
   RooRealVar CMSpeak_fake_DT ("CMSpeak_fake_DT", "CMSpeak_fake_DT", 50.,40.,60.);
   RooRealVar CMSgamma_fake_DT ("CMSgamma_fake_DT", "CMSgamma_fake_DT",0.08 ,0.,0.1);
   RooCMSShape CMS_fake_DT("CMS_fake_DT","CMS_fake_DT", m_fake_DT, CMSalpha_fake_DT, CMSbeta_fake_DT, CMSgamma_fake_DT, CMSpeak_fake_DT);

   RooRealVar bkgfrac_fake_DT("bkgfrac_fake_DT","bkgfrac_fake_DT",0.9, 0., 1.) ;
   RooAddPdf  model_fake_DT("model_fake_DT","model_fake_DT",RooArgList(CMS_fake_DT,TP_fake_DT),bkgfrac_fake_DT) ;

   RooFitResult* fit_fake_DT = model_fake_DT.fitTo(data_fake_DT, RooFit::SumW2Error(kFALSE), RooFit::Range(40., 200.), RooFit::Save(kTRUE));
   fit_fake_DT->SetName("fit_fake_DT");

   // Z DT

   RooRealVar CBn1_Z_DT("CBn1_Z_DT","CBn1_Z_DT",1.5,0.,3.);
   RooRealVar CBn2_Z_DT("CBn2_Z_DT","CBn2_Z_DT",7.,0.,10.);
   RooRealVar CBalpha1_Z_DT("CBalpha1_Z_DT","CBalpha1_Z_DT",1.3,0.,3.);
   RooRealVar CBalpha2_Z_DT("CBalpha2_Z_DT","CBalpha2_Z_DT",3.,0.,5.);
   RooRealVar CBmean_Z_DT ("CBmean_Z_DT", "CBmean_Z_DT", 88.,80., 100.);
   RooRealVar CBsigma_Z_DT("CBsigma_Z_DT","CBsigma_Z_DT", 4., 0., 7.);
   RooDoubleCB CB_Z_DT("CB_Z_DT","CB_Z_DT", m_Z_DT, CBmean_Z_DT, CBsigma_Z_DT, CBalpha1_Z_DT, CBn1_Z_DT, CBalpha2_Z_DT, CBn2_Z_DT);

   RooRealVar CMSalpha_Z_DT ("CMSalpha_Z_DT", "CMSalpha_Z_DT", 60.,50.,80.);
   RooRealVar CMSbeta_Z_DT ("CMSbeta_Z_DT", "CMSbeta_Z_DT", 0.4,0.,1.);
   RooRealVar CMSpeak_Z_DT ("CMSpeak_Z_DT", "CMSpeak_Z_DT", 70.,50.,90.);
   RooRealVar CMSgamma_Z_DT ("CMSgamma_Z_DT", "CMSgamma_Z_DT",0.2 ,0.,1.);
   RooCMSShape CMS_Z_DT("CMS_Z_DT","CMS_Z_DT", m_Z_DT, CMSalpha_Z_DT, CMSbeta_Z_DT, CMSgamma_Z_DT, CMSpeak_Z_DT);

   RooRealVar bkgfrac_Z_DT("bkgfrac_Z_DT","bkgfrac_Z_DT",0.01, 0., 1.) ;
   RooAddPdf  model_Z_DT("model_Z_DT","model_Z_DT",RooArgList(CMS_Z_DT,CB_Z_DT),bkgfrac_Z_DT) ;

   RooFitResult* fit_Z_DT = model_Z_DT.fitTo(data_Z_DT, RooFit::SumW2Error(kFALSE), RooFit::Range(40., 200.), RooFit::Save(kTRUE));
   fit_Z_DT->SetName("fit_Z_DT");

   TCanvas * c = new TCanvas("c","c",0,0,1000,1000);
   c->Divide(2,2);
   c->cd(1);
   RooPlot* plot_fake_MC = m_fake_MC.frame();
   data_fake_MC.plotOn(plot_fake_MC);
   model_fake_MC.plotOn(plot_fake_MC, RooFit::LineColor(kRed));
   model_fake_MC.plotOn(plot_fake_MC, RooFit::Components(CMS_fake_MC), RooFit::LineColor(kBlue)) ;
   model_fake_MC.plotOn(plot_fake_MC, RooFit::Components(TP_fake_MC), RooFit::LineColor(kGreen)) ;
   plot_fake_MC->Draw();

   c->cd(2);
   RooPlot* plot_Z_MC = m_Z_MC.frame();
   data_Z_MC.plotOn(plot_Z_MC);
   model_Z_MC.plotOn(plot_Z_MC, RooFit::LineColor(kRed));
   model_Z_MC.plotOn(plot_Z_MC, RooFit::Components(CMS_Z_MC), RooFit::LineColor(kBlue)) ;
   model_Z_MC.plotOn(plot_Z_MC, RooFit::Components(CB_Z_MC), RooFit::LineColor(kGreen)) ;
   plot_Z_MC->Draw();

   c->cd(3);
   RooPlot* plot_fake_DT = m_fake_DT.frame();
   data_fake_DT.plotOn(plot_fake_DT);
   model_fake_DT.plotOn(plot_fake_DT, RooFit::LineColor(kRed));
   model_fake_DT.plotOn(plot_fake_DT, RooFit::Components(CMS_fake_DT), RooFit::LineColor(kBlue)) ;
   model_fake_DT.plotOn(plot_fake_DT, RooFit::Components(TP_fake_DT), RooFit::LineColor(kGreen)) ;
   plot_fake_DT->Draw();

   c->cd(4);
   RooPlot* plot_Z_DT = m_Z_DT.frame();
   data_Z_DT.plotOn(plot_Z_DT);
   model_Z_DT.plotOn(plot_Z_DT, RooFit::LineColor(kRed));
   model_Z_DT.plotOn(plot_Z_DT, RooFit::Components(CMS_Z_DT), RooFit::LineColor(kBlue)) ;
   model_Z_DT.plotOn(plot_Z_DT, RooFit::Components(CB_Z_DT), RooFit::LineColor(kGreen)) ;
   plot_Z_DT->Draw();

   string plot_title = "../../macros/html/egamma_v5/" + syst + "/plot/TP_bin_";
   plot_title += std::to_string(year);
   plot_title = plot_title + sqcd + "_";
   plot_title += std::to_string(number);
   plot_title = plot_title + ".pdf";
   c->SaveAs((plot_title).c_str());

   float n_fake_MC = h_WG_ele_ele0_pho0_fake_MC->Integral(1, h_WG_ele_ele0_pho0_fake_MC->GetNbinsX())*(1.-bkgfrac_fake_MC.getVal());
   float n_Z_MC = h_Z_ele_MC->Integral(1, h_Z_ele_MC->GetNbinsX())*(1.-bkgfrac_Z_MC.getVal());
   float n_fake_DT = h_WG_ele_ele0_pho0_fake_DT->Integral(1, h_WG_ele_ele0_pho0_fake_DT->GetNbinsX())*(1.-bkgfrac_fake_DT.getVal());
   float n_Z_DT = h_Z_ele_DT->Integral(1, h_Z_ele_DT->GetNbinsX())*(1.-bkgfrac_Z_DT.getVal());

   float N_D = h_WG_ele_ele0_pho0_fake_DT->Integral(1, h_WG_ele_ele0_pho0_fake_DT->GetNbinsX());
   float N_MC = h_WG_ele_ele0_pho0_fake_MC->Integral(1, h_WG_ele_ele0_pho0_fake_MC->GetNbinsX());
   float sf_error = (N_D/n_Z_DT) * (n_Z_MC/N_MC) * TMath::Sqrt( TMath::Power( fabs((1/(1-bkgfrac_fake_MC.getVal()))), 2) * TMath::Power(bkgfrac_fake_DT.getError(), 2) + TMath::Power(fabs((1-bkgfrac_fake_DT.getVal())/TMath::Power(1-bkgfrac_fake_MC.getVal(), 2)), 2) * TMath::Power(bkgfrac_fake_MC.getError(), 2));

   cout << "Scale factor for bin number " << number << " = " << (n_fake_DT/n_Z_DT)/(n_fake_MC/n_Z_MC) << endl;

   string txt_title = syst + "/sf_data_TP" + sqcd + "_";
   txt_title += std::to_string(year);
   txt_title = txt_title + ".txt";

   ofstream sf_data;
   sf_data.open((txt_title).c_str(), std::ios_base::app);
   sf_data << number << "\t" << (n_fake_DT/n_Z_DT)/(n_fake_MC/n_Z_MC) << "\t" << sf_error << endl;
   sf_data.close();

   float xsec_factor = 0;
   if (year == 2016) xsec_factor = 6225.42 * 1000. * 35.922 / h_nevt->GetBinContent(2);
   if (year == 2017) xsec_factor = 6225.42 * 1000. * 41.525 / h_nevt->GetBinContent(2);
   if (year == 2018) xsec_factor = 6225.42 * 1000. * 58.722 / h_nevt->GetBinContent(2);
   float n_fake_MC_lumixsec = n_fake_MC * xsec_factor;

   string txt_title2 = syst + "/sf_xsec_TP" + sqcd + "_";
   txt_title2 += std::to_string(year);
   txt_title2 = txt_title2 + ".txt";

   ofstream sf_xsec;
   sf_xsec.open((txt_title2).c_str(), std::ios_base::app);
   sf_xsec << number << "\t" << n_fake_DT/n_fake_MC_lumixsec << "\t" << (sf_error*n_Z_DT)/(n_Z_MC*xsec_factor) << endl;
   sf_xsec.close();  

}
