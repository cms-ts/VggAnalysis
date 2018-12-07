#include "plot2.h"

void plot2(string plot="", string title="", string version="v00", string flags="") {

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";

  plot = plot + ".dat";
  if (flags.find("test") != string::npos) plot = plot + ".test";

  if (flags.find("amcatnlo") != string::npos) plot = "amcatnlo/" + plot;
  if (flags.find("madgraph") != string::npos) plot = "madgraph/" + plot;

  map<string, float> xsecMap;
  readMap("xsec.dat", xsecMap);
  cout << "Read xsec map for " << xsecMap.size() << " datasets from " << "xsec.dat" << endl;

  multimap<string, float> plotMap;
  readMultiMap(plot, plotMap);
  cout << "Read plot map for " << plotMap.size() << " datasets from " << plot << endl;

  TH1D* h1 = 0;
  TH1D* h2 = 0;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if ((index >= 10 && index <= 12) || (index >= 1010 && index <= 1012)) {
      TFile* file = new TFile(("data/" + version + "/" + it->first + ".root").c_str());
      if (!file->IsOpen()) {
        cout << "ERROR: file " << it->first + ".root" << " is MISSING !!" << endl;
        return;
      }
      double norm = 1.;
      double ngen = ((TH1D*)gDirectory->Get("h_nevt"))->GetBinContent(2);
      if (xsecMap[it->first] != 0) {
        norm = xsecMap[it->first] / ngen;
      } else {
        cout << "ERROR: cross section for " << it->first << " is ZERO !!" << endl;
        return;
      }
      if (h1) {
        h1->Add((TH1D*)gDirectory->Get(title.c_str()), norm);
      } else {
        h1 = (TH1D*)gDirectory->Get(title.c_str());
        h1->SetDirectory(0);
        h1->Scale(norm);
      }
      if (h2) {
        h2->Add((TH1D*)gDirectory->Get((title + "_gen").c_str()), norm);
      } else {
        h2 = (TH1D*)gDirectory->Get((title + "_gen").c_str());
        h2->SetDirectory(0);
        h2->Scale(norm);
      }
      file->Close();
      delete file;
    }
  }

  if (flags.find("test") != string::npos) version = version + ".test";

  if (flags.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (flags.find("madgraph") != string::npos) version = version + ".madgraph";

  TH1D* h_eff = (TH1D*)h1->Clone();

  h_eff->Divide(h2);

  TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
  c1->cd();

  h_eff->SetStats(kFALSE);

  h_eff->Draw();

  TLatex* label = new TLatex();
  label->SetTextSize(0.0275);
  label->SetTextFont(42);
  label->SetLineWidth(2);
  label->SetNDC();
  char buff[100];
  sprintf(buff, "< #epsilon 0 > = %5.3f #pm %5.3f", h_eff->GetBinContent(1), h_eff->GetBinError(1));
  label->DrawLatex(0.50, 0.65, buff);
  sprintf(buff, "< #epsilon 1 > = %5.3f #pm %5.3f", h_eff->GetBinContent(2), h_eff->GetBinError(2));
  label->DrawLatex(0.50, 0.60, buff);
  sprintf(buff, "< #epsilon 2 > = %5.3f #pm %5.3f", h_eff->GetBinContent(3), h_eff->GetBinError(3));
  label->DrawLatex(0.50, 0.55, buff);

  gSystem->mkdir(("html/" + version + "/" + year + ".eff/").c_str(), kTRUE);
  c1->SaveAs(("html/" + version + "/" + year + ".eff/" + title + ".pdf").c_str());

  ofstream out;
  out.open(("html/" + version + "/" + year + ".eff/" + title + ".dat").c_str());
  out << 0 << " " << h_eff->GetBinContent(1) << " " << h_eff->GetBinError(1) << endl;
  out << 1 << " " << h_eff->GetBinContent(2) << " " << h_eff->GetBinError(2) << endl;
  out << 2 << " " << h_eff->GetBinContent(3) << " " << h_eff->GetBinError(3) << endl;
  out.close();

  gSystem->mkdir(("html/" + version + "/" + year + ".eff/root/").c_str(), kTRUE);
  TFile* file = new TFile(("html/" + version + "/" + year + ".eff/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + year + ".eff/root/" + title + ".root").c_str());
  h_eff->Write((title + "_eff").c_str());
  file->Close();
  delete file;

}
