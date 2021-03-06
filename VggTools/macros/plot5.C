#include "plot5.h"

#ifndef CMS_lumi_C
#define CMS_lumi_C
#include "CMS_lumi.C"
#endif

int plot5(string plot="", string title="", string version="v00", string options="default", string flag="reference") {

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

  map<string, double> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets from " << "lumi.dat" << endl;

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
    Error("plot5", "plot map %s is EMPTY or MISSING !!", plot.c_str());
    return 1;
  }

  double lumi = 0.;
  double lumi2016 = 0.;
  double lumi2017 = 0.;
  double lumi2018 = 0.;

  for (multimap<string, double>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      if (lumiMap[it->first] != 0) {
        double var = (flag == "lumi_up") - (flag == "lumi_down");
        lumi = lumi + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2016") != string::npos) lumi2016 = lumi2016 + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2017") != string::npos) lumi2017 = lumi2017 + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2018") != string::npos) lumi2018 = lumi2018 + lumiMap[it->first] * (1.000 + 0.018 * var);
      } else {
        Warning("plot5", "luminosity for %s is ZERO !!", it->first.c_str());
      }
    }
  }

  if (lumi == 0) {
    Error("plot5", "total luminosity is ZERO !!");
    return 1;
  }

  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("sherpa") != string::npos) version = version + ".sherpa";
  if (options.find("default") != string::npos) version = version + ".default";

// #define USE_RUN2_AVERAGES

#if defined(USE_RUN2_AVERAGES)
  TFile* file1 = 0;
  if (flag == "jet_bkg_mc") {
    file1 = new TFile(("html/" + version + "/" + flag + "/" + year + "/root/" + title + ".root").c_str());
  } else {
    file1 = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + ".root").c_str());
  }
  TFile* file2 = new TFile(("html/" + version + "/" + flag + "/" + year + ".eff/root/" + title + ".root").c_str());

  if (file1->IsZombie()) {
    Error("plot5", "file %s is MISSING !!", file1->GetName());
    return 1;
  }
  if (file2->IsZombie()) {
    Error("plot5", "file %s is MISSING !!", file2->GetName());
    return 1;
  }

  TH1D* h_data = (TH1D*)file1->Get((title + "_data").c_str());
  TH1D* h_bkg = 0;
  if (flag == "jet_bkg_mc") {
    h_bkg = (TH1D*)file1->Get((title + "_bkg").c_str());
  } else {
    h_bkg = (TH1D*)file1->Get((title + "_misid").c_str());
    if (title.find("h_WGG_") != string::npos) {
      TH1D* h1 = (TH1D*)file1->Get((title + "_wg").c_str());
      h_bkg->Add(h1);
      TH1D* h2 = (TH1D*)file1->Get((title + "_zg").c_str());
      h_bkg->Add(h2);
      TH1D* h3 = (TH1D*)file1->Get((title + "_zgg").c_str());
      h_bkg->Add(h3);
      TH1D* h4 = (TH1D*)file1->Get((title + "_ttg").c_str());
      h_bkg->Add(h4);
      TH1D* h5 = (TH1D*)file1->Get((title + "_ttgg").c_str());
      h_bkg->Add(h5);
      TH1D* h6 = (TH1D*)file1->Get((title + "_tg").c_str());
      h_bkg->Add(h6);
      TH1D* h7 = (TH1D*)file1->Get((title + "_vvg").c_str());
      h_bkg->Add(h7);
      TH1D* h8 = (TH1D*)file1->Get((title + "_gj").c_str());
      h_bkg->Add(h8);
    }
    if (title.find("h_ZGG_") != string::npos) {
      TH1D* h1 = (TH1D*)file1->Get((title + "_wg").c_str());
      h_bkg->Add(h1);
      TH1D* h2 = (TH1D*)file1->Get((title + "_zg").c_str());
      h_bkg->Add(h2);
      TH1D* h3 = (TH1D*)file1->Get((title + "_ttg").c_str());
      h_bkg->Add(h3);
      TH1D* h4 = (TH1D*)file1->Get((title + "_ttgg").c_str());
      h_bkg->Add(h4);
      TH1D* h5 = (TH1D*)file1->Get((title + "_tg").c_str());
      h_bkg->Add(h5);
      TH1D* h6 = (TH1D*)file1->Get((title + "_vvg").c_str());
      h_bkg->Add(h6);
      TH1D* h7 = (TH1D*)file1->Get((title + "_gj").c_str());
      h_bkg->Add(h7);
    }
  }

  TH1D* h_mc_gen = (TH1D*)file2->Get((title + "_mc_gen").c_str());

  TH1D* h_mc_eff = (TH1D*)file2->Get((title + "_mc_eff_genmatch").c_str());

  h_data->SetDirectory(0);
  h_bkg->SetDirectory(0);
  h_mc_gen->SetDirectory(0);
  h_mc_eff->SetDirectory(0);

  delete file1;
  delete file2;

  h_data->Add(h_bkg, -1);

  for (int i = 0; i < h_data->GetNbinsX()+2; i++) {
    if (h_data->GetBinContent(i) < 0) {
      h_data->SetBinContent(i, 0);
      h_data->SetBinError(i, 0);
    }
  }

  TH1D* h_xsec_rec = (TH1D*)h_data->Clone("h_xsec_rec");

  h_xsec_rec->Divide(h_mc_eff);
  h_xsec_rec->Scale(1. / (1000. * lumi), "width");

  TH1D* h_xsec_mc_gen = (TH1D*)h_mc_gen->Clone("h_xsec_mc_gen");

  h_xsec_mc_gen->Scale(1. / (1000. * lumi), "width");
