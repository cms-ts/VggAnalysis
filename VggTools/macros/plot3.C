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
  if (options.find("default") != string::npos) plot = "default/" + plot;

// #define USE_CATEGORIES
#define USE_MATRIX

#if defined(USE_CATEGORIES)
  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("default") != string::npos) version = version + ".default";

  TFile* file_iso = new TFile(("html/" + version + "/" + flag + "/" + year + "/root/" + title + ".root").c_str());
  TH1D* h_iso_data = (TH1D*)file_iso->Get("h_data_cat");
  TH1D* h_iso_mc = (TH1D*)file_iso->Get("h_mc_cat");

  h_iso_data->SetDirectory(0);
  h_iso_mc->SetDirectory(0);
  file_iso->Close();
  delete file_iso;

  TFile* file_noiso = new TFile(("html/" + version + "/" + flag + "/" + year + "/root/" + title + "_noiso.root").c_str());
  TH1D* h_noiso_data = (TH1D*)file_noiso->Get("h_data_cat");
  TH1D* h_noiso_mc = (TH1D*)file_noiso->Get("h_mc_cat");

  h_noiso_data->SetDirectory(0);
  h_noiso_mc->SetDirectory(0);
  file_noiso->Close();
  delete file_noiso;

  for (int i = 0; i < h_iso_data->GetNbinsX()+2; i++) {
    if (h_iso_data->GetBinContent(i) <= 0) {
      h_iso_data->SetBinContent(i, 0);
      h_iso_data->SetBinError(i, 0);
    }
    if (h_noiso_data->GetBinContent(i) <= 0) {
      h_noiso_data->SetBinContent(i, 0);
      h_noiso_data->SetBinError(i, 0);
    }
  }

  for (int i = 0; i < h_iso_mc->GetNbinsX()+2; i++) {
    if (h_iso_mc->GetBinContent(i) <= 0) {
      h_iso_mc->SetBinContent(i, 0);
      h_iso_mc->SetBinError(i, 0);
    }
    if (h_noiso_mc->GetBinContent(i) <= 0) {
      h_noiso_mc->SetBinContent(i, 0);
      h_noiso_mc->SetBinError(i, 0);
    }
  }

  TH1D* h_sum_data = (TH1D*)h_iso_data->Clone("h_sum_data");
  h_sum_data->Add(h_noiso_data);

  TH1D* h_sum_mc = (TH1D*)h_iso_mc->Clone("h_sum_mc");
  h_sum_mc->Add(h_noiso_mc);

  TH1D* h_weight_data = (TH1D*)h_iso_data->Clone("h_weight_data");
  h_weight_data->Divide(h_weight_data, h_sum_data, 1., 1., "B");

  TH1D* h_weight_mc = (TH1D*)h_iso_mc->Clone("h_weight_mc");
  h_weight_mc->Divide(h_weight_mc, h_sum_mc, 1., 1., "B");

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str(), kTRUE);
  }
  TFile* file = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + "_matrix_weight.root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + "_matrix_weight.root").c_str());

  h_weight_data->Write("h_weight_data");
  h_weight_mc->Write("h_weight_mc");

  file->Close();
  delete file;
#endif // defined(USE_CATEGORIES)

