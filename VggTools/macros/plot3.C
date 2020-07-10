#include "plot3.h"
#include "rebin.h"

#include "CMS_lumi.C"

void plot3(string plot="", string title="", string version="v00", string options="", string flag="reference") {

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
  if (options.find("sherpa") != string::npos) plot = "sherpa/" + plot;
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

  map<int, TH3D*> histo;
  map<int, TH1D*> histo1;

  float lumi = 0.;
  float lumi2016 = 0.;
  float lumi2017 = 0.;
  float lumi2018 = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit" || flag == "lumi_up" || flag == "lumi_down") {
        file = new TFile(("data/" + version + "/reference/" + it->first + ".root").c_str());
      } else {
        file = new TFile(("data/" + version + "/" + flag + "/" + it->first + ".root").c_str());
      }
      if (file->IsZombie()) {
        cout << "ERROR: file " << it->first + ".root" << " is MISSING !!" << endl;
        return;
      }
      if (lumiMap[it->first] != 0) {
        float var = (flag == "lumi_up") - (flag == "lumi_down");
        lumi = lumi + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2016") != string::npos) lumi2016 = lumi2016 + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2017") != string::npos) lumi2017 = lumi2017 + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2018") != string::npos) lumi2018 = lumi2018 + lumiMap[it->first] * (1.000 + 0.018 * var);
      } else {
        cout << "WARNING: luminosity for " << it->first << " is ZERO !!" << endl;
      }

      if (histo1[index]) {
        TH1D* h1 = (TH1D*)gDirectory->Get(title.c_str());
        if (h1) {
          histo1[index]->Add(h1);
        }
      } else {
        TH1D* h1 = (TH1D*)gDirectory->Get(title.c_str());
        if (h1) {
          histo1[index] = h1;
          histo1[index]->SetDirectory(0);
        } else {
          Error("plot0", "skip missing histogram: %s", title.c_str());
          return;
        }
      }
      if (histo[index]) {
        TH3D* h = (TH3D*)gDirectory->Get(string(title).erase(title.find("pho0_pt"), 6).c_str());
        if (h) {
          histo[index]->Add(h);
        }
      } else {
        TH3D* h = (TH3D*)gDirectory->Get(string(title).erase(title.find("pho0_pt"), 6).c_str());
        if (h) {
          histo[index] = h;
          histo[index]->SetDirectory(0);
        } else {
          Error("plot0", "skip missing histogram: %s", string(title).erase(title.find("pho0_pt"), 6).c_str());
          return;
        }
      }

      file->Close();
      delete file;
    }
  }

  if (lumi == 0) {
    cout << "ERROR: total luminosity is ZERO !!" << endl;
    return;
  }

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 10 || index == 11 || index == 21 || index == 22 || index == 31 || index == 41 || index == 42 || index == 51 || index == 1010 || index == 1011 || index == 1021 || index == 1022 || index == 1031 || index == 1032 || index == 1041 || index == 1051) {
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit" || flag == "lumi_up" || flag == "lumi_down") {
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
        if (it->first.find("RunIISummer16") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2016 / ngen;
        if (it->first.find("RunIIFall17") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2017 / ngen;
        if (it->first.find("RunIIAutumn18") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2018 / ngen;
      } else {
        cout << "ERROR: cross section for " << it->first << " is ZERO !!" << endl;
        return;
      }
      if (histo[index]) {
        TH3D* h = (TH3D*)gDirectory->Get((string(title).erase(title.find("pho0_pt"), 6) + "_genmatch").c_str());
        if (h) {
          histo[index]->Add(h, norm);
        }
      } else {
        TH3D* h = (TH3D*)gDirectory->Get((string(title).erase(title.find("pho0_pt"), 6) + "_genmatch").c_str());
        if (h) {
          histo[index] = h;
          histo[index]->SetDirectory(0);
          histo[index]->Scale(norm);
        }
      }
      file->Close();
      delete file;
    }
  }

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 10 || index == 11 || index == 21 || index == 22 || index == 31 || index == 41 || index == 42 || index == 51 || index == 1010 || index == 1011 || index == 1021 || index == 1022 || index == 1031 || index == 1032 || index == 1041 || index == 1051) {
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit" || flag == "lumi_up" || flag == "lumi_down") {
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
        if (it->first.find("RunIISummer16") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2016 / ngen;
        if (it->first.find("RunIIFall17") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2017 / ngen;
        if (it->first.find("RunIIAutumn18") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2018 / ngen;
      } else {
        cout << "ERROR: cross section for " << it->first << " is ZERO !!" << endl;
        return;
      }
      if (histo1[index]) {
        TH1D* h1 = (TH1D*)gDirectory->Get((title + "_genmatch").c_str());
        if (h1) {
          histo1[index]->Add(h1, norm);
        }
      } else {
        TH1D* h1 = (TH1D*)gDirectory->Get((title + "_genmatch").c_str());
        if (h1) {
          histo1[index] = h1;
          histo1[index]->SetDirectory(0);
          histo1[index]->Scale(norm);
        }
      }
      file->Close();
      delete file;
    }
  }

  for (map<int, TH3D*>::iterator it = histo.begin(); it != histo.end(); it++) {
    int index = int(it->first);
    if (histo[index]) histo[index] = rebin(histo[index]);
  }

  for (map<int, TH1D*>::iterator it = histo1.begin(); it != histo1.end(); it++) {
    int index = int(it->first);
    if (histo1[index]) histo1[index] = rebin(histo1[index]);
  }

  int myindex = -1;

  if (title.find("h_WG") != string::npos) myindex = 1011;
  if (title.find("h_ZG") != string::npos) myindex = 11;

  for (int i = 0; i < histo[myindex]->GetNbinsX() + 2; i++) {
    for (int j = 0; j < histo[myindex]->GetNbinsY() + 2; j++) {
      for (int k = 0; k < histo[myindex]->GetNbinsZ() + 2; k++) {
        if (histo[myindex]->GetBinContent(i, j, k) < 0) {
          histo[myindex]->SetBinContent(i, j, k, 0.);
          histo[myindex]->SetBinError(i, j, k, 0.);
        }
      }
    }
  }

  TH3D* histo_data = (TH3D*)histo[0]->Clone("histo_data");

  TH3D* histo_mc_sum = (TH3D*)histo[0]->Clone("histo_mc_sum");
  histo_mc_sum->Reset();

  for (map<int, TH3D*>::iterator it = histo.begin(); it != histo.end(); it++) {
    int index = int(it->first);
    if (index > 0) {
      histo[0]->Add(histo[index], -1);
      histo_mc_sum->Add(histo[index]);
    }
  }

  for (int i = 0; i < histo[0]->GetNbinsX() + 2; i++) {
    for (int j = 0; j < histo[0]->GetNbinsY() + 2; j++) {
      for (int k = 0; k < histo[0]->GetNbinsZ() + 2; k++) {
        if (histo[0]->GetBinContent(i, j, k) < 0) {
          float Nb = histo[0]->GetBinContent(i, j, k);
          float eNb = TMath::Sqrt(TMath::Power(histo_data->GetBinError(i, j, k), 2) + TMath::Power(histo_mc_sum->GetBinError(i, j, k), 2));
          float eNb0 = eNb != 0. ? eNb * (TMath::ErfcInverse(0.157299 * TMath::Erfc(fabs(Nb / eNb))) - fabs(Nb / eNb)) : 0.;

          histo[0]->SetBinContent(i, j, k, 0.);
          histo[0]->SetBinError(i, j, k, eNb0);
        }
      }
    }
  }

  gStyle->SetOptStat(0);

  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("sherpa") != string::npos) version = version + ".sherpa";
  if (options.find("default") != string::npos) version = version + ".default";

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str(), kTRUE);
  }
  TFile* file = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + ".root").c_str());

  for (int eta = 1; eta < 5; eta++) {
    for (int pho0_pt = 2; pho0_pt < histo[0]->GetNbinsX()+1; pho0_pt++) {
      for (int pho1_pt = 2; pho1_pt < histo[0]->GetNbinsX()+1; pho1_pt++) {
        double e1 = 0;
        double e2 = 0;
        double f1 = 0;
        double f2 = 0;

        double e1_err = 0;
        double e2_err = 0;
        double f1_err = 0;
        double f2_err = 0;

        if (eta == 1) {
          e1 = histo[myindex]->GetBinContent(pho0_pt, 1, 1) / (histo[myindex]->GetBinContent(pho0_pt, 1, 1) + histo[myindex]->GetBinContent(pho0_pt, 1, 2));
          e2 = histo[myindex]->GetBinContent(pho1_pt, 1, 1) / (histo[myindex]->GetBinContent(pho1_pt, 1, 1) + histo[myindex]->GetBinContent(pho1_pt, 1, 2));
          f1 = histo[0]->GetBinContent(pho0_pt, 1, 1) / (histo[0]->GetBinContent(pho0_pt, 1, 1) + histo[0]->GetBinContent(pho0_pt, 1, 2));
          f2 = histo[0]->GetBinContent(pho1_pt, 1, 1) / (histo[0]->GetBinContent(pho1_pt, 1, 1) + histo[0]->GetBinContent(pho1_pt, 1, 2));

          e1_err = TMath::Power(1. / (histo[myindex]->GetBinContent(pho0_pt, 1, 1) + histo[myindex]->GetBinContent(pho0_pt, 1, 2)), 2) * TMath::Sqrt(TMath::Power(histo[myindex]->GetBinContent(pho0_pt, 1, 2) * histo[myindex]->GetBinError(pho0_pt, 1, 1), 2) + TMath::Power(histo[myindex]->GetBinContent(pho0_pt, 1, 1) * histo[myindex]->GetBinError(pho0_pt, 1, 2), 2));
          e2_err = TMath::Power(1. / (histo[myindex]->GetBinContent(pho1_pt, 1, 1) + histo[myindex]->GetBinContent(pho1_pt, 1, 2)), 2) * TMath::Sqrt(TMath::Power(histo[myindex]->GetBinContent(pho1_pt, 1, 2) * histo[myindex]->GetBinError(pho1_pt, 1, 1), 2) + TMath::Power(histo[myindex]->GetBinContent(pho1_pt, 1, 1) * histo[myindex]->GetBinError(pho1_pt, 1, 2), 2));
          f1_err = TMath::Power(1. / (histo[0]->GetBinContent(pho0_pt, 1, 1) + histo[0]->GetBinContent(pho0_pt, 1, 2)), 2) * TMath::Sqrt(TMath::Power(histo[0]->GetBinContent(pho0_pt, 1, 2) * histo[0]->GetBinError(pho0_pt, 1, 1), 2) + TMath::Power(histo[0]->GetBinContent(pho0_pt, 1, 1) * histo[0]->GetBinError(pho0_pt, 1, 2), 2));
          f2_err = TMath::Power(1. / (histo[0]->GetBinContent(pho1_pt, 1, 1) + histo[0]->GetBinContent(pho1_pt, 1, 2)), 2) * TMath::Sqrt(TMath::Power(histo[0]->GetBinContent(pho1_pt, 1, 2) * histo[0]->GetBinError(pho1_pt, 1, 1), 2) + TMath::Power(histo[0]->GetBinContent(pho1_pt, 1, 1) * histo[0]->GetBinError(pho1_pt, 1, 2), 2));
        }

        if (eta == 2) {
          e1 = histo[myindex]->GetBinContent(pho0_pt, 1, 1) / (histo[myindex]->GetBinContent(pho0_pt, 1, 1) + histo[myindex]->GetBinContent(pho0_pt, 1, 2));
          e2 = histo[myindex]->GetBinContent(pho1_pt, 2, 1) / (histo[myindex]->GetBinContent(pho1_pt, 2, 1) + histo[myindex]->GetBinContent(pho1_pt, 2, 2));
          f1 = histo[0]->GetBinContent(pho0_pt, 1, 1) / (histo[0]->GetBinContent(pho0_pt, 1, 1) + histo[0]->GetBinContent(pho0_pt, 1, 2));
          f2 = histo[0]->GetBinContent(pho1_pt, 2, 1) / (histo[0]->GetBinContent(pho1_pt, 2, 1) + histo[0]->GetBinContent(pho1_pt, 2, 2));

          e1_err = TMath::Power(1. / (histo[myindex]->GetBinContent(pho0_pt, 1, 1) + histo[myindex]->GetBinContent(pho0_pt, 1, 2)), 2) * TMath::Sqrt(TMath::Power(histo[myindex]->GetBinContent(pho0_pt, 1, 2) * histo[myindex]->GetBinError(pho0_pt, 1, 1), 2) + TMath::Power(histo[myindex]->GetBinContent(pho0_pt, 1, 1) * histo[myindex]->GetBinError(pho0_pt, 1, 2), 2));
          e2_err = TMath::Power(1. / (histo[myindex]->GetBinContent(pho1_pt, 2, 1) + histo[myindex]->GetBinContent(pho1_pt, 2, 2)), 2) * TMath::Sqrt(TMath::Power(histo[myindex]->GetBinContent(pho1_pt, 2, 2) * histo[myindex]->GetBinError(pho1_pt, 2, 1), 2) + TMath::Power(histo[myindex]->GetBinContent(pho1_pt, 2, 1) * histo[myindex]->GetBinError(pho1_pt, 2, 2), 2));
          f1_err = TMath::Power(1. / (histo[0]->GetBinContent(pho0_pt, 1, 1) + histo[0]->GetBinContent(pho0_pt, 1, 2)), 2) * TMath::Sqrt(TMath::Power(histo[0]->GetBinContent(pho0_pt, 1, 2) * histo[0]->GetBinError(pho0_pt, 1, 1), 2) + TMath::Power(histo[0]->GetBinContent(pho0_pt, 1, 1) * histo[0]->GetBinError(pho0_pt, 1, 2), 2));
          f2_err = TMath::Power(1. / (histo[0]->GetBinContent(pho1_pt, 2, 1) + histo[0]->GetBinContent(pho1_pt, 2, 2)), 2) * TMath::Sqrt(TMath::Power(histo[0]->GetBinContent(pho1_pt, 2, 2) * histo[0]->GetBinError(pho1_pt, 2, 1), 2) + TMath::Power(histo[0]->GetBinContent(pho1_pt, 2, 1) * histo[0]->GetBinError(pho1_pt, 2, 2), 2));
        }

        if (eta == 3) {
          e1 = histo[myindex]->GetBinContent(pho0_pt, 2, 1) / (histo[myindex]->GetBinContent(pho0_pt, 2, 1) + histo[myindex]->GetBinContent(pho0_pt, 2, 2));
          e2 = histo[myindex]->GetBinContent(pho1_pt, 1, 1) / (histo[myindex]->GetBinContent(pho1_pt, 1, 1) + histo[myindex]->GetBinContent(pho1_pt, 1, 2));
          f1 = histo[0]->GetBinContent(pho0_pt, 2, 1) / (histo[0]->GetBinContent(pho0_pt, 2, 1) + histo[0]->GetBinContent(pho0_pt, 2, 2));
          f2 = histo[0]->GetBinContent(pho1_pt, 1, 1) / (histo[0]->GetBinContent(pho1_pt, 1, 1) + histo[0]->GetBinContent(pho1_pt, 1, 2));

          e1_err = TMath::Power(1. / (histo[myindex]->GetBinContent(pho0_pt, 2, 1) + histo[myindex]->GetBinContent(pho0_pt, 2, 2)), 2) * TMath::Sqrt(TMath::Power(histo[myindex]->GetBinContent(pho0_pt, 2, 2) * histo[myindex]->GetBinError(pho0_pt, 2, 1), 2) + TMath::Power(histo[myindex]->GetBinContent(pho0_pt, 2, 1) * histo[myindex]->GetBinError(pho0_pt, 2, 2), 2));
          e2_err = TMath::Power(1. / (histo[myindex]->GetBinContent(pho1_pt, 1, 1) + histo[myindex]->GetBinContent(pho1_pt, 1, 2)), 2) * TMath::Sqrt(TMath::Power(histo[myindex]->GetBinContent(pho1_pt, 1, 2) * histo[myindex]->GetBinError(pho1_pt, 1, 1), 2) + TMath::Power(histo[myindex]->GetBinContent(pho1_pt, 1, 1) * histo[myindex]->GetBinError(pho1_pt, 1, 2), 2));
          f1_err = TMath::Power(1. / (histo[0]->GetBinContent(pho0_pt, 2, 1) + histo[0]->GetBinContent(pho0_pt, 2, 2)), 2) * TMath::Sqrt(TMath::Power(histo[0]->GetBinContent(pho0_pt, 2, 2) * histo[0]->GetBinError(pho0_pt, 2, 1), 2) + TMath::Power(histo[0]->GetBinContent(pho0_pt, 2, 1) * histo[0]->GetBinError(pho0_pt, 2, 2), 2));
          f2_err = TMath::Power(1. / (histo[0]->GetBinContent(pho1_pt, 1, 1) + histo[0]->GetBinContent(pho1_pt, 1, 2)), 2) * TMath::Sqrt(TMath::Power(histo[0]->GetBinContent(pho1_pt, 1, 2) * histo[0]->GetBinError(pho1_pt, 1, 1), 2) + TMath::Power(histo[0]->GetBinContent(pho1_pt, 1, 1) * histo[0]->GetBinError(pho1_pt, 1, 2), 2));
        }

        if (eta == 4) {
          e1 = histo[myindex]->GetBinContent(pho0_pt, 2, 1) / (histo[myindex]->GetBinContent(pho0_pt, 2, 1) + histo[myindex]->GetBinContent(pho0_pt, 2, 2));
          e2 = histo[myindex]->GetBinContent(pho1_pt, 2, 1) / (histo[myindex]->GetBinContent(pho1_pt, 2, 1) + histo[myindex]->GetBinContent(pho1_pt, 2, 2));
          f1 = histo[0]->GetBinContent(pho0_pt, 2, 1) / (histo[0]->GetBinContent(pho0_pt, 2, 1) + histo[0]->GetBinContent(pho0_pt, 2, 2));
          f2 = histo[0]->GetBinContent(pho1_pt, 2, 1) / (histo[0]->GetBinContent(pho1_pt, 2, 1) + histo[0]->GetBinContent(pho1_pt, 2, 2));

          e1_err = TMath::Power(1. / (histo[myindex]->GetBinContent(pho0_pt, 2, 1) + histo[myindex]->GetBinContent(pho0_pt, 2, 2)), 2) * TMath::Sqrt(TMath::Power(histo[myindex]->GetBinContent(pho0_pt, 2, 2) * histo[myindex]->GetBinError(pho0_pt, 2, 1), 2) + TMath::Power(histo[myindex]->GetBinContent(pho0_pt, 2, 1) * histo[myindex]->GetBinError(pho0_pt, 2, 2), 2));
          e2_err = TMath::Power(1. / (histo[myindex]->GetBinContent(pho1_pt, 2, 1) + histo[myindex]->GetBinContent(pho1_pt, 2, 2)), 2) * TMath::Sqrt(TMath::Power(histo[myindex]->GetBinContent(pho1_pt, 2, 2) * histo[myindex]->GetBinError(pho1_pt, 2, 1), 2) + TMath::Power(histo[myindex]->GetBinContent(pho1_pt, 2, 1) * histo[myindex]->GetBinError(pho1_pt, 2, 2), 2));
          f1_err = TMath::Power(1. / (histo[0]->GetBinContent(pho0_pt, 2, 1) + histo[0]->GetBinContent(pho0_pt, 2, 2)), 2) * TMath::Sqrt(TMath::Power(histo[0]->GetBinContent(pho0_pt, 2, 2) * histo[0]->GetBinError(pho0_pt, 2, 1), 2) + TMath::Power(histo[0]->GetBinContent(pho0_pt, 2, 1) * histo[0]->GetBinError(pho0_pt, 2, 2), 2));
          f2_err = TMath::Power(1. / (histo[0]->GetBinContent(pho1_pt, 2, 1) + histo[0]->GetBinContent(pho1_pt, 2, 2)), 2) * TMath::Sqrt(TMath::Power(histo[0]->GetBinContent(pho1_pt, 2, 2) * histo[0]->GetBinError(pho1_pt, 2, 1), 2) + TMath::Power(histo[0]->GetBinContent(pho1_pt, 2, 1) * histo[0]->GetBinError(pho1_pt, 2, 2), 2));
        }

        for (int i=0; i < 9; i++) {
          string matrix_title = "matrix_";
          matrix_title += std::to_string(pho0_pt);
          matrix_title += std::to_string(pho1_pt);
          matrix_title += std::to_string(eta);

          if (i == 1) matrix_title += "_e1up";
          if (i == 2) matrix_title += "_e2up";
          if (i == 3) matrix_title += "_f1up";
          if (i == 4) matrix_title += "_f2up";
          if (i == 5) matrix_title += "_e1down";
          if (i == 6) matrix_title += "_e2down";
          if (i == 7) matrix_title += "_f1down";
          if (i == 8) matrix_title += "_f2down";

          TMatrixD matrix(4,4);

          matrix(0, 0) = (e1 + e1_err * ((i == 1) - (i == 5))) * (e2 + e2_err * ((i == 2) - (i == 6)));
          matrix(0, 1) = (e1 + e1_err * ((i == 1) - (i == 5))) * (f2 + f2_err * ((i == 4) - (i == 8)));
          matrix(0, 2) = (f1 + f1_err * ((i == 3) - (i == 7))) * (e2 + e2_err * ((i == 2) - (i == 6)));
          matrix(0, 3) = (f1 + f1_err * ((i == 3) - (i == 7))) * (f2 + f2_err * ((i == 4) - (i == 8)));

          matrix(1, 0) = (e1 + e1_err * ((i == 1) - (i == 5))) * (1. - (e2 + e2_err * ((i == 2) - (i == 6))));
          matrix(1, 1) = (e1 + e1_err * ((i == 1) - (i == 5))) * (1. - (f2 + f2_err * ((i == 4) - (i == 8))));
          matrix(1, 2) = (f1 + f1_err * ((i == 3) - (i == 7))) * (1. - (e2 + e2_err * ((i == 2) - (i == 6))));
          matrix(1, 3) = (f1 + f1_err * ((i == 3) - (i == 7))) * (1. - (f2 + f2_err * ((i == 4) - (i == 8))));

          matrix(2, 0) = (1. - (e1 + e1_err * ((i == 1) - (i == 5)))) * (e2 + e2_err * ((i == 2) - (i == 6)));
          matrix(2, 1) = (1. - (e1 + e1_err * ((i == 1) - (i == 5)))) * (f2 + f2_err * ((i == 4) - (i == 8)));
          matrix(2, 2) = (1. - (f1 + f1_err * ((i == 3) - (i == 7)))) * (e2 + e2_err * ((i == 2) - (i == 6)));
          matrix(2, 3) = (1. - (f1 + f1_err * ((i == 3) - (i == 7)))) * (f2 + f2_err * ((i == 4) - (i == 8)));

          matrix(3, 0) = (1. - (e1 + e1_err * ((i == 1) - (i == 5)))) * (1. - (e2 + e2_err * ((i == 2) - (i == 6))));
          matrix(3, 1) = (1. - (e1 + e1_err * ((i == 1) - (i == 5)))) * (1. - (f2 + f2_err * ((i == 4) - (i == 8))));
          matrix(3, 2) = (1. - (f1 + f1_err * ((i == 3) - (i == 7)))) * (1. - (e2 + e2_err * ((i == 2) - (i == 6))));
          matrix(3, 3) = (1. - (f1 + f1_err * ((i == 3) - (i == 7)))) * (1. - (f2 + f2_err * ((i == 4) - (i == 8))));

          matrix.Write((matrix_title).c_str());
        }
      }
    }
  }

  file->Close();
  delete file;

  histo1[8001] = (TH1D*)histo1[0]->Clone();
  histo1[8001]->Reset();

  for (int eta = 1; eta < 3; eta++) {
    for (int pho0_pt = 2; pho0_pt < histo_data->GetNbinsX() + 1; pho0_pt++) {

      TVectorD n_region(2);
      n_region[0] = histo_data->GetBinContent(pho0_pt, eta, 1);
      n_region[1] = histo_data->GetBinContent(pho0_pt, eta, 2);

      TMatrixD matrix(2,2);
      TMatrixD inverse_matrix(2,2);

      double e1 = 0;
      double f1 = 0;

      e1 = histo[myindex]->GetBinContent(pho0_pt, eta, 1) / (histo[myindex]->GetBinContent(pho0_pt, eta, 1) + histo[myindex]->GetBinContent(pho0_pt, eta, 2));
      f1 = histo[0]->GetBinContent(pho0_pt, eta, 1) / (histo[0]->GetBinContent(pho0_pt, eta, 1) + histo[0]->GetBinContent(pho0_pt, eta, 2));

      matrix(0, 0) = e1;
      matrix(1, 0) = 1. - e1;
      matrix(0, 1) = f1;
      matrix(1, 1) = 1. - f1;

      inverse_matrix = matrix;

      double det = -1;
      inverse_matrix.Invert(&det);

      TVectorD alpha(2);
      alpha = inverse_matrix * n_region;

      if (alpha(0) < 0) alpha(0) = 0.;
      if (alpha(1) < 0) alpha(1) = 0.;

      histo1[8001]->SetBinContent(pho0_pt, histo1[8001]->GetBinContent(pho0_pt) + matrix(0,1) * alpha(1));

    }
  }

  THStack* hstack_mc = new THStack("hstack_mc", "hstack_mc");
  TH1D* h_mc_sum = (TH1D*)histo1[0]->Clone("h_mc_sum");
  h_mc_sum->Reset();

  for (map<int, TH1D*>::reverse_iterator it = histo1.rbegin(); it != histo1.rend(); it++) {
    int index = int(it->first);
    if (index > 0) {
      hstack_mc->Add(histo1[index]);
      h_mc_sum->Add(histo1[index]);
    }
  }

  TH1D* h_ratio_mc = (TH1D*)h_mc_sum->Clone("h_ratio_mc");
  for (int i = 0; i < h_mc_sum->GetNbinsX()+2; i++) {
    h_mc_sum->SetBinError(i, 0.0);
  }
  h_ratio_mc->Divide(h_mc_sum);

  TH1D* h_ratio = (TH1D*)histo1[0]->Clone("h_ratio");
  h_ratio->Divide(h_mc_sum);

  TLegend* leg = new TLegend(0.65, 0.48, 0.91, 0.88);
  leg->SetBorderSize(0);
  leg->SetEntrySeparation(0.01);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);

  for (map<int, TH1D*>::iterator it = histo1.begin(); it != histo1.end(); it++) {
    int index = int(it->first);

    if (index == 0) {
      leg->AddEntry(histo1[index], "Data", "p");
    }

    if (index == 10) {
      histo1[index]->SetFillColor(kOrange+7);
      histo1[index]->SetFillStyle(3254);
      leg->AddEntry(histo1[index], "Z #gamma #gamma", "f");
    }
    if (index == 11) {
      histo1[index]->SetFillColor(kOrange-4);
      histo1[index]->SetFillStyle(3254);
      leg->AddEntry(histo1[index], "Z #gamma", "f");
    }
    if (index == 21) {
      histo1[index]->SetFillColor(kOrange-5);
      leg->AddEntry(histo1[index], "W #gamma", "f");
    }
    if (index == 22) {
      histo1[index]->SetFillColor(kOrange-6);
      leg->AddEntry(histo1[index], "W #gamma #gamma", "f");
    }
    if (index == 31) {
      histo1[index]->SetFillColor(kGreen+3);
      leg->AddEntry(histo1[index], "Diboson #gamma", "f");
    }
    if (index == 41) {
      histo1[index]->SetFillColor(kBlue+2);
      leg->AddEntry(histo1[index], "TT #gamma", "f");
    }
    if (index == 42) {
      histo1[index]->SetFillColor(kBlue+3);
      leg->AddEntry(histo1[index], "TT #gamma #gamma", "f");
    }
    if (index == 51) {
      histo1[index]->SetFillColor(kOrange+7);
      leg->AddEntry(histo1[index], "SingleTop #gamma", "f");
    }

    if (index == 1010) {
      histo1[index]->SetFillColor(kOrange+7);
      histo1[index]->SetFillStyle(3254);
      leg->AddEntry(histo1[index], "W #gamma #gamma", "f");
    }
    if (index == 1011) {
      histo1[index]->SetFillColor(kOrange-4);
      histo1[index]->SetFillStyle(3254);
      leg->AddEntry(histo1[index], "W #gamma", "f");
    }
    if (index == 1021) {
      histo1[index]->SetFillColor(kOrange-5);
      leg->AddEntry(histo1[index], "Z #gamma", "f");
    }
    if (index == 1022) {
      histo1[index]->SetFillColor(kOrange-6);
      leg->AddEntry(histo1[index], "Z #gamma #gamma", "f");
    }
    if (index == 1031) {
      histo1[index]->SetFillColor(kBlue+2);
      leg->AddEntry(histo1[index], "TT #gamma", "f");
    }
    if (index == 1032) {
      histo1[index]->SetFillColor(kBlue+3);
      leg->AddEntry(histo1[index], "TT #gamma #gamma", "f");
    }
    if (index == 1041) {
      histo1[index]->SetFillColor(kOrange+7);
      leg->AddEntry(histo1[index], "SingleTop #gamma", "f");
    }
    if (index == 1051) {
      histo1[index]->SetFillColor(kGreen+3);
      leg->AddEntry(histo1[index], "Diboson #gamma", "f");
    }

    if (index == 8001) {
      histo1[index]->SetFillColor(kPink+4);
      leg->AddEntry(histo1[index], "Jet MisID", "f");
    }
  }

  TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
  c1->cd();

  TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
  pad1->SetBottomMargin(0.001);
  pad1->Draw();
  pad1->cd();

  hstack_mc->SetMaximum(1.2*TMath::Max(hstack_mc->GetMaximum(), histo1[0]->GetMaximum()));
  if (options.find("nolog") == string::npos) hstack_mc->SetMinimum(0.0001*hstack_mc->GetMaximum());
  hstack_mc->SetMinimum(1.);

  hstack_mc->Draw("HIST");

  hstack_mc->SetTitle("");
  histo1[0]->SetStats(kFALSE);

  hstack_mc->GetXaxis()->SetTitleOffset(0.7);
  hstack_mc->GetXaxis()->SetLabelFont(42);
  hstack_mc->GetXaxis()->SetLabelSize(0.08);

  hstack_mc->GetYaxis()->SetTitle("Events");
  hstack_mc->GetYaxis()->SetTitleSize(0.05);
  hstack_mc->GetYaxis()->SetTitleOffset(0.8);
  hstack_mc->GetYaxis()->SetLabelSize(0.045);

  histo1[0]->SetMarkerColor(kBlack);
  histo1[0]->SetMarkerStyle(20);
  histo1[0]->SetMarkerSize(1.0);

  histo1[0]->Draw("EXP0SAMES");

  leg->Draw();

  if (options.find("nolog") == string::npos) {
    if (h_mc_sum->GetMaximum() != 0) pad1->SetLogy();
  }

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

  string tmp_title = title;

  if (tmp_title == "h_WG_ele_pho0_pt" || tmp_title == "h_WG_muo_pho0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_pt" || tmp_title == "h_ZG_muo_pho0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_eta" || tmp_title == "h_WGG_muo_pho1_eta") {
    h_ratio->GetXaxis()->SetTitle("#eta^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_phi" || tmp_title == "h_WGG_muo_pho1_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_r9" || tmp_title == "h_WGG_muo_pho1_r9") {
    h_ratio->GetXaxis()->SetTitle("R_{9}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_sieie" || tmp_title == "h_WGG_muo_pho0_sieie") {
    h_ratio->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_sieie" || tmp_title == "h_WGG_muo_pho1_sieie") {
    h_ratio->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_jet0_dR" || tmp_title == "h_WGG_muo_pho1_jet0_dR") {
    h_ratio->GetXaxis()->SetTitle("#DeltaR^{j#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_mva" || tmp_title == "h_WGG_muo_pho0_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_mva" || tmp_title == "h_WGG_muo_pho1_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_pf_iso_all" || tmp_title == "h_WGG_muo_pf_iso_all") {
    h_ratio->GetXaxis()->SetTitle("Iso_{all}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_pf_iso_chg" || tmp_title == "h_WGG_muo_pf_iso_chg") {
    h_ratio->GetXaxis()->SetTitle("Iso_{chg}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_dR" || tmp_title == "h_WGG_muo_pho1_dR") {
    h_ratio->GetXaxis()->SetTitle("#DeltaR^{l#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_pt" || tmp_title == "h_WGG_muo_pho0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_pt" || tmp_title == "h_WGG_muo_pho1_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pt" || tmp_title == "h_WGG_muo_muo0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1_dR" || tmp_title == "h_WGG_muo_pho0_pho1_dR") {
    h_ratio->GetXaxis()->SetTitle("#DeltaR^{#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_eta" || tmp_title == "h_ZGG_muo_pho1_eta") {
    h_ratio->GetXaxis()->SetTitle("#eta^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_phi" || tmp_title == "h_ZGG_muo_pho1_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_r9" || tmp_title == "h_ZGG_muo_pho1_r9") {
    h_ratio->GetXaxis()->SetTitle("R_{9}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_sieie" || tmp_title == "h_ZGG_muo_pho0_sieie") {
    h_ratio->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_sieie" || tmp_title == "h_ZGG_muo_pho1_sieie") {
    h_ratio->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_jet0_dR" || tmp_title == "h_ZGG_muo_pho1_jet0_dR") {
    h_ratio->GetXaxis()->SetTitle("#DeltaR^{j#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_mva" || tmp_title == "h_ZGG_muo_pho0_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_mva" || tmp_title == "h_ZGG_muo_pho1_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_pf_iso_all" || tmp_title == "h_ZGG_muo_pf_iso_all") {
    h_ratio->GetXaxis()->SetTitle("Iso_{all}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_pf_iso_chg" || tmp_title == "h_ZGG_muo_pf_iso_chg") {
    h_ratio->GetXaxis()->SetTitle("Iso_{chg}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_dR" || tmp_title == "h_ZGG_muo_pho1_dR") {
    h_ratio->GetXaxis()->SetTitle("#DeltaR^{l#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pt" || tmp_title == "h_ZGG_muo_pho0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_pt" || tmp_title == "h_ZGG_muo_pho1_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_pt" || tmp_title == "h_ZGG_muo_muo0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_ZGG_ele_ele1_pt" || tmp_title == "h_ZGG_muo_muo1_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1_dR" || tmp_title == "h_ZGG_muo_pho0_pho1_dR") {
    h_ratio->GetXaxis()->SetTitle("#DeltaR^{#gamma#gamma}");
  } else if (tmp_title == "h_WGG_ele" || tmp_title == "h_WGG_muo") {
    h_ratio->GetXaxis()->SetTitle("M_{T} [GeV]");
  } else if (tmp_title == "h_ZGG_ele" || tmp_title == "h_ZGG_muo") {
    h_ratio->GetXaxis()->SetTitle("M_{ll} [GeV]");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1_pt" || tmp_title == "h_WGG_muo_pho0_pho1_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1" || tmp_title == "h_WGG_muo_pho0_pho1") {
    h_ratio->GetXaxis()->SetTitle("M^{#gamma#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pho0" || tmp_title == "h_WGG_muo_muo0_pho0") {
    h_ratio->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pho1" || tmp_title == "h_WGG_muo_muo0_pho1") {
    h_ratio->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pho0_pho1" || tmp_title == "h_WGG_muo_muo0_pho0_pho1") {
    h_ratio->GetXaxis()->SetTitle("M^{l#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1_pt" || tmp_title == "h_ZGG_muo_pho0_pho1_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1" || tmp_title == "h_ZGG_muo_pho0_pho1") {
    h_ratio->GetXaxis()->SetTitle("M^{#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_pho1" || tmp_title == "h_ZGG_muo_muo0_pho1") {
    h_ratio->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele1_pho1" || tmp_title == "h_ZGG_muo_muo1_pho1") {
    h_ratio->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_pho0_pho1" || tmp_title == "h_ZGG_muo_muo0_pho0_pho1") {
    h_ratio->GetXaxis()->SetTitle("M^{l#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele1_pho0_pho1" || tmp_title == "h_ZGG_muo_muo1_pho0_pho1") {
    h_ratio->GetXaxis()->SetTitle("M^{l#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_ele1_pho0_pho1" || tmp_title == "h_ZGG_muo_muo0_muo1_pho0_pho1") {
    h_ratio->GetXaxis()->SetTitle("M^{ll#gamma#gamma}");
  } else {
    tmp_title.erase(0, 2);
    h_ratio->GetXaxis()->SetTitle(tmp_title.c_str());
  }

  h_ratio->GetXaxis()->SetTitleFont(42);
  h_ratio->GetXaxis()->SetTitleSize(0.11);
  h_ratio->GetXaxis()->SetTitleOffset(1.1);
  h_ratio->GetXaxis()->SetLabelFont(42);
  h_ratio->GetXaxis()->SetLabelSize(0.10);

  h_ratio->GetYaxis()->SetTitle("Data/MC");
  h_ratio->GetYaxis()->SetTitleSize(0.11);
  h_ratio->GetYaxis()->SetTitleOffset(0.36);
  h_ratio->GetYaxis()->SetLabelSize(0.1);
  h_ratio->GetYaxis()->SetLabelOffset(0.01);
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetRangeUser(0.5, 1.5);

  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw("E0PX0");

  h_ratio_mc->SetFillColor(kGray);
  h_ratio_mc->Draw("E2SAME");

  TLine* line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1.0, h_ratio->GetXaxis()->GetXmax(), 1.0);
  line->SetLineColor(kRed);
  line->SetLineWidth(2);
  line->Draw();

  h_ratio->Draw("E0PX0SAME");

  writeExtraText = true;

  lumi_13TeV  = Form("%.1f fb^{-1}", lumi);
  int iPeriod = 4;
  int iPos = 0;
  CMS_lumi(pad1, iPeriod, iPos);
  c1->cd();

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".matrix/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".matrix/").c_str(), kTRUE);
  }
  c1->SaveAs(("html/" + version + "/" + flag + "/" + year + ".matrix/" + title + ".pdf").c_str());

}

int main(int argc, char *argv[]) {

#pragma unused (argc)

cout << "Processing plot3.C(\"" << argv[1] << "\",\""
                                << argv[2] << "\",\""
                                << argv[3] << "\",\""
                                << argv[4] << "\",\""
                                << argv[5] << "\")..." << endl;

plot3(argv[1], argv[2], argv[3], argv[4], argv[5]);

}
