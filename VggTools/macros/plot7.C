#include "plot7.h"

#ifndef CMS_lumi_C
#define CMS_lumi_C
#include "CMS_lumi.C"
#endif

void plot7(string plot="", string title="", string version="v00", string options="") {

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
    cout << "ERROR: plot map " << plot << " is EMPTY or MISSING !!" << endl;
    return;
  }

  double lumi = 0.;
  double lumi2016 = 0.;
  double lumi2017 = 0.;
  double lumi2018 = 0.;

  for (multimap<string, double>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
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

  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("sherpa") != string::npos) version = version + ".sherpa";
  if (options.find("default") != string::npos) version = version + ".default";

  vector<string> flags;

  flags.push_back("reference");

  flags.push_back("bkg_stat");
  flags.push_back("jet_misid_stat");

  flags.push_back("pileup_up");
  flags.push_back("pileup_down");

#if 0
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
#endif

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

  flags.push_back("jet_misid_syst");

//  flags.push_back("bkg_syst");
  flags.push_back("xsec_syst_wg");
  flags.push_back("xsec_syst_zg");
  flags.push_back("xsec_syst_others");

//  flags.push_back("jet_misid_mc");

//  flags.push_back("jet_bkg_mc");

//  flags.push_back("qcd_fit");

//  flags.push_back("veto_ele_medium");
//  flags.push_back("veto_muo_medium");

  flags.push_back("lumi_up");
  flags.push_back("lumi_down");

  map<string, TH1D*> h_data;
  map<string, TH1D*> h_sig;
  map<string, TH1D*> h_misid;
  map<string, TH1D*> h_zg;
  map<string, TH1D*> h_irred;

  map<string, TH1D*> h_mc_bkg;
  map<string, TH1D*> h_mc_sum;

  for (uint i = 0; i < flags.size(); i++) {

    TFile* file = new TFile(("html/" + version + "/" + flags[i] + "/" + year + ".matrix/root/" + title + ".root").c_str());

    if (!file->IsZombie()) {

      TH1D* h_data_tmp = (TH1D*)file->Get((title + "_data").c_str());
      TH1D* h_sig_tmp = (TH1D*)file->Get((title + "_sig").c_str());
      TH1D* h_misid_tmp = (TH1D*)file->Get((title + "_misid").c_str());
      TH1D* h_zg_tmp = (TH1D*)file->Get((title + "_zg").c_str());
      TH1D* h_irred_tmp = (TH1D*)file->Get((title + "_irred").c_str());

      h_data[flags[i]] = h_data_tmp;
      h_sig[flags[i]] = h_sig_tmp;
      h_misid[flags[i]] = h_misid_tmp;
      h_zg[flags[i]] = h_zg_tmp;
      h_irred[flags[i]] = h_irred_tmp;

      h_mc_bkg[flags[i]] = (TH1D*)h_misid_tmp->Clone();
      if (title.find("h_WGG") != string::npos) h_mc_bkg[flags[i]]->Add(h_zg_tmp);
      h_mc_bkg[flags[i]]->Add(h_irred_tmp);

      h_mc_sum[flags[i]] = (TH1D*)h_misid_tmp->Clone();
      if (title.find("h_WGG") != string::npos) h_mc_sum[flags[i]]->Add(h_zg_tmp);
      h_mc_sum[flags[i]]->Add(h_irred_tmp);
      h_mc_sum[flags[i]]->Add(h_sig_tmp);

      h_data[flags[i]]->SetDirectory(0);
      h_sig[flags[i]]->SetDirectory(0);
      h_misid[flags[i]]->SetDirectory(0);
      h_zg[flags[i]]->SetDirectory(0);
      h_irred[flags[i]]->SetDirectory(0);

      h_mc_bkg[flags[i]]->SetDirectory(0);
      h_mc_sum[flags[i]]->SetDirectory(0);

      file->Close();
      delete file;

    }

  }

  double syst_sig = 0.;
  double syst_misid = 0.;
  double syst_zg = 0.;
  double syst_irred = 0.;

  double syst_mc_bkg = 0.;
  double syst_mc_sum = 0.;

  for (uint i = 0; i < flags.size(); i++) {

    if (h_data[flags[i]]) {

      if (flags[i] == "reference") continue;

      if (flags[i] == "jet_misid_syst" || flags[i] == "xsec_syst_wg" || flags[i] == "xsec_syst_zg" || flags[i] == "xsec_syst_others") {

        syst_sig += TMath::Power(fabs(h_sig[flags[i]]->Integral() - h_sig["reference"]->Integral()), 2);
        syst_misid += TMath::Power(fabs(h_misid[flags[i]]->Integral() - h_misid["reference"]->Integral()), 2);
        syst_zg += TMath::Power(fabs(h_zg[flags[i]]->Integral() - h_zg["reference"]->Integral()), 2);
        syst_irred += TMath::Power(fabs(h_irred[flags[i]]->Integral() - h_irred["reference"]->Integral()), 2);

        syst_mc_bkg += TMath::Power(fabs(h_mc_bkg[flags[i]]->Integral() - h_mc_bkg["reference"]->Integral()), 2);
        syst_mc_sum += TMath::Power(fabs(h_mc_sum[flags[i]]->Integral() - h_mc_sum["reference"]->Integral()), 2);

      }

      if (flags[i].find("down") != string::npos) {

        string up_flag = flags[i];
        size_t index = up_flag.find("down");
        up_flag.replace(index, 4, "up");

        syst_sig += TMath::Power(0.5 * (fabs(h_sig[flags[i]]->Integral() - h_sig["reference"]->Integral()) + fabs(h_sig[up_flag]->Integral() - h_sig["reference"]->Integral())) , 2);
        syst_misid += TMath::Power(0.5 * (fabs(h_misid[flags[i]]->Integral() - h_misid["reference"]->Integral()) + fabs(h_misid[up_flag]->Integral() - h_misid["reference"]->Integral())) , 2);
        syst_zg += TMath::Power(0.5 * (fabs(h_zg[flags[i]]->Integral() - h_zg["reference"]->Integral()) + fabs(h_zg[up_flag]->Integral() - h_zg["reference"]->Integral())) , 2);
        syst_irred += TMath::Power(0.5 * (fabs(h_irred[flags[i]]->Integral() - h_irred["reference"]->Integral()) + fabs(h_irred[up_flag]->Integral() - h_irred["reference"]->Integral())) , 2);

        syst_mc_bkg += TMath::Power(0.5 * (fabs(h_mc_bkg[flags[i]]->Integral() - h_mc_bkg["reference"]->Integral()) + fabs(h_mc_bkg[up_flag]->Integral() - h_mc_bkg["reference"]->Integral())) , 2);
        syst_mc_sum += TMath::Power(0.5 * (fabs(h_mc_sum[flags[i]]->Integral() - h_mc_sum["reference"]->Integral()) + fabs(h_mc_sum[up_flag]->Integral() - h_mc_sum["reference"]->Integral())) , 2);

      }

    }

  }

  double stat_data = 0.;
  double stat_sig = 0.;
  double stat_misid = 0.;
  double stat_zg = 0.;
  double stat_irred = 0.;

  double stat_mc_bkg = 0.;
  double stat_mc_sum = 0.;

  double int_data = h_data["reference"]->IntegralAndError(0, h_data["reference"]->GetNbinsX()+1, stat_data);
  double int_sig = h_sig["reference"]->IntegralAndError(0, h_sig["reference"]->GetNbinsX()+1, stat_sig);
  double int_misid = h_misid["reference"]->IntegralAndError(0, h_misid["reference"]->GetNbinsX()+1, stat_misid);
  double int_zg = h_zg["reference"]->IntegralAndError(0, h_zg["reference"]->GetNbinsX()+1, stat_zg);
  double int_irred = h_irred["reference"]->IntegralAndError(0, h_irred["reference"]->GetNbinsX()+1, stat_irred);

  double int_mc_bkg = h_mc_bkg["reference"]->IntegralAndError(0, h_mc_bkg["reference"]->GetNbinsX()+1, stat_mc_bkg);
  double int_mc_sum = h_mc_sum["reference"]->IntegralAndError(0, h_mc_sum["reference"]->GetNbinsX()+1, stat_mc_sum);

  cout << std::fixed << std::setprecision(1) << std::setw(15);

  cout << "" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << title << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "Signal       = " << std::setw(6) << int_sig << " +- " << std::setw(5) << stat_sig << " (stat.) +- " << std::setw(5) << TMath::Sqrt(syst_sig) << " (syst.)" << endl; 
  cout << "Jetpho misid = " << std::setw(6) << int_misid << " +- " << std::setw(5) << stat_misid << " (stat.) +- " << std::setw(5) << TMath::Sqrt(syst_misid) << " (syst.)" << endl; 
  cout << "Irreducible  = " << std::setw(6) << int_irred << " +- " << std::setw(5) << stat_irred << " (stat.) +- " << std::setw(5) << TMath::Sqrt(syst_irred) << " (syst.)" << endl; 
  if (title.find("h_WGG") != string::npos) cout << "Elepho misid = " << std::setw(6) << int_zg << " +- " << std::setw(5) << stat_zg << " (stat.) +- " << std::setw(5) << TMath::Sqrt(syst_zg) << " (syst.)" << endl; 
  cout << "-------------------------------------------------------" << endl;
  cout << "Total bkg    = " << std::setw(6) << int_mc_bkg << " +- " << std::setw(5) << stat_mc_bkg << " (stat.) +- " << std::setw(5) << TMath::Sqrt(syst_mc_bkg) << " (syst.)" << endl; 
  cout << "Total MC     = " << std::setw(6) << int_mc_sum << " +- " << std::setw(5) << stat_mc_sum << " (stat.) +- " << std::setw(5) << TMath::Sqrt(syst_mc_sum) << " (syst.)" << endl; 
  cout << "-------------------------------------------------------" << endl;
  cout << "Data         = " << std::setw(6) << int_data << " +- " << std::setw(5) << stat_data << " (stat.)" << endl; 
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "" << endl;

}

#ifndef __CLING__
int main(int argc, char *argv[]) {

#pragma unused (argc)

cout << "Processing plot7.C(\"" << argv[1] << "\",\""
                                << argv[2] << "\",\""
                                << argv[3] << "\",\""
                                << argv[4] << "\")..." << endl;

plot7(argv[1], argv[2], argv[3], argv[4]);

return 0;

}
#endif
