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
        lumi2016 = lumi2016 + lumiMap[it->first];
        lumi2017 = lumi2017 + lumiMap[it->first];
        lumi2018 = lumi2018 + lumiMap[it->first];
      } else {
        cout << "WARNING: luminosity for " << it->first << " is ZERO !!" << endl;
      }
    }
  }

  if (lumi == 0) {
    cout << "ERROR: total luminosity is ZERO !!" << endl;
    return;
  }

  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("default") != string::npos) version = version + ".default";

  vector<string> flags;

  flags.push_back("reference");

  flags.push_back("pileup_up");

  flags.push_back("jec_up_2016");
  flags.push_back("jec_up_2017");
  flags.push_back("jec_up_2018");

  flags.push_back("jer_up_2016");
  flags.push_back("jer_up_2017");
  flags.push_back("jer_up_2018");

  flags.push_back("sf_ele_hlt_up");
  flags.push_back("sf_ele_reco_up");
  flags.push_back("sf_ele_eff_up");

  flags.push_back("sf_muo_trig_up");
  flags.push_back("sf_muo_id_up");
  flags.push_back("sf_muo_iso_up");

  flags.push_back("sf_pho_eff_up");
  flags.push_back("sf_pho_veto_up_2016");
  flags.push_back("sf_pho_veto_up_2017");
  flags.push_back("sf_pho_veto_up_2018");

  map<string, TH1D*> h_xsec;
  map<string, TH1D*> h_xsec_mc_gen;

  for (uint i = 0; i < flags.size(); i++) {

    if (!gSystem->AccessPathName(("html/" + version + "/" + flags[i] + "/" + year + ".xsec/root/" + title + ".root").c_str())) {

      TFile* file = new TFile(("html/" + version + "/" + flags[i] + "/" + year + ".xsec/root/" + title + ".root").c_str());

      TH1D* h_xsec_tmp = (TH1D*)file->Get((title + "_xsec").c_str());
      TH1D* h_xsec_mc_gen_tmp = (TH1D*)file->Get((title + "_xsec_mc_gen").c_str());

      h_xsec[flags[i]] = h_xsec_tmp;
      h_xsec_mc_gen[flags[i]] = h_xsec_mc_gen_tmp;

      h_xsec[flags[i]]->SetDirectory(0);
      h_xsec_mc_gen[flags[i]]->SetDirectory(0);

      file->Close();
      delete file;

    }

  }

  double xsec_data_ref = 0.;
  double xsec_stat_data_ref = 0.;

  if (h_xsec["reference"]) xsec_data_ref = h_xsec["reference"]->IntegralAndError(0,h_xsec["reference"]->GetNbinsX()+1,xsec_stat_data_ref);

  for (uint i = 0; i < flags.size(); i++) {

      double xsec_data = 0.;
      double xsec_stat_data = 0.;

    if (h_xsec[flags[i]]) {

      xsec_data = h_xsec[flags[i]]->IntegralAndError(0,h_xsec[flags[i]]->GetNbinsX()+1,xsec_stat_data);

      cout << std::setw(19)
           << flags[i]
           << " : xsec = "
           << std::fixed << std::setprecision(5)
           << std::setw(8) << xsec_data
           << " +- "
           << std::setw(4) << xsec_stat_data
           << " : ";
      if (xsec_data_ref != 0) {
        cout << std::fixed << std::setprecision(2)
             << std::setw(5) << 100.*(xsec_data-xsec_data_ref)/xsec_data
             << " %"
             << endl;
      } else {
        cout << "reference cross section not available" << endl;
      }

    } else {

      cout << flags[i] << " : " << "cross section not available" << endl;

    }

  }

}

int main(int argc, char *argv[]) {

plot6(argv[1], argv[2], argv[3], argv[4]);

}
