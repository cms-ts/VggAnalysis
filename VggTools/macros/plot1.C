#include "plot1.h"

TH1D* h_fit1 = 0;
TH1D* h_fit2 = 0;

void fcn(int& npar, double* gin, double& fun, double* par, int iflag) {
  double chisq = 0.0;
  if (npar) {}
  if (iflag) {}
  if (gin) {}
  for (int i = 1; i < h_fit1->FindBin(40.); i++) {
    double xn = h_fit1->GetBinContent(i);
    double xd = TMath::Power(h_fit1->GetBinError(i),2);
    xn = xn - par[0]*h_fit2->GetBinContent(i);
    xd = xd + TMath::Power(par[0]*h_fit2->GetBinError(i),2);

    if (xd!=0) chisq = chisq + (xn*xn)/xd;
  }
  fun = chisq;
}

void plot1(string plot="", string title="", string version="v00", string flags="") {

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";

  plot = plot + ".dat";
  if (flags.find("test") != string::npos) plot = plot + ".test";
  if (flags.find("new") != string::npos) plot = plot + ".new";

  if (flags.find("amcatnlo") != string::npos) plot = "amcatnlo/" + plot;
  if (flags.find("madgraph") != string::npos) plot = "madgraph/" + plot;

  multimap<string, float> plotMap;
  readMultiMap(plot, plotMap);
  cout << "Read plot map for " << plotMap.size() << " datasets from " << plot << endl;

  if (plotMap.size() == 0) {
    cout << "ERROR: plot map " << plot << " is EMPTY or MISSING !!" << endl;
    return;
  }

  if (flags.find("test") != string::npos) version = version + ".test";
  if (flags.find("new") != string::npos) version = version + ".new";

  if (flags.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (flags.find("madgraph") != string::npos) version = version + ".madgraph";

  TFile* f1 = new TFile(("html/" + version + "/" + year + "/root/" + title + "_nofit.root").c_str());
  TFile* f2 = new TFile(("html/" + version + "/" + year + ".qcd/root/" + title + "_qcd_nofit.root").c_str());

  TH1D* h1 = (TH1D*)f1->Get((title + "_nofit").c_str());
  TH1D* h2 = (TH1D*)f2->Get((title + "_qcd_nofit").c_str());

  h1->SetDirectory(0);
  h2->SetDirectory(0);

  f1->Close();
  f2->Close();

  delete f1;
  delete f2;

  h_fit1 = (TH1D*)h1->Clone("h_fit1");
  h_fit2 = (TH1D*)h2->Clone("h_fit2");

  TVirtualFitter::SetDefaultFitter("Minuit");
  TVirtualFitter* fitter = 0;
  fitter = TVirtualFitter::Fitter(0, 1);
  fitter->SetFCN(fcn);
  double arglist[1] = {-1.0};
  fitter->ExecuteCommand("SET PRINT", arglist, 1);
  fitter->SetParameter(0, "c_qcd", 1.0, 0.1, 0., 999.);
  fitter->ExecuteCommand("MIGRAD",arglist, 0);

  h2->Scale(fitter->GetParameter(0));

  TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
  c1->cd();

  h1->Draw();
  h2->Draw("same");
  h2->SetLineColor(kRed);

  c1->Update();
  TBox* box1 = new TBox(40., c1->GetFrame()->GetY1(), c1->GetFrame()->GetX2(), c1->GetFrame()->GetY2());
  box1->SetFillStyle(3344);
  box1->SetFillColor(kGray);
  box1->Draw();
  TBox* box2 = (TBox*)box1->Clone();
  box2->SetFillStyle(0);
  box2->SetLineColor(kGray);
  box2->Draw();

  h1->Draw("same");
  h2->Draw("same");

  TLatex* label = new TLatex();
  label->SetTextSize(0.0275);
  label->SetTextFont(42);
  label->SetLineWidth(2);
  label->SetNDC();
  char buff[100];
  sprintf(buff, "c_{qcd} = %5.3f #pm %5.3f", fitter->GetParameter(0), fitter->GetParError(0));
  label->DrawLatex(0.50, 0.68, buff);

  while (gSystem->AccessPathName(("html/" + version + "/" + year + ".qcd/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + year + ".qcd/root/").c_str(), kTRUE);
  }
  c1->SaveAs(("html/" + version + "/" + year + ".qcd/root/" + title + "_qcd_fit.pdf").c_str());

  ofstream out;
  out.open(("html/" + version + "/" + year + ".qcd/root/" + title + "_qcd_fit.dat").c_str());
  out << fitter->GetParameter(0) << " " << fitter->GetParError(0) << endl;
  out.close();

}
