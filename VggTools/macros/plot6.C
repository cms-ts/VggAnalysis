#include "plot6.h"

#include "CMS_lumi.C"

void plot6(string plot="", string title="", string version="v00", string options="") {

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
        if (it->first.find("Run2016") != string::npos) lumi2016 = lumi2016 + lumiMap[it->first];
        if (it->first.find("Run2017") != string::npos) lumi2017 = lumi2017 + lumiMap[it->first];
        if (it->first.find("Run2018") != string::npos) lumi2018 = lumi2018 + lumiMap[it->first];
      } else {
        cout << "WARNING: luminosity for " << it->first << " is ZERO !!" << endl;
      }
    }
  }

  if (lumi == 0) {
    cout << "ERROR: total luminosity is ZERO !!" << endl;
    return;
  }

  double lumierror = (lumi2016 * 2.5 + lumi2017 * 2.3 + lumi2018 * 2.5) / lumi;
  if (plot.find("Run2") != string::npos) lumierror = 1.8;

  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("default") != string::npos) version = version + ".default";

  vector<string> flags;

  flags.push_back("reference");

  flags.push_back("bkg_stat");
  flags.push_back("jet_misid_stat");

  flags.push_back("pileup_up");
  flags.push_back("pileup_down");

  flags.push_back("jec_up_2016");
  flags.push_back("jec_up_2017");
  flags.push_back("jec_up_2018");
  flags.push_back("jec_down_2016");
  flags.push_back("jec_down_2017");
  flags.push_back("jec_down_2018");

  flags.push_back("jer_up_2016");
  flags.push_back("jer_up_2017");
  flags.push_back("jer_up_2018");
  flags.push_back("jer_down_2016");
  flags.push_back("jer_down_2017");
  flags.push_back("jer_down_2018");

  flags.push_back("sf_ele_eff_up");
  flags.push_back("sf_ele_eff_down");
  flags.push_back("sf_ele_reco_up");
  flags.push_back("sf_ele_reco_down");
  flags.push_back("sf_ele_trig_up");
  flags.push_back("sf_ele_trig_down");

  flags.push_back("sf_muo_id_up");
  flags.push_back("sf_muo_id_down");
  flags.push_back("sf_muo_iso_up");
  flags.push_back("sf_muo_iso_down");
  flags.push_back("sf_muo_trig_up");
  flags.push_back("sf_muo_trig_down");

  flags.push_back("sf_pho_eff_up");
  flags.push_back("sf_pho_eff_down");
  flags.push_back("sf_pho_veto_up_2016");
  flags.push_back("sf_pho_veto_up_2017");
  flags.push_back("sf_pho_veto_up_2018");
  flags.push_back("sf_pho_veto_down_2016");
  flags.push_back("sf_pho_veto_down_2017");
  flags.push_back("sf_pho_veto_down_2018");

  flags.push_back("l1prefiring_up");
  flags.push_back("l1prefiring_down");

  flags.push_back("eg_misid_up");
  flags.push_back("eg_misid_down");

  flags.push_back("jet_misid_iso1");
  flags.push_back("jet_misid_iso2");

  flags.push_back("jet_misid_mc");
  flags.push_back("jet_bkg_mc");

  flags.push_back("qcd_fit");

  map<string, TH1D*> h_xsec_rec;
  map<string, TH1D*> h_xsec_mc_gen;

  for (uint i = 0; i < flags.size(); i++) {

    TFile* file = new TFile(("html/" + version + "/" + flags[i] + "/" + year + ".xsec/root/" + title + ".root").c_str());

    if (!file->IsZombie()) {

      TH1D* h_xsec_tmp = (TH1D*)file->Get((title + "_xsec_rec").c_str());
      TH1D* h_xsec_mc_gen_tmp = (TH1D*)file->Get((title + "_xsec_mc_gen").c_str());

      h_xsec_rec[flags[i]] = h_xsec_tmp;
      h_xsec_mc_gen[flags[i]] = h_xsec_mc_gen_tmp;

      h_xsec_rec[flags[i]]->SetDirectory(0);
      h_xsec_mc_gen[flags[i]]->SetDirectory(0);

      file->Close();
      delete file;

    }

  }

  double xsec_data_ref = 0.;
  double xsec_stat_data_ref = 0.;

  if (h_xsec_rec["reference"]) xsec_data_ref = h_xsec_rec["reference"]->IntegralAndError(0, h_xsec_rec["reference"]->GetNbinsX()+1, xsec_stat_data_ref, "width");

  for (uint i = 0; i < flags.size(); i++) {

    double xsec_data = 0.;
    double xsec_stat_data = 0.;

    cout << std::setw(21) << flags[i]
         << " : ";

    if (h_xsec_rec[flags[i]]) {

      xsec_data = h_xsec_rec[flags[i]]->IntegralAndError(0, h_xsec_rec[flags[i]]->GetNbinsX()+1, xsec_stat_data, "width");

      cout << "xsec = "
           << std::fixed << std::setprecision(5)
           << std::setw(8) << xsec_data
           << " +- "
           << std::setw(4) << xsec_stat_data
           << " : ";
      if (h_xsec_rec["reference"]) {
        cout << std::fixed << std::setprecision(2)
             << std::setw(6) << 100. * (xsec_data - xsec_data_ref) / xsec_data
             << " %"
             << " : "
             << std::setw(6) << TMath::Sign(1, xsec_data - xsec_data_ref) * 100. * (TMath::Sqrt(TMath::Max(0.,TMath::Power(xsec_data - xsec_data_ref,2) - TMath::Abs(TMath::Power(xsec_stat_data,2) - TMath::Power(xsec_stat_data_ref,2))))) / xsec_data
             << " %"
             << endl;
      } else {
        cout << "reference cross section not available" << endl;
      }

    } else {

      cout << "cross section not available" << endl;

    }

  }

  if (h_xsec_rec["reference"]) {
    cout << std::setw(21)
         << "lumi"
         << " : "
         << "xsec = "
         << std::fixed << std::setprecision(5)
         << std::setw(8) << xsec_data_ref * (1 + lumierror / 100.)
         << " +- "
         << std::setw(4) << xsec_stat_data_ref
         << " : "
         << std::fixed << std::setprecision(2)
         << std::setw(5) << lumierror
         << " %"
         << endl;
  } else {
    cout << "reference cross section not available" << endl;
    return;
  }

  map<string, double> errors_tot;

  if (h_xsec_rec["bkg_stat"]) {
    double xval_stat = 0.;
    double xval = h_xsec_rec["bkg_stat"]->IntegralAndError(0, h_xsec_rec["bkg_stat"]->GetNbinsX()+1, xval_stat, "width");
    xval = TMath::Sqrt((TMath::Power(xval_stat, 2) - TMath::Power(xsec_stat_data_ref, 2))/(1.1 * 1.1 - 1.));
    errors_tot["bkg_stat"] = xval;
  }

  if (h_xsec_rec["jet_misid_stat"]) {
    double xval_stat = 0.;
    double xval = h_xsec_rec["jet_misid_stat"]->IntegralAndError(0, h_xsec_rec["jet_misid_stat"]->GetNbinsX()+1, xval_stat, "width");
    xval = TMath::Sqrt((TMath::Power(xval_stat, 2) - TMath::Power(xsec_stat_data_ref, 2))/(1.1 * 1.1 - 1.));
    errors_tot["jet_misid_stat"] = xval;
  }

  if (h_xsec_rec["pileup_up"] && h_xsec_rec["pileup_down"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["pileup_up"]->IntegralAndError(0, h_xsec_rec["pileup_up"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["pileup_down"]->IntegralAndError(0, h_xsec_rec["pileup_down"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["pileup"] = xval;
  }

  if (h_xsec_rec["jec_up_2016"] && h_xsec_rec["jec_down_2016"] && h_xsec_rec["jec_up_2017"] && h_xsec_rec["jec_down_2017"] && h_xsec_rec["jec_up_2018"] && h_xsec_rec["jec_down_2018"]) {
    double xval_2016_stat_up = 0.;
    double xval_2016_up = h_xsec_rec["jec_up_2016"]->IntegralAndError(0, h_xsec_rec["jec_up_2016"]->GetNbinsX()+1, xval_2016_stat_up, "width");
    xval_2016_up = xval_2016_up - xsec_data_ref;
    xval_2016_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_up, 2) - TMath::Abs(TMath::Power(xval_2016_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2016_stat_down = 0.;
    double xval_2016_down = h_xsec_rec["jec_down_2016"]->IntegralAndError(0, h_xsec_rec["jec_down_2016"]->GetNbinsX()+1, xval_2016_stat_down, "width");
    xval_2016_down = xval_2016_down - xsec_data_ref;
    xval_2016_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_down, 2) - TMath::Abs(TMath::Power(xval_2016_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2017_stat_up = 0.;
    double xval_2017_up = h_xsec_rec["jec_up_2017"]->IntegralAndError(0, h_xsec_rec["jec_up_2017"]->GetNbinsX()+1, xval_2017_stat_up, "width");
    xval_2017_up = xval_2017_up - xsec_data_ref;
    xval_2017_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_up, 2) - TMath::Abs(TMath::Power(xval_2017_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2017_stat_down = 0.;
    double xval_2017_down = h_xsec_rec["jec_down_2017"]->IntegralAndError(0, h_xsec_rec["jec_down_2017"]->GetNbinsX()+1, xval_2017_stat_down, "width");
    xval_2017_down = xval_2017_down - xsec_data_ref;
    xval_2017_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_down, 2) - TMath::Abs(TMath::Power(xval_2017_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2018_stat_up = 0.;
    double xval_2018_up = h_xsec_rec["jec_up_2018"]->IntegralAndError(0, h_xsec_rec["jec_up_2018"]->GetNbinsX()+1, xval_2018_stat_up, "width");
    xval_2018_up = xval_2018_up - xsec_data_ref;
    xval_2018_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_up, 2) - TMath::Abs(TMath::Power(xval_2018_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2018_stat_down = 0.;
    double xval_2018_down = h_xsec_rec["jec_down_2018"]->IntegralAndError(0, h_xsec_rec["jec_down_2018"]->GetNbinsX()+1, xval_2018_stat_down, "width");
    xval_2018_down = xval_2018_down - xsec_data_ref;
    xval_2018_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_down, 2) - TMath::Abs(TMath::Power(xval_2018_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = TMath::Sqrt(TMath::Power(0.5 * (xval_2016_up + xval_2016_down), 2) + TMath::Power(0.5 * (xval_2017_up + xval_2017_down), 2) + TMath::Power(0.5 * (xval_2018_up + xval_2018_down), 2));
    errors_tot["jec"] = xval;
  }

  if (h_xsec_rec["jer_up_2016"] && h_xsec_rec["jer_down_2016"] && h_xsec_rec["jer_up_2017"] && h_xsec_rec["jer_down_2017"] && h_xsec_rec["jer_up_2018"] && h_xsec_rec["jer_down_2018"]) {
    double xval_2016_stat_up = 0.;
    double xval_2016_up = h_xsec_rec["jer_up_2016"]->IntegralAndError(0, h_xsec_rec["jer_up_2016"]->GetNbinsX()+1, xval_2016_stat_up, "width");
    xval_2016_up = xval_2016_up - xsec_data_ref;
    xval_2016_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_up, 2) - TMath::Abs(TMath::Power(xval_2016_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2016_stat_down = 0.;
    double xval_2016_down = h_xsec_rec["jer_down_2016"]->IntegralAndError(0, h_xsec_rec["jer_down_2016"]->GetNbinsX()+1, xval_2016_stat_down, "width");
    xval_2016_down = xval_2016_down - xsec_data_ref;
    xval_2016_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_down, 2) - TMath::Abs(TMath::Power(xval_2016_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2017_stat_up = 0.;
    double xval_2017_up = h_xsec_rec["jer_up_2017"]->IntegralAndError(0, h_xsec_rec["jer_up_2017"]->GetNbinsX()+1, xval_2017_stat_up, "width");
    xval_2017_up = xval_2017_up - xsec_data_ref;
    xval_2017_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_up, 2) - TMath::Abs(TMath::Power(xval_2017_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2017_stat_down = 0.;
    double xval_2017_down = h_xsec_rec["jer_down_2017"]->IntegralAndError(0, h_xsec_rec["jer_down_2017"]->GetNbinsX()+1, xval_2017_stat_down, "width");
    xval_2017_down = xval_2017_down - xsec_data_ref;
    xval_2017_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_down, 2) - TMath::Abs(TMath::Power(xval_2017_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2018_stat_up = 0.;
    double xval_2018_up = h_xsec_rec["jer_up_2018"]->IntegralAndError(0, h_xsec_rec["jer_up_2018"]->GetNbinsX()+1, xval_2018_stat_up, "width");
    xval_2018_up = xval_2018_up - xsec_data_ref;
    xval_2018_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_up, 2) - TMath::Abs(TMath::Power(xval_2018_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2018_stat_down = 0.;
    double xval_2018_down = h_xsec_rec["jer_down_2018"]->IntegralAndError(0, h_xsec_rec["jer_down_2018"]->GetNbinsX()+1, xval_2018_stat_down, "width");
    xval_2018_down = xval_2018_down - xsec_data_ref;
    xval_2018_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_down, 2) - TMath::Abs(TMath::Power(xval_2018_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = TMath::Sqrt(TMath::Power(0.5 * (xval_2016_up + xval_2016_down), 2) + TMath::Power(0.5 * (xval_2017_up + xval_2017_down), 2) + TMath::Power(0.5 * (xval_2018_up + xval_2018_down), 2));
    errors_tot["jer"] = xval;
  }

  if (h_xsec_rec["sf_ele_eff_up"] && h_xsec_rec["sf_ele_eff_down"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["sf_ele_eff_up"]->IntegralAndError(0, h_xsec_rec["sf_ele_eff_up"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["sf_ele_eff_down"]->IntegralAndError(0, h_xsec_rec["sf_ele_eff_down"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["ele_eff"] = xval;
  }
  if (h_xsec_rec["sf_ele_reco_up"] && h_xsec_rec["sf_ele_reco_down"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["sf_ele_reco_up"]->IntegralAndError(0, h_xsec_rec["sf_ele_reco_up"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["sf_ele_reco_down"]->IntegralAndError(0, h_xsec_rec["sf_ele_reco_down"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["ele_reco"] = xval;
  }
  if (h_xsec_rec["sf_ele_trig_up"] && h_xsec_rec["sf_ele_trig_down"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["sf_ele_trig_up"]->IntegralAndError(0, h_xsec_rec["sf_ele_trig_up"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["sf_ele_trig_down"]->IntegralAndError(0, h_xsec_rec["sf_ele_trig_down"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["ele_trig"] = xval;
  }

  if (h_xsec_rec["sf_muo_id_up"] && h_xsec_rec["sf_muo_id_down"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["sf_muo_id_up"]->IntegralAndError(0, h_xsec_rec["sf_muo_id_up"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["sf_muo_id_down"]->IntegralAndError(0, h_xsec_rec["sf_muo_id_down"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["muo_id"] = xval;
  }
  if (h_xsec_rec["sf_muo_iso_up"] && h_xsec_rec["sf_muo_iso_down"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["sf_muo_iso_up"]->IntegralAndError(0, h_xsec_rec["sf_muo_iso_up"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["sf_muo_iso_down"]->IntegralAndError(0, h_xsec_rec["sf_muo_iso_down"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["muo_iso"] = xval;
  }
  if (h_xsec_rec["sf_muo_trig_up"] && h_xsec_rec["sf_muo_trig_down"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["sf_muo_trig_up"]->IntegralAndError(0, h_xsec_rec["sf_muo_trig_up"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["sf_muo_trig_down"]->IntegralAndError(0, h_xsec_rec["sf_muo_trig_down"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["muo_trig"] = xval;
  }

  if (h_xsec_rec["sf_pho_eff_up"] && h_xsec_rec["sf_pho_eff_down"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["sf_pho_eff_up"]->IntegralAndError(0, h_xsec_rec["sf_pho_eff_up"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["sf_pho_eff_down"]->IntegralAndError(0, h_xsec_rec["sf_pho_eff_down"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["pho_eff"] = xval;
  }

  if (h_xsec_rec["sf_pho_veto_up_2016"] && h_xsec_rec["sf_pho_veto_down_2016"] && h_xsec_rec["sf_pho_veto_up_2017"] && h_xsec_rec["sf_pho_veto_down_2017"] && h_xsec_rec["sf_pho_veto_up_2018"] && h_xsec_rec["sf_pho_veto_down_2018"]) {
    double xval_2016_stat_up = 0.;
    double xval_2016_up = h_xsec_rec["sf_pho_veto_up_2016"]->IntegralAndError(0, h_xsec_rec["sf_pho_veto_up_2016"]->GetNbinsX()+1, xval_2016_stat_up, "width");
    xval_2016_up = xval_2016_up - xsec_data_ref;
    xval_2016_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_up, 2) - TMath::Abs(TMath::Power(xval_2016_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2016_stat_down = 0.;
    double xval_2016_down = h_xsec_rec["sf_pho_veto_down_2016"]->IntegralAndError(0, h_xsec_rec["sf_pho_veto_down_2016"]->GetNbinsX()+1, xval_2016_stat_down, "width");
    xval_2016_down = xval_2016_down - xsec_data_ref;
    xval_2016_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_down, 2) - TMath::Abs(TMath::Power(xval_2016_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2017_stat_up = 0.;
    double xval_2017_up = h_xsec_rec["sf_pho_veto_up_2017"]->IntegralAndError(0, h_xsec_rec["sf_pho_veto_up_2017"]->GetNbinsX()+1, xval_2017_stat_up, "width");
    xval_2017_up = xval_2017_up - xsec_data_ref;
    xval_2017_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_up, 2) - TMath::Abs(TMath::Power(xval_2017_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2017_stat_down = 0.;
    double xval_2017_down = h_xsec_rec["sf_pho_veto_down_2017"]->IntegralAndError(0, h_xsec_rec["sf_pho_veto_down_2017"]->GetNbinsX()+1, xval_2017_stat_down, "width");
    xval_2017_down = xval_2017_down - xsec_data_ref;
    xval_2017_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_down, 2) - TMath::Abs(TMath::Power(xval_2017_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2018_stat_up = 0.;
    double xval_2018_up = h_xsec_rec["sf_pho_veto_up_2018"]->IntegralAndError(0, h_xsec_rec["sf_pho_veto_up_2018"]->GetNbinsX()+1, xval_2018_stat_up, "width");
    xval_2018_up = xval_2018_up - xsec_data_ref;
    xval_2018_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_up, 2) - TMath::Abs(TMath::Power(xval_2018_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_2018_stat_down = 0.;
    double xval_2018_down = h_xsec_rec["sf_pho_veto_down_2018"]->IntegralAndError(0, h_xsec_rec["sf_pho_veto_down_2018"]->GetNbinsX()+1, xval_2018_stat_down, "width");
    xval_2018_down = xval_2018_down - xsec_data_ref;
    xval_2018_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_down, 2) - TMath::Abs(TMath::Power(xval_2018_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = TMath::Sqrt(TMath::Power(0.5 * (xval_2016_up + xval_2016_down), 2) + TMath::Power(0.5 * (xval_2017_up + xval_2017_down), 2) + TMath::Power(0.5 * (xval_2018_up + xval_2018_down), 2));
    errors_tot["pho_veto"] = xval;
  }

  if (h_xsec_rec["l1prefiring_up"] && h_xsec_rec["l1prefiring_down"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["l1prefiring_up"]->IntegralAndError(0, h_xsec_rec["l1prefiring_up"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["l1prefiring_down"]->IntegralAndError(0, h_xsec_rec["l1prefiring_down"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["l1prefiring"] = xval;
  }

  if (h_xsec_rec["eg_misid_up"] && h_xsec_rec["eg_misid_down"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["eg_misid_up"]->IntegralAndError(0, h_xsec_rec["eg_misid_up"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["eg_misid_down"]->IntegralAndError(0, h_xsec_rec["eg_misid_down"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["eg_misid"] = xval;
  }

  if (h_xsec_rec["jet_misid_iso1"] && h_xsec_rec["jet_misid_iso2"]) {
    double xval_stat_up = 0.;
    double xval_up = h_xsec_rec["jet_misid_iso1"]->IntegralAndError(0, h_xsec_rec["jet_misid_iso1"]->GetNbinsX()+1, xval_stat_up, "width");
    xval_up = xval_up - xsec_data_ref;
    xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(xval_stat_up, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval_stat_down = 0.;
    double xval_down = h_xsec_rec["jet_misid_iso2"]->IntegralAndError(0, h_xsec_rec["jet_misid_iso2"]->GetNbinsX()+1, xval_stat_down, "width");
    xval_down = xval_down - xsec_data_ref;
    xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(xval_stat_down, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    double xval = 0.5 * (xval_up + xval_down);
    errors_tot["jet_misid"] = xval;
  }

  if (h_xsec_rec["jet_misid_mc"]) {
    double xval_stat = 0.;
    double xval = h_xsec_rec["jet_misid_mc"]->IntegralAndError(0, h_xsec_rec["jet_misid_mc"]->GetNbinsX()+1, xval_stat, "width");
    xval = xval - xsec_data_ref;
    xval = TMath::Sqrt(TMath::Max(0., TMath::Power(xval, 2) - TMath::Abs(TMath::Power(xval_stat, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    errors_tot["jet_misid_mc"] = xval;
  }

  if (h_xsec_rec["jet_bkg_mc"]) {
    double xval_stat = 0.;
    double xval = h_xsec_rec["jet_bkg_mc"]->IntegralAndError(0, h_xsec_rec["jet_bkg_mc"]->GetNbinsX()+1, xval_stat, "width");
    xval = xval - xsec_data_ref;
    xval = TMath::Sqrt(TMath::Max(0., TMath::Power(xval, 2) - TMath::Abs(TMath::Power(xval_stat, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    errors_tot["jet_bkg_mc"] = xval;
  }

  if (h_xsec_rec["qcd_fit"]) {
    double xval_stat = 0.;
    double xval = h_xsec_rec["qcd_fit"]->IntegralAndError(0, h_xsec_rec["qcd_fit"]->GetNbinsX()+1, xval_stat, "width");
    xval = xval - xsec_data_ref;
    xval = TMath::Sqrt(TMath::Max(0., TMath::Power(xval, 2) - TMath::Abs(TMath::Power(xval_stat, 2) - TMath::Power(xsec_stat_data_ref, 2))));
    errors_tot["qcd_fit"] = xval;
  }

  double xval = xsec_data_ref * lumierror / 100.;
  errors_tot["lumi"] = xval;

  map<string, vector<double>> values;
  map<string, vector<double>> errors;

  for (int i = 0; i < h_xsec_rec["reference"]->GetNbinsX()+2; i++) {

    if (h_xsec_rec["reference"]) {
      double val = h_xsec_rec["reference"]->GetBinContent(i);
      val = val * h_xsec_rec["reference"]->GetBinWidth(i);
      values["reference"].push_back(val);
      double xval = h_xsec_rec["reference"]->GetBinError(i);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["reference"].push_back(xval);
    }

    if (h_xsec_rec["bkg_stat"]) {
      double xval = TMath::Sqrt((TMath::Power(h_xsec_rec["bkg_stat"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))/(1.1 * 1.1 - 1.));
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["bkg_stat"].push_back(xval);
    }

    if (h_xsec_rec["jet_misid_stat"]) {
      double xval = TMath::Sqrt((TMath::Power(h_xsec_rec["jet_misid_stat"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))/(1.1 * 1.1 - 1.));
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["jet_misid_stat"].push_back(xval);
    }

    if (h_xsec_rec["pileup_up"] && h_xsec_rec["pileup_down"]) {
      double xval_up = fabs(h_xsec_rec["pileup_up"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["pileup_up"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["pileup_down"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["pileup_down"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["pileup"].push_back(xval);
    }

    if (h_xsec_rec["jec_up_2016"] && h_xsec_rec["jec_down_2016"] && h_xsec_rec["jec_up_2017"] && h_xsec_rec["jec_down_2017"] && h_xsec_rec["jec_up_2018"] && h_xsec_rec["jec_down_2018"]) {
      double xval_2016_up = fabs(h_xsec_rec["jec_up_2016"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2016_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jec_up_2016"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2016_down = fabs(h_xsec_rec["jec_down_2016"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2016_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jec_down_2016"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2017_up = fabs(h_xsec_rec["jec_up_2017"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2017_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jec_up_2017"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2017_down = fabs(h_xsec_rec["jec_down_2017"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2017_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jec_down_2017"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2018_up = fabs(h_xsec_rec["jec_up_2018"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2018_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jec_up_2018"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2018_down = fabs(h_xsec_rec["jec_down_2018"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2018_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jec_down_2018"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = TMath::Sqrt(TMath::Power(0.5 * (xval_2016_up + xval_2016_down), 2) + TMath::Power(0.5 * (xval_2017_up + xval_2017_down), 2) + TMath::Power(0.5 * (xval_2018_up + xval_2018_down), 2));
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["jec"].push_back(xval);
    }

    if (h_xsec_rec["jer_up_2016"] && h_xsec_rec["jer_down_2016"] && h_xsec_rec["jer_up_2017"] && h_xsec_rec["jer_down_2017"] && h_xsec_rec["jer_up_2018"] && h_xsec_rec["jer_down_2018"]) {
      double xval_2016_up = fabs(h_xsec_rec["jer_up_2016"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2016_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jer_up_2016"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2016_down = fabs(h_xsec_rec["jer_down_2016"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2016_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jer_down_2016"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2017_up = fabs(h_xsec_rec["jer_up_2017"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2017_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jer_up_2017"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2017_down = fabs(h_xsec_rec["jer_down_2017"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2017_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jer_down_2017"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2018_up = fabs(h_xsec_rec["jer_up_2018"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2018_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jer_up_2018"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2018_down = fabs(h_xsec_rec["jer_down_2018"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2018_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jer_down_2018"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = TMath::Sqrt(TMath::Power(0.5 * (xval_2016_up + xval_2016_down), 2) + TMath::Power(0.5 * (xval_2017_up + xval_2017_down), 2) + TMath::Power(0.5 * (xval_2018_up + xval_2018_down), 2));
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["jer"].push_back(xval);
    }

    if (h_xsec_rec["sf_ele_eff_up"] && h_xsec_rec["sf_ele_eff_down"]) {
      double xval_up = fabs(h_xsec_rec["sf_ele_eff_up"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_ele_eff_up"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["sf_ele_eff_down"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_ele_eff_down"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["ele_eff"].push_back(xval);
    }
    if (h_xsec_rec["sf_ele_reco_up"] && h_xsec_rec["sf_ele_reco_down"]) {
      double xval_up = fabs(h_xsec_rec["sf_ele_reco_up"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_ele_reco_up"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["sf_ele_reco_down"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_ele_reco_down"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["ele_reco"].push_back(xval);
    }
    if (h_xsec_rec["sf_ele_trig_up"] && h_xsec_rec["sf_ele_trig_down"]) {
      double xval_up = fabs(h_xsec_rec["sf_ele_trig_up"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_ele_trig_up"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["sf_ele_trig_down"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_ele_trig_down"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["ele_trig"].push_back(xval);
    }

    if (h_xsec_rec["sf_muo_id_up"] && h_xsec_rec["sf_muo_id_down"]) {
      double xval_up = fabs(h_xsec_rec["sf_muo_id_up"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_muo_id_up"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["sf_muo_id_down"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_muo_id_down"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["muo_id"].push_back(xval);
    }
    if (h_xsec_rec["sf_muo_iso_up"] && h_xsec_rec["sf_muo_iso_down"]) {
      double xval_up = fabs(h_xsec_rec["sf_muo_iso_up"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_muo_iso_up"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["sf_muo_iso_down"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_muo_iso_down"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["muo_iso"].push_back(xval);
    }
    if (h_xsec_rec["sf_muo_trig_up"] && h_xsec_rec["sf_muo_trig_down"]) {
      double xval_up = fabs(h_xsec_rec["sf_muo_trig_up"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_muo_trig_up"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["sf_muo_trig_down"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_muo_trig_down"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["muo_trig"].push_back(xval);
    }

    if (h_xsec_rec["sf_pho_eff_up"] && h_xsec_rec["sf_pho_eff_down"]) {
      double xval_up = fabs(h_xsec_rec["sf_pho_eff_up"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_pho_eff_up"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["sf_pho_eff_down"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_pho_eff_down"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["pho_eff"].push_back(xval);
    }

    if (h_xsec_rec["sf_pho_veto_up_2016"] && h_xsec_rec["sf_pho_veto_down_2016"] && h_xsec_rec["sf_pho_veto_up_2017"] && h_xsec_rec["sf_pho_veto_down_2017"] && h_xsec_rec["sf_pho_veto_up_2018"] && h_xsec_rec["sf_pho_veto_down_2018"]) {
      double xval_2016_up = fabs(h_xsec_rec["sf_pho_veto_up_2016"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2016_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_pho_veto_up_2016"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2016_down = fabs(h_xsec_rec["sf_pho_veto_down_2016"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2016_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2016_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_pho_veto_down_2016"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2017_up = fabs(h_xsec_rec["sf_pho_veto_up_2017"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2017_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_pho_veto_up_2017"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2017_down = fabs(h_xsec_rec["sf_pho_veto_down_2017"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2017_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2017_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_pho_veto_down_2017"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2018_up = fabs(h_xsec_rec["sf_pho_veto_up_2018"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2018_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_pho_veto_up_2018"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_2018_down = fabs(h_xsec_rec["sf_pho_veto_down_2018"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_2018_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_2018_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["sf_pho_veto_down_2018"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = TMath::Sqrt(TMath::Power(0.5 * (xval_2016_up + xval_2016_down), 2) + TMath::Power(0.5 * (xval_2017_up + xval_2017_down), 2) + TMath::Power(0.5 * (xval_2018_up + xval_2018_down), 2));
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["pho_veto"].push_back(xval);
    }

    if (h_xsec_rec["l1prefiring_up"] && h_xsec_rec["l1prefiring_down"]) {
      double xval_up = fabs(h_xsec_rec["l1prefiring_up"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["l1prefiring_up"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["l1prefiring_down"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["l1prefiring_down"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["l1prefiring"].push_back(xval);
    }

    if (h_xsec_rec["eg_misid_up"] && h_xsec_rec["eg_misid_down"]) {
      double xval_up = fabs(h_xsec_rec["eg_misid_up"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["eg_misid_up"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["eg_misid_down"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["eg_misid_down"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["eg_misid"].push_back(xval);
    }

    if (h_xsec_rec["jet_misid_iso1"] && h_xsec_rec["jet_misid_iso2"]) {
      double xval_up = fabs(h_xsec_rec["jet_misid_iso1"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_up = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_up, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jet_misid_iso1"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval_down = fabs(h_xsec_rec["jet_misid_iso2"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval_down = TMath::Sqrt(TMath::Max(0., TMath::Power(xval_down, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jet_misid_iso2"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      double xval = 0.5 * (xval_up + xval_down);
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["jet_misid"].push_back(xval);
    }

    if (h_xsec_rec["jet_misid_mc"]) {
      double xval = fabs(h_xsec_rec["jet_misid_mc"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval = TMath::Sqrt(TMath::Max(0., TMath::Power(xval, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jet_misid_mc"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["jet_misid_mc"].push_back(xval);
    }

    if (h_xsec_rec["jet_bkg_mc"]) {
      double xval = fabs(h_xsec_rec["jet_bkg_mc"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval = TMath::Sqrt(TMath::Max(0., TMath::Power(xval, 2) - TMath::Abs(TMath::Power(h_xsec_rec["jet_bkg_mc"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["jet_bkg_mc"].push_back(xval);
    }

    if (h_xsec_rec["qcd_fit"]) {
      double xval = fabs(h_xsec_rec["qcd_fit"]->GetBinContent(i) - h_xsec_rec["reference"]->GetBinContent(i));
      xval = TMath::Sqrt(TMath::Max(0., TMath::Power(xval, 2) - TMath::Abs(TMath::Power(h_xsec_rec["qcd_fit"]->GetBinError(i), 2) - TMath::Power(h_xsec_rec["reference"]->GetBinError(i), 2))));
      xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
      errors["qcd_fit"].push_back(xval);
    }

    double xval = h_xsec_rec["reference"]->GetBinContent(i) * lumierror / 100.;
    xval = xval * h_xsec_rec["reference"]->GetBinWidth(i);
    errors["lumi"].push_back(xval);
  }

  while (gSystem->AccessPathName(("html/" + version + "/reference/" + year + ".xsec/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/reference/" + year + ".xsec/root/").c_str(), kTRUE);
  }

  vector<string> labels;

  if (errors["bkg_stat"].size()) labels.push_back("bkg_stat");
  if (errors["jet_misid_stat"].size()) labels.push_back("jet_misid_stat");
  if (errors["pileup"].size()) labels.push_back("pileup");
  if (errors["jec"].size()) labels.push_back("jec");
  if (errors["jer"].size()) labels.push_back("jer");
  if (errors["ele_eff"].size()) labels.push_back("ele_eff");
  if (errors["ele_reco"].size()) labels.push_back("ele_reco");
  if (errors["ele_trig"].size()) labels.push_back("ele_trig");
  if (errors["muo_id"].size()) labels.push_back("muo_id");
  if (errors["muo_iso"].size()) labels.push_back("muo_iso");
  if (errors["muo_trig"].size()) labels.push_back("muo_trig");
  if (errors["pho_eff"].size()) labels.push_back("pho_eff");
  if (errors["pho_veto"].size()) labels.push_back("pho_veto");
  if (errors["l1prefiring"].size()) labels.push_back("l1prefiring");
  if (errors["eg_misid"].size()) labels.push_back("eg_misid");
  if (errors["jet_misid"].size()) labels.push_back("jet_misid");
  if (errors["jet_misid_mc"].size()) labels.push_back("jet_misid_mc");
  if (errors["jet_bkg_mc"].size()) labels.push_back("jet_bkg_mc");
  if (errors["qcd_fit"].size()) labels.push_back("qcd_fit");
  if (errors["lumi"].size()) labels.push_back("lumi");

  ofstream out;
  out.open(("html/" + version + "/reference/" + year + ".xsec/root/" + title + ".dat").c_str());
  Info("File::Open", "dat file %s has been created", ("html/" + version + "/reference/" + year + ".xsec/root/" + title + ".dat").c_str());

  out << title << " (" << h_xsec_mc_gen["reference"]->Integral(0, h_xsec_mc_gen["reference"]->GetNbinsX()+1, "width") << ")" << endl;

  out << std::setw(25) << "data";

  for (uint i = 0; i < labels.size(); i++) {
    out << std::setw(11) << TString(labels[i]).ReplaceAll("_stat", "").Data();
  }

  out << std::setw(11) << "total"
      << std::setw(11) << "total"
      << std::setw(11) << "total"
      << std::setw(11) << ""
      << endl;

  out << std::setw(25) << "stat";

  for (uint i = 0; i < labels.size(); i++) {
    if (labels[i] == "bkg_stat" || labels[i] == "jet_misid_stat") {
      if (errors[labels[i]].size()) out << std::setw(11) << "stat";
    } else {
      if (errors[labels[i]].size()) out << std::setw(11) << "syst";
    }
  }

  out << std::setw(11) << "stat"
      << std::setw(11) << "syst"
      << std::setw(11) << "error"
      << std::setw(9) << "%"
      << endl;

  double err_data[h_xsec_rec["reference"]->GetNbinsX()+2];

  for (int i = 0; i < h_xsec_rec["reference"]->GetNbinsX()+2; i++) {

    out << std::setw(2) << i
        << std::fixed << std::setprecision(5)
        << std::setw(12) << values["reference"][i]
        << std::setw(3) << " +-"
        << std::setw(8) << (errors["bkg_stat"].size() ? (errors["jet_misid_stat"].size() ? TMath::Sqrt(TMath::Power(errors["reference"][i], 2) - TMath::Power(errors["bkg_stat"][i], 2) - TMath::Power(errors["jet_misid_stat"][i], 2)) : TMath::Sqrt(TMath::Power(errors["reference"][i], 2) - TMath::Power(errors["bkg_stat"][i], 2)) ) : (errors["jet_misid_stat"].size() ? TMath::Sqrt(TMath::Power(errors["reference"][i], 2) - TMath::Power(errors["jet_misid_stat"][i], 2)) : errors["reference"][i]));

    for (uint j = 0; j < labels.size(); j++) {
      out << std::setw(3) << " +-"
          << std::setw(8) << errors[labels[j]][i];
    }

    out << std::setw(3) << " =>"
        << std::setw(8) <<  errors["reference"][i]
        << std::setw(3) << " +-";

    double sumw2 = 0.;

    for (uint j = 0; j < labels.size(); j++) {
      if (labels[j] != "bkg_stat" && labels[j] != "jet_misid_stat") {
        sumw2 = sumw2 + TMath::Power(errors[labels[j]][i], 2);
      }
    }
    out << std::setw(8) << TMath::Sqrt(sumw2)
        << std::setw(3) << " =>"
        << std::setw(8) <<  TMath::Sqrt(TMath::Power(errors["reference"][i], 2) + sumw2);

    err_data[i] = TMath::Sqrt(TMath::Power(errors["reference"][i], 2) + sumw2);

    out << std::setw(3) << " =>"
        << std::fixed << std::setprecision(1)
        << std::setw(6) << (values["reference"][i] != 0. ? 100 * TMath::Sqrt(TMath::Power(errors["reference"][i], 2) + sumw2)/values["reference"][i] : 0.)
        << endl;

  }

  out << std::setw(3) << "tot"
      << std::fixed << std::setprecision(5)
      << std::setw(11) << xsec_data_ref
      << " +-"
      << std::setw(8) << (errors_tot["bkg_stat"] ? (errors_tot["jet_misid_stat"] ? TMath::Sqrt(TMath::Power(xsec_stat_data_ref, 2) - TMath::Power(errors_tot["bkg_stat"], 2) - TMath::Power(errors_tot["jet_misid_stat"], 2))  : TMath::Sqrt(TMath::Power(xsec_stat_data_ref, 2) - TMath::Power(errors_tot["bkg_stat"], 2)) ) : (errors_tot["jet_misid_stat"] ? TMath::Sqrt(TMath::Power(xsec_stat_data_ref, 2) - TMath::Power(errors_tot["jet_misid_stat"], 2)) : xsec_stat_data_ref));

  for (uint j = 0; j < labels.size(); j++) {
    out << std::setw(3) << " +-";
    if (labels[j] == "lumi") {
      out << std::setw(8) << xsec_data_ref * lumierror / 100.;
    } else {
      out << std::setw(8) << errors_tot[labels[j]];
    }
  }

  out << std::setw(3) << " =>"
      << std::setw(8) << xsec_stat_data_ref
      << std::setw(3) << " +-";

  double sumw2 = 0.;

  for (uint j = 0; j < labels.size(); j++) {
    if (labels[j] != "bkg_stat" && labels[j] != "jet_misid_stat") {
      sumw2 = sumw2 + TMath::Power(errors_tot[labels[j]], 2);
    }
  }

  out << std::setw(8) << TMath::Sqrt(sumw2)
      << std::setw(3) << " =>"
      << std::setw(8) <<  TMath::Sqrt(xsec_stat_data_ref * xsec_stat_data_ref + sumw2)
      << std::setw(3) << " =>"
      << std::fixed << std::setprecision(1)
      << std::setw(6) << (xsec_data_ref != 0. ? 100 * TMath::Sqrt(xsec_stat_data_ref * xsec_stat_data_ref + sumw2)/xsec_data_ref : 0.)
      << endl;

  out.close();

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

  h_xsec_mc_gen["reference"]->SetMaximum(10.*TMath::Max(h_xsec_mc_gen["reference"]->GetMaximum(), h_xsec_rec["reference"]->GetMaximum()));
  h_xsec_mc_gen["reference"]->SetMinimum(TMath::Max(5.e-9, 0.1*TMath::Min(h_xsec_mc_gen["reference"]->GetMinimum(), h_xsec_rec["reference"]->GetMinimum())));
 
  if (title.find("nphotons") != string::npos) h_xsec_mc_gen["reference"]->SetMinimum(5.e-3);

  pad1->SetLogy();

  h_xsec_mc_gen["reference"]->SetTitle("");
  h_xsec_mc_gen["reference"]->SetStats(kFALSE);

  h_xsec_mc_gen["reference"]->SetLineColor(kBlue-4);
  h_xsec_mc_gen["reference"]->SetLineWidth(2);
  h_xsec_mc_gen["reference"]->SetFillColor(kBlue-4);
  h_xsec_mc_gen["reference"]->SetMarkerColor(kBlue-4);

  h_xsec_mc_gen["reference"]->GetXaxis()->SetTitleOffset(0.7);
  h_xsec_mc_gen["reference"]->GetXaxis()->SetLabelFont(42);
  h_xsec_mc_gen["reference"]->GetXaxis()->SetLabelSize(0.08);

  h_xsec_mc_gen["reference"]->GetYaxis()->SetTitle("d#sigma / dN_{#gamma} [pb]");
  h_xsec_mc_gen["reference"]->GetYaxis()->SetTitleSize(0.05);
  h_xsec_mc_gen["reference"]->GetYaxis()->SetTitleOffset(0.8);
  h_xsec_mc_gen["reference"]->GetYaxis()->SetLabelSize(0.045);

  if (title.find("nphotons") != string::npos) h_xsec_mc_gen["reference"]->GetXaxis()->SetRangeUser(-0.5, 2.5);

  h_xsec_mc_gen["reference"]->Draw("E2");

  TH1D* h_xsec_mc_gen1 = (TH1D*)h_xsec_mc_gen["reference"]->Clone("h_xsec_mc_gen1");
  for (int i = 0; i < h_xsec_mc_gen1->GetNbinsX()+2; i++) {
    h_xsec_mc_gen1->SetBinError(i, 1e-12);
  }
  h_xsec_mc_gen1->SetLineWidth(4);
  h_xsec_mc_gen1->Draw("SAME");

  TH1D* h_xsec_rec_err = (TH1D*)h_xsec_rec["reference"]->Clone("h_xsec_rec_err");

  for (int i = 0; i < h_xsec_rec_err->GetNbinsX()+2; i++) {
    h_xsec_rec_err->SetBinError(i, err_data[i] / h_xsec_rec["reference"]->GetBinWidth(i));
  }

  h_xsec_rec_err->SetTitle("");
  h_xsec_rec_err->SetStats(kFALSE);

  h_xsec_rec_err->SetTitle("");
  h_xsec_rec_err->SetStats(kFALSE);

  h_xsec_rec_err->SetLineColor(kRed+1);
  h_xsec_rec_err->SetLineWidth(1);
  h_xsec_rec_err->SetFillColor(kRed+1);
  h_xsec_rec_err->SetMarkerColor(kRed+1);
  h_xsec_rec_err->SetMarkerStyle(24);
  h_xsec_rec_err->SetMarkerSize(0.7);

  h_xsec_rec_err->SetMarkerColor(kRed+1);

  h_xsec_rec_err->Draw("E0PX0SAME");
  h_xsec_rec_err->Draw("E1PX0SAME");

  h_xsec_rec["reference"]->SetTitle("");
  h_xsec_rec["reference"]->SetStats(kFALSE);

  h_xsec_rec["reference"]->SetTitle("");
  h_xsec_rec["reference"]->SetStats(kFALSE);

  h_xsec_rec["reference"]->SetLineColor(kBlack);
  h_xsec_rec["reference"]->SetLineWidth(1);
  h_xsec_rec["reference"]->SetFillColor(kBlack);
  h_xsec_rec["reference"]->SetMarkerColor(kBlack);
  h_xsec_rec["reference"]->SetMarkerStyle(24);
  h_xsec_rec["reference"]->SetMarkerSize(0.7);

  h_xsec_rec["reference"]->SetMarkerColor(kBlack);

  h_xsec_rec["reference"]->Draw("E0PX0SAME");
  h_xsec_rec["reference"]->Draw("E1PX0SAME");

  pad1->Update();
  c1->Update();
  c1->cd();

  TH1D* h_ratio_rec = (TH1D*)h_xsec_rec["reference"]->Clone("h_ratio_rec");

  TH1D* h_xsec_mc_gen2 = (TH1D*)h_xsec_mc_gen["reference"]->Clone("h_xsec_mc_gen2");
  for (int i = 0; i < h_xsec_mc_gen2->GetNbinsX()+2; i++) {
    h_xsec_mc_gen2->SetBinError(i, 0.);
  }
  h_ratio_rec->Divide(h_xsec_mc_gen2);

  TH1D* h_ratio_err = (TH1D*)h_xsec_rec_err->Clone("h_ratio_err");
  h_ratio_err->Divide(h_xsec_mc_gen2);

  TPad* pad2 = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->Draw();
  pad2->cd();

  TH1D* h_ratio_gen = (TH1D*)h_xsec_mc_gen["reference"]->Clone("h_ratio_gen");
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
  h_ratio_gen->GetYaxis()->SetTitleOffset(0.35);
  h_ratio_gen->GetYaxis()->SetLabelSize(0.10);
  h_ratio_gen->GetYaxis()->SetNdivisions(505);
  h_ratio_gen->GetYaxis()->SetRangeUser(0.5, 1.5);

  if (title.find("nphotons") != string::npos) h_ratio_gen->GetXaxis()->SetRangeUser(-0.5, 2.5);

  h_ratio_gen->GetXaxis()->SetNdivisions(1003);
  h_ratio_gen->GetXaxis()->SetTickLength(0.1);

  string tmp_title = title;

  if (tmp_title == "h_W_ele_nphotons" || tmp_title == "h_W_muo_nphotons") {
    h_ratio_gen->GetXaxis()->SetTitle("Number of photons");
  } else if (tmp_title == "h_Z_ele_nphotons" || tmp_title == "h_Z_muo_nphotons") {
    h_ratio_gen->GetXaxis()->SetTitle("Number of photons");
  } else if (tmp_title == "h_WG_ele_pho0_pt" || tmp_title == "h_WG_muo_pho0_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_pt" || tmp_title == "h_ZG_muo_pho0_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_eta" || tmp_title == "h_WGG_muo_pho1_eta") {
    h_ratio_gen->GetXaxis()->SetTitle("#eta^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_phi" || tmp_title == "h_WGG_muo_pho1_phi") {
    h_ratio_gen->GetXaxis()->SetTitle("#phi^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_r9" || tmp_title == "h_WGG_muo_pho1_r9") {
    h_ratio_gen->GetXaxis()->SetTitle("R_{9}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_sieie" || tmp_title == "h_WGG_muo_pho0_sieie") {
    h_ratio_gen->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_sieie" || tmp_title == "h_WGG_muo_pho1_sieie") {
    h_ratio_gen->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_jet0_dR" || tmp_title == "h_WGG_muo_pho1_jet0_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{j#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_mva" || tmp_title == "h_WGG_muo_pho0_mva") {
    h_ratio_gen->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_mva" || tmp_title == "h_WGG_muo_pho1_mva") {
    h_ratio_gen->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_pf_iso_all" || tmp_title == "h_WGG_muo_pf_iso_all") {
    h_ratio_gen->GetXaxis()->SetTitle("Iso_{all}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_pf_iso_chg" || tmp_title == "h_WGG_muo_pf_iso_chg") {
    h_ratio_gen->GetXaxis()->SetTitle("Iso_{chg}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_dR" || tmp_title == "h_WGG_muo_pho1_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{l#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_pt" || tmp_title == "h_WGG_muo_pho0_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_pt" || tmp_title == "h_WGG_muo_pho1_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pt" || tmp_title == "h_WGG_muo_muo0_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1_dR" || tmp_title == "h_WGG_muo_pho0_pho1_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_eta" || tmp_title == "h_ZGG_muo_pho1_eta") {
    h_ratio_gen->GetXaxis()->SetTitle("#eta^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_phi" || tmp_title == "h_ZGG_muo_pho1_phi") {
    h_ratio_gen->GetXaxis()->SetTitle("#phi^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_r9" || tmp_title == "h_ZGG_muo_pho1_r9") {
    h_ratio_gen->GetXaxis()->SetTitle("R_{9}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_sieie" || tmp_title == "h_ZGG_muo_pho0_sieie") {
    h_ratio_gen->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_sieie" || tmp_title == "h_ZGG_muo_pho1_sieie") {
    h_ratio_gen->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_jet0_dR" || tmp_title == "h_ZGG_muo_pho1_jet0_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{j#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_mva" || tmp_title == "h_ZGG_muo_pho0_mva") {
    h_ratio_gen->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_mva" || tmp_title == "h_ZGG_muo_pho1_mva") {
    h_ratio_gen->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_pf_iso_all" || tmp_title == "h_ZGG_muo_pf_iso_all") {
    h_ratio_gen->GetXaxis()->SetTitle("Iso_{all}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_pf_iso_chg" || tmp_title == "h_ZGG_muo_pf_iso_chg") {
    h_ratio_gen->GetXaxis()->SetTitle("Iso_{chg}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_dR" || tmp_title == "h_ZGG_muo_pho1_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{l#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pt" || tmp_title == "h_ZGG_muo_pho0_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_pt" || tmp_title == "h_ZGG_muo_pho1_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1_dR" || tmp_title == "h_ZGG_muo_pho0_pho1_dR") {
    h_ratio_gen->GetXaxis()->SetTitle("#DeltaR^{#gamma#gamma}");
  } else if (tmp_title == "h_WGG_ele" || tmp_title == "h_WGG_muo") {
    h_ratio_gen->GetXaxis()->SetTitle("M_{T} [GeV]");
  } else if (tmp_title == "h_ZGG_ele" || tmp_title == "h_ZGG_muo") {
    h_ratio_gen->GetXaxis()->SetTitle("M_{ll} [GeV]");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1_pt" || tmp_title == "h_WGG_muo_pho0_pho1_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1" || tmp_title == "h_WGG_muo_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{#gamma#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pho0" || tmp_title == "h_WGG_muo_muo0_pho0") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pho1" || tmp_title == "h_WGG_muo_muo0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pho0_pho1" || tmp_title == "h_WGG_muo_muo0_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1_pt" || tmp_title == "h_ZGG_muo_pho0_pho1_pt") {
    h_ratio_gen->GetXaxis()->SetTitle("p_{T}^{#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1" || tmp_title == "h_ZGG_muo_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_pho1" || tmp_title == "h_ZGG_muo_muo0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele1_pho1" || tmp_title == "h_ZGG_muo_muo1_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_pho0_pho1" || tmp_title == "h_ZGG_muo_muo0_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele1_pho0_pho1" || tmp_title == "h_ZGG_muo_muo1_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{l#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_ele1_pho0_pho1" || tmp_title == "h_ZGG_muo_muo0_muo1_pho0_pho1") {
    h_ratio_gen->GetXaxis()->SetTitle("M^{ll#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_noiso_mva" || tmp_title == "h_ZGG_muo_pho0_noiso_mva") {
    h_ratio_gen->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_noiso_mva" || tmp_title == "h_ZGG_muo_pho1_noiso_mva") {
    h_ratio_gen->GetXaxis()->SetTitle("mva^{#gamma}");
  } else {
    tmp_title.erase(0, 2);
    h_ratio_gen->GetXaxis()->SetTitle(tmp_title.c_str());
  }

  h_ratio_gen->Draw("E2");

  pad2->Update();
  TLine* line = new TLine(pad2->GetUxmax(), 1.0, pad2->GetUxmin(), 1.0);
  line->SetLineColor(kBlue-4);
  line->SetLineWidth(2);
  line->Draw();

  h_ratio_err->SetLineColor(kRed+1);
  h_ratio_err->SetLineWidth(1);
  h_ratio_err->SetFillColor(kRed+1);
  h_ratio_err->SetMarkerColor(kRed+1);
  h_ratio_err->SetMarkerStyle(24);
  h_ratio_err->SetMarkerSize(0.7);

  h_ratio_err->Draw("E0PX0SAME");
  h_ratio_err->Draw("E1PX0SAME");

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
      label->DrawLatex(0.55, 0.75, "p_{T}^{e} > 40 GeV, #||{#eta^{e}} < 2.4, #slash{E}_{T} > 40 GeV");
    }
    if (plot.find("muo") != string::npos) {
      label->DrawLatex(0.55, 0.80, "W #rightarrow #mu#nu");
      label->DrawLatex(0.55, 0.75, "p_{T}^{#mu} > 30 GeV, #||{#eta^{#mu}} < 2.4, #slash{E}_{T} > 40 GeV");
    }
    label->DrawLatex(0.55, 0.69, "p_{T}^{#gamma} > 20 GeV, #||{#eta^{#gamma}} < 2.4");
  }
  if (plot.find("Z") != string::npos) {
    label->DrawLatex(0.55, 0.85, "Z, Z#gamma, Z#gamma#gamma selection");
    if (plot.find("ele") != string::npos) {
      label->DrawLatex(0.55, 0.80, "Z #rightarrow ee");
      label->DrawLatex(0.55, 0.75, "p_{T}^{e#scale[0.8]{1}} > 28 GeV, p_{T}^{e#scale[0.8]{2}} > 20 GeV, #||{#eta^{e}} < 2.4");
    }
    if (plot.find("muo") != string::npos) {
      label->DrawLatex(0.55, 0.80, "Z #rightarrow #mu#mu");
      label->DrawLatex(0.55, 0.75, "p_{T}^{#mu#scale[0.8]{1}} > 20 GeV, p_{T}^{#mu#scale[0.8]{2}} > 15 GeV, #||{#eta^{#mu}} < 2.4");
    }
    label->DrawLatex(0.55, 0.69, "p_{T}^{#gamma} > 20 GeV, #||{#eta^{#gamma}} < 2.4");
  }

  label->Draw("same");

  c1->SaveAs(("html/" + version + "/reference/" + year + ".xsec/" + title + ".pdf").c_str());

  TFile* file = new TFile(("html/" + version + "/reference/" + year + ".xsec/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/reference/" + year + ".xsec/root/" + title + ".root").c_str());
  h_xsec_rec["reference"]->Write((title + "_xsec_rec").c_str());
  h_xsec_mc_gen["reference"]->Write((title + "_xsec_mc_gen").c_str());
  h_xsec_rec_err->Write((title + "_xsec_rec_err").c_str());
  file->Close();
  delete file;

}

int main(int argc, char *argv[]) {

plot6(argv[1], argv[2], argv[3], argv[4]);

}
