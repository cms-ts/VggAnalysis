#include "plot2.h"
#include "rebin.h"

#ifndef CMS_lumi_C
#define CMS_lumi_C
#include "CMS_lumi.C"
#endif

int plot2(string plot="", string title="", string version="v00", string options="", string flag="reference") {

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
    Error("plot2", "plot map %s is EMPTY or MISSING !!", plot.c_str());
    return 1;
  }

  double lumi = 0.;
  double lumi2016 = 0.;
  double lumi2017 = 0.;
  double lumi2018 = 0.;

  for (multimap<string, double>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_test" || flag == "jet_misid_qcd" || flag == "jet_misid_sherpa" || flag == "bkg_syst" || flag == "xsec_syst_wg" || flag == "xsec_syst_zg" || flag == "xsec_syst_others" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit" || flag == "lumi_up" || flag == "lumi_down") {
        file = new TFile(("data/" + version + "/reference/" + it->first + ".root").c_str());
      } else {
        file = new TFile(("data/" + version + "/" + flag + "/" + it->first + ".root").c_str());
      }
      if (file->IsZombie()) {
        Error("plot2", "file %s is MISSING !!", file->GetName());
        return 1;
      }
      if (lumiMap[it->first] != 0) {
        double var = (flag == "lumi_up") - (flag == "lumi_down");
        lumi = lumi + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2016") != string::npos) lumi2016 = lumi2016 + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2017") != string::npos) lumi2017 = lumi2017 + lumiMap[it->first] * (1.000 + 0.018 * var);
        if (it->first.find("Run2018") != string::npos) lumi2018 = lumi2018 + lumiMap[it->first] * (1.000 + 0.018 * var);
      } else {
        Warning("plot2", "luminosity for %s is ZERO !!", it->first.c_str());
      }
      file->Close();
      delete file;
    }
  }

  if (lumi == 0) {
    Error("plot2", "total luminosity is ZERO !!");
    return 1;
  }

  TH1D* h1 = 0;
  TH1D* h2 = 0;
  TH1D* h3 = 0;

  for (multimap<string, double>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index > 0) {
      if (title.find("h_ZGG_") != string::npos && index != 10) continue;
      if (title.find("h_WGG_") != string::npos && index != 1010) continue;
      TFile* file = 0;
      if (flag == "bkg_stat" || flag == "jet_misid_stat" || flag == "jet_misid_test" || flag == "jet_misid_qcd" || flag == "jet_misid_sherpa" || flag == "bkg_syst" || flag == "xsec_syst_wg" || flag == "xsec_syst_zg" || flag == "xsec_syst_others" || flag == "jet_misid_mc" || flag == "jet_bkg_mc" || flag == "qcd_fit" || flag == "lumi_up" || flag == "lumi_down") {
        file = new TFile(("data/" + version + "/reference/" + it->first + ".root").c_str());
      } else {
        file = new TFile(("data/" + version + "/" + flag + "/" + it->first + ".root").c_str());
      }
      if (file->IsZombie()) {
        Error("plot2", "file %s is MISSING !!", file->GetName());
        return 1;
      }
      double norm = 1.;
      if (xsecMap[it->first] != 0) {
        double ngen = ((TH1D*)file->Get("h_nevt"))->GetBinContent(2);
        if (it->first.find("RunIISummer16") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2016 / ngen;
        if (it->first.find("RunIIFall17") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2017 / ngen;
        if (it->first.find("RunIIAutumn18") != string::npos) norm = xsecMap[it->first] * 1000. * lumi2018 / ngen;
        if (flag == "bkg_syst") norm = norm * 1.075;
        if (flag == "xsec_syst_wg" && (index == 21 || index == 1011)) norm = norm * 1.075;
        if (flag == "xsec_syst_zg" && (index == 11 || index == 1021)) norm = norm * 1.075;
        if (flag == "xsec_syst_others" && index != 10 && index != 11 && index != 21 && index != 1010 && index != 1011 && index != 1021) norm = norm * 1.075;
      } else {
        Error("plot2", "cross section for %s is ZERO !!", it->first.c_str());
        return 1;
      }
      if (h1) {
        TH1D* h = (TH1D*)file->Get(title.c_str());
        if (h) {
          h1->Add(h, norm);
        }
      } else {
        TH1D* h = (TH1D*)file->Get(title.c_str());
        if (h) {
          h1 = h;
          h1->SetDirectory(0);
          h1->Scale(norm);
        }
      }
      if (h2) {
        TH1D* h = (TH1D*)file->Get((title + "_gen").c_str());
        if (h) {
          h2->Add(h, norm);
        }
      } else {
        TH1D* h = (TH1D*)file->Get((title + "_gen").c_str());
        if (h) {
          h2 = h;
          h2->SetDirectory(0);
          h2->Scale(norm);
        }
      }
      if (h3) {
        TH1D* h = (TH1D*)file->Get((title + "_genmatch").c_str());
        if (h) {
          h3->Add(h, norm);
        }
      } else {
        TH1D* h = (TH1D*)file->Get((title + "_genmatch").c_str());
        if (h) {
          h3 = h;
          h3->SetDirectory(0);
          h3->Scale(norm);
        }
      }
      file->Close();
      delete file;
    }
  }

  h1 = rebin(h1);
  h2 = rebin(h2);
  h3 = rebin(h3);

  h1->SetName((string(h1->GetName()) + "_rebin").c_str());
  h1 = rebin(h1);
  h2->SetName((string(h2->GetName()) + "_rebin").c_str());
  h2 = rebin(h2);
  h3->SetName((string(h3->GetName()) + "_rebin").c_str());
  h3 = rebin(h3);

  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("sherpa") != string::npos) version = version + ".sherpa";
  if (options.find("default") != string::npos) version = version + ".default";

  TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
  c1->cd();

  TH1D* h_mc_eff = (TH1D*)h1->Clone("h_mc_eff");
  TH1D* h_mc_eff_genmatch = (TH1D*)h3->Clone("h_mc_eff_genmatch");
  TH1D* h_mc_pur = (TH1D*)h3->Clone("h_mc_pur");

  h_mc_eff->Divide(h_mc_eff, h2, 1., 1., "B");
  h_mc_eff_genmatch->Divide(h_mc_eff_genmatch, h2, 1., 1., "B");
  h_mc_pur->Divide(h_mc_pur, h1, 1., 1., "B");

  h_mc_eff->SetTitle("");
  h_mc_eff->SetStats(kFALSE);
  h_mc_eff_genmatch->SetStats(kFALSE);
  h_mc_pur->SetStats(kFALSE);

  h_mc_eff->SetMinimum(0.0);
  h_mc_eff->SetMaximum(1.1);
  h_mc_eff_genmatch->SetMinimum(0.0);
  h_mc_eff_genmatch->SetMaximum(1.1);
  h_mc_pur->SetMinimum(0.0);
  h_mc_pur->SetMaximum(1.1);

  h_mc_eff->Draw("0");

  h_mc_eff_genmatch->SetLineColor(kRed);
  h_mc_eff_genmatch->SetMarkerStyle(24);
  h_mc_eff_genmatch->SetMarkerColor(kRed);

  h_mc_eff_genmatch->Draw("0SAME");

  h_mc_pur->SetLineColor(kGreen+2);
  h_mc_pur->SetMarkerStyle(26);
  h_mc_pur->SetMarkerColor(kGreen+2);

  h_mc_pur->Draw("0SAME");

  string tmp_title = title;

  if (tmp_title == "h_WG_ele_pho0_pt" || tmp_title == "h_WG_muo_pho0_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_pt" || tmp_title == "h_ZG_muo_pho0_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_eta" || tmp_title == "h_WGG_muo_pho1_eta") {
    h_mc_eff->GetXaxis()->SetTitle("#eta^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_phi" || tmp_title == "h_WGG_muo_pho1_phi") {
    h_mc_eff->GetXaxis()->SetTitle("#phi^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_r9" || tmp_title == "h_WGG_muo_pho1_r9") {
    h_mc_eff->GetXaxis()->SetTitle("R_{9}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_sieie" || tmp_title == "h_WGG_muo_pho0_sieie") {
    h_mc_eff->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_sieie" || tmp_title == "h_WGG_muo_pho1_sieie") {
    h_mc_eff->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_jet0_dR" || tmp_title == "h_WGG_muo_pho1_jet0_dR") {
    h_mc_eff->GetXaxis()->SetTitle("#DeltaR^{j#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_mva" || tmp_title == "h_WGG_muo_pho0_mva") {
    h_mc_eff->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_mva" || tmp_title == "h_WGG_muo_pho1_mva") {
    h_mc_eff->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_pf_iso_all" || tmp_title == "h_WGG_muo_pf_iso_all") {
    h_mc_eff->GetXaxis()->SetTitle("Iso_{all}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_pf_iso_chg" || tmp_title == "h_WGG_muo_pf_iso_chg") {
    h_mc_eff->GetXaxis()->SetTitle("Iso_{chg}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_dR" || tmp_title == "h_WGG_muo_pho1_dR") {
    h_mc_eff->GetXaxis()->SetTitle("#DeltaR^{l#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_pt" || tmp_title == "h_WGG_muo_pho0_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_pt" || tmp_title == "h_WGG_muo_pho1_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pt" || tmp_title == "h_WGG_muo_muo0_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1_dR" || tmp_title == "h_WGG_muo_pho0_pho1_dR") {
    h_mc_eff->GetXaxis()->SetTitle("#DeltaR^{#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_eta" || tmp_title == "h_ZGG_muo_pho1_eta") {
    h_mc_eff->GetXaxis()->SetTitle("#eta^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_phi" || tmp_title == "h_ZGG_muo_pho1_phi") {
    h_mc_eff->GetXaxis()->SetTitle("#phi^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_r9" || tmp_title == "h_ZGG_muo_pho1_r9") {
    h_mc_eff->GetXaxis()->SetTitle("R_{9}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_sieie" || tmp_title == "h_ZGG_muo_pho0_sieie") {
    h_mc_eff->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_sieie" || tmp_title == "h_ZGG_muo_pho1_sieie") {
    h_mc_eff->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_jet0_dR" || tmp_title == "h_ZGG_muo_pho1_jet0_dR") {
    h_mc_eff->GetXaxis()->SetTitle("#DeltaR^{j#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_mva" || tmp_title == "h_ZGG_muo_pho0_mva") {
    h_mc_eff->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_mva" || tmp_title == "h_ZGG_muo_pho1_mva") {
    h_mc_eff->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_pf_iso_all" || tmp_title == "h_ZGG_muo_pf_iso_all") {
    h_mc_eff->GetXaxis()->SetTitle("Iso_{all}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_pf_iso_chg" || tmp_title == "h_ZGG_muo_pf_iso_chg") {
    h_mc_eff->GetXaxis()->SetTitle("Iso_{chg}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_dR" || tmp_title == "h_ZGG_muo_pho1_dR") {
    h_mc_eff->GetXaxis()->SetTitle("#DeltaR^{l#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pt" || tmp_title == "h_ZGG_muo_pho0_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_pt" || tmp_title == "h_ZGG_muo_pho1_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_pt" || tmp_title == "h_ZGG_muo_muo0_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_ZGG_ele_ele1_pt" || tmp_title == "h_ZGG_muo_muo1_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1_dR" || tmp_title == "h_ZGG_muo_pho0_pho1_dR") {
    h_mc_eff->GetXaxis()->SetTitle("#DeltaR^{#gamma#gamma}");
  } else if (tmp_title == "h_WGG_ele" || tmp_title == "h_WGG_muo") {
    h_mc_eff->GetXaxis()->SetTitle("M_{T} [GeV]");
  } else if (tmp_title == "h_ZGG_ele" || tmp_title == "h_ZGG_muo") {
    h_mc_eff->GetXaxis()->SetTitle("M_{ll} [GeV]");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1_pt" || tmp_title == "h_WGG_muo_pho0_pho1_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{#gamma#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_pho1" || tmp_title == "h_WGG_muo_pho0_pho1") {
    h_mc_eff->GetXaxis()->SetTitle("M^{#gamma#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pho0" || tmp_title == "h_WGG_muo_muo0_pho0") {
    h_mc_eff->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pho1" || tmp_title == "h_WGG_muo_muo0_pho1") {
    h_mc_eff->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_WGG_ele_ele0_pho0_pho1" || tmp_title == "h_WGG_muo_muo0_pho0_pho1") {
    h_mc_eff->GetXaxis()->SetTitle("M^{l#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1_pt" || tmp_title == "h_ZGG_muo_pho0_pho1_pt") {
    h_mc_eff->GetXaxis()->SetTitle("p_{T}^{#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_pho1" || tmp_title == "h_ZGG_muo_pho0_pho1") {
    h_mc_eff->GetXaxis()->SetTitle("M^{#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_pho1" || tmp_title == "h_ZGG_muo_muo0_pho1") {
    h_mc_eff->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele1_pho1" || tmp_title == "h_ZGG_muo_muo1_pho1") {
    h_mc_eff->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_pho0_pho1" || tmp_title == "h_ZGG_muo_muo0_pho0_pho1") {
    h_mc_eff->GetXaxis()->SetTitle("M^{l#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele1_pho0_pho1" || tmp_title == "h_ZGG_muo_muo1_pho0_pho1") {
    h_mc_eff->GetXaxis()->SetTitle("M^{l#gamma#gamma}");
  } else if (tmp_title == "h_ZGG_ele_ele0_ele1_pho0_pho1" || tmp_title == "h_ZGG_muo_muo0_muo1_pho0_pho1") {
    h_mc_eff->GetXaxis()->SetTitle("M^{ll#gamma#gamma}");
  } else {
    tmp_title.erase(0, 2);
    h_mc_eff->GetXaxis()->SetTitle(tmp_title.c_str());
  }

  h_mc_eff->GetXaxis()->SetTitleSize(0.04);
  h_mc_eff->GetXaxis()->SetLabelFont(42);
  h_mc_eff->GetXaxis()->SetLabelSize(0.03);

  h_mc_eff->GetYaxis()->SetTitle("fraction");
  h_mc_eff->GetYaxis()->SetTitleSize(0.04);
  h_mc_eff->GetYaxis()->SetTitleOffset(0.8);
  h_mc_eff->GetYaxis()->SetLabelSize(0.03);

  TLatex* label = new TLatex();
  label->SetTextSize(0.0275);
  label->SetTextFont(42);
  label->SetLineWidth(2);
  label->SetNDC();

  char buff[100];

  double xval = 0.;
  double xerr = 0.;

  xval = h1->IntegralAndError(0, h1->GetNbinsX()+1, xerr);
  xval = xval / h2->Integral(0, h2->GetNbinsX()+1);
  xerr = xerr / h2->Integral(0, h2->GetNbinsX()+1) * TMath::Sqrt(1. - xval);
  sprintf(buff, "< efficiency > = %6.4f #pm %6.4f", xval, xerr);
  label->DrawLatex(0.50, 0.65, buff);

  xval = h3->IntegralAndError(0, h3->GetNbinsX()+1, xerr);
  xval = xval / h2->Integral(0, h2->GetNbinsX()+1);
  xerr = xerr / h2->Integral(0, h2->GetNbinsX()+1) * TMath::Sqrt(1. - xval);
  sprintf(buff, "< matching > = %6.4f #pm %6.4f", xval, xerr);
  label->SetTextColor(kRed);
  label->DrawLatex(0.50, 0.55, buff);

  xval = h3->IntegralAndError(0, h3->GetNbinsX()+1, xerr);
  xval = xval / h1->Integral(0, h1->GetNbinsX()+1);
  xerr = xerr / h1->Integral(0, h1->GetNbinsX()+1) * TMath::Sqrt(1. - xval);
  sprintf(buff, "< purity > = %6.4f #pm %6.4f", xval, xerr);
  label->SetTextColor(kGreen+2);
  label->DrawLatex(0.50, 0.45, buff);

  writeExtraText = true;

  lumiTextSize = 0.4;
  cmsTextSize = 0.50;

  lumi_13TeV  = Form("%.1f fb^{-1}", lumi);
  int iPeriod = 4;
  int iPos = 0;
  CMS_lumi(c1, iPeriod, iPos);

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".eff/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".eff/").c_str(), kTRUE);
  }

  c1->SaveAs(("html/" + version + "/" + flag + "/" + year + ".eff/" + title + ".pdf").c_str());

  ofstream out;
  out.open(("html/" + version + "/" + flag + "/" + year + ".eff/" + title + ".dat").c_str());
  Info("File::Open", "dat file %s has been created", ("html/" + version + "/" + flag + "/" + year + ".eff/" + title + ".dat").c_str());

  for (int i = 0; i < h_mc_eff->GetNbinsX()+2; i++) {
    out << i << " " << h_mc_eff->GetBinContent(i) << " " << h_mc_eff->GetBinError(i);
    out << " " << h_mc_eff_genmatch->GetBinContent(i) << " " << h_mc_eff_genmatch->GetBinError(i);
    out << " " << h_mc_pur->GetBinContent(i) << " " << h_mc_pur->GetBinError(i);
    out << endl;
  }

  out.close();

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".eff/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".eff/root/").c_str(), kTRUE);
  }

  TFile* file = new TFile(("html/" + version + "/" + flag + "/" + year + ".eff/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + flag + "/" + year + ".eff/root/" + title + ".root").c_str());

  h1->Write((title + "_mc_rec").c_str());
  h2->Write((title + "_mc_gen").c_str());
  h3->Write((title + "_mc_genmatch").c_str());

  h_mc_eff->Write((title + "_mc_eff").c_str());
  h_mc_eff_genmatch->Write((title + "_mc_eff_genmatch").c_str());
  h_mc_pur->Write((title + "_mc_pur").c_str());

  file->Close();
  delete file;

  return 0;

}

#ifndef __CLING__
int main(int argc, char *argv[]) {

#pragma unused (argc)

cout << "Processing plot2.C(\"" << argv[1] << "\",\""
                                << argv[2] << "\",\""
                                << argv[3] << "\",\""
                                << argv[4] << "\",\""
                                << argv[5] << "\")..." << endl;

return plot2(argv[1], argv[2], argv[3], argv[4], argv[5]);

}
#endif
