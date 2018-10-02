#include "plot0.h"

void plot0(string plot="", string title="") {

  string version = "v00";

  map<string, float> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets" << endl;

  map<string, float> xsecMap;
  readMap("xsec.dat", xsecMap);
  cout << "Read xsec map for " << xsecMap.size() << " datasets" << endl;

  multimap<string, float> plotMap;
  readMultiMap(plot, plotMap);
  cout << "Read plot map for " << plotMap.size() << " datasets" << endl;

  map<int, TH1D*> histo;

  float lumi = 0.0;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index == 0) {
      TFile file(("data/" + version + "/" + it->first + ".root").c_str()); 
      lumi = lumi + lumiMap[it->first];
      if (histo[index]) {
        histo[index]->Add((TH1D*)gDirectory->Get(title.c_str()));
      } else {
        histo[index] = (TH1D*)gDirectory->Get(title.c_str());
        histo[index]->SetDirectory(0);
      }
      file.Close();
    }
  }

  int ngen = 0;

  for (multimap<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    int index = int(it->second);
    if (index > 0) {
      TFile file(("data/" + version + "/" + it->first + ".root").c_str()); 
      ngen = ((TH1D*)gDirectory->Get("h_nevt"))->GetBinContent(1);
      float norm = xsecMap[it->first]*1000*lumi/ngen;
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
    if (it->first == 0) {
      leg->AddEntry(it->second, "Data", "p");
    }
    if (it->first == 10) {
      it->second->SetFillColor(kYellow-4);
      leg->AddEntry(it->second, "Drell-Yan", "f");
    }
    if (it->first == 20) {
      it->second->SetFillColor(kBlue);
      leg->AddEntry(it->second, "TTJets", "f");
    }
    if (it->first == 30) {
      it->second->SetFillColor(kBlue-4);
      leg->AddEntry(it->second, "ZZ", "f");
    }

  }

  TH1D* h_ratio = (TH1D*) histo[0]->Clone();
  h_ratio->Divide(h_mcsum);  

  TCanvas* c1 = 0;
  c1 = new TCanvas("c", "c", 10, 10, 600, 600);
  c1->cd();

  TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
  pad1->SetBottomMargin(0.001);
  pad1->Draw();
  pad1->cd();
  pad1->SetLogy();

  histo[0]->SetTitle("");
  histo[0]->SetStats(0);

  histo[0]->GetXaxis()->SetTitleOffset(0.7);
  histo[0]->GetXaxis()->SetLabelSize(0.08);

  histo[0]->GetYaxis()->SetTitle("Events");
  histo[0]->GetYaxis()->SetTitleSize(0.05);
  histo[0]->GetYaxis()->SetTitleOffset(1.0);
  histo[0]->GetYaxis()->SetLabelSize(0.045);
  histo[0]->SetMinimum(0.5);

  histo[0]->SetMarkerColor(kBlack);
  histo[0]->SetMarkerStyle(20);
  histo[0]->SetMarkerSize (1.0);
  histo[0]->Draw("HIST");
  histo[0]->Draw("EPX0SAMES");

  hstack_mc->Draw("HSAME");

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

  if (title == "h_Z_ele" || title == "h_Z_muo") {
    h_ratio->GetXaxis()->SetTitle("Invariant mass [GeV]");
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

  gSystem->mkdir(("html/" + version).c_str(), kTRUE);
  c1->SaveAs(("html/" + version + "/" + title + ".pdf").c_str());

}
