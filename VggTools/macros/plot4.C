#include "plot4.h"
#include "rebin.h"

#include "CMS_lumi.C"

void plot4(string plot="", string title="", string version="v00", string options="", string flag="reference"){

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

  string cat = "cat3";
  if (flag == "jet_misid_cat1") cat = "cat1";
  if (flag == "jet_misid_cat2") cat = "cat2";

  bool useMC = false;
  if (flag == "jet_misid_mc") useMC = true;

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

  map<int, TH1D*> histo;
  map<int, TH3D*> histo3;

  float lumi = 0.;
  float lumi2016 = 0.;
  float lumi2017 = 0.;
  float lumi2018 = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_cat1" || flag == "jet_misid_cat2" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit") {
        file = new TFile(("data/" + version + "/reference/" + it->first + ".root").c_str());
      } else {
        file = new TFile(("data/" + version + "/" + flag + "/" + it->first + ".root").c_str());
      }
      if (!file->IsOpen()) {
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
      if (histo[index]) {
        TH1D* h = (TH1D*)gDirectory->Get(title.c_str());
        if (h) {
          histo[index]->Add(h);
        }
      } else {
        TH1D* h = (TH1D*)gDirectory->Get(title.c_str());
        if (h) {
          histo[index] = h;
          histo[index]->SetDirectory(0);
        } else {
          Error("plot0", "skip missing histogram: %s", title.c_str());
          return;
        }
      }
      if (histo3[index]) {
        TH3D* h3 = (TH3D*)gDirectory->Get((title + "_" + cat + "_map").c_str());
        if (h3) {
          histo3[index]->Add(h3);
        }
      } else {
        TH3D* h3 = (TH3D*)gDirectory->Get((title + "_" + cat + "_map").c_str());
        if (h3) {
          histo3[index] = h3;
          histo3[index]->SetDirectory(0);
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
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_cat1" || flag == "jet_misid_cat2" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit") {
        file = new TFile(("data/" + version + "/reference/" + it->first + ".root").c_str());
      } else {
        file = new TFile(("data/" + version + "/" + flag + "/" + it->first + ".root").c_str());
      }
      if (!file->IsOpen()) {
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
      if (histo[index]) {
        TH1D* h = (TH1D*)gDirectory->Get(title.c_str());
        if (h) {
          histo[index]->Add(h, norm);
        }
      } else {
        TH1D* h = (TH1D*)gDirectory->Get(title.c_str());
        if (h) {
          histo[index] = h;
          histo[index]->SetDirectory(0);
          histo[index]->Scale(norm);
        }
      }
      if (histo3[index]) {
        TH3D* h3 = (TH3D*)gDirectory->Get((title + "_" + cat + "_map").c_str());
        if (h3) {
          histo3[index]->Add(h3, norm);
        }
      } else {
        TH3D* h3 = (TH3D*)gDirectory->Get((title + "_" + cat + "_map").c_str());
        if (h3) {
          histo3[index] = h3;
          histo3[index]->SetDirectory(0);
          histo3[index]->Scale(norm);
        }
      }
      file->Close();
      delete file;
    }
  }

  for (map<int, TH1D*>::iterator it = histo.begin(); it != histo.end(); it++) {
    int index = int(it->first);
    if (histo[index]) histo[index] = rebin(histo[index]);
  }

  for (map<int, TH3D*>::iterator it = histo3.begin(); it != histo3.end(); it++) {
    int index = int(it->first);
    if (histo3[index]) histo3[index] = rebin(histo3[index]);
  }

  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("default") != string::npos) version = version + ".default";

  if (flag == "bkg_stat") {
    for (map<int, TH1D*>::reverse_iterator it = histo.rbegin(); it != histo.rend(); it++) {
      int index = int(it->first);
      if (index > 0) {
        for (int i = 0; i < histo[index]->GetNbinsX()+2; i++) {
          histo[index]->SetBinError(i, histo[index]->GetBinError(i) * 1.1);
        }
      }
    }
  }