#if defined(USE_MATRIX)
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
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_syst" || flag == "jet_misid_cat1" || flag == "jet_misid_cat2" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit") {
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
    if (index == 10 || index == 11 || index == 21 || index == 22 || index == 31 || index == 41 || index == 42 || index == 1010 || index == 1011 || index == 1020 || index == 1021 || index == 1022 || index == 1031 || index == 1032 || index == 1051) {
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_syst" || flag == "jet_misid_cat1" || flag == "jet_misid_cat2" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit") {
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
        double ngen = ((TH3D*)gDirectory->Get("h_nevt"))->GetBinContent(2);
        norm = xsecMap[it->first] * 1000. * lumi / ngen;
        if (it->first.find("RunIISummer16") != string::npos) norm = norm * lumi2016 / lumi;
        if (it->first.find("RunIIFall17") != string::npos) norm = norm * lumi2017 / lumi;
        if (it->first.find("RunIIAutumn18") != string::npos) norm = norm * lumi2018 / lumi;
      } else {
        cout << "ERROR: cross section for " << it->first << " is ZERO !!" << endl;
        return;
      }
      if (histo[index]) {
        TH3D* h = (TH3D*)gDirectory->Get(string(title).erase(title.find("pho0_pt"), 6).c_str());
        if (h) {
          histo[index]->Add(h, norm);
        }
      } else {
        TH3D* h = (TH3D*)gDirectory->Get(string(title).erase(title.find("pho0_pt"), 6).c_str());
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
    if (index == 10 || index == 11 || index == 21 || index == 22 || index == 31 || index == 41 || index == 42 || index == 1010 || index == 1011 || index == 1020 || index == 1021 || index == 1022 || index == 1031 || index == 1032 || index == 1051) {
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_syst" || flag == "jet_misid_cat1" || flag == "jet_misid_cat2" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit") {
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
        double ngen = ((TH3D*)gDirectory->Get("h_nevt"))->GetBinContent(2);
        norm = xsecMap[it->first] * 1000. * lumi / ngen;
        if (it->first.find("RunIISummer16") != string::npos) norm = norm * lumi2016 / lumi;
        if (it->first.find("RunIIFall17") != string::npos) norm = norm * lumi2017 / lumi;
        if (it->first.find("RunIIAutumn18") != string::npos) norm = norm * lumi2018 / lumi;
      } else {
        cout << "ERROR: cross section for " << it->first << " is ZERO !!" << endl;
        return;
      }
      if (histo1[index]) {
        TH1D* h1 = (TH1D*)gDirectory->Get(title.c_str());
        if (index == 1020) h1 = (TH1D*)gDirectory->Get((title + "_genmatch2").c_str());
        if (h1) {
          histo1[index]->Add(h1, norm);
        }
      } else {
        TH1D* h1 = (TH1D*)gDirectory->Get(title.c_str());
        if (index == 1020) h1 = (TH1D*)gDirectory->Get((title + "_genmatch2").c_str());
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

  for (int i = 0; i < histo[myindex]->GetNbinsX() + 1; i++) {
    for (int j = 0; j < histo[myindex]->GetNbinsY() + 1; j++) {
      for (int k = 0; k < histo[myindex]->GetNbinsZ() + 1; k++) {
        if (histo[myindex]->GetBinContent(i, j, k) < 0) {
          histo[myindex]->SetBinContent(i, j, k, 0.);
          histo[myindex]->SetBinError(i, j, k, 0.);
        }
      }
    }
  }

  TH3D* histo_data = (TH3D*)histo[0]->Clone("histo_data");

  if (title.find("h_WG") != string::npos) {
    histo[0]->Add(histo[1010], -1);
    histo[0]->Add(histo[1011], -1);
    histo[0]->Add(histo[1020], -1);
    histo[0]->Add(histo[1021], -1);
    histo[0]->Add(histo[1022], -1);
    histo[0]->Add(histo[1031], -1);
    histo[0]->Add(histo[1032], -1);
    histo[0]->Add(histo[1051], -1);
  }

  if (title.find("h_ZG") != string::npos) {
    histo[0]->Add(histo[10], -1);
    histo[0]->Add(histo[11], -1);
    histo[0]->Add(histo[21], -1);
    histo[0]->Add(histo[22], -1);
    histo[0]->Add(histo[31], -1);
    histo[0]->Add(histo[41], -1);
    histo[0]->Add(histo[42], -1);
  }

  for (int i = 0; i < histo[0]->GetNbinsX() + 1; i++) {
    for (int j = 0; j < histo[0]->GetNbinsY() + 1; j++) {
      for (int k = 0; k < histo[0]->GetNbinsZ() + 1; k++) {
        if (histo[0]->GetBinContent(i, j, k) < 0) {
          histo[0]->SetBinContent(i, j, k, 0.);
          histo[0]->SetBinError(i, j, k, 0.);
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
  if (options.find("default") != string::npos) version = version + ".default";

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str(), kTRUE);
  }
  TFile* file = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + "_matrix_weight.root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + "_matrix_weight.root").c_str());

  for (int eta = 1; eta < 5; eta++) {
    for (int pho0_pt = 2; pho0_pt < histo[0]->GetNbinsX() + 1; pho0_pt++) {
      for (int pho1_pt = 2; pho1_pt < histo[0]->GetNbinsX() + 1; pho1_pt++) {
        double e1 = 0;
        double e2 = 0;
        double f1 = 0;
        double f2 = 0;

        if (eta == 1) {
          e1 = histo[myindex]->GetBinContent(pho0_pt, 1, 1) / (histo[myindex]->GetBinContent(pho0_pt, 1, 1) + histo[myindex]->GetBinContent(pho0_pt, 1, 2));
          e2 = histo[myindex]->GetBinContent(pho1_pt, 1, 1) / (histo[myindex]->GetBinContent(pho1_pt, 1, 1) + histo[myindex]->GetBinContent(pho1_pt, 1, 2));
          f1 = histo[0]->GetBinContent(pho0_pt, 1, 1) / (histo[0]->GetBinContent(pho0_pt, 1, 1) + histo[0]->GetBinContent(pho0_pt, 1, 2));
          f2 = histo[0]->GetBinContent(pho1_pt, 1, 1) / (histo[0]->GetBinContent(pho1_pt, 1, 1) + histo[0]->GetBinContent(pho1_pt, 1, 2));
        }
        if (eta == 2) {
          e1 = histo[myindex]->GetBinContent(pho0_pt, 1, 1) / (histo[myindex]->GetBinContent(pho0_pt, 1, 1) + histo[myindex]->GetBinContent(pho0_pt, 1, 2));
          e2 = histo[myindex]->GetBinContent(pho1_pt, 2, 1) / (histo[myindex]->GetBinContent(pho1_pt, 2, 1) + histo[myindex]->GetBinContent(pho1_pt, 2, 2));
          f1 = histo[0]->GetBinContent(pho0_pt, 1, 1) / (histo[0]->GetBinContent(pho0_pt, 1, 1) + histo[0]->GetBinContent(pho0_pt, 1, 2));
          f2 = histo[0]->GetBinContent(pho1_pt, 2, 1) / (histo[0]->GetBinContent(pho1_pt, 2, 1) + histo[0]->GetBinContent(pho1_pt, 2, 2));
        }
        if (eta == 3) {
          e1 = histo[myindex]->GetBinContent(pho0_pt, 2, 1) / (histo[myindex]->GetBinContent(pho0_pt, 2, 1) + histo[myindex]->GetBinContent(pho0_pt, 2, 2));
          e2 = histo[myindex]->GetBinContent(pho1_pt, 1, 1) / (histo[myindex]->GetBinContent(pho1_pt, 1, 1) + histo[myindex]->GetBinContent(pho1_pt, 1, 2));
          f1 = histo[0]->GetBinContent(pho0_pt, 2, 1) / (histo[0]->GetBinContent(pho0_pt, 2, 1) + histo[0]->GetBinContent(pho0_pt, 2, 2));
          f2 = histo[0]->GetBinContent(pho1_pt, 1, 1) / (histo[0]->GetBinContent(pho1_pt, 1, 1) + histo[0]->GetBinContent(pho1_pt, 1, 2));
        }
        if (eta == 4) {
          e1 = histo[myindex]->GetBinContent(pho0_pt, 2, 1) / (histo[myindex]->GetBinContent(pho0_pt, 2, 1) + histo[myindex]->GetBinContent(pho0_pt, 2, 2));
          e2 = histo[myindex]->GetBinContent(pho1_pt, 2, 1) / (histo[myindex]->GetBinContent(pho1_pt, 2, 1) + histo[myindex]->GetBinContent(pho1_pt, 2, 2));
          f1 = histo[0]->GetBinContent(pho0_pt, 2, 1) / (histo[0]->GetBinContent(pho0_pt, 2, 1) + histo[0]->GetBinContent(pho0_pt, 2, 2));
          f2 = histo[0]->GetBinContent(pho1_pt, 2, 1) / (histo[0]->GetBinContent(pho1_pt, 2, 1) + histo[0]->GetBinContent(pho1_pt, 2, 2));
        }

        string matrix_title = "h_matrix_";
        matrix_title += std::to_string(pho0_pt);
        matrix_title += std::to_string(pho1_pt);
        matrix_title += std::to_string(eta);

        TH2D* matrix = new TH2D("matrix", "matrix", 4, -0.5, 3.5, 4, -0.5, 3.5);

        matrix->SetBinContent(1, 1, e1 * e2);
        matrix->SetBinContent(1, 2, e1 * f2);
        matrix->SetBinContent(1, 3, f1 * e2);
        matrix->SetBinContent(1, 4, f1 * f2);

        matrix->SetBinContent(2, 1, e1 * (1.-e2));
        matrix->SetBinContent(2, 2, e1 * (1.-f2));
        matrix->SetBinContent(2, 3, f1 * (1.-e2));
        matrix->SetBinContent(2, 4, f1 * (1.-f2));

        matrix->SetBinContent(3, 1, (1.-e1) * e2);
        matrix->SetBinContent(3, 2, (1.-e1) * f2);
        matrix->SetBinContent(3, 3, (1.-f1) * e2);
        matrix->SetBinContent(3, 4, (1.-f1) * f2);

        matrix->SetBinContent(4, 1, (1.-e1) * (1.-e2));
        matrix->SetBinContent(4, 2, (1.-e1) * (1.-f2));
        matrix->SetBinContent(4, 3, (1.-f1) * (1.-e2));
        matrix->SetBinContent(4, 4, (1.-f1) * (1.-f2));

        matrix->Write((matrix_title).c_str());

        delete matrix;
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

  bool flowbins = true;

  for (map<int, TH1D*>::reverse_iterator it = histo1.rbegin(); it != histo1.rend(); it++) {
    int index = int(it->first);
    if (flowbins) {
      histo1[index]->SetBinContent(1, histo1[index]->GetBinContent(1) + histo1[index]->GetBinContent(0));
      histo1[index]->SetBinContent(histo1[index]->GetNbinsX(), histo1[index]->GetBinContent(histo1[index]->GetNbinsX()) + histo1[index]->GetBinContent(histo1[index]->GetNbinsX()+1));
      histo1[index]->SetBinError(1, TMath::Sqrt(TMath::Power(histo1[index]->GetBinError(1), 2) + TMath::Power(histo1[index]->GetBinError(0), 2)));
      histo1[index]->SetBinError(histo1[index]->GetNbinsX(), TMath::Sqrt(TMath::Power(histo1[index]->GetBinError(histo1[index]->GetNbinsX()), 2) + TMath::Power(histo1[index]->GetBinError(histo1[index]->GetNbinsX()+1), 2)));
      histo1[index]->SetBinContent(0, 0.);
      histo1[index]->SetBinContent(histo1[index]->GetNbinsX()+1, 0.);
      histo1[index]->SetBinError(0, 0.);
      histo1[index]->SetBinError(histo1[index]->GetNbinsX()+1, 0.);
    }
    if (index > 0) {
      hstack_mc->Add(histo1[index]);
      h_mc_sum->Add(histo1[index]);
    }
  }

  TH1D* h_ratio = (TH1D*)histo1[0]->Clone("h_ratio");
  h_ratio->Divide(h_mc_sum);

  TLegend* leg = new TLegend(0.65, 0.640, 0.91, 0.88);
  leg->SetBorderSize(0);
  leg->SetEntrySeparation(0.01);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);

  for (map<int, TH1D*>::iterator it = histo1.begin(); it != histo1.end(); it++) {
    int index = int(it->first);

    if (index == 0) {
      leg->AddEntry(it->second, "Data", "p");
    }

    if (index == 10) {
      it->second->SetFillColor(kOrange);
      leg->AddEntry(it->second, "Z #gamma #gamma", "f");
    }
    if (index == 11) {
      it->second->SetFillColor(kOrange-5);
      leg->AddEntry(it->second, "Z #gamma", "f");
    }
    if (index == 21) {
      it->second->SetFillColor(kViolet-5);
      leg->AddEntry(it->second, "W #gamma", "f");
    }
    if (index == 22) {
      it->second->SetFillColor(kViolet);
      leg->AddEntry(it->second, "W #gamma #gamma", "f");
    }
    if (index == 31) {
      it->second->SetFillColor(kViolet+1);
      leg->AddEntry(it->second, "Diboson #gamma", "f");
    }
    if (index == 41) {
      it->second->SetFillColor(kViolet-4);
      leg->AddEntry(it->second, "TT #gamma", "f");
    }
    if (index == 42) {
      it->second->SetFillColor(kViolet-9);
      leg->AddEntry(it->second, "TT #gamma #gamma", "f");
    }

    if (index == 1010) {
      it->second->SetFillColor(kOrange);
      leg->AddEntry(it->second, "W #gamma #gamma", "f");
    }
    if (index == 1011) {
      it->second->SetFillColor(kOrange-5);
      leg->AddEntry(it->second, "W #gamma", "f");
    }
    if (index == 1020) {
      it->second->SetFillColor(kYellow-4);
      leg->AddEntry(it->second, "DYJets", "f");
    }
    if (index == 1031) {
      it->second->SetFillColor(kViolet-4);
      leg->AddEntry(it->second, "TT #gamma", "f");
    }
    if (index == 1032) {
      it->second->SetFillColor(kViolet-9);
      leg->AddEntry(it->second, "TT #gamma #gamma", "f");
    }
    if (index == 1051) {
      it->second->SetFillColor(kViolet+1);
      leg->AddEntry(it->second, "Diboson #gamma", "f");
    }
    if (index == 1021) {
      it->second->SetFillColor(kViolet-5);
      leg->AddEntry(it->second, "Z #gamma", "f");
    }
    if (index == 1022) {
      it->second->SetFillColor(kViolet);
      leg->AddEntry(it->second, "Z #gamma #gamma", "f");
    }

    if (index == 8001) {
      it->second->SetFillColor(kBlue);
      leg->AddEntry(it->second, "Jet MisID", "f");
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

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".matrix/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".matrix/").c_str(), kTRUE);
  }
  c1->SaveAs(("html/" + version + "/" + flag + "/" + year + ".matrix/" + title + ".pdf").c_str());
#endif // defined(USE_MATRIX)

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
