#include "plot0.h"
 
#include "CMS_lumi.C"

void plot0(string plot="", string title="", string version="v00", string flags="") {

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";

  plot = plot + ".dat";
  if (flags.find("test") != string::npos) plot = plot + ".test";
  if (flags.find("new") != string::npos) plot = plot + ".new";

  if (flags.find("qcd") != string::npos) {
    year = year + ".qcd";
    title = title + "_qcd";
    flags = flags + ",nofit";
    if (flags.find("nofit") == string::npos) flags = flags + ",nofit";
  }

  if (flags.find("amcatnlo") != string::npos) plot = "amcatnlo/" + plot;
  if (flags.find("madgraph") != string::npos) plot = "madgraph/" + plot;

  map<string, float> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets from " << "lumi.dat" << endl;

  map<string, float> xsecMap;
  readMap("xsec.dat", xsecMap);
  cout << "Read xsec map for " << xsecMap.size() << " datasets from " << "xsec.dat" << endl;

  multimap<string, float> plotMap;
  readMultiMap(plot, plotMap);
  cout << "Read plot map for " << plotMap.size() << " datasets from " << plot << endl;

  if (plotMap.size() == 0) {
    cout << "ERROR: plot map " << plot << " is EMPTY or MISSING !!" << endl;
    return;
  }

  map<int, TH1D*> histo;
  map<int, TH1D*> histo_mc_gen;

  float lumi = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      TFile* file = new TFile(("data/" + version + "/" + it->first + ".root").c_str()); 
      if (!file->IsOpen()) {
        cout << "ERROR: file " << it->first + ".root" << " is MISSING !!" << endl;
        return;
      }
      if (lumiMap[it->first] != 0) {
        lumi = lumi + lumiMap[it->first];
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
    if (index > 0) {
      TFile* file = new TFile(("data/" + version + "/" + it->first + ".root").c_str()); 
      if (!file->IsOpen()) {
        cout << "ERROR: file " << it->first + ".root" << " is MISSING !!" << endl;
        return;
      }
      double norm = 1.;
      if (xsecMap[it->first] != 0) {
        double ngen = ((TH1D*)gDirectory->Get("h_nevt"))->GetBinContent(2);
        norm = xsecMap[it->first] * 1000. * lumi / ngen;
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
      if (flags.find("qcd") == string::npos) {
        if ((index >= 10 && index <= 12) || (index >= 1010 && index <= 1012)) {
          if (histo_mc_gen[index]) {
            TH1D* h = (TH1D*)gDirectory->Get((title + "_gen").c_str());
            if (h) {
              histo_mc_gen[index]->Add(h, norm);
            }
          } else {
            TH1D* h = (TH1D*)gDirectory->Get((title + "_gen").c_str());
            if (h) {
              histo_mc_gen[index] = h;
              histo_mc_gen[index]->SetDirectory(0);
              histo_mc_gen[index]->Scale(norm);
            }
          }
        }
      }
      file->Close();
      delete file;
    }
  }

  if (flags.find("test") != string::npos) version = version + ".test";
  if (flags.find("new") != string::npos) version = version + ".new";

  if (flags.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (flags.find("madgraph") != string::npos) version = version + ".madgraph";

  if (flags.find("nofit") == string::npos) {
    float fitval = 0.;
    float fiterr = 0.;
    int index = 9001;
    ifstream file1;
    if (title.find("h_W_") != string::npos) {
      file1.open(("html/" + version + "/" + year + ".qcd/root/" + "h_W_" + title.substr(4, 3) + "_qcd_fit.dat").c_str());
    }
    if (title.find("h_WG_") != string::npos) {
      file1.open(("html/" + version + "/" + year + ".qcd/root/" + "h_WG_" + title.substr(5, 3) + "_qcd_fit.dat").c_str());
    }
    if (title.find("h_WGG_") != string::npos) {
      file1.open(("html/" + version + "/" + year + ".qcd/root/" + "h_WG_" + title.substr(6, 3) + "_qcd_fit.dat").c_str());
    }

    if (file1.good()) {
      file1 >> fitval >> fiterr;
      file1.close();
      TFile* file2 = new TFile(("html/" + version + "/" + year + ".qcd/root/" + title + "_qcd_nofit.root").c_str());
      if (file2->IsOpen()) { 
        histo[index] = (TH1D*)gDirectory->Get((title + "_qcd_nofit").c_str());
        histo[index]->SetDirectory(0);
        histo[index]->Scale(fitval);
        file2->Close();
        delete file2;
      }
    }
  }

  if (flags.find("nofit") != string::npos) title = title + "_nofit";

  THStack* hstack_mc = new THStack("hstack_mc", "hstack_mc");

  TH1D* h_mc_sum = (TH1D*)histo[0]->Clone("h_mc_sum");
  h_mc_sum->Reset();  

  TH1D* h_bkg = (TH1D*)histo[0]->Clone("h_bkg");
  h_bkg->Reset();  

  for (map<int, TH1D*>::reverse_iterator it = histo.rbegin(); it != histo.rend(); it++) {
    int index = int(it->first);
    if (index > 0) {
      hstack_mc->Add(it->second);
      h_mc_sum->Add(it->second);
      if ((index >= 20 && index <= 1000) || (index >= 1020 && index <= 2000) || index == 9001) {
        h_bkg->Add(it->second);
      }
    }
  }

  TH1D* h_mc_gen = (TH1D*)histo[0]->Clone("h_mc_gen");
  h_mc_gen->Reset();

  for (map<int, TH1D*>::iterator it = histo_mc_gen.begin(); it != histo_mc_gen.end(); it++) {
    if (it->second) h_mc_gen->Add(it->second);
  }

  TH1D* h_qcd = (TH1D*)histo[0]->Clone("h_qcd");
  if (flags.find("nofit") != string::npos) {
    h_qcd->Add(h_mc_sum, -1);
    for (int i = 0; i < h_qcd->GetNbinsX()+1; i++) {
      if (h_qcd->GetBinContent(i) < 0) {
        h_qcd->SetBinContent(i, 0);
        h_qcd->SetBinError(i, 0);
      }
    }
  }

  TH1D* h_nobs = (TH1D*)histo[0]->Clone("h_nobs");
  if (flags.find("nofit") == string::npos) {
    h_nobs->Add(h_bkg, -1);
    for (int i = 0; i < h_nobs->GetNbinsX()+1; i++) {
      if (h_nobs->GetBinContent(i) < 0) {
        h_nobs->SetBinContent(i, 0);
        h_nobs->SetBinError(i, 0);
      }
    }
  }

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
      it->second->SetFillColor(kYellow-4);
      leg->AddEntry(it->second, "DYJets", "f");
    }
    if (it->first == 11) {
      it->second->SetFillColor(kOrange-4);
      it->second->SetFillStyle(3245);
      leg->AddEntry(it->second, "Z #gamma", "f");
    }
    if (it->first == 12) {
      it->second->SetFillColor(kOrange+7);
      it->second->SetFillStyle(3254);
      leg->AddEntry(it->second, "Z #gamma #gamma", "f");
    }
    if (it->first == 13) {
      it->second->SetFillColor(kOrange+2);
      leg->AddEntry(it->second, "Z #rightarrow #tau #tau", "f");
    }
    if (it->first == 20) {
      it->second->SetFillColor(kOrange);
      leg->AddEntry(it->second, "WJets", "f");
    }
    if (it->first == 30) {
      it->second->SetFillColor(kGreen+2);
      leg->AddEntry(it->second, "Diboson", "f");
    }
    if (it->first == 35) {
      it->second->SetFillColor(kGreen+2);
      leg->AddEntry(it->second, "Triboson", "f");
    }
    if (it->first == 40) {
      it->second->SetFillColor(kBlue);
      leg->AddEntry(it->second, "TTJets", "f");
    }
    if (it->first == 50) {
      it->second->SetFillColor(kOrange-3);
      leg->AddEntry(it->second, "SingleTop", "f");
    }

    if (it->first == 1010) {
      it->second->SetFillColor(kYellow-4);
      leg->AddEntry(it->second, "WJets", "f");
    }
    if (it->first == 1011) {
      it->second->SetFillColor(kOrange-4);
      it->second->SetFillStyle(3245);
      leg->AddEntry(it->second, "W #gamma", "f");
    }
    if (it->first == 1012) {
      it->second->SetFillColor(kOrange+7);
      it->second->SetFillStyle(3254);
      leg->AddEntry(it->second, "W #gamma #gamma", "f");
    }
    if (it->first == 1013) {
      it->second->SetFillColor(kOrange+2);
      leg->AddEntry(it->second, "W #rightarrow #tau #nu", "f");
    }
    if (it->first == 1020) {
      it->second->SetFillColor(kOrange);
      leg->AddEntry(it->second, "DYJets", "f");
    }
    if (it->first == 1021) {
      it->second->SetFillColor(kOrange-5);
      leg->AddEntry(it->second, "Z #gamma", "f");
    }
    if (it->first == 1022) {
      it->second->SetFillColor(kOrange-6);
      leg->AddEntry(it->second, "Z #gamma #gamma", "f");
    }
    if (it->first == 1030) {
      it->second->SetFillColor(kBlue);
      leg->AddEntry(it->second, "TTJets", "f");
    }
    if (it->first == 1040) {
      it->second->SetFillColor(kOrange-3);
      leg->AddEntry(it->second, "SingleTop", "f");
    }
    if (it->first == 1050) {
      it->second->SetFillColor(kGreen+2);
      leg->AddEntry(it->second, "Diboson", "f");
    }
    if (it->first == 1055) {
      it->second->SetFillColor(kGreen+2);
      leg->AddEntry(it->second, "Triboson", "f");
    }

    if (it->first == 9001) {
      it->second->SetFillColor(kMagenta+3);
      leg->AddEntry(it->second, "QCD", "f");
    }
  }

  TH1D* h_ratio = (TH1D*)histo[0]->Clone("h_ratio");
  h_ratio->Divide(h_mc_sum);  

  TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
  c1->cd();

  TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
  pad1->SetBottomMargin(0.001);
  pad1->Draw();
  pad1->cd();

  hstack_mc->SetMaximum(1.2*TMath::Max(hstack_mc->GetMaximum(), histo[0]->GetMaximum()));
  if (flags.find("nolog") == string::npos) hstack_mc->SetMinimum(0.0001*hstack_mc->GetMaximum());

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

  if (flags.find("nolog") == string::npos) {
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

  if (tmp_title.find("_qcd") != string::npos) tmp_title.erase(tmp_title.find("_qcd"), 4);
  if (tmp_title.find("_nofit") != string::npos) tmp_title.erase(tmp_title.find("_nofit"), 6);

  if (tmp_title == "h_W_ele" || tmp_title == "h_W_muo") {
    h_ratio->GetXaxis()->SetTitle("M_{T} [GeV]");
  } else if (tmp_title == "h_W_ele_npvs" || tmp_title == "h_W_muo_npvs") {
    h_ratio->GetXaxis()->SetTitle("Number of primary vertices");
  } else if (tmp_title == "h_W_ele_npvs_w" || tmp_title == "h_W_muo_npvs_w") {
    h_ratio->GetXaxis()->SetTitle("Number of primary vertices");
  } else if (tmp_title == "h_W_ele0_pt" || tmp_title == "h_W_muo0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_W_ele0_eta" || tmp_title == "h_W_muo0_eta") {
    h_ratio->GetXaxis()->SetTitle("#eta^{l}");
  } else if (tmp_title == "h_W_ele0_phi" || tmp_title == "h_W_muo0_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{l}");
  } else if (tmp_title == "h_W_ele0_r9") {
    h_ratio->GetXaxis()->SetTitle("R_{9}^{l}");
  } else if (tmp_title == "h_W_ele0_sieie") {
    h_ratio->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{l}");
  } else if (tmp_title == "h_W_ele_met_pt" || tmp_title == "h_W_muo_met_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{miss}");
  } else if (tmp_title == "h_W_ele_met_phi" || tmp_title == "h_W_muo_met_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{miss}");
  } else if (tmp_title == "h_W_ele0_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{e}");
  } else if (tmp_title == "h_W_ele0_pf_iso_all" || tmp_title == "h_W_muo0_pf_iso_all") {
    h_ratio->GetXaxis()->SetTitle("Iso_{all}^{l}");
  } else if (tmp_title == "h_W_ele0_pf_iso_chg" || tmp_title == "h_W_muo0_pf_iso_chg") {
    h_ratio->GetXaxis()->SetTitle("Iso_{chg}^{l}");
  } else if (tmp_title == "h_Z_ele" || tmp_title == "h_Z_muo") {
    h_ratio->GetXaxis()->SetTitle("M_{ll} [GeV]");
  } else if (tmp_title == "h_Z_ele_npvs" || tmp_title == "h_Z_muo_npvs") {
    h_ratio->GetXaxis()->SetTitle("Number of primary vertices");
  } else if (tmp_title == "h_Z_ele_npvs_w" || tmp_title == "h_Z_muo_npvs_w") {
    h_ratio->GetXaxis()->SetTitle("Number of primary vertices");
  } else if (tmp_title == "h_Z_ele0_pt" || tmp_title == "h_Z_muo0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_Z_ele0_eta" || tmp_title == "h_Z_muo0_eta") {
    h_ratio->GetXaxis()->SetTitle("#eta^{l}");
  } else if (tmp_title == "h_Z_ele0_phi" || tmp_title == "h_Z_muo0_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{l}");
  } else if (tmp_title == "h_Z_ele0_r9") {
    h_ratio->GetXaxis()->SetTitle("R_{9}^{l}");
  } else if (tmp_title == "h_Z_ele0_sieie") {
    h_ratio->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{l}");
  } else if (tmp_title == "h_Z_ele1_pt" || tmp_title == "h_Z_muo0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_Z_ele1_eta" || tmp_title == "h_Z_muo0_eta") {
    h_ratio->GetXaxis()->SetTitle("#eta^{l}");
  } else if (tmp_title == "h_Z_ele1_phi" || tmp_title == "h_Z_muo0_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{l}");
  } else if (tmp_title == "h_Z_ele1_r9") {
    h_ratio->GetXaxis()->SetTitle("R_{9}^{l}");
  } else if (tmp_title == "h_Z_ele1_sieie") {
    h_ratio->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{l}");
  } else if (tmp_title == "h_Z_ele_met_pt" || tmp_title == "h_Z_muo_met_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{miss}");
  } else if (tmp_title == "h_Z_ele_met_phi" || tmp_title == "h_Z_muo_met_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{miss}");
  } else if (tmp_title == "h_Z_ele0_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{e}");
  } else if (tmp_title == "h_Z_ele1_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{e}");
  } else if (tmp_title == "h_Z_ele0_pf_iso_all" || tmp_title == "h_Z_muo0_pf_iso_all") {
    h_ratio->GetXaxis()->SetTitle("Iso_{all}^{l}");
  } else if (tmp_title == "h_Z_ele0_pf_iso_chg" || tmp_title == "h_Z_muo0_pf_iso_chg") {
    h_ratio->GetXaxis()->SetTitle("Iso_{chg}^{l}");
  } else if (tmp_title == "h_Z_ele1_pf_iso_all" || tmp_title == "h_Z_muo1_pf_iso_all") {
    h_ratio->GetXaxis()->SetTitle("Iso_{all}^{l}");
  } else if (tmp_title == "h_Z_ele1_pf_iso_chg" || tmp_title == "h_Z_muo1_pf_iso_chg") {
    h_ratio->GetXaxis()->SetTitle("Iso_{chg}^{l}");
  } else if (tmp_title == "h_W_ele_njets" || tmp_title == "h_W_muo_njets") {
    h_ratio->GetXaxis()->SetTitle("Number of jets");
  } else if (tmp_title == "h_W_ele_jet0_pt" || tmp_title == "h_W_muo_jet0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{j}");
  } else if (tmp_title == "h_W_ele_jet0_eta" || tmp_title == "h_W_muo_jet0_eta") {
    h_ratio->GetXaxis()->SetTitle("#eta^{j}");
  } else if (tmp_title == "h_W_ele_jet0_phi" || tmp_title == "h_W_muo_jet0_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{j}");
  } else if (tmp_title == "h_Z_ele_njets" || tmp_title == "h_Z_muo_njets") {
    h_ratio->GetXaxis()->SetTitle("Number of jets");
  } else if (tmp_title == "h_Z_ele_jet0_pt" || tmp_title == "h_Z_muo_jet0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{j}");
  } else if (tmp_title == "h_Z_ele_jet0_eta" || tmp_title == "h_Z_muo_jet0_eta") {
    h_ratio->GetXaxis()->SetTitle("#eta^{j}");
  } else if (tmp_title == "h_Z_ele_jet0_phi" || tmp_title == "h_Z_muo_jet0_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{j}");
  } else if (tmp_title == "h_W_ele_nphotons" || tmp_title == "h_W_muo_nphotons") {
    h_ratio->GetXaxis()->SetTitle("Number of photons");
  } else if (tmp_title == "h_WG_ele_ele0_pt" || tmp_title == "h_WG_muo_muo0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_WG_ele_pho0_pt" || tmp_title == "h_WG_muo_pho0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_WG_ele_pho0_eta" || tmp_title == "h_WG_muo_pho0_eta") {
    h_ratio->GetXaxis()->SetTitle("#eta^{#gamma}");
  } else if (tmp_title == "h_WG_ele_pho0_phi" || tmp_title == "h_WG_muo_pho0_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{#gamma}");
  } else if (tmp_title == "h_WG_ele_pho0_r9" || tmp_title == "h_WG_muo_pho0_r9") {
    h_ratio->GetXaxis()->SetTitle("R_{9}^{#gamma}");
  } else if (tmp_title == "h_WG_ele_pho0_sieie" || tmp_title == "h_WG_muo_pho0_sieie") {
    h_ratio->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_WG_ele_pho0_jet0_dR" || tmp_title == "h_WG_muo_pho0_jet0_dR") {
    h_ratio->GetXaxis()->SetTitle("#DeltaR^{j#gamma}");
  } else if (tmp_title == "h_WG_ele_pho0_mva" || tmp_title == "h_WG_muo_pho0_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_WG_ele_pho0_pf_iso_all" || tmp_title == "h_WG_muo_pho0_pf_iso_all") {
    h_ratio->GetXaxis()->SetTitle("Iso_{all}^{#gamma}");
  } else if (tmp_title == "h_WG_ele_pho0_pf_iso_chg" || tmp_title == "h_WG_muo_pho0_pf_iso_chg") {
    h_ratio->GetXaxis()->SetTitle("Iso_{chg}^{#gamma}");
  } else if (tmp_title == "h_WG_ele_pho0_dR" || tmp_title == "h_WG_muo_pho0_dR") {
    h_ratio->GetXaxis()->SetTitle("#DeltaR^{l#gamma}");
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
  } else if (tmp_title == "h_Z_ele_nphotons" || tmp_title == "h_Z_muo_nphotons") {
    h_ratio->GetXaxis()->SetTitle("Number of photons");
  } else if (tmp_title == "h_ZG_ele_ele0_pt" || tmp_title == "h_ZG_muo_muo0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{l}");
  } else if (tmp_title == "h_ZG_ele_pho0_pt" || tmp_title == "h_ZG_muo_pho0_pt") {
    h_ratio->GetXaxis()->SetTitle("p_{T}^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_eta" || tmp_title == "h_ZG_muo_pho0_eta") {
    h_ratio->GetXaxis()->SetTitle("#eta^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_phi" || tmp_title == "h_ZG_muo_pho0_phi") {
    h_ratio->GetXaxis()->SetTitle("#phi^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_r9" || tmp_title == "h_ZG_muo_pho0_r9") {
    h_ratio->GetXaxis()->SetTitle("R_{9}^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_sieie" || tmp_title == "h_ZG_muo_pho0_sieie") {
    h_ratio->GetXaxis()->SetTitle("#sigma_{i#etai#eta}^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_jet0_dR" || tmp_title == "h_ZG_muo_pho0_jet0_dR") {
    h_ratio->GetXaxis()->SetTitle("#DeltaR^{j#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_mva" || tmp_title == "h_ZG_muo_pho0_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_pf_iso_all" || tmp_title == "h_ZG_muo_pho0_pf_iso_all") {
    h_ratio->GetXaxis()->SetTitle("Iso_{all}^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_pf_iso_chg" || tmp_title == "h_ZG_muo_pho0_pf_iso_chg") {
    h_ratio->GetXaxis()->SetTitle("Iso_{chg}^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_dR" || tmp_title == "h_ZG_muo_pho0_dR") {
    h_ratio->GetXaxis()->SetTitle("#DeltaR^{l#gamma}");
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
  }  else if (tmp_title == "h_WG_ele" || tmp_title == "h_WG_muo") {
    h_ratio->GetXaxis()->SetTitle("M_{T} [GeV]");
  } else if (tmp_title == "h_ZG_ele" || tmp_title == "h_ZG_muo") {
    h_ratio->GetXaxis()->SetTitle("M_{ll} [GeV]");
  } else if (tmp_title == "h_WGG_ele" || tmp_title == "h_WGG_muo") {
    h_ratio->GetXaxis()->SetTitle("M_{T} [GeV]");
  } else if (tmp_title == "h_ZGG_ele" || tmp_title == "h_ZGG_muo") {
    h_ratio->GetXaxis()->SetTitle("M_{ll} [GeV]");
  } else if (tmp_title == "h_WG_ele_ele0_pho0" || tmp_title == "h_WG_muo_muo0_pho0") {
    h_ratio->GetXaxis()->SetTitle("M^{l#gamma}");
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
  } else if (tmp_title == "h_ZG_ele_ele0_pho0" || tmp_title == "h_ZG_muo_muo0_pho0") {
    h_ratio->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_ZG_ele_ele1_pho0" || tmp_title == "h_ZG_muo_muo1_pho0") {
    h_ratio->GetXaxis()->SetTitle("M^{l#gamma}");
  } else if (tmp_title == "h_ZG_ele_ele0_ele1_pho0" || tmp_title == "h_ZG_muo_ele0_ele1_pho0") {
    h_ratio->GetXaxis()->SetTitle("M^{ll#gamma}");
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
  } else if (tmp_title == "h_WG_ele_pho0_noiso_mva" || tmp_title == "h_WG_muo_pho0_noiso_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho0_noiso_mva" || tmp_title == "h_WGG_muo_pho0_noiso_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_WGG_ele_pho1_noiso_mva" || tmp_title == "h_WGG_muo_pho1_noiso_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZG_ele_pho0_noiso_mva" || tmp_title == "h_ZG_muo_pho0_noiso_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho0_noiso_mva" || tmp_title == "h_ZGG_muo_pho0_noiso_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_ZGG_ele_pho1_noiso_mva" || tmp_title == "h_ZGG_muo_pho1_noiso_mva") {
    h_ratio->GetXaxis()->SetTitle("mva^{#gamma}");
  } else if (tmp_title == "h_W_ele0_trig" || tmp_title == "h_W_muo0_trig") {
    h_ratio->GetXaxis()->SetTitle("Trigger bits");
  } else if (tmp_title == "h_Z_ele0_trig" || tmp_title == "h_Z_muo0_trig") {
    h_ratio->GetXaxis()->SetTitle("Trigger bits");
  } else if (tmp_title == "h_Z_ele1_trig" || tmp_title == "h_Z_muo1_trig") {
    h_ratio->GetXaxis()->SetTitle("Trigger bits");
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

  while (gSystem->AccessPathName(("html/" + version + "/" + year + "/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + year + "/").c_str(), kTRUE);
  }
  c1->SaveAs(("html/" + version + "/" + year + "/" + title + ".pdf").c_str());

  while (gSystem->AccessPathName(("html/" + version + "/" + year + "/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + year + "/root/").c_str(), kTRUE);
  }
  TFile* file = new TFile(("html/" + version + "/" + year + "/root/" + title + ".root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + year + "/root/" + title + ".root").c_str());
  if (flags.find("nofit") != string::npos) h_qcd->Write(title.c_str());
  if (flags.find("nofit") == string::npos) {
    h_nobs->Write(title.c_str());
    h_mc_gen->Write((title + "_mc_gen").c_str());
  }
  file->Close();
  delete file;

}

int main(int argc, char *argv[]) {

plot0(argv[1], argv[2], argv[3], argv[4]);

}