// #define USE_RUN2_AVERAGES

#if defined(USE_RUN2_AVERAGES)
  TFile* file_matrix = 0;

  if (title.find("h_WGG_ele") != string::npos) file_matrix = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/h_WG_ele_pho0_pt_matrix_weight.root").c_str());
  if (title.find("h_WGG_muo") != string::npos) file_matrix = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/h_WG_muo_pho0_pt_matrix_weight.root").c_str());
  if (title.find("h_ZGG_ele") != string::npos) file_matrix = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/h_ZG_ele_pho0_pt_matrix_weight.root").c_str());
  if (title.find("h_ZGG_muo") != string::npos) file_matrix = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/h_ZG_muo_pho0_pt_matrix_weight.root").c_str());
  if (file_matrix->IsZombie()) {
    cout << "ERROR: file " << file_matrix->GetName() << " is MISSING !!" << endl;
    return;
  }

  TH1D* h_weight = (TH1D*)file_matrix->Get(useMC ? "h_weight_mc" : "h_weight_data");

  h_weight->SetDirectory(0);
  file_matrix->Close();
  delete file_matrix;
#else
  TFile* file_matrix_2016 = 0;
  TFile* file_matrix_2017 = 0;
  TFile* file_matrix_2018 = 0;

  if (plot.find("2016") != string::npos || plot.find("Run2") != string::npos) {
    if (title.find("h_WGG_ele") != string::npos) file_matrix_2016 = new TFile(("html/" + version + "/" + flag + "/2016.matrix/root/h_WG_ele_pho0_pt_matrix_weight.root").c_str());
    if (title.find("h_WGG_muo") != string::npos) file_matrix_2016 = new TFile(("html/" + version + "/" + flag + "/2016.matrix/root/h_WG_muo_pho0_pt_matrix_weight.root").c_str());
    if (title.find("h_ZGG_ele") != string::npos) file_matrix_2016 = new TFile(("html/" + version + "/" + flag + "/2016.matrix/root/h_ZG_ele_pho0_pt_matrix_weight.root").c_str());
    if (title.find("h_ZGG_muo") != string::npos) file_matrix_2016 = new TFile(("html/" + version + "/" + flag + "/2016.matrix/root/h_ZG_muo_pho0_pt_matrix_weight.root").c_str());
    if (file_matrix_2016->IsZombie()) {
      cout << "ERROR: file " << file_matrix_2016->GetName() << " is MISSING !!" << endl;
      return;
    }
  }
  if (plot.find("2017") != string::npos || plot.find("Run2") != string::npos) {
    if (title.find("h_WGG_ele") != string::npos) file_matrix_2017 = new TFile(("html/" + version + "/" + flag + "/2017.matrix/root/h_WG_ele_pho0_pt_matrix_weight.root").c_str());
    if (title.find("h_WGG_muo") != string::npos) file_matrix_2017 = new TFile(("html/" + version + "/" + flag + "/2017.matrix/root/h_WG_muo_pho0_pt_matrix_weight.root").c_str());
    if (title.find("h_ZGG_ele") != string::npos) file_matrix_2017 = new TFile(("html/" + version + "/" + flag + "/2017.matrix/root/h_ZG_ele_pho0_pt_matrix_weight.root").c_str());
    if (title.find("h_ZGG_muo") != string::npos) file_matrix_2017 = new TFile(("html/" + version + "/" + flag + "/2017.matrix/root/h_ZG_muo_pho0_pt_matrix_weight.root").c_str());
    if ( file_matrix_2017->IsZombie()) {
      cout << "ERROR: file " << file_matrix_2017->GetName() << " is MISSING !!" << endl;
      return;
    }
  }
  if (plot.find("2018") != string::npos || plot.find("Run2") != string::npos) {
    if (title.find("h_WGG_ele") != string::npos) file_matrix_2018 = new TFile(("html/" + version + "/" + flag + "/2018.matrix/root/h_WG_ele_pho0_pt_matrix_weight.root").c_str());
    if (title.find("h_WGG_muo") != string::npos) file_matrix_2018 = new TFile(("html/" + version + "/" + flag + "/2018.matrix/root/h_WG_muo_pho0_pt_matrix_weight.root").c_str());
    if (title.find("h_ZGG_ele") != string::npos) file_matrix_2018 = new TFile(("html/" + version + "/" + flag + "/2018.matrix/root/h_ZG_ele_pho0_pt_matrix_weight.root").c_str());
    if (title.find("h_ZGG_muo") != string::npos) file_matrix_2018 = new TFile(("html/" + version + "/" + flag + "/2018.matrix/root/h_ZG_muo_pho0_pt_matrix_weight.root").c_str());
    if (file_matrix_2018->IsZombie()) {
      cout << "ERROR: file " << file_matrix_2018->GetName() << " is MISSING !!" << endl;
      return;
    }
  }

  TH1D* h_weight_2016 = 0;
  TH1D* h_weight_2017 = 0;
  TH1D* h_weight_2018 = 0;

  if (file_matrix_2016) h_weight_2016 = (TH1D*)file_matrix_2016->Get(useMC ? "h_weight_mc" : "h_weight_data");
  if (file_matrix_2017) h_weight_2017 = (TH1D*)file_matrix_2017->Get(useMC ? "h_weight_mc" : "h_weight_data");
  if (file_matrix_2018) h_weight_2018 = (TH1D*)file_matrix_2018->Get(useMC ? "h_weight_mc" : "h_weight_data");

  if (file_matrix_2016) {
    h_weight_2016->SetDirectory(0);
    file_matrix_2016->Close();
    delete file_matrix_2016;
  }
  if (file_matrix_2017) {
    h_weight_2017->SetDirectory(0);
    file_matrix_2017->Close();
    delete file_matrix_2017;
  }
  if (file_matrix_2018) {
    h_weight_2018->SetDirectory(0);
    file_matrix_2018->Close();
    delete file_matrix_2018;
  }

  TH1D* h_weight = 0;

  if (!h_weight && h_weight_2016) h_weight = (TH1D*)h_weight_2016->Clone("h_weight");
  if (!h_weight && h_weight_2017) h_weight = (TH1D*)h_weight_2017->Clone("h_weight");
  if (!h_weight && h_weight_2018) h_weight = (TH1D*)h_weight_2018->Clone("h_weight");

  h_weight->Reset();
  if (h_weight_2016) h_weight->Add(h_weight_2016, lumi2016/lumi);
  if (h_weight_2017) h_weight->Add(h_weight_2017, lumi2017/lumi);
  if (h_weight_2018) h_weight->Add(h_weight_2018, lumi2018/lumi);