#else
  TFile* file1_2016 = 0;
  TFile* file2_2016 = 0;
  TFile* file1_2017 = 0;
  TFile* file2_2017 = 0;
  TFile* file1_2018 = 0;
  TFile* file2_2018 = 0;

  if (plot.find("2016") != string::npos || plot.find("Run2") != string::npos) {
    if (flag == "jet_bkg_mc") {
      file1_2016 = new TFile(("html/" + version + "/" + flag + "/2016/root/" + title + ".root").c_str());
    } else {
      file1_2016 = new TFile(("html/" + version + "/" + flag + "/2016.matrix/root/" + title + ".root").c_str());
    }
    if (file1_2016->IsZombie()) {
      Error("plot5", "file %s is MISSING !!", file1_2016->GetName());
      return 1;
    }
    file2_2016 = new TFile(("html/" + version + "/" + flag + "/2016.eff/root/" + title + ".root").c_str());
    if (file2_2016->IsZombie()) {
      Error("plot5", "file %s is MISSING !!", file2_2016->GetName());
      return 1;
    }
  }
  if (plot.find("2017") != string::npos || plot.find("Run2") != string::npos) {
    if (flag == "jet_bkg_mc") {
      file1_2017 = new TFile(("html/" + version + "/" + flag + "/2017/root/" + title + ".root").c_str());
    } else {
      file1_2017 = new TFile(("html/" + version + "/" + flag + "/2017.matrix/root/" + title + ".root").c_str());
    }
    if (file1_2017->IsZombie()) {
      Error("plot5", "file %s is MISSING !!", file1_2017->GetName());
      return 1;
    }
    file2_2017 = new TFile(("html/" + version + "/" + flag + "/2017.eff/root/" + title + ".root").c_str());
    if (file2_2017->IsZombie()) {
      Error("plot5", "file %s is MISSING !!", file2_2017->GetName());
      return 1;
    }
  }
  if (plot.find("2018") != string::npos || plot.find("Run2") != string::npos) {
    if (flag == "jet_bkg_mc") {
      file1_2018 = new TFile(("html/" + version + "/" + flag + "/2018/root/" + title + ".root").c_str());
    } else {
      file1_2018 = new TFile(("html/" + version + "/" + flag + "/2018.matrix/root/" + title + ".root").c_str());
    }
    if (file1_2018->IsZombie()) {
      Error("plot5", "file %s is MISSING !!", file1_2018->GetName());
      return 1;
    }
    file2_2018 = new TFile(("html/" + version + "/" + flag + "/2018.eff/root/" + title + ".root").c_str());
    if (file2_2018->IsZombie()) {
      Error("plot5", "file %s is MISSING !!", file2_2018->GetName());
      return 1;
    }
  }

  TH1D* h_data_2016 = 0;
  TH1D* h_data_2017 = 0;
  TH1D* h_data_2018 = 0;

  if (file1_2016) h_data_2016 = (TH1D*)file1_2016->Get((title + "_data").c_str());
  if (file1_2017) h_data_2017 = (TH1D*)file1_2017->Get((title + "_data").c_str());
  if (file1_2018) h_data_2018 = (TH1D*)file1_2018->Get((title + "_data").c_str());

  TH1D* h_bkg_2016 = 0;
  TH1D* h_bkg_2017 = 0;
  TH1D* h_bkg_2018 = 0;

  if (flag == "jet_bkg_mc") {
    if (file1_2016) h_bkg_2016 = (TH1D*)file1_2016->Get((title + "_bkg").c_str());
    if (file1_2017) h_bkg_2017 = (TH1D*)file1_2017->Get((title + "_bkg").c_str());
    if (file1_2018) h_bkg_2018 = (TH1D*)file1_2018->Get((title + "_bkg").c_str());
  } else {
    if (file1_2016) {
      h_bkg_2016 = (TH1D*)file1_2016->Get((title + "_misid").c_str());
    }
    if (file1_2017) {
      h_bkg_2017 = (TH1D*)file1_2017->Get((title + "_misid").c_str());
    }
    if (file1_2018) {
      h_bkg_2018 = (TH1D*)file1_2018->Get((title + "_misid").c_str());
    }

    if (file1_2016) {
      if (title.find("h_WGG_") != string::npos) {
        TH1D* h1 = (TH1D*)file1_2016->Get((title + "_wg").c_str());
        h_bkg_2016->Add(h1);
        TH1D* h2 = (TH1D*)file1_2016->Get((title + "_zg").c_str());
        h_bkg_2016->Add(h2);
        TH1D* h3 = (TH1D*)file1_2016->Get((title + "_zgg").c_str());
        h_bkg_2016->Add(h3);
        TH1D* h4 = (TH1D*)file1_2016->Get((title + "_ttg").c_str());
        h_bkg_2016->Add(h4);
        TH1D* h5 = (TH1D*)file1_2016->Get((title + "_ttgg").c_str());
        h_bkg_2016->Add(h5);
        TH1D* h6 = (TH1D*)file1_2016->Get((title + "_tg").c_str());
        h_bkg_2016->Add(h6);
        TH1D* h7 = (TH1D*)file1_2016->Get((title + "_vvg").c_str());
        h_bkg_2016->Add(h7);
        TH1D* h8 = (TH1D*)file1_2016->Get((title + "_gj").c_str());
        h_bkg_2016->Add(h8);
      }
      if (title.find("h_ZGG_") != string::npos) {
        TH1D* h1 = (TH1D*)file1_2016->Get((title + "_wg").c_str());
        h_bkg_2016->Add(h1);
        TH1D* h2 = (TH1D*)file1_2016->Get((title + "_zg").c_str());
        h_bkg_2016->Add(h2);
        TH1D* h3 = (TH1D*)file1_2016->Get((title + "_ttg").c_str());
        h_bkg_2016->Add(h3);
        TH1D* h4 = (TH1D*)file1_2016->Get((title + "_ttgg").c_str());
        h_bkg_2016->Add(h4);
        TH1D* h5 = (TH1D*)file1_2016->Get((title + "_tg").c_str());
        h_bkg_2016->Add(h5);
        TH1D* h6 = (TH1D*)file1_2016->Get((title + "_vvg").c_str());
        h_bkg_2016->Add(h6);
        TH1D* h7 = (TH1D*)file1_2016->Get((title + "_gj").c_str());
        h_bkg_2016->Add(h7);
      }
    }

    if (file1_2017) {
      if (title.find("h_WGG_") != string::npos) {
        TH1D* h1 = (TH1D*)file1_2017->Get((title + "_wg").c_str());
        h_bkg_2017->Add(h1);
        TH1D* h2 = (TH1D*)file1_2017->Get((title + "_zg").c_str());
        h_bkg_2017->Add(h2);
        TH1D* h3 = (TH1D*)file1_2017->Get((title + "_zgg").c_str());
        h_bkg_2017->Add(h3);
        TH1D* h4 = (TH1D*)file1_2017->Get((title + "_ttg").c_str());
        h_bkg_2017->Add(h4);
        TH1D* h5 = (TH1D*)file1_2017->Get((title + "_ttgg").c_str());
        h_bkg_2017->Add(h5);
        TH1D* h6 = (TH1D*)file1_2017->Get((title + "_tg").c_str());
        h_bkg_2017->Add(h6);
        TH1D* h7 = (TH1D*)file1_2017->Get((title + "_vvg").c_str());
        h_bkg_2017->Add(h7);
        TH1D* h8 = (TH1D*)file1_2017->Get((title + "_gj").c_str());
        h_bkg_2017->Add(h8);
      }
      if (title.find("h_ZGG_") != string::npos) {
        TH1D* h1 = (TH1D*)file1_2017->Get((title + "_wg").c_str());
        h_bkg_2017->Add(h1);
        TH1D* h2 = (TH1D*)file1_2017->Get((title + "_zg").c_str());
        h_bkg_2017->Add(h2);
        TH1D* h3 = (TH1D*)file1_2017->Get((title + "_ttg").c_str());
        h_bkg_2017->Add(h3);
        TH1D* h4 = (TH1D*)file1_2017->Get((title + "_ttgg").c_str());
        h_bkg_2017->Add(h4);
        TH1D* h5 = (TH1D*)file1_2017->Get((title + "_tg").c_str());
        h_bkg_2017->Add(h5);
        TH1D* h6 = (TH1D*)file1_2017->Get((title + "_vvg").c_str());
        h_bkg_2017->Add(h6);
        TH1D* h7 = (TH1D*)file1_2017->Get((title + "_gj").c_str());
        h_bkg_2017->Add(h7);
      }
    }

    if (file1_2018) {
      if (title.find("h_WGG_") != string::npos) {
        TH1D* h1 = (TH1D*)file1_2018->Get((title + "_wg").c_str());
        h_bkg_2018->Add(h1);
        TH1D* h2 = (TH1D*)file1_2018->Get((title + "_zg").c_str());
        h_bkg_2018->Add(h2);
        TH1D* h3 = (TH1D*)file1_2018->Get((title + "_zgg").c_str());
        h_bkg_2018->Add(h3);
        TH1D* h4 = (TH1D*)file1_2018->Get((title + "_ttg").c_str());
        h_bkg_2018->Add(h4);
        TH1D* h5 = (TH1D*)file1_2018->Get((title + "_ttgg").c_str());
        h_bkg_2018->Add(h5);
        TH1D* h6 = (TH1D*)file1_2018->Get((title + "_tg").c_str());
        h_bkg_2018->Add(h6);
        TH1D* h7 = (TH1D*)file1_2018->Get((title + "_vvg").c_str());
        h_bkg_2018->Add(h7);
        TH1D* h8 = (TH1D*)file1_2018->Get((title + "_gj").c_str());
        h_bkg_2018->Add(h8);
      }
      if (title.find("h_ZGG_") != string::npos) {
        TH1D* h1 = (TH1D*)file1_2018->Get((title + "_wg").c_str());
        h_bkg_2018->Add(h1);
        TH1D* h2 = (TH1D*)file1_2018->Get((title + "_zg").c_str());
        h_bkg_2018->Add(h2);
        TH1D* h3 = (TH1D*)file1_2018->Get((title + "_ttg").c_str());
        h_bkg_2018->Add(h3);
        TH1D* h4 = (TH1D*)file1_2018->Get((title + "_ttgg").c_str());
        h_bkg_2018->Add(h4);
        TH1D* h5 = (TH1D*)file1_2018->Get((title + "_tg").c_str());
        h_bkg_2018->Add(h5);
        TH1D* h6 = (TH1D*)file1_2018->Get((title + "_vvg").c_str());
        h_bkg_2018->Add(h6);
        TH1D* h7 = (TH1D*)file1_2018->Get((title + "_gj").c_str());
        h_bkg_2018->Add(h7);
      }
    }
  }

  TH1D* h_mc_gen_2016 = 0;
  TH1D* h_mc_gen_2017 = 0;
  TH1D* h_mc_gen_2018 = 0;

  if (file2_2016) h_mc_gen_2016 = (TH1D*)file2_2016->Get((title + "_mc_gen").c_str());
  if (file2_2017) h_mc_gen_2017 = (TH1D*)file2_2017->Get((title + "_mc_gen").c_str());
  if (file2_2018) h_mc_gen_2018 = (TH1D*)file2_2018->Get((title + "_mc_gen").c_str());

  TH1D* h_mc_eff_2016 = 0;
  TH1D* h_mc_eff_2017 = 0;
  TH1D* h_mc_eff_2018 = 0;

  if (file2_2016) h_mc_eff_2016 = (TH1D*)file2_2016->Get((title + "_mc_eff_genmatch").c_str());
  if (file2_2017) h_mc_eff_2017 = (TH1D*)file2_2017->Get((title + "_mc_eff_genmatch").c_str());
  if (file2_2018) h_mc_eff_2018 = (TH1D*)file2_2018->Get((title + "_mc_eff_genmatch").c_str());

  if (file1_2016) {
    h_data_2016->SetDirectory(0);
    h_bkg_2016->SetDirectory(0);
    delete file1_2016;
  }
  if (file2_2016) {
    h_mc_gen_2016->SetDirectory(0);
    h_mc_eff_2016->SetDirectory(0);
    delete file2_2016;
  }

  if (file1_2017) {
    h_data_2017->SetDirectory(0);
    h_bkg_2017->SetDirectory(0);
    delete file1_2017;
  }
  if (file2_2017) {
    h_mc_gen_2017->SetDirectory(0);
    h_mc_eff_2017->SetDirectory(0);
    delete file2_2017;
  }

  if (file1_2018) {
    h_data_2018->SetDirectory(0);
    h_bkg_2018->SetDirectory(0);
    delete file1_2018;
  }
    if (file2_2018) {
    h_mc_gen_2018->SetDirectory(0);
    h_mc_eff_2018->SetDirectory(0);
    delete file2_2018;
  }

  if (h_data_2016 && h_bkg_2016 && h_mc_eff_2016) {
    h_data_2016->Add(h_bkg_2016, -1);
    for (int i = 0; i < h_data_2016->GetNbinsX()+2; i++) {
      if (h_data_2016->GetBinContent(i) < 0) {
        h_data_2016->SetBinContent(i, 0);
        h_data_2016->SetBinError(i, 0);
      }
    }
    h_data_2016->Divide(h_mc_eff_2016);
  }

  if (h_data_2017 && h_bkg_2017 && h_mc_eff_2017) {
    h_data_2017->Add(h_bkg_2017, -1);
    for (int i = 0; i < h_data_2017->GetNbinsX()+2; i++) {
      if (h_data_2017->GetBinContent(i) < 0) {
        h_data_2017->SetBinContent(i, 0);
        h_data_2017->SetBinError(i, 0);
      }
    }
    h_data_2017->Divide(h_mc_eff_2017);
  }

  if (h_data_2018 && h_bkg_2018 && h_mc_eff_2018) {
    h_data_2018->Add(h_bkg_2018, -1);
    for (int i = 0; i < h_data_2018->GetNbinsX()+2; i++) {
      if (h_data_2018->GetBinContent(i) < 0) {
        h_data_2018->SetBinContent(i, 0);
        h_data_2018->SetBinError(i, 0);
      }
    }
    h_data_2018->Divide(h_mc_eff_2018);
  }

  TH1D* h_xsec_rec = 0;

  if (!h_xsec_rec && h_data_2016) h_xsec_rec = (TH1D*)h_data_2016->Clone("h_xsec_rec");
  if (!h_xsec_rec && h_data_2017) h_xsec_rec = (TH1D*)h_data_2017->Clone("h_xsec_rec");
  if (!h_xsec_rec && h_data_2018) h_xsec_rec = (TH1D*)h_data_2018->Clone("h_xsec_rec");

  h_xsec_rec->Reset();
  if (h_data_2016) h_xsec_rec->Add(h_data_2016);
  if (h_data_2017) h_xsec_rec->Add(h_data_2017);
  if (h_data_2018) h_xsec_rec->Add(h_data_2018);

  h_xsec_rec->Scale(1. / (1000. * lumi), "width");

  TH1D* h_xsec_mc_gen = 0;

  if (!h_xsec_mc_gen && h_mc_gen_2016) h_xsec_mc_gen = (TH1D*)h_mc_gen_2016->Clone("h_xsec_mc_gen");
  if (!h_xsec_mc_gen && h_mc_gen_2017) h_xsec_mc_gen = (TH1D*)h_mc_gen_2017->Clone("h_xsec_mc_gen");
  if (!h_xsec_mc_gen && h_mc_gen_2018) h_xsec_mc_gen = (TH1D*)h_mc_gen_2018->Clone("h_xsec_mc_gen");

  h_xsec_mc_gen->Reset();
  if (h_mc_gen_2016) h_xsec_mc_gen->Add(h_mc_gen_2016);
  if (h_mc_gen_2017) h_xsec_mc_gen->Add(h_mc_gen_2017);
  if (h_mc_gen_2018) h_xsec_mc_gen->Add(h_mc_gen_2018);

  h_xsec_mc_gen->Scale(1. / (1000. * lumi), "width");
