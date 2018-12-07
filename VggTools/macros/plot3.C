#include "plot3.h"

#include "CMS_lumi.C"

void plot3(string plot="", string title="", string version="v00", string flags="") {

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";

  plot = plot + ".dat";
  if (flags.find("test") != string::npos) plot = plot + ".test";

  if (flags.find("amcatnlo") != string::npos) plot = "amcatnlo/" + plot;
  if (flags.find("madgraph") != string::npos) plot = "madgraph/" + plot;

  map<string, float> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets from " << "lumi.dat" << endl;

  multimap<string, float> plotMap;
  readMultiMap(plot, plotMap);
  cout << "Read plot map for " << plotMap.size() << " datasets from " << plot << endl;

  float lumi = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      if (lumiMap[it->first] != 0) {
        lumi = lumi + lumiMap[it->first];
      } else {
        cout << "ERROR: luminosity for " << it->first << " is ZERO !!" << endl;
        return;
      }
    }
  }

  if (flags.find("test") != string::npos) version = version + ".test";

  if (flags.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (flags.find("madgraph") != string::npos) version = version + ".madgraph";

  TFile* f1 = new TFile(("html/" + version + "/" + year + "/root/" + title + ".root").c_str());
  TFile* f2 = new TFile(("html/" + version + "/" + year + ".eff/root/" + title + ".root").c_str());

  TH1D* h1 = (TH1D*)f1->Get(title.c_str());
  TH1D* h2 = (TH1D*)f1->Get((title + "_gen").c_str());
  TH1D* h3 = (TH1D*)f2->Get((title + "_eff").c_str());

  h1->SetDirectory(0);
  h2->SetDirectory(0);
  h3->SetDirectory(0);

  f1->Close();
  f2->Close();

  delete f1;
  delete f2;

  TH1D* h_xsec = (TH1D*)h1->Clone();
  TH1D* h_gen = (TH1D*)h3->Clone();

//
//
//

  TH1D* h_ratio = (TH1D*)h1->Clone();

//
//
//

  gROOT->GetColor(kRed)->SetAlpha(0.5);
  gROOT->GetColor(kGreen+2)->SetAlpha(0.5);
  gROOT->GetColor(kMagenta-6)->SetAlpha(0.5);
  gROOT->GetColor(kBlue-4)->SetAlpha(0.5);
  gROOT->GetColor(kOrange+7)->SetAlpha(0.5);

  TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
  c1->cd();

  TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
  pad1->SetBottomMargin(0.001);
  pad1->Draw();
  pad1->cd();

//

  h_gen->SetStats(kFALSE);

  h_gen->SetTitle("");

  h_gen->SetLineColor(kGreen+2);
  h_gen->SetLineWidth(2);
  h_gen->SetFillColor(kGreen+2);
  h_gen->SetMarkerColor(kGreen+2);

  h_gen->Draw("E5");

  TH1D* h_gen1 = (TH1D*)h_gen->Clone();
  h_gen1->SetFillColor(0);
  h_gen1->Draw("HISTLSAME");

  h_xsec->SetStats(kFALSE);

  h_xsec->SetTitle("");

  h_xsec->GetXaxis()->SetTitleOffset(0.7);
  h_xsec->GetXaxis()->SetLabelSize(0.08);

  h_xsec->GetYaxis()->SetTitle("#sigma [pb]");
  h_xsec->GetYaxis()->SetTitleSize(0.05);
  h_xsec->GetYaxis()->SetTitleOffset(1.0);
  h_xsec->GetYaxis()->SetLabelSize(0.045);

  h_xsec->SetMarkerStyle(24);
  h_xsec->SetMarkerSize(0.7);

  h_xsec->SetMarkerColor(kBlack);
  h_xsec->SetLineColor(kBlack);

  h_xsec->Draw("E1PX0SAME");

  pad1->Update();
  c1->Update();
  c1->cd();

  TPad* pad2 = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->Draw();
  pad2->cd();

  h_ratio->SetTitle("");
  h_ratio->SetStats(kFALSE);

//
//
//

  h_ratio->GetXaxis()->SetTitleFont(42);
  h_ratio->GetXaxis()->SetTitleSize(0.11);
  h_ratio->GetXaxis()->SetTitleOffset(1.1);
  h_ratio->GetXaxis()->SetLabelFont(42);
  h_ratio->GetXaxis()->SetLabelSize(0.10);

  h_ratio->GetYaxis()->SetTitle("Data/Theory");
  h_ratio->GetYaxis()->SetTitleSize(0.11);
  h_ratio->GetYaxis()->SetTitleOffset(0.47);
  h_ratio->GetYaxis()->SetLabelSize(0.10);
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetRangeUser(0.5, 1.5);

  h_ratio->SetLineColor(kGreen+2);
  h_ratio->SetLineWidth(1);
  h_ratio->SetFillColor(kGreen+2);
  h_ratio->SetMarkerColor(kGreen+2);
  h_ratio->SetMarkerStyle(24);
  h_ratio->SetMarkerSize(0.7);

  h_ratio->Draw("E0PX0");

  TLine* line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1.0, h_ratio->GetXaxis()->GetXmax(), 1.0);
  line->SetLineColor(kRed);
  line->SetLineWidth(2);
  line->Draw();

  writeExtraText = true;

  lumi_13TeV  = Form("%.1f fb^{-1}", lumi);
  int iPeriod = 4;
  int iPos = 0;
  CMS_lumi(pad1, iPeriod, iPos);
  c1->cd();

  gSystem->mkdir(("html/" + version + "/" + year + ".xsec/").c_str(), kTRUE);
  c1->SaveAs(("html/" + version + "/" + year + ".xsec/" + title + ".pdf").c_str());

  gSystem->mkdir(("html/" + version + "/" + year + ".xsec/root/").c_str(), kTRUE);
  TFile* file = new TFile(("html/" + version + "/" + year + ".xsec/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + year + ".xsec/root/" + title + ".root").c_str());
  h_xsec->Write((title + "_eff").c_str());
  file->Close();
  delete file;

}
