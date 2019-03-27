#include "plot5.h"

#include "CMS_lumi.C"

void plot5(string plot="", string title="", string version="v00", string flags="") {

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";
  if (plot.find("Run2") != string::npos) year = "Run2";

  plot = plot + ".dat";
  if (flags.find("test") != string::npos) plot = plot + ".test";
  if (flags.find("new") != string::npos) plot = plot + ".new";
  if (flags.find("jet") != string::npos) plot = plot + ".jet";

  if (flags.find("amcatnlo") != string::npos) plot = "amcatnlo/" + plot;
  if (flags.find("madgraph") != string::npos) plot = "madgraph/" + plot;
  if (flags.find("default") != string::npos) plot = "default/" + plot;

  map<string, float> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets from " << "lumi.dat" << endl;

  multimap<string, float> plotMap;
  if (plot.find("Run2") == string::npos) {
    readMultiMap(plot, plotMap);
  } else {
    readMultiMap(string(plot).replace(plot.find("Run2"), 4, "2016"), plotMap);
    readMultiMap(string(plot).replace(plot.find("Run2"), 4, "2017"), plotMap);
    readMultiMap(string(plot).replace(plot.find("Run2"), 4, "2018"), plotMap);
  }
  cout << "Read plot map for " << plotMap.size() << " datasets from " << plot << endl;

  if (plotMap.size() == 0) {
    cout << "ERROR: plot map " << plot << " is EMPTY or MISSING !!" << endl;
    return;
  }

  float lumi = 0.;
  float lumi2016 = 0.;
  float lumi2017 = 0.;
  float lumi2018 = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      if (lumiMap[it->first] != 0) {
        lumi = lumi + lumiMap[it->first];
        lumi2016 = lumi2016 + lumiMap[it->first];
        lumi2017 = lumi2017 + lumiMap[it->first];
        lumi2018 = lumi2018 + lumiMap[it->first];
      } else {
        cout << "WARNING: luminosity for " << it->first << " is ZERO !!" << endl;
      }
    }
  }

  if (lumi == 0) {
    cout << "ERROR: total luminosity is ZERO !!" << endl;
    return;
  }

  if (flags.find("test") != string::npos) version = version + ".test";
  if (flags.find("new") != string::npos) version = version + ".new";
  if (flags.find("jet") != string::npos) version = version + ".jet";

  if (flags.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (flags.find("madgraph") != string::npos) version = version + ".madgraph";
  if (flags.find("default") != string::npos) version = version + ".default";

  TFile* f1 = new TFile(("html/" + version + "/" + year + "/root/" + title + ".root").c_str());
  TFile* f2 = new TFile(("html/" + version + "/" + year + ".eff/root/" + title + ".root").c_str());

  TH1D* h_data = (TH1D*)f1->Get(title.c_str());
  TH1D* h_mc_gen = (TH1D*)f1->Get((title + "_mc_gen").c_str());
  TH1D* h_mc_eff = (TH1D*)f2->Get((title + "_mc_eff").c_str());

  h_data->SetDirectory(0);
  h_mc_gen->SetDirectory(0);
  h_mc_eff->SetDirectory(0);

  f1->Close();
  f2->Close();

  delete f1;
  delete f2;

  TH1D* h_xsec_rec = (TH1D*)h_data->Clone("h_xsec_rec");

  h_xsec_rec->Divide(h_mc_eff);
  h_xsec_rec->Scale(1. / (1000. * lumi));

  TH1D* h_xsec_mc_gen = (TH1D*)h_mc_gen->Clone("h_xsec_mc_gen");

  h_xsec_mc_gen->Scale(1. / (1000. * lumi));

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

  h_xsec_mc_gen->SetMaximum(1.2*TMath::Max(h_xsec_mc_gen->GetMaximum(), h_xsec_rec->GetMaximum()));
  h_xsec_mc_gen->SetMinimum(TMath::Max(0.005, 0.8*TMath::Min(h_xsec_mc_gen->GetMinimum(), h_xsec_rec->GetMinimum())));

  pad1->SetLogy();

  h_xsec_mc_gen->SetTitle("");
  h_xsec_mc_gen->SetStats(kFALSE);

  h_xsec_mc_gen->SetLineColor(kBlue-4);
  h_xsec_mc_gen->SetLineWidth(2);
  h_xsec_mc_gen->SetFillColor(kBlue-4);
  h_xsec_mc_gen->SetMarkerColor(kBlue-4);

  h_xsec_mc_gen->GetXaxis()->SetTitleOffset(0.7);
  h_xsec_mc_gen->GetXaxis()->SetLabelFont(42);
  h_xsec_mc_gen->GetXaxis()->SetLabelSize(0.08);

  h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dN_{#gamma} [pb]");
  h_xsec_mc_gen->GetYaxis()->SetTitleSize(0.05);
  h_xsec_mc_gen->GetYaxis()->SetTitleOffset(0.8);
  h_xsec_mc_gen->GetYaxis()->SetLabelSize(0.045);

  h_xsec_mc_gen->GetXaxis()->SetRangeUser(-0.5, 2.5);

  h_xsec_mc_gen->Draw("E5");

  TH1D* h_xsec_mc_gen1 = (TH1D*)h_xsec_mc_gen->Clone("h_xsec_mc_gen1");
  h_xsec_mc_gen1->SetFillColor(0);
  h_xsec_mc_gen1->Draw("HISTLSAME");

  h_xsec_rec->SetTitle("");
  h_xsec_rec->SetStats(kFALSE);

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

  TH1D* h_ratio_rec = (TH1D*)h_xsec_rec->Clone("h_ratio_rec");

  TH1D* h_xsec_mc_gen2 = (TH1D*)h_xsec_mc_gen->Clone("h_xsec_mc_gen2");
  for (int i = 0; i < h_xsec_mc_gen2->GetNbinsX()+1; i++) {
    h_xsec_mc_gen2->SetBinError(i, 0.);
  }
  h_ratio_rec->Divide(h_xsec_mc_gen2);

  TPad* pad2 = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->Draw();
  pad2->cd();

  TH1D* h_ratio_gen = (TH1D*)h_xsec_mc_gen->Clone("h_ratio_gen");
  h_ratio_gen->Divide(h_xsec_mc_gen2);

  h_ratio_gen->SetTitle("");
  h_ratio_gen->SetStats(kFALSE);

  h_ratio_gen->GetXaxis()->SetTitle("N_{#gamma}");
  h_ratio_gen->GetXaxis()->SetTitleFont(42);
  h_ratio_gen->GetXaxis()->SetTitleSize(0.11);
  h_ratio_gen->GetXaxis()->SetTitleOffset(1.0);
  h_ratio_gen->GetXaxis()->SetLabelFont(42);
  h_ratio_gen->GetXaxis()->SetLabelSize(0.10);

  h_ratio_gen->GetYaxis()->SetTitle("Data/Theory");
  h_ratio_gen->GetYaxis()->SetTitleSize(0.11);
  h_ratio_gen->GetYaxis()->SetTitleOffset(0.35);
  h_ratio_gen->GetYaxis()->SetLabelSize(0.10);
  h_ratio_gen->GetYaxis()->SetNdivisions(505);
  h_ratio_gen->GetYaxis()->SetRangeUser(0.5, 1.5);

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

  TLatex* label = new TLatex();
  label->SetTextFont(43);
  label->SetTextSize(16);
  label->SetLineWidth(2);
  label->SetNDC();

  if (plot.find("W") != string::npos) {
    label->DrawLatex(0.55, 0.85, "W, W#gamma, W#gamma#gamma selection");
    if (plot.find("ele") != string::npos) {
      label->DrawLatex(0.55, 0.80, "W #rightarrow e#nu");
      label->DrawLatex(0.55, 0.75, "p_{T}^{e} > 40 GeV, #||{#eta^{e}} < 2.4, #slash{E}_{T} > 40 GeV");
    }
    if (plot.find("muo") != string::npos) {
      label->DrawLatex(0.55, 0.80, "W #rightarrow #mu#nu");
      label->DrawLatex(0.55, 0.75, "p_{T}^{#mu} > 30 GeV, #||{#eta^{#mu}} < 2.4, #slash{E}_{T} > 40 GeV");
    }
    label->DrawLatex(0.55, 0.69, "p_{T}^{#gamma#scale[0.8]{1}} > 20 GeV, p_{T}^{#gamma#scale[0.8]{2}} > 15 GeV, #||{#eta^{#gamma}} < 2.4");
  }
  if (plot.find("Z") != string::npos) {
    label->DrawLatex(0.55, 0.85, "Z, Z#gamma, Z#gamma#gamma selection");
    if (plot.find("ele") != string::npos) {
      label->DrawLatex(0.55, 0.80, "Z #rightarrow ee");
      label->DrawLatex(0.55, 0.75, "p_{T}^{e} > 25 GeV, #||{#eta^{e}} < 2.4");
    }
    if (plot.find("muo") != string::npos) {
      label->DrawLatex(0.55, 0.80, "Z #rightarrow #mu#mu");
      label->DrawLatex(0.55, 0.75, "p_{T}^{#mu} > 25 GeV, #||{#eta^{#mu}} < 2.4");
    }
    label->DrawLatex(0.55, 0.69, "p_{T}^{#gamma#scale[0.8]{1}} > 20 GeV, p_{T}^{#gamma#scale[0.8]{2}} > 15 GeV, #||{#eta^{#gamma}} < 2.4");
  }

  label->Draw("same");

  while (gSystem->AccessPathName(("html/" + version + "/" + year + ".xsec/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + year + ".xsec/").c_str(), kTRUE);
  }
  c1->SaveAs(("html/" + version + "/" + year + ".xsec/" + title + ".pdf").c_str());

  while (gSystem->AccessPathName(("html/" + version + "/" + year + ".xsec/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + year + ".xsec/root/").c_str(), kTRUE);
  }
  TFile* file = new TFile(("html/" + version + "/" + year + ".xsec/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + year + ".xsec/root/" + title + ".root").c_str());
  h_xsec_rec->Write((title + "_xsec").c_str());
  h_xsec_mc_gen->Write((title + "_xsec_mc_gen").c_str());
  file->Close();
  delete file;

}

int main(int argc, char *argv[]) {

plot5(argv[1], argv[2], argv[3], argv[4]);

}