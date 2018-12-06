#include "plot2.h"

#include "CMS_lumi.C"

void plot2(string plot="", string title="", string version="v00", string flags="") {

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";

  plot = plot + ".dat";
  if (flags.find("test") != string::npos) {
    plot = plot + ".test";
    version = version + ".test";
  }

  if (flags.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (flags.find("madgraph") != string::npos) version = version + ".madgraph";

  TFile* f1 = new TFile(("html/" + version + "/" + year + "/root/" + title + ".root").c_str());
  TFile* f2 = new TFile(("html/" + version + "/" + year + "/root/" + title + "_gen.root").c_str());

  TH1D* h1 = (TH1D*)f1->Get(title.c_str());
  TH1D* h2 = (TH1D*)f2->Get((title + "_gen").c_str());

  h1->SetDirectory(0);
  h2->SetDirectory(0);

  f1->Close();
  f2->Close();

  delete f1;
  delete f2;

  TH1D* h_eff = (TH1D*)h1->Clone();

  h_eff->Divide(h2);

  double xval;
  double xerr;
  xval = h1->IntegralAndError(0, h1->GetNbinsX()+1, xerr) / h2->Integral(0, h2->GetNbinsX()+1);
  xerr = xerr / h2->Integral(0, h2->GetNbinsX()+1);

  TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
  c1->cd();

  h_eff->Draw();

  TLatex* label = new TLatex();
  label->SetTextSize(0.0275);
  label->SetTextFont(42);
  label->SetLineWidth(2);
  label->SetNDC();
  char buff[100];
  sprintf(buff, "< #epsilon > = #frac{#int RECO}{#int GEN} = %5.3f #pm %5.3f", xval, xerr);
  label->DrawLatex(0.50, 0.68, buff);

  gSystem->mkdir(("html/" + version + "/" + year + ".eff/").c_str(), kTRUE);
  c1->SaveAs(("html/" + version + "/" + year + ".eff/" + title + ".pdf").c_str());

  ofstream out;
  out.open(("html/" + version + "/" + year + ".eff/" + title + ".dat").c_str());
  out << xval << " " << xerr << endl;
  out.close();

  gSystem->mkdir(("html/" + version + "/" + year + ".eff/root/").c_str(), kTRUE);
  TFile* file = new TFile(("html/" + version + "/" + year + "/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + year + "/root/" + title + ".root").c_str());
  h_eff->Write((title + "_eff").c_str());
  file->Close();
  delete file;

}
