#include "plot2.h"
#include "rebin.h"

void plot2(string plot="", string title="", string version="v00", string options="", string flag="reference") {

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";
  if (plot.find("Run2") != string::npos) year = "Run2";

  plot = plot + ".dat";
  if (options.find("test") != string::npos) plot = plot + ".test";
  if (options.find("new") != string::npos) plot = plot + ".new";
  if (options.find("jet") != string::npos) plot = plot + ".jet";

  if (options.find("amcatnlo") != string::npos) plot = "amcatnlo/" + plot;
  if (options.find("madgraph") != string::npos) plot = "madgraph/" + plot;
  if (options.find("default") != string::npos) plot = "default/" + plot;

  map<string, float> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets from " << "lumi.dat" << endl;

  map<string, float> xsecMap;
  readMap("xsec.dat", xsecMap);
  cout << "Read xsec map for " << xsecMap.size() << " datasets from " << "xsec.dat" << endl;

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
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "mc_matrix" || flag == "mc_bkg" || flag == "qcd_fit") {
        file = new TFile(("data/" + version + "/reference/" + it->first + ".root").c_str());
      } else {
        file = new TFile(("data/" + version + "/" + flag + "/" + it->first + ".root").c_str());
      }
      if (file->IsZombie()) {
        cout << "ERROR: file " << it->first + ".root" << " is MISSING !!" << endl;
        return;
      }
      if (lumiMap[it->first] != 0) {
        lumi = lumi + lumiMap[it->first];
        if (it->first.find("Run2016") != string::npos) lumi2016 = lumi2016 + lumiMap[it->first];
        if (it->first.find("Run2017") != string::npos) lumi2017 = lumi2017 + lumiMap[it->first];
        if (it->first.find("Run2018") != string::npos) lumi2018 = lumi2018 + lumiMap[it->first];
      } else {
        cout << "WARNING: luminosity for " << it->first << " is ZERO !!" << endl;
      }
      file->Close();
      delete file;
    }
  }

  if (lumi == 0) {
    cout << "ERROR: total luminosity is ZERO !!" << endl;
    return;
  }

  TH1D* h1 = 0;
  TH1D* h2 = 0;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (title.find("nphotons") != string::npos) {
      if (!((index >= 10 && index <= 12) || (index >= 1010 && index <= 1012))) continue;
    } else {
      if (index !=   10 && title.find("h_ZGG_") != string::npos) continue;
      if (index != 1010 && title.find("h_WGG_") != string::npos) continue;
    }
    TFile* file = 0;
    if (flag == "bkg_stat" || flag == "mc_matrix" || flag == "mc_bkg" || flag == "qcd_fit") {
      file = new TFile(("data/" + version + "/reference/" + it->first + ".root").c_str());
    } else {
      file = new TFile(("data/" + version + "/" + flag + "/" + it->first + ".root").c_str());
    }
    if (file->IsZombie()) {
      cout << "ERROR: file " << it->first + ".root" << " is MISSING !!" << endl;
      return;
    }
    double norm = 1.;
    if (xsecMap[it->first] != 0) {
      double ngen = ((TH1D*)gDirectory->Get("h_nevt"))->GetBinContent(2);
      norm = xsecMap[it->first] * 1000. * lumi / ngen;
      if (it->first.find("RunIISummer16") != string::npos) norm = norm * lumi2016 / lumi;
      if (it->first.find("RunIIFall17") != string::npos) norm = norm * lumi2017 / lumi;
      if (it->first.find("RunIIAutumn18") != string::npos) norm = norm * lumi2018 / lumi;
    } else {
      cout << "ERROR: cross section for " << it->first << " is ZERO !!" << endl;
      return;
    }
    if (h1) {
      TH1D* h = (TH1D*)gDirectory->Get(title.c_str());
      if (h) {
        h1->Add(h, norm);
      }
    } else {
      TH1D* h = (TH1D*)gDirectory->Get(title.c_str());
      if (h) {
        h1 = h;
        h1->SetDirectory(0);
        h1->Scale(norm);
      }
    }
    if (h2) {
      TH1D* h = (TH1D*)gDirectory->Get((title + "_gen").c_str());
      if (h) {
        h2->Add(h, norm);
      }
    } else {
      TH1D* h = (TH1D*)gDirectory->Get((title + "_gen").c_str());
      if (h) {
        h2 = h;
        h2->SetDirectory(0);
        h2->Scale(norm);
      }
    }
    file->Close();
    delete file;
  }

  if (h1) h1 = rebin(h1);
  if (h2) h2 = rebin(h2);

  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("default") != string::npos) version = version + ".default";

  TH1D* h_mc_eff = (TH1D*)h1->Clone("h_mc_eff");

  h_mc_eff->Divide(h2);

  TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
  c1->cd();

  h_mc_eff->SetStats(kFALSE);

  h_mc_eff->SetMinimum(0.);
  h_mc_eff->SetMaximum(1.);

  h_mc_eff->Draw("0");

  TLatex* label = new TLatex();
  label->SetTextSize(0.0275);
  label->SetTextFont(42);
  label->SetLineWidth(2);
  label->SetNDC();
  char buff[100];
  if (title.find("nphotons") != string::npos) {
    sprintf(buff, "< #epsilon 0 > = %5.3f #pm %5.3f", h_mc_eff->GetBinContent(1), h_mc_eff->GetBinError(1));
    label->DrawLatex(0.50, 0.65, buff);
    sprintf(buff, "< #epsilon 1 > = %5.3f #pm %5.3f", h_mc_eff->GetBinContent(2), h_mc_eff->GetBinError(2));
    label->DrawLatex(0.50, 0.60, buff);
    sprintf(buff, "< #epsilon 2 > = %5.3f #pm %5.3f", h_mc_eff->GetBinContent(3), h_mc_eff->GetBinError(3));
    label->DrawLatex(0.50, 0.55, buff);
  } else {
    double xval = 0.;
    double xerr = 0.;
    xval = h1->IntegralAndError(0, h1->GetNbinsX()+1, xerr);
    xval = xval / h2->Integral(0, h2->GetNbinsX()+1);
    xerr = xerr / h2->Integral(0, h2->GetNbinsX()+1);
    sprintf(buff, "< #epsilon > = %5.3f #pm %5.3f", xval, xerr);
    label->DrawLatex(0.50, 0.65, buff);
  }

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".eff/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".eff/").c_str(), kTRUE);
  }
  c1->SaveAs(("html/" + version + "/" + flag + "/" + year + ".eff/" + title + ".pdf").c_str());

  ofstream out;
  out.open(("html/" + version + "/" + flag + "/" + year + ".eff/" + title + ".dat").c_str());
  for (int i = 0; i < h_mc_eff->GetNbinsX()+1; i++) {
    out << i << " " << h_mc_eff->GetBinContent(i) << " " << h_mc_eff->GetBinError(i) << endl;
  }
  out.close();

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".eff/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".eff/root/").c_str(), kTRUE);
  }
  TFile* file = new TFile(("html/" + version + "/" + flag + "/" + year + ".eff/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + flag + "/" + year + ".eff/root/" + title + ".root").c_str());
  h1->Write((title + "_mc_rec").c_str());
  h2->Write((title + "_mc_gen").c_str());
  h_mc_eff->Write((title + "_mc_eff").c_str());
  file->Close();
  delete file;

}

int main(int argc, char *argv[]) {

plot2(argv[1], argv[2], argv[3], argv[4], argv[5]);

}
