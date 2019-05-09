#include "plot3.h"

void plot3(string plot="", string title="", string version="", string options="", string flags="reference") {

  if (plot.find("Zgg") != string::npos) {
    if (options.find("qcd") != string::npos) {
      cout << "Skipping plot map " << plot << " for options " << options << endl;
      return;
    }
  }

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";
  if (plot.find("Run2") != string::npos) year = "Run2";

  plot = plot + ".dat";
  if (options.find("test") != string::npos) plot = plot + ".test";
  if (options.find("new") != string::npos) plot = plot + ".new";
  if (options.find("jet") != string::npos) plot = plot + ".jet";

  if (options.find("qcd") != string::npos) {
    year = year + ".qcd";
    title = title + "_qcd";
    options = options + ",nofit";
    if (options.find("nofit") == string::npos) options = options + ",nofit";
  }

  if (options.find("amcatnlo") != string::npos) plot = "amcatnlo/" + plot;
  if (options.find("madgraph") != string::npos) plot = "madgraph/" + plot;
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

  map<int, TH1D*> histo;
  map<int, TH1D*> histo_mc_gen;

  float lumi = 0.;
  float lumi2016 = 0.;
  float lumi2017 = 0.;
  float lumi2018 = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      TFile* file = new TFile(("data/" + version + "/" + flags + "/" + it->first + ".root").c_str());
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

  bool useMC = false;

  if (useMC){
    for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
      int index = int(it->second);
      if (index > 0) {
        TFile* file = new TFile(("data/" + version + "/" + flags + "/" + it->first + ".root").c_str());
        if (file->IsZombie()) {
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
        if (options.find("qcd") == string::npos) {
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
  }

  TH1D* h_mc_bkg = (TH1D*)histo[0]->Clone("h_mc_bkg");
  h_mc_bkg->Reset();

  TH1D* h_mc_sgn = (TH1D*)histo[0]->Clone("h_mc_sgn");
  h_mc_sgn->Reset();

  TH1D* h_mc_sum = (TH1D*)histo[0]->Clone("h_mc_sum");
  h_mc_sum->Reset();

  bool flowbins = true;

  for (map<int, TH1D*>::reverse_iterator it = histo.rbegin(); it != histo.rend(); it++) {
    int index = int(it->first);
    if (flowbins) {
      histo[index]->SetBinContent(1, histo[index]->GetBinContent(1) + histo[index]->GetBinContent(0));
      histo[index]->SetBinContent(histo[index]->GetNbinsX(), histo[index]->GetBinContent(histo[index]->GetNbinsX()) + histo[index]->GetBinContent(histo[index]->GetNbinsX() + 1));
      histo[index]->SetBinError(1, TMath::Sqrt(TMath::Power(histo[index]->GetBinError(1), 2) + TMath::Power(histo[index]->GetBinError(0), 2)));
      histo[index]->SetBinError(histo[index]->GetNbinsX(), TMath::Sqrt(TMath::Power(histo[index]->GetBinError(histo[index]->GetNbinsX()), 2) + TMath::Power(histo[index]->GetBinError(histo[index]->GetNbinsX() + 1), 2)));
      histo[index]->SetBinContent(0, 0.);
      histo[index]->SetBinContent(histo[index]->GetNbinsX() + 1, 0.);
      histo[index]->SetBinError(0, 0.);
      histo[index]->SetBinError(histo[index]->GetNbinsX() + 1, 0.);
    }
    if (index > 0){
      h_mc_sum->Add(it->second);
      if (index == 10 || index == 11 || index == 21 || index == 22 || index == 1010 || index == 1011 || index == 1021 || index == 1022) {
        h_mc_sgn->Add(it->second);
      }
      if (index != 10 && index != 11 && index != 21 && index != 22 && index != 1010 && index != 1011 && index != 1021 && index != 1022) {
        h_mc_bkg->Add(it->second);
      }
    }
  }

  map<int, TH2D*> histo2;

  lumi = 0.;
  lumi2016 = 0.;
  lumi2017 = 0.;
  lumi2018 = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      TFile* file = new TFile(("data/" + version + "/" + flags + "/" + it->first + ".root").c_str());
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
      if (histo2[index]) {
        TH2D* h2 = (TH2D*)gDirectory->Get((title.substr(0, 8) + "_misid").c_str());
        if (h2) {
          histo2[index]->Add(h2);
        }
      } else {
        TH2D* h2 = (TH2D*)gDirectory->Get((title.substr(0, 8) + "_misid").c_str());
        if (h2) {
          histo2[index] = h2;
          histo2[index]->SetDirectory(0);
        } else {
          Error("plot0", "skip missing histogram: %s", (title.substr(0, 8) + "_misid").c_str());
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
      TFile* file = new TFile(("data/" + version + "/" + flags + "/" + it->first + ".root").c_str());
      if (file->IsZombie()) {
        cout << "ERROR: file " << it->first + ".root" << " is MISSING !!" << endl;
        return;
      }
      double norm = 1.;
      if (xsecMap[it->first] != 0) {
        double ngen = ((TH2D*)gDirectory->Get("h_nevt"))->GetBinContent(2);
        norm = xsecMap[it->first] * 1000. * lumi / ngen;
        if (it->first.find("RunIISummer16") != string::npos) norm = norm * lumi2016 / lumi;
        if (it->first.find("RunIIFall17") != string::npos) norm = norm * lumi2017 / lumi;
        if (it->first.find("RunIIAutumn18") != string::npos) norm = norm * lumi2018 / lumi;
      } else {
        cout << "ERROR: cross section for " << it->first << " is ZERO !!" << endl;
        return;
      }
      if (histo2[index]) {
        TH2D* h = (TH2D*)gDirectory->Get((title.substr(0, 8) + "_misid").c_str());
        if (h) {
          histo2[index]->Add(h, norm);
        }
      } else {
        TH2D* h = (TH2D*)gDirectory->Get((title.substr(0, 8) + "_misid").c_str());
        if (h) {
          histo2[index] = h;
          histo2[index]->SetDirectory(0);
          histo2[index]->Scale(norm);
        }
      }
      file->Close();
      delete file;
    }
  }

  for (map<int, TH2D*>::reverse_iterator it = histo2.rbegin(); it != histo2.rend(); it++) {
    int index = int(it->first);
    if (flowbins) {
      for (int i = 0; i < histo2[index]->GetNbinsX() + 1; i++) {
        histo2[index]->SetBinContent(i, 1, histo2[index]->GetBinContent(i, 1) + histo2[index]->GetBinContent(i, 0));
        histo2[index]->SetBinContent(i, histo2[index]->GetNbinsY(), histo2[index]->GetBinContent(i, histo2[index]->GetNbinsY()) + histo2[index]->GetBinContent(i, histo2[index]->GetNbinsY() + 1));
        histo2[index]->SetBinError(i, 1, TMath::Sqrt(TMath::Power(histo2[index]->GetBinError(i, 1), 2) + TMath::Power(histo2[index]->GetBinError(i, 0), 2)));
        histo2[index]->SetBinError(i, histo2[index]->GetNbinsY(), TMath::Sqrt(TMath::Power(histo2[index]->GetBinError(i, histo2[index]->GetNbinsY()), 2) + TMath::Power(histo2[index]->GetBinError(i, histo2[index]->GetNbinsY() + 1), 2)));
        histo2[index]->SetBinContent(i, 0, 0.);
        histo2[index]->SetBinContent(i, histo2[index]->GetNbinsY() + 1, 0.);
        histo2[index]->SetBinError(i, 0, 0.);
        histo2[index]->SetBinError(i, histo2[index]->GetNbinsY() + 1, 0.);
      }
    }
  }
  
  TH1D* h_weight = (TH1D*)histo[0]->Clone("h_weight");
  h_weight->Reset();

  TH1D* h_sgn = (TH1D*)histo[0]->Clone("h_sgn");
  h_sgn->Reset();

  TH1D* h_bkg = (TH1D*)histo[0]->Clone("h_bkg");
  h_bkg->Reset();

  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("default") != string::npos) version = version + ".default";

  if (useMC) {
    float fitval = 0.;
    float fiterr = 0.;
    int index = 9001;
    ifstream file1;
    if (title.find("h_WG_") != string::npos) {
      file1.open(("html/" + version + "/" + flags + "/" + year + ".qcd/root/" + "h_WG_" + title.substr(5, 3) + "_qcd_fit.dat").c_str());
    }
    if (file1.is_open()) {
      file1 >> fitval >> fiterr;
      file1.close();
      TFile* file2 = new TFile(("html/" + version + "/" + flags + "/" + year + ".qcd/root/" + title + "_qcd_nofit.root").c_str());
      if (!file2->IsZombie()) {
        histo[index] = (TH1D*)gDirectory->Get((title + "_qcd_nofit").c_str());
        histo[index]->SetDirectory(0);
        histo[index]->Scale(fitval);
        file2->Close();
        delete file2;
      }
    }
  }

  int index1 = -1.;

  if (plot.find("Zgg") != string::npos) index1 = 10;
  if (plot.find("Wgg") != string::npos) index1 = 1010;

  for (map<int, TH2D*>::reverse_iterator it = histo2.rbegin(); it != histo2.rend(); it++) {
    int index = int(it->first);
    if (index == 11 || index == 21 || index == 22 || index == 1011 || index == 1020 || index == 1021 || index == 1022 || index == 9001) {
      histo2[index1]->Add(histo2[index]);
    }
  }

  for (int i = 0; i < histo2[0]->GetNbinsY() + 1; i++) {
    double s0 = -1;
    double s1 = -1;
    double s2 = -1;
    double s3 = -1;

    double d0 = -1;
    double d0_err = -1;
    double d1 = -1;
    double d1_err = -1;
    double d2 = -1;
    double d3 = -1;

    double s0_b = histo2[index1]->GetBinContent(1, i);
    double s1_b = histo2[index1]->GetBinContent(2, i);
    double s2_b = histo2[index1]->GetBinContent(3, i);
    double s3_b = histo2[index1]->GetBinContent(4, i);

    double d0_b = histo2[0]->GetBinContent(1, i);
    double d0_b_err = histo2[0]->GetBinError(1, i);
    double d1_b = histo2[0]->GetBinContent(2, i);
    double d1_b_err = histo2[0]->GetBinError(2, i);
    double d2_b = histo2[0]->GetBinContent(3, i);
    double d3_b = histo2[0]->GetBinContent(4, i);

    double s0_e = histo2[index1]->GetBinContent(1+4, i);
    double s1_e = histo2[index1]->GetBinContent(2+4, i);
    double s2_e = histo2[index1]->GetBinContent(3+4, i);
    double s3_e = histo2[index1]->GetBinContent(4+4, i);

    double d0_e = histo2[0]->GetBinContent(1+4, i);
    double d0_e_err = histo2[0]->GetBinError(1+4, i);
    double d1_e = histo2[0]->GetBinContent(2+4, i);
    double d1_e_err = histo2[0]->GetBinError(2+4, i);
    double d2_e = histo2[0]->GetBinContent(3+4, i);
    double d3_e = histo2[0]->GetBinContent(4+4, i);

    s0 = s0_b + s0_e;
    s1 = s1_b + s1_e;
    s2 = s2_b + s2_e;
    s3 = s3_b + s3_e;

    d0 = d0_b + d0_e;
    d0_err = TMath::Sqrt(TMath::Power(d0_b_err, 2)+TMath::Power(d0_e_err, 2));
    d1 = d1_b + d1_e;
    d1_err = TMath::Sqrt(TMath::Power(d1_b_err, 2)+TMath::Power(d1_e_err, 2));
    d2 = d2_b + d2_e;
    d3 = d3_b + d3_e;

    double b2 = d2 - s2;
    double b3 = d3 - s3;

    if (b2 < 0) b2 = 0.;
    if (b3 < 0) b3 = 0.;
    if (s0 < 0) s0 = 0.;
    if (s1 < 0) s1 = 0.;

    double s0s1 = s0 + s1;
    double b2b3 = b2 + b3;

    if (b2b3 == 0) b2b3 = 1.;
    if (s0s1 == 0) s0s1 = 1.;

    double s0_err = TMath::Sqrt((s0*s1)/TMath::Power(s0s1, 3));
    double b2_err = TMath::Sqrt((b2*b3)/TMath::Power(b2b3, 3));

    s0 = s0/s0s1;
    b2 = b2/b2b3;

    double dalphagamma_ds0 = b2 * ((b2 - 1) * d0 + b2 * d1)/TMath::Power(b2 - s0, 2) * s0_err;
    double dalphagamma_db2 = s0 * ((s0 - 1) * d0 + s0 * d1)/TMath::Power(b2 - s0, 2) * b2_err;
    double dalphagamma_dd0 = ((b2 - 1) * s0) / (b2 - s0) * d0_err;
    double dalphagamma_dd1 = (b2 * s0) / (b2 - s0) * d1_err;

    double dalphajet_ds0 = b2 * ((b2 - 1) * d0 + b2 * d1)/TMath::Power(b2 - s0, 2) * s0_err;
    double dalphajet_db2 = s0 * ((s0 - 1) * d0 + s0 * d1)/TMath::Power(b2 - s0, 2) * b2_err;
    double dalphajet_dd0 = ((s0 - 1) * b2)/(b2 - s0) * d0_err;
    double dalphajet_dd1 = (b2 * s0) / (b2 - s0) * d1_err;

    double alpha_gamma_err = TMath::Sqrt( TMath::Power(dalphagamma_ds0, 2) + TMath::Power(dalphagamma_db2, 2) + TMath::Power(dalphagamma_dd0, 2) + TMath::Power(dalphagamma_dd1, 2));
    double alpha_jet_err = TMath::Sqrt( TMath::Power(dalphajet_ds0, 2) + TMath::Power(dalphajet_db2, 2) + TMath::Power(dalphajet_dd0, 2) + TMath::Power(dalphajet_dd1, 2));

    TMatrixD matrix(2,2);
    matrix(0,0) = s0;
    matrix(0,1) = b2;
    matrix(1,0) = 1-s0;
    matrix(1,1) = 1-b2;

    double det = -1.;

    matrix.Invert(&det);

    TVectorD vector_d(2);
    vector_d[0] = d0;
    vector_d[1] = d1;

    TVectorD vector_alpha(2);
    vector_alpha = matrix * vector_d;

    double alpha_gamma = vector_alpha[0]*s0;
    double alpha_jet = vector_alpha[1]*b2;

    if (alpha_gamma < 0 && alpha_jet > 0) {
      alpha_jet = alpha_jet+alpha_gamma;
      alpha_gamma = 0;
    }
    if (alpha_gamma > 0 && alpha_jet < 0) {
      alpha_gamma = alpha_jet+alpha_gamma;
      alpha_jet = 0;
    }

    if (useMC) {
      alpha_gamma = h_mc_sgn->GetBinContent(i);
      alpha_gamma_err = h_mc_sgn->GetBinError(i);
      alpha_jet = h_mc_bkg->GetBinContent(i);
      alpha_jet_err = h_mc_bkg->GetBinError(i);
    }

    if (alpha_gamma > -1e20 && alpha_gamma < 1e20 && alpha_jet > -1e20 && alpha_jet < 1e20 && (alpha_gamma + alpha_jet) != 0) {
      h_weight->SetBinContent(i, alpha_gamma/(alpha_gamma+alpha_jet));
    } else {
      h_weight->SetBinContent(i, 0.);
    }

    if (alpha_gamma > -1e20 && alpha_gamma < 1e20) {
      h_sgn->SetBinContent(i, alpha_gamma);
      h_sgn->SetBinError(i, alpha_gamma_err);
    } else {
      h_sgn->SetBinContent(i, 0.);
      h_sgn->SetBinError(i, 0.);
    }
    if (alpha_jet > -1e20 && alpha_jet < 1e20) {
      h_bkg->SetBinContent(i, alpha_jet);
      h_bkg->SetBinError(i, alpha_jet_err);
    } else {
      h_bkg->SetBinContent(i, 0.);
      h_bkg->SetBinError(i, 0.);
    }

  }

  h_bkg->SetFillColor(kBlue);
  h_sgn->SetFillColor(kYellow);

  THStack* hstack_mc = new THStack("hstack_mc", "hstack_mc");
  hstack_mc->Add(h_bkg);
  hstack_mc->Add(h_sgn);

  TH1D* h_sum = (TH1D*)h_bkg->Clone("h_sum");
  h_sum->Add(h_sgn);

  TH1D* h_ratio = (TH1D*)histo[0]->Clone("h_ratio");
  h_ratio->Divide(h_sum);

  TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
  c1->cd();

  TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
  pad1->SetBottomMargin(0.001);
  pad1->Draw();
  pad1->cd();

  hstack_mc->SetMinimum(1.0);
  hstack_mc->SetMaximum((1.2*TMath::Max(hstack_mc->GetMaximum(), histo[0]->GetMaximum())));

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

  pad1->SetLogy();
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

  while (gSystem->AccessPathName(("html/" + version + "/" + flags + "/" + year + ".matrix/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flags + "/" + year + ".matrix/").c_str(), kTRUE);
  }
  c1->SaveAs(("html/" + version + "/" + flags + "/" + year + ".matrix/" + title +"_consistency.pdf").c_str());

  while (gSystem->AccessPathName(("html/" + version + "/" + flags + "/" + year + ".matrix/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flags + "/" + year + ".matrix/root/").c_str(), kTRUE);
  }
  TFile* file = new TFile(("html/" + version + "/" + flags + "/" + year + ".matrix/root/matrix_weight.root").c_str(), "update");
  h_weight->Write((title.substr(0, 8) + "_weight").c_str());
  file->Close();
  delete file;

}

int main(int argc, char *argv[]) {

plot3(argv[1], argv[2], argv[3], argv[4]);

}
