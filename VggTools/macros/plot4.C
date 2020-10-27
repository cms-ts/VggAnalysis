#include "plot4.h"
#include "rebin.h"

#ifndef CMS_lumi_C
#define CMS_lumi_C
#include "CMS_lumi.C"
#endif

int plot4(string plot="", string title="", string version="v00", string options="default", string flag="reference"){

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

  if (options.find("identity0") != string::npos || options.find("identity1") != string::npos || options.find("closure0") != string::npos || options.find("closure1") != string::npos) {
    if (flag != "reference") {
      Warning("plot4", "skipping options %s for flag %s", options.c_str(), flag.c_str());
      return 0;
    }
  }

  if (options.find("identity1") != string::npos || options.find("closure0") != string::npos || options.find("closure1") != string::npos) {
    if (plot.find("2018") != string::npos || plot.find("Run2") != string::npos) {
      Warning("plot4", "no sherpa sample available for this year !!");
      return 0;
    }
    if (title.find("h_WG") != string::npos) {
      Warning("plot4", "no sherpa sample available for the W channel !!");
      return 0;
    }
  }

  map<string, double> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets from " << "lumi.dat" << endl;

  map<string, double> xsecMap;
  readMap("xsec.dat", xsecMap);
  cout << "Read xsec map for " << xsecMap.size() << " datasets from " << "xsec.dat" << endl;

  multimap<string, double> plotMap;
  if (plot.find("Run2") == string::npos) {
    readMultiMap(plot, plotMap);
  } else {
    readMultiMap(string(plot).replace(plot.find("Run2"), 4, "2016"), plotMap);
    readMultiMap(string(plot).replace(plot.find("Run2"), 4, "2017"), plotMap);
    readMultiMap(string(plot).replace(plot.find("Run2"), 4, "2018"), plotMap);
  }
  cout << "Read plot map for " << plotMap.size() << " datasets from " << plot << endl;

  if (plotMap.size() == 0) {
    Error("plot4", "plot map %s is EMPTY or MISSING !!", plot.c_str());
    return 1;
  }

  map<int, TH1D*> histo;
  map<int, TH3D*> histo3;

  double lumi = 0.;
  double lumi2016 = 0.;
  double lumi2017 = 0.;
  double lumi2018 = 0.;

  for (multimap<string, double>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_test" || flag == "jet_misid_qcd" || flag == "jet_misid_sherpa"|| flag == "bkg_syst" || flag == "xsec_syst_wg" || flag == "xsec_syst_zg" || flag == "xsec_syst_others" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit" || flag == "lumi_up" || flag == "lumi_down") {
        file = new TFile(("data/" + version + "/reference/" + it->first + ".root").c_str());
      } else {
        file = new TFile(("data/" + version + "/" + flag + "/" + it->first + ".root").c_str());
      }
      if (file->IsZombie()) {
        Error("plot4", "file %s is MISSING !!", file->GetName());
        return 1;
      }
      if (lumiMap[it->first] != 0) {
        double var = (flag == "lumi_up") - (flag == "lumi_down");
        lumi = lumi + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2016") != string::npos) lumi2016 = lumi2016 + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2017") != string::npos) lumi2017 = lumi2017 + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2018") != string::npos) lumi2018 = lumi2018 + lumiMap[it->first] * (1.000 + 0.018 * var);
      } else {
        Warning("plot4", "luminosity for %s is ZERO !!", it->first.c_str());
      }
      if (histo[index]) {
        TH1D* h = (TH1D*)file->Get(title.c_str());
        if (h) {
          histo[index]->Add(h);
        }
      } else {
        TH1D* h = (TH1D*)file->Get(title.c_str());
        if (h) {
          histo[index] = h;
          histo[index]->SetDirectory(0);
        } else {
          Error("plot4", "histogram %s is MISSING !!", title.c_str());
          return 1;
        }
      }

      int index_region = -1;
      string eta_string = "";
      string iso_string = "";
      for (int eta_region = 1; eta_region < 5; eta_region++) {
        if (eta_region == 1) eta_string = "bb";
        if (eta_region == 2) eta_string = "be";
        if (eta_region == 3) eta_string = "eb";
        if (eta_region == 4) eta_string = "ee";
        for (int iso_region = 1; iso_region < 5; iso_region++) {
          if (iso_region == 1) iso_string = "tt";
          if (iso_region == 2) iso_string = "tl";
          if (iso_region == 3) iso_string = "lt";
          if (iso_region == 4) iso_string = "ll";
          index_region = 4200 + eta_region*10 + iso_region;
          if (histo3[index_region]) {
            TH3D* h3 = (TH3D*)file->Get((title + "_" + eta_string + "_" + iso_string).c_str());
            if (h3) {
              histo3[index_region]->Add(h3);
            }
          } else {
            TH3D* h3 = (TH3D*)file->Get((title + "_" + eta_string + "_" + iso_string).c_str());
            if (h3) {
              histo3[index_region] = h3;
              histo3[index_region]->SetDirectory(0);
            }
          }
        }
      }
      delete file;
    }
  }

  if (lumi == 0) {
    Error("plot4", "total luminosity is ZERO !!");
    return 1;
  }

  for (multimap<string, double>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 10 || index == 11 || index == 21 || index == 22 || index == 31 || index == 41 || index == 42 || index == 51 || index == 61 || index == 1010 || index == 1011 || index == 1021 || index == 1022 || index == 1031 || index == 1032 || index == 1041 || index == 1051 || index == 1061) {
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_test" || flag == "jet_misid_qcd" || flag == "jet_misid_sherpa" || flag == "bkg_syst" || flag == "xsec_syst_wg" || flag == "xsec_syst_zg" || flag == "xsec_syst_others" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit" || flag == "lumi_up" || flag == "lumi_down") {
        file = new TFile(("data/" + version + "/reference/" + it->first + ".root").c_str());
      } else {
        file = new TFile(("data/" + version + "/" + flag + "/" + it->first + ".root").c_str());
      }
      if (file->IsZombie()) {
        Error("plot4", "file %s is MISSING !!", file->GetName());
        return 1;
      }
      double norm = 1.;
      if (xsecMap[it->first] != 0) {
        double ngen = ((TH1D*)file->Get("h_nevt"))->GetBinContent(2);
        if (it->first.find("RunIISummer16") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2016 / ngen;
        if (it->first.find("RunIIFall17") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2017 / ngen;
        if (it->first.find("RunIIAutumn18") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2018 / ngen;
        if (flag == "bkg_syst") norm = norm * 1.075;
        if (flag == "xsec_syst_wg" && (index == 21 || index == 1011)) norm = norm * 1.025;
        if (flag == "xsec_syst_zg" && (index == 11 || index == 1021)) norm = norm * 1.025;
        if (flag == "xsec_syst_others" && index != 10 && index != 11 && index != 21 && index != 1010 && index != 1011 && index != 1021) norm = norm * 1.075;
      } else {
        Error("plot4", "cross section for %s is ZERO !!", it->first.c_str());
        return 1;
      }
      if (histo[index]) {
        TH1D* h = (TH1D*)file->Get((title + "_genmatch").c_str());
        if (title.find("h_WGG_ele") != string::npos) {
          TH1D* h1 = (TH1D*)file->Get((title + "_genmatch2").c_str());
          h->Add(h1);
        }
        if (h) {
          histo[index]->Add(h, norm);
        }
      } else {
        TH1D* h = (TH1D*)file->Get((title + "_genmatch").c_str());
        if (title.find("h_WGG_ele") != string::npos) {
          TH1D* h1 = (TH1D*)file->Get((title + "_genmatch2").c_str());
          h->Add(h1);
        }
        if (h) {
          histo[index] = h;
          histo[index]->SetDirectory(0);
          histo[index]->Scale(norm);
        }
      }

      if (title.find("h_WGG_ele") != string::npos && index == 1021) {
        int index_region = -1;
        string eta_string = "";
        string iso_string = "";
        for (int eta_region = 1; eta_region < 5; eta_region++) {
          if (eta_region == 1) eta_string = "bb";
          if (eta_region == 2) eta_string = "be";
          if (eta_region == 3) eta_string = "eb";
          if (eta_region == 4) eta_string = "ee";
          for (int iso_region = 1; iso_region < 5; iso_region++) {
            if (iso_region == 1) iso_string = "tt";
            if (iso_region == 2) iso_string = "tl";
            if (iso_region == 3) iso_string = "lt";
            if (iso_region == 4) iso_string = "ll";
            index_region = 4200 + eta_region*10 + iso_region;
            if (histo3[-index_region]) {
              TH3D* h3 = (TH3D*)file->Get((title + "_" + eta_string + "_" + iso_string).c_str());
              if (h3) {
                histo3[-index_region]->Add(h3, norm);
              }
            } else {
              TH3D* h3 = (TH3D*)file->Get((title + "_" + eta_string + "_" + iso_string).c_str());
              if (h3) {
                histo3[-index_region] = h3;
                histo3[-index_region]->SetDirectory(0);
                histo3[-index_region]->Scale(norm);
              }
            }
          }
        }
      }
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
  if (options.find("sherpa") != string::npos) version = version + ".sherpa";
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

// #define CHECK_CLOSURE

#if defined(CHECK_CLOSURE)
  if (title.find("h_WGG_") != string::npos) {
    histo[1010]->Reset();
  }
  if (title.find("h_ZGG_") != string::npos) {
    histo[10]->Reset();
  }
#endif // defined(CHECK_CLOSURE)

  histo[8001] = (TH1D*)histo[0]->Clone();
  histo[8001]->Reset();

  for (int i = 1; i < 9; i++) {
    histo[8001 + i] = (TH1D*)histo[0]->Clone();
    histo[8001 + i]->Reset();
  }

  TFile* file_matrix_2016 = 0;
  TFile* file_matrix_2017 = 0;
  TFile* file_matrix_2018 = 0;

  string title_tmp = "";
  if (options.find("identity0") != string::npos) title_tmp += "_identity0";
  if (options.find("identity1") != string::npos) title_tmp += "_identity1";
  if (options.find("closure0") != string::npos) title_tmp += "_closure0";
  if (options.find("closure1") != string::npos) title_tmp += "_closure1";

  if (plot.find("2016") != string::npos || plot.find("Run2") != string::npos) {
    if (flag == "jet_misid_test") {
      if (title.find("h_WGG") != string::npos) file_matrix_2016 = new TFile(("html/" + version + "/" + flag + "/2016.matrix/root/h_WG_ele_pho0_pt" + title_tmp + ".root").c_str());
      if (title.find("h_ZGG") != string::npos) file_matrix_2016 = new TFile(("html/" + version + "/" + flag + "/2016.matrix/root/h_ZG_ele_pho0_pt" + title_tmp + ".root").c_str());
    } else {
      if (title.find("h_WGG") != string::npos) file_matrix_2016 = new TFile(("html/" + version + "/" + flag + "/2016.matrix/root/h_WG_muo_pho0_pt" + title_tmp + ".root").c_str());
      if (title.find("h_ZGG") != string::npos) file_matrix_2016 = new TFile(("html/" + version + "/" + flag + "/2016.matrix/root/h_ZG_muo_pho0_pt" + title_tmp + ".root").c_str());
    }
    if (file_matrix_2016->IsZombie()) {
      Error("plot4", "file %s is MISSING !!", file_matrix_2016->GetName());
      return 1;
    }
  }
  if (plot.find("2017") != string::npos || plot.find("Run2") != string::npos) {
    if (flag == "jet_misid_test") {
      if (title.find("h_WGG") != string::npos) file_matrix_2017 = new TFile(("html/" + version + "/" + flag + "/2017.matrix/root/h_WG_ele_pho0_pt" + title_tmp + ".root").c_str());
      if (title.find("h_ZGG") != string::npos) file_matrix_2017 = new TFile(("html/" + version + "/" + flag + "/2017.matrix/root/h_ZG_ele_pho0_pt" + title_tmp + ".root").c_str());
    } else {
      if (title.find("h_WGG") != string::npos) file_matrix_2017 = new TFile(("html/" + version + "/" + flag + "/2017.matrix/root/h_WG_muo_pho0_pt" + title_tmp + ".root").c_str());
      if (title.find("h_ZGG") != string::npos) file_matrix_2017 = new TFile(("html/" + version + "/" + flag + "/2017.matrix/root/h_ZG_muo_pho0_pt" + title_tmp + ".root").c_str());
    }
    if ( file_matrix_2017->IsZombie()) {
      Error("plot4", "file %s is MISSING !!", file_matrix_2017->GetName());
      return 1;
    }
  }
  if (plot.find("2018") != string::npos || plot.find("Run2") != string::npos) {
    if (flag == "jet_misid_test") {
      if (title.find("h_WGG") != string::npos) file_matrix_2018 = new TFile(("html/" + version + "/" + flag + "/2018.matrix/root/h_WG_ele_pho0_pt" + title_tmp + ".root").c_str());
      if (title.find("h_ZGG") != string::npos) file_matrix_2018 = new TFile(("html/" + version + "/" + flag + "/2018.matrix/root/h_ZG_ele_pho0_pt" + title_tmp + ".root").c_str());
    } else {
      if (title.find("h_WGG") != string::npos) file_matrix_2018 = new TFile(("html/" + version + "/" + flag + "/2018.matrix/root/h_WG_muo_pho0_pt" + title_tmp + ".root").c_str());
      if (title.find("h_ZGG") != string::npos) file_matrix_2018 = new TFile(("html/" + version + "/" + flag + "/2018.matrix/root/h_ZG_muo_pho0_pt" + title_tmp + ".root").c_str());
    }
    if (file_matrix_2018->IsZombie()) {
      Error("plot4", "file %s is MISSING !!", file_matrix_2018->GetName());
      return 1;
    }
  }

  for (int var = 1; var < histo3[4211]->GetNbinsZ()+1; var++) {
    for (int eta = 1; eta < 5; eta++) {
      for (int pho0_pt = 2; pho0_pt < histo3[4211]->GetNbinsX()+1; pho0_pt++) {
        for (int pho1_pt = 2; pho1_pt < histo3[4211]->GetNbinsY()+1; pho1_pt++) {

          int index_region = 4200 + eta*10;

          TVectorD n_region(4);
          n_region[0] = histo3[index_region + 1]->GetBinContent(pho0_pt, pho1_pt, var);
          n_region[1] = histo3[index_region + 2]->GetBinContent(pho0_pt, pho1_pt, var);
          n_region[2] = histo3[index_region + 3]->GetBinContent(pho0_pt, pho1_pt, var);
          n_region[3] = histo3[index_region + 4]->GetBinContent(pho0_pt, pho1_pt, var);

          TVectorD n_region_err(4);
          n_region_err[0] = histo3[index_region + 1]->GetBinError(pho0_pt, pho1_pt, var);
          n_region_err[1] = histo3[index_region + 2]->GetBinError(pho0_pt, pho1_pt, var);
          n_region_err[2] = histo3[index_region + 3]->GetBinError(pho0_pt, pho1_pt, var);
          n_region_err[3] = histo3[index_region + 4]->GetBinError(pho0_pt, pho1_pt, var);

          if (title.find("h_WGG_ele") != string::npos) {

            n_region[0] = n_region[0] - histo3[-(index_region + 1)]->GetBinContent(pho0_pt, pho1_pt, var);
            n_region[1] = n_region[1] - histo3[-(index_region + 2)]->GetBinContent(pho0_pt, pho1_pt, var);
            n_region[2] = n_region[2] - histo3[-(index_region + 3)]->GetBinContent(pho0_pt, pho1_pt, var);
            n_region[3] = n_region[3] - histo3[-(index_region + 4)]->GetBinContent(pho0_pt, pho1_pt, var);

            n_region_err[0] = TMath::Sqrt(TMath::Power(n_region_err[0], 2) + TMath::Power(histo3[-(index_region + 1)]->GetBinError(pho0_pt, pho1_pt, var), 2));
            n_region_err[1] = TMath::Sqrt(TMath::Power(n_region_err[1], 2) + TMath::Power(histo3[-(index_region + 2)]->GetBinError(pho0_pt, pho1_pt, var), 2));
            n_region_err[2] = TMath::Sqrt(TMath::Power(n_region_err[2], 2) + TMath::Power(histo3[-(index_region + 3)]->GetBinError(pho0_pt, pho1_pt, var), 2));
            n_region_err[3] = TMath::Sqrt(TMath::Power(n_region_err[3], 2) + TMath::Power(histo3[-(index_region + 4)]->GetBinError(pho0_pt, pho1_pt, var), 2));

          }

          if (n_region[0] < 0) {
            n_region[0] = 0;
            n_region_err[0] = 0;
          }
          if (n_region[1] < 0) {
            n_region[1] = 0;
            n_region_err[1] = 0;
          }
          if (n_region[2] < 0) {
            n_region[2] = 0;
            n_region_err[2] = 0;
          }
          if (n_region[3] < 0) {
            n_region[3] = 0;
            n_region_err[3] = 0;
          }

          for (int i = 0; i < 9; i++) {

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

            if (file_matrix_2016) {
              TMatrixD* matrix_2016 = (TMatrixD*)file_matrix_2016->Get((flag == "jet_misid_qcd" && title.find("h_WGG") != string::npos) ? (matrix_title + "_qcd").c_str() : matrix_title.c_str());
              matrix = matrix + (*matrix_2016) * double(lumi2016/lumi);
              delete matrix_2016;
            }
            if (file_matrix_2017) {
              TMatrixD* matrix_2017 = (TMatrixD*)file_matrix_2017->Get((flag == "jet_misid_qcd" && title.find("h_WGG") != string::npos) ? (matrix_title + "_qcd").c_str() : matrix_title.c_str());
              matrix = matrix + (*matrix_2017) * double(lumi2017/lumi);
              delete matrix_2017;
            }
            if (file_matrix_2018) {
              TMatrixD* matrix_2018 = (TMatrixD*)file_matrix_2018->Get((flag == "jet_misid_qcd" && title.find("h_WGG") != string::npos) ? (matrix_title + "_qcd").c_str() : matrix_title.c_str());
              matrix = matrix + (*matrix_2018) * double(lumi2018/lumi);
              delete matrix_2018;
            }

            TMatrixD inverse_matrix = matrix;
            inverse_matrix.Invert();

            TVectorD alpha(4);
            alpha = inverse_matrix * n_region;

            TVectorD alpha_err(4);
            alpha_err(0) = TMath::Sqrt(TMath::Power(inverse_matrix(0,0)*n_region_err(0), 2) + TMath::Power(inverse_matrix(0,1)*n_region_err(1), 2) + TMath::Power(inverse_matrix(0,2)*n_region_err(2), 2) + TMath::Power(inverse_matrix(0,3)*n_region_err(3), 2));
            alpha_err(1) = TMath::Sqrt(TMath::Power(inverse_matrix(1,0)*n_region_err(0), 2) + TMath::Power(inverse_matrix(1,1)*n_region_err(1), 2) + TMath::Power(inverse_matrix(1,2)*n_region_err(2), 2) + TMath::Power(inverse_matrix(1,3)*n_region_err(3), 2));
            alpha_err(2) = TMath::Sqrt(TMath::Power(inverse_matrix(2,0)*n_region_err(0), 2) + TMath::Power(inverse_matrix(2,1)*n_region_err(1), 2) + TMath::Power(inverse_matrix(2,2)*n_region_err(2), 2) + TMath::Power(inverse_matrix(2,3)*n_region_err(3), 2));
            alpha_err(3) = TMath::Sqrt(TMath::Power(inverse_matrix(3,0)*n_region_err(0), 2) + TMath::Power(inverse_matrix(3,1)*n_region_err(1), 2) + TMath::Power(inverse_matrix(3,2)*n_region_err(2), 2) + TMath::Power(inverse_matrix(3,3)*n_region_err(3), 2));

            alpha_err(0) = alpha_err(0) * (1. + 0.1 * (flag == "jet_misid_stat"));
            alpha_err(1) = alpha_err(1) * (1. + 0.1 * (flag == "jet_misid_stat"));
            alpha_err(2) = alpha_err(2) * (1. + 0.1 * (flag == "jet_misid_stat"));
            alpha_err(3) = alpha_err(3) * (1. + 0.1 * (flag == "jet_misid_stat"));

            histo[8001 + i]->SetBinContent(var, histo[8001 + i]->GetBinContent(var) + matrix(0,1)*alpha(1) + matrix(0,2)*alpha(2) + matrix(0,3)*alpha(3));
            histo[8001 + i]->SetBinError(var, TMath::Sqrt(TMath::Power(histo[8001 + i]->GetBinError(var), 2) + TMath::Power(matrix(0,1)*alpha_err(1), 2) + TMath::Power(matrix(0,2)*alpha_err(2), 2) + TMath::Power(matrix(0,3)*alpha_err(3), 2)));
          }

#if defined(CHECK_CLOSURE)
          if (title.find("h_WGG_") != string::npos) {
            histo[1010]->SetBinContent(var, histo[1010]->GetBinContent(var) + matrix(0,0)*alpha(0));
            histo[1010]->SetBinError(var, TMath::Sqrt(TMath::Power(histo[1010]->GetBinError(var), 2) + TMath::Power(matrix(0,0)*alpha_err(0), 2)));
          }
          if (title.find("h_ZGG_") != string::npos) {
            histo[10]->SetBinContent(var, histo[10]->GetBinContent(var) + matrix(0,0)*alpha(0));
            histo[10]->SetBinError(var, TMath::Sqrt(TMath::Power(histo[10]->GetBinError(var), 2) + TMath::Power(matrix(0,0)*alpha_err(0), 2)));
          }
#endif // defined(CHECK_CLOSURE)
        }
      }
    }
  }

  for (int i = 0; i < histo[8001]->GetNbinsX() + 1; i++) {
    histo[8001]->SetBinError(i, TMath::Sqrt(TMath::Power(histo[8001]->GetBinError(i), 2)
    + TMath::Power(0.5 * (fabs(histo[8002]->GetBinContent(i) - histo[8001]->GetBinContent(i)) + fabs(histo[8006]->GetBinContent(i) - histo[8001]->GetBinContent(i))), 2)
    + TMath::Power(0.5 * (fabs(histo[8003]->GetBinContent(i) - histo[8001]->GetBinContent(i)) + fabs(histo[8007]->GetBinContent(i) - histo[8001]->GetBinContent(i))), 2)
    + TMath::Power(0.5 * (fabs(histo[8004]->GetBinContent(i) - histo[8001]->GetBinContent(i)) + fabs(histo[8008]->GetBinContent(i) - histo[8001]->GetBinContent(i))), 2)
    + TMath::Power(0.5 * (fabs(histo[8005]->GetBinContent(i) - histo[8001]->GetBinContent(i)) + fabs(histo[8009]->GetBinContent(i) - histo[8001]->GetBinContent(i))), 2)));
  }

  if (file_matrix_2016) {
    delete file_matrix_2016;
  }
  if (file_matrix_2017) {
    delete file_matrix_2017;
  }
  if (file_matrix_2018) {
    delete file_matrix_2018;
  }

  for (int i = 1; i < 9; i++) {
    delete histo[8001 + i];
    histo.erase(8001 + i);
  }

#if defined(CHECK_CLOSURE)
  for (map<int, TH1D*>::iterator it = histo.begin(); it != histo.end(); it++) {
    int index = int(it->first);
    if (index > 0) {
      if (title.find("h_WGG_") != string::npos && index != 1010 && index != 8001) {
        for (int i = 0; i < histo[1010]->GetNbinsX()+2; i++) {
          histo[1010]->SetBinContent(i, histo[1010]->GetBinContent(i) - histo[index]->GetBinContent(i));
          histo[1010]->SetBinError(i, TMath::Sqrt(TMath::Max(0., TMath::Power(histo[1010]->GetBinError(i), 2) - TMath::Power(histo[index]->GetBinError(i), 2))));
        }
      }
      if (title.find("h_ZGG_") != string::npos && index != 10 && index != 8001) {
        for (int i = 0; i < histo[10]->GetNbinsX()+2; i++) {
          histo[10]->SetBinContent(i, histo[10]->GetBinContent(i) - histo[index]->GetBinContent(i));
          histo[10]->SetBinError(i, TMath::Sqrt(TMath::Max(0., TMath::Power(histo[10]->GetBinError(i), 2) - TMath::Power(histo[index]->GetBinError(i), 2))));
        }
      }
    }
  }
#endif // defined(CHECK_CLOSURE)

  for (map<int, TH1D*>::iterator it = histo.begin(); it != histo.end(); it++) {
    int index = int(it->first);
    if (histo[index]) {
      histo[index]->SetName((string(histo[index]->GetName()) + "_rebin").c_str());
      histo[index] = rebin(histo[index]);
    }
  }

  if (plot.find("Run2") != string::npos) {
    TFile* file_2016 = new TFile(("html/" + version + "/" + flag + "/2016.matrix/root/" + title + ".root").c_str());
    TFile* file_2017 = new TFile(("html/" + version + "/" + flag + "/2017.matrix/root/" + title + ".root").c_str());
    TFile* file_2018 = new TFile(("html/" + version + "/" + flag + "/2018.matrix/root/" + title + ".root").c_str());

    histo[8001]->Reset();

    TH1D* h = 0;

    h = (TH1D*)file_2016->Get((title + "_misid").c_str());
    if (h) {
      if (histo[8001]) {
        histo[8001]->Add(h);
      } else {
        histo[8001] = h;
        histo[8001]->SetDirectory(0);
      }
    }
    h = (TH1D*)file_2017->Get((title + "_misid").c_str());
    if (h) {
      if (histo[8001]) {
        histo[8001]->Add(h);
      } else {
        histo[8001] = h;
        histo[8001]->SetDirectory(0);
      }
    }
    h = (TH1D*)file_2018->Get((title + "_misid").c_str());
    if (h) {
      if (histo[8001]) {
        histo[8001]->Add(h);
      } else {
        histo[8001] = h;
        histo[8001]->SetDirectory(0);
      }
    }

    delete file_2016;
    delete file_2017;
    delete file_2018;
  }

  if (options.find("paper") != string::npos) title = title + "_paper";

  THStack* hstack_mc = new THStack("hstack_mc", "hstack_mc");
  TH1D* h_mc_sum = (TH1D*)histo[0]->Clone("h_mc_sum");
  h_mc_sum->Reset();

  for (map<int, TH1D*>::reverse_iterator it = histo.rbegin(); it != histo.rend(); it++) {
    int index = int(it->first);
    if (index > 0) {
      if (options.find("paper") == string::npos) hstack_mc->Add(histo[index]);
      h_mc_sum->Add(histo[index]);
    }
  }

  TH1D* h_ratio_mc = (TH1D*)h_mc_sum->Clone("h_ratio_mc");
  for (int i = 0; i < h_mc_sum->GetNbinsX()+2; i++) {
    h_mc_sum->SetBinError(i, 0.0);
  }
  h_ratio_mc->Divide(h_mc_sum);

  TH1D* h_ratio = (TH1D*)histo[0]->Clone("h_ratio");
  h_ratio->Divide(h_mc_sum);

  TLegend* legend = new TLegend(0.65, 0.44, 0.91, 0.88);
  legend->SetBorderSize(0);
  legend->SetEntrySeparation(0.01);
  legend->SetFillColor(0);
  legend->SetFillStyle(0);

  for (map<int, TH1D*>::iterator it = histo.begin(); it != histo.end(); it++) {
    int index = int(it->first);

    if (index == 0) {
      legend->AddEntry(histo[index], "Data", "p");
    }

    if (index == 10) {
      histo[index]->SetFillColor(kOrange+7);
      histo[index]->SetFillStyle(3254);
      legend->AddEntry(histo[index], "Z #gamma #gamma", "f");
    }
    if (index == 11) {
      histo[index]->SetFillColor(kOrange-4);
      histo[index]->SetFillStyle(3254);
      legend->AddEntry(histo[index], "Z #gamma", "f");
    }
    if (index == 21) {
      histo[index]->SetFillColor(kOrange-5);
      legend->AddEntry(histo[index], "W #gamma", "f");
    }
    if (index == 22) {
      histo[index]->SetFillColor(kOrange-6);
      legend->AddEntry(histo[index], "W #gamma #gamma", "f");
    }
    if (index == 31) {
      histo[index]->SetFillColor(kGreen+3);
      legend->AddEntry(histo[index], "VV #gamma", "f");
    }
    if (index == 41) {
      histo[index]->SetFillColor(kBlue+2);
      legend->AddEntry(histo[index], "TT #gamma", "f");
    }
    if (index == 42) {
      histo[index]->SetFillColor(kBlue+3);
      legend->AddEntry(histo[index], "TT #gamma #gamma", "f");
    }
    if (index == 51) {
      histo[index]->SetFillColor(kOrange+7);
      legend->AddEntry(histo[index], "T #gamma", "f");
    }
    if (index == 61) {
      histo[index]->SetFillColor(kRed+1);
      legend->AddEntry(histo[index], "#gamma Jets", "f");
    }

    if (index == 1010) {
      histo[index]->SetFillColor(kOrange+7);
      histo[index]->SetFillStyle(3254);
      legend->AddEntry(histo[index], "W #gamma #gamma", "f");
    }
    if (index == 1011) {
      histo[index]->SetFillColor(kOrange-4);
      histo[index]->SetFillStyle(3254);
      legend->AddEntry(histo[index], "W #gamma", "f");
    }
    if (index == 1021) {
      histo[index]->SetFillColor(kOrange-5);
      legend->AddEntry(histo[index], "Z #gamma", "f");
    }
    if (index == 1022) {
      histo[index]->SetFillColor(kOrange-6);
      legend->AddEntry(histo[index], "Z #gamma #gamma", "f");
    }
    if (index == 1031) {
      histo[index]->SetFillColor(kBlue+2);
      legend->AddEntry(histo[index], "TT #gamma", "f");
    }
    if (index == 1032) {
      histo[index]->SetFillColor(kBlue+3);
      legend->AddEntry(histo[index], "TT #gamma #gamma", "f");
    }
    if (index == 1041) {
      histo[index]->SetFillColor(kOrange+7);
      legend->AddEntry(histo[index], "T #gamma", "f");
    }
    if (index == 1051) {
      histo[index]->SetFillColor(kGreen+3);
      legend->AddEntry(histo[index], "VV #gamma", "f");
    }
    if (index == 1061) {
      histo[index]->SetFillColor(kRed+1);
      legend->AddEntry(histo[index], "#gamma Jets", "f");
    }

    if (index == 8001) {
      histo[index]->SetFillColor(kPink+4);
      legend->AddEntry(histo[index], "Jet MisID", "f");
    }
  }

  TH1D* h_irred = (TH1D*)histo[0]->Clone("h_irred");
  h_irred->Reset();

  if (title.find("h_WGG_") != string::npos) {
    h_irred->Add(histo[1011]);
    h_irred->Add(histo[1022]);
    h_irred->Add(histo[1031]);
    h_irred->Add(histo[1032]);
    h_irred->Add(histo[1041]);
    h_irred->Add(histo[1051]);
    h_irred->Add(histo[1061]);
  }
  if (title.find("h_ZGG_") != string::npos) {
    h_irred->Add(histo[11]);
    h_irred->Add(histo[21]);
    h_irred->Add(histo[31]);
    h_irred->Add(histo[41]);
    h_irred->Add(histo[42]);
    h_irred->Add(histo[51]);
    h_irred->Add(histo[61]);
  }

  if (options.find("paper") != string::npos) {
    legend->Clear();

    histo[0]->SetLineColor(kBlack);
    histo[0]->SetBinErrorOption(TH1::kPoisson);
    legend->AddEntry(histo[0], "Data", "p");

    if (title.find("h_WGG_") != string::npos) {
      hstack_mc->Add(histo[8001]);
      h_mc_sum->Add(histo[8001]);
      hstack_mc->Add(h_irred);
      h_mc_sum->Add(h_irred);
      hstack_mc->Add(histo[1021]);
      h_mc_sum->Add(histo[1021]);
      hstack_mc->Add(histo[1010]);
      h_mc_sum->Add(histo[1010]);

      histo[1010]->SetFillColor(kOrange+7);
      histo[1010]->SetFillStyle(3254);
      legend->AddEntry(histo[1010], "W#gamma#gamma", "f");

      histo[1021]->SetFillColorAlpha(kOrange, 0.3);
      legend->AddEntry(histo[1021], "Misid. electrons", "f");
    }
    if (title.find("h_ZGG_") != string::npos) {
      hstack_mc->Add(histo[8001]);
      h_mc_sum->Add(histo[8001]);
      hstack_mc->Add(h_irred);
      h_mc_sum->Add(h_irred);
      hstack_mc->Add(histo[10]);
      h_mc_sum->Add(histo[10]);

      histo[10]->SetFillColor(kOrange+7);
      histo[10]->SetFillStyle(3254);
      legend->AddEntry(histo[10], "Z#gamma#gamma", "f");
    }

    h_irred->SetFillColorAlpha(kGreen+3, 0.5);
    legend->AddEntry(h_irred, "Others", "f");

    histo[8001]->SetFillColor(kPink+4);
    legend->AddEntry(histo[8001], "Misid. jets", "f");
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
  if (options.find("paper") != string::npos) hstack_mc->GetYaxis()->SetTitle("Events / bin");
  hstack_mc->GetYaxis()->SetTitleSize(0.05);
  hstack_mc->GetYaxis()->SetTitleOffset(0.95);
  hstack_mc->GetYaxis()->SetLabelSize(0.045);

  histo[0]->SetMarkerColor(kBlack);
  histo[0]->SetMarkerStyle(20);
  histo[0]->SetMarkerSize(1.0);

  histo[0]->Draw("EXP0SAMES");

  legend->Draw();

  if (options.find("nolog") == string::npos) {
    if (h_mc_sum->GetMaximum() != 0) pad1->SetLogy();
  }

  if (options.find("nolog") != string::npos) TGaxis::SetExponentOffset(-0.05, 0.01, "y");

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
  } else if (tmp_title == "h_WGG_ele_pho0_pt_paper" || tmp_title == "h_WGG_muo_pho0_pt_paper") {
      h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma} [GeV]");
  } else if (tmp_title == "h_WGG_ele_pho1_pt_paper" || tmp_title == "h_WGG_muo_pho1_pt_paper") {
      h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma} [GeV]");
  } else if (tmp_title == "h_ZGG_ele_pho0_pt_paper" || tmp_title == "h_ZGG_muo_pho0_pt_paper") {
      h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma} [GeV]");
  } else if (tmp_title == "h_ZGG_ele_pho1_pt_paper" || tmp_title == "h_ZGG_muo_pho1_pt_paper") {
      h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma} [GeV]");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1_pt_paper" || tmp_title == "h_WGG_muo_pho0_pho1_pt_paper") {
      h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma#gamma} [GeV]");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1_pt_paper" || tmp_title == "h_ZGG_muo_pho0_pho1_pt_paper") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma#gamma} [GeV]");
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
  if (options.find("paper") != string::npos) h_ratio->GetYaxis()->SetTitle("Data / Prediction ");
  h_ratio->GetYaxis()->SetTitleSize(0.11);
  h_ratio->GetYaxis()->SetTitleOffset(0.43);
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

  if (options.find("identity0") != string::npos) title += "_identity0";
  if (options.find("identity1") != string::npos) title += "_identity1";
  if (options.find("closure0") != string::npos) title += "_closure0";
  if (options.find("closure1") != string::npos) title += "_closure1";

  c1->SaveAs(("html/" + version + "/" + flag + "/" + year + ".matrix/" + title + ".pdf").c_str());

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str(), kTRUE);
  }

  TFile* file = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + ".root").c_str());

  histo[0]->Write((title + "_data").c_str());
  histo[8001]->Write((title + "_misid").c_str());

  if (title.find("h_WGG_") != string::npos) {
    histo[1010]->Write((title + "_sig").c_str());
    histo[1021]->Write((title + "_egmisid").c_str());
    histo[1011]->Write((title + "_wg").c_str());
    histo[1021]->Write((title + "_zg").c_str());
    histo[1022]->Write((title + "_zgg").c_str());
    histo[1031]->Write((title + "_ttg").c_str());
    histo[1032]->Write((title + "_ttgg").c_str());
    histo[1041]->Write((title + "_tg").c_str());
    histo[1051]->Write((title + "_vvg").c_str());
    histo[1061]->Write((title + "_gj").c_str());
    h_irred->Write((title + "_irred").c_str());
  }

  if (title.find("h_ZGG_") != string::npos) {
    histo[10]->Write((title + "_sig").c_str());
    histo[11]->Write((title + "_zg").c_str());
    histo[21]->Write((title + "_wg").c_str());
    histo[31]->Write((title + "_vvg").c_str());
    histo[41]->Write((title + "_ttg").c_str());
    histo[42]->Write((title + "_ttgg").c_str());
    histo[51]->Write((title + "_tg").c_str());
    histo[61]->Write((title + "_gj").c_str());
    h_irred->Write((title + "_irred").c_str());
  }

  delete file;

  if (gROOT->IsBatch()) {
    for (map<int, TH1D*>::iterator it = histo.begin(); it != histo.end(); it++) {
      delete histo[it->first];
    }
    for (map<int, TH3D*>::iterator it = histo3.begin(); it != histo3.end(); it++) {
      delete histo3[it->first];
    }

    delete hstack_mc;
    delete h_mc_sum;
    delete h_ratio;
    delete h_ratio_mc;
    delete h_irred;

    delete legend;
    delete line;
    delete pad1;
    delete pad2;
    delete c1;
  }

  return 0;

}