#endif // defined(USE_RUN2_AVERAGES)

  TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
  c1->cd();

  TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
  pad1->SetBottomMargin(0.001);
  pad1->Draw();
  pad1->cd();

  h_xsec_mc_gen->SetMaximum(10.*TMath::Max(h_xsec_mc_gen->GetBinContent(h_xsec_mc_gen->GetMaximumBin()), h_xsec_rec->GetBinContent(h_xsec_rec->GetMaximumBin())));
  h_xsec_mc_gen->SetMinimum(TMath::Max(5.e-9, 0.1*TMath::Min(h_xsec_mc_gen->GetBinContent(h_xsec_mc_gen->GetMinimumBin()), h_xsec_rec->GetBinContent(h_xsec_rec->GetMinimumBin()))));

  pad1->SetLogy();

  h_xsec_mc_gen->SetTitle("");
  h_xsec_mc_gen->SetStats(kFALSE);

  h_xsec_mc_gen->SetLineColorAlpha(kBlue-4, 0.5);
  h_xsec_mc_gen->SetLineWidth(2);
  h_xsec_mc_gen->SetFillColorAlpha(kBlue-4, 0.5);
  h_xsec_mc_gen->SetMarkerColorAlpha(kBlue-4, 0.5);

  h_xsec_mc_gen->GetXaxis()->SetTitleOffset(0.7);
  h_xsec_mc_gen->GetXaxis()->SetLabelFont(42);
  h_xsec_mc_gen->GetXaxis()->SetLabelSize(0.08);

  h_xsec_mc_gen->GetYaxis()->SetTitleSize(0.05);
  h_xsec_mc_gen->GetYaxis()->SetTitleOffset(0.95);
  h_xsec_mc_gen->GetYaxis()->SetLabelSize(0.045);

  h_xsec_mc_gen->Draw("E2");

  TH1D* h_xsec_mc_gen1 = (TH1D*)h_xsec_mc_gen->Clone("h_xsec_mc_gen1");
  for (int i = 0; i < h_xsec_mc_gen1->GetNbinsX()+2; i++) {
    h_xsec_mc_gen1->SetBinError(i, 1e-12);
  }
  h_xsec_mc_gen1->SetLineWidth(4);
  h_xsec_mc_gen1->Draw("SAME");

  h_xsec_rec->SetTitle("");
  h_xsec_rec->SetStats(kFALSE);

  h_xsec_rec->SetLineColor(kBlack);
  h_xsec_rec->SetLineWidth(1);
  h_xsec_rec->SetFillColor(kBlack);
  h_xsec_rec->SetMarkerColor(kBlack);
  h_xsec_rec->SetMarkerStyle(24);
  h_xsec_rec->SetMarkerSize(0.7);

  h_xsec_rec->SetMarkerColor(kBlack);

  h_xsec_rec->Draw("E0PX0SAME");
  h_xsec_rec->Draw("E1PX0SAME");

  pad1->Update();
  c1->Update();
  c1->cd();

  TH1D* h_ratio_rec = (TH1D*)h_xsec_rec->Clone("h_ratio_rec");

  TH1D* h_xsec_mc_gen2 = (TH1D*)h_xsec_mc_gen->Clone("h_xsec_mc_gen2");
  for (int i = 0; i < h_xsec_mc_gen2->GetNbinsX()+2; i++) {
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

  h_ratio_gen->GetXaxis()->SetTitleFont(42);
  h_ratio_gen->GetXaxis()->SetTitleSize(0.11);
  h_ratio_gen->GetXaxis()->SetTitleOffset(1.0);
  h_ratio_gen->GetXaxis()->SetLabelFont(42);
  h_ratio_gen->GetXaxis()->SetLabelSize(0.10);

  h_ratio_gen->GetYaxis()->SetTitle("Data/Theory");
  h_ratio_gen->GetYaxis()->SetTitleSize(0.11);
  h_ratio_gen->GetYaxis()->SetTitleOffset(0.43);
  h_ratio_gen->GetYaxis()->SetLabelSize(0.10);
  h_ratio_gen->GetYaxis()->SetNdivisions(505);
  h_ratio_gen->GetYaxis()->SetRangeUser(0.5, 1.5);

  h_ratio_gen->GetXaxis()->SetNdivisions(1003);
  h_ratio_gen->GetXaxis()->SetTickLength(0.1);

  string tmp_title = title;

  if (tmp_title == "h_WGG_ele_pho1_eta" || tmp_title == "h_WGG_muo_pho1_eta") {
    h_ratio_gen->GetXaxis()->SetTitle("#eta^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#eta^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho1_phi" || tmp_title == "h_WGG_muo_pho1_phi") {
    h_ratio_gen->GetXaxis()->SetTitle("#phi^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#phi^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho1_r9" || tmp_title == "h_WGG_muo_pho1_r9") {
    h_ratio_gen->GetXaxis()->SetTitle("R_{9}^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dR_{9}^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho0_sieie" || tmp_title == "h_WGG_muo_pho0_sieie") {
    h_ratio_gen->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma_{1}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#sigma_{i#etai#eta}^{#gamma_{1}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho1_sieie" || tmp_title == "h_WGG_muo_pho1_sieie") {
    h_ratio_gen->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#sigma_{i#etai#eta}^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho1_jet0_dR" || tmp_title == "h_WGG_muo_pho1_jet0_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{j#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#DeltaR^{j#gamma_{2}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho0_mva" || tmp_title == "h_WGG_muo_pho0_mva") {
    h_ratio_gen->GetXaxis()->SetTitle("mva^{#gamma_{1}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dmva^{#gamma_{1}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho1_mva" || tmp_title == "h_WGG_muo_pho1_mva") {
    h_ratio_gen->GetXaxis()->SetTitle("mva^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dmva^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho1_pf_iso_all" || tmp_title == "h_WGG_muo_pf_iso_all") {
    h_ratio_gen->GetXaxis()->SetTitle("Iso_{all}^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dIso_{all}^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho1_pf_iso_chg" || tmp_title == "h_WGG_muo_pf_iso_chg") {
    h_ratio_gen->GetXaxis()->SetTitle("Iso_{chg}^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dIso_{chg}^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho1_dR" || tmp_title == "h_WGG_muo_pho1_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{l#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#DeltaR^{l#gamma_{2}} [pb]");
  } else if (tmp_title == "h_WGG_ele_pho0_pt" || tmp_title == "h_WGG_muo_pho0_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma_{1}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dp_{T}^{#gamma_{1}} [pb/GeV]");
  } else if (tmp_title == "h_WGG_ele_pho1_pt" || tmp_title == "h_WGG_muo_pho1_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dp_{T}^{#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_WGG_ele_ele0_pt" || tmp_title == "h_WGG_muo_muo0_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{l_{1}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dp_{T}^{l_{1}} [pb/GeV]");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1_dR" || tmp_title == "h_WGG_muo_pho0_pho1_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{#gamma_{1}#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#DeltaR^{#gamma_{1}#gamma_{2}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho1_eta" || tmp_title == "h_ZGG_muo_pho1_eta") {
    h_ratio_gen->GetXaxis()->SetTitle("#eta^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#eta^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho1_phi" || tmp_title == "h_ZGG_muo_pho1_phi") {
    h_ratio_gen->GetXaxis()->SetTitle("#phi^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#phi^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho1_r9" || tmp_title == "h_ZGG_muo_pho1_r9") {
    h_ratio_gen->GetXaxis()->SetTitle("R_{9}^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dR_{9}^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho0_sieie" || tmp_title == "h_ZGG_muo_pho0_sieie") {
    h_ratio_gen->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma_{1}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#sigma_{i#etai#eta}^{#gamma_{1}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho1_sieie" || tmp_title == "h_ZGG_muo_pho1_sieie") {
    h_ratio_gen->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#sigma_{i#etai#eta}^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho1_jet0_dR" || tmp_title == "h_ZGG_muo_pho1_jet0_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{j#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#DeltaR^{j#gamma_{2}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho0_mva" || tmp_title == "h_ZGG_muo_pho0_mva") {
    h_ratio_gen->GetXaxis()->SetTitle("mva^{#gamma_{1}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dmva^{#gamma_{1}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho1_mva" || tmp_title == "h_ZGG_muo_pho1_mva") {
    h_ratio_gen->GetXaxis()->SetTitle("mva^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dmva^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho1_pf_iso_all" || tmp_title == "h_ZGG_muo_pf_iso_all") {
    h_ratio_gen->GetXaxis()->SetTitle("Iso_{all}^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dIso_{all}^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho1_pf_iso_chg" || tmp_title == "h_ZGG_muo_pf_iso_chg") {
    h_ratio_gen->GetXaxis()->SetTitle("Iso_{chg}^{#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dIso_{chg}^{#gamma_{2}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho1_dR" || tmp_title == "h_ZGG_muo_pho1_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{l#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#DeltaR^{l#gamma_{2}} [pb]");
  } else if (tmp_title == "h_ZGG_ele_pho0_pt" || tmp_title == "h_ZGG_muo_pho0_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma_{1}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dp_{T}^{#gamma_{1}} [pb/GeV]");
  } else if (tmp_title == "h_ZGG_ele_pho1_pt" || tmp_title == "h_ZGG_muo_pho1_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dp_{T}^{#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1_dR" || tmp_title == "h_ZGG_muo_pho0_pho1_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{#gamma_{1}#gamma_{2}}");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d#DeltaR^{#gamma_{1}#gamma_{2}} [pb]");
  } else if (tmp_title == "h_WGG_ele" || tmp_title == "h_WGG_muo") {
    h_ratio_gen->GetXaxis()->SetTitle("M_{T} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM_{T} [pb/GeV]");
  } else if (tmp_title == "h_ZGG_ele" || tmp_title == "h_ZGG_muo") {
    h_ratio_gen->GetXaxis()->SetTitle("M_{ll} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM_{ll} [pb/GeV]");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1_pt" || tmp_title == "h_WGG_muo_pho0_pho1_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma_{1}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dp_{T}^{#gamma_{1}#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1" || tmp_title == "h_WGG_muo_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{#gamma_{1}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM^{#gamma_{1}#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_WGG_ele_ele0_pho0" || tmp_title == "h_WGG_muo_muo0_pho0") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l_{1}#gamma_{1}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM^{l_{1}#gamma_{1}} [pb/GeV]");
  } else if (tmp_title == "h_WGG_ele_ele0_pho1" || tmp_title == "h_WGG_muo_muo0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l_{1}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM^{l_{1}#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_WGG_ele_ele0_pho0_pho1" || tmp_title == "h_WGG_muo_muo0_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l_{1}#gamma_{1}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM^{l_{1}#gamma_{1}#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1_pt" || tmp_title == "h_ZGG_muo_pho0_pho1_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma_{1}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dp_{T}^{#gamma_{1}#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1" || tmp_title == "h_ZGG_muo_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{#gamma_{1}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM^{#gamma_{1}#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_ZGG_ele_ele0_pho1" || tmp_title == "h_ZGG_muo_muo0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l_{1}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM^{l_{1}#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_ZGG_ele_ele1_pho1" || tmp_title == "h_ZGG_muo_muo1_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l_{2}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM^{l#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_ZGG_ele_ele0_pho0_pho1" || tmp_title == "h_ZGG_muo_muo0_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{_{1}l#gamma_{1}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM^{l_{1}#gamma_{1}#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_ZGG_ele_ele1_pho0_pho1" || tmp_title == "h_ZGG_muo_muo1_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l_{2}#gamma_{1}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM^{l#gamma_{1}#gamma_{2}} [pb/GeV]");
  } else if (tmp_title == "h_ZGG_ele_ele0_ele1_pho0_pho1" || tmp_title == "h_ZGG_muo_muo0_muo1_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l_{1}l_{2}#gamma_{1}#gamma_{2}} [GeV]");
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / dM^{l_{1}l_{2}#gamma_{1}#gamma_{2}} [pb/GeV]");
  } else {
    tmp_title.erase(0, 2);
    h_ratio_gen->GetXaxis()->SetTitle(tmp_title.c_str());
    h_xsec_mc_gen->GetYaxis()->SetTitle("d#sigma / d?");
  }

  h_ratio_gen->Draw("E2");

  pad2->Update();
  TLine* line = new TLine(pad2->GetUxmax(), 1.0, pad2->GetUxmin(), 1.0);
  line->SetLineColorAlpha(kBlue-4, 0.5);
  line->SetLineWidth(2);
  line->Draw();

  h_ratio_rec->SetLineColor(kBlack);
  h_ratio_rec->SetLineWidth(1);
  h_ratio_rec->SetFillColor(kBlack);
  h_ratio_rec->SetMarkerColor(kBlack);
  h_ratio_rec->SetMarkerStyle(24);
  h_ratio_rec->SetMarkerSize(0.7);

  h_ratio_rec->Draw("E0PX0SAME");
  h_ratio_rec->Draw("E1PX0SAME");

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
      label->DrawLatex(0.55, 0.75, "p_{T}^{e} > 30 GeV, #||{#eta^{e}} < 2.5");
    }
    if (plot.find("muo") != string::npos) {
      label->DrawLatex(0.55, 0.80, "W #rightarrow #mu#nu");
      label->DrawLatex(0.55, 0.75, "p_{T}^{#mu} > 30 GeV, #||{#eta^{#mu}} < 2.5");
    }
    label->DrawLatex(0.55, 0.69, "p_{T}^{#gamma} > 20 GeV, #||{#eta^{#gamma}} < 2.5");
  }
  if (plot.find("Z") != string::npos) {
    label->DrawLatex(0.55, 0.85, "Z, Z#gamma, Z#gamma#gamma selection");
    if (plot.find("ele") != string::npos) {
      label->DrawLatex(0.55, 0.80, "Z #rightarrow ee");
      label->DrawLatex(0.55, 0.75, "p_{T}^{e#scale[0.8]{1}} > 30 GeV, p_{T}^{e#scale[0.8]{2}} > 15 GeV, #||{#eta^{e}} < 2.5");
    }
    if (plot.find("muo") != string::npos) {
      label->DrawLatex(0.55, 0.80, "Z #rightarrow #mu#mu");
      label->DrawLatex(0.55, 0.75, "p_{T}^{#mu#scale[0.8]{1}} > 30 GeV, p_{T}^{#mu#scale[0.8]{2}} > 15 GeV, #||{#eta^{#mu}} < 2.5");
    }
    label->DrawLatex(0.55, 0.69, "p_{T}^{#gamma} > 20 GeV, #||{#eta^{#gamma}} < 2.5");
  }

  label->Draw("same");

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".xsec/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".xsec/").c_str(), kTRUE);
  }

  c1->SaveAs(("html/" + version + "/" + flag + "/" + year + ".xsec/" + title + ".pdf").c_str());

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".xsec/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".xsec/root/").c_str(), kTRUE);
  }

  TFile* file = new TFile(("html/" + version + "/" + flag + "/" + year + ".xsec/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + flag + "/" + year + ".xsec/root/" + title + ".root").c_str());

  h_xsec_rec->Write((title + "_xsec_rec").c_str());
  h_xsec_mc_gen->Write((title + "_xsec_mc_gen").c_str());

  delete file;

  double xsec_data = 0.;
  double xsec_stat_data = 0.;

  xsec_data = h_xsec_rec->IntegralAndError(0, h_xsec_rec->GetNbinsX()+1, xsec_stat_data, "width");

  ofstream out;
  out.open(("html/" + version + "/" + flag + "/" + year + ".xsec/root/" + title + ".dat").c_str());
  Info("File::Open", "dat file %s has been created", ("html/" + version + "/" + flag + "/" + year + ".xsec/root/" + title + ".dat").c_str());

  out << title  << " (" << h_xsec_mc_gen->Integral(0, h_xsec_mc_gen->GetNbinsX()+1, "width") << ")" << endl;
  out << std::fixed << std::setprecision(4);
  out << std::setw(29) << "data";
  out << endl;
  out << std::setw(29) << "stat";
  out << endl;

  for (int i = 0; i < h_xsec_rec->GetNbinsX()+2; i++) {
    out << std::fixed;
    out << std::setw(2) << i;
    out << " ";
    out << std::setprecision(8);
    out << std::setw(12) << h_xsec_rec->GetBinContent(i) * h_xsec_rec->GetBinWidth(i);
    out << " +- ";
    out << std::setw(10) << h_xsec_rec->GetBinError(i) * h_xsec_rec->GetBinWidth(i);
    out << endl;
  }

  out << "tot";
  out << std::setprecision(8);
  out << std::setw(12) << xsec_data;
  out << " +- ";
  out << std::setw(10) << xsec_stat_data;
  out << endl;

  out.close();

  if (gROOT->IsBatch()) {
#if defined(USE_RUN2_AVERAGES)
    delete h_data;
    delete h_bkg;
    delete h_mc_gen;
    delete h_mc_eff;
#else
    delete h_data_2016;
    delete h_bkg_2016;
    delete h_mc_gen_2016;
    delete h_mc_eff_2016;
    delete h_data_2017;
    delete h_bkg_2017;
    delete h_mc_gen_2017;
    delete h_mc_eff_2017;
    delete h_data_2018;
    delete h_bkg_2018;
    delete h_mc_gen_2018;
    delete h_mc_eff_2018;
#endif
    delete h_xsec_rec;
    delete h_xsec_mc_gen;
    delete h_xsec_mc_gen1;
    delete h_xsec_mc_gen2;
    delete h_ratio_rec;
    delete h_ratio_gen;

    delete label;
    delete line;
    delete pad1;
    delete pad2;
    delete c1;
  }

  return 0;

}
