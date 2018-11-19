#include "plot0.h"

#include "CMS_lumi.C"

void plot0(string plot="", string title="", string version="v00", string test="") {

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";

  map<string, float> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets from " << "lumi.dat" << endl;

  map<string, float> xsecMap;
  readMap("xsec.dat", xsecMap);
  cout << "Read xsec map for " << xsecMap.size() << " datasets from " << "xsec.dat" << endl;

  plot = plot + ".dat";
  if (test.size()) plot = plot + "." + test;

  multimap<string, float> plotMap;
  readMultiMap(plot, plotMap);
  cout << "Read plot map for " << plotMap.size() << " datasets from " << plot << endl;

  if (plotMap.size() == 0) {
    cout << "ERROR: plot map " << plot << " is EMPTY or MISSING !!" << endl;
    return;
  }

  map<int, TH1D*> histo;

  float lumi = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      TFile file(("data/" + version + "/" + it->first + ".root").c_str()); 
      if (lumiMap[it->first] != 0) {
        lumi = lumi + lumiMap[it->first];
      } else {
        cout << "ERROR: luminosity for " << it->first << " is ZERO !!" << endl;
        return;
      }
      if (histo[index]) {
        histo[index]->Add((TH1D*)gDirectory->Get(title.c_str()));
      } else {
        histo[index] = (TH1D*)gDirectory->Get(title.c_str());
        if (histo[index]) {
          histo[index]->SetDirectory(0);
        } else {
          Error("plot0", "skip missing histogram: %s", title.c_str());
          return;
        }
      }
      file.Close();
    }
  }

  double ngen = 0.;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index > 0) {
      TFile file(("data/" + version + "/" + it->first + ".root").c_str()); 
      if (!file.IsOpen()) {
        cout << "ERROR: file " << it->first + ".root" << " is MISSING !!" << endl;
        return;
      }
      ngen = ((TH1D*)gDirectory->Get("h_nevt"))->GetBinContent(2);
      double norm = 1.;
      if (xsecMap[it->first] != 0) {
        norm = xsecMap[it->first] * 1000. * lumi / ngen;
      } else {
        cout << "ERROR: cross section for " << it->first << " is ZERO !!" << endl;
        return;
      }
      if (histo[index]) {
        histo[index]->Add((TH1D*)gDirectory->Get(title.c_str()), norm);
      } else {
        histo[index] = (TH1D*)gDirectory->Get(title.c_str());
        histo[index]->SetDirectory(0);
        histo[index]->Scale(norm);
      }
      file.Close();
    }
  }

  THStack* hstack_mc = new THStack("hstack_mc", "hstack_mc");

  TH1D* h_mcsum = (TH1D*) histo[0]->Clone("h_mcsum");
  h_mcsum->Reset();  

  TLegend* leg = new TLegend(0.65, 0.640, 0.91, 0.88);
  leg->SetBorderSize(0);
  leg->SetEntrySeparation(0.01);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);

  for (map<int, TH1D*>::reverse_iterator it = histo.rbegin(); it != histo.rend(); it++) {
    if (it->first > 0) {
       hstack_mc->Add(it->second);
       h_mcsum->Add(it->second);
    }
  }

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
  }

  TH1D* h_ratio = (TH1D*) histo[0]->Clone();
  h_ratio->Divide(h_mcsum);  

  TCanvas* c1 = 0;
  c1 = new TCanvas("c", "c", 10, 10, 800, 600);
  c1->cd();

  TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
  pad1->SetBottomMargin(0.001);
  pad1->Draw();
  pad1->cd();
  pad1->SetLogy();

  hstack_mc->Draw("HIST");

  hstack_mc->SetTitle("");

  hstack_mc->GetXaxis()->SetTitleOffset(0.7);
  hstack_mc->GetXaxis()->SetLabelSize(0.08);

  hstack_mc->GetYaxis()->SetTitle("Events");
  hstack_mc->GetYaxis()->SetTitleSize(0.05);
  hstack_mc->GetYaxis()->SetTitleOffset(1.0);
  hstack_mc->GetYaxis()->SetLabelSize(0.045);
  hstack_mc->SetMinimum(0.5);

  histo[0]->SetStats(0);
  histo[0]->SetMarkerColor(kBlack);
  histo[0]->SetMarkerStyle(20);
  histo[0]->SetMarkerSize (1.0);

  histo[0]->Draw("HISTSAMES");
  histo[0]->Draw("EXP0SAMES");

  leg->Draw();

  pad1->Update();
  c1->Update();
  c1->cd();

  TPad* pad2 = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->Draw();
  pad2->cd();

  h_ratio->SetTitle("");
  h_ratio->SetStats(0);

  if (title == "h_W_ele" || title == "h_W_muo") {
    h_ratio->GetXaxis()->SetTitle("M_{T} [GeV]");
  }

  if (title == "h_Z_ele" || title == "h_Z_muo") {
    h_ratio->GetXaxis()->SetTitle("M_{ll} [GeV]");
  }

  h_ratio->GetXaxis()->SetTitleFont(42);
  h_ratio->GetXaxis()->SetTitleSize(0.11);
  h_ratio->GetXaxis()->SetTitleOffset(1.1);
  h_ratio->GetXaxis()->SetLabelFont(42);
  h_ratio->GetXaxis()->SetLabelSize(0.10);

  h_ratio->GetYaxis()->SetTitle("Data/MC");
  h_ratio->GetYaxis()->SetTitleSize(0.11);
  h_ratio->GetYaxis()->SetTitleOffset(0.47);
  h_ratio->GetYaxis()->SetLabelSize(0.10);
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

  if (test.size()) version = version + "." + test;

  gSystem->mkdir(("html/" + version + "/" + year + "/").c_str(), kTRUE);
  c1->SaveAs(("html/" + version + "/" + year + "/" + title + ".pdf").c_str());

}
