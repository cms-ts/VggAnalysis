#include "plot1.h"

#include "CMS_lumi.C"

void plot1(string plot="", string title="", string version="v00", string flags="") {

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";

  plot = plot + ".dat";
  if (flags.find("test") != string::npos) plot = plot + ".test";

  year = year + ".qcd";

  if (flags.find("fit") != string::npos) {

    TFile* f1 = TFile::Open(("html/" + version + "/" + year + "/root/" + title + ".root").c_str());
    TFile* f2 = TFile::Open(("html/" + version + "/" + year + "/root/" + title + "_qcd.root").c_str());

    TH1D* h1 = (TH1D*)f1->Get((title).c_str());
    TH1D* h2 = (TH1D*)f2->Get((title + "_qcd").c_str());

    for (int i = h1->FindBin(40.); i <= h1->GetNbinsX(); i++) {
      h1->SetBinContent(i, 0.);
      h1->SetBinError(i, 0.);
      h2->SetBinContent(i, 0.);
      h2->SetBinError(i, 0.);
    }

    double xval = h1->Integral() / h2->Integral();

    ofstream out;
    out.open(("html/" + version + "/" + year + "/root/" + title + "_qcd.dat").c_str());
    out << xval << " " << xval << endl;
    out.close();

    h2->Scale(xval);

    TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
    c1->cd();

    h1->Draw();
    h2->Draw("same");
    h2->SetLineColor(kRed);

    c1->SaveAs(("html/" + version + "/" + year + "/root/" + title + "_qcdfit.pdf").c_str());

  }

  if (flags.find("fit") != string::npos) return;

  if (flags.find("qcd") != string::npos) title = title + "_qcd";

  map<string, float> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets from " << "lumi.dat" << endl;

  map<string, float> xsecMap;
  readMap("xsec.dat", xsecMap);
  cout << "Read xsec map for " << xsecMap.size() << " datasets from " << "xsec.dat" << endl;

  multimap<string, float> plotMap;
  readMultiMap(plot, plotMap);
  cout << "Read plot map for " << plotMap.size() << " datasets from " << plot << endl;

  if (plotMap.size() == 0) {
    cout << "ERROR: plot map " << plot << " is EMPTY or MISSING !!" << endl;
    return;
  }

  map<int, TH1D*> histo;

  float lumi = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      TFile file(("data/" + version + "/" + it->first + ".root").c_str()); 
      if (lumiMap[it->first] != 0) {
        lumi = lumi + lumiMap[it->first];
      } else {
        cout << "ERROR: luminosity for " << it->first << " is ZERO !!" << endl;
        return;
      }
      if (histo[index]) {
        histo[index]->Add((TH1D*)gDirectory->Get(title.c_str()));
      } else {
        histo[index] = (TH1D*)gDirectory->Get(title.c_str());
        if (histo[index]) {
          histo[index]->SetDirectory(0);
        } else {
          Error("plot0", "skip missing histogram: %s", title.c_str());
          return;
        }
      }
      file.Close();
    }
  }

  double ngen = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index > 0) {
      TFile file(("data/" + version + "/" + it->first + ".root").c_str()); 
      if (!file.IsOpen()) {
        cout << "ERROR: file " << it->first + ".root" << " is MISSING !!" << endl;
        return;
      }
      ngen = ((TH1D*)gDirectory->Get("h_nevt"))->GetBinContent(2);
      double norm = 1.;
      if (xsecMap[it->first] != 0) {
        norm = xsecMap[it->first] * 1000. * lumi / ngen;
      } else {
        cout << "ERROR: cross section for " << it->first << " is ZERO !!" << endl;
        return;
      }
      if (histo[index]) {
        histo[index]->Add((TH1D*)gDirectory->Get(title.c_str()), norm);
      } else {
        histo[index] = (TH1D*)gDirectory->Get(title.c_str());
        histo[index]->SetDirectory(0);
        histo[index]->Scale(norm);
      }
      file.Close();
    }
  }

  TH1D* h_mcsum = (TH1D*) histo[0]->Clone("h_mcsum");
  h_mcsum->Reset();  

  for (map<int, TH1D*>::reverse_iterator it = histo.rbegin(); it != histo.rend(); it++) {
    if (it->first > 0) {
       h_mcsum->Add(it->second);
    }
  }

  TH1D* h_qcd = (TH1D*) histo[0]->Clone("h_qcd");

  h_qcd->Add(h_mcsum, -1);

  if (flags.find("test") != string::npos) version = version + ".test";

  gSystem->mkdir(("html/" + version + "/" + year + "/root/").c_str(), kTRUE);
  TFile f(("html/" + version + "/" + year + "/root/" + title + ".root").c_str(), "RECREATE");
  h_qcd->Write(title.c_str());
  f.Close();

}