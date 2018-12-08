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

  TH1D* h_rec = (TH1D*)f1->Get(title.c_str());
  TH1D* h_gen = (TH1D*)f1->Get((title + "_gen").c_str());
  TH1D* h_eff = (TH1D*)f2->Get((title + "_eff").c_str());

  h_rec->SetDirectory(0);
  h_gen->SetDirectory(0);
  h_eff->SetDirectory(0);

  f1->Close();
  f2->Close();

  delete f1;
  delete f2;

  TH1D* h_xsec_rec = (TH1D*)h_rec->Clone();

  h_xsec_rec->Divide(h_eff);
  h_xsec_rec->Scale(1. / (1000. * lumi));

  TH1D* h_xsec_gen = (TH1D*)h_gen->Clone();

  h_xsec_gen->Scale(1. / (1000. * lumi));

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

  h_xsec_gen->SetMaximum(1.2*TMath::Max(h_xsec_gen->GetMaximum(), h_xsec_rec->GetMaximum()));
  h_xsec_gen->SetMinimum(TMath::Max(0.005, 0.8*TMath::Min(h_xsec_gen->GetMinimum(), h_xsec_rec->GetMinimum())));

  pad1->SetLogy();

  h_xsec_gen->SetStats(kFALSE);

  h_xsec_gen->SetTitle("");

  h_xsec_gen->SetLineColor(kBlue-4);
  h_xsec_gen->SetLineWidth(2);
  h_xsec_gen->SetFillColor(kBlue-4);
  h_xsec_gen->SetMarkerColor(kBlue-4);

  h_xsec_gen->GetXaxis()->SetTitleOffset(0.7);
  h_xsec_gen->GetXaxis()->SetLabelFont(42);
  h_xsec_gen->GetXaxis()->SetLabelSize(0.08);

  h_xsec_gen->GetYaxis()->SetTitleSize(0.05);
  h_xsec_gen->GetYaxis()->SetTitleOffset(0.8);
  h_xsec_gen->GetYaxis()->SetLabelSize(0.045);

  h_xsec_gen->GetYaxis()->SetTitle("d#sigma / dN_{#gamma} [pb]");

  h_xsec_gen->GetXaxis()->SetRangeUser(-0.5, 2.5);

  h_xsec_gen->Draw("E5");

  TH1D* h_xsec_gen1 = (TH1D*)h_xsec_gen->Clone();
  h_xsec_gen1->SetFillColor(0);
  h_xsec_gen1->Draw("HISTLSAME");

  h_xsec_rec->SetStats(kFALSE);

  h_xsec_rec->SetTitle("");

  h_xsec_rec->SetLineColor(kBlack);
  h_xsec_rec->SetLineWidth(1);
  h_xsec_rec->SetFillColor(kBlack);
  h_xsec_rec->SetMarkerColor(kBlack);
  h_xsec_rec->SetMarkerStyle(24);
  h_xsec_rec->SetMarkerSize(0.7);

  h_xsec_rec->SetMarkerColor(kBlack);

  h_xsec_rec->Draw("E0P0X0SAME");

  pad1->Update();
  c1->Update();
  c1->cd();

  TH1D* h_ratio_rec = (TH1D*)h_xsec_rec->Clone();

  TH1D* h_xsec_gen2 = (TH1D*)h_xsec_gen->Clone();
  for (int i = 0; i < h_xsec_gen2->GetNbinsX()+1; i++) {
    h_xsec_gen2->SetBinError(i, 0.);
  }
  h_ratio_rec->Divide(h_xsec_gen2);

  TPad* pad2 = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->Draw();
  pad2->cd();

  TH1D* h_ratio_gen = (TH1D*)h_xsec_gen->Clone();
  h_ratio_gen->Divide(h_xsec_gen2);

  h_ratio_gen->SetTitle("");
  h_ratio_gen->SetStats(kFALSE);

  h_ratio_gen->GetXaxis()->SetTitleFont(42);
  h_ratio_gen->GetXaxis()->SetTitleSize(0.11);
  h_ratio_gen->GetXaxis()->SetTitleOffset(1.0);
  h_ratio_gen->GetXaxis()->SetLabelFont(42);
  h_ratio_gen->GetXaxis()->SetLabelSize(0.10);
  h_ratio_gen->GetXaxis()->SetTitle("N_{#gamma}");

  h_ratio_gen->GetYaxis()->SetTitleSize(0.11);
  h_ratio_gen->GetYaxis()->SetTitleOffset(0.35);
  h_ratio_gen->GetYaxis()->SetLabelSize(0.10);
  h_ratio_gen->GetYaxis()->SetNdivisions(505);
  h_ratio_gen->GetYaxis()->SetRangeUser(0.5, 1.5);
  h_ratio_gen->GetYaxis()->SetTitle("Data/Theory");

  h_ratio_gen->GetXaxis()->SetRangeUser(-0.5, 2.5);

  h_ratio_gen->GetXaxis()->SetNdivisions(1003);
  h_ratio_gen->GetXaxis()->SetTickLength(0.1);

  h_ratio_gen->Draw("E5");

  pad2->Update();
  TLine* line = new TLine(pad2->GetUxmax(), 1.0, pad2->GetUxmin(), 1.0);
  line->SetLineColor(kBlue-4);
  line->SetLineWidth(2);
  line->Draw();

  h_ratio_rec->SetLineColor(kBlack);
  h_ratio_rec->SetLineWidth(1);
  h_ratio_rec->SetFillColor(kBlack);
  h_ratio_rec->SetMarkerColor(kBlack);
  h_ratio_rec->SetMarkerStyle(24);
  h_ratio_rec->SetMarkerSize(0.7);

  h_ratio_rec->Draw("E0P0X0SAME");

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
  h_xsec_rec->Write((title + "_xsec").c_str());
  h_xsec_gen->Write((title + "_xsec_gen").c_str());
  file->Close();
  delete file;

}