#endif // defined(USE_RUN2_AVERAGES)

  for (map<int, TH3D*>::iterator it = histo3.begin(); it != histo3.end(); it++) {
    int index = int(it->first);
    if (!histo3[index]) continue;
    if (title.find("h_WGG_") != string::npos || title.find("h_ZGG_") != string::npos) {
      for (int var = 0; var < histo3[index]->GetNbinsZ()+2; var++) {
        for (int pho0 = 0; pho0 < histo3[index]->GetNbinsX()+2; pho0++) {
          for (int pho1 = 0; pho1 < histo3[index]->GetNbinsY()+2; pho1++) {
            if (cat == "cat1") {
              histo3[index]->SetBinContent(pho0, pho1, var, histo3[index]->GetBinContent(pho0, pho1, var) * h_weight->GetBinContent(pho0) / (1 - h_weight->GetBinContent(pho0)));
              histo3[index]->SetBinError(pho0, pho1, var, TMath::Sqrt(TMath::Power(histo3[index]->GetBinError(pho0, pho1, var) * h_weight->GetBinContent(pho0) / (1 - h_weight->GetBinContent(pho0)), 2) + TMath::Power(histo3[index]->GetBinContent(pho0, pho1, var) * h_weight->GetBinError(pho0) / TMath::Power(1 - h_weight->GetBinContent(pho0), 2), 2)));
            }
            if (cat == "cat2") {
              histo3[index]->SetBinContent(pho0, pho1, var, histo3[index]->GetBinContent(pho0, pho1, var) * h_weight->GetBinContent(pho1) / (1 - h_weight->GetBinContent(pho1)));
              histo3[index]->SetBinError(pho0, pho1, var, TMath::Sqrt(TMath::Power(histo3[index]->GetBinError(pho0, pho1, var) * h_weight->GetBinContent(pho1) / (1 - h_weight->GetBinContent(pho1)), 2) + TMath::Power(histo3[index]->GetBinContent(pho0, pho1, var) * h_weight->GetBinError(pho1) / TMath::Power(1 - h_weight->GetBinContent(pho1), 2), 2)));
            }
            if (cat == "cat3") {
              histo3[index]->SetBinContent(pho0, pho1, var, histo3[index]->GetBinContent(pho0, pho1, var) * h_weight->GetBinContent(pho0) * h_weight->GetBinContent(pho1) / (1 - h_weight->GetBinContent(pho0) * h_weight->GetBinContent(pho1)));
              histo3[index]->SetBinError(pho0, pho1, var, TMath::Sqrt(TMath::Power(histo3[index]->GetBinError(pho0, pho1, var) * h_weight->GetBinContent(pho0) * h_weight->GetBinContent(pho1) / (1 - h_weight->GetBinContent(pho0) * h_weight->GetBinContent(pho1)), 2) + TMath::Power(histo3[index]->GetBinContent(pho0, pho1, var) * h_weight->GetBinError(pho0) * h_weight->GetBinContent(pho1) / TMath::Power(1 - h_weight->GetBinContent(pho0) * h_weight->GetBinContent(pho1), 2), 2) + TMath::Power(histo3[index]->GetBinContent(pho0, pho1, var) * h_weight->GetBinContent(pho0) * h_weight->GetBinError(pho1) / TMath::Power(1 - h_weight->GetBinContent(pho0) * h_weight->GetBinContent(pho1), 2), 2)));

            }
            histo3[index]->SetBinError(pho0, pho1, var, histo3[index]->GetBinError(pho0, pho1, var) * (1 + 0.1 * (flag == "jet_misid_stat")));
          }
        }
      }
    }
  }

  TH3D* histo3_cr = (TH3D*)histo3[0]->Clone("histo3_cr");

  for (map<int, TH3D*>::iterator it = histo3.begin(); it != histo3.end(); it++) {
    int index = int(it->first);
    if (index == 10 || index == 11 || index == 21 || index == 22 || index == 31 || index == 41 || index == 42 || index == 1010 || index == 1011 || index == 1021 || index == 1022 || index == 1031 || index == 1032 || index == 1051) { 
      histo3_cr->Add(histo3[index], -1);
    }
  }

  histo[8001] = (TH1D*)histo[0]->Clone();
  histo[8001]->Reset();

  if (title.find("h_WGG_") != string::npos || title.find("h_ZGG_") != string::npos) {
    for (int var = 0; var < histo3[0]->GetNbinsZ()+2; var++) {
      for (int pho0 = 0; pho0 < histo3[0]->GetNbinsX()+2; pho0++) {
        for (int pho1 = 0; pho1 < histo3[0]->GetNbinsY()+2; pho1++) {
          histo[8001]->SetBinContent(var, histo[8001]->GetBinContent(var) + histo3_cr->GetBinContent(pho0, pho1, var));
          histo[8001]->SetBinError(var, TMath::Sqrt(TMath::Power(histo[8001]->GetBinError(var), 2) + TMath::Power(histo3_cr->GetBinError(pho0, pho1, var), 2)));
        }
      }
    }
  }

  THStack* hstack_mc = new THStack("hstack_mc", "hstack_mc");

  TH1D* h_mc_sum = (TH1D*)histo[0]->Clone("h_mc_sum");
  h_mc_sum->Reset();

  bool flowbins = true;

  for (map<int, TH1D*>::reverse_iterator it = histo.rbegin(); it != histo.rend(); it++) {
    int index = int(it->first);
    if (flowbins) {
      histo[index]->SetBinContent(1, histo[index]->GetBinContent(1) + histo[index]->GetBinContent(0));
      histo[index]->SetBinContent(histo[index]->GetNbinsX(), histo[index]->GetBinContent(histo[index]->GetNbinsX()) + histo[index]->GetBinContent(histo[index]->GetNbinsX()+1));
      histo[index]->SetBinError(1, TMath::Sqrt(TMath::Power(histo[index]->GetBinError(1), 2) + TMath::Power(histo[index]->GetBinError(0), 2)));
      histo[index]->SetBinError(histo[index]->GetNbinsX(), TMath::Sqrt(TMath::Power(histo[index]->GetBinError(histo[index]->GetNbinsX()), 2) + TMath::Power(histo[index]->GetBinError(histo[index]->GetNbinsX()+1), 2)));
      histo[index]->SetBinContent(0, 0.);
      histo[index]->SetBinContent(histo[index]->GetNbinsX()+1, 0.);
      histo[index]->SetBinError(0, 0.);
      histo[index]->SetBinError(histo[index]->GetNbinsX()+1, 0.);
    }
    if (index > 0) {
      if (options.find("nobkg") != string::npos) {
        if ((title.find("h_WGG_") != string::npos || title.find("h_ZGG_") != string::npos) && (index == 10 || index == 1010)) {
          hstack_mc->Add(it->second);
          h_mc_sum->Add(it->second);
        }
      } else {
        if ((title.find("h_WGG_") != string::npos || title.find("h_ZGG_") != string::npos) && (index == 10 || index == 11 || index == 21 || index == 22 || index == 31 || index == 41 || index == 42 || index == 1010 || index == 1011 || index == 1021 || index == 1022 || index == 1031 || index == 1032 || index == 1051 || index == 8001)) {
          hstack_mc->Add(it->second);
          h_mc_sum->Add(it->second);
        }
      }
    }
  }

  TH1D* h_ratio = (TH1D*)histo[0]->Clone("h_ratio");
  h_ratio->Divide(h_mc_sum);

  TLegend* leg = new TLegend(0.65, 0.640, 0.91, 0.88);
  leg->SetBorderSize(0);
  leg->SetEntrySeparation(0.01);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);

  for (map<int, TH1D*>::iterator it = histo.begin(); it != histo.end(); it++) {
    if (it->first == 0) {
      leg->AddEntry(it->second, "Data", "p");
    }
    if (it->first == 10) {
      it->second->SetFillColor(kOrange);
      leg->AddEntry(it->second, "Z #gamma #gamma", "f");
    }
    if (it->first == 11) {
      it->second->SetFillColor(kOrange-5);
      leg->AddEntry(it->second, "Z #gamma", "f");
    }
    if (it->first == 21) {
      it->second->SetFillColor(kViolet-5);
      leg->AddEntry(it->second, "W #gamma", "f");
    }
    if (it->first == 22) {
      it->second->SetFillColor(kViolet);
      leg->AddEntry(it->second, "W #gamma #gamma", "f");
    }
    if (it->first == 31) {
      it->second->SetFillColor(kViolet+1);
      leg->AddEntry(it->second, "Diboson #gamma", "f");
    }
    if (it->first == 41) {
      it->second->SetFillColor(kViolet-4);
      leg->AddEntry(it->second, "TT #gamma", "f");
    }
    if (it->first == 42) {
      it->second->SetFillColor(kViolet-9);
      leg->AddEntry(it->second, "TT #gamma #gamma", "f");
    }
    if (it->first == 1010) {
      it->second->SetFillColor(kOrange);
      leg->AddEntry(it->second, "W #gamma #gamma", "f");
    }
    if (it->first == 1011) {
      it->second->SetFillColor(kOrange-5);
      leg->AddEntry(it->second, "W #gamma", "f");
    }
    if (it->first == 1020) {
      it->second->SetFillColor(kYellow-4);
      leg->AddEntry(it->second, "DYJets", "f");
    }
    if (title.find("h_WGG_") != string::npos && it->first == 1031) {
      it->second->SetFillColor(kViolet-4);
      leg->AddEntry(it->second, "TT #gamma", "f");
    }
    if (title.find("h_WGG_") != string::npos && it->first == 1032) {
      it->second->SetFillColor(kViolet-9);
      leg->AddEntry(it->second, "TT #gamma #gamma", "f");
    }
    if (title.find("h_WGG_") != string::npos && it->first == 1051) {
      it->second->SetFillColor(kViolet+1);
      leg->AddEntry(it->second, "Diboson #gamma", "f");
    }
    if (title.find("h_WGG_") != string::npos && it->first == 1021) {
      it->second->SetFillColor(kViolet-5);
      leg->AddEntry(it->second, "Z #gamma", "f");
    }
    if (it->first == 1022) {
      it->second->SetFillColor(kViolet);
      leg->AddEntry(it->second, "Z #gamma #gamma", "f");
    }
    if (it->first == 8001) {
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

  hstack_mc->SetMaximum(1.2*TMath::Max(hstack_mc->GetMaximum(), histo[0]->GetMaximum()));
  if (options.find("nolog") == string::npos) hstack_mc->SetMinimum(0.0001*hstack_mc->GetMaximum());
  hstack_mc->SetMinimum(1.);

  hstack_mc->Draw("HIST");

  hstack_mc->SetTitle("");
  histo[0]->SetStats(kFALSE);

  hstack_mc->GetXaxis()->SetTitleOffset(0.7);
  hstack_mc->GetXaxis()->SetLabelFont(42);
  hstack_mc->GetXaxis()->SetLabelSize(0.08);

  hstack_mc->GetYaxis()->SetTitle("Events");
  hstack_mc->GetYaxis()->SetTitleSize(0.05);
  hstack_mc->GetYaxis()->SetTitleOffset(0.8);
  hstack_mc->GetYaxis()->SetLabelSize(0.045);

  histo[0]->SetMarkerColor(kBlack);
  histo[0]->SetMarkerStyle(20);
  histo[0]->SetMarkerSize(1.0);

  histo[0]->Draw("EXP0SAMES");

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

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str(), kTRUE);
  }
  TFile* file = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + ".root").c_str(), "RECREATE");
  histo[0]->Write((title + "_data").c_str());
  histo[8001]->Write((title + "_misid").c_str());
  if (title.find("h_WGG_") != string::npos) {
    histo[1010]->Write((title + "_sig").c_str());
    histo[1011]->Write((title + "_wg").c_str());
    histo[1021]->Write((title + "_zg").c_str());
    histo[1022]->Write((title + "_zgg").c_str());
    histo[1031]->Write((title + "_ttg").c_str());
    histo[1032]->Write((title + "_ttgg").c_str());
    histo[1051]->Write((title + "_vvg").c_str());
  }
  if (title.find("h_ZGG_") != string::npos) {
    histo[10]->Write((title + "_sig").c_str());
    histo[11]->Write((title + "_zg").c_str());
    histo[21]->Write((title + "_wg").c_str());
    histo[22]->Write((title + "_wgg").c_str());
    histo[31]->Write((title + "_vvg").c_str());
    histo[41]->Write((title + "_ttg").c_str());
    histo[42]->Write((title + "_ttgg").c_str());
  }
  file->Close();
  delete file;

}

int main(int argc, char *argv[]) {

#pragma unused (argc)

cout << "Processing plot4.C(\"" << argv[1] << "\",\""
                                << argv[2] << "\",\""
                                << argv[3] << "\",\""
                                << argv[4] << "\",\""
                                << argv[5] << "\")..." << endl;

plot4(argv[1], argv[2], argv[3], argv[4], argv[5]);

}
