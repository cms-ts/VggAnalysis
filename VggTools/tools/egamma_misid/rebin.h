#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TMath.h"

TH1D* rebin(TH1D* old) {

  string name = old->GetName();

  int nb = 0;
  float nbins[25];

  nb = 25;
  for (int i = 0; i < 25; i++){
    nbins[i] = 2;
  }

  if (old->GetNbinsX() == nb) {
    cout << "ERROR: " << name << " already binned" << endl;
    return old;
  }

  int n = 0;
  for (int i = 0; i < nb; i++) {
    n = n + nbins[i];
  }
  if (n != old->GetNbinsX()) {
    cout << "ERROR: " << name << " - " << n << " " << old->GetNbinsX() << endl;
    return old;
  }

  int s = 0;
  const int nbs = nb + 1;

#if __clang_major__ > 16
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvla-cxx-extension"
#endif

  double xbins[nbs];

#if __clang_major__ > 16
#pragma clang diagnostic pop
#endif

  for (int i = 0; i < nb + 1; i++) {
    if (i > 0) s = s + nbins[i - 1];
    xbins[i] = old->GetXaxis()->GetBinUpEdge(s);
  }

  TH1D* tmp = new TH1D("tmp", old->GetTitle(), nb, xbins);

  for (int i = 0; i < old->GetXaxis()->GetNbins()+2; i++) {
    float c1 = old->GetBinContent(i);
    float e1 = old->GetBinError(i);
    float c1b = tmp->GetBinContent(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)));
    float e1b = tmp->GetBinError(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)));
    tmp->SetBinContent(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), c1+c1b);
    tmp->SetBinError(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), TMath::Sqrt(e1*e1+e1b*e1b));
  }

  old->Delete();
  tmp->SetName(name.c_str());

  return tmp;
}
