#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "Riostream.h"
#include "TMath.h"
#include "TStyle.h"

double CMSshape_prenorm(double* x, double* p) {

  double alpha = p[0];
  double beta = p[1];
  double peak = p[2];
  double gamma = p[3];

  double erf = RooMath::erfc((alpha - x[0]) * beta);
  double u = (x[0] - peak) * gamma;

  double fitval;

  if (u < -70)
    u = 1e20;
  else if (u > 70)
    u = 0;
  else
    u = exp(-u);  //exponential decay

  fitval = erf*u;
  return fitval;
}

double CMSshape(double* x, double* p) {

  double alpha = p[0];
  double beta = p[1];
  double peak = p[2];
  double gamma = p[3];
  double norm = p[4];

  double erf = RooMath::erfc((alpha - x[0]) * beta);
  double u = (x[0] - peak) * gamma;

  double fitval;

  if (u < -70)
    u = 1e20;
  else if (u > 70)
    u = 0;
  else
    u = exp(-u);  //exponential decay

  fitval = norm*erf*u;
  return fitval;
}

TH1D* histoFromCurve(TH1D* h_in, TGraph* gr, double alpha, double beta, double peak, double gamma) {

  TH1D* h = (TH1D*)h_in->Clone("h");
  h->Reset();
  
  TF1* f = new TF1("f", CMSshape_prenorm, 40.0, 120.0, 4);
  f->SetParameter(0,alpha);
  f->SetParameter(1,beta);
  f->SetParameter(2,peak);
  f->SetParameter(3,gamma);
  
  double norm = gr->Integral()/f->Integral(40,120);
  
  TF1* ff = new TF1("ff", CMSshape, 40.0, 120.0, 5);
  ff->SetParameter(0,alpha);
  ff->SetParameter(1,beta);
  ff->SetParameter(2,peak);
  ff->SetParameter(3,gamma);
  ff->SetParameter(4,norm);
  
  for (int i = 0; i < h->GetNbinsX()+2; i++) {
    h->SetBinContent(i, ff->Eval(h->GetBinCenter(i)));
    h->SetBinError(i, 0.);
  }
  
  return h;

}
