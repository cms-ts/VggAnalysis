#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"
#include "Riostream.h"
#include "TMath.h"
#include "TROOT.h"

void merger(int year, string title) {

   TFile * f0 = 0;
   TFile * f1 = 0;
   TFile * f2 = 0;

   if (year == 2016) {
     f0 = new TFile("RunIISummer16NanoAODv6_DYToLL_0J_13TeV-amcatnloFXFX-pythia8.root");
     f1 = new TFile("RunIISummer16NanoAODv6_DYToLL_1J_13TeV-amcatnloFXFX-pythia8.root");
     f2 = new TFile("RunIISummer16NanoAODv6_DYToLL_2J_13TeV-amcatnloFXFX-pythia8.root");
   }
   if (year == 2017) {
     f0 = new TFile("RunIIFall17NanoAODv6_DYJetsToLL_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
     f1 = new TFile("RunIIFall17NanoAODv6_DYJetsToLL_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
     f2 = new TFile("RunIIFall17NanoAODv6_DYJetsToLL_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
   }
   if (year == 2018) {
     f0 = new TFile("RunIIAutumn18NanoAODv6_DYJetsToLL_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
     f1 = new TFile("RunIIAutumn18NanoAODv6_DYJetsToLL_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
     f2 = new TFile("RunIIAutumn18NanoAODv6_DYJetsToLL_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
   }

   TH1D * h0 = (TH1D*)f0->Get((title).c_str());
   TH1D * h1 = (TH1D*)f1->Get((title).c_str());
   TH1D * h2 = (TH1D*)f2->Get((title).c_str());

   TH1D * hn0 = (TH1D*)f0->Get("h_nevt");
   TH1D * hn1 = (TH1D*)f1->Get("h_nevt");
   TH1D * hn2 = (TH1D*)f2->Get("h_nevt");

   double total_xsec = 4833.39 + 889.66 + 354.17;

   h0->Scale(4833.39 * hn0->GetBinContent(1)/(total_xsec * hn0->GetBinContent(2)));
   h1->Scale( 889.66 * hn1->GetBinContent(1)/(total_xsec * hn1->GetBinContent(2)));
   h2->Scale( 354.17 * hn2->GetBinContent(1)/(total_xsec * hn2->GetBinContent(2)));

   TH1D * h = (TH1D*)h0->Clone("h");
   h->Add(h1);
   h->Add(h2);

   string root_title = "";
   if (year == 2016) root_title = "RunIISummer16NanoAODv6_DYToLL_13TeV-amcatnloFXFX-pythia8.root";
   if (year == 2017) root_title = "RunIIFall17NanoAODv6_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8.root";
   if (year == 2018) root_title = "RunIIAutumn18NanoAODv6_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8.root"; 

   TFile * file_root = new TFile((root_title).c_str(), "UPDATE");
   h->Write((title).c_str(),TObject::kOverwrite);
   file_root->Close();

}
